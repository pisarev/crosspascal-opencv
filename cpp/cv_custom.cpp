

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_custom.h"
#include "helper.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>


// The Doxa-named API uses the local image and thresholding routines below.
namespace Doxa {

class Image {
public:
    int width;
    int height;
    uint8_t *data;
    bool ownsData;

    Image() : width(0), height(0), data(nullptr), ownsData(false) {}
    Image(int w, int h) : width(w), height(h), ownsData(true) {
        data = new uint8_t[w * h];
        memset(data, 0, w * h);
    }
    ~Image() {
        if (ownsData && data) {
            delete[] data;
            data = nullptr;
        }
    }

    uint8_t& pixel(int x, int y) { return data[y * width + x]; }
    uint8_t pixel(int x, int y) const { return data[y * width + x]; }
    int size() const { return width * height; }
};


static void computeIntegralImages(const Image &src,
                                   std::vector<double> &integralSum,
                                   std::vector<double> &integralSqSum)
{
    int w = src.width;
    int h = src.height;
    integralSum.resize((w + 1) * (h + 1), 0.0);
    integralSqSum.resize((w + 1) * (h + 1), 0.0);

    for (int y = 0; y < h; y++) {
        double rowSum = 0.0;
        double rowSqSum = 0.0;
        for (int x = 0; x < w; x++) {
            double val = src.pixel(x, y);
            rowSum += val;
            rowSqSum += val * val;
            integralSum[(y + 1) * (w + 1) + (x + 1)] = integralSum[y * (w + 1) + (x + 1)] + rowSum;
            integralSqSum[(y + 1) * (w + 1) + (x + 1)] = integralSqSum[y * (w + 1) + (x + 1)] + rowSqSum;
        }
    }
}

static void getLocalStats(const std::vector<double> &integralSum,
                           const std::vector<double> &integralSqSum,
                           int W, int x, int y, int winSize,
                           double &mean, double &stddev)
{
    int halfWin = winSize / 2;
    int x1 = std::max(0, x - halfWin);
    int y1 = std::max(0, y - halfWin);
    int x2 = std::min(W - 1, x + halfWin);
    int y2 = std::min((int)(integralSum.size() / (W + 1)) - 2, y + halfWin);

    int count = (x2 - x1 + 1) * (y2 - y1 + 1);
    if (count <= 0) { mean = 0; stddev = 0; return; }

    int stride = W + 1;
    double sum = integralSum[(y2 + 1) * stride + (x2 + 1)]
               - integralSum[(y1) * stride + (x2 + 1)]
               - integralSum[(y2 + 1) * stride + (x1)]
               + integralSum[(y1) * stride + (x1)];

    double sqSum = integralSqSum[(y2 + 1) * stride + (x2 + 1)]
                 - integralSqSum[(y1) * stride + (x2 + 1)]
                 - integralSqSum[(y2 + 1) * stride + (x1)]
                 + integralSqSum[(y1) * stride + (x1)];

    mean = sum / count;
    double variance = (sqSum / count) - (mean * mean);
    stddev = (variance > 0) ? std::sqrt(variance) : 0.0;
}


static void niblackThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            double threshold = mean + k * stddev;
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}

static void sauvolaThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    const double R = 128.0;
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            double threshold = mean * (1.0 + k * (stddev / R - 1.0));
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}

static void wolfThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);


    double globalMinGray = 255.0;
    double globalMaxStddev = 0.0;
    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            if (src.pixel(x, y) < globalMinGray)
                globalMinGray = src.pixel(x, y);
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            if (stddev > globalMaxStddev)
                globalMaxStddev = stddev;
        }
    }

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            double R = globalMaxStddev;
            double threshold = mean - k * (1.0 - stddev / (R > 0 ? R : 1.0)) * (mean - globalMinGray);
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}

static void nickThreshold(const Image &src, Image &dst, int windowSize, double k)
{

    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            int halfWin = windowSize / 2;
            int x1 = std::max(0, x - halfWin);
            int y1 = std::max(0, y - halfWin);
            int x2 = std::min(src.width - 1, x + halfWin);
            int y2 = std::min(src.height - 1, y + halfWin);
            int count = (x2 - x1 + 1) * (y2 - y1 + 1);

            int stride = src.width + 1;
            double sum = integralSum[(y2 + 1) * stride + (x2 + 1)]
                       - integralSum[(y1) * stride + (x2 + 1)]
                       - integralSum[(y2 + 1) * stride + (x1)]
                       + integralSum[(y1) * stride + (x1)];

            double sqSum = integralSqSum[(y2 + 1) * stride + (x2 + 1)]
                         - integralSqSum[(y1) * stride + (x2 + 1)]
                         - integralSqSum[(y2 + 1) * stride + (x1)]
                         + integralSqSum[(y1) * stride + (x1)];

            double mean = sum / count;
            double val = std::sqrt((sqSum - mean * mean * count) / count);
            double threshold = mean + k * val;
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}

static void otsuThreshold(const Image &src, Image &dst)
{

    cv::Mat srcMat(src.height, src.width, CV_8UC1, src.data);
    cv::Mat dstMat(dst.height, dst.width, CV_8UC1, dst.data);
    cv::threshold(srcMat, dstMat, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

}


static void trsinghThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    const double p = 2.0;
    const double q = 0.1;
    const double R = 128.0;
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            double threshold = mean * (1.0 + p * std::exp(-q * mean) + k * (stddev / R - 1.0));
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}


// This variant uses a fixed local window and the global standard deviation.

static void batainehThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);


    double globalMean = 0.0, globalSqMean = 0.0;
    int total = src.width * src.height;
    for (int i = 0; i < total; i++) {
        double val = src.data[i];
        globalMean += val;
        globalSqMean += val * val;
    }
    globalMean /= total;
    globalSqMean /= total;
    double globalStddev = std::sqrt(std::max(0.0, globalSqMean - globalMean * globalMean));
    if (globalStddev < 1.0) globalStddev = 1.0;

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            double threshold = mean * (1.0 + k * (1.0 - stddev / globalStddev));
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}


// Like Sauvola but with dynamic R based on maximum local standard deviation

static void isauvolaThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);


    double maxStddev = 0.0;
    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            if (stddev > maxStddev) maxStddev = stddev;
        }
    }
    double R = (maxStddev > 0) ? maxStddev : 128.0;


    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);
            double threshold = mean * (1.0 + k * (stddev / R - 1.0));
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}


static void suThreshold(const Image &src, Image &dst, int windowSize, double)
{
    int halfWin = windowSize / 2;
    int w = src.width;
    int h = src.height;


    std::vector<double> contrast(w * h, 0.0);
    std::vector<uint8_t> localMinMap(w * h, 0);
    std::vector<uint8_t> localMaxMap(w * h, 0);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int x1 = std::max(0, x - halfWin);
            int y1 = std::max(0, y - halfWin);
            int x2 = std::min(w - 1, x + halfWin);
            int y2 = std::min(h - 1, y + halfWin);

            uint8_t mn = 255, mx = 0;
            for (int yy = y1; yy <= y2; yy++) {
                for (int xx = x1; xx <= x2; xx++) {
                    uint8_t v = src.pixel(xx, yy);
                    if (v < mn) mn = v;
                    if (v > mx) mx = v;
                }
            }
            localMinMap[y * w + x] = mn;
            localMaxMap[y * w + x] = mx;
            contrast[y * w + x] = (mx + mn > 0) ?
                (double)(mx - mn) / (double)(mx + mn) : 0.0;
        }
    }


    double cMean = 0.0;
    for (int i = 0; i < w * h; i++) cMean += contrast[i];
    cMean /= (w * h);

    double cStd = 0.0;
    for (int i = 0; i < w * h; i++) {
        double d = contrast[i] - cMean;
        cStd += d * d;
    }
    cStd = std::sqrt(cStd / (w * h));
    double edgeThreshold = cMean + cStd / 2.0;


    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (contrast[y * w + x] >= edgeThreshold) {

                double threshold = (localMinMap[y * w + x] + localMaxMap[y * w + x]) / 2.0;
                dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
            } else {

                double mean, stddev;
                getLocalStats(integralSum, integralSqSum, w, x, y, windowSize, mean, stddev);
                dst.pixel(x, y) = (src.pixel(x, y) > mean) ? 255 : 0;
            }
        }
    }
}


static void wanThreshold(const Image &src, Image &dst, int windowSize, double k)
{
    const double R = 128.0;
    std::vector<double> integralSum, integralSqSum;
    computeIntegralImages(src, integralSum, integralSqSum);

    int halfWin = windowSize / 2;
    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            double mean, stddev;
            getLocalStats(integralSum, integralSqSum, src.width, x, y, windowSize, mean, stddev);


            int x1 = std::max(0, x - halfWin);
            int y1 = std::max(0, y - halfWin);
            int x2 = std::min(src.width - 1, x + halfWin);
            int y2 = std::min(src.height - 1, y + halfWin);
            uint8_t localMin = 255;
            for (int yy = y1; yy <= y2; yy++) {
                for (int xx = x1; xx <= x2; xx++) {
                    if (src.pixel(xx, yy) < localMin) localMin = src.pixel(xx, yy);
                }
            }

            double threshold = mean + k * (stddev / R - 1.0) * (mean - localMin);
            dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
        }
    }
}

static void bernsenThreshold(const Image &src, Image &dst, int windowSize, double)
{
    const int contrastMin = 15;
    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            int halfWin = windowSize / 2;
            int x1 = std::max(0, x - halfWin);
            int y1 = std::max(0, y - halfWin);
            int x2 = std::min(src.width - 1, x + halfWin);
            int y2 = std::min(src.height - 1, y + halfWin);

            uint8_t localMin = 255, localMax = 0;
            for (int yy = y1; yy <= y2; yy++) {
                for (int xx = x1; xx <= x2; xx++) {
                    uint8_t v = src.pixel(xx, yy);
                    if (v < localMin) localMin = v;
                    if (v > localMax) localMax = v;
                }
            }

            int contrast = localMax - localMin;
            if (contrast < contrastMin) {
                // Low contrast region: use midpoint
                dst.pixel(x, y) = ((localMax + localMin) / 2 >= 128) ? 255 : 0;
            } else {
                double threshold = (localMax + localMin) / 2.0;
                dst.pixel(x, y) = (src.pixel(x, y) > threshold) ? 255 : 0;
            }
        }
    }
}

}


CVAPI int cv_custom_toDoxaImage(cv::Mat *mat, void **target)
{
    cv_clear_error();

    try {
        if (!mat || mat->empty()) {
            cv_set_error_literal("Input mat is null or empty");
            return 0;
        }
        cv::Mat gray;
        if (mat->channels() > 1) {
            cv::cvtColor(*mat, gray, cv::COLOR_BGR2GRAY);
        } else {
            gray = *mat;
        }
        if (gray.dims != 2 || gray.type() != CV_8UC1 ||
            (static_cast<int64_t>(gray.cols) + 1) * (static_cast<int64_t>(gray.rows) + 1) >
                std::numeric_limits<int>::max()) {
            cv_set_error_literal("Doxa requires a two-dimensional 8-bit image within the supported size");
            return 0;
        }
        Doxa::Image *img = new Doxa::Image(gray.cols, gray.rows);
        for (int y = 0; y < gray.rows; y++) {
            memcpy(img->data + y * gray.cols, gray.ptr<uint8_t>(y), gray.cols);
        }
        *target = img;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_fromDoxaImage(void *image, cv::Mat **mat)
{
    cv_clear_error();

    try {
        Doxa::Image *img = static_cast<Doxa::Image *>(image);
        if (!img || !img->data) {
            cv_set_error_literal("Doxa image is null");
            return 0;
        }
        cv::Mat result(img->height, img->width, CV_8UC1);
        cv::Mat wrapper(img->height, img->width, CV_8UC1, img->data);
        wrapper.copyTo(result);
        *mat = new cv::Mat(result);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_deleteDoxaImage(void *image)
{
    cv_clear_error();

    try {
        Doxa::Image *img = static_cast<Doxa::Image *>(image);
        if (!img) {
            cv_set_error_literal("Doxa image is null");
            return 0;
        }
        delete img;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_doxaThreshold(void *image, void *dst, int algorithm, double k, double window, double r)
{
    cv_clear_error();

    try {
        Doxa::Image *srcImg = static_cast<Doxa::Image *>(image);
        Doxa::Image *dstImg = static_cast<Doxa::Image *>(dst);
        if (!srcImg || !dstImg) {
            cv_set_error_literal("Doxa image or destination is null");
            return 0;
        }

        if (!std::isfinite(window) || window > std::numeric_limits<int>::max()) {
            cv_set_error_literal("Doxa window size is out of range");
            return 0;
        }

        if (dstImg->width != srcImg->width || dstImg->height != srcImg->height) {
            auto *replacement = new uint8_t[srcImg->size()];
            if (dstImg->ownsData) delete[] dstImg->data;
            dstImg->width = srcImg->width;
            dstImg->height = srcImg->height;
            dstImg->data = replacement;
            dstImg->ownsData = true;
        }

        int windowSize = static_cast<int>(std::max(3.0, window));
        if (windowSize % 2 == 0) windowSize++;

        switch (algorithm) {
            case DTK_OTSU:
                Doxa::otsuThreshold(*srcImg, *dstImg);
                break;
            case DTK_BERNSEN:
                Doxa::bernsenThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_NIBLACK:
                Doxa::niblackThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_SAUVOLA:
                Doxa::sauvolaThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_WOLF:
                Doxa::wolfThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_NICK:
                Doxa::nickThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_SU:
                Doxa::suThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_TRSINGH:
                Doxa::trsinghThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_BATAINEH:
                Doxa::batainehThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_ISAUVOLA:
                Doxa::isauvolaThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            case DTK_WAN:
                Doxa::wanThreshold(*srcImg, *dstImg, windowSize, k);
                break;
            default:
                cv_set_error_cstr(("Unknown Doxa threshold kind: " + std::to_string(algorithm)).c_str());
                return 0;
        }
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_custom_locateTemplate(cv::Mat *source, cv::Mat *templ, double threshold, int method, cv::Mat *mask, SetData *setData, void *data)
{
    cv_clear_error();

    try {
        if (!source || !templ || source->empty() || templ->empty()) {
            cv_set_error_literal("Image or template is null or empty");
            return 0;
        }
        cv::Mat matchResult;
        if (mask && !mask->empty())
            cv::matchTemplate(*source, *templ, matchResult, method, *mask);
        else
            cv::matchTemplate(*source, *templ, matchResult, method);

        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(matchResult, &minVal, &maxVal, &minLoc, &maxLoc);

        cv::Point matchLoc;
        double matchVal;

        if (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED) {
            matchLoc = minLoc;
            matchVal = minVal;
        } else {
            matchLoc = maxLoc;
            matchVal = maxVal;
        }


        bool passThreshold = false;
        if (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED) {
            passThreshold = (matchVal <= threshold);
        } else {
            passThreshold = (matchVal >= threshold);
        }

        if (passThreshold && setData) {
            CVPlace place;
            place.a.x = matchLoc.x;
            place.a.y = matchLoc.y;
            place.b.x = matchLoc.x + templ->cols;
            place.b.y = matchLoc.y + templ->rows;
            place.value = matchVal;
            setData(1, &place);
        }

        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_searchTemplate(cv::Mat *source, cv::Mat *templ, double threshold, int method, cv::Mat *mask, int maxResults, SetMat *setMat, void *data)
{
    cv_clear_error();

    try {
        if (!source || !templ || source->empty() || templ->empty()) {
            cv_set_error_literal("Image or template is null or empty");
            return 0;
        }
        cv::Mat matchResult;
        if (mask && !mask->empty())
            cv::matchTemplate(*source, *templ, matchResult, method, *mask);
        else
            cv::matchTemplate(*source, *templ, matchResult, method);

        int tw = templ->cols;
        int th = templ->rows;


        std::vector<CVPlace> results;
        for (int y = 0; y < matchResult.rows; y++) {
            for (int x = 0; x < matchResult.cols; x++) {
                float val = matchResult.at<float>(y, x);
                bool isMatch = false;
                if (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED) {
                    isMatch = (val <= threshold);
                } else {
                    isMatch = (val >= threshold);
                }
                if (isMatch) {

                    bool suppressed = false;
                    for (size_t i = 0; i < results.size(); i++) {
                        int dx = std::abs(results[i].a.x - x);
                        int dy = std::abs(results[i].a.y - y);
                        if (dx < tw / 2 && dy < th / 2) {
                            suppressed = true;

                            if (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED) {
                                if (val < results[i].value) {
                                    results[i].a.x = x;
                                    results[i].a.y = y;
                                    results[i].b.x = x + tw;
                                    results[i].b.y = y + th;
                                    results[i].value = val;
                                }
                            } else {
                                if (val > results[i].value) {
                                    results[i].a.x = x;
                                    results[i].a.y = y;
                                    results[i].b.x = x + tw;
                                    results[i].b.y = y + th;
                                    results[i].value = val;
                                }
                            }
                            break;
                        }
                    }
                    if (!suppressed) {
                        CVPlace p;
                        p.a.x = x;
                        p.a.y = y;
                        p.b.x = x + tw;
                        p.b.y = y + th;
                        p.value = val;
                        results.push_back(p);
                        if ((int)results.size() >= maxResults)
                            goto done;
                    }
                }
            }
        }
        done:


        if (setMat) {
            int count = (int)results.size();
            for (int i = 0; i < count; i++) {
                double scale = 1.0;
                double angle = 0.0;
                // Extract the matched region as a slice
                cv::Rect roi(results[i].a.x, results[i].a.y, tw, th);
                cv::Mat slice = (*source)(roi);
                cv::Mat *slicePtr = &slice;
                cv::Mat *imgPtr = source;
                int ret = setMat(scale, angle, results[i], &imgPtr, &slicePtr, i, count, data);
                if (ret != 0) break;
            }
        }

        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_custom_createCLAHE(double clipLimit, CVSize tilesGridSize, void **handle)
{
    cv_clear_error();

    try {
        auto clahe = cv::createCLAHE(clipLimit, cv::Size(tilesGridSize.cx, tilesGridSize.cy));
        if (clahe.empty()) {
            cv_set_error_literal("Failed to create CLAHE");
            return 0;
        }
        *handle = new cv::Ptr<cv::CLAHE>(clahe);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_deleteCLAHE(void *clahe)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        delete ptr;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_setClipLimit(void *clahe, double clipLimit)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        (*ptr)->setClipLimit(clipLimit);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_getClipLimit(void *clahe, double *clipLimit)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        *clipLimit = (*ptr)->getClipLimit();
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_setTilesGridSize(void *clahe, CVSize tilesGridSize)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        (*ptr)->setTilesGridSize(cv::Size(tilesGridSize.cx, tilesGridSize.cy));
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_getTilesGridSize(void *clahe, CVSize *tilesGridSize)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        cv::Size sz = (*ptr)->getTilesGridSize();
        tilesGridSize->cx = sz.width;
        tilesGridSize->cy = sz.height;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_collectGarbage(void *clahe)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        (*ptr)->collectGarbage();
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_claheApply(void *clahe, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();

    try {
        if (!clahe) {
            cv_set_error_literal("CLAHE pointer is null");
            return 0;
        }
        cv::Ptr<cv::CLAHE> *ptr = static_cast<cv::Ptr<cv::CLAHE> *>(clahe);
        cv::Mat result;
        (*ptr)->apply(*src, result);
        *dst = new cv::Mat(result);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_custom_varianceOfLaplacian(cv::Mat *src, double *value)
{
    cv_clear_error();

    try {
        if (!src || src->empty()) {
            cv_set_error_literal("Source image is null or empty");
            return 0;
        }
        cv::Mat gray;
        if (src->channels() > 1) {
            cv::cvtColor(*src, gray, cv::COLOR_BGR2GRAY);
        } else {
            gray = *src;
        }
        cv::Mat laplacian;
        cv::Laplacian(gray, laplacian, CV_64F);
        cv::Scalar mu, sigma;
        cv::meanStdDev(laplacian, mu, sigma);
        *value = sigma.val[0] * sigma.val[0];
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_tenengrad(cv::Mat *src, int kSize, double *value)
{
    cv_clear_error();

    try {
        if (!src || src->empty()) {
            cv_set_error_literal("Source image is null or empty");
            return 0;
        }
        cv::Mat gray;
        if (src->channels() > 1) {
            cv::cvtColor(*src, gray, cv::COLOR_BGR2GRAY);
        } else {
            gray = *src;
        }
        if (kSize < 3) kSize = 3;
        cv::Mat gx, gy;
        cv::Sobel(gray, gx, CV_64F, 1, 0, kSize);
        cv::Sobel(gray, gy, CV_64F, 0, 1, kSize);
        cv::Mat fm;
        cv::magnitude(gx, gy, fm);

        cv::Mat fm2;
        cv::multiply(fm, fm, fm2);
        *value = cv::mean(fm2).val[0];
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_normalizedGrayLevelVariance(cv::Mat *src, double *value)
{
    cv_clear_error();

    try {
        if (!src || src->empty()) {
            cv_set_error_literal("Source image is null or empty");
            return 0;
        }
        cv::Mat gray;
        if (src->channels() > 1) {
            cv::cvtColor(*src, gray, cv::COLOR_BGR2GRAY);
        } else {
            gray = *src;
        }
        cv::Scalar mu, sigma;
        cv::meanStdDev(gray, mu, sigma);
        double mean = mu.val[0];
        if (mean < 1e-6) {
            *value = 0.0;
        } else {
            *value = (sigma.val[0] * sigma.val[0]) / mean;
        }
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


// algorithmType: 0 = MOG2, 1 = KNN


struct BGSHolder {
    cv::Ptr<cv::BackgroundSubtractor> subtractor;
    BGSHolder(cv::Ptr<cv::BackgroundSubtractor> s) : subtractor(s) {}
};

CVAPI int cv_custom_createBGSSubtractor(int algorithmType, void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::BackgroundSubtractor> sub;
        switch (algorithmType) {
            case 0:
                sub = cv::createBackgroundSubtractorMOG2();
                break;
            case 1:
                sub = cv::createBackgroundSubtractorKNN();
                break;
            default:

                sub = cv::createBackgroundSubtractorMOG2();
                break;
        }
        if (sub.empty()) {
            cv_set_error_literal("Failed to create BGS subtractor");
            return 0;
        }
        *handle = new BGSHolder(sub);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_deleteBGSSubtractor(void *subtractor)
{
    cv_clear_error();

    try {
        if (!subtractor) {
            cv_set_error_literal("BGS subtractor pointer is null");
            return 0;
        }
        BGSHolder *holder = static_cast<BGSHolder *>(subtractor);
        delete holder;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_custom_subtractorBGSApply(void *subtractor, cv::Mat *image, cv::Mat **fgmask)
{
    cv_clear_error();

    try {
        if (!subtractor) {
            cv_set_error_literal("BGS subtractor pointer is null");
            return 0;
        }
        BGSHolder *holder = static_cast<BGSHolder *>(subtractor);
        cv::Mat result;
        holder->subtractor->apply(*image, result);
        *fgmask = new cv::Mat(result);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void cv_custom_resizeWithAspectRatio(cv::Mat *src, cv::Mat **dst, int width, int height, int interpolation)
{
    cv_clear_error();

    try {
        if (!src || src->empty()) return;

        int srcW = src->cols;
        int srcH = src->rows;

        double scaleW = (width > 0) ? (double)width / srcW : 0.0;
        double scaleH = (height > 0) ? (double)height / srcH : 0.0;

        double scale;
        if (width > 0 && height > 0) {

            scale = std::min(scaleW, scaleH);
        } else if (width > 0) {
            scale = scaleW;
        } else if (height > 0) {
            scale = scaleH;
        } else {
            *dst = new cv::Mat(src->clone());
            return;
        }

        int newW = (int)(srcW * scale);
        int newH = (int)(srcH * scale);
        if (newW < 1) newW = 1;
        if (newH < 1) newH = 1;

        cv::Mat result;
        cv::resize(*src, result, cv::Size(newW, newH), 0, 0, interpolation);
        *dst = new cv::Mat(result);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_drawCrosshair(cv::Mat **img, CVPoint center, int size, CVScalar color, int thickness)
{
    cv_clear_error();

    try {
        if (!img || !*img || (*img)->empty()) return;
        cv::Scalar cvColor(color.v0, color.v1, color.v2, color.v3);
        cv::Point c(center.x, center.y);
        int half = size / 2;

        cv::line(**img, cv::Point(c.x - half, c.y), cv::Point(c.x + half, c.y), cvColor, thickness);

        cv::line(**img, cv::Point(c.x, c.y - half), cv::Point(c.x, c.y + half), cvColor, thickness);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_matToArray(cv::Mat *mat, float *data, int *count)
{
    cv_clear_error();

    try {
        if (!mat || mat->empty() || !data || !count) return;
        if (*count < 0 || mat->dims != 2) {
            cv_set_error_literal("MatToArray requires a nonnegative capacity and a two-dimensional matrix");
            return;
        }
        if (*count == 0) return;
        cv::Mat floatMat;
        mat->convertTo(floatMat, CV_32F);
        const size_t rowElems = static_cast<size_t>(floatMat.cols) * floatMat.channels();
        const size_t total = std::min(rowElems * floatMat.rows, static_cast<size_t>(*count));
        if (floatMat.isContinuous()) {
            memcpy(data, floatMat.ptr<float>(), total * sizeof(float));
        } else {
            size_t idx = 0;
            for (int y = 0; y < floatMat.rows && idx < total; y++) {
                const float *row = floatMat.ptr<float>(y);
                const size_t toCopy = std::min(rowElems, total - idx);
                memcpy(data + idx, row, toCopy * sizeof(float));
                idx += toCopy;
            }
        }
        *count = static_cast<int>(total);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_arrayToMat(float *data, int rows, int cols, int type, cv::Mat **mat)
{
    cv_clear_error();

    try {
        if (!data || !mat) return;
        cv::Mat temp(rows, cols, type, data);
        cv::Mat result;
        temp.copyTo(result);
        *mat = new cv::Mat(result);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_concatHorizontal(cv::Mat *src1, cv::Mat *src2, cv::Mat **dst)
{
    cv_clear_error();

    try {
        if (!src1 || !src2) return;
        cv::Mat result;
        cv::hconcat(*src1, *src2, result);
        *dst = new cv::Mat(result);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_concatVertical(cv::Mat *src1, cv::Mat *src2, cv::Mat **dst)
{
    cv_clear_error();

    try {
        if (!src1 || !src2) return;
        cv::Mat result;
        cv::vconcat(*src1, *src2, result);
        *dst = new cv::Mat(result);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_drawGrid(cv::Mat **img, int rows, int cols, CVScalar color, int thickness)
{
    cv_clear_error();

    try {
        if (!img || !*img || (*img)->empty()) return;
        cv::Scalar cvColor(color.v0, color.v1, color.v2, color.v3);
        int w = (*img)->cols;
        int h = (*img)->rows;


        for (int i = 1; i < rows; i++) {
            int y = (int)((double)h * i / rows);
            cv::line(**img, cv::Point(0, y), cv::Point(w - 1, y), cvColor, thickness);
        }

        for (int j = 1; j < cols; j++) {
            int x = (int)((double)w * j / cols);
            cv::line(**img, cv::Point(x, 0), cv::Point(x, h - 1), cvColor, thickness);
        }
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_calculateHistogramImage(cv::Mat *src, cv::Mat **histImg, int width, int height)
{
    cv_clear_error();

    try {
        if (!src || src->empty()) return;

        cv::Mat gray;
        if (src->channels() > 1) {
            cv::cvtColor(*src, gray, cv::COLOR_BGR2GRAY);
        } else {
            gray = *src;
        }


        int histSize = 256;
        float range[] = { 0, 256 };
        const float *histRange = { range };
        cv::Mat hist;
        cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);


        cv::normalize(hist, hist, 0, height, cv::NORM_MINMAX);


        cv::Mat result(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
        int binW = cvRound((double)width / histSize);

        for (int i = 0; i < histSize; i++) {
            int h = cvRound(hist.at<float>(i));
            cv::rectangle(result,
                          cv::Point(i * binW, height - h),
                          cv::Point((i + 1) * binW - 1, height - 1),
                          cv::Scalar(200, 200, 200),
                          cv::FILLED);
        }
        *histImg = new cv::Mat(result);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_maskOverlay(cv::Mat *src, cv::Mat *mask, cv::Mat **dst, CVScalar color, double alpha)
{
    cv_clear_error();

    try {
        if (!src || !mask || src->empty() || mask->empty()) return;

        cv::Scalar cvColor(color.v0, color.v1, color.v2, color.v3);
        cv::Mat result;
        src->copyTo(result);


        cv::Mat overlay;
        result.copyTo(overlay);


        cv::Mat colorMat(src->size(), src->type(), cvColor);
        colorMat.copyTo(overlay, *mask);


        cv::addWeighted(result, 1.0 - alpha, overlay, alpha, 0, result);
        *dst = new cv::Mat(result);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_custom_drawDetections(cv::Mat **img, CVRect *rects, int count, CVScalar color, int thickness)
{
    cv_clear_error();

    try {
        if (!img || !*img || (*img)->empty() || !rects) return;
        cv::Scalar cvColor(color.v0, color.v1, color.v2, color.v3);
        for (int i = 0; i < count; i++) {
            cv::Rect r(rects[i].x, rects[i].y, rects[i].hSize, rects[i].vSize);
            cv::rectangle(**img, r, cvColor, thickness);
        }
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}
