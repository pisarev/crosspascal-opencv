
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_BIOINSPIRED_H
#define CV_BIOINSPIRED_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/bioinspired.hpp>

CVAPI int cv_bioinspired_createRetina(CVSize inputSize, int colorMode, int colorSamplingMethod, int useRetinaLogSampling, float reductionFactor, float samplingStrength, void **handle);
CVAPI int cv_bioinspired_deleteRetina(void *retina);
CVAPI int cv_bioinspired_runRetina(void *retina, cv::Mat *inputImage);
CVAPI int cv_bioinspired_getParvoOutput(void *retina, cv::Mat **retinaOutput);
CVAPI int cv_bioinspired_getMagnoOutput(void *retina, cv::Mat **retinaOutput);

#endif
