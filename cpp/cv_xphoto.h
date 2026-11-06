
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_XPHOTO_H
#define CV_XPHOTO_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/xphoto.hpp>

CVAPI void *cv_xphoto_createSimpleWB();
CVAPI int cv_xphoto_deleteSimpleWB(void *wb);
CVAPI int cv_xphoto_simpleWBBalanceWhite(void *wb, cv::Mat *src, cv::Mat **dst);
CVAPI float cv_xphoto_simpleWBGetInputMin(void *wb);
CVAPI int cv_xphoto_simpleWBSetInputMin(void *wb, float val);
CVAPI float cv_xphoto_simpleWBGetInputMax(void *wb);
CVAPI int cv_xphoto_simpleWBSetInputMax(void *wb, float val);
CVAPI float cv_xphoto_simpleWBGetOutputMin(void *wb);
CVAPI int cv_xphoto_simpleWBSetOutputMin(void *wb, float val);
CVAPI float cv_xphoto_simpleWBGetOutputMax(void *wb);
CVAPI int cv_xphoto_simpleWBSetOutputMax(void *wb, float val);

CVAPI void *cv_xphoto_createGrayworldWB();
CVAPI int cv_xphoto_deleteGrayworldWB(void *wb);
CVAPI int cv_xphoto_grayworldWBBalanceWhite(void *wb, cv::Mat *src, cv::Mat **dst);
CVAPI float cv_xphoto_grayworldWBGetSaturationThreshold(void *wb);
CVAPI int cv_xphoto_grayworldWBSetSaturationThreshold(void *wb, float val);

CVAPI void *cv_xphoto_createLearningBasedWB(const char *pathToModel);
CVAPI int cv_xphoto_deleteLearningBasedWB(void *wb);
CVAPI int cv_xphoto_learningBasedWBBalanceWhite(void *wb, cv::Mat *src, cv::Mat **dst);

CVAPI int cv_xphoto_bm3dDenoising(cv::Mat *src, cv::Mat **dst, float h, int templateWindowSize, int searchWindowSize, int blockMatchingStep1, int blockMatchingStep2, int groupSize, int slidingStep, float beta, int normType, int step, int transformType);
CVAPI int cv_xphoto_dctDenoising(cv::Mat *src, cv::Mat **dst, double sigma, int psize);

CVAPI int cv_xphoto_applyChannelGains(cv::Mat *src, cv::Mat **dst, float gainB, float gainG, float gainR);

CVAPI int cv_xphoto_oilPainting(cv::Mat *src, cv::Mat **dst, int size, int dynRatio, int code);

CVAPI int cv_xphoto_inpaint(cv::Mat *src, cv::Mat *mask, cv::Mat **dst, int algorithmType);

#endif
