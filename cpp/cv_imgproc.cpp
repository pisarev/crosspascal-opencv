

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_imgproc.h"
#include "helper.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include <limits>
#include <utility>


CVAPI int cv_imgproc_convertColor(cv::Mat *src, cv::Mat **pDst, int code) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::cvtColor(*src, *dst, code);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_bilateralFilter(cv::Mat *src, cv::Mat **pDst, int d, double sigmaColor, double sigmaSpace, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::bilateralFilter(*src, *dst, d, sigmaColor, sigmaSpace, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_blur(cv::Mat *src, cv::Mat **pDst, CVSize kSize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::blur(*src, *dst, cv::Size(kSize.cx, kSize.cy), cv::Point(-1, -1), borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_gaussianBlur(cv::Mat *src, cv::Mat **pDst, CVSize kSize, double sigmaX, double sigmaY, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::GaussianBlur(*src, *dst, cv::Size(kSize.cx, kSize.cy), sigmaX, sigmaY, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_medianBlur(cv::Mat *src, cv::Mat **pDst, int kSize) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::medianBlur(*src, *dst, kSize);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_boxFilter(cv::Mat *src, cv::Mat **pDst, int ddepth, CVSize kSize, CVPoint anchor, int normalize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::boxFilter(*src, *dst, ddepth, cv::Size(kSize.cx, kSize.cy), cv::Point(anchor.x, anchor.y), normalize != 0, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_sqrBoxFilter(cv::Mat *src, cv::Mat **pDst, int ddepth, CVSize kSize, CVPoint anchor, int normalize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::sqrBoxFilter(*src, *dst, ddepth, cv::Size(kSize.cx, kSize.cy), cv::Point(anchor.x, anchor.y), normalize != 0, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_filter2D(cv::Mat *src, cv::Mat **pDst, int ddepth, cv::Mat *kernel, CVPoint anchor, double delta, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::filter2D(*src, *dst, ddepth, *kernel, cv::Point(anchor.x, anchor.y), delta, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_sepFilter2D(cv::Mat *src, cv::Mat **pDst, int ddepth, cv::Mat *kernelX, cv::Mat *kernelY, CVPoint anchor, double delta, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::sepFilter2D(*src, *dst, ddepth, *kernelX, *kernelY, cv::Point(anchor.x, anchor.y), delta, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_getGaborKernel(CVSize kSize, double sigma, double theta, double lambd, double gamma, double psi, int kType, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        *dst = cv::getGaborKernel(cv::Size(kSize.cx, kSize.cy), sigma, theta, lambd, gamma, psi, kType);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_sobel(cv::Mat *src, cv::Mat **pDst, int ddepth, int dx, int dy, int kSize, double scale, double delta, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::Sobel(*src, *dst, ddepth, dx, dy, kSize, scale, delta, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_scharr(cv::Mat *src, cv::Mat **pDst, int ddepth, int dx, int dy, double scale, double delta, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::Scharr(*src, *dst, ddepth, dx, dy, scale, delta, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_laplacian(cv::Mat *src, cv::Mat **pDst, int ddepth, int kSize, double scale, double delta, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::Laplacian(*src, *dst, ddepth, kSize, scale, delta, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_canny(cv::Mat *src, cv::Mat **pDst, double threshold1, double threshold2, int apertureSize, int L2gradient) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::Canny(*src, *dst, threshold1, threshold2, apertureSize, L2gradient != 0);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_erode(cv::Mat *src, cv::Mat **pDst, cv::Mat *kernel, int iterations, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::erode(*src, *dst, kernel ? *kernel : cv::Mat(), cv::Point(-1, -1), iterations, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_dilate(cv::Mat *src, cv::Mat **pDst, cv::Mat *kernel, int iterations, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::dilate(*src, *dst, kernel ? *kernel : cv::Mat(), cv::Point(-1, -1), iterations, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_morphologyEx(cv::Mat *src, cv::Mat **pDst, int op, cv::Mat *kernel, int iterations, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::morphologyEx(*src, *dst, op, kernel ? *kernel : cv::Mat(), cv::Point(-1, -1), iterations, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_createStructuringElement(int shape, CVSize kSize, CVPoint anchor, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        *dst = cv::getStructuringElement(shape, cv::Size(kSize.cx, kSize.cy), cv::Point(anchor.x, anchor.y));
        *pDst = dst.release();
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


CVAPI int cv_imgproc_threshold(cv::Mat *src, cv::Mat **pDst, double thresh, double maxval, int type) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::threshold(*src, *dst, thresh, maxval, type);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_adaptiveThreshold(cv::Mat *src, cv::Mat **pDst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::adaptiveThreshold(*src, *dst, maxValue, adaptiveMethod, thresholdType, blockSize, C);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_resizeImage(cv::Mat *src, cv::Mat **pDst, CVSize dSize, double fx, double fy, int interpolation) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::resize(*src, *dst, cv::Size(dSize.cx, dSize.cy), fx, fy, interpolation);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_rotateImage(cv::Mat *src, cv::Mat **pDst, int rotateCode) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::rotate(*src, *dst, rotateCode);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_deskew(cv::Mat *src, cv::Mat **pDst, double angle) {
    cv_clear_error();

    try {

        cv::Mat gray;
        if (src->channels() > 1)
            cv::cvtColor(*src, gray, cv::COLOR_BGR2GRAY);
        else
            gray = src->clone();


        cv::Mat edges;
        cv::Canny(gray, edges, 50, 150, 3);


        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 100, gray.cols / 4.0, 20);

        auto dst = std::make_unique<cv::Mat>();

        if (lines.empty()) {
            src->copyTo(*dst);
            *pDst = dst.release();
            return 1;
        }


        std::vector<double> angles;
        for (const auto &l : lines) {
            double dx = l[2] - l[0];
            double dy = l[3] - l[1];
            double a = atan2(dy, dx) * 180.0 / CV_PI;
            if (fabs(a) <= angle) {
                angles.push_back(a);
            }
        }

        if (angles.empty()) {
            src->copyTo(*dst);
            *pDst = dst.release();
            return 1;
        }

        std::sort(angles.begin(), angles.end());
        double medianAngle = angles[angles.size() / 2];


        cv::Point2f center(src->cols / 2.0f, src->rows / 2.0f);
        cv::Mat rot = cv::getRotationMatrix2D(center, medianAngle, 1.0);
        cv::warpAffine(*src, *dst, rot, src->size(), cv::INTER_LINEAR, cv::BORDER_REPLICATE);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_warpAffine(cv::Mat *src, cv::Mat **pDst, cv::Mat *M, CVSize dSize, int flags, int borderMode, CVScalar borderValue) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::warpAffine(*src, *dst, *M, cv::Size(dSize.cx, dSize.cy), flags, borderMode,
                        cv::Scalar(borderValue.v0, borderValue.v1, borderValue.v2, borderValue.v3));
        *pDst = dst.release();
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

CVAPI int cv_imgproc_warpPerspective(cv::Mat *src, cv::Mat **pDst, cv::Mat *M, CVSize dSize, int flags, int borderMode, CVScalar borderValue) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::warpPerspective(*src, *dst, *M, cv::Size(dSize.cx, dSize.cy), flags, borderMode,
                             cv::Scalar(borderValue.v0, borderValue.v1, borderValue.v2, borderValue.v3));
        *pDst = dst.release();
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

CVAPI int cv_imgproc_remap(cv::Mat *src, cv::Mat **pDst, cv::Mat *map1, cv::Mat *map2, int interpolation, int borderMode, CVScalar borderValue) {
    cv_clear_error();
    if (!src || !pDst || !map1) {
        cv_set_error_literal("Remap requires an image, a primary map and an output");
        return 0;
    }

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::remap(*src, *dst, *map1, map2 ? *map2 : cv::noArray(), interpolation, borderMode,
                   cv::Scalar(borderValue.v0, borderValue.v1, borderValue.v2, borderValue.v3));
        *pDst = dst.release();
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

CVAPI int cv_imgproc_getRotationMatrix2D(CVPoint2f center, double angle, double scale, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        *dst = cv::getRotationMatrix2D(cv::Point2f(center.x, center.y), angle, scale);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_getAffineTransform(CVPoint2f *src, CVPoint2f *dst, cv::Mat **pResult) {
    cv_clear_error();

    try {
        cv::Point2f srcPts[3] = {
            cv::Point2f(src[0].x, src[0].y),
            cv::Point2f(src[1].x, src[1].y),
            cv::Point2f(src[2].x, src[2].y)
        };
        cv::Point2f dstPts[3] = {
            cv::Point2f(dst[0].x, dst[0].y),
            cv::Point2f(dst[1].x, dst[1].y),
            cv::Point2f(dst[2].x, dst[2].y)
        };
        auto result = std::make_unique<cv::Mat>();
        *result = cv::getAffineTransform(srcPts, dstPts);
        *pResult = result.release();
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

CVAPI int cv_imgproc_getPerspectiveTransform(CVPoint2f *src, CVPoint2f *dst, cv::Mat **pResult) {
    cv_clear_error();

    try {
        cv::Point2f srcPts[4] = {
            cv::Point2f(src[0].x, src[0].y),
            cv::Point2f(src[1].x, src[1].y),
            cv::Point2f(src[2].x, src[2].y),
            cv::Point2f(src[3].x, src[3].y)
        };
        cv::Point2f dstPts[4] = {
            cv::Point2f(dst[0].x, dst[0].y),
            cv::Point2f(dst[1].x, dst[1].y),
            cv::Point2f(dst[2].x, dst[2].y),
            cv::Point2f(dst[3].x, dst[3].y)
        };
        auto result = std::make_unique<cv::Mat>();
        *result = cv::getPerspectiveTransform(srcPts, dstPts);
        *pResult = result.release();
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


CVAPI int cv_imgproc_houghLinesP(cv::Mat *src, double rho, double theta, int threshold, int minLineLength, int maxLineGap, GetData get, void *data) {
    cv_clear_error();

    try {
        std::vector<cv::Vec4i> linesVec;
        cv::HoughLinesP(*src, linesVec, rho, theta, threshold, minLineLength, maxLineGap);
        int n = (int)linesVec.size();
        if (n > 0 && get) {
            std::vector<CVLine> lines(n);
            for (int i = 0; i < n; i++) {
                lines[i].a.x = linesVec[i][0];
                lines[i].a.y = linesVec[i][1];
                lines[i].b.x = linesVec[i][2];
                lines[i].b.y = linesVec[i][3];
            }
            get(n, lines.data(), data);
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

CVAPI int cv_imgproc_houghLines(cv::Mat *src, double rho, double theta, int threshold, double srn, double stn, GetData get, void *data) {
    cv_clear_error();

    try {
        cv::Mat linesM;
        cv::HoughLines(*src, linesM, rho, theta, threshold, srn, stn);
        int n = linesM.rows;
        if (n > 0 && get) {
            get(n, linesM.data, data);
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

CVAPI int cv_imgproc_houghCircles(cv::Mat *src, int method, double dp, double minDist, double param1, double param2, int minRadius, int maxRadius, GetData get, void *data) {
    cv_clear_error();

    try {
        cv::Mat circlesM;
        cv::HoughCircles(*src, circlesM, method, dp, minDist, param1, param2, minRadius, maxRadius);
        int n = circlesM.cols;
        if (n > 0 && get) {
            get(n, circlesM.data, data);
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


CVAPI int cv_imgproc_denoise(cv::Mat *src, cv::Mat **pDst, double h, int templateWindowSize, int searchWindowSize) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::fastNlMeansDenoising(*src, *dst, (float)h, templateWindowSize, searchWindowSize);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_reverse(cv::Mat *src, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::bitwise_not(*src, *dst);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_adjustGamma(cv::Mat *src, cv::Mat **pDst, double gamma) {
    cv_clear_error();
    if (!std::isfinite(gamma) || gamma <= 0) {
        cv_set_error_literal("Gamma must be finite and greater than zero");
        return 0;
    }

    try {
        cv::Mat lut(1, 256, CV_8UC1);
        uchar *p = lut.ptr();
        double invGamma = 1.0 / gamma;
        for (int i = 0; i < 256; i++) {
            p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, invGamma) * 255.0);
        }
        auto dst = std::make_unique<cv::Mat>();
        cv::LUT(*src, lut, *dst);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_equalizeHist(cv::Mat *src, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::equalizeHist(*src, *dst);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_findContours(cv::Mat *src, int mode, int method, CVPoint offset, GetData get, void *data) {
    cv_clear_error();

    try {
        std::vector<std::vector<cv::Point>> contoursVec;
        cv::findContours(*src, contoursVec, mode, method, cv::Point(offset.x, offset.y));
        int n = (int)contoursVec.size();
        if (n > 0 && get) {
            for (int i = 0; i < n; i++) {


                get((int)contoursVec[i].size(), (void *)contoursVec[i].data(), data);
            }
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

CVAPI int cv_imgproc_findContoursHierarchy(cv::Mat *src, int mode, int method, CVPoint offset, GetDataParent get, void *data) {
    cv_clear_error();

    try {
        std::vector<std::vector<cv::Point>> contoursVec;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(*src, contoursVec, hierarchy, mode, method, cv::Point(offset.x, offset.y));
        int n = (int)contoursVec.size();
        if (n > 0 && get) {
            for (int i = 0; i < n; i++) {


                get((int)contoursVec[i].size(), (void *)contoursVec[i].data(), (int)hierarchy[i][3], data);
            }
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

CVAPI int cv_imgproc_drawContours(cv::Mat **pImage, cv::Mat *contours, int contourIdx, CVScalar color, int thickness, int lineType) {
    cv_clear_error();

    try {

        std::vector<std::vector<cv::Point>> contoursVec;

        int n = contours->rows;
        std::vector<cv::Point> pts(n);
        for (int j = 0; j < n; j++) {
            cv::Vec2i v = contours->at<cv::Vec2i>(j, 0);
            pts[j] = cv::Point(v[0], v[1]);
        }
        contoursVec.push_back(pts);
        cv::drawContours(**pImage, contoursVec, contourIdx,
                          cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType);
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

CVAPI int cv_imgproc_boundingRect(cv::Mat *contour, CVRect *result) {
    cv_clear_error();

    try {
        cv::Rect rect = cv::boundingRect(*contour);
        result->x = rect.x;
        result->y = rect.y;
        result->hSize = rect.width;
        result->vSize = rect.height;
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

CVAPI int cv_imgproc_contourArea(cv::Mat *contour, int oriented, double *area) {
    cv_clear_error();

    try {
        *area = cv::contourArea(*contour, oriented != 0);
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

CVAPI int cv_imgproc_arcLength(cv::Mat *curve, int closed, double *length) {
    cv_clear_error();

    try {
        *length = cv::arcLength(*curve, closed != 0);
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

CVAPI int cv_imgproc_convexHull(cv::Mat *src, cv::Mat **pDst, int clockwise) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::convexHull(*src, *dst, clockwise != 0);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_fitEllipse(cv::Mat *points, CVRotatedRect *result) {
    cv_clear_error();

    try {
        cv::RotatedRect rr = cv::fitEllipse(*points);
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

CVAPI int cv_imgproc_fitLine(cv::Mat *points, cv::Mat **pDst, int distType, double param, double reps, double aeps) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::fitLine(*points, *dst, distType, param, reps, aeps);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_matchShapes(cv::Mat *contour1, cv::Mat *contour2, int method, double parameter, double *result) {
    cv_clear_error();

    try {
        *result = cv::matchShapes(*contour1, *contour2, method, parameter);
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

CVAPI int cv_imgproc_moments(cv::Mat *src, int binaryImage, CVMoments *result) {
    cv_clear_error();

    try {
        cv::Moments m = cv::moments(*src, binaryImage != 0);
        result->m00 = m.m00;
        result->m10 = m.m10;
        result->m01 = m.m01;
        result->m20 = m.m20;
        result->m11 = m.m11;
        result->m02 = m.m02;
        result->m30 = m.m30;
        result->m21 = m.m21;
        result->m12 = m.m12;
        result->m03 = m.m03;
        result->mu20 = m.mu20;
        result->mu11 = m.mu11;
        result->mu02 = m.mu02;
        result->mu30 = m.mu30;
        result->mu21 = m.mu21;
        result->mu12 = m.mu12;
        result->mu03 = m.mu03;
        result->nu20 = m.nu20;
        result->nu11 = m.nu11;
        result->nu02 = m.nu02;
        result->nu30 = m.nu30;
        result->nu21 = m.nu21;
        result->nu12 = m.nu12;
        result->nu03 = m.nu03;
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


CVAPI int cv_imgproc_straightenCurve(cv::Mat *src, cv::Mat **pDst, SetData set, void *data,
                                     int thickness, int interpolation, int borderType, double borderValue) {
    cv_clear_error();
    if (!pDst) {
        cv_set_error_literal("Missing straightened image output");
        return 0;
    }

    try {
        if (!src || src->empty()) {
            cv_set_error_literal("Source image is null or empty");
            return 0;
        }
        if (!set) {
            cv_set_error_literal("SetData callback is null");
            return 0;
        }


        int count = 0;
        void *pointsPtr = set(0, data);
        if (!pointsPtr) {

            *pDst = new cv::Mat(src->clone());
            return 1;
        }


        count = *((int *)pointsPtr);
        if (count < 2) {
            cv_set_error_literal("Need at least 2 curve points for straightening");
            return 0;
        }
        CVPoint *pts = (CVPoint *)((int *)pointsPtr + 1);


        std::vector<cv::Point2f> curvePoints(count);
        for (int i = 0; i < count; i++) {
            curvePoints[i] = cv::Point2f((float)pts[i].x, (float)pts[i].y);
        }


        double totalLen = 0;
        std::vector<double> segLens(count - 1);
        for (int i = 0; i < count - 1; i++) {
            double dx = curvePoints[i + 1].x - curvePoints[i].x;
            double dy = curvePoints[i + 1].y - curvePoints[i].y;
            segLens[i] = std::sqrt(dx * dx + dy * dy);
            totalLen += segLens[i];
        }


        if (totalLen < 1 || totalLen > std::numeric_limits<int>::max()) {
            cv_set_error_literal("Curve length is outside the supported image width");
            return 0;
        }
        int stripHeight = (thickness > 0) ? thickness : std::max(10, (int)(totalLen / count * 2));
        int outWidth = (int)std::ceil(totalLen);
        int outHeight = stripHeight;

        bool transparentBlend = (borderType == cv::BORDER_TRANSPARENT);
        cv::Scalar borderScalar(borderValue, borderValue, borderValue, borderValue);
        auto dst = std::make_unique<cv::Mat>(outHeight, outWidth, src->type(), cv::Scalar(0));


        double accLen = 0;
        for (int i = 0; i < count - 1; i++) {
            cv::Point2f p0 = curvePoints[i];
            cv::Point2f p1 = curvePoints[i + 1];
            double segLen = segLens[i];
            if (segLen < 1.0) continue;


            double dx = (p1.x - p0.x) / segLen;
            double dy = (p1.y - p0.y) / segLen;
            double nx = -dy;
            double ny = dx;
            double halfH = stripHeight / 2.0;


            cv::Point2f srcPts[4] = {
                cv::Point2f((float)(p0.x + nx * halfH), (float)(p0.y + ny * halfH)),
                cv::Point2f((float)(p1.x + nx * halfH), (float)(p1.y + ny * halfH)),
                cv::Point2f((float)(p1.x - nx * halfH), (float)(p1.y - ny * halfH)),
                cv::Point2f((float)(p0.x - nx * halfH), (float)(p0.y - ny * halfH))
            };


            const double dstX0 = accLen;
            const double dstX1 = accLen + segLen;
            cv::Point2f dstPts[4] = {
                cv::Point2f(dstX0, 0),
                cv::Point2f(dstX1, 0),
                cv::Point2f(dstX1, (float)outHeight),
                cv::Point2f(dstX0, (float)outHeight)
            };


            cv::Mat M = cv::getPerspectiveTransform(srcPts, dstPts);
            cv::Mat warped;
            if (transparentBlend)
                warped = cv::Mat::zeros(dst->size(), src->type());
            int warpBorder = transparentBlend ? cv::BORDER_TRANSPARENT : borderType;
            cv::warpPerspective(*src, warped, M, dst->size(), interpolation, warpBorder, borderScalar);
            if (!transparentBlend) {
                int sX = std::max(0, (int)dstX0);
                int eX = static_cast<int>(std::min(std::ceil(dstX1), static_cast<double>(outWidth)));
                if (eX > sX)
                    warped(cv::Rect(sX, 0, eX - sX, outHeight)).copyTo((*dst)(cv::Rect(sX, 0, eX - sX, outHeight)));
                accLen += segLen;
                continue;
            }


            int startX = (int)dstX0;
            int endX = static_cast<int>(std::min(std::ceil(dstX1), static_cast<double>(outWidth)));
            for (int row = 0; row < outHeight; row++) {
                for (int col = startX; col < endX; col++) {
                    if (src->channels() == 1) {
                        uint8_t val = warped.at<uint8_t>(row, col);
                        if (val != 0) dst->at<uint8_t>(row, col) = val;
                    } else if (src->channels() == 3) {
                        cv::Vec3b val = warped.at<cv::Vec3b>(row, col);
                        if (val != cv::Vec3b(0, 0, 0)) dst->at<cv::Vec3b>(row, col) = val;
                    }
                }
            }
            accLen += segLen;
        }

        *pDst = dst.release();
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

CVAPI int cv_imgproc_approximateCurve(cv::Mat *curve, cv::Mat **pDst, double epsilon, int closed) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::approxPolyDP(*curve, *dst, epsilon, closed != 0);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_watershed(cv::Mat *image, cv::Mat **pMarkers) {
    cv_clear_error();

    try {
        cv::watershed(*image, **pMarkers);
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

CVAPI int cv_imgproc_grabCut(cv::Mat *img, cv::Mat **pMask, CVRect rect, cv::Mat **pBgdModel, cv::Mat **pFgdModel, int iterCount, int mode) {
    cv_clear_error();

    try {
        cv::Rect r(rect.x, rect.y, rect.hSize, rect.vSize);
        cv::grabCut(*img, **pMask, r, **pBgdModel, **pFgdModel, iterCount, mode);
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

CVAPI int cv_imgproc_connectedComponents(cv::Mat *image, cv::Mat **pLabels, int connectivity, int ltype) {
    cv_clear_error();

    try {
        auto labels = std::make_unique<cv::Mat>();
        cv::connectedComponents(*image, *labels, connectivity, ltype);
        *pLabels = labels.release();
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

CVAPI int cv_imgproc_connectedComponentsWithStats(cv::Mat *image, cv::Mat **pLabels, cv::Mat **pStats, cv::Mat **pCentroids, int connectivity, int ltype) {
    cv_clear_error();
    if (!pLabels || !pStats || !pCentroids || pLabels == pStats || pLabels == pCentroids || pStats == pCentroids) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto labels = std::make_unique<cv::Mat>();
        auto stats = std::make_unique<cv::Mat>();
        auto centroids = std::make_unique<cv::Mat>();
        cv::connectedComponentsWithStats(*image, *labels, *stats, *centroids, connectivity, ltype);
        *pLabels = labels.release();
        *pStats = stats.release();
        *pCentroids = centroids.release();
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


CVAPI int cv_imgproc_pyrUp(cv::Mat *src, cv::Mat **pDst, CVSize dSize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::pyrUp(*src, *dst, cv::Size(dSize.cx, dSize.cy), borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_pyrDown(cv::Mat *src, cv::Mat **pDst, CVSize dSize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::pyrDown(*src, *dst, cv::Size(dSize.cx, dSize.cy), borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_pyrMeanShiftFiltering(cv::Mat *src, cv::Mat **pDst, double sp, double sr, int maxLevel) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::pyrMeanShiftFiltering(*src, *dst, sp, sr, maxLevel);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_distanceTransform(cv::Mat *src, cv::Mat **pDst, int distanceType, int maskSize) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::distanceTransform(*src, *dst, distanceType, maskSize);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_floodFill(cv::Mat **pImage, cv::Mat **pMask, CVPoint seedPoint, CVScalar newVal, CVScalar loDiff, CVScalar upDiff, int flags) {
    cv_clear_error();

    try {
        if (pMask && *pMask && !(*pMask)->empty()) {
            cv::floodFill(**pImage, **pMask, cv::Point(seedPoint.x, seedPoint.y),
                           cv::Scalar(newVal.v0, newVal.v1, newVal.v2, newVal.v3),
                           nullptr,
                           cv::Scalar(loDiff.v0, loDiff.v1, loDiff.v2, loDiff.v3),
                           cv::Scalar(upDiff.v0, upDiff.v1, upDiff.v2, upDiff.v3),
                           flags);
        } else {
            cv::floodFill(**pImage, cv::Point(seedPoint.x, seedPoint.y),
                           cv::Scalar(newVal.v0, newVal.v1, newVal.v2, newVal.v3),
                           nullptr,
                           cv::Scalar(loDiff.v0, loDiff.v1, loDiff.v2, loDiff.v3),
                           cv::Scalar(upDiff.v0, upDiff.v1, upDiff.v2, upDiff.v3),
                           flags);
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

CVAPI int cv_imgproc_integral(cv::Mat *src, cv::Mat **pSum, cv::Mat **pSqSum, cv::Mat **pTilted, int sDepth, int sqDepth) {
    cv_clear_error();
    if (!pSum || !pSqSum || !pTilted || pSum == pSqSum || pSum == pTilted || pSqSum == pTilted) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto sum = std::make_unique<cv::Mat>();
        auto sqsum = std::make_unique<cv::Mat>();
        auto tilted = std::make_unique<cv::Mat>();
        cv::integral(*src, *sum, *sqsum, *tilted, sDepth, sqDepth);
        *pSum = sum.release();
        *pSqSum = sqsum.release();
        *pTilted = tilted.release();
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


CVAPI int cv_imgproc_calcHist(cv::Mat *image, int channel, cv::Mat *mask, cv::Mat **pHist, int histSize, float rangeMin, float rangeMax, int accumulate) {
    cv_clear_error();
    if (!image || !pHist) {
        cv_set_error_literal("Histogram requires an image and an output");
        return 0;
    }

    try {
        int channels[] = { channel };
        int histSizes[] = { histSize };
        float range[] = { rangeMin, rangeMax };
        const float *ranges[] = { range };
        const bool useExisting = accumulate && *pHist;
        auto hist = std::make_unique<cv::Mat>(useExisting ? (*pHist)->clone() : cv::Mat());
        cv::Mat maskMat = (mask && !mask->empty()) ? *mask : cv::Mat();
        cv::calcHist(image, 1, channels, maskMat, *hist, 1, histSizes, ranges, true, useExisting);
        if (useExisting)
            **pHist = std::move(*hist);
        else
            *pHist = hist.release();
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

CVAPI int cv_imgproc_compareHist(cv::Mat *H1, cv::Mat *H2, int method, double *result) {
    cv_clear_error();

    try {
        *result = cv::compareHist(*H1, *H2, method);
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

CVAPI int cv_imgproc_calcBackProject(cv::Mat *image, int channel, cv::Mat *hist, cv::Mat **pDst, float rangeMin, float rangeMax, double scale) {
    cv_clear_error();

    try {
        int channels[] = { channel };
        float range[] = { rangeMin, rangeMax };
        const float *ranges[] = { range };
        auto dst = std::make_unique<cv::Mat>();
        cv::calcBackProject(image, 1, channels, *hist, *dst, ranges, scale);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_drawLine(cv::Mat **pImg, CVPoint pt1, CVPoint pt2, CVScalar color, int thickness, int lineType) {
    cv_clear_error();

    try {
        cv::line(**pImg, cv::Point(pt1.x, pt1.y), cv::Point(pt2.x, pt2.y),
                  cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType);
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

CVAPI int cv_imgproc_drawRectangle(cv::Mat **pImg, CVRect rect, CVScalar color, int thickness, int lineType) {
    cv_clear_error();

    try {
        cv::rectangle(**pImg, cv::Rect(rect.x, rect.y, rect.hSize, rect.vSize),
                       cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType);
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

CVAPI int cv_imgproc_drawCircle(cv::Mat **pImg, CVPoint center, int radius, CVScalar color, int thickness, int lineType) {
    cv_clear_error();

    try {
        cv::circle(**pImg, cv::Point(center.x, center.y), radius,
                    cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType);
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

CVAPI int cv_imgproc_drawEllipse(cv::Mat **pImg, CVPoint center, CVSize axes, double angle, double startAngle, double endAngle, CVScalar color, int thickness, int lineType) {
    cv_clear_error();

    try {
        cv::ellipse(**pImg, cv::Point(center.x, center.y), cv::Size(axes.cx, axes.cy),
                     angle, startAngle, endAngle,
                     cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType);
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

CVAPI int cv_imgproc_drawPolylines(cv::Mat **pImg, CVPoint *pts, int *npts, int nCurves, int isClosed, CVScalar color, int thickness, int lineType) {
    cv_clear_error();

    try {
        std::vector<std::vector<cv::Point>> allPts(nCurves);
        int offset = 0;
        for (int c = 0; c < nCurves; c++) {
            allPts[c].resize(npts[c]);
            for (int i = 0; i < npts[c]; i++) {
                allPts[c][i] = cv::Point(pts[offset + i].x, pts[offset + i].y);
            }
            offset += npts[c];
        }
        std::vector<const cv::Point*> pptrs(nCurves);
        for (int c = 0; c < nCurves; c++) {
            pptrs[c] = allPts[c].data();
        }
        cv::polylines(**pImg, pptrs.data(), npts, nCurves, isClosed != 0,
                       cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType);
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

CVAPI int cv_imgproc_drawPolylinesShift(cv::Mat **pImg, CVPoint *pts, int *npts, int nCurves, int isClosed, CVScalar color, int thickness, int lineType, int shift) {
    cv_clear_error();

    try {
        std::vector<std::vector<cv::Point>> allPts(nCurves);
        int offset = 0;
        for (int c = 0; c < nCurves; c++) {
            allPts[c].resize(npts[c]);
            for (int i = 0; i < npts[c]; i++) {
                allPts[c][i] = cv::Point(pts[offset + i].x, pts[offset + i].y);
            }
            offset += npts[c];
        }
        std::vector<const cv::Point*> pptrs(nCurves);
        for (int c = 0; c < nCurves; c++) {
            pptrs[c] = allPts[c].data();
        }
        cv::polylines(**pImg, pptrs.data(), npts, nCurves, isClosed != 0,
                       cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType, shift);
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

CVAPI int cv_imgproc_fillPoly(cv::Mat **pImg, CVPoint *pts, int *npts, int nCurves, CVScalar color, int lineType) {
    cv_clear_error();

    try {
        std::vector<std::vector<cv::Point>> allPts(nCurves);
        int offset = 0;
        for (int c = 0; c < nCurves; c++) {
            allPts[c].resize(npts[c]);
            for (int i = 0; i < npts[c]; i++) {
                allPts[c][i] = cv::Point(pts[offset + i].x, pts[offset + i].y);
            }
            offset += npts[c];
        }
        std::vector<const cv::Point*> pptrs(nCurves);
        for (int c = 0; c < nCurves; c++) {
            pptrs[c] = allPts[c].data();
        }
        cv::fillPoly(**pImg, pptrs.data(), npts, nCurves,
                      cv::Scalar(color.v0, color.v1, color.v2, color.v3), lineType);
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

CVAPI int cv_imgproc_putText(cv::Mat **pImg, const char *text, CVPoint org, int fontFace, double fontScale, CVScalar color, int thickness, int lineType, int bottomLeftOrigin) {
    cv_clear_error();

    try {
        cv::putText(**pImg, text, cv::Point(org.x, org.y), fontFace, fontScale,
                     cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType, bottomLeftOrigin != 0);
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

CVAPI int cv_imgproc_getTextSize(const char *text, int fontFace, double fontScale, int thickness, int *baseLine, CVSize *result) {
    cv_clear_error();

    try {
        cv::Size sz = cv::getTextSize(text, fontFace, fontScale, thickness, baseLine);
        result->cx = sz.width;
        result->cy = sz.height;
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

CVAPI int cv_imgproc_arrowedLine(cv::Mat **pImg, CVPoint pt1, CVPoint pt2, CVScalar color, int thickness, int lineType, double tipLength) {
    cv_clear_error();

    try {
        cv::arrowedLine(**pImg, cv::Point(pt1.x, pt1.y), cv::Point(pt2.x, pt2.y),
                         cv::Scalar(color.v0, color.v1, color.v2, color.v3), thickness, lineType, 0, tipLength);
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

CVAPI int cv_imgproc_drawMarker(cv::Mat **pImg, CVPoint position, CVScalar color, int markerType, int markerSize, int thickness, int lineType) {
    cv_clear_error();

    try {
        cv::drawMarker(**pImg, cv::Point(position.x, position.y),
                        cv::Scalar(color.v0, color.v1, color.v2, color.v3), markerType, markerSize, thickness, lineType);
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


CVAPI int cv_imgproc_cornerHarris(cv::Mat *src, cv::Mat **pDst, int blockSize, int ksize, double k, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::cornerHarris(*src, *dst, blockSize, ksize, k, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_cornerMinEigenVal(cv::Mat *src, cv::Mat **pDst, int blockSize, int ksize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::cornerMinEigenVal(*src, *dst, blockSize, ksize, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_preCornerDetect(cv::Mat *src, cv::Mat **pDst, int ksize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::preCornerDetect(*src, *dst, ksize, borderType);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_cornerSubPix(cv::Mat *image, cv::Mat **pCorners, CVSize winSize, CVSize zeroZone, int maxCount, double epsilon) {
    cv_clear_error();

    try {
        cv::cornerSubPix(*image, **pCorners, cv::Size(winSize.cx, winSize.cy),
                          cv::Size(zeroZone.cx, zeroZone.cy),
                          cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, maxCount, epsilon));
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


CVAPI int cv_imgproc_matchTemplate(cv::Mat *image, cv::Mat *templ, cv::Mat **pResult, int method, cv::Mat *mask) {
    cv_clear_error();

    try {
        auto result = std::make_unique<cv::Mat>();
        if (mask && !mask->empty())
            cv::matchTemplate(*image, *templ, *result, method, *mask);
        else
            cv::matchTemplate(*image, *templ, *result, method);
        *pResult = result.release();
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

CVAPI int cv_imgproc_phaseCorrelate(cv::Mat *src1, cv::Mat *src2, cv::Mat *window, double *response, CVPoint2f *shift) {
    cv_clear_error();

    try {
        cv::Point2d result;
        if (window && !window->empty()) {
            result = cv::phaseCorrelate(*src1, *src2, *window, response);
        } else {
            result = cv::phaseCorrelate(*src1, *src2, cv::noArray(), response);
        }
        shift->x = (float)result.x;
        shift->y = (float)result.y;
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


CVAPI int cv_imgproc_cvtColorTwoPlane(cv::Mat *src1, cv::Mat *src2, cv::Mat **pDst, int code) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::cvtColorTwoPlane(*src1, *src2, *dst, code);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_logPolar(cv::Mat *src, cv::Mat **pDst, CVPoint2f center, double M, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::logPolar(*src, *dst, cv::Point2f(center.x, center.y), M, flags);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_linearPolar(cv::Mat *src, cv::Mat **pDst, CVPoint2f center, double maxRadius, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::linearPolar(*src, *dst, cv::Point2f(center.x, center.y), maxRadius, flags);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_warpPolar(cv::Mat *src, cv::Mat **pDst, int dstW, int dstH, CVPoint2f center, double maxRadius, int flags) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::warpPolar(*src, *dst, cv::Size(dstW, dstH), cv::Point2f(center.x, center.y), maxRadius, flags);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_accumulate(cv::Mat *src, cv::Mat **pDst, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty())
            cv::accumulate(*src, **pDst, *mask);
        else
            cv::accumulate(*src, **pDst);
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

CVAPI int cv_imgproc_accumulateSquare(cv::Mat *src, cv::Mat **pDst, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty())
            cv::accumulateSquare(*src, **pDst, *mask);
        else
            cv::accumulateSquare(*src, **pDst);
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

CVAPI int cv_imgproc_accumulateProduct(cv::Mat *src1, cv::Mat *src2, cv::Mat **pDst, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty())
            cv::accumulateProduct(*src1, *src2, **pDst, *mask);
        else
            cv::accumulateProduct(*src1, *src2, **pDst);
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

CVAPI int cv_imgproc_accumulateWeighted(cv::Mat *src, cv::Mat **pDst, double alpha, cv::Mat *mask) {
    cv_clear_error();

    try {
        if (mask && !mask->empty())
            cv::accumulateWeighted(*src, **pDst, alpha, *mask);
        else
            cv::accumulateWeighted(*src, **pDst, alpha);
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

CVAPI int cv_imgproc_createHanningWindow(cv::Mat **pDst, int winW, int winH, int type) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::createHanningWindow(*dst, cv::Size(winW, winH), type);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_minEnclosingCircle(cv::Mat *points, CVPoint2f *center, float *radius) {
    cv_clear_error();

    try {
        cv::Point2f c;
        float r;
        cv::minEnclosingCircle(*points, c, r);
        center->x = c.x;
        center->y = c.y;
        *radius = r;
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

CVAPI int cv_imgproc_minEnclosingTriangle(cv::Mat *points, cv::Mat **pTriangle) {
    cv_clear_error();

    try {
        auto triangle = std::make_unique<cv::Mat>();
        cv::minEnclosingTriangle(*points, *triangle);
        *pTriangle = triangle.release();
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

CVAPI double cv_imgproc_pointPolygonTest(cv::Mat *contour, CVPoint2f pt, int measureDist) {
    cv_clear_error();

    try {
        return cv::pointPolygonTest(*contour, cv::Point2f(pt.x, pt.y), measureDist != 0);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}

CVAPI int cv_imgproc_isContourConvex(cv::Mat *contour) {
    cv_clear_error();

    try {
        return cv::isContourConvex(*contour) ? 1 : 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_imgproc_approxPolyDP(cv::Mat *curve, cv::Mat **pApproxCurve, double epsilon, int closed) {
    cv_clear_error();

    try {
        auto approxCurve = std::make_unique<cv::Mat>();
        cv::approxPolyDP(*curve, *approxCurve, epsilon, closed != 0);
        *pApproxCurve = approxCurve.release();
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

CVAPI int cv_imgproc_HuMoments(CVMoments *moments, double *hu) {
    cv_clear_error();

    try {
        cv::Moments m;
        m.m00 = moments->m00; m.m10 = moments->m10; m.m01 = moments->m01;
        m.m20 = moments->m20; m.m11 = moments->m11; m.m02 = moments->m02;
        m.m30 = moments->m30; m.m21 = moments->m21; m.m12 = moments->m12; m.m03 = moments->m03;
        m.mu20 = moments->mu20; m.mu11 = moments->mu11; m.mu02 = moments->mu02;
        m.mu30 = moments->mu30; m.mu21 = moments->mu21; m.mu12 = moments->mu12; m.mu03 = moments->mu03;
        m.nu20 = moments->nu20; m.nu11 = moments->nu11; m.nu02 = moments->nu02;
        m.nu30 = moments->nu30; m.nu21 = moments->nu21; m.nu12 = moments->nu12; m.nu03 = moments->nu03;
        cv::HuMoments(m, hu);
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


CVAPI int cv_imgproc_buildPyramid(cv::Mat *src, cv::Mat **pDst, int *count, int maxlevel, int borderType) {
    cv_clear_error();
    if (!src || !pDst || !count || maxlevel < 0) {
        cv_set_error_literal("Missing pyramid input or outputs, or invalid level count");
        return 0;
    }

    try {
        std::vector<cv::Mat> pyramid;
        cv::buildPyramid(*src, pyramid, maxlevel, borderType);
        std::vector<std::unique_ptr<cv::Mat>> results;
        results.reserve(pyramid.size());
        for (const auto &level : pyramid)
            results.push_back(std::make_unique<cv::Mat>(level.clone()));
        for (size_t i = 0; i < results.size(); ++i)
            pDst[i] = results[i].release();
        *count = static_cast<int>(results.size());
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


CVAPI int cv_imgproc_invertAffineTransform(cv::Mat *M, cv::Mat **pIM) {
    cv_clear_error();

    try {
        auto iM = std::make_unique<cv::Mat>();
        cv::invertAffineTransform(*M, *iM);
        *pIM = iM.release();
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

CVAPI int cv_imgproc_clipLine(int imgW, int imgH, CVPoint *pt1, CVPoint *pt2) {
    cv_clear_error();

    try {
        cv::Point p1(pt1->x, pt1->y);
        cv::Point p2(pt2->x, pt2->y);
        bool result = cv::clipLine(cv::Size(imgW, imgH), p1, p2);
        pt1->x = p1.x; pt1->y = p1.y;
        pt2->x = p2.x; pt2->y = p2.y;
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

CVAPI int cv_imgproc_ellipse2Poly(CVPoint center, CVSize axes, int angle, int arcStart, int arcEnd, int delta, CVPoint *pts, int *count, int maxCount) {
    cv_clear_error();

    try {
        std::vector<cv::Point> points;
        cv::ellipse2Poly(cv::Point(center.x, center.y), cv::Size(axes.cx, axes.cy),
                          angle, arcStart, arcEnd, delta, points);
        int n = std::min((int)points.size(), maxCount);
        for (int i = 0; i < n; i++) {
            pts[i].x = points[i].x;
            pts[i].y = points[i].y;
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


CVAPI int cv_imgproc_getGaussianKernel(int ksize, double sigma, int ktype, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        *dst = cv::getGaussianKernel(ksize, sigma, ktype);
        *pDst = dst.release();
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

CVAPI int cv_imgproc_convertMaps(cv::Mat *map1, cv::Mat *map2, cv::Mat **pDstmap1, cv::Mat **pDstmap2, int dstmap1type, int nninterpolation) {
    cv_clear_error();
    if (!map1 || !pDstmap1 || !pDstmap2 || pDstmap1 == pDstmap2) {
        cv_set_error_literal("Invalid map inputs or output slots");
        return 0;
    }

    try {
        auto dstmap1 = std::make_unique<cv::Mat>();
        auto dstmap2 = std::make_unique<cv::Mat>();
        cv::convertMaps(*map1, map2 ? *map2 : cv::noArray(), *dstmap1, *dstmap2, dstmap1type, nninterpolation != 0);
        *pDstmap1 = dstmap1.release();
        *pDstmap2 = dstmap2.release();
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


CVAPI void *cv_imgproc_createLineSegmentDetector(int refine, double scale, double sigma_scale, double quant, double ang_th, double log_eps, double density_th, int n_bins) {
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::LineSegmentDetector>(
            cv::createLineSegmentDetector(refine, scale, sigma_scale, quant, ang_th, log_eps, density_th, n_bins));
        return ptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_imgproc_deleteLineSegmentDetector(void *lsd) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Ptr<cv::LineSegmentDetector>*>(lsd);
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

CVAPI int cv_imgproc_lsdDetect(void *lsd, cv::Mat *image, cv::Mat **pLines) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Ptr<cv::LineSegmentDetector>*>(lsd);
        auto lines = std::make_unique<cv::Mat>();
        (*ptr)->detect(*image, *lines);
        *pLines = lines.release();
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


CVAPI int cv_imgproc_goodFeaturesToTrack(cv::Mat *image, cv::Mat **pCorners, int maxCorners, double qualityLevel, double minDistance, cv::Mat *mask, int blockSize, int useHarrisDetector, double k) {
    cv_clear_error();

    try {
        auto corners = std::make_unique<cv::Mat>();
        if (mask && !mask->empty())
            cv::goodFeaturesToTrack(*image, *corners, maxCorners, qualityLevel, minDistance, *mask, blockSize, useHarrisDetector != 0, k);
        else
            cv::goodFeaturesToTrack(*image, *corners, maxCorners, qualityLevel, minDistance, cv::noArray(), blockSize, useHarrisDetector != 0, k);
        *pCorners = corners.release();
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


CVAPI int cv_imgproc_stackBlur(cv::Mat *src, cv::Mat **pDst, int kW, int kH) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::stackBlur(*src, *dst, cv::Size(kW, kH));
        *pDst = dst.release();
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


CVAPI int cv_imgproc_spatialGradient(cv::Mat *src, cv::Mat **pDx, cv::Mat **pDy, int ksize, int borderType) {
    cv_clear_error();
    if (!pDx || !pDy || pDx == pDy) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto dx = std::make_unique<cv::Mat>();
        auto dy = std::make_unique<cv::Mat>();
        cv::spatialGradient(*src, *dx, *dy, ksize, borderType);
        *pDx = dx.release();
        *pDy = dy.release();
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


CVAPI int cv_imgproc_cornerEigenValsAndVecs(cv::Mat *src, cv::Mat **pDst, int blockSize, int apertureSize, int borderType) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::cornerEigenValsAndVecs(*src, *dst, blockSize, apertureSize, borderType);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_getDerivKernels(cv::Mat **pKx, cv::Mat **pKy, int dx, int dy, int ksize, int normalize, int ktype) {
    cv_clear_error();
    if (!pKx || !pKy || pKx == pKy) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto kx = std::make_unique<cv::Mat>();
        auto ky = std::make_unique<cv::Mat>();
        cv::getDerivKernels(*kx, *ky, dx, dy, ksize, normalize != 0, ktype);
        *pKx = kx.release();
        *pKy = ky.release();
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


CVAPI int cv_imgproc_getRectSubPix(cv::Mat *image, int patchW, int patchH, CVPoint2f center, cv::Mat **pPatch, int patchType) {
    cv_clear_error();

    try {
        auto patch = std::make_unique<cv::Mat>();
        cv::getRectSubPix(*image, cv::Size(patchW, patchH), cv::Point2f(center.x, center.y), *patch, patchType);
        *pPatch = patch.release();
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


CVAPI int cv_imgproc_fillConvexPoly(cv::Mat **pImg, CVPoint *pts, int npts, CVScalar color, int lineType, int shift) {
    cv_clear_error();

    try {
        std::vector<cv::Point> points(npts);
        for (int i = 0; i < npts; i++) {
            points[i] = cv::Point(pts[i].x, pts[i].y);
        }
        cv::fillConvexPoly(**pImg, points,
                            cv::Scalar(color.v0, color.v1, color.v2, color.v3), lineType, shift);
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


CVAPI int cv_imgproc_convexityDefects(cv::Mat *contour, cv::Mat *convexhull, cv::Mat **pConvexityDefects) {
    cv_clear_error();

    try {
        auto defects = std::make_unique<cv::Mat>();
        cv::convexityDefects(*contour, *convexhull, *defects);
        *pConvexityDefects = defects.release();
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

CVAPI int cv_imgproc_intersectConvexConvex(cv::Mat *p1, cv::Mat *p2, cv::Mat **pP12, int handleNested) {
    cv_clear_error();

    try {
        auto p12 = std::make_unique<cv::Mat>();
        cv::intersectConvexConvex(*p1, *p2, *p12, handleNested != 0);
        *pP12 = p12.release();
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

CVAPI int cv_imgproc_rotatedRectangleIntersection(CVRotatedRect *rect1, CVRotatedRect *rect2, cv::Mat **pIntersectingRegion) {
    cv_clear_error();

    try {
        cv::RotatedRect rr1(
            cv::Point2f(rect1->center.x, rect1->center.y),
            cv::Size2f(rect1->size.x, rect1->size.y),
            rect1->angle);
        cv::RotatedRect rr2(
            cv::Point2f(rect2->center.x, rect2->center.y),
            cv::Size2f(rect2->size.x, rect2->size.y),
            rect2->angle);
        auto region = std::make_unique<cv::Mat>();
        cv::rotatedRectangleIntersection(rr1, rr2, *region);
        *pIntersectingRegion = region.release();
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


CVAPI int cv_imgproc_applyColorMap(cv::Mat *src, cv::Mat **pDst, int colormap) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::applyColorMap(*src, *dst, colormap);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_demosaicing(cv::Mat *src, cv::Mat **pDst, int code, int dstCn) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::demosaicing(*src, *dst, code, dstCn);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_integral2(cv::Mat *src, cv::Mat **pSum, cv::Mat **pSqSum, int sdepth, int sqdepth) {
    cv_clear_error();
    if (!pSum || !pSqSum || pSum == pSqSum) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto sum = std::make_unique<cv::Mat>();
        auto sqsum = std::make_unique<cv::Mat>();
        cv::integral(*src, *sum, *sqsum, sdepth, sqdepth);
        *pSum = sum.release();
        *pSqSum = sqsum.release();
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

CVAPI int cv_imgproc_integral3(cv::Mat *src, cv::Mat **pSum, cv::Mat **pSqSum, cv::Mat **pTilted, int sdepth, int sqdepth) {
    cv_clear_error();
    if (!pSum || !pSqSum || !pTilted || pSum == pSqSum || pSum == pTilted || pSqSum == pTilted) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto sum = std::make_unique<cv::Mat>();
        auto sqsum = std::make_unique<cv::Mat>();
        auto tilted = std::make_unique<cv::Mat>();
        cv::integral(*src, *sum, *sqsum, *tilted, sdepth, sqdepth);
        *pSum = sum.release();
        *pSqSum = sqsum.release();
        *pTilted = tilted.release();
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


CVAPI double cv_imgproc_getFontScaleFromHeight(int fontFace, int pixelHeight, int thickness) {
    cv_clear_error();

    try {
        return cv::getFontScaleFromHeight(fontFace, pixelHeight, thickness);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}


CVAPI void *cv_imgproc_createGeneralizedHoughBallard() {
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::GeneralizedHough>(cv::createGeneralizedHoughBallard());
        return ptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI void *cv_imgproc_createGeneralizedHoughGuil() {
    cv_clear_error();

    try {
        auto ptr = new cv::Ptr<cv::GeneralizedHough>(cv::createGeneralizedHoughGuil());
        return ptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_imgproc_deleteGeneralizedHough(void *hough) {
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::GeneralizedHough> *>(hough);
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


CVAPI int cv_imgproc_blendLinear(cv::Mat *src1, cv::Mat *src2, cv::Mat *weights1, cv::Mat *weights2, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::blendLinear(*src1, *src2, *weights1, *weights2, *dst);
        *pDst = dst.release();
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


CVAPI int cv_imgproc_findContoursLinkRuns(cv::Mat *image, cv::Mat **pContours, int *contourCount) {
    cv_clear_error();
    if (!image || !contourCount || (pContours && *contourCount < 0)) {
        cv_set_error_literal("Invalid image or contour output capacity");
        return 0;
    }

    try {
        std::vector<std::vector<cv::Point>> contoursVec;
        cv::findContoursLinkRuns(*image, contoursVec);
        if (contoursVec.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
            cv_set_error_literal("Contour count exceeds the API limit");
            return 0;
        }
        const int required = static_cast<int>(contoursVec.size());
        if (pContours && *contourCount < required) {
            *contourCount = required;
            cv_set_error_literal("Contour output capacity is too small");
            return 0;
        }
        if (pContours) {
            std::vector<std::unique_ptr<cv::Mat>> results;
            results.reserve(contoursVec.size());
            for (const auto &contour : contoursVec)
                results.push_back(std::make_unique<cv::Mat>(contour, true));
            for (size_t i = 0; i < results.size(); ++i)
                pContours[i] = results[i].release();
        }
        *contourCount = required;
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


CVAPI int cv_imgproc_fitEllipseAMS(cv::Mat *points, CVRotatedRect *result) {
    cv_clear_error();

    try {
        cv::RotatedRect rr = cv::fitEllipseAMS(*points);
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

CVAPI int cv_imgproc_fitEllipseDirect(cv::Mat *points, CVRotatedRect *result) {
    cv_clear_error();

    try {
        cv::RotatedRect rr = cv::fitEllipseDirect(*points);
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


CVAPI int cv_imgproc_goodFeaturesToTrackWithQuality(cv::Mat *image, cv::Mat **pCorners, int maxCorners, double qualityLevel, double minDistance, cv::Mat *mask, cv::Mat **pCornersQuality, int blockSize, int gradientSize, int useHarrisDetector, double k) {
    cv_clear_error();
    if (!pCorners || !pCornersQuality || pCorners == pCornersQuality) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return 0;
    }

    try {
        auto corners = std::make_unique<cv::Mat>();
        auto cornersQuality = std::make_unique<cv::Mat>();
        if (mask && !mask->empty())
            cv::goodFeaturesToTrack(*image, *corners, maxCorners, qualityLevel, minDistance, *mask, *cornersQuality, blockSize, gradientSize, useHarrisDetector != 0, k);
        else
            cv::goodFeaturesToTrack(*image, *corners, maxCorners, qualityLevel, minDistance, cv::noArray(), *cornersQuality, blockSize, gradientSize, useHarrisDetector != 0, k);
        *pCorners = corners.release();
        *pCornersQuality = cornersQuality.release();
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


CVAPI int cv_imgproc_HoughLinesPointSet(cv::Mat *point, cv::Mat **pLines, int lines_max, int threshold, double min_rho, double max_rho, double rho_step, double min_theta, double max_theta, double theta_step) {
    cv_clear_error();

    try {
        auto lines = std::make_unique<cv::Mat>();
        cv::HoughLinesPointSet(*point, *lines, lines_max, threshold, min_rho, max_rho, rho_step, min_theta, max_theta, theta_step);
        *pLines = lines.release();
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


CVAPI float cv_imgproc_EMD(cv::Mat *signature1, cv::Mat *signature2, int distType, cv::Mat *cost, float *lowerBound, cv::Mat **pFlow) {
    cv_clear_error();

    try {
        cv::Mat costMat = (cost && !cost->empty()) ? *cost : cv::Mat();
        if (pFlow) {
            auto flow = std::make_unique<cv::Mat>();
            float result = cv::EMD(*signature1, *signature2, distType, costMat, lowerBound, *flow);
            *pFlow = flow.release();
            return result;
        } else {
            return cv::EMD(*signature1, *signature2, distType, costMat, lowerBound);
        }
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}


CVAPI int cv_imgproc_getStructuringElementEx(int shape, int kW, int kH, int anchorX, int anchorY, cv::Mat **pDst) {
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        *dst = cv::getStructuringElement(shape, cv::Size(kW, kH), cv::Point(anchorX, anchorY));
        *pDst = dst.release();
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


CVAPI int cv_imgproc_lsdDrawSegments(cv::Mat **pImage, cv::Mat *lines, CVScalar color) {
    cv_clear_error();

    try {
        auto lsd = cv::createLineSegmentDetector();
        lsd->drawSegments(**pImage, *lines);
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

CVAPI int cv_imgproc_lsdCompareSegments(int width, int height, cv::Mat *lines1, cv::Mat *lines2, cv::Mat **pImage) {
    cv_clear_error();

    try {
        auto lsd = cv::createLineSegmentDetector();
        auto image = std::make_unique<cv::Mat>();
        lsd->compareSegments(cv::Size(width, height), *lines1, *lines2, *image);
        *pImage = image.release();
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


CVAPI CVScalar cv_imgproc_morphologyDefaultBorderValue() {
    cv_clear_error();
    try {
        cv::Scalar s = cv::morphologyDefaultBorderValue();
        CVScalar result;
        result.v0 = s[0];
        result.v1 = s[1];
        result.v2 = s[2];
        result.v3 = s[3];
        return result;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return CVScalar();
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return CVScalar();
    } catch (...) {
        cv_set_error_literal("unknown error");
        return CVScalar();
    }
}


CVAPI int cv_imgproc_phaseCorrelateResult(cv::Mat *src1, cv::Mat *src2, cv::Mat *window, double *response, double *shiftX, double *shiftY) {
    cv_clear_error();

    try {
        cv::Point2d result;
        if (window && !window->empty()) {
            result = cv::phaseCorrelate(*src1, *src2, *window, response);
        } else {
            result = cv::phaseCorrelate(*src1, *src2, cv::noArray(), response);
        }
        *shiftX = result.x;
        *shiftY = result.y;
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


CVAPI void *cv_imgproc_createSubdiv2D(int x, int y, int width, int height) {
    cv_clear_error();

    try {
        return new cv::Subdiv2D(cv::Rect(x, y, width, height));
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_imgproc_deleteSubdiv2D(void *subdiv) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
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

CVAPI int cv_imgproc_subdiv2DInitDelaunay(void *subdiv, int x, int y, int width, int height) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        ptr->initDelaunay(cv::Rect(x, y, width, height));
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

CVAPI int cv_imgproc_subdiv2DInsert(void *subdiv, float x, float y) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        ptr->insert(cv::Point2f(x, y));
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

CVAPI int cv_imgproc_subdiv2DInsertMulti(void *subdiv, CVPoint2f *pts, int count) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        std::vector<cv::Point2f> points(count);
        for (int i = 0; i < count; i++) {
            points[i] = cv::Point2f(pts[i].x, pts[i].y);
        }
        ptr->insert(points);
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

CVAPI int cv_imgproc_subdiv2DLocate(void *subdiv, float x, float y, int *edge, int *vertex) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        ptr->locate(cv::Point2f(x, y), *edge, *vertex);
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

CVAPI int cv_imgproc_subdiv2DFindNearest(void *subdiv, float x, float y, float *nearestX, float *nearestY) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        cv::Point2f nearest;
        ptr->findNearest(cv::Point2f(x, y), &nearest);
        if (nearestX) *nearestX = nearest.x;
        if (nearestY) *nearestY = nearest.y;
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

CVAPI int cv_imgproc_subdiv2DGetEdgeList(void *subdiv, float *edges, int *count, int maxCount) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        std::vector<cv::Vec4f> edgeList;
        ptr->getEdgeList(edgeList);
        int n = std::min((int)edgeList.size(), maxCount);
        for (int i = 0; i < n; i++) {
            edges[i * 4 + 0] = edgeList[i][0];
            edges[i * 4 + 1] = edgeList[i][1];
            edges[i * 4 + 2] = edgeList[i][2];
            edges[i * 4 + 3] = edgeList[i][3];
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

CVAPI int cv_imgproc_subdiv2DGetLeadingEdgeList(void *subdiv, int *leadingEdges, int *count, int maxCount) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        std::vector<int> edgeList;
        ptr->getLeadingEdgeList(edgeList);
        int n = std::min((int)edgeList.size(), maxCount);
        for (int i = 0; i < n; i++) {
            leadingEdges[i] = edgeList[i];
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

CVAPI int cv_imgproc_subdiv2DGetTriangleList(void *subdiv, float *triangles, int *count, int maxCount) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        std::vector<cv::Vec6f> triangleList;
        ptr->getTriangleList(triangleList);
        int n = std::min((int)triangleList.size(), maxCount);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 6; j++)
                triangles[i * 6 + j] = triangleList[i][j];
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

CVAPI int cv_imgproc_subdiv2DGetVoronoiFacetList(void *subdiv, int *idx, int idxCount, CVPoint2f *facetCenters, int *facetCount, int maxFacets) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        std::vector<int> idxVec(idx, idx + idxCount);
        std::vector<std::vector<cv::Point2f>> facetList;
        std::vector<cv::Point2f> facetCentersList;
        ptr->getVoronoiFacetList(idxVec, facetList, facetCentersList);
        int n = std::min((int)facetCentersList.size(), maxFacets);
        for (int i = 0; i < n; i++) {
            facetCenters[i].x = facetCentersList[i].x;
            facetCenters[i].y = facetCentersList[i].y;
        }
        *facetCount = n;
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

CVAPI int cv_imgproc_subdiv2DGetVertex(void *subdiv, int vertex, int *firstEdge, float *ptX, float *ptY) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        cv::Point2f pt = ptr->getVertex(vertex, firstEdge);
        *ptX = pt.x;
        *ptY = pt.y;
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

CVAPI int cv_imgproc_subdiv2DGetEdge(void *subdiv, int edge, int nextEdgeType) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        return ptr->getEdge(edge, nextEdgeType);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}

CVAPI int cv_imgproc_subdiv2DNextEdge(void *subdiv, int edge) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        return ptr->nextEdge(edge);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}

CVAPI int cv_imgproc_subdiv2DRotateEdge(void *subdiv, int edge, int rotate) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        return ptr->rotateEdge(edge, rotate);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}

CVAPI int cv_imgproc_subdiv2DSymEdge(void *subdiv, int edge) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        return ptr->symEdge(edge);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}

CVAPI int cv_imgproc_subdiv2DEdgeOrg(void *subdiv, int edge, float *ptX, float *ptY) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        cv::Point2f pt;
        ptr->edgeOrg(edge, &pt);
        *ptX = pt.x;
        *ptY = pt.y;
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

CVAPI int cv_imgproc_subdiv2DEdgeDst(void *subdiv, int edge, float *ptX, float *ptY) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Subdiv2D*>(subdiv);
        cv::Point2f pt;
        ptr->edgeDst(edge, &pt);
        *ptX = pt.x;
        *ptY = pt.y;
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


static cv::GeneralizedHough *getGeneralizedHough(void *hough)
{
    auto *handle = static_cast<cv::Ptr<cv::GeneralizedHough> *>(hough);
    return handle ? handle->get() : nullptr;
}

template<class Detector>
static Detector *getGeneralizedHoughAs(void *hough)
{
    auto *detector = dynamic_cast<Detector *>(getGeneralizedHough(hough));
    if (hough && !detector)
        cv_set_error_literal("Wrong generalized Hough detector type");
    return detector;
}

CVAPI void cv_imgproc_generalizedHoughSetTemplate(void *hough, cv::Mat *templ, CVPoint templCenter) {
    cv_clear_error();

    try {
        auto p = getGeneralizedHough(hough);
        if (p) p->setTemplate(*templ, cv::Point(templCenter.x, templCenter.y));
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}

CVAPI void cv_imgproc_generalizedHoughSetTemplateWithEdges(void *hough, cv::Mat *edges, cv::Mat *dx, cv::Mat *dy, CVPoint templCenter) {
    cv_clear_error();

    try {
        auto p = getGeneralizedHough(hough);
        if (p) p->setTemplate(*edges, *dx, *dy, cv::Point(templCenter.x, templCenter.y));
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}

CVAPI void cv_imgproc_generalizedHoughDetect(void *hough, cv::Mat *image, cv::Mat **pPositions, cv::Mat **pVotes) {
    cv_clear_error();
    if (!pPositions || !pVotes || pPositions == pVotes) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return;
    }

    try {
        auto p = getGeneralizedHough(hough);
        if (p) {
            auto positions = std::make_unique<cv::Mat>();
            auto votes = std::make_unique<cv::Mat>();
            p->detect(*image, *positions, *votes);
            *pPositions = positions.release();
            *pVotes = votes.release();
        }
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}

CVAPI void cv_imgproc_generalizedHoughDetectWithEdges(void *hough, cv::Mat *edges, cv::Mat *dx, cv::Mat *dy, cv::Mat **pPositions, cv::Mat **pVotes) {
    cv_clear_error();
    if (!pPositions || !pVotes || pPositions == pVotes) {
        cv_set_error_literal("Missing or overlapping matrix outputs");
        return;
    }

    try {
        auto p = getGeneralizedHough(hough);
        if (p) {
            auto positions = std::make_unique<cv::Mat>();
            auto votes = std::make_unique<cv::Mat>();
            p->detect(*edges, *dx, *dy, *positions, *votes);
            *pPositions = positions.release();
            *pVotes = votes.release();
        }
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}

CVAPI double cv_imgproc_generalizedHoughGetCannyLowThresh(void *hough) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) return p->getCannyLowThresh(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughSetCannyLowThresh(void *hough, double value) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) p->setCannyLowThresh((int)value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGetCannyHighThresh(void *hough) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) return p->getCannyHighThresh(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughSetCannyHighThresh(void *hough, double value) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) p->setCannyHighThresh((int)value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGetMinDist(void *hough) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) return p->getMinDist(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughSetMinDist(void *hough, double value) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) p->setMinDist(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGetDp(void *hough) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) return p->getDp(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughSetDp(void *hough, double value) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) p->setDp(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI int cv_imgproc_generalizedHoughGetMaxBufferSize(void *hough) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) return p->getMaxBufferSize(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughSetMaxBufferSize(void *hough, int value) {
    cv_clear_error();

    try { auto p = getGeneralizedHough(hough); if (p) p->setMaxBufferSize(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}


CVAPI int cv_imgproc_generalizedHoughBallardGetLevels(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughBallard>(hough); if (detector) return detector->getLevels(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughBallardSetLevels(void *hough, int value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughBallard>(hough); if (detector) detector->setLevels(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI int cv_imgproc_generalizedHoughBallardGetVotesThreshold(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughBallard>(hough); if (detector) return detector->getVotesThreshold(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughBallardSetVotesThreshold(void *hough, int value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughBallard>(hough); if (detector) detector->setVotesThreshold(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}


CVAPI double cv_imgproc_generalizedHoughGuilGetMinAngle(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getMinAngle(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetMinAngle(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setMinAngle(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGuilGetMaxAngle(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getMaxAngle(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetMaxAngle(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setMaxAngle(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGuilGetAngleStep(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getAngleStep(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetAngleStep(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setAngleStep(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI int cv_imgproc_generalizedHoughGuilGetAngleThresh(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getAngleThresh(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetAngleThresh(void *hough, int value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setAngleThresh(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGuilGetMinScale(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getMinScale(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetMinScale(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setMinScale(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGuilGetMaxScale(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getMaxScale(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetMaxScale(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setMaxScale(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGuilGetScaleStep(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getScaleStep(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetScaleStep(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setScaleStep(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI int cv_imgproc_generalizedHoughGuilGetScaleThresh(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getScaleThresh(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetScaleThresh(void *hough, int value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setScaleThresh(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI int cv_imgproc_generalizedHoughGuilGetPosThresh(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getPosThresh(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetPosThresh(void *hough, int value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setPosThresh(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI double cv_imgproc_generalizedHoughGuilGetXi(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getXi(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetXi(void *hough, double value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setXi(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}
CVAPI int cv_imgproc_generalizedHoughGuilGetLevels(void *hough) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) return detector->getLevels(); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) { cv_set_error_literal("unknown error"); } return 0;
}
CVAPI void cv_imgproc_generalizedHoughGuilSetLevels(void *hough, int value) {
    cv_clear_error();

    try { auto *detector = getGeneralizedHoughAs<cv::GeneralizedHoughGuil>(hough); if (detector) detector->setLevels(value); } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return;
    } catch (...) { cv_set_error_literal("unknown error"); }
}


CVAPI int cv_imgproc_lsdGetLines(void *lsd, cv::Mat **pLines) {
    cv_clear_error();

    try {
        auto ptr = static_cast<cv::Ptr<cv::LineSegmentDetector>*>(lsd);
        if (!ptr || !*ptr) return 0;


        if (pLines && *pLines) {
            return (*pLines)->rows;
        }
        return 0;
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
