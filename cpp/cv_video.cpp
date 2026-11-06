

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_video.h"
#include <opencv2/calib3d.hpp>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>


CVAPI int cv_video_goodFeaturesToTrack(cv::Mat *image, int maxCorners, double qualityLevel, double minDistance, cv::Mat *mask, int blockSize, int useHarrisDetector, double k, SetData *setCallback, void *data)
{
    cv_clear_error();

    try {
        cv::Mat maskMat = mask ? *mask : cv::Mat();
        cv::Mat corners;
        cv::goodFeaturesToTrack(*image, corners, maxCorners, qualityLevel, minDistance, maskMat, blockSize, useHarrisDetector != 0, k);
        if (setCallback) {
            if (corners.total() > static_cast<size_t>(std::numeric_limits<int>::max())) {
                cv_set_error_literal("Feature count exceeds the callback limit");
                return 0;
            }
            int count = static_cast<int>(corners.total());
            void *buf = setCallback(count, data);
            if (buf && count > 0) {
                memcpy(buf, corners.data, count * sizeof(cv::Point2f));
            }
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


CVAPI int cv_video_calcOpticalFlowPyrLK(cv::Mat *prevImg, cv::Mat *nextImg, void *prevPts, int prevCount, CVSize winSize, int maxLevel, int maxCount, double epsilon, SetData *setCallback, void *data)
{
    cv_clear_error();
    if (!prevImg || !nextImg || prevCount < 0 || (prevCount > 0 && !prevPts)) {
        cv_set_error_literal("Invalid PyrLK images or point array");
        return 0;
    }

    try {
        CVPoint2f *pts = static_cast<CVPoint2f*>(prevPts);
        std::vector<cv::Point2f> prev(prevCount);
        for (int i = 0; i < prevCount; i++) {
            prev[i] = cv::Point2f(pts[i].x, pts[i].y);
        }

        std::vector<cv::Point2f> next;
        std::vector<uchar> status;
        std::vector<float> err;

        cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, maxCount, epsilon);
        cv::calcOpticalFlowPyrLK(*prevImg, *nextImg, prev, next, status, err, cv::Size(winSize.cx, winSize.cy), maxLevel, criteria);


        int count = (int)next.size();
        std::vector<CVFlowPoint2f> result(count);
        for (int i = 0; i < count; i++) {
            result[i].x = next[i].x;
            result[i].y = next[i].y;
            result[i].status = (i < (int)status.size()) ? status[i] : 0;
            result[i].err = (result[i].status && i < (int)err.size()) ? err[i] : 0.0f;
        }
        if (setCallback) {
            void *buf = setCallback(count, data);
            if (buf && count > 0) {
                memcpy(buf, result.data(), count * sizeof(CVFlowPoint2f));
            }
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


CVAPI int cv_video_calcOpticalFlowFarneback(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow, double pyrScale, int levels, int winsize, int iterations, int polyN, double polySigma, int flags)
{
    cv_clear_error();
    if (!prev || !next || !pFlow) {
        cv_set_error_literal("Missing Farneback input or output");
        return 0;
    }

    try {
        const bool useInitial = (flags & cv::OPTFLOW_USE_INITIAL_FLOW) != 0;
        if (useInitial && (!*pFlow || (*pFlow)->empty())) {
            cv_set_error_literal("Farneback requires an initial flow matrix for this flag");
            return 0;
        }
        cv::Mat result = useInitial ? (*pFlow)->clone() : cv::Mat();
        cv::calcOpticalFlowFarneback(*prev, *next, result, pyrScale, levels, winsize, iterations, polyN, polySigma, flags);
        if (useInitial)
            **pFlow = std::move(result);
        else
            *pFlow = new cv::Mat(std::move(result));
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


CVAPI int cv_video_calcOpticalFlowDeepFlow(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow)
{
    cv_clear_error();

    try {
        auto flow = std::make_unique<cv::Mat>();
        auto deepFlow = cv::optflow::createOptFlow_DeepFlow();
        deepFlow->calc(*prev, *next, *flow);
        *pFlow = flow.release();
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


CVAPI int cv_video_buildOpticalFlowPyramid(cv::Mat *img, cv::Mat **pPyramid, CVSize winSize, int maxLevel, int withDerivatives, int pyrBorder, int derivBorder, int *levels)
{
    cv_clear_error();

    try {
        auto pyramid = std::make_unique<cv::Mat>();

        std::vector<cv::Mat> pyr;
        int retLevels = cv::buildOpticalFlowPyramid(*img, pyr, cv::Size(winSize.cx, winSize.cy), maxLevel, withDerivatives != 0, pyrBorder, derivBorder);


        if (!pyr.empty()) {
            pyr[0].copyTo(*pyramid);
        }
        *pPyramid = pyramid.release();
        if (levels) {
            *levels = retLevels;
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


CVAPI int cv_video_findHomography(void *srcPoints, void *dstPoints, int count, int method, double ransacReprojThreshold, cv::Mat **pTarget)
{
    cv_clear_error();
    if (!srcPoints || !dstPoints || count < 4 || !pTarget) {
        cv_set_error_literal("Homography requires at least four point pairs and an output");
        return 0;
    }

    try {
        CVPoint2f *srcPts = static_cast<CVPoint2f*>(srcPoints);
        CVPoint2f *dstPts = static_cast<CVPoint2f*>(dstPoints);
        std::vector<cv::Point2f> src(count);
        std::vector<cv::Point2f> dst(count);
        for (int i = 0; i < count; i++) {
            src[i] = cv::Point2f(srcPts[i].x, srcPts[i].y);
            dst[i] = cv::Point2f(dstPts[i].x, dstPts[i].y);
        }
        auto target = std::make_unique<cv::Mat>();
        *target = cv::findHomography(src, dst, method, ransacReprojThreshold);
        if (target->empty()) {
            cv_set_error_literal("Could not estimate a homography");
            return 0;
        }
        *pTarget = target.release();
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


CVAPI int cv_video_perspectiveTransform(cv::Mat *src, cv::Mat **pDst, cv::Mat *m)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::perspectiveTransform(*src, *dst, *m);
        *pDst = dst.release();
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


using BackgroundSubtractorHandle = cv::Ptr<cv::BackgroundSubtractor>;

static cv::BackgroundSubtractor &backgroundSubtractor(void *handle)
{
    auto *subtractor = static_cast<BackgroundSubtractorHandle *>(handle);
    if (!subtractor || !*subtractor)
        throw std::invalid_argument("Invalid background subtractor handle");
    return **subtractor;
}

template<class Subtractor>
static Subtractor &backgroundSubtractorAs(void *handle)
{
    auto *subtractor = dynamic_cast<Subtractor *>(&backgroundSubtractor(handle));
    if (!subtractor)
        throw std::invalid_argument("Wrong background subtractor type");
    return *subtractor;
}

CVAPI int cv_video_createMOG2Subtractor(int history, double varThreshold, int detectShadows, void **handle)
{
    cv_clear_error();

    try {
        auto ptr = new BackgroundSubtractorHandle(
            cv::createBackgroundSubtractorMOG2(history, varThreshold, detectShadows != 0));
        *handle = ptr;
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


CVAPI int cv_video_createKNNSubtractor(int history, double dist2Threshold, int detectShadows, void **handle)
{
    cv_clear_error();

    try {
        auto ptr = new BackgroundSubtractorHandle(
            cv::createBackgroundSubtractorKNN(history, dist2Threshold, detectShadows != 0));
        *handle = ptr;
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


CVAPI int cv_video_deleteSubtractor(void *subtractor)
{
    cv_clear_error();

    try {
        delete static_cast<BackgroundSubtractorHandle *>(subtractor);
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


CVAPI int cv_video_subtractorApply(void *subtractor, cv::Mat *image, cv::Mat **pFgMask, double learningRate)
{
    cv_clear_error();

    try {
        if (!image || !pFgMask) {
            cv_set_error_literal("Missing background subtraction input or output");
            return 0;
        }
        auto fgmask = std::make_unique<cv::Mat>();
        backgroundSubtractor(subtractor).apply(*image, *fgmask, learningRate);
        *pFgMask = fgmask.release();
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


CVAPI int cv_video_subtractorGetBackgroundImage(void *subtractor, cv::Mat **pBackgroundImage)
{
    cv_clear_error();

    try {
        if (!pBackgroundImage) {
            cv_set_error_literal("Missing background image output");
            return 0;
        }
        auto background = std::make_unique<cv::Mat>();
        backgroundSubtractor(subtractor).getBackgroundImage(*background);
        *pBackgroundImage = background.release();
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


CVAPI int cv_video_blockMatchingFlow(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow, int blockSize, int shiftSize, int maxRange)
{
    cv_clear_error();

    try {
        if (!pFlow || !prev || !next || prev->empty() || next->empty() ||
            prev->dims != 2 || next->dims != 2 || prev->size() != next->size() ||
            prev->depth() != CV_8U || next->depth() != CV_8U ||
            blockSize <= 0 || shiftSize <= 0 || maxRange < 0) {
            cv_set_error_literal("Block flow requires matching nonempty 8-bit frames and valid block parameters");
            return 0;
        }

        int rows = prev->rows;
        int cols = prev->cols;

        cv::Mat gray_prev, gray_next;
        if (prev->channels() > 1)
            cv::cvtColor(*prev, gray_prev, cv::COLOR_BGR2GRAY);
        else
            gray_prev = *prev;
        if (next->channels() > 1)
            cv::cvtColor(*next, gray_next, cv::COLOR_BGR2GRAY);
        else
            gray_next = *next;

        auto flow = std::make_unique<cv::Mat>(cv::Mat::zeros(rows, cols, CV_32FC2));

        int halfBlock = blockSize / 2;

        for (std::int64_t row = halfBlock; row < rows - halfBlock; row += shiftSize) {
            int y = static_cast<int>(row);
            int minDy = std::max(-maxRange, halfBlock - y);
            int maxDy = std::min(maxRange, rows - halfBlock - 1 - y);
            for (std::int64_t col = halfBlock; col < cols - halfBlock; col += shiftSize) {
                int x = static_cast<int>(col);
                int minDx = std::max(-maxRange, halfBlock - x);
                int maxDx = std::min(maxRange, cols - halfBlock - 1 - x);
                int bestDx = 0, bestDy = 0;
                double bestSAD = 1e30;

                for (int dy = minDy; dy <= maxDy; dy++) {
                    for (int dx = minDx; dx <= maxDx; dx++) {
                        int nx = x + dx;
                        int ny = y + dy;

                        double sad = 0;
                        for (int by = -halfBlock; by <= halfBlock; by++) {
                            for (int bx = -halfBlock; bx <= halfBlock; bx++) {
                                sad += std::abs(
                                    (int)gray_prev.at<uchar>(y + by, x + bx) -
                                    (int)gray_next.at<uchar>(ny + by, nx + bx));
                            }
                        }

                        if (sad < bestSAD) {
                            bestSAD = sad;
                            bestDx = dx;
                            bestDy = dy;
                        }
                    }
                }

                const int endY = static_cast<int>(std::min<std::int64_t>(rows, row + shiftSize / 2 + 1));
                const int endX = static_cast<int>(std::min<std::int64_t>(cols, col + shiftSize / 2 + 1));
                for (int fy = std::max(0, y - shiftSize / 2); fy < endY; fy++) {
                    for (int fx = std::max(0, x - shiftSize / 2); fx < endX; fx++) {
                        flow->at<cv::Vec2f>(fy, fx) = cv::Vec2f((float)bestDx, (float)bestDy);
                    }
                }
            }
        }
        *pFlow = flow.release();
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


CVAPI int cv_video_blockFlowTracking(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow, int blockSize, int shiftSize, int maxRange, SetData *setCallback, void *data)
{
    cv_clear_error();
    if (!pFlow) {
        cv_set_error_literal("Missing block flow output");
        return 0;
    }

    try {
        if (setCallback && prev && prev->dims == 2 &&
            prev->total() > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
            cv_set_error_literal("Block flow result exceeds the callback count limit");
            return 0;
        }

        cv::Mat *computed = nullptr;
        if (!cv_video_blockMatchingFlow(prev, next, &computed, blockSize, shiftSize, maxRange))
            return 0;
        std::unique_ptr<cv::Mat> flow(computed);

        if (setCallback) {
            int count = static_cast<int>(flow->total());
            void *buffer = setCallback(count, data);
            if (buffer && count > 0)
                std::memcpy(buffer, flow->data, static_cast<size_t>(count) * flow->elemSize());
        }
        *pFlow = flow.release();
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


CVAPI int cv_video_camShift(cv::Mat *probImage, CVRect *window, int maxCount, double epsilon, CVRotatedRect *result)
{
    cv_clear_error();

    try {
        cv::Rect rect(window->x, window->y, window->hSize, window->vSize);
        cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, maxCount, epsilon);
        cv::RotatedRect rr = cv::CamShift(*probImage, rect, criteria);

        window->x = rect.x;
        window->y = rect.y;
        window->hSize = rect.width;
        window->vSize = rect.height;

        result->center.x = rr.center.x;
        result->center.y = rr.center.y;
        result->size.x = rr.size.width;
        result->size.y = rr.size.height;
        result->angle = rr.angle;
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


CVAPI int cv_video_meanShift(cv::Mat *probImage, CVRect *window, int maxCount, double epsilon)
{
    cv_clear_error();

    try {
        cv::Rect rect(window->x, window->y, window->hSize, window->vSize);
        cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, maxCount, epsilon);
        cv::meanShift(*probImage, rect, criteria);

        window->x = rect.x;
        window->y = rect.y;
        window->hSize = rect.width;
        window->vSize = rect.height;
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


CVAPI void *cv_video_createDISOpticalFlow(int preset)
{
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::DISOpticalFlow>(
            cv::DISOpticalFlow::create(preset));
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


CVAPI int cv_video_deleteDISOpticalFlow(void *dis)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        delete ptr;
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


CVAPI int cv_video_DISOpticalFlowCalc(void *dis, cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        auto flow = std::make_unique<cv::Mat>();
        (*ptr)->calc(*prev, *next, *flow);
        *pFlow = flow.release();
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


CVAPI int cv_video_DISOpticalFlowSetFinestScale(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setFinestScale(val);
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


CVAPI int cv_video_DISOpticalFlowGetFinestScale(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getFinestScale();
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

CVAPI int cv_video_DISOpticalFlowGetPatchSize(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getPatchSize();
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

CVAPI int cv_video_DISOpticalFlowSetPatchSize(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setPatchSize(val);
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

CVAPI int cv_video_DISOpticalFlowGetPatchStride(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getPatchStride();
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

CVAPI int cv_video_DISOpticalFlowSetPatchStride(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setPatchStride(val);
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

CVAPI int cv_video_DISOpticalFlowGetGradientDescentIterations(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getGradientDescentIterations();
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

CVAPI int cv_video_DISOpticalFlowSetGradientDescentIterations(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setGradientDescentIterations(val);
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

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementIterations(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getVariationalRefinementIterations();
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

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementIterations(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setVariationalRefinementIterations(val);
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

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementAlpha(void *dis, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getVariationalRefinementAlpha();
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

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementAlpha(void *dis, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setVariationalRefinementAlpha(val);
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

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementDelta(void *dis, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getVariationalRefinementDelta();
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

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementDelta(void *dis, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setVariationalRefinementDelta(val);
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

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementGamma(void *dis, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getVariationalRefinementGamma();
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

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementGamma(void *dis, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setVariationalRefinementGamma(val);
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


CVAPI int cv_video_DISOpticalFlowGetUseMeanNormalization(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getUseMeanNormalization() ? 1 : 0;
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

CVAPI int cv_video_DISOpticalFlowSetUseMeanNormalization(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setUseMeanNormalization(val != 0);
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

CVAPI int cv_video_DISOpticalFlowGetUseSpatialPropagation(void *dis, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        *val = (*ptr)->getUseSpatialPropagation() ? 1 : 0;
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

CVAPI int cv_video_DISOpticalFlowSetUseSpatialPropagation(void *dis, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DISOpticalFlow>*>(dis);
        (*ptr)->setUseSpatialPropagation(val != 0);
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


CVAPI int cv_video_readOpticalFlow(const char *path, cv::Mat **pFlow)
{
    cv_clear_error();

    try {
        cv::Mat result = cv::readOpticalFlow(path);
        if (result.empty()) {
            cv_set_error_literal("Failed to read optical flow from file");
            return 0;
        }
        auto flow = std::make_unique<cv::Mat>();
        result.copyTo(*flow);
        *pFlow = flow.release();
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


CVAPI int cv_video_writeOpticalFlow(const char *path, cv::Mat *flow)
{
    cv_clear_error();

    try {
        bool ok = cv::writeOpticalFlow(path, *flow);
        if (!ok) {
            cv_set_error_literal("Failed to write optical flow to file");
            return 0;
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


CVAPI int cv_video_findTransformECC(cv::Mat *templateImage, cv::Mat *inputImage, cv::Mat **pWarpMatrix, int motionType, int maxCount, double epsilon, cv::Mat *inputMask, int gaussFiltSize)
{
    cv_clear_error();

    try {
        auto warpMatrix = std::make_unique<cv::Mat>();
        // Initialize warp matrix based on motion type
        if (motionType == cv::MOTION_HOMOGRAPHY)
            *warpMatrix = cv::Mat::eye(3, 3, CV_32F);
        else
            *warpMatrix = cv::Mat::eye(2, 3, CV_32F);
        cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, maxCount, epsilon);
        cv::Mat mask = inputMask ? *inputMask : cv::Mat();
        cv::findTransformECC(*templateImage, *inputImage, *warpMatrix, motionType, criteria, mask, gaussFiltSize);
        *pWarpMatrix = warpMatrix.release();
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


CVAPI int cv_video_estimateRigidTransform(cv::Mat *src, cv::Mat *dst, cv::Mat **pM, int fullAffine)
{
    cv_clear_error();

    try {
        auto M = std::make_unique<cv::Mat>();
        if (fullAffine)
            *M = cv::estimateAffine2D(*src, *dst);
        else
            *M = cv::estimateAffinePartial2D(*src, *dst);
        if (M->empty()) {
            cv_set_error_literal("Failed to estimate rigid transform");
            return 0;
        }
        *pM = M.release();
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


CVAPI int cv_video_computeECC(cv::Mat *templateImage, cv::Mat *inputImage, cv::Mat *inputMask, double *result)
{
    cv_clear_error();

    try {
        cv::Mat mask = inputMask ? *inputMask : cv::Mat();
        if (mask.empty())
            *result = cv::computeECC(*templateImage, *inputImage);
        else
            *result = cv::computeECC(*templateImage, *inputImage, mask);
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


// Pascal: TCreateKalmanFilter = function(DynamParams, MeasureParams, ControlParams, Type: Integer): Pointer;
CVAPI void *cv_video_createKalmanFilter(int dynamParams, int measureParams, int controlParams, int type)
{
    cv_clear_error();

    try {
        auto *kf = new cv::KalmanFilter(dynamParams, measureParams, controlParams, type);
        return kf;
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


CVAPI int cv_video_deleteKalmanFilter(void *kf)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        delete ptr;
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


CVAPI int cv_video_kalmanPredict(void *kf, cv::Mat *control, cv::Mat **pResult)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        cv::Mat ctrl = control ? *control : cv::Mat();
        cv::Mat prediction = ptr->predict(ctrl);
        auto result = std::make_unique<cv::Mat>();
        prediction.copyTo(*result);
        *pResult = result.release();
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


CVAPI int cv_video_kalmanCorrect(void *kf, cv::Mat *measurement, cv::Mat **pResult)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        cv::Mat corrected = ptr->correct(*measurement);
        auto result = std::make_unique<cv::Mat>();
        corrected.copyTo(*result);
        *pResult = result.release();
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


CVAPI int cv_video_kalmanGetStatePre(void *kf, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        auto dst = std::make_unique<cv::Mat>();
        ptr->statePre.copyTo(*dst);
        *pDst = dst.release();
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


CVAPI int cv_video_kalmanSetStatePre(void *kf, cv::Mat *src)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        src->copyTo(ptr->statePre);
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


CVAPI int cv_video_kalmanGetStatePost(void *kf, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        auto dst = std::make_unique<cv::Mat>();
        ptr->statePost.copyTo(*dst);
        *pDst = dst.release();
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


CVAPI int cv_video_kalmanSetStatePost(void *kf, cv::Mat *src)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        src->copyTo(ptr->statePost);
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


CVAPI int cv_video_kalmanGetTransitionMatrix(void *kf, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        auto dst = std::make_unique<cv::Mat>();
        ptr->transitionMatrix.copyTo(*dst);
        *pDst = dst.release();
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


CVAPI int cv_video_kalmanSetTransitionMatrix(void *kf, cv::Mat *src)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::KalmanFilter*>(kf);
        src->copyTo(ptr->transitionMatrix);
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


CVAPI int cv_video_mog2GetHistory(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        return model.getHistory();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_mog2SetHistory(void *subtractor, int history)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        model.setHistory(history);
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


CVAPI int cv_video_mog2GetNMixtures(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        return model.getNMixtures();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_mog2SetNMixtures(void *subtractor, int nmixtures)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        model.setNMixtures(nmixtures);
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


CVAPI double cv_video_mog2GetBackgroundRatio(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        return model.getBackgroundRatio();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_mog2SetBackgroundRatio(void *subtractor, double ratio)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        model.setBackgroundRatio(ratio);
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


CVAPI double cv_video_mog2GetVarThreshold(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        return model.getVarThreshold();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_mog2SetVarThreshold(void *subtractor, double varThreshold)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        model.setVarThreshold(varThreshold);
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


CVAPI double cv_video_mog2GetVarThresholdGen(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        return model.getVarThresholdGen();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_mog2SetVarThresholdGen(void *subtractor, double varThresholdGen)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        model.setVarThresholdGen(varThresholdGen);
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


CVAPI int cv_video_mog2GetDetectShadows(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        return model.getDetectShadows() ? 1 : 0;
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


CVAPI int cv_video_mog2SetDetectShadows(void *subtractor, int detectShadows)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorMOG2>(subtractor);
        model.setDetectShadows(detectShadows != 0);
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


CVAPI int cv_video_knnGetHistory(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        return model.getHistory();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_knnSetHistory(void *subtractor, int history)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        model.setHistory(history);
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


CVAPI int cv_video_knnGetNSamples(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        return model.getNSamples();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_knnSetNSamples(void *subtractor, int nSamples)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        model.setNSamples(nSamples);
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


CVAPI double cv_video_knnGetDist2Threshold(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        return model.getDist2Threshold();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_knnSetDist2Threshold(void *subtractor, double dist2Threshold)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        model.setDist2Threshold(dist2Threshold);
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


CVAPI int cv_video_knnGetDetectShadows(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        return model.getDetectShadows() ? 1 : 0;
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


CVAPI int cv_video_knnSetDetectShadows(void *subtractor, int detectShadows)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        model.setDetectShadows(detectShadows != 0);
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


CVAPI int cv_video_knnGetShadowValue(void *subtractor)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        return model.getShadowValue();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_video_knnSetShadowValue(void *subtractor, int value)
{
    cv_clear_error();

    try {
        auto &model = backgroundSubtractorAs<cv::BackgroundSubtractorKNN>(subtractor);
        model.setShadowValue(value);
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


CVAPI void *cv_video_createFarnebackOpticalFlow()
{
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::FarnebackOpticalFlow>(
            cv::FarnebackOpticalFlow::create());
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


CVAPI int cv_video_deleteFarnebackOpticalFlow(void *flow)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        delete ptr;
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


CVAPI int cv_video_farnebackOpticalFlowCalc(void *flow, cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow)
{
    cv_clear_error();
    if (!flow || !prev || !next || !pFlow) {
        cv_set_error_literal("Missing Farneback input or output");
        return 0;
    }

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        const bool useInitial = ((*ptr)->getFlags() & cv::OPTFLOW_USE_INITIAL_FLOW) != 0;
        if (useInitial && (!*pFlow || (*pFlow)->empty())) {
            cv_set_error_literal("Farneback requires an initial flow matrix for this flag");
            return 0;
        }
        cv::Mat result = useInitial ? (*pFlow)->clone() : cv::Mat();
        (*ptr)->calc(*prev, *next, result);
        if (useInitial)
            **pFlow = std::move(result);
        else
            *pFlow = new cv::Mat(std::move(result));
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

CVAPI int cv_video_farnebackOpticalFlowGetNumLevels(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getNumLevels();
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

CVAPI int cv_video_farnebackOpticalFlowSetNumLevels(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setNumLevels(val);
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

CVAPI int cv_video_farnebackOpticalFlowGetPyrScale(void *flow, double *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getPyrScale();
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

CVAPI int cv_video_farnebackOpticalFlowSetPyrScale(void *flow, double val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setPyrScale(val);
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


CVAPI int cv_video_farnebackOpticalFlowGetFastPyramids(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getFastPyramids() ? 1 : 0;
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

CVAPI int cv_video_farnebackOpticalFlowSetFastPyramids(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setFastPyramids(val != 0);
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

CVAPI int cv_video_farnebackOpticalFlowGetWinSize(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getWinSize();
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

CVAPI int cv_video_farnebackOpticalFlowSetWinSize(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setWinSize(val);
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

CVAPI int cv_video_farnebackOpticalFlowGetNumIters(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getNumIters();
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

CVAPI int cv_video_farnebackOpticalFlowSetNumIters(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setNumIters(val);
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

CVAPI int cv_video_farnebackOpticalFlowGetPolyN(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getPolyN();
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

CVAPI int cv_video_farnebackOpticalFlowSetPolyN(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setPolyN(val);
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

CVAPI int cv_video_farnebackOpticalFlowGetPolySigma(void *flow, double *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getPolySigma();
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

CVAPI int cv_video_farnebackOpticalFlowSetPolySigma(void *flow, double val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setPolySigma(val);
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

CVAPI int cv_video_farnebackOpticalFlowGetFlags(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        *val = (*ptr)->getFlags();
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

CVAPI int cv_video_farnebackOpticalFlowSetFlags(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FarnebackOpticalFlow>*>(flow);
        (*ptr)->setFlags(val);
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


CVAPI void *cv_video_createSparsePyrLKOpticalFlow()
{
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::SparsePyrLKOpticalFlow>(
            cv::SparsePyrLKOpticalFlow::create());
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


CVAPI int cv_video_deleteSparsePyrLKOpticalFlow(void *flow)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        delete ptr;
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


CVAPI int cv_video_sparsePyrLKCalc(void *flow, cv::Mat *prevImg, cv::Mat *nextImg, cv::Mat **pPrevPts, cv::Mat **pNextPts, cv::Mat **pStatus, cv::Mat **pErr)
{
    cv_clear_error();
    if (!flow || !prevImg || !nextImg || !pPrevPts || !*pPrevPts || !pNextPts || !pStatus || !pErr
        || pPrevPts == pNextPts || pPrevPts == pStatus || pPrevPts == pErr
        || pNextPts == pStatus || pNextPts == pErr || pStatus == pErr) {
        cv_set_error_literal("Invalid or overlapping SparsePyrLK inputs and outputs");
        return 0;
    }

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        const bool useInitial = ((*ptr)->getFlags() & cv::OPTFLOW_USE_INITIAL_FLOW) != 0;
        if (useInitial && (!*pNextPts || *pPrevPts == *pNextPts || (*pNextPts)->empty())) {
            cv_set_error_literal("SparsePyrLK requires a separate initial next-point matrix");
            return 0;
        }

        auto nextPts = std::make_unique<cv::Mat>(useInitial ? (*pNextPts)->clone() : cv::Mat());
        auto status = std::make_unique<cv::Mat>();
        auto err = std::make_unique<cv::Mat>();
        (*ptr)->calc(*prevImg, *nextImg, **pPrevPts, *nextPts, *status, *err);
        if (useInitial)
            **pNextPts = std::move(*nextPts);
        else
            *pNextPts = nextPts.release();
        *pStatus = status.release();
        *pErr = err.release();
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

CVAPI int cv_video_sparsePyrLKGetWinSizeW(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        cv::Size sz = (*ptr)->getWinSize();
        *val = sz.width;
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

CVAPI int cv_video_sparsePyrLKSetWinSizeW(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        cv::Size sz = (*ptr)->getWinSize();
        sz.width = val;
        (*ptr)->setWinSize(sz);
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

CVAPI int cv_video_sparsePyrLKGetWinSizeH(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        cv::Size sz = (*ptr)->getWinSize();
        *val = sz.height;
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

CVAPI int cv_video_sparsePyrLKSetWinSizeH(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        cv::Size sz = (*ptr)->getWinSize();
        sz.height = val;
        (*ptr)->setWinSize(sz);
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

CVAPI int cv_video_sparsePyrLKGetMaxLevel(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        *val = (*ptr)->getMaxLevel();
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

CVAPI int cv_video_sparsePyrLKSetMaxLevel(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        (*ptr)->setMaxLevel(val);
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

CVAPI int cv_video_sparsePyrLKGetFlags(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        *val = (*ptr)->getFlags();
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

CVAPI int cv_video_sparsePyrLKSetFlags(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        (*ptr)->setFlags(val);
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

CVAPI int cv_video_sparsePyrLKGetMinEigThreshold(void *flow, double *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        *val = (*ptr)->getMinEigThreshold();
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

CVAPI int cv_video_sparsePyrLKSetMinEigThreshold(void *flow, double val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SparsePyrLKOpticalFlow>*>(flow);
        (*ptr)->setMinEigThreshold(val);
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


CVAPI void *cv_video_createVariationalRefinement()
{
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::VariationalRefinement>(
            cv::VariationalRefinement::create());
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


CVAPI int cv_video_deleteVariationalRefinement(void *flow)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        delete ptr;
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


CVAPI int cv_video_variationalRefinementCalc(void *flow, cv::Mat *I0, cv::Mat *I1, cv::Mat **pFlow)
{
    cv_clear_error();
    if (!flow || !I0 || !I1 || !pFlow || !*pFlow || (*pFlow)->empty()) {
        cv_set_error_literal("Variational refinement requires two frames and an initial flow matrix");
        return 0;
    }

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        cv::Mat result = (*pFlow)->clone();
        (*ptr)->calc(*I0, *I1, result);
        **pFlow = std::move(result);
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

CVAPI int cv_video_variationalRefinementGetFixedPointIterations(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        *val = (*ptr)->getFixedPointIterations();
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

CVAPI int cv_video_variationalRefinementSetFixedPointIterations(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        (*ptr)->setFixedPointIterations(val);
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

CVAPI int cv_video_variationalRefinementGetSorIterations(void *flow, int *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        *val = (*ptr)->getSorIterations();
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

CVAPI int cv_video_variationalRefinementSetSorIterations(void *flow, int val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        (*ptr)->setSorIterations(val);
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

CVAPI int cv_video_variationalRefinementGetOmega(void *flow, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        *val = (*ptr)->getOmega();
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

CVAPI int cv_video_variationalRefinementSetOmega(void *flow, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        (*ptr)->setOmega(val);
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

CVAPI int cv_video_variationalRefinementGetAlpha(void *flow, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        *val = (*ptr)->getAlpha();
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

CVAPI int cv_video_variationalRefinementSetAlpha(void *flow, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        (*ptr)->setAlpha(val);
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

CVAPI int cv_video_variationalRefinementGetDelta(void *flow, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        *val = (*ptr)->getDelta();
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

CVAPI int cv_video_variationalRefinementSetDelta(void *flow, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        (*ptr)->setDelta(val);
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

CVAPI int cv_video_variationalRefinementGetGamma(void *flow, float *val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        *val = (*ptr)->getGamma();
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

CVAPI int cv_video_variationalRefinementSetGamma(void *flow, float val)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::VariationalRefinement>*>(flow);
        (*ptr)->setGamma(val);
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
