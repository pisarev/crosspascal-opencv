
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_HIGHGUI_H
#define CV_HIGHGUI_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/highgui.hpp>

typedef void (*TrackbarCallback)(int pos, void *userdata);

CVAPI int cv_highgui_namedWindow(const char *winname, int flags);
CVAPI int cv_highgui_destroyWindow(const char *winname);
CVAPI int cv_highgui_destroyAllWindows();
CVAPI int cv_highgui_imShow(const char *winname, cv::Mat *mat);

CVAPI int cv_highgui_waitKey(int delay, int *key);
CVAPI int cv_highgui_waitKeyEx(int delay, int *key);

CVAPI int cv_highgui_createTrackbar(const char *trackbarname, const char *winname, int *value, int count, TrackbarCallback onChange, void *userdata);
CVAPI int cv_highgui_getTrackbarPos(const char *trackbarname, const char *winname, int *pos);

typedef void (*MouseCallback)(int event, int x, int y, int flags, void *userdata);

CVAPI int cv_highgui_moveWindow(const char *winname, int x, int y);
CVAPI int cv_highgui_resizeWindow(const char *winname, int width, int height);
CVAPI int cv_highgui_setWindowProperty(const char *winname, int propId, double propValue);
CVAPI double cv_highgui_getWindowProperty(const char *winname, int propId);
CVAPI int cv_highgui_setWindowTitle(const char *winname, const char *title);

CVAPI int cv_highgui_pollKey();

CVAPI int cv_highgui_selectROI(const char *winname, cv::Mat *img, CVRect *result, int showCrosshair, int fromCenter);

CVAPI int cv_highgui_setMouseCallback(const char *winname, MouseCallback onMouse, void *userdata);

CVAPI int cv_highgui_getWindowImageRect(const char *winname, CVRect *result);
CVAPI int cv_highgui_setTrackbarPos(const char *trackbarname, const char *winname, int pos);
CVAPI int cv_highgui_setTrackbarMin(const char *trackbarname, const char *winname, int minval);
CVAPI int cv_highgui_setTrackbarMax(const char *trackbarname, const char *winname, int maxval);
CVAPI int cv_highgui_selectROIs(const char *winname, cv::Mat *img, CVRect *rois, int *count, int maxCount, int showCrosshair, int fromCenter);

#endif
