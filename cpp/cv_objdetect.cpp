

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_objdetect.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <vector>
#include <cstring>
#include <memory>


CVAPI int cv_objdetect_createHOG(CVSize winSize, CVSize blockSize, CVSize blockStride, CVSize cellSize, int nbins, void **handle)
{
    cv_clear_error();

    try {
        auto *hog = new cv::HOGDescriptor(
            cv::Size(winSize.cx, winSize.cy),
            cv::Size(blockSize.cx, blockSize.cy),
            cv::Size(blockStride.cx, blockStride.cy),
            cv::Size(cellSize.cx, cellSize.cy),
            nbins
        );
        *handle = hog;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_deleteHOG(void *hog)
{
    cv_clear_error();

    try {
        delete static_cast<cv::HOGDescriptor*>(hog);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_calcHistogram(void *hog, cv::Mat *image, CVSize winStride, CVSize padding, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        std::vector<float> desc;
        h->compute(*image, desc, cv::Size(winStride.cx, winStride.cy), cv::Size(padding.cx, padding.cy));
        if (get) {
            get((int)desc.size(), desc.data(), data);
        }
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogDetectMultiScale(void *hog, cv::Mat *image, double hitThreshold, CVSize winStride, CVSize padding, double scale, double finalThreshold, int useMeanShiftGrouping, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        std::vector<cv::Rect> found;
        h->detectMultiScale(*image, found, hitThreshold,
            cv::Size(winStride.cx, winStride.cy),
            cv::Size(padding.cx, padding.cy),
            scale, finalThreshold, useMeanShiftGrouping != 0);
        if (get) {
            int n = (int)found.size();
            std::vector<CVRect> rects(n);
            for (int i = 0; i < n; i++) {
                rects[i].x = found[i].x;
                rects[i].y = found[i].y;
                rects[i].hSize = found[i].width;
                rects[i].vSize = found[i].height;
            }
            get(n, n > 0 ? rects.data() : nullptr, data);
        }
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetSVMDetector(void *hog, void *detector, int count)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        float *detData = static_cast<float*>(detector);
        std::vector<float> svmDetector(detData, detData + count);
        h->setSVMDetector(svmDetector);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_createCascadeClassifier(const char *filename, void **handle)
{
    cv_clear_error();

    try {
        auto *classifier = new cv::CascadeClassifier(filename);
        *handle = classifier;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_deleteCascadeClassifier(void *classifier)
{
    cv_clear_error();

    try {
        delete static_cast<cv::CascadeClassifier*>(classifier);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_cascadeDetectMultiScale(void *classifier, cv::Mat *image, double scaleFactor, int minNeighbors, int flags, CVSize minSize, CVSize maxSize, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *c = static_cast<cv::CascadeClassifier*>(classifier);
        std::vector<cv::Rect> found;
        c->detectMultiScale(*image, found, scaleFactor, minNeighbors, flags,
            cv::Size(minSize.cx, minSize.cy),
            cv::Size(maxSize.cx, maxSize.cy));
        if (get) {
            int n = (int)found.size();
            std::vector<CVRect> rects(n);
            for (int i = 0; i < n; i++) {
                rects[i].x = found[i].x;
                rects[i].y = found[i].y;
                rects[i].hSize = found[i].width;
                rects[i].vSize = found[i].height;
            }
            get(n, n > 0 ? rects.data() : nullptr, data);
        }
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_createQRCodeDetector(void **handle)
{
    cv_clear_error();

    try {
        auto *detector = new cv::QRCodeDetector();
        *handle = detector;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_deleteQRCodeDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::QRCodeDetector*>(detector);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_qrCodeDetect(void *detector, cv::Mat *image, cv::Mat **points, int *detected)
{
    cv_clear_error();

    try {
        auto *d = static_cast<cv::QRCodeDetector*>(detector);
        auto pts = std::make_unique<cv::Mat>();
        bool found = d->detect(*image, *pts);
        *points = pts.release();
        if (detected) *detected = found ? 1 : 0;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_qrCodeDetectAndDecode(void *detector, cv::Mat *image, cv::Mat **points, char *decodedInfo, int *maxLen)
{
    cv_clear_error();

    try {
        auto *d = static_cast<cv::QRCodeDetector*>(detector);
        auto pts = std::make_unique<cv::Mat>();
        std::string decoded = d->detectAndDecode(*image, *pts);
        *points = pts.release();
        if (decodedInfo && maxLen && *maxLen > 0) {
            int len = std::min((int)decoded.size(), *maxLen - 1);
            std::memcpy(decodedInfo, decoded.c_str(), len);
            decodedInfo[len] = '\0';
            *maxLen = len;
        }
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_hogCompute(void *hog, cv::Mat *image, cv::Mat **descriptors, int winStrideW, int winStrideH, int paddingW, int paddingH)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        std::vector<float> desc;
        h->compute(*image, desc, cv::Size(winStrideW, winStrideH), cv::Size(paddingW, paddingH));
        cv::Mat *dst = new cv::Mat(1, (int)desc.size(), CV_32F);
        if (!desc.empty()) {
            std::memcpy(dst->data, desc.data(), desc.size() * sizeof(float));
        }
        *descriptors = dst;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetDefaultPeopleDetector(cv::Mat **detector)
{
    cv_clear_error();

    try {
        std::vector<float> d = cv::HOGDescriptor::getDefaultPeopleDetector();
        cv::Mat *dst = new cv::Mat(1, (int)d.size(), CV_32F);
        if (!d.empty()) {
            std::memcpy(dst->data, d.data(), d.size() * sizeof(float));
        }
        *detector = dst;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_cascadeClassifierLoad(void *classifier, const char *filename)
{
    cv_clear_error();

    try {
        auto *c = static_cast<cv::CascadeClassifier*>(classifier);
        bool loaded = c->load(filename);
        return loaded ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_cascadeClassifierEmpty(void *classifier)
{
    cv_clear_error();

    try {
        auto *c = static_cast<cv::CascadeClassifier*>(classifier);
        return c->empty() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_qrCodeDetectMulti(void *detector, cv::Mat *image, cv::Mat **points)
{
    cv_clear_error();

    try {
        auto *d = static_cast<cv::QRCodeDetector*>(detector);
        auto pts = std::make_unique<cv::Mat>();
        bool found = d->detectMulti(*image, *pts);
        *points = pts.release();
        return found ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_qrCodeDecodeCurved(void *detector, cv::Mat *image, cv::Mat **points, char *result, int resultMaxLen, cv::Mat **straightQrCode)
{
    cv_clear_error();

    try {
        auto *d = static_cast<cv::QRCodeDetector*>(detector);
        auto sqr = std::make_unique<cv::Mat>();


        cv::Mat *inputPts = *points;
        std::string decoded = d->decodeCurved(*image, *inputPts, *sqr);
        if (straightQrCode) *straightQrCode = sqr.release();
        if (result && resultMaxLen > 0) {
            int len = std::min((int)decoded.size(), resultMaxLen - 1);
            std::memcpy(result, decoded.c_str(), len);
            result[len] = '\0';
        }
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_groupRectangles(CVRect *rectList, int *count, int groupThreshold, double eps)
{
    cv_clear_error();

    try {
        int n = *count;
        std::vector<cv::Rect> rects(n);
        for (int i = 0; i < n; i++) {
            rects[i].x = rectList[i].x;
            rects[i].y = rectList[i].y;
            rects[i].width = rectList[i].hSize;
            rects[i].height = rectList[i].vSize;
        }
        cv::groupRectangles(rects, groupThreshold, eps);
        int outCount = (int)rects.size();
        for (int i = 0; i < outCount; i++) {
            rectList[i].x = rects[i].x;
            rectList[i].y = rects[i].y;
            rectList[i].hSize = rects[i].width;
            rectList[i].vSize = rects[i].height;
        }
        *count = outCount;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_objdetect_createFaceDetectorYN(const char *model, const char *config, int inputW, int inputH, float scoreThreshold, float nmsThreshold, int topK, int backendId, int targetId)
{
    cv_clear_error();

    try {
        auto detector = cv::FaceDetectorYN::create(model, config, cv::Size(inputW, inputH), scoreThreshold, nmsThreshold, topK, backendId, targetId);
        auto *ptr = new cv::Ptr<cv::FaceDetectorYN>(detector);
        return ptr;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_objdetect_deleteFaceDetectorYN(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNDetect(void *detector, cv::Mat *image, cv::Mat **faces)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        auto dst = std::make_unique<cv::Mat>();
        (*ptr)->detect(*image, *dst);
        *faces = dst.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_objdetect_createFaceRecognizerSF(const char *model, const char *config, int backendId, int targetId)
{
    cv_clear_error();

    try {
        auto recognizer = cv::FaceRecognizerSF::create(model, config, backendId, targetId);
        auto *ptr = new cv::Ptr<cv::FaceRecognizerSF>(recognizer);
        return ptr;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}


CVAPI int cv_objdetect_hogDetect(void *hog, cv::Mat *image, double hitThreshold, CVSize winStride, CVSize padding, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        std::vector<cv::Point> found;
        h->detect(*image, found, hitThreshold,
            cv::Size(winStride.cx, winStride.cy),
            cv::Size(padding.cx, padding.cy));
        if (get) {
            int n = (int)found.size();
            std::vector<CVPoint> pts(n);
            for (int i = 0; i < n; i++) {
                pts[i].x = found[i].x;
                pts[i].y = found[i].y;
            }
            get(n, n > 0 ? pts.data() : nullptr, data);
        }
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetWinSize(void *hog, CVSize *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        value->cx = h->winSize.width;
        value->cy = h->winSize.height;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetWinSize(void *hog, CVSize value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->winSize = cv::Size(value.cx, value.cy);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetBlockSize(void *hog, CVSize *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        value->cx = h->blockSize.width;
        value->cy = h->blockSize.height;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetBlockSize(void *hog, CVSize value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->blockSize = cv::Size(value.cx, value.cy);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetBlockStride(void *hog, CVSize *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        value->cx = h->blockStride.width;
        value->cy = h->blockStride.height;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetBlockStride(void *hog, CVSize value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->blockStride = cv::Size(value.cx, value.cy);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetCellSize(void *hog, CVSize *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        value->cx = h->cellSize.width;
        value->cy = h->cellSize.height;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetCellSize(void *hog, CVSize value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->cellSize = cv::Size(value.cx, value.cy);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetNbins(void *hog, int *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        *value = h->nbins;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetNbins(void *hog, int value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->nbins = value;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetWinSigma(void *hog, double *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        *value = h->winSigma;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetWinSigma(void *hog, double value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->winSigma = value;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetL2HysThreshold(void *hog, double *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        *value = h->L2HysThreshold;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetL2HysThreshold(void *hog, double value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->L2HysThreshold = value;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetGammaCorrection(void *hog, int *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        *value = h->gammaCorrection ? 1 : 0;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetGammaCorrection(void *hog, int value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->gammaCorrection = value != 0;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetNlevels(void *hog, int *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        *value = h->nlevels;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetNlevels(void *hog, int value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->nlevels = value;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogGetSignedGradient(void *hog, int *value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        *value = h->signedGradient ? 1 : 0;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetSignedGradient(void *hog, int value)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->signedGradient = value != 0;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSetSVMDetectorDefault(void *hog)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogSave(void *hog, const char *filename)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        h->save(filename);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_hogLoad(void *hog, const char *filename)
{
    cv_clear_error();

    try {
        auto *h = static_cast<cv::HOGDescriptor*>(hog);
        bool loaded = h->load(filename);
        return loaded ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_faceDetectorYNSetInputSize(void *detector, int width, int height)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        (*ptr)->setInputSize(cv::Size(width, height));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNGetScoreThreshold(void *detector, float *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        *value = (*ptr)->getScoreThreshold();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNSetScoreThreshold(void *detector, float value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        (*ptr)->setScoreThreshold(value);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNGetNMSThreshold(void *detector, float *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        *value = (*ptr)->getNMSThreshold();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNSetNMSThreshold(void *detector, float value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        (*ptr)->setNMSThreshold(value);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNGetTopK(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        *value = (*ptr)->getTopK();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceDetectorYNSetTopK(void *detector, int value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceDetectorYN>*>(detector);
        (*ptr)->setTopK(value);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_objdetect_deleteFaceRecognizerSF(void *recognizer)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::FaceRecognizerSF>*>(recognizer);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceRecognizerSFAlignCrop(void *recognizer, cv::Mat *srcImg, cv::Mat **faceBox, cv::Mat **alignedImg)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceRecognizerSF>*>(recognizer);
        cv::Mat *inputFaceBox = *faceBox;
        auto dst = std::make_unique<cv::Mat>();
        (*ptr)->alignCrop(*srcImg, *inputFaceBox, *dst);
        *alignedImg = dst.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceRecognizerSFFeature(void *recognizer, cv::Mat *alignedImg, cv::Mat **faceFeature)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceRecognizerSF>*>(recognizer);
        auto dst = std::make_unique<cv::Mat>();
        (*ptr)->feature(*alignedImg, *dst);
        *faceFeature = dst.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_objdetect_faceRecognizerSFMatch(void *recognizer, cv::Mat *faceFeature1, cv::Mat *faceFeature2, int disType, double *distance)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FaceRecognizerSF>*>(recognizer);
        *distance = (*ptr)->match(*faceFeature1, *faceFeature2, disType);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
