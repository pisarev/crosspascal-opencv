
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_ARUCO_H
#define CV_ARUCO_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>

CVAPI void *cv_aruco_getPredefinedDictionary(int dict);
CVAPI void *cv_aruco_extendDictionary(int nMarkers, int markerSize, void *baseDictionary, int randomSeed);
CVAPI int cv_aruco_deleteDictionary(void *dictionary);

CVAPI int cv_aruco_generateImageMarker(void *dictionary, int id, int sidePixels, cv::Mat **img, int borderBits);

CVAPI void *cv_aruco_createArucoDetector(void *dictionary, void *parameters);
CVAPI int cv_aruco_deleteArucoDetector(void *detector);
CVAPI int cv_aruco_detectMarkers(void *detector, cv::Mat **image, cv::Mat **corners, int *cornerCount, cv::Mat **ids, cv::Mat **rejectedImgPoints, int *rejectedCount);

CVAPI int cv_aruco_drawDetectedMarkers(cv::Mat **image, cv::Mat **corners, int cornerCount, cv::Mat **ids, CVScalar borderColor);
CVAPI int cv_aruco_drawDetectedCornersCharuco(cv::Mat **image, cv::Mat **charucoCorners, cv::Mat **charucoIds, CVScalar cornerColor);
CVAPI int cv_aruco_drawDetectedDiamonds(cv::Mat **image, cv::Mat **diamondCorners, int count, cv::Mat **diamondIds, CVScalar borderColor);

CVAPI void *cv_aruco_createGridBoard(int markersX, int markersY, float markerLength, float markerSeparation, void *dictionary, cv::Mat **ids);
CVAPI void *cv_aruco_createCharucoBoard(int squaresX, int squaresY, float squareLength, float markerLength, void *dictionary);
CVAPI int cv_aruco_deleteBoard(void *board);
CVAPI int cv_aruco_drawPlanarBoard(void *board, int outW, int outH, cv::Mat **img, int marginSize, int borderBits);

CVAPI void *cv_aruco_createCharucoDetector(void *board, void *detectorParams);
CVAPI int cv_aruco_deleteCharucoDetector(void *detector);
CVAPI int cv_aruco_detectCharucoDiamond(cv::Mat **image, cv::Mat **markerCorners, int markerCount, cv::Mat **markerIds, float squareMarkerLengthRate, cv::Mat **diamondCorners, int *diamondCount, cv::Mat **diamondIds, cv::Mat **cameraMatrix, cv::Mat **distCoeffs);

CVAPI int cv_aruco_estimatePoseSingleMarkers(cv::Mat **corners, int cornerCount, float markerLength, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs);
CVAPI int cv_aruco_estimatePoseBoard(cv::Mat **corners, int cornerCount, cv::Mat **ids, void *board, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess);
CVAPI int cv_aruco_estimatePoseCharucoBoard(cv::Mat **charucoCorners, cv::Mat **charucoIds, void *board, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess);

CVAPI double cv_aruco_calibrateCameraAruco(cv::Mat **corners, cv::Mat **ids, cv::Mat **counter, void *board, int imageW, int imageH, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int flags);
CVAPI double cv_aruco_calibrateCameraCharuco(cv::Mat **charucoCorners, cv::Mat **charucoIds, int imageCount, void *board, int imageW, int imageH, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int flags);

CVAPI void *cv_aruco_createDetectorParameters();
CVAPI int cv_aruco_deleteDetectorParameters(void *params);
CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshWinSizeMin(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshWinSizeMax(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshWinSizeStep(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshConstant(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMinMarkerPerimeterRate(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMaxMarkerPerimeterRate(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersPolygonalApproxAccuracyRate(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMinCornerDistanceRate(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMinDistanceToBorder(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersMinMarkerDistanceRate(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersCornerRefinementMethod(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersCornerRefinementWinSize(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersCornerRefinementMaxIterations(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersCornerRefinementMinAccuracy(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMarkerBorderBits(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersPerspectiveRemovePixelPerCell(void *params, int value);
CVAPI int cv_aruco_setDetectorParametersPerspectiveRemoveIgnoredMarginPerCell(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMaxErroneousBitsInBorderRate(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersMinOtsuStdDev(void *params, double value);
CVAPI int cv_aruco_setDetectorParametersErrorCorrectionRate(void *params, double value);

#endif
