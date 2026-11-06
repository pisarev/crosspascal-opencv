
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_videoio.h"
#include <cstring>

CVAPI int cv_videoio_createVideoCapture(const char *filename, int apiPreference, void **handle)
{
    cv_clear_error();

    try {
        auto *cap = new cv::VideoCapture(filename, apiPreference);
        *handle = cap;
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

CVAPI int cv_videoio_deleteVideoCapture(void *cap)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        delete ptr;
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

CVAPI int cv_videoio_videoCaptureIsOpened(void *cap, int *opened)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        *opened = ptr->isOpened() ? 1 : 0;
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

CVAPI int cv_videoio_videoCaptureGet(void *cap, int propId, double *value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        *value = ptr->get(propId);
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

CVAPI int cv_videoio_videoCaptureSet(void *cap, int propId, double value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        ptr->set(propId, value);
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

CVAPI int cv_videoio_videoCaptureGrab(void *cap)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        bool ok = ptr->grab();
        return ok ? 1 : 0;
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

CVAPI int cv_videoio_videoCaptureRead(void *cap, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        cv::Mat *dst = new cv::Mat();
        bool ok = ptr->read(*dst);
        if (!ok) {
            delete dst;
            cv_set_error_literal("VideoCaptureRead: no frame available");
            return 0;
        }
        *pDst = dst;
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

CVAPI int cv_videoio_videoCaptureRetrieve(void *cap, cv::Mat **pDst, int flag)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        cv::Mat *dst = new cv::Mat();
        bool ok = ptr->retrieve(*dst, flag);
        if (!ok) {
            delete dst;
            cv_set_error_literal("VideoCaptureRetrieve: no frame available");
            return 0;
        }
        *pDst = dst;
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

CVAPI int cv_videoio_videoCaptureGetFrame(void *cap, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        cv::Mat *dst = new cv::Mat();
        *ptr >> *dst;
        if (dst->empty()) {
            delete dst;
            cv_set_error_literal("VideoCaptureGetFrame: no frame available");
            return 0;
        }
        *pDst = dst;
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

CVAPI int cv_videoio_createVideoCaptureFromDevice(int index, int apiPreference, void **handle)
{
    cv_clear_error();

    try {
        auto *cap = new cv::VideoCapture(index, apiPreference);
        *handle = cap;
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

CVAPI int cv_videoio_createVideoWriter(const char *filename, int fourcc, double fps, CVSize frameSize, int isColor, void **handle)
{
    cv_clear_error();

    try {
        auto *writer = new cv::VideoWriter(filename, fourcc, fps, cv::Size(frameSize.cx, frameSize.cy), isColor != 0);
        *handle = writer;
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

CVAPI int cv_videoio_deleteVideoWriter(void *writer)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        delete ptr;
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

CVAPI int cv_videoio_videoWriterIsOpened(void *writer, int *opened)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        *opened = ptr->isOpened() ? 1 : 0;
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

CVAPI int cv_videoio_videoWriterWrite(void *writer, cv::Mat *image)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        ptr->write(*image);
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

CVAPI int cv_videoio_videoWriterRelease(void *writer)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        ptr->release();
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

CVAPI double cv_videoio_videoWriterGet(void *writer, int propId)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        return ptr->get(propId);
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

CVAPI int cv_videoio_videoWriterSet(void *writer, int propId, double value)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        ptr->set(propId, value);
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

CVAPI int cv_videoio_videoCaptureRelease(void *cap)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        ptr->release();
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

CVAPI int cv_videoio_videoCaptureFourCC(char c1, char c2, char c3, char c4)
{
    cv_clear_error();
    try {
        return cv::VideoWriter::fourcc(c1, c2, c3, c4);
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

CVAPI int cv_videoio_videoCaptureGetBackendName(void *cap, char *name, int maxLen)
{
    cv_clear_error();
    if (!name || maxLen <= 0) {
        cv_set_error_literal("Output buffer must have positive capacity");
        return 0;
    }

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        std::string backend = ptr->getBackendName();
        int len = (int)backend.size();
        if (len >= maxLen) len = maxLen - 1;
        memcpy(name, backend.c_str(), len);
        name[len] = '\0';
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

CVAPI int cv_videoio_videoCaptureGetExceptionMode(void *cap, int *mode)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        *mode = ptr->getExceptionMode() ? 1 : 0;
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

CVAPI int cv_videoio_videoCaptureSetExceptionMode(void *cap, int mode)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::VideoCapture*>(cap);
        ptr->setExceptionMode(mode != 0);
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

CVAPI int cv_videoio_videoWriterGetBackendName(void *writer, char *name, int maxLen)
{
    cv_clear_error();
    if (!name || maxLen <= 0) {
        cv_set_error_literal("Output buffer must have positive capacity");
        return 0;
    }

    try {
        auto *ptr = static_cast<cv::VideoWriter*>(writer);
        std::string backend = ptr->getBackendName();
        int len = (int)backend.size();
        if (len >= maxLen) len = maxLen - 1;
        memcpy(name, backend.c_str(), len);
        name[len] = '\0';
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

CVAPI int cv_videoio_videoWriterFourcc(char c1, char c2, char c3, char c4)
{
    cv_clear_error();
    try {
        return cv::VideoWriter::fourcc(c1, c2, c3, c4);
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
