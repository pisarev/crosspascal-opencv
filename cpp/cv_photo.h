
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_PHOTO_H
#define CV_PHOTO_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/photo.hpp>

CVAPI int cv_photo_inpaint(cv::Mat *src, cv::Mat *inpaintMask, cv::Mat **pDst, double inpaintRadius, int flags);

CVAPI int cv_photo_fastNlMeansDenoising(cv::Mat *src, cv::Mat **pDst, float h, int templateWindowSize, int searchWindowSize);
CVAPI int cv_photo_fastNlMeansDenoisingColored(cv::Mat *src, cv::Mat **pDst, float h, float hForColorComponents, int templateWindowSize, int searchWindowSize);
CVAPI int cv_photo_fastNlMeansDenoisingMulti(cv::Mat **srcImgs, int srcCount, int imgToDenoiseIndex, int temporalWindowSize, cv::Mat **pDst, float h, int templateWindowSize, int searchWindowSize);
CVAPI int cv_photo_fastNlMeansDenoisingColoredMulti(cv::Mat **srcImgs, int srcCount, int imgToDenoiseIndex, int temporalWindowSize, cv::Mat **pDst, float h, float hForColorComponents, int templateWindowSize, int searchWindowSize);

CVAPI int cv_photo_seamlessClone(cv::Mat *src, cv::Mat *destination, cv::Mat *mask, CVPoint center, cv::Mat **pDst, int flags);

CVAPI int cv_photo_edgePreservingFilter(cv::Mat *src, cv::Mat **pDst, int flags, float sigma_s, float sigma_r);
CVAPI int cv_photo_detailEnhance(cv::Mat *src, cv::Mat **pDst, float sigma_s, float sigma_r);
CVAPI int cv_photo_pencilSketch(cv::Mat *src, cv::Mat **pDst1, cv::Mat **pDst2, float sigma_s, float sigma_r, float shade_factor);
CVAPI int cv_photo_stylization(cv::Mat *src, cv::Mat **pDst, float sigma_s, float sigma_r);
CVAPI int cv_photo_colorChange(cv::Mat *src, cv::Mat *mask, cv::Mat **pDst, float red_mul, float green_mul, float blue_mul);
CVAPI int cv_photo_illuminationChange(cv::Mat *src, cv::Mat *mask, cv::Mat **pDst, float alpha, float beta);
CVAPI int cv_photo_textureFlattening(cv::Mat *src, cv::Mat *mask, cv::Mat **pDst, float low_threshold, float high_threshold, int kernel_size);

CVAPI int cv_photo_createMergeMertens(float contrast_weight, float saturation_weight, float exposure_weight, void **handle);
CVAPI int cv_photo_createMergeDebevec(void **handle);
CVAPI int cv_photo_createAlignMTB(int max_bits, int exclude_range, int cut, void **handle);
CVAPI int cv_photo_createTonemapDrago(float gamma, float saturation, float bias, void **handle);
CVAPI int cv_photo_createTonemapReinhard(float gamma, float intensity, float light_adapt, float color_adapt, void **handle);

CVAPI void *cv_photo_createMergeRobertson();
CVAPI void *cv_photo_createTonemapMantiuk(float gamma, float scale, float saturation);
CVAPI void *cv_photo_createCalibrateDebevec(int samples, float lambda, int random);
CVAPI void *cv_photo_createCalibrateRobertson(int max_iter, float threshold);

CVAPI int cv_photo_decolor(cv::Mat *src, cv::Mat **pGrayscale, cv::Mat **pColorBoost);

CVAPI int cv_photo_denoise_TVL1(cv::Mat **observations, int count, cv::Mat **pResult, double lambda, int niters);
CVAPI void *cv_photo_createTonemap(float gamma);
CVAPI int cv_photo_deleteTonemap(void *tonemap);
CVAPI int cv_photo_tonemapProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst);
CVAPI int cv_photo_tonemapGetGamma(void *tonemap, float *gamma);
CVAPI int cv_photo_tonemapSetGamma(void *tonemap, float gamma);

CVAPI int cv_photo_deleteTonemapDrago(void *tonemap);
CVAPI int cv_photo_tonemapDragoProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst);
CVAPI int cv_photo_tonemapDragoGetSaturation(void *tonemap, float *saturation);
CVAPI int cv_photo_tonemapDragoSetSaturation(void *tonemap, float saturation);
CVAPI int cv_photo_tonemapDragoGetBias(void *tonemap, float *bias);
CVAPI int cv_photo_tonemapDragoSetBias(void *tonemap, float bias);

CVAPI int cv_photo_deleteTonemapReinhard(void *tonemap);
CVAPI int cv_photo_tonemapReinhardProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst);
CVAPI int cv_photo_tonemapReinhardGetIntensity(void *tonemap, float *intensity);
CVAPI int cv_photo_tonemapReinhardSetIntensity(void *tonemap, float intensity);
CVAPI int cv_photo_tonemapReinhardGetLightAdaptation(void *tonemap, float *lightAdapt);
CVAPI int cv_photo_tonemapReinhardSetLightAdaptation(void *tonemap, float lightAdapt);
CVAPI int cv_photo_tonemapReinhardGetColorAdaptation(void *tonemap, float *colorAdapt);
CVAPI int cv_photo_tonemapReinhardSetColorAdaptation(void *tonemap, float colorAdapt);

CVAPI int cv_photo_deleteTonemapMantiuk(void *tonemap);
CVAPI int cv_photo_tonemapMantiukProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst);
CVAPI int cv_photo_tonemapMantiukGetScale(void *tonemap, float *scale);
CVAPI int cv_photo_tonemapMantiukSetScale(void *tonemap, float scale);
CVAPI int cv_photo_tonemapMantiukGetSaturation(void *tonemap, float *saturation);
CVAPI int cv_photo_tonemapMantiukSetSaturation(void *tonemap, float saturation);

CVAPI int cv_photo_deleteMergeMertens(void *merge);
CVAPI int cv_photo_mergeMertensProcess(void *merge, cv::Mat **src, int srcCount, cv::Mat **pDst);
CVAPI int cv_photo_mergeMertensGetContrastWeight(void *merge, float *weight);
CVAPI int cv_photo_mergeMertensSetContrastWeight(void *merge, float weight);
CVAPI int cv_photo_mergeMertensGetSaturationWeight(void *merge, float *weight);
CVAPI int cv_photo_mergeMertensSetSaturationWeight(void *merge, float weight);
CVAPI int cv_photo_mergeMertensGetExposureWeight(void *merge, float *weight);
CVAPI int cv_photo_mergeMertensSetExposureWeight(void *merge, float weight);

CVAPI int cv_photo_deleteMergeDebevec(void *merge);
CVAPI int cv_photo_mergeDebevecProcess(void *merge, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst);

CVAPI int cv_photo_deleteMergeRobertson(void *merge);
CVAPI int cv_photo_mergeRobertsonProcess(void *merge, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst);

CVAPI int cv_photo_deleteAlignMTB(void *align);
CVAPI int cv_photo_alignMTBProcess(void *align, cv::Mat **src, int srcCount, cv::Mat **pDst);
CVAPI int cv_photo_alignMTBGetMaxBits(void *align, int *maxBits);
CVAPI int cv_photo_alignMTBSetMaxBits(void *align, int maxBits);
CVAPI int cv_photo_alignMTBGetExcludeRange(void *align, int *excludeRange);
CVAPI int cv_photo_alignMTBSetExcludeRange(void *align, int excludeRange);
CVAPI int cv_photo_alignMTBGetCut(void *align, int *cut);
CVAPI int cv_photo_alignMTBSetCut(void *align, int cut);

CVAPI int cv_photo_deleteCalibrateDebevec(void *calibrate);
CVAPI int cv_photo_calibrateDebevecProcess(void *calibrate, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst);
CVAPI int cv_photo_calibrateDebevecGetSamples(void *calibrate, int *samples);
CVAPI int cv_photo_calibrateDebevecSetSamples(void *calibrate, int samples);
CVAPI int cv_photo_calibrateDebevecGetLambda(void *calibrate, float *lambda);
CVAPI int cv_photo_calibrateDebevecSetLambda(void *calibrate, float lambda);
CVAPI int cv_photo_calibrateDebevecGetRandom(void *calibrate, int *random);
CVAPI int cv_photo_calibrateDebevecSetRandom(void *calibrate, int random);

CVAPI int cv_photo_deleteCalibrateRobertson(void *calibrate);
CVAPI int cv_photo_calibrateRobertsonProcess(void *calibrate, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst);
CVAPI int cv_photo_calibrateRobertsonGetMaxIter(void *calibrate, int *maxIter);
CVAPI int cv_photo_calibrateRobertsonSetMaxIter(void *calibrate, int maxIter);
CVAPI int cv_photo_calibrateRobertsonGetThreshold(void *calibrate, float *threshold);
CVAPI int cv_photo_calibrateRobertsonSetThreshold(void *calibrate, float threshold);

#endif
