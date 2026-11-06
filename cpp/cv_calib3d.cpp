

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_calib3d.h"
#include <opencv2/video/tracking.hpp>
#include <memory>
#include <utility>
#include <vector>


using MatOutputs = std::vector<std::unique_ptr<cv::Mat>>;

static MatOutputs prepareMatOutputs(const std::vector<cv::Mat> &values, cv::Mat **destination)
{
    MatOutputs outputs;
    if (destination) {
        outputs.reserve(values.size());
        for (const auto &value : values)
            outputs.push_back(std::make_unique<cv::Mat>(value.clone()));
    }
    return outputs;
}

static void publishMatOutputs(MatOutputs &outputs, cv::Mat **destination)
{
    for (size_t i = 0; i < outputs.size(); ++i)
        destination[i] = outputs[i].release();
}

CVAPI int cv_calib3d_calibrateCamera(cv::Mat **objectPoints, cv::Mat **imagePoints, int imageCount, CVSize imageSize, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int flags, double *reprojError)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> objPts, imgPts;
        for (int i = 0; i < imageCount; i++) {
            objPts.push_back(*objectPoints[i]);
            imgPts.push_back(*imagePoints[i]);
        }

        auto camMat = std::make_unique<cv::Mat>();
        auto distC = std::make_unique<cv::Mat>();
        std::vector<cv::Mat> rv, tv;
        double result = cv::calibrateCamera(objPts, imgPts, cv::Size(imageSize.cx, imageSize.cy), *camMat, *distC, rv, tv, flags);

        auto rvecsOutput = prepareMatOutputs(rv, rvecs);
        auto tvecsOutput = prepareMatOutputs(tv, tvecs);
        *cameraMatrix = camMat.release();
        *distCoeffs = distC.release();
        if (reprojError) *reprojError = result;
        publishMatOutputs(rvecsOutput, rvecs);
        publishMatOutputs(tvecsOutput, tvecs);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_findChessboardCorners(cv::Mat *image, CVSize patternSize, cv::Mat **corners, int flags, int *found)
{
    cv_clear_error();

    try {
        auto corn = std::make_unique<cv::Mat>();
        bool f = cv::findChessboardCorners(*image, cv::Size(patternSize.cx, patternSize.cy), *corn, flags);
        *corners = corn.release();
        if (found) *found = f ? 1 : 0;
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_drawChessboardCorners(cv::Mat **image, CVSize patternSize, cv::Mat *corners, int patternWasFound)
{
    cv_clear_error();
    if (!image || !*image) {
        cv_set_error_literal("image matrix is required");
        return 0;
    }

    try {
        cv::Mat result = (*image)->clone();
        cv::drawChessboardCorners(result, cv::Size(patternSize.cx, patternSize.cy), *corners, patternWasFound != 0);
        **image = std::move(result);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_solvePnP(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess, int flags)
{
    cv_clear_error();
    const bool useGuess = useExtrinsicGuess != 0 && flags == cv::SOLVEPNP_ITERATIVE;
    if (!objectPoints || !imagePoints || !cameraMatrix || !rvec || !tvec || rvec == tvec
        || (useGuess && (!*rvec || !*tvec || *rvec == *tvec))) {
        cv_set_error_literal("invalid pose input or output matrix");
        return 0;
    }

    try {
        auto rv = std::make_unique<cv::Mat>(useGuess ? (*rvec)->clone() : cv::Mat());
        auto tv = std::make_unique<cv::Mat>(useGuess ? (*tvec)->clone() : cv::Mat());
        const cv::Mat distortion = distCoeffs ? *distCoeffs : cv::Mat();
        if (!cv::solvePnP(*objectPoints, *imagePoints, *cameraMatrix, distortion, *rv, *tv, useGuess, flags)) {
            cv_set_error_literal("could not estimate a camera pose");
            return 0;
        }
        if (useGuess) {
            **rvec = std::move(*rv);
            **tvec = std::move(*tv);
        } else {
            *rvec = rv.release();
            *tvec = tv.release();
        }
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_solvePnPRansac(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess, int iterationsCount, float reprojectionError, double confidence, cv::Mat **inliers, int flags)
{
    cv_clear_error();
    const bool useGuess = useExtrinsicGuess != 0 && flags == cv::SOLVEPNP_ITERATIVE;
    if (!objectPoints || !imagePoints || !cameraMatrix || !rvec || !tvec || rvec == tvec
        || (inliers && (inliers == rvec || inliers == tvec))
        || (useGuess && (!*rvec || !*tvec || *rvec == *tvec))) {
        cv_set_error_literal("invalid pose input or output matrix");
        return 0;
    }

    try {
        auto rv = std::make_unique<cv::Mat>(useGuess ? (*rvec)->clone() : cv::Mat());
        auto tv = std::make_unique<cv::Mat>(useGuess ? (*tvec)->clone() : cv::Mat());
        auto inl = std::make_unique<cv::Mat>();
        const cv::Mat distortion = distCoeffs ? *distCoeffs : cv::Mat();
        if (!cv::solvePnPRansac(*objectPoints, *imagePoints, *cameraMatrix, distortion, *rv, *tv, useGuess, iterationsCount, reprojectionError, confidence, *inl, flags)) {
            cv_set_error_literal("could not estimate a camera pose");
            return 0;
        }
        if (useGuess) {
            **rvec = std::move(*rv);
            **tvec = std::move(*tv);
        } else {
            *rvec = rv.release();
            *tvec = tv.release();
        }
        if (inliers) *inliers = inl.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_projectPoints(cv::Mat *objectPoints, cv::Mat *rvec, cv::Mat *tvec, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **imagePoints)
{
    cv_clear_error();

    try {
        auto imgPts = std::make_unique<cv::Mat>();
        cv::projectPoints(*objectPoints, *rvec, *tvec, *cameraMatrix, *distCoeffs, *imgPts);
        *imagePoints = imgPts.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_rodrigues(cv::Mat *source, cv::Mat **target, cv::Mat **jacobian)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (jacobian) {
            auto jac = std::make_unique<cv::Mat>();
            cv::Rodrigues(*source, *dst, *jac);
            *jacobian = jac.release();
        } else {
            cv::Rodrigues(*source, *dst);
        }
        *target = dst.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_stereoCalibrate(cv::Mat **objectPoints, cv::Mat **imagePoints1, cv::Mat **imagePoints2, int imageCount, cv::Mat **cameraMatrix1, cv::Mat **distCoeffs1, cv::Mat **cameraMatrix2, cv::Mat **distCoeffs2, CVSize imageSize, cv::Mat **R, cv::Mat **T, cv::Mat **E, cv::Mat **F, int flags, double *reprojError)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> objPts, imgPts1, imgPts2;
        for (int i = 0; i < imageCount; i++) {
            objPts.push_back(*objectPoints[i]);
            imgPts1.push_back(*imagePoints1[i]);
            imgPts2.push_back(*imagePoints2[i]);
        }
        auto cm1 = std::make_unique<cv::Mat>();
        auto dc1 = std::make_unique<cv::Mat>();
        auto cm2 = std::make_unique<cv::Mat>();
        auto dc2 = std::make_unique<cv::Mat>();
        auto rMat = std::make_unique<cv::Mat>();
        auto tMat = std::make_unique<cv::Mat>();
        auto eMat = std::make_unique<cv::Mat>();
        auto fMat = std::make_unique<cv::Mat>();
        double result = cv::stereoCalibrate(objPts, imgPts1, imgPts2, *cm1, *dc1, *cm2, *dc2, cv::Size(imageSize.cx, imageSize.cy), *rMat, *tMat, *eMat, *fMat, flags);
        *cameraMatrix1 = cm1.release();
        *distCoeffs1 = dc1.release();
        *cameraMatrix2 = cm2.release();
        *distCoeffs2 = dc2.release();
        *R = rMat.release();
        *T = tMat.release();
        *E = eMat.release();
        *F = fMat.release();
        if (reprojError) *reprojError = result;
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoRectify(cv::Mat *cameraMatrix1, cv::Mat *distCoeffs1, cv::Mat *cameraMatrix2, cv::Mat *distCoeffs2, CVSize imageSize, cv::Mat *R, cv::Mat *T, cv::Mat **R1, cv::Mat **R2, cv::Mat **P1, cv::Mat **P2, cv::Mat **Q, int flags, double alpha, CVSize newImageSize)
{
    cv_clear_error();

    try {
        auto r1 = std::make_unique<cv::Mat>();
        auto r2 = std::make_unique<cv::Mat>();
        auto p1 = std::make_unique<cv::Mat>();
        auto p2 = std::make_unique<cv::Mat>();
        auto q = std::make_unique<cv::Mat>();
        cv::stereoRectify(*cameraMatrix1, *distCoeffs1, *cameraMatrix2, *distCoeffs2, cv::Size(imageSize.cx, imageSize.cy), *R, *T, *r1, *r2, *p1, *p2, *q, flags, alpha, cv::Size(newImageSize.cx, newImageSize.cy));
        *R1 = r1.release();
        *R2 = r2.release();
        *P1 = p1.release();
        *P2 = p2.release();
        *Q = q.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_initUndistortRectifyMap(cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *R, cv::Mat *newCameraMatrix, CVSize size, int m1type, cv::Mat **map1, cv::Mat **map2)
{
    cv_clear_error();

    try {
        auto m1 = std::make_unique<cv::Mat>();
        auto m2 = std::make_unique<cv::Mat>();
        cv::initUndistortRectifyMap(*cameraMatrix, *distCoeffs, *R, *newCameraMatrix, cv::Size(size.cx, size.cy), m1type, *m1, *m2);
        *map1 = m1.release();
        *map2 = m2.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_undistort(cv::Mat *source, cv::Mat **target, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *newCameraMatrix)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        if (newCameraMatrix)
            cv::undistort(*source, *dst, *cameraMatrix, *distCoeffs, *newCameraMatrix);
        else
            cv::undistort(*source, *dst, *cameraMatrix, *distCoeffs);
        *target = dst.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_findFundamentalMat(cv::Mat *points1, cv::Mat *points2, cv::Mat **target, int method, double ransacReprojThreshold, double confidence, cv::Mat **mask)
{
    cv_clear_error();
    if (!target || target == mask) {
        cv_set_error_literal("invalid matrix or mask output pointer");
        return 0;
    }

    try {
        auto result = std::make_unique<cv::Mat>();
        cv::Mat maskMat;
        *result = cv::findFundamentalMat(*points1, *points2, method, ransacReprojThreshold, confidence, maskMat);
        if (mask) {
            auto m = std::make_unique<cv::Mat>(std::move(maskMat));
            *mask = m.release();
        }
        *target = result.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_findEssentialMat(cv::Mat *points1, cv::Mat *points2, cv::Mat *cameraMatrix, int method, double prob, double threshold, cv::Mat **mask, cv::Mat **target)
{
    cv_clear_error();
    if (!target || target == mask) {
        cv_set_error_literal("invalid matrix or mask output pointer");
        return 0;
    }

    try {
        auto result = std::make_unique<cv::Mat>();
        cv::Mat maskMat;
        *result = cv::findEssentialMat(*points1, *points2, *cameraMatrix, method, prob, threshold, maskMat);
        if (mask) {
            auto m = std::make_unique<cv::Mat>(std::move(maskMat));
            *mask = m.release();
        }
        *target = result.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_decomposeEssentialMat(cv::Mat *E, cv::Mat **R1, cv::Mat **R2, cv::Mat **T)
{
    cv_clear_error();

    try {
        auto r1 = std::make_unique<cv::Mat>();
        auto r2 = std::make_unique<cv::Mat>();
        auto t = std::make_unique<cv::Mat>();
        cv::decomposeEssentialMat(*E, *r1, *r2, *t);
        *R1 = r1.release();
        *R2 = r2.release();
        *T = t.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_triangulatePoints(cv::Mat *projMatr1, cv::Mat *projMatr2, cv::Mat *projPoints1, cv::Mat *projPoints2, cv::Mat **points4D)
{
    cv_clear_error();

    try {
        auto pts = std::make_unique<cv::Mat>();
        cv::triangulatePoints(*projMatr1, *projMatr2, *projPoints1, *projPoints2, *pts);
        *points4D = pts.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_findChessboardCornersSB(cv::Mat *image, int patternW, int patternH, cv::Mat **corners, int flags)
{
    cv_clear_error();

    try {
        auto corn = std::make_unique<cv::Mat>();
        bool found = cv::findChessboardCornersSB(*image, cv::Size(patternW, patternH), *corn, flags);
        *corners = corn.release();
        return found ? 1 : 0;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_findCirclesGrid(cv::Mat *image, int patternW, int patternH, cv::Mat **centers, int flags)
{
    cv_clear_error();

    try {
        auto ctr = std::make_unique<cv::Mat>();
        bool found = cv::findCirclesGrid(*image, cv::Size(patternW, patternH), *ctr, flags);
        *centers = ctr.release();
        return found ? 1 : 0;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_recoverPose(cv::Mat *E, cv::Mat *points1, cv::Mat *points2, cv::Mat *cameraMatrix, cv::Mat **R, cv::Mat **T, cv::Mat **mask)
{
    cv_clear_error();

    try {
        auto rMat = std::make_unique<cv::Mat>();
        auto tMat = std::make_unique<cv::Mat>();
        if (mask) {
            auto mMat = std::make_unique<cv::Mat>();
            cv::recoverPose(*E, *points1, *points2, *cameraMatrix, *rMat, *tMat, *mMat);
            *mask = mMat.release();
        } else {
            cv::recoverPose(*E, *points1, *points2, *cameraMatrix, *rMat, *tMat);
        }
        *R = rMat.release();
        *T = tMat.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_computeCorrespondEpilines(cv::Mat *points, int whichImage, cv::Mat *F, cv::Mat **lines)
{
    cv_clear_error();

    try {
        auto l = std::make_unique<cv::Mat>();
        cv::computeCorrespondEpilines(*points, whichImage, *F, *l);
        *lines = l.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_convertPointsFromHomogeneous(cv::Mat *source, cv::Mat **target)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::convertPointsFromHomogeneous(*source, *dst);
        *target = dst.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_convertPointsToHomogeneous(cv::Mat *source, cv::Mat **target)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::convertPointsToHomogeneous(*source, *dst);
        *target = dst.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_undistortPoints(cv::Mat *source, cv::Mat **target, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *R, cv::Mat *P)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::Mat Rmat = R ? *R : cv::Mat();
        cv::Mat Pmat = P ? *P : cv::Mat();
        cv::undistortPoints(*source, *dst, *cameraMatrix, *distCoeffs, Rmat, Pmat);
        *target = dst.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_estimateAffine3D(cv::Mat *source, cv::Mat *target, cv::Mat **out, cv::Mat **inliers, double ransacThreshold, double confidence)
{
    cv_clear_error();
    if (!out || !inliers || out == inliers) {
        cv_set_error_literal("invalid transform or inliers output pointer");
        return 0;
    }

    try {
        auto o = std::make_unique<cv::Mat>();
        auto inl = std::make_unique<cv::Mat>();
        if (!cv::estimateAffine3D(*source, *target, *o, *inl, ransacThreshold, confidence)) {
            cv_set_error_literal("could not estimate a 3D transform");
            return 0;
        }
        *out = o.release();
        *inliers = inl.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

static int estimateAffine2D(cv::Mat *source, cv::Mat *target, cv::Mat **inliers,
    int method, double ransacReprojThreshold, int maxIters, double confidence,
    int refineIters, cv::Mat **output)
{
    cv_clear_error();
    if (!source || !target || !inliers || (output && output == inliers)) {
        cv_set_error_literal("invalid affine input or output pointer");
        return 0;
    }

    try {
        auto mask = std::make_unique<cv::Mat>();
        cv::Mat transform = cv::estimateAffine2D(*source, *target, *mask, method,
            ransacReprojThreshold, maxIters, confidence, (size_t)refineIters);
        if (output) {
            if (transform.empty()) {
                cv_set_error_literal("could not estimate a 2D affine transform");
                return 0;
            }
            auto matrix = std::make_unique<cv::Mat>(std::move(transform));
            *output = matrix.release();
        }
        *inliers = mask.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_estimateAffine2D(cv::Mat *source, cv::Mat *target, cv::Mat **inliers, int method, double ransacReprojThreshold, int maxIters, double confidence, int refineIters)
{
    return estimateAffine2D(source, target, inliers, method, ransacReprojThreshold,
        maxIters, confidence, refineIters, nullptr);
}

CVAPI int cv_calib3d_estimateAffine2DWithTransform(cv::Mat *source, cv::Mat *target,
    cv::Mat **inliers, int method, double ransacReprojThreshold, int maxIters,
    double confidence, int refineIters, cv::Mat **output)
{
    if (!output) {
        cv_clear_error();
        cv_set_error_literal("affine transform output pointer is required");
        return 0;
    }
    return estimateAffine2D(source, target, inliers, method, ransacReprojThreshold,
        maxIters, confidence, refineIters, output);
}


CVAPI int cv_calib3d_getOptimalNewCameraMatrix(cv::Mat *cameraMatrix, cv::Mat *distCoeffs, int imageW, int imageH, double alpha, int newImageW, int newImageH, CVRect *validPixROI, int centerPrincipalPoint, cv::Mat **result)
{
    cv_clear_error();

    try {
        cv::Rect roi;
        auto newCam = std::make_unique<cv::Mat>();
        *newCam = cv::getOptimalNewCameraMatrix(*cameraMatrix, *distCoeffs, cv::Size(imageW, imageH), alpha, cv::Size(newImageW, newImageH), &roi, centerPrincipalPoint != 0);
        *result = newCam.release();
        if (validPixROI) {
            validPixROI->x = roi.x;
            validPixROI->y = roi.y;
            validPixROI->hSize = roi.width;
            validPixROI->vSize = roi.height;
        }
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_calibrateCameraExtended(cv::Mat **objectPoints, cv::Mat **imagePoints, int imageCount, int hSize, int vSize, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, cv::Mat **stdDeviationsIntrinsics, cv::Mat **stdDeviationsExtrinsics, cv::Mat **perViewErrors, int flags)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> objPts, imgPts;
        for (int i = 0; i < imageCount; i++) {
            objPts.push_back(*objectPoints[i]);
            imgPts.push_back(*imagePoints[i]);
        }
        auto camMat = std::make_unique<cv::Mat>();
        auto distC = std::make_unique<cv::Mat>();
        auto stdIntr = std::make_unique<cv::Mat>();
        auto stdExtr = std::make_unique<cv::Mat>();
        auto pvErrors = std::make_unique<cv::Mat>();
        std::vector<cv::Mat> rv, tv;
        cv::calibrateCamera(objPts, imgPts, cv::Size(hSize, vSize), *camMat, *distC, rv, tv, *stdIntr, *stdExtr, *pvErrors, flags);

        auto rvecsOutput = prepareMatOutputs(rv, rvecs);
        auto tvecsOutput = prepareMatOutputs(tv, tvecs);
        *cameraMatrix = camMat.release();
        *distCoeffs = distC.release();
        *stdDeviationsIntrinsics = stdIntr.release();
        *stdDeviationsExtrinsics = stdExtr.release();
        *perViewErrors = pvErrors.release();
        publishMatOutputs(rvecsOutput, rvecs);
        publishMatOutputs(tvecsOutput, tvecs);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_calibrateHandEye(cv::Mat **R_gripper2base, cv::Mat **t_gripper2base, cv::Mat **R_target2cam, cv::Mat **t_target2cam, int count, cv::Mat **R_cam2gripper, cv::Mat **t_cam2gripper, int method)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> Rg2b, tg2b, Rt2c, tt2c;
        for (int i = 0; i < count; i++) {
            Rg2b.push_back(*R_gripper2base[i]);
            tg2b.push_back(*t_gripper2base[i]);
            Rt2c.push_back(*R_target2cam[i]);
            tt2c.push_back(*t_target2cam[i]);
        }
        auto rOut = std::make_unique<cv::Mat>();
        auto tOut = std::make_unique<cv::Mat>();
        cv::calibrateHandEye(Rg2b, tg2b, Rt2c, tt2c, *rOut, *tOut, (cv::HandEyeCalibrationMethod)method);
        *R_cam2gripper = rOut.release();
        *t_cam2gripper = tOut.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_calibrateRobotWorldHandEye(cv::Mat **R_world2cam, cv::Mat **t_world2cam, cv::Mat **R_base2gripper, cv::Mat **t_base2gripper, int count, cv::Mat **R_base2world, cv::Mat **t_base2world, cv::Mat **R_gripper2cam, cv::Mat **t_gripper2cam, int method)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> Rw2c, tw2c, Rb2g, tb2g;
        for (int i = 0; i < count; i++) {
            Rw2c.push_back(*R_world2cam[i]);
            tw2c.push_back(*t_world2cam[i]);
            Rb2g.push_back(*R_base2gripper[i]);
            tb2g.push_back(*t_base2gripper[i]);
        }
        auto rb2w = std::make_unique<cv::Mat>();
        auto tb2w = std::make_unique<cv::Mat>();
        auto rg2c = std::make_unique<cv::Mat>();
        auto tg2c = std::make_unique<cv::Mat>();
        cv::calibrateRobotWorldHandEye(Rw2c, tw2c, Rb2g, tb2g, *rb2w, *tb2w, *rg2c, *tg2c, (cv::RobotWorldHandEyeCalibrationMethod)method);
        *R_base2world = rb2w.release();
        *t_base2world = tb2w.release();
        *R_gripper2cam = rg2c.release();
        *t_gripper2cam = tg2c.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_composeRT(cv::Mat *rvec1, cv::Mat *tvec1, cv::Mat *rvec2, cv::Mat *tvec2, cv::Mat **rvec3, cv::Mat **tvec3)
{
    cv_clear_error();

    try {
        auto r3 = std::make_unique<cv::Mat>();
        auto t3 = std::make_unique<cv::Mat>();
        cv::composeRT(*rvec1, *tvec1, *rvec2, *tvec2, *r3, *t3);
        *rvec3 = r3.release();
        *tvec3 = t3.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_decomposeHomographyMat(cv::Mat *H, cv::Mat *K, cv::Mat **rotations, cv::Mat **translations, cv::Mat **normals, int *count)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> rots, trans, norms;
        int n = cv::decomposeHomographyMat(*H, *K, rots, trans, norms);
        auto rotationsOutput = prepareMatOutputs(rots, rotations);
        auto translationsOutput = prepareMatOutputs(trans, translations);
        auto normalsOutput = prepareMatOutputs(norms, normals);
        if (count) *count = n;
        publishMatOutputs(rotationsOutput, rotations);
        publishMatOutputs(translationsOutput, translations);
        publishMatOutputs(normalsOutput, normals);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_decomposeProjectionMatrix(cv::Mat *projMatrix, cv::Mat **cameraMatrix, cv::Mat **rotMatrix, cv::Mat **transVect)
{
    cv_clear_error();

    try {
        auto camMat = std::make_unique<cv::Mat>();
        auto rotMat = std::make_unique<cv::Mat>();
        auto transV = std::make_unique<cv::Mat>();
        cv::decomposeProjectionMatrix(*projMatrix, *camMat, *rotMat, *transV);
        *cameraMatrix = camMat.release();
        *rotMatrix = rotMat.release();
        *transVect = transV.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_drawFrameAxes(cv::Mat **image, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *rvec, cv::Mat *tvec, float length, int thickness)
{
    cv_clear_error();
    if (!image || !*image) {
        cv_set_error_literal("image matrix is required");
        return 0;
    }

    try {
        cv::Mat result = (*image)->clone();
        cv::drawFrameAxes(result, *cameraMatrix, *distCoeffs, *rvec, *tvec, length, thickness);
        **image = std::move(result);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_estimateAffinePartial2D(cv::Mat *source, cv::Mat *target, cv::Mat **inliers, int method, double ransacReprojThreshold, int maxIters, double confidence, int refineIters, cv::Mat **output)
{
    cv_clear_error();

    try {
        auto inl = std::make_unique<cv::Mat>();
        auto out = std::make_unique<cv::Mat>();
        *out = cv::estimateAffinePartial2D(*source, *target, *inl, method, ransacReprojThreshold, maxIters, confidence, (size_t)refineIters);
        *inliers = inl.release();
        *output = out.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_estimateTranslation3D(cv::Mat *source, cv::Mat *target, cv::Mat **out, cv::Mat **inliers, double ransacThreshold, double confidence)
{
    cv_clear_error();
    if (!out || !inliers || out == inliers) {
        cv_set_error_literal("invalid transform or inliers output pointer");
        return 0;
    }

    try {
        auto o = std::make_unique<cv::Mat>();
        auto inl = std::make_unique<cv::Mat>();
        if (!cv::estimateTranslation3D(*source, *target, *o, *inl, ransacThreshold, confidence)) {
            cv_set_error_literal("could not estimate a 3D transform");
            return 0;
        }
        *out = o.release();
        *inliers = inl.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_filterSpeckles(cv::Mat **image, double newVal, int maxSpeckleSize, double maxDiff, cv::Mat **buf)
{
    cv_clear_error();
    if (!image || !*image || image == buf) {
        cv_set_error_literal("invalid image or buffer pointer");
        return 0;
    }

    try {
        cv::Mat img = (*image)->clone();
        if (buf) {
            auto buffer = std::make_unique<cv::Mat>();
            cv::filterSpeckles(img, newVal, maxSpeckleSize, maxDiff, *buffer);
            *buf = buffer.release();
        } else {
            cv::filterSpeckles(img, newVal, maxSpeckleSize, maxDiff);
        }
        **image = std::move(img);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_find4QuadCornerSubpix(cv::Mat *image, cv::Mat **corners, int regionSizeW, int regionSizeH)
{
    cv_clear_error();
    if (!image || !corners || !*corners) {
        cv_set_error_literal("image and initial corners are required");
        return 0;
    }

    try {
        cv::Mat refined = (*corners)->clone();
        if (!cv::find4QuadCornerSubpix(*image, refined, cv::Size(regionSizeW, regionSizeH)))
            return 0;
        **corners = std::move(refined);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_findTransformECC(cv::Mat *templateImage, cv::Mat *inputImage, cv::Mat **warpMatrix, int motionType, int maxCount, double epsilon, cv::Mat *inputMask, int gaussFiltSize)
{
    cv_clear_error();

    try {
        cv::TermCriteria criteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, maxCount, epsilon);
        cv::Mat mask = inputMask ? *inputMask : cv::Mat();
        auto warp = std::make_unique<cv::Mat>();
        cv::findTransformECC(*templateImage, *inputImage, *warp, motionType, criteria, mask, gaussFiltSize);
        *warpMatrix = warp.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_initCameraMatrix2D(cv::Mat **objectPoints, cv::Mat **imagePoints, int count, int hSize, int vSize, double aspectRatio, cv::Mat **cameraMatrix)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> objPts, imgPts;
        for (int i = 0; i < count; i++) {
            objPts.push_back(*objectPoints[i]);
            imgPts.push_back(*imagePoints[i]);
        }
        auto result = std::make_unique<cv::Mat>();
        *result = cv::initCameraMatrix2D(objPts, imgPts, cv::Size(hSize, vSize), aspectRatio);
        *cameraMatrix = result.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_initInverseRectificationMap(cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *R, cv::Mat *newCameraMatrix, int hSize, int vSize, int m1type, cv::Mat **map1, cv::Mat **map2)
{
    cv_clear_error();

    try {
        auto m1 = std::make_unique<cv::Mat>();
        auto m2 = std::make_unique<cv::Mat>();
        cv::initInverseRectificationMap(*cameraMatrix, *distCoeffs, *R, *newCameraMatrix, cv::Size(hSize, vSize), m1type, *m1, *m2);
        *map1 = m1.release();
        *map2 = m2.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_matMulDeriv(cv::Mat *A, cv::Mat *B, cv::Mat **dABdA, cv::Mat **dABdB)
{
    cv_clear_error();

    try {
        auto da = std::make_unique<cv::Mat>();
        auto db = std::make_unique<cv::Mat>();
        cv::matMulDeriv(*A, *B, *da, *db);
        *dABdA = da.release();
        *dABdB = db.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_RQDecomp3x3(cv::Mat *source, cv::Mat **mtxR, cv::Mat **mtxQ, cv::Mat **Qx, cv::Mat **Qy, cv::Mat **Qz)
{
    cv_clear_error();

    try {
        auto r = std::make_unique<cv::Mat>();
        auto q = std::make_unique<cv::Mat>();
        if (Qx && Qy && Qz) {
            auto qx = std::make_unique<cv::Mat>();
            auto qy = std::make_unique<cv::Mat>();
            auto qz = std::make_unique<cv::Mat>();
            cv::RQDecomp3x3(*source, *r, *q, *qx, *qy, *qz);
            *Qx = qx.release();
            *Qy = qy.release();
            *Qz = qz.release();
        } else {
            cv::RQDecomp3x3(*source, *r, *q);
        }
        *mtxR = r.release();
        *mtxQ = q.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_reprojectImageTo3D(cv::Mat *disparity, cv::Mat **image3D, cv::Mat *Q, int handleMissingValues, int ddepth)
{
    cv_clear_error();

    try {
        auto img3d = std::make_unique<cv::Mat>();
        cv::reprojectImageTo3D(*disparity, *img3d, *Q, handleMissingValues != 0, ddepth);
        *image3D = img3d.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_sampsonDistance(cv::Mat *pt1, cv::Mat *pt2, cv::Mat *F, double *distance)
{
    cv_clear_error();

    try {
        double d = cv::sampsonDistance(*pt1, *pt2, *F);
        if (distance) *distance = d;
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoRectifyUncalibrated(cv::Mat *points1, cv::Mat *points2, cv::Mat *F, int imgW, int imgH, cv::Mat **H1, cv::Mat **H2, double threshold)
{
    cv_clear_error();

    try {
        auto h1 = std::make_unique<cv::Mat>();
        auto h2 = std::make_unique<cv::Mat>();
        bool result = cv::stereoRectifyUncalibrated(*points1, *points2, *F, cv::Size(imgW, imgH), *h1, *h2, threshold);
        *H1 = h1.release();
        *H2 = h2.release();
        return result ? 1 : 0;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoCalibrateExtended(cv::Mat **objectPoints, cv::Mat **imagePoints1, cv::Mat **imagePoints2, int count, cv::Mat **cameraMatrix1, cv::Mat **distCoeffs1, cv::Mat **cameraMatrix2, cv::Mat **distCoeffs2, int hSize, int vSize, cv::Mat **R, cv::Mat **T, cv::Mat **E, cv::Mat **F, cv::Mat **perViewErrors, int flags)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> objPts, imgPts1, imgPts2;
        for (int i = 0; i < count; i++) {
            objPts.push_back(*objectPoints[i]);
            imgPts1.push_back(*imagePoints1[i]);
            imgPts2.push_back(*imagePoints2[i]);
        }
        auto cm1 = std::make_unique<cv::Mat>();
        auto dc1 = std::make_unique<cv::Mat>();
        auto cm2 = std::make_unique<cv::Mat>();
        auto dc2 = std::make_unique<cv::Mat>();
        auto rMat = std::make_unique<cv::Mat>();
        auto tMat = std::make_unique<cv::Mat>();
        auto eMat = std::make_unique<cv::Mat>();
        auto fMat = std::make_unique<cv::Mat>();
        auto pvErr = std::make_unique<cv::Mat>();
        cv::stereoCalibrate(objPts, imgPts1, imgPts2, *cm1, *dc1, *cm2, *dc2, cv::Size(hSize, vSize), *rMat, *tMat, *eMat, *fMat, *pvErr, flags);
        *cameraMatrix1 = cm1.release();
        *distCoeffs1 = dc1.release();
        *cameraMatrix2 = cm2.release();
        *distCoeffs2 = dc2.release();
        *R = rMat.release();
        *T = tMat.release();
        *E = eMat.release();
        *F = fMat.release();
        *perViewErrors = pvErr.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_calib3d_solveP3P(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int *solutionCount, int flags)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> rv, tv;
        int n = cv::solveP3P(*objectPoints, *imagePoints, *cameraMatrix, *distCoeffs, rv, tv, flags);
        auto rvecsOutput = prepareMatOutputs(rv, rvecs);
        auto tvecsOutput = prepareMatOutputs(tv, tvecs);
        if (solutionCount) *solutionCount = n;
        publishMatOutputs(rvecsOutput, rvecs);
        publishMatOutputs(tvecsOutput, tvecs);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_solvePnPGeneric(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int *solutionCount, int useExtrinsicGuess, int flags, cv::Mat **rvec, cv::Mat **tvec, cv::Mat **reprojectionError)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> rv, tv;
        cv::Mat rvecGuess = (rvec && *rvec && useExtrinsicGuess) ? **rvec : cv::Mat();
        cv::Mat tvecGuess = (tvec && *tvec && useExtrinsicGuess) ? **tvec : cv::Mat();
        cv::Mat reprErr;
        int n = cv::solvePnPGeneric(*objectPoints, *imagePoints, *cameraMatrix, *distCoeffs, rv, tv, useExtrinsicGuess != 0, (cv::SolvePnPMethod)flags, rvecGuess, tvecGuess, reprErr);
        auto rvecsOutput = prepareMatOutputs(rv, rvecs);
        auto tvecsOutput = prepareMatOutputs(tv, tvecs);
        if (reprojectionError) {
            auto error = std::make_unique<cv::Mat>(std::move(reprErr));
            *reprojectionError = error.release();
        }
        if (solutionCount) *solutionCount = n;
        publishMatOutputs(rvecsOutput, rvecs);
        publishMatOutputs(tvecsOutput, tvecs);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_solvePnPRefineLM(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec)
{
    cv_clear_error();
    if (!objectPoints || !imagePoints || !cameraMatrix || !rvec || !tvec
        || !*rvec || !*tvec || *rvec == *tvec) {
        cv_set_error_literal("initial rotation and translation are required");
        return 0;
    }

    try {
        cv::Mat rv = (*rvec)->clone();
        cv::Mat tv = (*tvec)->clone();
        const cv::Mat distortion = distCoeffs ? *distCoeffs : cv::Mat();
        cv::solvePnPRefineLM(*objectPoints, *imagePoints, *cameraMatrix, distortion, rv, tv);
        **rvec = std::move(rv);
        **tvec = std::move(tv);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_solvePnPRefineVVS(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec, double lambda, int maxCount, double epsilon)
{
    cv_clear_error();
    if (!objectPoints || !imagePoints || !cameraMatrix || !rvec || !tvec
        || !*rvec || !*tvec || *rvec == *tvec) {
        cv_set_error_literal("initial rotation and translation are required");
        return 0;
    }

    try {
        cv::TermCriteria criteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, maxCount, epsilon);
        cv::Mat rv = (*rvec)->clone();
        cv::Mat tv = (*tvec)->clone();
        const cv::Mat distortion = distCoeffs ? *distCoeffs : cv::Mat();
        cv::solvePnPRefineVVS(*objectPoints, *imagePoints, *cameraMatrix, distortion, rv, tv, criteria, lambda);
        **rvec = std::move(rv);
        **tvec = std::move(tv);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_validateDisparity(cv::Mat **disparity, cv::Mat **cost, int minDisparity, int numberOfDisparities, int disp12MaxDiff)
{
    cv_clear_error();
    if (!disparity || !*disparity || !cost || !*cost || *disparity == *cost) {
        cv_set_error_literal("invalid disparity or cost matrix");
        return 0;
    }

    try {
        cv::Mat result = (*disparity)->clone();
        cv::validateDisparity(result, **cost, minDisparity, numberOfDisparities, disp12MaxDiff);
        **disparity = std::move(result);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_calib3d_createStereoBM(int numDisparities, int blockSize)
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::StereoBM>(cv::StereoBM::create(numDisparities, blockSize));
    } catch (cv::Exception &e) {
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

CVAPI int cv_calib3d_deleteStereoBM(void *bm)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMCompute(void *bm, cv::Mat *left, cv::Mat *right, cv::Mat **disparity)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        auto disp = std::make_unique<cv::Mat>();
        (*ptr)->compute(*left, *right, *disp);
        *disparity = disp.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetMinDisparity(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getMinDisparity();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetMinDisparity(void *bm, int minDisparity)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setMinDisparity(minDisparity);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetNumDisparities(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getNumDisparities();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetNumDisparities(void *bm, int numDisparities)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setNumDisparities(numDisparities);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetBlockSize(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getBlockSize();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetBlockSize(void *bm, int blockSize)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setBlockSize(blockSize);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetSpeckleWindowSize(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getSpeckleWindowSize();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetSpeckleWindowSize(void *bm, int speckleWindowSize)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setSpeckleWindowSize(speckleWindowSize);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetSpeckleRange(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getSpeckleRange();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetSpeckleRange(void *bm, int speckleRange)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setSpeckleRange(speckleRange);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetDisp12MaxDiff(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getDisp12MaxDiff();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetDisp12MaxDiff(void *bm, int disp12MaxDiff)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setDisp12MaxDiff(disp12MaxDiff);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetPreFilterType(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getPreFilterType();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetPreFilterType(void *bm, int preFilterType)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setPreFilterType(preFilterType);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetPreFilterSize(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getPreFilterSize();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetPreFilterSize(void *bm, int preFilterSize)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setPreFilterSize(preFilterSize);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetPreFilterCap(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getPreFilterCap();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetPreFilterCap(void *bm, int preFilterCap)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setPreFilterCap(preFilterCap);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetTextureThreshold(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getTextureThreshold();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetTextureThreshold(void *bm, int textureThreshold)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setTextureThreshold(textureThreshold);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMGetUniquenessRatio(void *bm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        return (*ptr)->getUniquenessRatio();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoBMSetUniquenessRatio(void *bm, int uniquenessRatio)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoBM>*>(bm);
        (*ptr)->setUniquenessRatio(uniquenessRatio);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_calib3d_createStereoSGBM(int minDisparity, int numDisparities, int blockSize, int P1, int P2, int disp12MaxDiff, int preFilterCap, int uniquenessRatio, int speckleWindowSize, int speckleRange, int mode)
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::StereoSGBM>(cv::StereoSGBM::create(minDisparity, numDisparities, blockSize, P1, P2, disp12MaxDiff, preFilterCap, uniquenessRatio, speckleWindowSize, speckleRange, mode));
    } catch (cv::Exception &e) {
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

CVAPI int cv_calib3d_deleteStereoSGBM(void *sgbm)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMCompute(void *sgbm, cv::Mat *left, cv::Mat *right, cv::Mat **disparity)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        auto disp = std::make_unique<cv::Mat>();
        (*ptr)->compute(*left, *right, *disp);
        *disparity = disp.release();
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMGetMode(void *sgbm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return (*ptr)->getMode();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMSetMode(void *sgbm, int mode)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        (*ptr)->setMode(mode);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMGetP1(void *sgbm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return (*ptr)->getP1();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMSetP1(void *sgbm, int P1)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        (*ptr)->setP1(P1);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMGetP2(void *sgbm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return (*ptr)->getP2();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMSetP2(void *sgbm, int P2)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        (*ptr)->setP2(P2);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMGetMinDisparity(void *sgbm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return (*ptr)->getMinDisparity();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMSetMinDisparity(void *sgbm, int minDisparity)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        (*ptr)->setMinDisparity(minDisparity);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMGetNumDisparities(void *sgbm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return (*ptr)->getNumDisparities();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMSetNumDisparities(void *sgbm, int numDisparities)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        (*ptr)->setNumDisparities(numDisparities);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMGetUniquenessRatio(void *sgbm)
{
    cv_clear_error();
    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        return (*ptr)->getUniquenessRatio();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_calib3d_stereoSGBMSetUniquenessRatio(void *sgbm, int uniquenessRatio)
{
    cv_clear_error();

    try {
        auto* ptr = static_cast<cv::Ptr<cv::StereoSGBM>*>(sgbm);
        (*ptr)->setUniquenessRatio(uniquenessRatio);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
