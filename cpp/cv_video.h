
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_VIDEO_H
#define CV_VIDEO_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/video.hpp>
#include <opencv2/optflow.hpp>

CVAPI int cv_video_goodFeaturesToTrack(cv::Mat *image, int maxCorners, double qualityLevel, double minDistance, cv::Mat *mask, int blockSize, int useHarrisDetector, double k, SetData *setCallback, void *data);

CVAPI int cv_video_calcOpticalFlowPyrLK(cv::Mat *prevImg, cv::Mat *nextImg, void *prevPts, int prevCount, CVSize winSize, int maxLevel, int maxCount, double epsilon, SetData *setCallback, void *data);

CVAPI int cv_video_calcOpticalFlowFarneback(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow, double pyrScale, int levels, int winsize, int iterations, int polyN, double polySigma, int flags);

CVAPI int cv_video_calcOpticalFlowDeepFlow(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow);

CVAPI int cv_video_buildOpticalFlowPyramid(cv::Mat *img, cv::Mat **pPyramid, CVSize winSize, int maxLevel, int withDerivatives, int pyrBorder, int derivBorder, int *levels);

CVAPI int cv_video_findHomography(void *srcPoints, void *dstPoints, int count, int method, double ransacReprojThreshold, cv::Mat **pTarget);

CVAPI int cv_video_perspectiveTransform(cv::Mat *src, cv::Mat **pDst, cv::Mat *m);

CVAPI int cv_video_createMOG2Subtractor(int history, double varThreshold, int detectShadows, void **handle);

CVAPI int cv_video_createKNNSubtractor(int history, double dist2Threshold, int detectShadows, void **handle);

CVAPI int cv_video_deleteSubtractor(void *subtractor);

CVAPI int cv_video_subtractorApply(void *subtractor, cv::Mat *image, cv::Mat **pFgMask, double learningRate);

CVAPI int cv_video_blockMatchingFlow(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow, int blockSize, int shiftSize, int maxRange);

CVAPI int cv_video_blockFlowTracking(cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow, int blockSize, int shiftSize, int maxRange, SetData *setCallback, void *data);

CVAPI int cv_video_camShift(cv::Mat *probImage, CVRect *window, int maxCount, double epsilon, CVRotatedRect *result);

CVAPI int cv_video_meanShift(cv::Mat *probImage, CVRect *window, int maxCount, double epsilon);

CVAPI int cv_video_subtractorGetBackgroundImage(void *subtractor, cv::Mat **pBackgroundImage);

CVAPI void *cv_video_createDISOpticalFlow(int preset);

CVAPI int cv_video_deleteDISOpticalFlow(void *dis);

CVAPI int cv_video_DISOpticalFlowCalc(void *dis, cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow);

CVAPI int cv_video_DISOpticalFlowSetFinestScale(void *dis, int val);

CVAPI int cv_video_readOpticalFlow(const char *path, cv::Mat **pFlow);

CVAPI int cv_video_writeOpticalFlow(const char *path, cv::Mat *flow);

CVAPI int cv_video_findTransformECC(cv::Mat *templateImage, cv::Mat *inputImage, cv::Mat **pWarpMatrix, int motionType, int maxCount, double epsilon, cv::Mat *inputMask, int gaussFiltSize);

CVAPI int cv_video_estimateRigidTransform(cv::Mat *src, cv::Mat *dst, cv::Mat **pM, int fullAffine);

CVAPI int cv_video_computeECC(cv::Mat *templateImage, cv::Mat *inputImage, cv::Mat *inputMask, double *result);

// Pascal: TCreateKalmanFilter = function(DynamParams, MeasureParams, ControlParams, Type: Integer): Pointer;
CVAPI void *cv_video_createKalmanFilter(int dynamParams, int measureParams, int controlParams, int type);

CVAPI int cv_video_deleteKalmanFilter(void *kf);

CVAPI int cv_video_kalmanPredict(void *kf, cv::Mat *control, cv::Mat **pResult);

CVAPI int cv_video_kalmanCorrect(void *kf, cv::Mat *measurement, cv::Mat **pResult);

CVAPI int cv_video_kalmanGetStatePre(void *kf, cv::Mat **pDst);

CVAPI int cv_video_kalmanSetStatePre(void *kf, cv::Mat *src);

CVAPI int cv_video_kalmanGetStatePost(void *kf, cv::Mat **pDst);

CVAPI int cv_video_kalmanSetStatePost(void *kf, cv::Mat *src);

CVAPI int cv_video_kalmanGetTransitionMatrix(void *kf, cv::Mat **pDst);

CVAPI int cv_video_kalmanSetTransitionMatrix(void *kf, cv::Mat *src);

CVAPI int cv_video_mog2GetHistory(void *subtractor);

CVAPI int cv_video_mog2SetHistory(void *subtractor, int history);

CVAPI int cv_video_mog2GetNMixtures(void *subtractor);

CVAPI int cv_video_mog2SetNMixtures(void *subtractor, int nmixtures);

CVAPI double cv_video_mog2GetBackgroundRatio(void *subtractor);

CVAPI int cv_video_mog2SetBackgroundRatio(void *subtractor, double ratio);

CVAPI double cv_video_mog2GetVarThreshold(void *subtractor);

CVAPI int cv_video_mog2SetVarThreshold(void *subtractor, double varThreshold);

CVAPI double cv_video_mog2GetVarThresholdGen(void *subtractor);

CVAPI int cv_video_mog2SetVarThresholdGen(void *subtractor, double varThresholdGen);

CVAPI int cv_video_mog2GetDetectShadows(void *subtractor);

CVAPI int cv_video_mog2SetDetectShadows(void *subtractor, int detectShadows);

CVAPI int cv_video_knnGetHistory(void *subtractor);

CVAPI int cv_video_knnSetHistory(void *subtractor, int history);

CVAPI int cv_video_knnGetNSamples(void *subtractor);

CVAPI int cv_video_knnSetNSamples(void *subtractor, int nSamples);

CVAPI double cv_video_knnGetDist2Threshold(void *subtractor);

CVAPI int cv_video_knnSetDist2Threshold(void *subtractor, double dist2Threshold);

CVAPI int cv_video_knnGetDetectShadows(void *subtractor);

CVAPI int cv_video_knnSetDetectShadows(void *subtractor, int detectShadows);

CVAPI int cv_video_knnGetShadowValue(void *subtractor);

CVAPI int cv_video_knnSetShadowValue(void *subtractor, int value);

CVAPI int cv_video_DISOpticalFlowGetFinestScale(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowGetPatchSize(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowSetPatchSize(void *dis, int val);

CVAPI int cv_video_DISOpticalFlowGetPatchStride(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowSetPatchStride(void *dis, int val);

CVAPI int cv_video_DISOpticalFlowGetGradientDescentIterations(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowSetGradientDescentIterations(void *dis, int val);

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementIterations(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementIterations(void *dis, int val);

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementAlpha(void *dis, float *val);

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementAlpha(void *dis, float val);

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementDelta(void *dis, float *val);

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementDelta(void *dis, float val);

CVAPI int cv_video_DISOpticalFlowGetVariationalRefinementGamma(void *dis, float *val);

CVAPI int cv_video_DISOpticalFlowSetVariationalRefinementGamma(void *dis, float val);

CVAPI int cv_video_DISOpticalFlowGetUseMeanNormalization(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowSetUseMeanNormalization(void *dis, int val);

CVAPI int cv_video_DISOpticalFlowGetUseSpatialPropagation(void *dis, int *val);

CVAPI int cv_video_DISOpticalFlowSetUseSpatialPropagation(void *dis, int val);

CVAPI void *cv_video_createFarnebackOpticalFlow();

CVAPI int cv_video_deleteFarnebackOpticalFlow(void *flow);

CVAPI int cv_video_farnebackOpticalFlowCalc(void *flow, cv::Mat *prev, cv::Mat *next, cv::Mat **pFlow);

CVAPI int cv_video_farnebackOpticalFlowGetNumLevels(void *flow, int *val);

CVAPI int cv_video_farnebackOpticalFlowSetNumLevels(void *flow, int val);

CVAPI int cv_video_farnebackOpticalFlowGetPyrScale(void *flow, double *val);

CVAPI int cv_video_farnebackOpticalFlowSetPyrScale(void *flow, double val);

CVAPI int cv_video_farnebackOpticalFlowGetFastPyramids(void *flow, int *val);

CVAPI int cv_video_farnebackOpticalFlowSetFastPyramids(void *flow, int val);

CVAPI int cv_video_farnebackOpticalFlowGetWinSize(void *flow, int *val);

CVAPI int cv_video_farnebackOpticalFlowSetWinSize(void *flow, int val);

CVAPI int cv_video_farnebackOpticalFlowGetNumIters(void *flow, int *val);

CVAPI int cv_video_farnebackOpticalFlowSetNumIters(void *flow, int val);

CVAPI int cv_video_farnebackOpticalFlowGetPolyN(void *flow, int *val);

CVAPI int cv_video_farnebackOpticalFlowSetPolyN(void *flow, int val);

CVAPI int cv_video_farnebackOpticalFlowGetPolySigma(void *flow, double *val);

CVAPI int cv_video_farnebackOpticalFlowSetPolySigma(void *flow, double val);

CVAPI int cv_video_farnebackOpticalFlowGetFlags(void *flow, int *val);

CVAPI int cv_video_farnebackOpticalFlowSetFlags(void *flow, int val);

CVAPI void *cv_video_createSparsePyrLKOpticalFlow();

CVAPI int cv_video_deleteSparsePyrLKOpticalFlow(void *flow);

CVAPI int cv_video_sparsePyrLKCalc(void *flow, cv::Mat *prevImg, cv::Mat *nextImg, cv::Mat **pPrevPts, cv::Mat **pNextPts, cv::Mat **pStatus, cv::Mat **pErr);

CVAPI int cv_video_sparsePyrLKGetWinSizeW(void *flow, int *val);

CVAPI int cv_video_sparsePyrLKSetWinSizeW(void *flow, int val);

CVAPI int cv_video_sparsePyrLKGetWinSizeH(void *flow, int *val);

CVAPI int cv_video_sparsePyrLKSetWinSizeH(void *flow, int val);

CVAPI int cv_video_sparsePyrLKGetMaxLevel(void *flow, int *val);

CVAPI int cv_video_sparsePyrLKSetMaxLevel(void *flow, int val);

CVAPI int cv_video_sparsePyrLKGetFlags(void *flow, int *val);

CVAPI int cv_video_sparsePyrLKSetFlags(void *flow, int val);

CVAPI int cv_video_sparsePyrLKGetMinEigThreshold(void *flow, double *val);

CVAPI int cv_video_sparsePyrLKSetMinEigThreshold(void *flow, double val);

CVAPI void *cv_video_createVariationalRefinement();

CVAPI int cv_video_deleteVariationalRefinement(void *flow);

CVAPI int cv_video_variationalRefinementCalc(void *flow, cv::Mat *I0, cv::Mat *I1, cv::Mat **pFlow);

CVAPI int cv_video_variationalRefinementGetFixedPointIterations(void *flow, int *val);

CVAPI int cv_video_variationalRefinementSetFixedPointIterations(void *flow, int val);

CVAPI int cv_video_variationalRefinementGetSorIterations(void *flow, int *val);

CVAPI int cv_video_variationalRefinementSetSorIterations(void *flow, int val);

CVAPI int cv_video_variationalRefinementGetOmega(void *flow, float *val);

CVAPI int cv_video_variationalRefinementSetOmega(void *flow, float val);

CVAPI int cv_video_variationalRefinementGetAlpha(void *flow, float *val);

CVAPI int cv_video_variationalRefinementSetAlpha(void *flow, float val);

CVAPI int cv_video_variationalRefinementGetDelta(void *flow, float *val);

CVAPI int cv_video_variationalRefinementSetDelta(void *flow, float val);

CVAPI int cv_video_variationalRefinementGetGamma(void *flow, float *val);

CVAPI int cv_video_variationalRefinementSetGamma(void *flow, float val);

#endif
