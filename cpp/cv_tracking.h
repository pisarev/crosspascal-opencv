
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_TRACKING_H
#define CV_TRACKING_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/tracking.hpp>

CVAPI int cv_tracking_createBoostingTracker(void **handle);
CVAPI int cv_tracking_createMOSSETracker(void **handle);
CVAPI int cv_tracking_createMILTracker(void **handle);
CVAPI int cv_tracking_createKCFTracker(void **handle);
CVAPI int cv_tracking_createTLDTracker(void **handle);
CVAPI int cv_tracking_createMedianFlowTracker(void **handle);
CVAPI int cv_tracking_createGOTURNTracker(void **handle);
CVAPI int cv_tracking_createCSRTTracker(void **handle);

CVAPI int cv_tracking_deleteTracker(void *tracker);

CVAPI int cv_tracking_trackerInit(void *tracker, cv::Mat *image, CVRect boundingBox);

CVAPI int cv_tracking_trackerUpdate(void *tracker, cv::Mat *image, CVRect *boundingBox);

#endif
