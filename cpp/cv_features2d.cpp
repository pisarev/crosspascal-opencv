

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_features2d.h"
#include <algorithm>
#include <limits>
#include <memory>
#include <vector>


static std::vector<cv::KeyPoint> cvKeyPointsToVector(CVKeyPoint *keypoints, int count)
{
    std::vector<cv::KeyPoint> kps(count);
    for (int i = 0; i < count; i++) {
        kps[i].pt.x = keypoints[i].x;
        kps[i].pt.y = keypoints[i].y;
        kps[i].size = keypoints[i].size;
        kps[i].angle = keypoints[i].angle;
        kps[i].response = keypoints[i].response;
        kps[i].octave = keypoints[i].octave;
        kps[i].class_id = keypoints[i].classId;
    }
    return kps;
}


static std::vector<cv::DMatch> cvDMatchesToVector(CVDMatch *matches, int count)
{
    std::vector<cv::DMatch> dmatches(count);
    for (int i = 0; i < count; i++) {
        dmatches[i].queryIdx = matches[i].queryIdx;
        dmatches[i].trainIdx = matches[i].trainIdx;
        dmatches[i].imgIdx = matches[i].imgIdx;
        dmatches[i].distance = matches[i].distance;
    }
    return dmatches;
}


static void keypointsToCallback(const std::vector<cv::KeyPoint> &kps, GetData get, void *data)
{
    if (!get) return;
    int count = (int)kps.size();
    if (count == 0) {
        get(0, nullptr, data);
        return;
    }
    std::vector<CVKeyPoint> cvkps(count);
    for (int i = 0; i < count; i++) {
        cvkps[i].x = kps[i].pt.x;
        cvkps[i].y = kps[i].pt.y;
        cvkps[i].size = kps[i].size;
        cvkps[i].angle = kps[i].angle;
        cvkps[i].response = kps[i].response;
        cvkps[i].octave = kps[i].octave;
        cvkps[i].classId = kps[i].class_id;
    }
    get(count, cvkps.data(), data);
}


static void matchesToCallback(const std::vector<cv::DMatch> &dmatches, GetData get, void *data)
{
    if (!get) return;
    int count = (int)dmatches.size();
    if (count == 0) {
        get(0, nullptr, data);
        return;
    }
    std::vector<CVDMatch> cvmatches(count);
    for (int i = 0; i < count; i++) {
        cvmatches[i].queryIdx = dmatches[i].queryIdx;
        cvmatches[i].trainIdx = dmatches[i].trainIdx;
        cvmatches[i].imgIdx = dmatches[i].imgIdx;
        cvmatches[i].distance = dmatches[i].distance;
    }
    get(count, cvmatches.data(), data);
}


CVAPI int cv_features2d_createORB(int nfeatures, double scaleFactor, int nlevels, int edgeThreshold, int firstLevel, int WTA_K, int scoreType, int patchSize, int fastThreshold, void **handle)
{
    cv_clear_error();

    try {
        auto orb = cv::ORB::create(nfeatures, (float)scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, (cv::ORB::ScoreType)scoreType, patchSize, fastThreshold);
        auto *ptr = new cv::Ptr<cv::ORB>(orb);
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

CVAPI int cv_features2d_deleteORB(void *orb)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::ORB>*>(orb);
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

CVAPI int cv_features2d_orbDetectAndCompute(void *orb, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::ORB>*>(orb);
        std::vector<cv::KeyPoint> kps;
        auto desc = std::make_unique<cv::Mat>();
        (*ptr)->detectAndCompute(*image, mask ? *mask : cv::noArray(), kps, *desc);
        keypointsToCallback(kps, get, data);
        *descriptors = desc.release();
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


CVAPI int cv_features2d_createSIFT(int nfeatures, int nOctaveLayers, double contrastThreshold, double edgeThreshold, double sigma, void **handle)
{
    cv_clear_error();

    try {
        auto sift = cv::SIFT::create(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
        auto *ptr = new cv::Ptr<cv::SIFT>(sift);
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

CVAPI int cv_features2d_deleteSIFT(void *sift)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::SIFT>*>(sift);
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

CVAPI int cv_features2d_siftDetectAndCompute(void *sift, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SIFT>*>(sift);
        std::vector<cv::KeyPoint> kps;
        auto desc = std::make_unique<cv::Mat>();
        (*ptr)->detectAndCompute(*image, mask ? *mask : cv::noArray(), kps, *desc);
        keypointsToCallback(kps, get, data);
        *descriptors = desc.release();
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


CVAPI int cv_features2d_createBRISK(int thresh, int octaves, float patternScale, void **handle)
{
    cv_clear_error();

    try {
        auto brisk = cv::BRISK::create(thresh, octaves, patternScale);
        auto *ptr = new cv::Ptr<cv::BRISK>(brisk);
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

CVAPI int cv_features2d_deleteBRISK(void *brisk)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::BRISK>*>(brisk);
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

CVAPI int cv_features2d_briskDetectAndCompute(void *brisk, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::BRISK>*>(brisk);
        std::vector<cv::KeyPoint> kps;
        auto desc = std::make_unique<cv::Mat>();
        (*ptr)->detectAndCompute(*image, mask ? *mask : cv::noArray(), kps, *desc);
        keypointsToCallback(kps, get, data);
        *descriptors = desc.release();
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


CVAPI int cv_features2d_createAKAZE(int descriptorType, int descriptorSize, int descriptorChannels, float threshold, int nOctaves, int nOctaveLayers, int diffusivity, void **handle)
{
    cv_clear_error();

    try {
        auto akaze = cv::AKAZE::create((cv::AKAZE::DescriptorType)descriptorType, descriptorSize, descriptorChannels, threshold, nOctaves, nOctaveLayers, (cv::KAZE::DiffusivityType)diffusivity);
        auto *ptr = new cv::Ptr<cv::AKAZE>(akaze);
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

CVAPI int cv_features2d_deleteAKAZE(void *akaze)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::AKAZE>*>(akaze);
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

CVAPI int cv_features2d_akazeDetectAndCompute(void *akaze, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::AKAZE>*>(akaze);
        std::vector<cv::KeyPoint> kps;
        auto desc = std::make_unique<cv::Mat>();
        (*ptr)->detectAndCompute(*image, mask ? *mask : cv::noArray(), kps, *desc);
        keypointsToCallback(kps, get, data);
        *descriptors = desc.release();
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


CVAPI int cv_features2d_createBFMatcher(int normType, int crossCheck, void **handle)
{
    cv_clear_error();

    try {
        auto matcher = cv::BFMatcher::create(normType, crossCheck != 0);
        auto *ptr = new cv::Ptr<cv::DescriptorMatcher>(matcher);
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

CVAPI int cv_features2d_deleteBFMatcher(void *matcher)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::DescriptorMatcher>*>(matcher);
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

CVAPI int cv_features2d_bfMatch(void *matcher, cv::Mat *queryDescriptors, cv::Mat *trainDescriptors, cv::Mat *mask, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DescriptorMatcher>*>(matcher);
        std::vector<cv::DMatch> dmatches;
        (*ptr)->match(*queryDescriptors, *trainDescriptors, dmatches, mask ? *mask : cv::noArray());
        matchesToCallback(dmatches, get, data);
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

CVAPI int cv_features2d_bfKnnMatch(void *matcher, cv::Mat *queryDescriptors, cv::Mat *trainDescriptors, int k, cv::Mat *mask, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DescriptorMatcher>*>(matcher);
        std::vector<std::vector<cv::DMatch>> knnMatches;
        (*ptr)->knnMatch(*queryDescriptors, *trainDescriptors, knnMatches, k, mask ? *mask : cv::noArray());

        std::vector<cv::DMatch> flat;
        for (size_t i = 0; i < knnMatches.size(); i++) {
            for (size_t j = 0; j < knnMatches[i].size(); j++) {
                flat.push_back(knnMatches[i][j]);
            }
        }
        matchesToCallback(flat, get, data);
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


CVAPI int cv_features2d_createFlannMatcher(void **handle)
{
    cv_clear_error();

    try {
        auto matcher = cv::FlannBasedMatcher::create();
        auto *ptr = new cv::Ptr<cv::DescriptorMatcher>(matcher);
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

CVAPI int cv_features2d_deleteFlannMatcher(void *matcher)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::DescriptorMatcher>*>(matcher);
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

CVAPI int cv_features2d_flannMatch(void *matcher, cv::Mat *queryDescriptors, cv::Mat *trainDescriptors, cv::Mat *mask, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::DescriptorMatcher>*>(matcher);
        std::vector<cv::DMatch> dmatches;
        (*ptr)->match(*queryDescriptors, *trainDescriptors, dmatches, mask ? *mask : cv::noArray());
        matchesToCallback(dmatches, get, data);
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


CVAPI int cv_features2d_drawMatches(cv::Mat *img1, CVKeyPoint *keypoints1, int kpCount1, cv::Mat *img2, CVKeyPoint *keypoints2, int kpCount2, CVDMatch *matches, int matchCount, cv::Mat **target, CVScalar matchColor, CVScalar singlePointColor, int flags)
{
    cv_clear_error();

    try {
        std::vector<cv::KeyPoint> kps1 = cvKeyPointsToVector(keypoints1, kpCount1);
        std::vector<cv::KeyPoint> kps2 = cvKeyPointsToVector(keypoints2, kpCount2);
        std::vector<cv::DMatch> dmatches = cvDMatchesToVector(matches, matchCount);
        cv::Scalar mc(matchColor.v0, matchColor.v1, matchColor.v2, matchColor.v3);
        cv::Scalar spc(singlePointColor.v0, singlePointColor.v1, singlePointColor.v2, singlePointColor.v3);
        auto dst = std::make_unique<cv::Mat>();
        cv::drawMatches(*img1, kps1, *img2, kps2, dmatches, *dst, mc, spc, std::vector<char>(), (cv::DrawMatchesFlags)flags);
        *target = dst.release();
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

CVAPI int cv_features2d_drawKeypoints(cv::Mat *image, CVKeyPoint *keypoints, int keypointCount, cv::Mat **target, CVScalar color, int flags)
{
    cv_clear_error();

    try {
        std::vector<cv::KeyPoint> kps = cvKeyPointsToVector(keypoints, keypointCount);
        cv::Scalar c(color.v0, color.v1, color.v2, color.v3);
        auto dst = std::make_unique<cv::Mat>();
        cv::drawKeypoints(*image, kps, *dst, c, (cv::DrawMatchesFlags)flags);
        *target = dst.release();
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


CVAPI int cv_features2d_drawMatchesKnn(cv::Mat *img1, CVKeyPoint *kp1, int kp1Count, cv::Mat *img2, CVKeyPoint *kp2, int kp2Count, CVDMatch *matches1to2, int *matchCounts, int matchGroupCount, cv::Mat **target, CVScalar matchColor, CVScalar singlePointColor, int flags)
{
    cv_clear_error();

    try {
        std::vector<cv::KeyPoint> kps1 = cvKeyPointsToVector(kp1, kp1Count);
        std::vector<cv::KeyPoint> kps2 = cvKeyPointsToVector(kp2, kp2Count);

        std::vector<std::vector<cv::DMatch>> knnMatches(matchGroupCount);
        int offset = 0;
        for (int i = 0; i < matchGroupCount; i++) {
            int cnt = matchCounts[i];
            knnMatches[i].resize(cnt);
            for (int j = 0; j < cnt; j++) {
                knnMatches[i][j].queryIdx = matches1to2[offset].queryIdx;
                knnMatches[i][j].trainIdx = matches1to2[offset].trainIdx;
                knnMatches[i][j].imgIdx = matches1to2[offset].imgIdx;
                knnMatches[i][j].distance = matches1to2[offset].distance;
                offset++;
            }
        }
        cv::Scalar mc(matchColor.v0, matchColor.v1, matchColor.v2, matchColor.v3);
        cv::Scalar spc(singlePointColor.v0, singlePointColor.v1, singlePointColor.v2, singlePointColor.v3);
        auto dst = std::make_unique<cv::Mat>();
        cv::drawMatches(*img1, kps1, *img2, kps2, knnMatches, *dst, mc, spc, std::vector<std::vector<char>>(), (cv::DrawMatchesFlags)flags);
        *target = dst.release();
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


CVAPI int cv_features2d_createSimpleBlobDetector(void **handle)
{
    cv_clear_error();

    try {
        auto detector = cv::SimpleBlobDetector::create();
        auto *ptr = new cv::Ptr<cv::SimpleBlobDetector>(detector);
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

CVAPI int cv_features2d_deleteSimpleBlobDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
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

CVAPI int cv_features2d_simpleBlobDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        std::vector<cv::KeyPoint> kps;
        (*ptr)->detect(*image, kps);
        keypointsToCallback(kps, get, data);
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

CVAPI int cv_features2d_simpleBlobDetectorGetMinThreshold(void *detector, float *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        cv::SimpleBlobDetector::Params params = (*ptr)->getParams();
        *value = (float)params.minThreshold;
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

CVAPI int cv_features2d_simpleBlobDetectorSetMinThreshold(void *detector, float minThreshold)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        cv::SimpleBlobDetector::Params params = (*ptr)->getParams();
        params.minThreshold = minThreshold;
        *ptr = cv::SimpleBlobDetector::create(params);
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

CVAPI int cv_features2d_simpleBlobDetectorGetMaxThreshold(void *detector, float *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        cv::SimpleBlobDetector::Params params = (*ptr)->getParams();
        *value = (float)params.maxThreshold;
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

CVAPI int cv_features2d_simpleBlobDetectorSetMaxThreshold(void *detector, float maxThreshold)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        cv::SimpleBlobDetector::Params params = (*ptr)->getParams();
        params.maxThreshold = maxThreshold;
        *ptr = cv::SimpleBlobDetector::create(params);
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

CVAPI int cv_features2d_simpleBlobDetectorGetMinArea(void *detector, float *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        cv::SimpleBlobDetector::Params params = (*ptr)->getParams();
        *value = params.minArea;
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

CVAPI int cv_features2d_simpleBlobDetectorSetMinArea(void *detector, float minArea)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::SimpleBlobDetector>*>(detector);
        cv::SimpleBlobDetector::Params params = (*ptr)->getParams();
        params.minArea = minArea;
        *ptr = cv::SimpleBlobDetector::create(params);
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


CVAPI int cv_features2d_createMSER(int delta, int minArea, int maxArea, double maxVariation, double minDiversity, void **handle)
{
    cv_clear_error();

    try {
        auto detector = cv::MSER::create(delta, minArea, maxArea, maxVariation, minDiversity);
        auto *ptr = new cv::Ptr<cv::MSER>(detector);
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

CVAPI int cv_features2d_deleteMSER(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::MSER>*>(detector);
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

CVAPI int cv_features2d_mserDetectRegions(void *detector, cv::Mat *image, cv::Mat **msers, cv::Mat **bboxes)
{
    cv_clear_error();
    if (msers && msers == bboxes) {
        cv_set_error_literal("MSER outputs require distinct storage");
        return 0;
    }

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        std::vector<std::vector<cv::Point>> regions;
        std::vector<cv::Rect> boxes;
        (*ptr)->detectRegions(*image, regions, boxes);

        std::unique_ptr<cv::Mat> b;
        std::unique_ptr<cv::Mat> m;
        if (bboxes) {
            b = std::make_unique<cv::Mat>((int)boxes.size(), 4, CV_32S);
            for (int i = 0; i < (int)boxes.size(); i++) {
                b->at<int>(i, 0) = boxes[i].x;
                b->at<int>(i, 1) = boxes[i].y;
                b->at<int>(i, 2) = boxes[i].width;
                b->at<int>(i, 3) = boxes[i].height;
            }
        }

        if (msers) {
            const auto maxRows = static_cast<size_t>(std::numeric_limits<int>::max());
            size_t totalPoints = 0;
            for (const auto &region : regions) {
                if (region.size() > maxRows - totalPoints) {
                    cv_set_error_literal("too many points for an MSER result matrix");
                    return 0;
                }
                totalPoints += region.size();
            }
            m = std::make_unique<cv::Mat>(static_cast<int>(totalPoints), 3, CV_32S);
            int row = 0;
            for (int i = 0; i < (int)regions.size(); i++) {
                for (int j = 0; j < (int)regions[i].size(); j++) {
                    m->at<int>(row, 0) = i;
                    m->at<int>(row, 1) = regions[i][j].x;
                    m->at<int>(row, 2) = regions[i][j].y;
                    row++;
                }
            }
        }
        if (bboxes) *bboxes = b.release();
        if (msers) *msers = m.release();
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

CVAPI int cv_features2d_mserGetDelta(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        *value = (*ptr)->getDelta();
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

CVAPI int cv_features2d_mserSetDelta(void *detector, int delta)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        (*ptr)->setDelta(delta);
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

CVAPI int cv_features2d_mserGetMinArea(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        *value = (*ptr)->getMinArea();
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

CVAPI int cv_features2d_mserSetMinArea(void *detector, int minArea)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        (*ptr)->setMinArea(minArea);
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

CVAPI int cv_features2d_mserGetMaxArea(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        *value = (*ptr)->getMaxArea();
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

CVAPI int cv_features2d_mserSetMaxArea(void *detector, int maxArea)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::MSER>*>(detector);
        (*ptr)->setMaxArea(maxArea);
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


CVAPI int cv_features2d_createGFTTDetector(int maxCorners, double qualityLevel, double minDistance, int blockSize, int useHarris, double k, void **handle)
{
    cv_clear_error();

    try {
        auto detector = cv::GFTTDetector::create(maxCorners, qualityLevel, minDistance, blockSize, useHarris != 0, k);
        auto *ptr = new cv::Ptr<cv::GFTTDetector>(detector);
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

CVAPI int cv_features2d_deleteGFTTDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
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

CVAPI int cv_features2d_gfttDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        std::vector<cv::KeyPoint> kps;
        (*ptr)->detect(*image, kps);
        keypointsToCallback(kps, get, data);
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

CVAPI int cv_features2d_gfttDetectorGetMaxCorners(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        *value = (*ptr)->getMaxFeatures();
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

CVAPI int cv_features2d_gfttDetectorSetMaxCorners(void *detector, int maxCorners)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        (*ptr)->setMaxFeatures(maxCorners);
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

CVAPI int cv_features2d_gfttDetectorGetQualityLevel(void *detector, double *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        *value = (*ptr)->getQualityLevel();
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

CVAPI int cv_features2d_gfttDetectorSetQualityLevel(void *detector, double qualityLevel)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        (*ptr)->setQualityLevel(qualityLevel);
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

CVAPI int cv_features2d_gfttDetectorGetMinDistance(void *detector, double *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        *value = (*ptr)->getMinDistance();
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

CVAPI int cv_features2d_gfttDetectorSetMinDistance(void *detector, double minDistance)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::GFTTDetector>*>(detector);
        (*ptr)->setMinDistance(minDistance);
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


CVAPI int cv_features2d_createFastFeatureDetector(int threshold, int nonmaxSuppression, int type, void **handle)
{
    cv_clear_error();

    try {
        auto detector = cv::FastFeatureDetector::create(threshold, nonmaxSuppression != 0, (cv::FastFeatureDetector::DetectorType)type);
        auto *ptr = new cv::Ptr<cv::FastFeatureDetector>(detector);
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

CVAPI int cv_features2d_deleteFastFeatureDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::FastFeatureDetector>*>(detector);
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

CVAPI int cv_features2d_fastFeatureDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FastFeatureDetector>*>(detector);
        std::vector<cv::KeyPoint> kps;
        (*ptr)->detect(*image, kps);
        keypointsToCallback(kps, get, data);
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

CVAPI int cv_features2d_fastFeatureDetectorGetThreshold(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FastFeatureDetector>*>(detector);
        *value = (*ptr)->getThreshold();
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

CVAPI int cv_features2d_fastFeatureDetectorSetThreshold(void *detector, int threshold)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FastFeatureDetector>*>(detector);
        (*ptr)->setThreshold(threshold);
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

CVAPI int cv_features2d_fastFeatureDetectorGetNonmaxSuppression(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FastFeatureDetector>*>(detector);
        *value = (*ptr)->getNonmaxSuppression() ? 1 : 0;
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

CVAPI int cv_features2d_fastFeatureDetectorSetNonmaxSuppression(void *detector, int nonmaxSuppression)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::FastFeatureDetector>*>(detector);
        (*ptr)->setNonmaxSuppression(nonmaxSuppression != 0);
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


CVAPI int cv_features2d_createAgastFeatureDetector(int threshold, int nonmaxSuppression, int type, void **handle)
{
    cv_clear_error();

    try {
        auto detector = cv::AgastFeatureDetector::create(threshold, nonmaxSuppression != 0, (cv::AgastFeatureDetector::DetectorType)type);
        auto *ptr = new cv::Ptr<cv::AgastFeatureDetector>(detector);
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

CVAPI int cv_features2d_deleteAgastFeatureDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::AgastFeatureDetector>*>(detector);
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

CVAPI int cv_features2d_agastFeatureDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::AgastFeatureDetector>*>(detector);
        std::vector<cv::KeyPoint> kps;
        (*ptr)->detect(*image, kps);
        keypointsToCallback(kps, get, data);
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

CVAPI int cv_features2d_agastFeatureDetectorGetThreshold(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::AgastFeatureDetector>*>(detector);
        *value = (*ptr)->getThreshold();
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

CVAPI int cv_features2d_agastFeatureDetectorSetThreshold(void *detector, int threshold)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::AgastFeatureDetector>*>(detector);
        (*ptr)->setThreshold(threshold);
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

CVAPI int cv_features2d_agastFeatureDetectorGetNonmaxSuppression(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::AgastFeatureDetector>*>(detector);
        *value = (*ptr)->getNonmaxSuppression() ? 1 : 0;
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

CVAPI int cv_features2d_agastFeatureDetectorSetNonmaxSuppression(void *detector, int nonmaxSuppression)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::AgastFeatureDetector>*>(detector);
        (*ptr)->setNonmaxSuppression(nonmaxSuppression != 0);
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


CVAPI int cv_features2d_createKAZE(int extended, int upright, float threshold, int nOctaves, int nOctaveLayers, int diffusivity, void **handle)
{
    cv_clear_error();

    try {
        auto detector = cv::KAZE::create(extended != 0, upright != 0, threshold, nOctaves, nOctaveLayers, (cv::KAZE::DiffusivityType)diffusivity);
        auto *ptr = new cv::Ptr<cv::KAZE>(detector);
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

CVAPI int cv_features2d_deleteKAZE(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::KAZE>*>(detector);
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

CVAPI int cv_features2d_kazeDetectAndCompute(void *detector, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        std::vector<cv::KeyPoint> kps;
        auto desc = std::make_unique<cv::Mat>();
        (*ptr)->detectAndCompute(*image, mask ? *mask : cv::noArray(), kps, *desc);
        keypointsToCallback(kps, get, data);
        *descriptors = desc.release();
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

CVAPI int cv_features2d_kazeGetExtended(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        *value = (*ptr)->getExtended() ? 1 : 0;
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

CVAPI int cv_features2d_kazeSetExtended(void *detector, int extended)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        (*ptr)->setExtended(extended != 0);
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

CVAPI int cv_features2d_kazeGetUpright(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        *value = (*ptr)->getUpright() ? 1 : 0;
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

CVAPI int cv_features2d_kazeSetUpright(void *detector, int upright)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        (*ptr)->setUpright(upright != 0);
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

CVAPI int cv_features2d_kazeGetThreshold(void *detector, float *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        *value = (float)(*ptr)->getThreshold();
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

CVAPI int cv_features2d_kazeSetThreshold(void *detector, float threshold)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        (*ptr)->setThreshold(threshold);
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

CVAPI int cv_features2d_kazeGetNOctaves(void *detector, int *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        *value = (*ptr)->getNOctaves();
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

CVAPI int cv_features2d_kazeSetNOctaves(void *detector, int nOctaves)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::Ptr<cv::KAZE>*>(detector);
        (*ptr)->setNOctaves(nOctaves);
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


CVAPI int cv_features2d_createBOWKMeansTrainer(int clusterCount, void **handle)
{
    cv_clear_error();

    try {
        auto *trainer = new cv::BOWKMeansTrainer(clusterCount);
        *handle = trainer;
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

CVAPI int cv_features2d_deleteBOWKMeansTrainer(void *trainer)
{
    cv_clear_error();

    try {
        delete static_cast<cv::BOWKMeansTrainer*>(trainer);
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

CVAPI int cv_features2d_bowKMeansTrainerAdd(void *trainer, cv::Mat *descriptors)
{
    cv_clear_error();

    try {
        auto *t = static_cast<cv::BOWKMeansTrainer*>(trainer);
        t->add(*descriptors);
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

CVAPI int cv_features2d_bowKMeansTrainerCluster(void *trainer, cv::Mat **result)
{
    cv_clear_error();

    try {
        auto *t = static_cast<cv::BOWKMeansTrainer*>(trainer);
        cv::Mat *dst = new cv::Mat(t->cluster());
        *result = dst;
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

CVAPI int cv_features2d_bowKMeansTrainerGetDescriptors(void *trainer, cv::Mat **result)
{
    cv_clear_error();

    try {
        auto *t = static_cast<cv::BOWKMeansTrainer*>(trainer);
        std::vector<cv::Mat> descs = t->getDescriptors();
        auto dst = std::make_unique<cv::Mat>();
        if (!descs.empty()) {
            cv::vconcat(descs, *dst);
        }
        *result = dst.release();
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

CVAPI int cv_features2d_bowKMeansTrainerDescriptorsCount(void *trainer, int *count)
{
    cv_clear_error();

    try {
        auto *t = static_cast<cv::BOWKMeansTrainer*>(trainer);
        *count = t->descriptorsCount();
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


CVAPI int cv_features2d_createBOWImgDescriptorExtractor(void *dmatcher, void **handle)
{
    cv_clear_error();

    try {
        auto *matcherPtr = static_cast<cv::Ptr<cv::DescriptorMatcher>*>(dmatcher);
        cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
        auto *bow = new cv::BOWImgDescriptorExtractor(extractor, *matcherPtr);
        *handle = bow;
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

CVAPI int cv_features2d_deleteBOWImgDescriptorExtractor(void *extractor)
{
    cv_clear_error();

    try {
        delete static_cast<cv::BOWImgDescriptorExtractor*>(extractor);
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

CVAPI int cv_features2d_bowImgDescriptorExtractorSetVocabulary(void *extractor, cv::Mat *vocabulary)
{
    cv_clear_error();

    try {
        auto *bow = static_cast<cv::BOWImgDescriptorExtractor*>(extractor);
        bow->setVocabulary(*vocabulary);
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

CVAPI int cv_features2d_bowImgDescriptorExtractorCompute(void *extractor, cv::Mat *image, CVKeyPoint *keypoints, int keypointCount, cv::Mat **imgDescriptor)
{
    cv_clear_error();

    try {
        auto *bow = static_cast<cv::BOWImgDescriptorExtractor*>(extractor);
        std::vector<cv::KeyPoint> kps = cvKeyPointsToVector(keypoints, keypointCount);
        auto dst = std::make_unique<cv::Mat>();
        bow->compute(*image, kps, *dst);
        *imgDescriptor = dst.release();
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

CVAPI int cv_features2d_bowImgDescriptorExtractorVocabularyEmpty(void *extractor, int *empty)
{
    cv_clear_error();

    try {
        auto *bow = static_cast<cv::BOWImgDescriptorExtractor*>(extractor);
        *empty = bow->getVocabulary().empty() ? 1 : 0;
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
