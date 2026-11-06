
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_imgcodecs.h"
#include <vector>

CVAPI int cv_imgcodecs_openMat(const char *filename, int flags, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        cv::Mat img = cv::imread(filename, flags);
        if (img.empty()) {
            cv_set_error_cstr(("Failed to read image: " + std::string(filename)).c_str());
            return 0;
        }
        *pDst = new cv::Mat(img);
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

CVAPI int cv_imgcodecs_saveMat(const char *filename, cv::Mat *mat)
{
    cv_clear_error();

    try {
        bool ok = cv::imwrite(filename, *mat);
        if (!ok) {
            cv_set_error_cstr(("Failed to write image: " + std::string(filename)).c_str());
            return 0;
        }
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

CVAPI int cv_imgcodecs_imDecode(void *data, int dataSize, int flags, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        std::vector<uchar> buf((uchar *)data, (uchar *)data + dataSize);
        cv::Mat img = cv::imdecode(buf, flags);
        if (img.empty()) {
            cv_set_error_literal("Failed to decode image from buffer");
            return 0;
        }
        *pDst = new cv::Mat(img);
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

CVAPI int cv_imgcodecs_imEncode(const char *ext, cv::Mat *img, void **data, int *dataSize, int quality)
{
    cv_clear_error();

    try {
        std::vector<int> params;
        if (quality >= 0) {

            std::string extension(ext);
            if (extension == ".jpg" || extension == ".jpeg") {
                params.push_back(cv::IMWRITE_JPEG_QUALITY);
            } else if (extension == ".png") {
                params.push_back(cv::IMWRITE_PNG_COMPRESSION);
            } else if (extension == ".webp") {
                params.push_back(cv::IMWRITE_WEBP_QUALITY);
            } else {
                params.push_back(cv::IMWRITE_JPEG_QUALITY);
            }
            params.push_back(quality);
        }
        std::vector<uchar> outBuf;
        bool ok = cv::imencode(ext, *img, outBuf, params);
        if (!ok) {
            cv_set_error_literal("Failed to encode image");
            return 0;
        }
        uchar *rawBuf = new uchar[outBuf.size()];
        memcpy(rawBuf, outBuf.data(), outBuf.size());
        *data = rawBuf;
        *dataSize = (int)outBuf.size();
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

CVAPI int cv_imgcodecs_freeBuf(void *data)
{
    cv_clear_error();
    try {


        if (data) {
            delete[] static_cast<unsigned char *>(data);
        }
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

CVAPI int cv_imgcodecs_imReadMulti(const char *filename, int flags, cv::Mat **targets, int *count)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> images;
        bool ok = cv::imreadmulti(filename, images, flags);
        if (!ok) {
            cv_set_error_cstr(("Failed to read multi-page image: " + std::string(filename)).c_str());
            return 0;
        }
        int n = (int)images.size();
        if (n > *count) n = *count;
        for (int i = 0; i < n; i++) {
            targets[i] = new cv::Mat(images[i].clone());
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

CVAPI int cv_imgcodecs_imCount(const char *filename, int flags, int *count)
{
    cv_clear_error();

    try {
        *count = (int)cv::imcount(filename, flags);
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

CVAPI int cv_imgcodecs_haveImageReader(const char *filename)
{
    cv_clear_error();

    try {
        return cv::haveImageReader(filename) ? 1 : 0;
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

CVAPI int cv_imgcodecs_haveImageWriter(const char *filename)
{
    cv_clear_error();

    try {
        return cv::haveImageWriter(filename) ? 1 : 0;
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
