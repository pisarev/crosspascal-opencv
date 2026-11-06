/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_xfeatures2d.h"
#include <vector>


static std::vector<cv::KeyPoint> matToKeyPoints(cv::Mat *kpMat)
{
    std::vector<cv::KeyPoint> kps;
    if (!kpMat || kpMat->empty()) return kps;


    int n = kpMat->rows;
    if (kpMat->type() == CV_32FC1 && kpMat->cols == 7) {
        for (int i = 0; i < n; i++) {
            float *row = kpMat->ptr<float>(i);
            cv::KeyPoint kp(row[0], row[1], row[2], row[3], row[4], (int)row[5], (int)row[6]);
            kps.push_back(kp);
        }
    }
    return kps;
}

static void keyPointsToMat(const std::vector<cv::KeyPoint> &kps, cv::Mat *kpMat)
{
    if (!kpMat) return;
    int n = (int)kps.size();
    cv::Mat result(n, 7, CV_32FC1);
    for (int i = 0; i < n; i++) {
        float *row = result.ptr<float>(i);
        row[0] = kps[i].pt.x;
        row[1] = kps[i].pt.y;
        row[2] = kps[i].size;
        row[3] = kps[i].angle;
        row[4] = kps[i].response;
        row[5] = (float)kps[i].octave;
        row[6] = (float)kps[i].class_id;
    }
    result.copyTo(*kpMat);
}


static std::vector<cv::DMatch> matToDMatches(cv::Mat *mMat)
{
    std::vector<cv::DMatch> matches;
    if (!mMat || mMat->empty()) return matches;
    int n = mMat->rows;
    if (mMat->type() == CV_32FC1 && mMat->cols == 4) {
        for (int i = 0; i < n; i++) {
            float *row = mMat->ptr<float>(i);
            matches.push_back(cv::DMatch((int)row[0], (int)row[1], (int)row[2], row[3]));
        }
    }
    return matches;
}

static void dMatchesToMat(const std::vector<cv::DMatch> &matches, cv::Mat *mMat)
{
    if (!mMat) return;
    int n = (int)matches.size();
    cv::Mat result(n, 4, CV_32FC1);
    for (int i = 0; i < n; i++) {
        float *row = result.ptr<float>(i);
        row[0] = (float)matches[i].queryIdx;
        row[1] = (float)matches[i].trainIdx;
        row[2] = (float)matches[i].imgIdx;
        row[3] = matches[i].distance;
    }
    result.copyTo(*mMat);
}


CVAPI void *cv_xfeatures2d_createSURF(double hessianThreshold, int nOctaves, int nOctaveLayers, int extended, int upright)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::SURF> *p = new cv::Ptr<cv::xfeatures2d::SURF>(
            cv::xfeatures2d::SURF::create(hessianThreshold, nOctaves, nOctaveLayers, extended != 0, upright != 0));
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

CVAPI int cv_xfeatures2d_deleteSURF(void *surf)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf);
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

CVAPI int cv_xfeatures2d_surfDetectAndCompute(void *surf, cv::Mat *image, cv::Mat *mask, cv::Mat **keypoints, cv::Mat **descriptors, int useProvidedKeypoints)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::SURF> *p = static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf);
        std::vector<cv::KeyPoint> kps;
        if (useProvidedKeypoints != 0 && keypoints && *keypoints)
            kps = matToKeyPoints(*keypoints);

        cv::Mat desc;
        (*p)->detectAndCompute(*image,
            (mask && !mask->empty()) ? *mask : cv::noArray(),
            kps, desc, useProvidedKeypoints != 0);

        if (keypoints) {
            cv::Mat kpMat;
            keyPointsToMat(kps, &kpMat);
            *keypoints = new cv::Mat(kpMat);
        }
        if (descriptors)
            *descriptors = new cv::Mat(desc);
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

CVAPI double cv_xfeatures2d_surfGetHessianThreshold(void *surf)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->getHessianThreshold();
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

CVAPI int cv_xfeatures2d_surfSetHessianThreshold(void *surf, double threshold)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->setHessianThreshold(threshold); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_surfGetNOctaves(void *surf)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->getNOctaves();
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

CVAPI int cv_xfeatures2d_surfSetNOctaves(void *surf, int nOctaves)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->setNOctaves(nOctaves); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_surfGetNOctaveLayers(void *surf)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->getNOctaveLayers();
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

CVAPI int cv_xfeatures2d_surfSetNOctaveLayers(void *surf, int nOctaveLayers)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->setNOctaveLayers(nOctaveLayers); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_surfGetExtended(void *surf)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->getExtended() ? 1 : 0;
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

CVAPI int cv_xfeatures2d_surfSetExtended(void *surf, int extended)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->setExtended(extended != 0); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_surfGetUpright(void *surf)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->getUpright() ? 1 : 0;
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

CVAPI int cv_xfeatures2d_surfSetUpright(void *surf, int upright)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xfeatures2d::SURF> *>(surf))->setUpright(upright != 0); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_xfeatures2d_createFREAK(int orientationNormalized, int scaleNormalized, float patternScale, int nOctaves)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::FREAK> *p = new cv::Ptr<cv::xfeatures2d::FREAK>(
            cv::xfeatures2d::FREAK::create(orientationNormalized != 0, scaleNormalized != 0, patternScale, nOctaves));
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

CVAPI int cv_xfeatures2d_deleteFREAK(void *freak)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::FREAK> *>(freak); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_freakCompute(void *freak, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::FREAK> *p = static_cast<cv::Ptr<cv::xfeatures2d::FREAK> *>(freak);
        std::vector<cv::KeyPoint> kps = matToKeyPoints(*keypoints);
        cv::Mat desc;
        (*p)->compute(*image, kps, desc);
        cv::Mat kpMat;
        keyPointsToMat(kps, &kpMat);
        *keypoints = new cv::Mat(kpMat);
        if (descriptors) *descriptors = new cv::Mat(desc);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_xfeatures2d_createDAISY(float radius, int q_radius, int q_theta, int q_hist, int norm, cv::Mat *H, int interpolation, int use_orientation)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::DAISY> *p = new cv::Ptr<cv::xfeatures2d::DAISY>(
            cv::xfeatures2d::DAISY::create(radius, q_radius, q_theta, q_hist,
                static_cast<cv::xfeatures2d::DAISY::NormalizationType>(norm),
                (H && !H->empty()) ? *H : cv::noArray(), interpolation != 0, use_orientation != 0));
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

CVAPI int cv_xfeatures2d_deleteDAISY(void *daisy)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::DAISY> *>(daisy); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_daisyCompute(void *daisy, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::DAISY> *p = static_cast<cv::Ptr<cv::xfeatures2d::DAISY> *>(daisy);
        std::vector<cv::KeyPoint> kps = matToKeyPoints(*keypoints);
        cv::Mat desc;
        (*p)->compute(*image, kps, desc);
        cv::Mat kpMat;
        keyPointsToMat(kps, &kpMat);
        *keypoints = new cv::Mat(kpMat);
        if (descriptors) *descriptors = new cv::Mat(desc);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_xfeatures2d_createBRIEF(int bytes, int use_orientation)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::BriefDescriptorExtractor> *p =
            new cv::Ptr<cv::xfeatures2d::BriefDescriptorExtractor>(
                cv::xfeatures2d::BriefDescriptorExtractor::create(bytes, use_orientation != 0));
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

CVAPI int cv_xfeatures2d_deleteBRIEF(void *brief)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::BriefDescriptorExtractor> *>(brief); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_briefCompute(void *brief, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::xfeatures2d::BriefDescriptorExtractor> *>(brief);
        std::vector<cv::KeyPoint> kps = matToKeyPoints(*keypoints);
        cv::Mat desc;
        (*p)->compute(*image, kps, desc);
        cv::Mat kpMat;
        keyPointsToMat(kps, &kpMat);
        *keypoints = new cv::Mat(kpMat);
        if (descriptors) *descriptors = new cv::Mat(desc);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_xfeatures2d_createLATCH(int bytes, int rotationInvariance, int half_ssd_size, double sigma)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::LATCH> *p = new cv::Ptr<cv::xfeatures2d::LATCH>(
            cv::xfeatures2d::LATCH::create(bytes, rotationInvariance != 0, half_ssd_size, sigma));
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

CVAPI int cv_xfeatures2d_deleteLATCH(void *latch)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::LATCH> *>(latch); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_latchCompute(void *latch, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::xfeatures2d::LATCH> *>(latch);
        std::vector<cv::KeyPoint> kps = matToKeyPoints(*keypoints);
        cv::Mat desc;
        (*p)->compute(*image, kps, desc);
        cv::Mat kpMat;
        keyPointsToMat(kps, &kpMat);
        *keypoints = new cv::Mat(kpMat);
        if (descriptors) *descriptors = new cv::Mat(desc);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_xfeatures2d_createBEBLID(float scale_factor, int n_bits)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::BEBLID> *p = new cv::Ptr<cv::xfeatures2d::BEBLID>(
            cv::xfeatures2d::BEBLID::create(scale_factor, n_bits));
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

CVAPI int cv_xfeatures2d_deleteBEBLID(void *beblid)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::BEBLID> *>(beblid); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_beblidCompute(void *beblid, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::xfeatures2d::BEBLID> *>(beblid);
        std::vector<cv::KeyPoint> kps = matToKeyPoints(*keypoints);
        cv::Mat desc;
        (*p)->compute(*image, kps, desc);
        cv::Mat kpMat;
        keyPointsToMat(kps, &kpMat);
        *keypoints = new cv::Mat(kpMat);
        if (descriptors) *descriptors = new cv::Mat(desc);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_xfeatures2d_createStarDetector(int maxSize, int responseThreshold, int lineThresholdProjected, int lineThresholdBinarized, int suppressNonmaxSize)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::StarDetector> *p = new cv::Ptr<cv::xfeatures2d::StarDetector>(
            cv::xfeatures2d::StarDetector::create(maxSize, responseThreshold, lineThresholdProjected, lineThresholdBinarized, suppressNonmaxSize));
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

CVAPI int cv_xfeatures2d_deleteStarDetector(void *detector)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::StarDetector> *>(detector); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_starDetectorDetect(void *detector, cv::Mat *image, cv::Mat **keypoints, cv::Mat *mask)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::xfeatures2d::StarDetector> *>(detector);
        std::vector<cv::KeyPoint> kps;
        (*p)->detect(*image, kps, (mask && !mask->empty()) ? *mask : cv::noArray());
        cv::Mat kpMat;
        keyPointsToMat(kps, &kpMat);
        *keypoints = new cv::Mat(kpMat);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_xfeatures2d_matchGMS(int size1W, int size1H, int size2W, int size2H,
    cv::Mat *keypoints1, cv::Mat *keypoints2, cv::Mat *matches1to2, cv::Mat **matchesGMS,
    int withRotation, int withScale, double thresholdFactor)
{
    cv_clear_error();

    try {
        std::vector<cv::KeyPoint> kps1 = matToKeyPoints(keypoints1);
        std::vector<cv::KeyPoint> kps2 = matToKeyPoints(keypoints2);
        std::vector<cv::DMatch> matchesIn = matToDMatches(matches1to2);
        std::vector<cv::DMatch> matchesOut;

        cv::xfeatures2d::matchGMS(cv::Size(size1W, size1H), cv::Size(size2W, size2H),
            kps1, kps2, matchesIn, matchesOut, withRotation != 0, withScale != 0, thresholdFactor);

        cv::Mat mMat;
        dMatchesToMat(matchesOut, &mMat);
        *matchesGMS = new cv::Mat(mMat);
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


CVAPI void *cv_xfeatures2d_createPCTSignatures(int initSampleCount, int initSeedCount, int pointDistribution)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xfeatures2d::PCTSignatures> *p = new cv::Ptr<cv::xfeatures2d::PCTSignatures>(
            cv::xfeatures2d::PCTSignatures::create(initSampleCount, initSeedCount, pointDistribution));
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

CVAPI int cv_xfeatures2d_deletePCTSignatures(void *pct)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xfeatures2d::PCTSignatures> *>(pct); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_pctComputeSignature(void *pct, cv::Mat *image, cv::Mat **signature)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::xfeatures2d::PCTSignatures> *>(pct);
        cv::Mat sig;
        (*p)->computeSignature(*image, sig);
        if (signature) *signature = new cv::Mat(sig);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xfeatures2d_pctDrawSignature(cv::Mat *source, cv::Mat *signature, cv::Mat **result,
    float radiusToShorterSideRatio, int borderThickness)
{
    cv_clear_error();

    try {
        cv::Mat res;
        cv::xfeatures2d::PCTSignatures::drawSignature(*source, *signature, res, radiusToShorterSideRatio, borderThickness);
        if (result) *result = new cv::Mat(res);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
