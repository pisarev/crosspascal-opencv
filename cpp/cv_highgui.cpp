
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_highgui.h"
#include <vector>

CVAPI int cv_highgui_namedWindow(const char *winname, int flags)
{
    cv_clear_error();

    try {
        cv::namedWindow(winname, flags);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_destroyWindow(const char *winname)
{
    cv_clear_error();

    try {
        cv::destroyWindow(winname);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_destroyAllWindows()
{
    cv_clear_error();

    try {
        cv::destroyAllWindows();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_imShow(const char *winname, cv::Mat *mat)
{
    cv_clear_error();

    try {
        cv::imshow(winname, *mat);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_waitKey(int delay, int *key)
{
    cv_clear_error();

    try {
        *key = cv::waitKey(delay);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_waitKeyEx(int delay, int *key)
{
    cv_clear_error();

    try {
        *key = cv::waitKeyEx(delay);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_createTrackbar(const char *trackbarname, const char *winname, int *value, int count, TrackbarCallback onChange, void *userdata)
{
    cv_clear_error();

    try {
        cv::createTrackbar(trackbarname, winname, value, count, onChange, userdata);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_getTrackbarPos(const char *trackbarname, const char *winname, int *pos)
{
    cv_clear_error();

    try {
        *pos = cv::getTrackbarPos(trackbarname, winname);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_moveWindow(const char *winname, int x, int y)
{
    cv_clear_error();

    try {
        cv::moveWindow(winname, x, y);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_resizeWindow(const char *winname, int width, int height)
{
    cv_clear_error();

    try {
        cv::resizeWindow(winname, width, height);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_setWindowProperty(const char *winname, int propId, double propValue)
{
    cv_clear_error();

    try {
        cv::setWindowProperty(winname, propId, propValue);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_highgui_getWindowProperty(const char *winname, int propId)
{
    cv_clear_error();

    try {
        return cv::getWindowProperty(winname, propId);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_setWindowTitle(const char *winname, const char *title)
{
    cv_clear_error();

    try {
        cv::setWindowTitle(winname, title);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_pollKey()
{
    cv_clear_error();

    try {
        return cv::pollKey();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_selectROI(const char *winname, cv::Mat *img, CVRect *result, int showCrosshair, int fromCenter)
{
    cv_clear_error();

    try {
        cv::Rect r = cv::selectROI(winname, *img, showCrosshair != 0, fromCenter != 0);
        result->x = r.x;
        result->y = r.y;
        result->hSize = r.width;
        result->vSize = r.height;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_setMouseCallback(const char *winname, MouseCallback onMouse, void *userdata)
{
    cv_clear_error();

    try {
        cv::setMouseCallback(winname, onMouse, userdata);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_getWindowImageRect(const char *winname, CVRect *result)
{
    cv_clear_error();

    try {
        cv::Rect r = cv::getWindowImageRect(winname);
        result->x = r.x;
        result->y = r.y;
        result->hSize = r.width;
        result->vSize = r.height;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_setTrackbarPos(const char *trackbarname, const char *winname, int pos)
{
    cv_clear_error();

    try {
        cv::setTrackbarPos(trackbarname, winname, pos);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_setTrackbarMin(const char *trackbarname, const char *winname, int minval)
{
    cv_clear_error();

    try {
        cv::setTrackbarMin(trackbarname, winname, minval);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_setTrackbarMax(const char *trackbarname, const char *winname, int maxval)
{
    cv_clear_error();

    try {
        cv::setTrackbarMax(trackbarname, winname, maxval);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_highgui_selectROIs(const char *winname, cv::Mat *img, CVRect *rois, int *count, int maxCount, int showCrosshair, int fromCenter)
{
    cv_clear_error();

    try {
        std::vector<cv::Rect> boundingBoxes;
        cv::selectROIs(winname, *img, boundingBoxes, showCrosshair != 0, fromCenter != 0);
        int n = (int)boundingBoxes.size();
        if (n > maxCount) n = maxCount;
        for (int i = 0; i < n; i++) {
            rois[i].x = boundingBoxes[i].x;
            rois[i].y = boundingBoxes[i].y;
            rois[i].hSize = boundingBoxes[i].width;
            rois[i].vSize = boundingBoxes[i].height;
        }
        *count = n;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
