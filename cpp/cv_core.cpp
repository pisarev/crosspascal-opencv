

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_core.h"
#include "helper.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <cstring>
#include <memory>
#include <utility>



CVAPI cv::Mat *cv_core_makeMat(int hSize, int vSize, int type) {
    cv_clear_error();

    try {
        return new cv::Mat(vSize, hSize, type);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}


CVAPI cv::Mat *cv_core_createMat(void *imageData, int imageSize, int flags) {
    cv_clear_error();

    try {
        cv::Mat buf(1, imageSize, CV_8UC1, imageData);
        cv::Mat decoded = cv::imdecode(buf, flags);
        if (decoded.empty()) {
            cv_set_error_literal("imdecode failed: empty result");
            return nullptr;
        }
        return new cv::Mat(decoded);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}


CVAPI int cv_core_deleteMat(cv::Mat **pmat) {
    cv_clear_error();

    try {
        if (pmat && *pmat) {
            delete *pmat;
            *pmat = nullptr;
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


CVAPI int cv_core_createRoi(cv::Mat *mat, CVRect rect, cv::Mat **target) {
    cv_clear_error();

    try {
        cv::Rect roi(rect.x, rect.y, rect.hSize, rect.vSize);
        *target = new cv::Mat(*mat, roi);
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


CVAPI int cv_core_copyTo(cv::Mat *src, cv::Mat **target, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            src->copyTo(*dst, *mask);
        } else {
            src->copyTo(*dst);
        }
        *target = dst.release();
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


CVAPI int cv_core_clone(cv::Mat *src, cv::Mat **target) {
    cv_clear_error();

    try {
        *target = new cv::Mat(src->clone());
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


CVAPI int cv_core_setTo(cv::Mat **pmat, CVScalar value, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty()) {
            (*pmat)->setTo(cv::Scalar(value.v0, value.v1, value.v2, value.v3), *mask);
        } else {
            (*pmat)->setTo(cv::Scalar(value.v0, value.v1, value.v2, value.v3));
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


CVAPI int cv_core_setRandom(cv::Mat **pmat, CVScalar low, CVScalar high) {
    cv_clear_error();

    try {
        cv::randu(**pmat,
            cv::Scalar(low.v0, low.v1, low.v2, low.v3),
            cv::Scalar(high.v0, high.v1, high.v2, high.v3));
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


CVAPI int cv_core_getMatHSize(cv::Mat *mat, int *hSize) {
    cv_clear_error();

    try {
        *hSize = mat->cols;
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


CVAPI int cv_core_getMatVSize(cv::Mat *mat, int *vSize) {
    cv_clear_error();

    try {
        *vSize = mat->rows;
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


CVAPI int cv_core_getMatDepth(cv::Mat *mat, int *depth) {
    cv_clear_error();

    try {
        *depth = mat->depth();
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


CVAPI int cv_core_getMatData(cv::Mat *mat, void **data) {
    cv_clear_error();

    try {
        *data = mat->data;
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


CVAPI int cv_core_getMatStep(cv::Mat *mat, int *step) {
    cv_clear_error();

    try {
        *step = (int)mat->step;
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


CVAPI int cv_core_getMatFormat(cv::Mat *mat, int *format) {
    cv_clear_error();

    try {
        *format = mat->channels();
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


CVAPI int cv_core_getMatType(cv::Mat *mat, int *type) {
    cv_clear_error();

    try {
        *type = mat->type();
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


CVAPI int cv_core_getMatTotal(cv::Mat *mat, int *total) {
    cv_clear_error();

    try {
        *total = (int)mat->total();
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


CVAPI int cv_core_getMatElemSize(cv::Mat *mat, int *elemSize) {
    cv_clear_error();

    try {
        *elemSize = (int)mat->elemSize();
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


CVAPI int cv_core_getMatEmpty(cv::Mat *mat, int *empty) {
    cv_clear_error();

    try {
        *empty = mat->empty() ? 1 : 0;
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


CVAPI int cv_core_readMat(cv::Mat *mat, ReadImage read, int depth, int n, void *data) {
    cv_clear_error();

    try {
        read_image(mat, read, depth, n, data);
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


CVAPI int cv_core_convertType(cv::Mat *src, cv::Mat **target, int rtype, double alpha, double beta) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        src->convertTo(*dst, rtype, alpha, beta);
        *target = dst.release();
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


CVAPI int cv_core_convertScaleAbs(cv::Mat *src, cv::Mat **target, double alpha, double beta) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::convertScaleAbs(*src, *dst, alpha, beta);
        *target = dst.release();
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


CVAPI int cv_core_invert(cv::Mat *src, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::invert(*src, *dst, flags);
        *target = dst.release();
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


CVAPI int cv_core_bitwiseAnd(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::bitwise_and(*src1, *src2, *dst, *mask);
        } else {
            cv::bitwise_and(*src1, *src2, *dst);
        }
        *target = dst.release();
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


CVAPI int cv_core_bitwiseNot(cv::Mat *src, cv::Mat **target, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::bitwise_not(*src, *dst, *mask);
        } else {
            cv::bitwise_not(*src, *dst);
        }
        *target = dst.release();
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


CVAPI int cv_core_bitwiseOr(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::bitwise_or(*src1, *src2, *dst, *mask);
        } else {
            cv::bitwise_or(*src1, *src2, *dst);
        }
        *target = dst.release();
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


CVAPI int cv_core_bitwiseXor(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::bitwise_xor(*src1, *src2, *dst, *mask);
        } else {
            cv::bitwise_xor(*src1, *src2, *dst);
        }
        *target = dst.release();
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


CVAPI int cv_core_operation(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, double alpha, double beta, double gamma, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::addWeighted(*src1, alpha, *src2, beta, gamma, *dst, dtype);
        *target = dst.release();
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


CVAPI int cv_core_normalize(cv::Mat *src, cv::Mat **target, double alpha, double beta, int normType, int dtype, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::normalize(*src, *dst, alpha, beta, normType, dtype, *mask);
        } else {
            cv::normalize(*src, *dst, alpha, beta, normType, dtype);
        }
        *target = dst.release();
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


CVAPI int cv_core_meanStdDev(cv::Mat *src, cv::Mat **mean, cv::Mat **stddev, cv::Mat *mask) {
    cv_clear_error();
    if (!mean || !stddev || mean == stddev) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstMean = std::make_unique<cv::Mat>();
        auto dstStddev = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::meanStdDev(*src, *dstMean, *dstStddev, *mask);
        } else {
            cv::meanStdDev(*src, *dstMean, *dstStddev);
        }
        *mean = dstMean.release();
        *stddev = dstStddev.release();
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


CVAPI int cv_core_minAreaRect(cv::Mat *points, CVRotatedRect *result) {
    cv_clear_error();

    try {
        cv::RotatedRect rr = cv::minAreaRect(*points);
        result->center.x = rr.center.x;
        result->center.y = rr.center.y;
        result->size.x = rr.size.width;
        result->size.y = rr.size.height;
        result->angle = rr.angle;
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



CVAPI int cv_core_add(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::add(*src1, *src2, *dst, *mask, dtype);
        } else {
            cv::add(*src1, *src2, *dst, cv::noArray(), dtype);
        }
        *target = dst.release();
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


CVAPI int cv_core_subtract(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (mask && !mask->empty()) {
            cv::subtract(*src1, *src2, *dst, *mask, dtype);
        } else {
            cv::subtract(*src1, *src2, *dst, cv::noArray(), dtype);
        }
        *target = dst.release();
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


CVAPI int cv_core_multiply(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, double scale, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::multiply(*src1, *src2, *dst, scale, dtype);
        *target = dst.release();
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


CVAPI int cv_core_divide(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, double scale, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::divide(*src1, *src2, *dst, scale, dtype);
        *target = dst.release();
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


CVAPI int cv_core_absdiff(cv::Mat *src1, cv::Mat *src2, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::absdiff(*src1, *src2, *dst);
        *target = dst.release();
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


CVAPI int cv_core_min(cv::Mat *src1, cv::Mat *src2, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::min(*src1, *src2, *dst);
        *target = dst.release();
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


CVAPI int cv_core_max(cv::Mat *src1, cv::Mat *src2, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::max(*src1, *src2, *dst);
        *target = dst.release();
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


CVAPI int cv_core_merge(cv::Mat **mv, int count, cv::Mat **target) {
    cv_clear_error();

    try {
        std::vector<cv::Mat> channels(count);
        for (int i = 0; i < count; i++)
            channels[i] = *mv[i];
        auto dst = std::make_unique<cv::Mat>();
        cv::merge(channels, *dst);
        *target = dst.release();
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


CVAPI int cv_core_split(cv::Mat *src, cv::Mat **mv) {
    cv_clear_error();
    if (!src || !mv) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        std::vector<cv::Mat> channels;
        cv::split(*src, channels);
        std::vector<std::unique_ptr<cv::Mat>> results;
        results.reserve(channels.size());
        for (auto &channel : channels)
            results.push_back(std::make_unique<cv::Mat>(std::move(channel)));
        for (size_t i = 0; i < results.size(); i++)
            mv[i] = results[i].release();
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


CVAPI int cv_core_flip(cv::Mat *src, cv::Mat **target, int flipCode) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::flip(*src, *dst, flipCode);
        *target = dst.release();
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


CVAPI int cv_core_transpose(cv::Mat *src, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::transpose(*src, *dst);
        *target = dst.release();
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


CVAPI int cv_core_vconcat(cv::Mat *src1, cv::Mat *src2, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::vconcat(*src1, *src2, *dst);
        *target = dst.release();
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


CVAPI int cv_core_hconcat(cv::Mat *src1, cv::Mat *src2, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::hconcat(*src1, *src2, *dst);
        *target = dst.release();
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


CVAPI int cv_core_pow(cv::Mat *src, double power, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::pow(*src, power, *dst);
        *target = dst.release();
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


CVAPI int cv_core_sqrt(cv::Mat *src, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::sqrt(*src, *dst);
        *target = dst.release();
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


CVAPI int cv_core_exp(cv::Mat *src, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::exp(*src, *dst);
        *target = dst.release();
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


CVAPI int cv_core_log(cv::Mat *src, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::log(*src, *dst);
        *target = dst.release();
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


CVAPI int cv_core_magnitude(cv::Mat *x, cv::Mat *y, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::magnitude(*x, *y, *dst);
        *target = dst.release();
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


CVAPI int cv_core_phase(cv::Mat *x, cv::Mat *y, cv::Mat **target, int angleInDegrees) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::phase(*x, *y, *dst, angleInDegrees != 0);
        *target = dst.release();
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


CVAPI int cv_core_compare(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, int cmpop) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::compare(*src1, *src2, *dst, cmpop);
        *target = dst.release();
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


CVAPI int cv_core_countNonZero(cv::Mat *src, int *count) {
    cv_clear_error();

    try {
        *count = cv::countNonZero(*src);
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


CVAPI int cv_core_sum(cv::Mat *src, CVScalar *result) {
    cv_clear_error();

    try {
        cv::Scalar s = cv::sum(*src);
        result->v0 = s[0];
        result->v1 = s[1];
        result->v2 = s[2];
        result->v3 = s[3];
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


CVAPI int cv_core_trace(cv::Mat *src, CVScalar *result) {
    cv_clear_error();

    try {
        cv::Scalar s = cv::trace(*src);
        result->v0 = s[0];
        result->v1 = s[1];
        result->v2 = s[2];
        result->v3 = s[3];
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


CVAPI int cv_core_determinant(cv::Mat *src, double *value) {
    cv_clear_error();

    try {
        *value = cv::determinant(*src);
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


CVAPI int cv_core_solve(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (!cv::solve(*src1, *src2, *dst, flags)) {
            cv_set_error_literal("Linear system has no solution for this decomposition");
            return 0;
        }
        *target = dst.release();
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


CVAPI int cv_core_eigen(cv::Mat *src, cv::Mat **eigenvalues, cv::Mat **eigenvectors) {
    cv_clear_error();
    if (!eigenvalues || !eigenvectors || eigenvalues == eigenvectors) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstVals = std::make_unique<cv::Mat>();
        auto dstVecs = std::make_unique<cv::Mat>();
        if (!cv::eigen(*src, *dstVals, *dstVecs)) {
            cv_set_error_literal("Could not compute the eigendecomposition");
            return 0;
        }
        *eigenvalues = dstVals.release();
        *eigenvectors = dstVecs.release();
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


CVAPI int cv_core_kmeans(cv::Mat *data, int K, int attempts, int flags, cv::Mat **labels, cv::Mat **centers) {
    cv_clear_error();
    if (!data || !labels || !centers || labels == centers) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 100, 0.2);
        const bool useInitial = (flags & cv::KMEANS_USE_INITIAL_LABELS) != 0;
        if (useInitial && (!*labels || (*labels)->empty())) {
            cv_set_error_literal("KMeans requires initial labels for this flag");
            return 0;
        }
        auto dstLabels = std::make_unique<cv::Mat>(useInitial ? (*labels)->clone() : cv::Mat());
        auto dstCenters = std::make_unique<cv::Mat>();
        cv::kmeans(*data, K, *dstLabels, criteria, attempts, flags, *dstCenters);
        if (useInitial)
            **labels = std::move(*dstLabels);
        else
            *labels = dstLabels.release();
        *centers = dstCenters.release();
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


CVAPI int cv_core_setIdentity(cv::Mat **pmat, CVScalar value) {
    cv_clear_error();
    if (!pmat) {
        cv_set_error_literal("Missing matrix pointer");
        return 0;
    }

    try {
        auto empty = *pmat ? nullptr : std::make_unique<cv::Mat>();
        cv::Mat &working = *pmat ? **pmat : *empty;
        cv::setIdentity(working, cv::Scalar(value.v0, value.v1, value.v2, value.v3));
        if (empty) *pmat = empty.release();
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


CVAPI int cv_core_reduce(cv::Mat *src, cv::Mat **target, int dim, int rtype, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::reduce(*src, *dst, dim, rtype, dtype);
        *target = dst.release();
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


CVAPI int cv_core_minMaxLoc(cv::Mat *src, double *minVal, double *maxVal, CVPoint *minLoc, CVPoint *maxLoc, cv::Mat *mask) {
    cv_clear_error();

    try {
        cv::Point cvMinLoc, cvMaxLoc;
        if (mask && !mask->empty()) {
            cv::minMaxLoc(*src, minVal, maxVal, minLoc ? &cvMinLoc : nullptr, maxLoc ? &cvMaxLoc : nullptr, *mask);
        } else {
            cv::minMaxLoc(*src, minVal, maxVal, minLoc ? &cvMinLoc : nullptr, maxLoc ? &cvMaxLoc : nullptr);
        }
        if (minLoc) {
            minLoc->x = cvMinLoc.x;
            minLoc->y = cvMinLoc.y;
        }
        if (maxLoc) {
            maxLoc->x = cvMaxLoc.x;
            maxLoc->y = cvMaxLoc.y;
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


CVAPI double cv_core_norm(cv::Mat *src, int normType, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty()) {
            return cv::norm(*src, normType, *mask);
        } else {
            return cv::norm(*src, normType);
        }
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}



CVAPI int cv_core_addWeighted(cv::Mat *src1, double alpha, cv::Mat *src2, double beta, double gamma, cv::Mat **target, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::addWeighted(*src1, alpha, *src2, beta, gamma, *dst, dtype);
        *target = dst.release();
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


CVAPI int cv_core_scaleAdd(cv::Mat *src1, double alpha, cv::Mat *src2, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::scaleAdd(*src1, alpha, *src2, *dst);
        *target = dst.release();
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


CVAPI int cv_core_gemm(cv::Mat *src1, cv::Mat *src2, double alpha, cv::Mat *src3, double beta, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::gemm(*src1, *src2, alpha, *src3, beta, *dst, flags);
        *target = dst.release();
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


CVAPI int cv_core_mulTransposed(cv::Mat *src, cv::Mat **target, int aTa, cv::Mat *delta, double scale, int dtype) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (delta && !delta->empty()) {
            cv::mulTransposed(*src, *dst, aTa != 0, *delta, scale, dtype);
        } else {
            cv::mulTransposed(*src, *dst, aTa != 0, cv::noArray(), scale, dtype);
        }
        *target = dst.release();
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


CVAPI int cv_core_transform(cv::Mat *src, cv::Mat **target, cv::Mat *m) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::transform(*src, *dst, *m);
        *target = dst.release();
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


CVAPI int cv_core_perspectiveTransformMat(cv::Mat *src, cv::Mat **target, cv::Mat *m) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::perspectiveTransform(*src, *dst, *m);
        *target = dst.release();
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


CVAPI int cv_core_inRange(cv::Mat *src, CVScalar lowerb, CVScalar upperb, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::inRange(*src,
            cv::Scalar(lowerb.v0, lowerb.v1, lowerb.v2, lowerb.v3),
            cv::Scalar(upperb.v0, upperb.v1, upperb.v2, upperb.v3),
            *dst);
        *target = dst.release();
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


CVAPI int cv_core_LUT(cv::Mat *src, cv::Mat *lut, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::LUT(*src, *lut, *dst);
        *target = dst.release();
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


CVAPI int cv_core_repeat(cv::Mat *src, int ny, int nx, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::repeat(*src, ny, nx, *dst);
        *target = dst.release();
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


CVAPI int cv_core_rotate(cv::Mat *src, cv::Mat **target, int rotateCode) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::rotate(*src, *dst, rotateCode);
        *target = dst.release();
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


CVAPI int cv_core_copyMakeBorder(cv::Mat *src, cv::Mat **target, int top, int bottom, int left, int right, int borderType, CVScalar value) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::copyMakeBorder(*src, *dst, top, bottom, left, right, borderType,
            cv::Scalar(value.v0, value.v1, value.v2, value.v3));
        *target = dst.release();
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


CVAPI int cv_core_mean(cv::Mat *src, cv::Mat *mask, CVScalar *result) {
    cv_clear_error();

    try {
        cv::Scalar s;
        if (mask && !mask->empty())
            s = cv::mean(*src, *mask);
        else
            s = cv::mean(*src);
        result->v0 = s[0];
        result->v1 = s[1];
        result->v2 = s[2];
        result->v3 = s[3];
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


CVAPI int cv_core_minMaxIdx(cv::Mat *src, double *minVal, double *maxVal, int *minIdx, int *maxIdx, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty())
            cv::minMaxIdx(*src, minVal, maxVal, minIdx, maxIdx, *mask);
        else
            cv::minMaxIdx(*src, minVal, maxVal, minIdx, maxIdx);
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


CVAPI int cv_core_findNonZero(cv::Mat *src, cv::Mat **idx) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::findNonZero(*src, *dst);
        *idx = dst.release();
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


CVAPI int cv_core_sort(cv::Mat *src, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::sort(*src, *dst, flags);
        *target = dst.release();
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


CVAPI int cv_core_sortIdx(cv::Mat *src, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::sortIdx(*src, *dst, flags);
        *target = dst.release();
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


CVAPI int cv_core_completeSymm(cv::Mat **pmat, int lowerToUpper) {
    cv_clear_error();
    if (!pmat) {
        cv_set_error_literal("Missing matrix pointer");
        return 0;
    }

    try {
        auto empty = *pmat ? nullptr : std::make_unique<cv::Mat>();
        cv::Mat &working = *pmat ? **pmat : *empty;
        cv::completeSymm(working, lowerToUpper != 0);
        if (empty) *pmat = empty.release();
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


CVAPI int cv_core_patchNaNs(cv::Mat **pmat, double val) {
    cv_clear_error();
    if (!pmat) {
        cv_set_error_literal("Missing matrix pointer");
        return 0;
    }

    try {
        auto empty = *pmat ? nullptr : std::make_unique<cv::Mat>();
        cv::Mat &working = *pmat ? **pmat : *empty;
        cv::patchNaNs(working, val);
        if (empty) *pmat = empty.release();
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


CVAPI int cv_core_randShuffle(cv::Mat **pmat, double iterFactor) {
    cv_clear_error();
    if (!pmat) {
        cv_set_error_literal("Missing matrix pointer");
        return 0;
    }

    try {
        auto empty = *pmat ? nullptr : std::make_unique<cv::Mat>();
        cv::Mat &working = *pmat ? **pmat : *empty;
        cv::randShuffle(working, iterFactor);
        if (empty) *pmat = empty.release();
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


CVAPI int cv_core_dft(cv::Mat *src, cv::Mat **target, int flags, int nonzeroRows) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::dft(*src, *dst, flags, nonzeroRows);
        *target = dst.release();
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


CVAPI int cv_core_idft(cv::Mat *src, cv::Mat **target, int flags, int nonzeroRows) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::idft(*src, *dst, flags, nonzeroRows);
        *target = dst.release();
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


CVAPI int cv_core_dct(cv::Mat *src, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::dct(*src, *dst, flags);
        *target = dst.release();
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


CVAPI int cv_core_idct(cv::Mat *src, cv::Mat **target, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::idct(*src, *dst, flags);
        *target = dst.release();
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


CVAPI int cv_core_getOptimalDFTSize(int vecsize) {
    cv_clear_error();
    try {
        return cv::getOptimalDFTSize(vecsize);
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


CVAPI int cv_core_mulSpectrums(cv::Mat *a, cv::Mat *b, cv::Mat **c, int flags, int conjB) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::mulSpectrums(*a, *b, *dst, flags, conjB != 0);
        *c = dst.release();
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



CVAPI int cv_core_calcCovarMatrix(cv::Mat *samples, cv::Mat **covar, cv::Mat **mean, int flags, int ctype) {
    cv_clear_error();
    if (!samples || !covar || !mean || covar == mean) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        const bool useMean = (flags & cv::COVAR_USE_AVG) != 0;
        if (useMean && (!*mean || (*mean)->empty())) {
            cv_set_error_literal("Covariance requires the supplied mean for this flag");
            return 0;
        }
        auto dstCovar = std::make_unique<cv::Mat>();
        auto dstMean = std::make_unique<cv::Mat>(useMean ? (*mean)->clone() : cv::Mat());
        cv::calcCovarMatrix(*samples, *dstCovar, *dstMean, flags, ctype);
        if (useMean)
            **mean = std::move(*dstMean);
        else
            *mean = dstMean.release();
        *covar = dstCovar.release();
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


CVAPI double cv_core_Mahalanobis(cv::Mat *v1, cv::Mat *v2, cv::Mat *icovar) {
    cv_clear_error();
    try {
        return cv::Mahalanobis(*v1, *v2, *icovar);
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


CVAPI int cv_core_getMatChannels(cv::Mat *mat) {
    cv_clear_error();
    try {
        return mat->channels();
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


CVAPI int cv_core_convertFp16(cv::Mat *src, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::convertFp16(*src, *dst);
        *target = dst.release();
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


CVAPI int cv_core_borderInterpolate(int p, int len, int borderType) {
    cv_clear_error();
    try {
        return cv::borderInterpolate(p, len, borderType);
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


CVAPI int cv_core_PCACompute(cv::Mat *data, cv::Mat *mean, cv::Mat *eigenvectors, int maxComponents) {
    cv_clear_error();

    try {
        cv::PCA pca(*data, *mean, cv::PCA::DATA_AS_ROW, maxComponents);
        pca.mean.copyTo(*mean);
        pca.eigenvectors.copyTo(*eigenvectors);
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


CVAPI int cv_core_PCAProject(cv::Mat *data, cv::Mat *mean, cv::Mat *eigenvectors, cv::Mat **result) {
    cv_clear_error();

    try {
        cv::PCA pca;
        pca.mean = mean->clone();
        pca.eigenvectors = eigenvectors->clone();
        auto dst = std::make_unique<cv::Mat>();
        pca.project(*data, *dst);
        *result = dst.release();
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


CVAPI int cv_core_PCABackProject(cv::Mat *data, cv::Mat *mean, cv::Mat *eigenvectors, cv::Mat **result) {
    cv_clear_error();

    try {
        cv::PCA pca;
        pca.mean = mean->clone();
        pca.eigenvectors = eigenvectors->clone();
        auto dst = std::make_unique<cv::Mat>();
        pca.backProject(*data, *dst);
        *result = dst.release();
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


CVAPI int cv_core_SVDecomp(cv::Mat *src, cv::Mat **w, cv::Mat **u, cv::Mat **vt, int flags) {
    cv_clear_error();
    if (!w || !u || !vt || w == u || w == vt || u == vt) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstW = std::make_unique<cv::Mat>();
        auto dstU = std::make_unique<cv::Mat>();
        auto dstVt = std::make_unique<cv::Mat>();
        cv::SVD::compute(*src, *dstW, *dstU, *dstVt, flags);
        *w = dstW.release();
        *u = dstU.release();
        *vt = dstVt.release();
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


CVAPI int cv_core_SVBackSubst(cv::Mat *w, cv::Mat *u, cv::Mat *vt, cv::Mat *rhs, cv::Mat **target) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::SVD::backSubst(*w, *u, *vt, *rhs, *dst);
        *target = dst.release();
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


CVAPI double cv_core_PSNR(cv::Mat *src1, cv::Mat *src2, double R) {
    cv_clear_error();
    try {
        return cv::PSNR(*src1, *src2, R);
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


CVAPI int cv_core_polarToCart(cv::Mat *magnitude, cv::Mat *angle, cv::Mat **x, cv::Mat **y, int angleInDegrees) {
    cv_clear_error();
    if (!x || !y || x == y) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstX = std::make_unique<cv::Mat>();
        auto dstY = std::make_unique<cv::Mat>();
        cv::polarToCart(*magnitude, *angle, *dstX, *dstY, angleInDegrees != 0);
        *x = dstX.release();
        *y = dstY.release();
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


CVAPI int cv_core_cartToPolar(cv::Mat *x, cv::Mat *y, cv::Mat **magnitude, cv::Mat **angle, int angleInDegrees) {
    cv_clear_error();
    if (!magnitude || !angle || magnitude == angle) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstMag = std::make_unique<cv::Mat>();
        auto dstAngle = std::make_unique<cv::Mat>();
        cv::cartToPolar(*x, *y, *dstMag, *dstAngle, angleInDegrees != 0);
        *magnitude = dstMag.release();
        *angle = dstAngle.release();
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


CVAPI int cv_core_checkRange(cv::Mat *a, int quiet, int *pos_x, int *pos_y, double minVal, double maxVal) {
    cv_clear_error();

    try {
        cv::Point pos;
        bool result = cv::checkRange(*a, quiet != 0, &pos, minVal, maxVal);
        if (pos_x) *pos_x = pos.x;
        if (pos_y) *pos_y = pos.y;
        return result ? 1 : 0;
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


CVAPI int cv_core_eigenNonSymmetric(cv::Mat *src, cv::Mat **eigenvalues, cv::Mat **eigenvectors) {
    cv_clear_error();
    if (!eigenvalues || !eigenvectors || eigenvalues == eigenvectors) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstVals = std::make_unique<cv::Mat>();
        auto dstVecs = std::make_unique<cv::Mat>();
        cv::eigenNonSymmetric(*src, *dstVals, *dstVecs);
        *eigenvalues = dstVals.release();
        *eigenvectors = dstVecs.release();
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


CVAPI int cv_core_solveCubic(cv::Mat *coeffs, cv::Mat **roots) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::solveCubic(*coeffs, *dst);
        *roots = dst.release();
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


CVAPI double cv_core_solvePoly(cv::Mat *coeffs, cv::Mat **roots, int maxIters) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        double result = cv::solvePoly(*coeffs, *dst, maxIters);
        *roots = dst.release();
        return result;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_core_mixChannels(cv::Mat **src, int nsrcs, cv::Mat **dst, int ndsts, const int *fromTo, int npairs) {
    cv_clear_error();
    if (npairs < 0 || (npairs > 0 && (!src || !dst || !fromTo || nsrcs <= 0 || ndsts <= 0))) {
        cv_set_error_literal("Invalid mixChannels arguments");
        return 0;
    }

    try {
        if (npairs == 0)
            return 1;
        std::vector<cv::Mat> srcVec(nsrcs);
        for (int i = 0; i < nsrcs; i++) {
            if (!src[i] || src[i]->empty()) {
                cv_set_error_literal("mixChannels requires nonempty source matrices");
                return 0;
            }
            srcVec[i] = *src[i];
        }
        std::vector<cv::Mat> dstVec(ndsts);
        for (int i = 0; i < ndsts; i++) {
            if (!dst[i] || dst[i]->empty()) {
                cv_set_error_literal("mixChannels requires preallocated destinations");
                return 0;
            }
            dstVec[i] = *dst[i];
        }
        cv::mixChannels(srcVec, dstVec, fromTo, npairs);
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


CVAPI int cv_core_extractChannel(cv::Mat *src, cv::Mat **target, int coi) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::extractChannel(*src, *dst, coi);
        *target = dst.release();
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


CVAPI int cv_core_insertChannel(cv::Mat *src, cv::Mat **target, int coi) {
    cv_clear_error();
    if (!src || !target || !*target || (*target)->empty()) {
        cv_set_error_literal("insertChannel requires a preallocated destination");
        return 0;
    }

    try {
        cv::insertChannel(*src, **target, coi);
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


CVAPI int cv_core_flipND(cv::Mat *src, cv::Mat **target, int axis) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::flipND(*src, *dst, axis);
        *target = dst.release();
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


CVAPI int cv_core_transposeND(cv::Mat *src, cv::Mat **target, int *order, int orderSize) {
    cv_clear_error();

    try {
        std::vector<int> orderVec(order, order + orderSize);
        auto dst = std::make_unique<cv::Mat>();
        cv::transposeND(*src, orderVec, *dst);
        *target = dst.release();
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


CVAPI int cv_core_broadcast(cv::Mat *src, int *shape, int shapeSize, cv::Mat **target) {
    cv_clear_error();

    try {
        std::vector<int> shapeVec(shape, shape + shapeSize);
        auto dst = std::make_unique<cv::Mat>();
        cv::broadcast(*src, shapeVec, *dst);
        *target = dst.release();
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


CVAPI int cv_core_reduceArgMin(cv::Mat *src, cv::Mat **target, int axis, int lastIndex) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::reduceArgMin(*src, *dst, axis, lastIndex != 0);
        *target = dst.release();
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


CVAPI int cv_core_reduceArgMax(cv::Mat *src, cv::Mat **target, int axis, int lastIndex) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::reduceArgMax(*src, *dst, axis, lastIndex != 0);
        *target = dst.release();
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


CVAPI int cv_core_hasNonZero(cv::Mat *src) {
    cv_clear_error();

    try {
        return cv::hasNonZero(*src) ? 1 : 0;
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



CVAPI int cv_core_batchDistance(cv::Mat *src1, cv::Mat *src2, cv::Mat **dist, int dtype, cv::Mat **nidx, int normType, int K) {
    cv_clear_error();
    if (!src1 || !src2 || !dist || K < 0 || (K > 0 && !nidx) || dist == nidx) {
        cv_set_error_literal("Invalid or overlapping matrix arguments");
        return 0;
    }

    try {
        auto dstDist = std::make_unique<cv::Mat>();
        auto dstNidx = nidx ? std::make_unique<cv::Mat>() : nullptr;
        cv::batchDistance(*src1, *src2, *dstDist, dtype,
            K > 0 ? *dstNidx : cv::noArray(), normType, K);
        *dist = dstDist.release();
        if (nidx) *nidx = dstNidx.release();
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


CVAPI int cv_core_divSpectrums(cv::Mat *a, cv::Mat *b, cv::Mat **c, int flags, int conjB) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::divSpectrums(*a, *b, *dst, flags, conjB != 0);
        *c = dst.release();
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


CVAPI int cv_core_randn(cv::Mat **pmat, double mean, double stddev) {
    cv_clear_error();
    if (!pmat) {
        cv_set_error_literal("Missing matrix pointer");
        return 0;
    }

    try {
        auto empty = *pmat ? nullptr : std::make_unique<cv::Mat>();
        cv::Mat &working = *pmat ? **pmat : *empty;
        cv::randn(working, cv::Scalar::all(mean), cv::Scalar::all(stddev));
        if (empty) *pmat = empty.release();
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


CVAPI int cv_core_randu(cv::Mat **pmat, double low, double high) {
    cv_clear_error();
    if (!pmat) {
        cv_set_error_literal("Missing matrix pointer");
        return 0;
    }

    try {
        auto empty = *pmat ? nullptr : std::make_unique<cv::Mat>();
        cv::Mat &working = *pmat ? **pmat : *empty;
        cv::randu(working, cv::Scalar::all(low), cv::Scalar::all(high));
        if (empty) *pmat = empty.release();
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


CVAPI void cv_core_setRNGSeed(int seed) {
    cv_clear_error();
    try {
        cv::setRNGSeed(seed);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI int64_t cv_core_getTickCount() {
    cv_clear_error();
    try {
        return cv::getTickCount();
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


CVAPI double cv_core_getTickFrequency() {
    cv_clear_error();
    try {
        return cv::getTickFrequency();
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


CVAPI int cv_core_getNumThreads() {
    cv_clear_error();
    try {
        return cv::getNumThreads();
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


CVAPI void cv_core_setNumThreads(int nthreads) {
    cv_clear_error();
    try {
        cv::setNumThreads(nthreads);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI const char* cv_core_getBuildInformation() {
    cv_clear_error();
    try {
        return cv::getBuildInformation().c_str();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}


CVAPI const char* cv_core_getVersionString() {
    cv_clear_error();
    try {
        return CV_VERSION;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}


CVAPI int cv_core_solveLP(cv::Mat *Func, cv::Mat *Constr, cv::Mat **z) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (cv::solveLP(*Func, *Constr, *dst) < 0) {
            cv_set_error_literal("Linear program is infeasible or unbounded");
            return 0;
        }
        *z = dst.release();
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


CVAPI float cv_core_cubeRoot(float val) {
    cv_clear_error();
    try {
        return cv::cubeRoot(val);
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


CVAPI float cv_core_fastAtan2(float y, float x) {
    cv_clear_error();
    try {
        return cv::fastAtan2(y, x);
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


CVAPI int cv_core_copyToMasked(cv::Mat *src, cv::Mat **target, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        src->copyTo(*dst, *mask);
        *target = dst.release();
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



CVAPI void *cv_core_createFileStorage(const char *filename, int flags, const char *encoding) {
    cv_clear_error();

    try {
        std::string enc = encoding ? encoding : "";
        auto *fs = new cv::FileStorage(filename, flags, enc);
        return static_cast<void*>(fs);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}


CVAPI void cv_core_deleteFileStorage(void *fs) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        delete p;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI int cv_core_fileStorageOpen(void *fs, const char *filename, int flags, const char *encoding) {
    cv_clear_error();

    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        std::string enc = encoding ? encoding : "";
        return p->open(filename, flags, enc) ? 1 : 0;
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


CVAPI void cv_core_fileStorageRelease(void *fs) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        p->release();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI int cv_core_fileStorageIsOpened(void *fs) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        return p->isOpened() ? 1 : 0;
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


CVAPI void cv_core_fileStorageWriteInt(void *fs, const char *name, int value) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        *p << name << value;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_core_fileStorageWriteDouble(void *fs, const char *name, double value) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        *p << name << value;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_core_fileStorageWriteString(void *fs, const char *name, const char *value) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        *p << name << std::string(value);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_core_fileStorageWriteMat(void *fs, const char *name, cv::Mat *mat) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        *p << name << *mat;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI int cv_core_fileStorageReadInt(void *fs, const char *name, int defaultValue) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        return (int)(*p)[name].empty() ? defaultValue : (int)(*p)[name];
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


CVAPI double cv_core_fileStorageReadDouble(void *fs, const char *name, double defaultValue) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        return (*p)[name].empty() ? defaultValue : (double)(*p)[name];
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


CVAPI int cv_core_fileStorageReadString(void *fs, const char *name, const char *defaultValue, char *buf, int bufSize) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        std::string val;
        if ((*p)[name].empty())
            val = defaultValue ? defaultValue : "";
        else
            val = (std::string)(*p)[name];
        int len = (int)val.size();
        if (buf && bufSize > 0) {
            int copyLen = (len < bufSize - 1) ? len : bufSize - 1;
            memcpy(buf, val.c_str(), copyLen);
            buf[copyLen] = '\0';
        }
        return len;
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


CVAPI void cv_core_fileStorageReadMat(void *fs, const char *name, cv::Mat **pmat) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);


        std::unique_ptr<cv::Mat> dst(new cv::Mat());
        (*p)[name] >> *dst;
        *pmat = dst.release();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_core_fileStorageStartWriteStruct(void *fs, const char *name, int flags, const char *typeName) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        std::string tn = typeName ? typeName : "";
        p->startWriteStruct(name, flags, tn);
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI void cv_core_fileStorageEndWriteStruct(void *fs) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        p->endWriteStruct();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return;
    }
}


CVAPI int cv_core_fileStorageGetFormat(void *fs) {
    cv_clear_error();
    try {
        auto *p = static_cast<cv::FileStorage*>(fs);
        return p->getFormat();
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
