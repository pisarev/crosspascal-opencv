
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_STITCHING_H
#define CV_STITCHING_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/stitching.hpp>

CVAPI void *cv_stitching_createStitcher(int mode);
CVAPI int cv_stitching_deleteStitcher(void *stitcher);
CVAPI int cv_stitching_stitch(void *stitcher, cv::Mat **images, int imageCount, cv::Mat **pano);
CVAPI int cv_stitching_estimateTransform(void *stitcher, cv::Mat **images, int imageCount);
CVAPI int cv_stitching_setPanoConfidenceThresh(void *stitcher, double confThresh);
CVAPI int cv_stitching_getPanoConfidenceThresh(void *stitcher, double *confThresh);


CVAPI int cv_stitching_composePanorama(void *stitcher, cv::Mat **pano);
CVAPI int cv_stitching_setRegistrationResol(void *stitcher, double resol);
CVAPI int cv_stitching_setSeamEstimationResol(void *stitcher, double resol);
CVAPI int cv_stitching_setCompositingResol(void *stitcher, double resol);
CVAPI int cv_stitching_getWaveCorrection(void *stitcher, int *val);
CVAPI int cv_stitching_setWaveCorrection(void *stitcher, int val);
CVAPI int cv_stitching_getWaveCorrectKind(void *stitcher, int *kind);
CVAPI int cv_stitching_setWaveCorrectKind(void *stitcher, int kind);
CVAPI int cv_stitching_getInterpolationFlags(void *stitcher, int *flags);
CVAPI int cv_stitching_setInterpolationFlags(void *stitcher, int flags);
CVAPI int cv_stitching_stitcherComponent(void *stitcher, int *indices, int *count);
CVAPI int cv_stitching_stitcherResultMask(void *stitcher, cv::Mat **mask);
CVAPI double cv_stitching_stitcherWorkScale(void *stitcher);

#endif
