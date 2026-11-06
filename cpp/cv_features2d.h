
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_FEATURES2D_H
#define CV_FEATURES2D_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/features2d.hpp>

CVAPI int cv_features2d_createORB(int nfeatures, double scaleFactor, int nlevels, int edgeThreshold, int firstLevel, int WTA_K, int scoreType, int patchSize, int fastThreshold, void **handle);
CVAPI int cv_features2d_deleteORB(void *orb);
CVAPI int cv_features2d_orbDetectAndCompute(void *orb, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data);

CVAPI int cv_features2d_createSIFT(int nfeatures, int nOctaveLayers, double contrastThreshold, double edgeThreshold, double sigma, void **handle);
CVAPI int cv_features2d_deleteSIFT(void *sift);
CVAPI int cv_features2d_siftDetectAndCompute(void *sift, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data);

CVAPI int cv_features2d_createBRISK(int thresh, int octaves, float patternScale, void **handle);
CVAPI int cv_features2d_deleteBRISK(void *brisk);
CVAPI int cv_features2d_briskDetectAndCompute(void *brisk, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data);

CVAPI int cv_features2d_createAKAZE(int descriptorType, int descriptorSize, int descriptorChannels, float threshold, int nOctaves, int nOctaveLayers, int diffusivity, void **handle);
CVAPI int cv_features2d_deleteAKAZE(void *akaze);
CVAPI int cv_features2d_akazeDetectAndCompute(void *akaze, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data);

CVAPI int cv_features2d_createBFMatcher(int normType, int crossCheck, void **handle);
CVAPI int cv_features2d_deleteBFMatcher(void *matcher);
CVAPI int cv_features2d_bfMatch(void *matcher, cv::Mat *queryDescriptors, cv::Mat *trainDescriptors, cv::Mat *mask, GetData get, void *data);
CVAPI int cv_features2d_bfKnnMatch(void *matcher, cv::Mat *queryDescriptors, cv::Mat *trainDescriptors, int k, cv::Mat *mask, GetData get, void *data);

CVAPI int cv_features2d_createFlannMatcher(void **handle);
CVAPI int cv_features2d_deleteFlannMatcher(void *matcher);
CVAPI int cv_features2d_flannMatch(void *matcher, cv::Mat *queryDescriptors, cv::Mat *trainDescriptors, cv::Mat *mask, GetData get, void *data);

CVAPI int cv_features2d_drawMatches(cv::Mat *img1, CVKeyPoint *keypoints1, int kpCount1, cv::Mat *img2, CVKeyPoint *keypoints2, int kpCount2, CVDMatch *matches, int matchCount, cv::Mat **target, CVScalar matchColor, CVScalar singlePointColor, int flags);
CVAPI int cv_features2d_drawKeypoints(cv::Mat *image, CVKeyPoint *keypoints, int keypointCount, cv::Mat **target, CVScalar color, int flags);

CVAPI int cv_features2d_drawMatchesKnn(cv::Mat *img1, CVKeyPoint *kp1, int kp1Count, cv::Mat *img2, CVKeyPoint *kp2, int kp2Count, CVDMatch *matches1to2, int *matchCounts, int matchGroupCount, cv::Mat **target, CVScalar matchColor, CVScalar singlePointColor, int flags);

CVAPI int cv_features2d_createSimpleBlobDetector(void **handle);
CVAPI int cv_features2d_deleteSimpleBlobDetector(void *detector);
CVAPI int cv_features2d_simpleBlobDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data);
CVAPI int cv_features2d_simpleBlobDetectorGetMinThreshold(void *detector, float *value);
CVAPI int cv_features2d_simpleBlobDetectorSetMinThreshold(void *detector, float minThreshold);
CVAPI int cv_features2d_simpleBlobDetectorGetMaxThreshold(void *detector, float *value);
CVAPI int cv_features2d_simpleBlobDetectorSetMaxThreshold(void *detector, float maxThreshold);
CVAPI int cv_features2d_simpleBlobDetectorGetMinArea(void *detector, float *value);
CVAPI int cv_features2d_simpleBlobDetectorSetMinArea(void *detector, float minArea);

CVAPI int cv_features2d_createMSER(int delta, int minArea, int maxArea, double maxVariation, double minDiversity, void **handle);
CVAPI int cv_features2d_deleteMSER(void *detector);
CVAPI int cv_features2d_mserDetectRegions(void *detector, cv::Mat *image, cv::Mat **msers, cv::Mat **bboxes);
CVAPI int cv_features2d_mserGetDelta(void *detector, int *value);
CVAPI int cv_features2d_mserSetDelta(void *detector, int delta);
CVAPI int cv_features2d_mserGetMinArea(void *detector, int *value);
CVAPI int cv_features2d_mserSetMinArea(void *detector, int minArea);
CVAPI int cv_features2d_mserGetMaxArea(void *detector, int *value);
CVAPI int cv_features2d_mserSetMaxArea(void *detector, int maxArea);

CVAPI int cv_features2d_createGFTTDetector(int maxCorners, double qualityLevel, double minDistance, int blockSize, int useHarris, double k, void **handle);
CVAPI int cv_features2d_deleteGFTTDetector(void *detector);
CVAPI int cv_features2d_gfttDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data);
CVAPI int cv_features2d_gfttDetectorGetMaxCorners(void *detector, int *value);
CVAPI int cv_features2d_gfttDetectorSetMaxCorners(void *detector, int maxCorners);
CVAPI int cv_features2d_gfttDetectorGetQualityLevel(void *detector, double *value);
CVAPI int cv_features2d_gfttDetectorSetQualityLevel(void *detector, double qualityLevel);
CVAPI int cv_features2d_gfttDetectorGetMinDistance(void *detector, double *value);
CVAPI int cv_features2d_gfttDetectorSetMinDistance(void *detector, double minDistance);

CVAPI int cv_features2d_createFastFeatureDetector(int threshold, int nonmaxSuppression, int type, void **handle);
CVAPI int cv_features2d_deleteFastFeatureDetector(void *detector);
CVAPI int cv_features2d_fastFeatureDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data);
CVAPI int cv_features2d_fastFeatureDetectorGetThreshold(void *detector, int *value);
CVAPI int cv_features2d_fastFeatureDetectorSetThreshold(void *detector, int threshold);
CVAPI int cv_features2d_fastFeatureDetectorGetNonmaxSuppression(void *detector, int *value);
CVAPI int cv_features2d_fastFeatureDetectorSetNonmaxSuppression(void *detector, int nonmaxSuppression);

CVAPI int cv_features2d_createAgastFeatureDetector(int threshold, int nonmaxSuppression, int type, void **handle);
CVAPI int cv_features2d_deleteAgastFeatureDetector(void *detector);
CVAPI int cv_features2d_agastFeatureDetectorDetect(void *detector, cv::Mat *image, GetData get, void *data);
CVAPI int cv_features2d_agastFeatureDetectorGetThreshold(void *detector, int *value);
CVAPI int cv_features2d_agastFeatureDetectorSetThreshold(void *detector, int threshold);
CVAPI int cv_features2d_agastFeatureDetectorGetNonmaxSuppression(void *detector, int *value);
CVAPI int cv_features2d_agastFeatureDetectorSetNonmaxSuppression(void *detector, int nonmaxSuppression);

CVAPI int cv_features2d_createKAZE(int extended, int upright, float threshold, int nOctaves, int nOctaveLayers, int diffusivity, void **handle);
CVAPI int cv_features2d_deleteKAZE(void *detector);
CVAPI int cv_features2d_kazeDetectAndCompute(void *detector, cv::Mat *image, cv::Mat *mask, cv::Mat **descriptors, GetData get, void *data);
CVAPI int cv_features2d_kazeGetExtended(void *detector, int *value);
CVAPI int cv_features2d_kazeSetExtended(void *detector, int extended);
CVAPI int cv_features2d_kazeGetUpright(void *detector, int *value);
CVAPI int cv_features2d_kazeSetUpright(void *detector, int upright);
CVAPI int cv_features2d_kazeGetThreshold(void *detector, float *value);
CVAPI int cv_features2d_kazeSetThreshold(void *detector, float threshold);
CVAPI int cv_features2d_kazeGetNOctaves(void *detector, int *value);
CVAPI int cv_features2d_kazeSetNOctaves(void *detector, int nOctaves);

CVAPI int cv_features2d_createBOWKMeansTrainer(int clusterCount, void **handle);
CVAPI int cv_features2d_deleteBOWKMeansTrainer(void *trainer);
CVAPI int cv_features2d_bowKMeansTrainerAdd(void *trainer, cv::Mat *descriptors);
CVAPI int cv_features2d_bowKMeansTrainerCluster(void *trainer, cv::Mat **result);
CVAPI int cv_features2d_bowKMeansTrainerGetDescriptors(void *trainer, cv::Mat **result);
CVAPI int cv_features2d_bowKMeansTrainerDescriptorsCount(void *trainer, int *count);

CVAPI int cv_features2d_createBOWImgDescriptorExtractor(void *dmatcher, void **handle);
CVAPI int cv_features2d_deleteBOWImgDescriptorExtractor(void *extractor);
CVAPI int cv_features2d_bowImgDescriptorExtractorSetVocabulary(void *extractor, cv::Mat *vocabulary);
CVAPI int cv_features2d_bowImgDescriptorExtractorCompute(void *extractor, cv::Mat *image, CVKeyPoint *keypoints, int keypointCount, cv::Mat **imgDescriptor);
CVAPI int cv_features2d_bowImgDescriptorExtractorVocabularyEmpty(void *extractor, int *empty);

#endif
