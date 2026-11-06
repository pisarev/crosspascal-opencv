
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_XFEATURES2D_H
#define CV_XFEATURES2D_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/xfeatures2d.hpp>

CVAPI void *cv_xfeatures2d_createSURF(double hessianThreshold, int nOctaves, int nOctaveLayers, int extended, int upright);
CVAPI int cv_xfeatures2d_deleteSURF(void *surf);
CVAPI int cv_xfeatures2d_surfDetectAndCompute(void *surf, cv::Mat *image, cv::Mat *mask, cv::Mat **keypoints, cv::Mat **descriptors, int useProvidedKeypoints);
CVAPI double cv_xfeatures2d_surfGetHessianThreshold(void *surf);
CVAPI int cv_xfeatures2d_surfSetHessianThreshold(void *surf, double threshold);
CVAPI int cv_xfeatures2d_surfGetNOctaves(void *surf);
CVAPI int cv_xfeatures2d_surfSetNOctaves(void *surf, int nOctaves);
CVAPI int cv_xfeatures2d_surfGetNOctaveLayers(void *surf);
CVAPI int cv_xfeatures2d_surfSetNOctaveLayers(void *surf, int nOctaveLayers);
CVAPI int cv_xfeatures2d_surfGetExtended(void *surf);
CVAPI int cv_xfeatures2d_surfSetExtended(void *surf, int extended);
CVAPI int cv_xfeatures2d_surfGetUpright(void *surf);
CVAPI int cv_xfeatures2d_surfSetUpright(void *surf, int upright);

CVAPI void *cv_xfeatures2d_createFREAK(int orientationNormalized, int scaleNormalized, float patternScale, int nOctaves);
CVAPI int cv_xfeatures2d_deleteFREAK(void *freak);
CVAPI int cv_xfeatures2d_freakCompute(void *freak, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors);

CVAPI void *cv_xfeatures2d_createDAISY(float radius, int q_radius, int q_theta, int q_hist, int norm, cv::Mat *H, int interpolation, int use_orientation);
CVAPI int cv_xfeatures2d_deleteDAISY(void *daisy);
CVAPI int cv_xfeatures2d_daisyCompute(void *daisy, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors);

CVAPI void *cv_xfeatures2d_createBRIEF(int bytes, int use_orientation);
CVAPI int cv_xfeatures2d_deleteBRIEF(void *brief);
CVAPI int cv_xfeatures2d_briefCompute(void *brief, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors);

CVAPI void *cv_xfeatures2d_createLATCH(int bytes, int rotationInvariance, int half_ssd_size, double sigma);
CVAPI int cv_xfeatures2d_deleteLATCH(void *latch);
CVAPI int cv_xfeatures2d_latchCompute(void *latch, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors);

CVAPI void *cv_xfeatures2d_createBEBLID(float scale_factor, int n_bits);
CVAPI int cv_xfeatures2d_deleteBEBLID(void *beblid);
CVAPI int cv_xfeatures2d_beblidCompute(void *beblid, cv::Mat *image, cv::Mat **keypoints, cv::Mat **descriptors);

CVAPI void *cv_xfeatures2d_createStarDetector(int maxSize, int responseThreshold, int lineThresholdProjected, int lineThresholdBinarized, int suppressNonmaxSize);
CVAPI int cv_xfeatures2d_deleteStarDetector(void *detector);
CVAPI int cv_xfeatures2d_starDetectorDetect(void *detector, cv::Mat *image, cv::Mat **keypoints, cv::Mat *mask);

CVAPI int cv_xfeatures2d_matchGMS(int size1W, int size1H, int size2W, int size2H, cv::Mat *keypoints1, cv::Mat *keypoints2, cv::Mat *matches1to2, cv::Mat **matchesGMS, int withRotation, int withScale, double thresholdFactor);

CVAPI void *cv_xfeatures2d_createPCTSignatures(int initSampleCount, int initSeedCount, int pointDistribution);
CVAPI int cv_xfeatures2d_deletePCTSignatures(void *pct);
CVAPI int cv_xfeatures2d_pctComputeSignature(void *pct, cv::Mat *image, cv::Mat **signature);
CVAPI int cv_xfeatures2d_pctDrawSignature(cv::Mat *source, cv::Mat *signature, cv::Mat **result, float radiusToShorterSideRatio, int borderThickness);

#endif
