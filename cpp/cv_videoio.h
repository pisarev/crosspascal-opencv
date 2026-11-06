
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_VIDEOIO_H
#define CV_VIDEOIO_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/videoio.hpp>

CVAPI int cv_videoio_createVideoCapture(const char *filename, int apiPreference, void **handle);
CVAPI int cv_videoio_deleteVideoCapture(void *cap);
CVAPI int cv_videoio_videoCaptureIsOpened(void *cap, int *opened);
CVAPI int cv_videoio_videoCaptureGet(void *cap, int propId, double *value);
CVAPI int cv_videoio_videoCaptureSet(void *cap, int propId, double value);
CVAPI int cv_videoio_videoCaptureGrab(void *cap);
CVAPI int cv_videoio_videoCaptureRead(void *cap, cv::Mat **pDst);
CVAPI int cv_videoio_videoCaptureRetrieve(void *cap, cv::Mat **pDst, int flag);
CVAPI int cv_videoio_videoCaptureGetFrame(void *cap, cv::Mat **pDst);

CVAPI int cv_videoio_createVideoCaptureFromDevice(int index, int apiPreference, void **handle);

CVAPI int cv_videoio_createVideoWriter(const char *filename, int fourcc, double fps, CVSize frameSize, int isColor, void **handle);
CVAPI int cv_videoio_deleteVideoWriter(void *writer);
CVAPI int cv_videoio_videoWriterIsOpened(void *writer, int *opened);
CVAPI int cv_videoio_videoWriterWrite(void *writer, cv::Mat *image);
CVAPI int cv_videoio_videoWriterRelease(void *writer);

CVAPI double cv_videoio_videoWriterGet(void *writer, int propId);
CVAPI int cv_videoio_videoWriterSet(void *writer, int propId, double value);

CVAPI int cv_videoio_videoCaptureRelease(void *cap);
CVAPI int cv_videoio_videoCaptureFourCC(char c1, char c2, char c3, char c4);
CVAPI int cv_videoio_videoCaptureGetBackendName(void *cap, char *name, int maxLen);
CVAPI int cv_videoio_videoCaptureGetExceptionMode(void *cap, int *mode);
CVAPI int cv_videoio_videoCaptureSetExceptionMode(void *cap, int mode);

CVAPI int cv_videoio_videoWriterGetBackendName(void *writer, char *name, int maxLen);
CVAPI int cv_videoio_videoWriterFourcc(char c1, char c2, char c3, char c4);

#endif
