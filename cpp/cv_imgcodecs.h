
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_IMGCODECS_H
#define CV_IMGCODECS_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/imgcodecs.hpp>

CVAPI int cv_imgcodecs_openMat(const char *filename, int flags, cv::Mat **pDst);
CVAPI int cv_imgcodecs_saveMat(const char *filename, cv::Mat *mat);
CVAPI int cv_imgcodecs_imDecode(void *data, int dataSize, int flags, cv::Mat **pDst);
CVAPI int cv_imgcodecs_imEncode(const char *ext, cv::Mat *img, void **data, int *dataSize, int quality);


CVAPI int cv_imgcodecs_freeBuf(void *data);
CVAPI int cv_imgcodecs_imReadMulti(const char *filename, int flags, cv::Mat **targets, int *count);
CVAPI int cv_imgcodecs_imCount(const char *filename, int flags, int *count);

CVAPI int cv_imgcodecs_haveImageReader(const char *filename);
CVAPI int cv_imgcodecs_haveImageWriter(const char *filename);

#endif
