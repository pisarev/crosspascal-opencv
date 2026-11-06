

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_ximgproc.h"
#include <limits>
#include <vector>


// Pascal: TThinning = function(Source: TMat; Target: PMat; ThinningType: Integer): LongBool; cdecl;


CVAPI int cv_ximgproc_thinning(cv::Mat *src, cv::Mat **dst, int thinningType)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::ximgproc::thinning(*src, result, thinningType);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ximgproc_lineDetect(cv::Mat *src, GetData get, void *data, double scale, double sigmaScale, double quant, double angTh, double logEps, double densityTh, int nBins)
{
    cv_clear_error();

    try {

        cv::Ptr<cv::ximgproc::FastLineDetector> fld = cv::ximgproc::createFastLineDetector(
            (int)scale, (float)sigmaScale, quant, angTh, (int)nBins, true);
        cv::Mat linesMat;
        fld->detect(*src, linesMat);

        int n = linesMat.rows;
        if (n > 0 && get) {

            std::vector<CVLine> lines(n);
            for (int i = 0; i < n; i++) {
                cv::Vec4f l = linesMat.at<cv::Vec4f>(i);
                lines[i].a.x = (int)l[0];
                lines[i].a.y = (int)l[1];
                lines[i].b.x = (int)l[2];
                lines[i].b.y = (int)l[3];
            }
            get(n, lines.data(), data);
        }
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ximgproc_niBlackThreshold(cv::Mat *src, cv::Mat **dst, double maxValue, int type, int blockSize, double k, int binarizationMethod)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::ximgproc::niBlackThreshold(*src, result, maxValue, type, blockSize, k, binarizationMethod);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ximgproc_createSuperpixelSLIC(cv::Mat *image, int algorithm, int region_size, float ruler, void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::SuperpixelSLIC> *p = new cv::Ptr<cv::ximgproc::SuperpixelSLIC>(
            cv::ximgproc::createSuperpixelSLIC(*image, algorithm, region_size, ruler));
        *handle = p;
        return 1;
    } catch (cv::Exception &e) {
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

CVAPI int cv_ximgproc_deleteSuperpixelSLIC(void *slic)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::ximgproc::SuperpixelSLIC> *>(slic); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ximgproc_createEdgeDrawing()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::EdgeDrawing> *p = new cv::Ptr<cv::ximgproc::EdgeDrawing>(
            cv::ximgproc::createEdgeDrawing());
        return p;
    } catch (cv::Exception &e) {
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

CVAPI int cv_ximgproc_deleteEdgeDrawing(void *ed)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::ximgproc::EdgeDrawing> *>(ed); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ximgproc_createStructuredEdgeDetection(const char *model)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::StructuredEdgeDetection> *p =
            new cv::Ptr<cv::ximgproc::StructuredEdgeDetection>(
                cv::ximgproc::createStructuredEdgeDetection(std::string(model)));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI int cv_ximgproc_deleteStructuredEdgeDetection(void *sed)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::ximgproc::StructuredEdgeDetection> *>(sed); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ximgproc_anisotropicDiffusion(cv::Mat *src, cv::Mat **dst, float alpha, float K, int niters)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::ximgproc::anisotropicDiffusion(*src, result, alpha, K, niters);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ximgproc_createDTFilter(cv::Mat *guide, double sigmaSpatial, double sigmaColor, int mode, int numIters)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::DTFilter> *p = new cv::Ptr<cv::ximgproc::DTFilter>(
            cv::ximgproc::createDTFilter(*guide, sigmaSpatial, sigmaColor, mode, numIters));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteDTFilter(void *filter)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::DTFilter> *>(filter);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_dtFilterFilter(void *filter, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::DTFilter> *>(filter))->filter(*src, result);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_dtFilter(cv::Mat *guide, cv::Mat *src, cv::Mat **dst, double sigmaSpatial, double sigmaColor, int mode, int numIters)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::dtFilter(*guide, *src, result, sigmaSpatial, sigmaColor, mode, numIters);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createGuidedFilter(cv::Mat *guide, int radius, double eps)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::GuidedFilter> *p = new cv::Ptr<cv::ximgproc::GuidedFilter>(
            cv::ximgproc::createGuidedFilter(*guide, radius, eps));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteGuidedFilter(void *filter)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::GuidedFilter> *>(filter);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_guidedFilterFilter(void *filter, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::GuidedFilter> *>(filter))->filter(*src, result);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_guidedFilter(cv::Mat *guide, cv::Mat *src, cv::Mat **dst, int radius, double eps)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::guidedFilter(*guide, *src, result, radius, eps);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createFastGlobalSmootherFilter(cv::Mat *guide, double lambda, double sigmaColor)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::FastGlobalSmootherFilter> *p =
            new cv::Ptr<cv::ximgproc::FastGlobalSmootherFilter>(
                cv::ximgproc::createFastGlobalSmootherFilter(*guide, lambda, sigmaColor));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteFastGlobalSmootherFilter(void *filter)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::FastGlobalSmootherFilter> *>(filter);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_fastGlobalSmootherFilterFilter(void *filter, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::FastGlobalSmootherFilter> *>(filter))->filter(*src, result);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_fastGlobalSmootherFilter(cv::Mat *guide, cv::Mat *src, cv::Mat **dst, double lambda, double sigmaColor)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::fastGlobalSmootherFilter(*guide, *src, result, lambda, sigmaColor);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_ximgproc_rollingGuidanceFilter(cv::Mat *src, cv::Mat **dst, int d, double sigmaColor, double sigmaSpace, int numOfIter)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::rollingGuidanceFilter(*src, result, d, sigmaColor, sigmaSpace, numOfIter);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_jointBilateralFilter(cv::Mat *joint, cv::Mat *src, cv::Mat **dst, int d, double sigmaColor, double sigmaSpace)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::jointBilateralFilter(*joint, *src, result, d, sigmaColor, sigmaSpace);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_bilateralTextureFilter(cv::Mat *src, cv::Mat **dst, int fr, int numIter, double sigmaAlpha, double sigmaAvg)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::bilateralTextureFilter(*src, result, fr, numIter, sigmaAlpha, sigmaAvg);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_weightedMedianFilter(cv::Mat *joint, cv::Mat *src, cv::Mat **dst, int r, double sigma, int weightType)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::weightedMedianFilter(*joint, *src, result, r, sigma, weightType);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_adaptiveManifoldFilter(cv::Mat *src, cv::Mat **dst, double sigma_s, double sigma_r)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::Ptr<cv::ximgproc::AdaptiveManifoldFilter> amf = cv::ximgproc::createAMFilter(sigma_s, sigma_r);
        amf->filter(*src, result);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createFastLineDetector(int lengthThreshold, float distanceThreshold, double cannyTh1, double cannyTh2, int cannyApertureSize, int doMerge)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::FastLineDetector> *p = new cv::Ptr<cv::ximgproc::FastLineDetector>(
            cv::ximgproc::createFastLineDetector(lengthThreshold, distanceThreshold, cannyTh1, cannyTh2, cannyApertureSize, doMerge != 0));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteFastLineDetector(void *detector)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::FastLineDetector> *>(detector);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_fastLineDetectorDetect(void *detector, cv::Mat *image, cv::Mat **lines)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::FastLineDetector> *>(detector))->detect(*image, result);
        *lines = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_fastLineDetectorDrawSegments(void *detector, cv::Mat **image, cv::Mat *lines)
{
    cv_clear_error();
    try {

        cv::Mat img = **image;
        (*static_cast<cv::Ptr<cv::ximgproc::FastLineDetector> *>(detector))->drawSegments(img, *lines);
        **image = img;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_fastLineDetectorDrawSegmentsEx(void *detector, cv::Mat **image, cv::Mat *lines, int drawArrow, int thickness)
{
    cv_clear_error();
    try {
        cv::Mat img = **image;
        (*static_cast<cv::Ptr<cv::ximgproc::FastLineDetector> *>(detector))->drawSegments(img, *lines, drawArrow != 0, cv::Scalar(0, 0, 255), thickness > 0 ? thickness : 1);
        **image = img;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createEdgeBoxes(float alpha, float beta, float eta, float minScore, int maxBoxes, float edgeMinMag, float edgeMergeThr, float clusterMinMag, float maxAspectRatio, float minBoxArea, float gamma, float kappa)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::EdgeBoxes> *p = new cv::Ptr<cv::ximgproc::EdgeBoxes>(
            cv::ximgproc::createEdgeBoxes(alpha, beta, eta, minScore, maxBoxes, edgeMinMag, edgeMergeThr, clusterMinMag, maxAspectRatio, minBoxArea, gamma, kappa));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteEdgeBoxes(void *edgeBoxes)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::EdgeBoxes> *>(edgeBoxes);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

static void write_rectangles(const std::vector<cv::Rect> &rects, CVRect *boxes, int *count)
{
    if (rects.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
        cv_set_error_literal("Rectangle count exceeds the API limit");
        return;
    }
    const int required = static_cast<int>(rects.size());
    if (boxes && *count < required) {
        *count = required;
        cv_set_error_literal("Rectangle output capacity is too small");
        return;
    }
    if (boxes) {
        for (int i = 0; i < required; ++i) {
            const auto &rect = rects[i];
            boxes[i] = {rect.x, rect.y, rect.width, rect.height};
        }
    }
    *count = required;
}

CVAPI void cv_ximgproc_edgeBoxesGetBoundingBoxes(void *edgeBoxes, cv::Mat *edgeMap, cv::Mat *orientationMap, CVRect *boxes, int *count)
{
    cv_clear_error();
    if (!edgeBoxes || !edgeMap || !orientationMap || !count || (boxes && *count < 0)) {
        cv_set_error_literal("Invalid EdgeBoxes inputs or rectangle output capacity");
        return;
    }
    try {
        std::vector<cv::Rect> rects;
        (*static_cast<cv::Ptr<cv::ximgproc::EdgeBoxes> *>(edgeBoxes))->getBoundingBoxes(*edgeMap, *orientationMap, rects);
        write_rectangles(rects, boxes, count);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI float cv_ximgproc_edgeBoxesGetAlpha(void *edgeBoxes)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::ximgproc::EdgeBoxes> *>(edgeBoxes))->getAlpha();
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

CVAPI void cv_ximgproc_edgeBoxesSetAlpha(void *edgeBoxes, float value)
{
    cv_clear_error();
    try {
        (*static_cast<cv::Ptr<cv::ximgproc::EdgeBoxes> *>(edgeBoxes))->setAlpha(value);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI float cv_ximgproc_edgeBoxesGetBeta(void *edgeBoxes)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::ximgproc::EdgeBoxes> *>(edgeBoxes))->getBeta();
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

CVAPI void cv_ximgproc_edgeBoxesSetBeta(void *edgeBoxes, float value)
{
    cv_clear_error();
    try {
        (*static_cast<cv::Ptr<cv::ximgproc::EdgeBoxes> *>(edgeBoxes))->setBeta(value);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createGraphSegmentation(double sigma, float k, int minSize)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation> *p =
            new cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation>(
                cv::ximgproc::segmentation::createGraphSegmentation(sigma, k, minSize));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteGraphSegmentation(void *gs)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation> *>(gs);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_graphSegmentationProcessImage(void *gs, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation> *>(gs))->processImage(*src, result);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI float cv_ximgproc_graphSegmentationGetK(void *gs)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation> *>(gs))->getK();
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

CVAPI void cv_ximgproc_graphSegmentationSetK(void *gs, float value)
{
    cv_clear_error();
    try {
        (*static_cast<cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation> *>(gs))->setK(value);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createSelectiveSearchSegmentation()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::segmentation::SelectiveSearchSegmentation> *p =
            new cv::Ptr<cv::ximgproc::segmentation::SelectiveSearchSegmentation>(
                cv::ximgproc::segmentation::createSelectiveSearchSegmentation());
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteSelectiveSearchSegmentation(void *ss)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::segmentation::SelectiveSearchSegmentation> *>(ss);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

static cv::Ptr<cv::ximgproc::segmentation::SelectiveSearchSegmentation> &getSS(void *ss)
{
    return *static_cast<cv::Ptr<cv::ximgproc::segmentation::SelectiveSearchSegmentation> *>(ss);
}

CVAPI void cv_ximgproc_selectiveSearchSetBaseImage(void *ss, cv::Mat *image)
{
    cv_clear_error();
    try {
        getSS(ss)->setBaseImage(*image);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_selectiveSearchSwitchToSingleStrategy(void *ss, int k, float sigma)
{
    cv_clear_error();
    try {
        getSS(ss)->switchToSingleStrategy(k, sigma);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_selectiveSearchSwitchToSelectiveSearchFast(void *ss, int baseK, int incK, float sigma)
{
    cv_clear_error();
    try {
        getSS(ss)->switchToSelectiveSearchFast(baseK, incK, sigma);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_selectiveSearchSwitchToSelectiveSearchQuality(void *ss, int baseK, int incK, float sigma)
{
    cv_clear_error();
    try {
        getSS(ss)->switchToSelectiveSearchQuality(baseK, incK, sigma);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_selectiveSearchProcess(void *ss, CVRect *rects, int *count)
{
    cv_clear_error();
    if (!ss || !count || (rects && *count < 0)) {
        cv_set_error_literal("Invalid Selective Search inputs or rectangle output capacity");
        return;
    }
    try {
        std::vector<cv::Rect> results;
        getSS(ss)->process(results);
        write_rectangles(results, rects, count);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_selectiveSearchAddImage(void *ss, cv::Mat *image)
{
    cv_clear_error();
    try {
        getSS(ss)->addImage(*image);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createSuperpixelSEEDS(int imageWidth, int imageHeight, int imageChannels, int numSuperpixels, int numLevels, int prior, int histogramBins, int doubleStep)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::SuperpixelSEEDS> *p = new cv::Ptr<cv::ximgproc::SuperpixelSEEDS>(
            cv::ximgproc::createSuperpixelSEEDS(imageWidth, imageHeight, imageChannels, numSuperpixels, numLevels, prior, histogramBins, doubleStep != 0));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteSuperpixelSEEDS(void *seeds)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::SuperpixelSEEDS> *>(seeds);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_superpixelSEEDSIterate(void *seeds, cv::Mat *image, int numIterations)
{
    cv_clear_error();
    try {
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelSEEDS> *>(seeds))->iterate(*image, numIterations);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_superpixelSEEDSGetLabels(void *seeds, cv::Mat **labels)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelSEEDS> *>(seeds))->getLabels(result);
        *labels = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI int cv_ximgproc_superpixelSEEDSGetNumberOfSuperpixels(void *seeds)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelSEEDS> *>(seeds))->getNumberOfSuperpixels();
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

CVAPI void cv_ximgproc_superpixelSEEDSGetLabelContourMask(void *seeds, cv::Mat **mask, int thickLine)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelSEEDS> *>(seeds))->getLabelContourMask(result, thickLine != 0);
        *mask = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void *cv_ximgproc_createSuperpixelLSC(cv::Mat *image, int regionSize, float ratio)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::ximgproc::SuperpixelLSC> *p = new cv::Ptr<cv::ximgproc::SuperpixelLSC>(
            cv::ximgproc::createSuperpixelLSC(*image, regionSize, ratio));
        return p;
    } catch (cv::Exception &e) {
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

CVAPI void cv_ximgproc_deleteSuperpixelLSC(void *lsc)
{
    cv_clear_error();
    try {
        delete static_cast<cv::Ptr<cv::ximgproc::SuperpixelLSC> *>(lsc);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_superpixelLSCIterate(void *lsc, int numIterations)
{
    cv_clear_error();
    try {
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelLSC> *>(lsc))->iterate(numIterations);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_superpixelLSCGetLabels(void *lsc, cv::Mat **labels)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelLSC> *>(lsc))->getLabels(result);
        *labels = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI int cv_ximgproc_superpixelLSCGetNumberOfSuperpixels(void *lsc)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelLSC> *>(lsc))->getNumberOfSuperpixels();
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

CVAPI void cv_ximgproc_superpixelLSCGetLabelContourMask(void *lsc, cv::Mat **mask, int thickLine)
{
    cv_clear_error();
    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelLSC> *>(lsc))->getLabelContourMask(result, thickLine != 0);
        *mask = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_superpixelLSCEnforceLabelConnectivity(void *lsc, int minElementSize)
{
    cv_clear_error();
    try {
        (*static_cast<cv::Ptr<cv::ximgproc::SuperpixelLSC> *>(lsc))->enforceLabelConnectivity(minElementSize);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_ximgproc_PeiLinNormalization(cv::Mat *I, cv::Mat **T)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::PeiLinNormalization(*I, result);
        *T = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_fourierDescriptor(cv::Mat *src, cv::Mat **dst, int nbElt, int nbFD)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::fourierDescriptor(*src, result, nbElt, nbFD);
        *dst = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_contourSampling(cv::Mat *src, cv::Mat **out, int nbElt)
{
    cv_clear_error();
    try {
        cv::Mat result;
        cv::ximgproc::contourSampling(*src, result, nbElt);
        *out = new cv::Mat(result);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}

CVAPI void cv_ximgproc_colorMatchTemplate(cv::Mat *img, cv::Mat *templ, cv::Mat **result)
{
    cv_clear_error();
    try {
        cv::Mat res;
        cv::ximgproc::colorMatchTemplate(*img, *templ, res);
        *result = new cv::Mat(res);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}
