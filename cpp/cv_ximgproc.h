
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_XIMGPROC_H
#define CV_XIMGPROC_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/ximgproc.hpp>

CVAPI int cv_ximgproc_thinning(cv::Mat *src, cv::Mat **dst, int thinningType);

CVAPI int cv_ximgproc_lineDetect(cv::Mat *src, GetData get, void *data, double scale, double sigmaScale, double quant, double angTh, double logEps, double densityTh, int nBins);

CVAPI int cv_ximgproc_niBlackThreshold(cv::Mat *src, cv::Mat **dst, double maxValue, int type, int blockSize, double k, int binarizationMethod);

CVAPI int cv_ximgproc_createSuperpixelSLIC(cv::Mat *image, int algorithm, int region_size, float ruler, void **handle);
CVAPI int cv_ximgproc_deleteSuperpixelSLIC(void *slic);

CVAPI void *cv_ximgproc_createEdgeDrawing();
CVAPI int cv_ximgproc_deleteEdgeDrawing(void *ed);

CVAPI void *cv_ximgproc_createStructuredEdgeDetection(const char *model);
CVAPI int cv_ximgproc_deleteStructuredEdgeDetection(void *sed);

CVAPI int cv_ximgproc_anisotropicDiffusion(cv::Mat *src, cv::Mat **dst, float alpha, float K, int niters);

CVAPI void *cv_ximgproc_createDTFilter(cv::Mat *guide, double sigmaSpatial, double sigmaColor, int mode, int numIters);
CVAPI void cv_ximgproc_deleteDTFilter(void *filter);
CVAPI void cv_ximgproc_dtFilterFilter(void *filter, cv::Mat *src, cv::Mat **dst);
CVAPI void cv_ximgproc_dtFilter(cv::Mat *guide, cv::Mat *src, cv::Mat **dst, double sigmaSpatial, double sigmaColor, int mode, int numIters);

CVAPI void *cv_ximgproc_createGuidedFilter(cv::Mat *guide, int radius, double eps);
CVAPI void cv_ximgproc_deleteGuidedFilter(void *filter);
CVAPI void cv_ximgproc_guidedFilterFilter(void *filter, cv::Mat *src, cv::Mat **dst);
CVAPI void cv_ximgproc_guidedFilter(cv::Mat *guide, cv::Mat *src, cv::Mat **dst, int radius, double eps);

CVAPI void *cv_ximgproc_createFastGlobalSmootherFilter(cv::Mat *guide, double lambda, double sigmaColor);
CVAPI void cv_ximgproc_deleteFastGlobalSmootherFilter(void *filter);
CVAPI void cv_ximgproc_fastGlobalSmootherFilterFilter(void *filter, cv::Mat *src, cv::Mat **dst);
CVAPI void cv_ximgproc_fastGlobalSmootherFilter(cv::Mat *guide, cv::Mat *src, cv::Mat **dst, double lambda, double sigmaColor);

CVAPI void cv_ximgproc_rollingGuidanceFilter(cv::Mat *src, cv::Mat **dst, int d, double sigmaColor, double sigmaSpace, int numOfIter);
CVAPI void cv_ximgproc_jointBilateralFilter(cv::Mat *joint, cv::Mat *src, cv::Mat **dst, int d, double sigmaColor, double sigmaSpace);
CVAPI void cv_ximgproc_bilateralTextureFilter(cv::Mat *src, cv::Mat **dst, int fr, int numIter, double sigmaAlpha, double sigmaAvg);
CVAPI void cv_ximgproc_weightedMedianFilter(cv::Mat *joint, cv::Mat *src, cv::Mat **dst, int r, double sigma, int weightType);
CVAPI void cv_ximgproc_adaptiveManifoldFilter(cv::Mat *src, cv::Mat **dst, double sigma_s, double sigma_r);

CVAPI void *cv_ximgproc_createFastLineDetector(int lengthThreshold, float distanceThreshold, double cannyTh1, double cannyTh2, int cannyApertureSize, int doMerge);
CVAPI void cv_ximgproc_deleteFastLineDetector(void *detector);
CVAPI void cv_ximgproc_fastLineDetectorDetect(void *detector, cv::Mat *image, cv::Mat **lines);
CVAPI void cv_ximgproc_fastLineDetectorDrawSegments(void *detector, cv::Mat **image, cv::Mat *lines);
CVAPI void cv_ximgproc_fastLineDetectorDrawSegmentsEx(void *detector, cv::Mat **image, cv::Mat *lines, int drawArrow, int thickness);

CVAPI void *cv_ximgproc_createEdgeBoxes(float alpha, float beta, float eta, float minScore, int maxBoxes, float edgeMinMag, float edgeMergeThr, float clusterMinMag, float maxAspectRatio, float minBoxArea, float gamma, float kappa);
CVAPI void cv_ximgproc_deleteEdgeBoxes(void *edgeBoxes);
// Pass a null buffer to query the required count. Otherwise supply capacity in *count.
// Insufficient capacity reports the required count and leaves the buffer untouched.
CVAPI void cv_ximgproc_edgeBoxesGetBoundingBoxes(void *edgeBoxes, cv::Mat *edgeMap, cv::Mat *orientationMap, CVRect *boxes, int *count);
CVAPI float cv_ximgproc_edgeBoxesGetAlpha(void *edgeBoxes);
CVAPI void cv_ximgproc_edgeBoxesSetAlpha(void *edgeBoxes, float value);
CVAPI float cv_ximgproc_edgeBoxesGetBeta(void *edgeBoxes);
CVAPI void cv_ximgproc_edgeBoxesSetBeta(void *edgeBoxes, float value);

CVAPI void *cv_ximgproc_createGraphSegmentation(double sigma, float k, int minSize);
CVAPI void cv_ximgproc_deleteGraphSegmentation(void *gs);
CVAPI void cv_ximgproc_graphSegmentationProcessImage(void *gs, cv::Mat *src, cv::Mat **dst);
CVAPI float cv_ximgproc_graphSegmentationGetK(void *gs);
CVAPI void cv_ximgproc_graphSegmentationSetK(void *gs, float value);

CVAPI void *cv_ximgproc_createSelectiveSearchSegmentation();
CVAPI void cv_ximgproc_deleteSelectiveSearchSegmentation(void *ss);
CVAPI void cv_ximgproc_selectiveSearchSetBaseImage(void *ss, cv::Mat *image);
CVAPI void cv_ximgproc_selectiveSearchSwitchToSingleStrategy(void *ss, int k, float sigma);
CVAPI void cv_ximgproc_selectiveSearchSwitchToSelectiveSearchFast(void *ss, int baseK, int incK, float sigma);
CVAPI void cv_ximgproc_selectiveSearchSwitchToSelectiveSearchQuality(void *ss, int baseK, int incK, float sigma);
// Uses the same count and capacity contract as cv_ximgproc_edgeBoxesGetBoundingBoxes.
CVAPI void cv_ximgproc_selectiveSearchProcess(void *ss, CVRect *rects, int *count);
CVAPI void cv_ximgproc_selectiveSearchAddImage(void *ss, cv::Mat *image);

CVAPI void *cv_ximgproc_createSuperpixelSEEDS(int imageWidth, int imageHeight, int imageChannels, int numSuperpixels, int numLevels, int prior, int histogramBins, int doubleStep);
CVAPI void cv_ximgproc_deleteSuperpixelSEEDS(void *seeds);
CVAPI void cv_ximgproc_superpixelSEEDSIterate(void *seeds, cv::Mat *image, int numIterations);
CVAPI void cv_ximgproc_superpixelSEEDSGetLabels(void *seeds, cv::Mat **labels);
CVAPI int cv_ximgproc_superpixelSEEDSGetNumberOfSuperpixels(void *seeds);
CVAPI void cv_ximgproc_superpixelSEEDSGetLabelContourMask(void *seeds, cv::Mat **mask, int thickLine);

CVAPI void *cv_ximgproc_createSuperpixelLSC(cv::Mat *image, int regionSize, float ratio);
CVAPI void cv_ximgproc_deleteSuperpixelLSC(void *lsc);
CVAPI void cv_ximgproc_superpixelLSCIterate(void *lsc, int numIterations);
CVAPI void cv_ximgproc_superpixelLSCGetLabels(void *lsc, cv::Mat **labels);
CVAPI int cv_ximgproc_superpixelLSCGetNumberOfSuperpixels(void *lsc);
CVAPI void cv_ximgproc_superpixelLSCGetLabelContourMask(void *lsc, cv::Mat **mask, int thickLine);
CVAPI void cv_ximgproc_superpixelLSCEnforceLabelConnectivity(void *lsc, int minElementSize);

CVAPI void cv_ximgproc_PeiLinNormalization(cv::Mat *I, cv::Mat **T);
CVAPI void cv_ximgproc_fourierDescriptor(cv::Mat *src, cv::Mat **dst, int nbElt, int nbFD);
CVAPI void cv_ximgproc_contourSampling(cv::Mat *src, cv::Mat **out, int nbElt);
CVAPI void cv_ximgproc_colorMatchTemplate(cv::Mat *img, cv::Mat *templ, cv::Mat **result);

#endif
