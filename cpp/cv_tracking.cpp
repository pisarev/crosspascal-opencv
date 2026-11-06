
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_tracking.h"
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>

struct TrackerHolder {
    cv::Ptr<cv::Tracker> tracker;
    cv::Ptr<cv::legacy::Tracker> legacy;
    bool isLegacy;

    TrackerHolder(cv::Ptr<cv::Tracker> t) : tracker(t), isLegacy(false) {}
    TrackerHolder(cv::Ptr<cv::legacy::Tracker> t) : legacy(t), isLegacy(true) {}
};

CVAPI int cv_tracking_createBoostingTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::legacy::TrackerBoosting> tracker = cv::legacy::TrackerBoosting::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerBoosting");
            return 0;
        }
        *handle = new TrackerHolder(tracker.staticCast<cv::legacy::Tracker>());
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createMOSSETracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::legacy::TrackerMOSSE> tracker = cv::legacy::TrackerMOSSE::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerMOSSE");
            return 0;
        }
        *handle = new TrackerHolder(tracker.staticCast<cv::legacy::Tracker>());
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createMILTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerMIL::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerMIL");
            return 0;
        }
        *handle = new TrackerHolder(tracker);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createKCFTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerKCF");
            return 0;
        }
        *handle = new TrackerHolder(tracker);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createTLDTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::legacy::TrackerTLD> tracker = cv::legacy::TrackerTLD::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerTLD");
            return 0;
        }
        *handle = new TrackerHolder(tracker.staticCast<cv::legacy::Tracker>());
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createMedianFlowTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::legacy::TrackerMedianFlow> tracker = cv::legacy::TrackerMedianFlow::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerMedianFlow");
            return 0;
        }
        *handle = new TrackerHolder(tracker.staticCast<cv::legacy::Tracker>());
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createGOTURNTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerGOTURN::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerGOTURN");
            return 0;
        }
        *handle = new TrackerHolder(tracker);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_createCSRTTracker(void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerCSRT::create();
        if (tracker.empty()) {
            cv_set_error_literal("Failed to create TrackerCSRT");
            return 0;
        }
        *handle = new TrackerHolder(tracker);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_tracking_deleteTracker(void *tracker)
{
    cv_clear_error();

    try {
        if (!tracker) {
            cv_set_error_literal("Tracker pointer is null");
            return 0;
        }
        TrackerHolder *holder = static_cast<TrackerHolder *>(tracker);
        delete holder;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_tracking_trackerInit(void *tracker, cv::Mat *image, CVRect boundingBox)
{
    cv_clear_error();

    try {
        if (!tracker) {
            cv_set_error_literal("Tracker pointer is null");
            return 0;
        }
        TrackerHolder *holder = static_cast<TrackerHolder *>(tracker);
        if (holder->isLegacy) {
            cv::Rect2d roi(boundingBox.x, boundingBox.y, boundingBox.hSize, boundingBox.vSize);
            bool ok = holder->legacy->init(*image, roi);
            if (!ok) {
                cv_set_error_literal("Legacy tracker init failed");
                return 0;
            }
        } else {
            cv::Rect roi(boundingBox.x, boundingBox.y, boundingBox.hSize, boundingBox.vSize);
            holder->tracker->init(*image, roi);
        }
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_tracking_trackerUpdate(void *tracker, cv::Mat *image, CVRect *boundingBox)
{
    cv_clear_error();

    try {
        if (!tracker) {
            cv_set_error_literal("Tracker pointer is null");
            return 0;
        }
        TrackerHolder *holder = static_cast<TrackerHolder *>(tracker);
        bool ok;
        if (holder->isLegacy) {
            cv::Rect2d roi;
            ok = holder->legacy->update(*image, roi);
            if (ok) {
                boundingBox->x = (int)roi.x;
                boundingBox->y = (int)roi.y;
                boundingBox->hSize = (int)roi.width;
                boundingBox->vSize = (int)roi.height;
            }
        } else {
            cv::Rect roi;
            ok = holder->tracker->update(*image, roi);
            if (ok) {
                boundingBox->x = roi.x;
                boundingBox->y = roi.y;
                boundingBox->hSize = roi.width;
                boundingBox->vSize = roi.height;
            }
        }
        if (!ok) {
            cv_set_error_literal("Tracker update failed - target lost");
            return 0;
        }
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
