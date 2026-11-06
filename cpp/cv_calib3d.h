
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_CALIB3D_H
#define CV_CALIB3D_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/calib3d.hpp>

CVAPI int cv_calib3d_calibrateCamera(cv::Mat **objectPoints, cv::Mat **imagePoints, int imageCount, CVSize imageSize, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int flags, double *reprojError);
CVAPI int cv_calib3d_findChessboardCorners(cv::Mat *image, CVSize patternSize, cv::Mat **corners, int flags, int *found);
CVAPI int cv_calib3d_drawChessboardCorners(cv::Mat **image, CVSize patternSize, cv::Mat *corners, int patternWasFound);

CVAPI int cv_calib3d_solvePnP(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess, int flags);
CVAPI int cv_calib3d_solvePnPRansac(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess, int iterationsCount, float reprojectionError, double confidence, cv::Mat **inliers, int flags);
CVAPI int cv_calib3d_projectPoints(cv::Mat *objectPoints, cv::Mat *rvec, cv::Mat *tvec, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **imagePoints);
CVAPI int cv_calib3d_rodrigues(cv::Mat *source, cv::Mat **target, cv::Mat **jacobian);

CVAPI int cv_calib3d_stereoCalibrate(cv::Mat **objectPoints, cv::Mat **imagePoints1, cv::Mat **imagePoints2, int imageCount, cv::Mat **cameraMatrix1, cv::Mat **distCoeffs1, cv::Mat **cameraMatrix2, cv::Mat **distCoeffs2, CVSize imageSize, cv::Mat **R, cv::Mat **T, cv::Mat **E, cv::Mat **F, int flags, double *reprojError);
CVAPI int cv_calib3d_stereoRectify(cv::Mat *cameraMatrix1, cv::Mat *distCoeffs1, cv::Mat *cameraMatrix2, cv::Mat *distCoeffs2, CVSize imageSize, cv::Mat *R, cv::Mat *T, cv::Mat **R1, cv::Mat **R2, cv::Mat **P1, cv::Mat **P2, cv::Mat **Q, int flags, double alpha, CVSize newImageSize);
CVAPI int cv_calib3d_initUndistortRectifyMap(cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *R, cv::Mat *newCameraMatrix, CVSize size, int m1type, cv::Mat **map1, cv::Mat **map2);
CVAPI int cv_calib3d_undistort(cv::Mat *source, cv::Mat **target, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *newCameraMatrix);

CVAPI int cv_calib3d_findFundamentalMat(cv::Mat *points1, cv::Mat *points2, cv::Mat **target, int method, double ransacReprojThreshold, double confidence, cv::Mat **mask);
CVAPI int cv_calib3d_findEssentialMat(cv::Mat *points1, cv::Mat *points2, cv::Mat *cameraMatrix, int method, double prob, double threshold, cv::Mat **mask, cv::Mat **target);
CVAPI int cv_calib3d_decomposeEssentialMat(cv::Mat *E, cv::Mat **R1, cv::Mat **R2, cv::Mat **T);
CVAPI int cv_calib3d_triangulatePoints(cv::Mat *projMatr1, cv::Mat *projMatr2, cv::Mat *projPoints1, cv::Mat *projPoints2, cv::Mat **points4D);

CVAPI int cv_calib3d_findChessboardCornersSB(cv::Mat *image, int patternW, int patternH, cv::Mat **corners, int flags);
CVAPI int cv_calib3d_findCirclesGrid(cv::Mat *image, int patternW, int patternH, cv::Mat **centers, int flags);

CVAPI int cv_calib3d_recoverPose(cv::Mat *E, cv::Mat *points1, cv::Mat *points2, cv::Mat *cameraMatrix, cv::Mat **R, cv::Mat **T, cv::Mat **mask);

CVAPI int cv_calib3d_computeCorrespondEpilines(cv::Mat *points, int whichImage, cv::Mat *F, cv::Mat **lines);
CVAPI int cv_calib3d_convertPointsFromHomogeneous(cv::Mat *source, cv::Mat **target);
CVAPI int cv_calib3d_convertPointsToHomogeneous(cv::Mat *source, cv::Mat **target);

CVAPI int cv_calib3d_undistortPoints(cv::Mat *source, cv::Mat **target, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *R, cv::Mat *P);

CVAPI int cv_calib3d_estimateAffine3D(cv::Mat *source, cv::Mat *target, cv::Mat **out, cv::Mat **inliers, double ransacThreshold, double confidence);
CVAPI int cv_calib3d_estimateAffine2D(cv::Mat *source, cv::Mat *target, cv::Mat **inliers, int method, double ransacReprojThreshold, int maxIters, double confidence, int refineIters);
CVAPI int cv_calib3d_estimateAffine2DWithTransform(cv::Mat *source, cv::Mat *target, cv::Mat **inliers, int method, double ransacReprojThreshold, int maxIters, double confidence, int refineIters, cv::Mat **output);

CVAPI int cv_calib3d_getOptimalNewCameraMatrix(cv::Mat *cameraMatrix, cv::Mat *distCoeffs, int imageW, int imageH, double alpha, int newImageW, int newImageH, CVRect *validPixROI, int centerPrincipalPoint, cv::Mat **result);

CVAPI int cv_calib3d_calibrateCameraExtended(cv::Mat **objectPoints, cv::Mat **imagePoints, int imageCount, int hSize, int vSize, cv::Mat **cameraMatrix, cv::Mat **distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, cv::Mat **stdDeviationsIntrinsics, cv::Mat **stdDeviationsExtrinsics, cv::Mat **perViewErrors, int flags);
CVAPI int cv_calib3d_calibrateHandEye(cv::Mat **R_gripper2base, cv::Mat **t_gripper2base, cv::Mat **R_target2cam, cv::Mat **t_target2cam, int count, cv::Mat **R_cam2gripper, cv::Mat **t_cam2gripper, int method);
CVAPI int cv_calib3d_calibrateRobotWorldHandEye(cv::Mat **R_world2cam, cv::Mat **t_world2cam, cv::Mat **R_base2gripper, cv::Mat **t_base2gripper, int count, cv::Mat **R_base2world, cv::Mat **t_base2world, cv::Mat **R_gripper2cam, cv::Mat **t_gripper2cam, int method);
CVAPI int cv_calib3d_composeRT(cv::Mat *rvec1, cv::Mat *tvec1, cv::Mat *rvec2, cv::Mat *tvec2, cv::Mat **rvec3, cv::Mat **tvec3);
CVAPI int cv_calib3d_decomposeHomographyMat(cv::Mat *H, cv::Mat *K, cv::Mat **rotations, cv::Mat **translations, cv::Mat **normals, int *count);

CVAPI int cv_calib3d_decomposeProjectionMatrix(cv::Mat *projMatrix, cv::Mat **cameraMatrix, cv::Mat **rotMatrix, cv::Mat **transVect);
CVAPI int cv_calib3d_drawFrameAxes(cv::Mat **image, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *rvec, cv::Mat *tvec, float length, int thickness);
CVAPI int cv_calib3d_estimateAffinePartial2D(cv::Mat *source, cv::Mat *target, cv::Mat **inliers, int method, double ransacReprojThreshold, int maxIters, double confidence, int refineIters, cv::Mat **output);
CVAPI int cv_calib3d_estimateTranslation3D(cv::Mat *source, cv::Mat *target, cv::Mat **out, cv::Mat **inliers, double ransacThreshold, double confidence);
CVAPI int cv_calib3d_filterSpeckles(cv::Mat **image, double newVal, int maxSpeckleSize, double maxDiff, cv::Mat **buf);

CVAPI int cv_calib3d_find4QuadCornerSubpix(cv::Mat *image, cv::Mat **corners, int regionSizeW, int regionSizeH);
CVAPI int cv_calib3d_findTransformECC(cv::Mat *templateImage, cv::Mat *inputImage, cv::Mat **warpMatrix, int motionType, int maxCount, double epsilon, cv::Mat *inputMask, int gaussFiltSize);
CVAPI int cv_calib3d_initCameraMatrix2D(cv::Mat **objectPoints, cv::Mat **imagePoints, int count, int hSize, int vSize, double aspectRatio, cv::Mat **cameraMatrix);
CVAPI int cv_calib3d_initInverseRectificationMap(cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat *R, cv::Mat *newCameraMatrix, int hSize, int vSize, int m1type, cv::Mat **map1, cv::Mat **map2);
CVAPI int cv_calib3d_matMulDeriv(cv::Mat *A, cv::Mat *B, cv::Mat **dABdA, cv::Mat **dABdB);

CVAPI int cv_calib3d_RQDecomp3x3(cv::Mat *source, cv::Mat **mtxR, cv::Mat **mtxQ, cv::Mat **Qx, cv::Mat **Qy, cv::Mat **Qz);
CVAPI int cv_calib3d_reprojectImageTo3D(cv::Mat *disparity, cv::Mat **image3D, cv::Mat *Q, int handleMissingValues, int ddepth);
CVAPI int cv_calib3d_sampsonDistance(cv::Mat *pt1, cv::Mat *pt2, cv::Mat *F, double *distance);
CVAPI int cv_calib3d_stereoRectifyUncalibrated(cv::Mat *points1, cv::Mat *points2, cv::Mat *F, int imgW, int imgH, cv::Mat **H1, cv::Mat **H2, double threshold);
CVAPI int cv_calib3d_stereoCalibrateExtended(cv::Mat **objectPoints, cv::Mat **imagePoints1, cv::Mat **imagePoints2, int count, cv::Mat **cameraMatrix1, cv::Mat **distCoeffs1, cv::Mat **cameraMatrix2, cv::Mat **distCoeffs2, int hSize, int vSize, cv::Mat **R, cv::Mat **T, cv::Mat **E, cv::Mat **F, cv::Mat **perViewErrors, int flags);

CVAPI int cv_calib3d_solveP3P(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int *solutionCount, int flags);
CVAPI int cv_calib3d_solvePnPGeneric(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvecs, cv::Mat **tvecs, int *solutionCount, int useExtrinsicGuess, int flags, cv::Mat **rvec, cv::Mat **tvec, cv::Mat **reprojectionError);
CVAPI int cv_calib3d_solvePnPRefineLM(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec);
CVAPI int cv_calib3d_solvePnPRefineVVS(cv::Mat *objectPoints, cv::Mat *imagePoints, cv::Mat *cameraMatrix, cv::Mat *distCoeffs, cv::Mat **rvec, cv::Mat **tvec, double lambda, int maxCount, double epsilon);
CVAPI int cv_calib3d_validateDisparity(cv::Mat **disparity, cv::Mat **cost, int minDisparity, int numberOfDisparities, int disp12MaxDiff);

CVAPI void *cv_calib3d_createStereoBM(int numDisparities, int blockSize);
CVAPI int cv_calib3d_deleteStereoBM(void *bm);
CVAPI int cv_calib3d_stereoBMCompute(void *bm, cv::Mat *left, cv::Mat *right, cv::Mat **disparity);
CVAPI int cv_calib3d_stereoBMGetMinDisparity(void *bm);
CVAPI int cv_calib3d_stereoBMSetMinDisparity(void *bm, int minDisparity);
CVAPI int cv_calib3d_stereoBMGetNumDisparities(void *bm);
CVAPI int cv_calib3d_stereoBMSetNumDisparities(void *bm, int numDisparities);
CVAPI int cv_calib3d_stereoBMGetBlockSize(void *bm);
CVAPI int cv_calib3d_stereoBMSetBlockSize(void *bm, int blockSize);
CVAPI int cv_calib3d_stereoBMGetSpeckleWindowSize(void *bm);
CVAPI int cv_calib3d_stereoBMSetSpeckleWindowSize(void *bm, int speckleWindowSize);
CVAPI int cv_calib3d_stereoBMGetSpeckleRange(void *bm);
CVAPI int cv_calib3d_stereoBMSetSpeckleRange(void *bm, int speckleRange);
CVAPI int cv_calib3d_stereoBMGetDisp12MaxDiff(void *bm);
CVAPI int cv_calib3d_stereoBMSetDisp12MaxDiff(void *bm, int disp12MaxDiff);
CVAPI int cv_calib3d_stereoBMGetPreFilterType(void *bm);
CVAPI int cv_calib3d_stereoBMSetPreFilterType(void *bm, int preFilterType);
CVAPI int cv_calib3d_stereoBMGetPreFilterSize(void *bm);
CVAPI int cv_calib3d_stereoBMSetPreFilterSize(void *bm, int preFilterSize);
CVAPI int cv_calib3d_stereoBMGetPreFilterCap(void *bm);
CVAPI int cv_calib3d_stereoBMSetPreFilterCap(void *bm, int preFilterCap);
CVAPI int cv_calib3d_stereoBMGetTextureThreshold(void *bm);
CVAPI int cv_calib3d_stereoBMSetTextureThreshold(void *bm, int textureThreshold);
CVAPI int cv_calib3d_stereoBMGetUniquenessRatio(void *bm);
CVAPI int cv_calib3d_stereoBMSetUniquenessRatio(void *bm, int uniquenessRatio);

CVAPI void *cv_calib3d_createStereoSGBM(int minDisparity, int numDisparities, int blockSize, int P1, int P2, int disp12MaxDiff, int preFilterCap, int uniquenessRatio, int speckleWindowSize, int speckleRange, int mode);
CVAPI int cv_calib3d_deleteStereoSGBM(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMCompute(void *sgbm, cv::Mat *left, cv::Mat *right, cv::Mat **disparity);
CVAPI int cv_calib3d_stereoSGBMGetMode(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMSetMode(void *sgbm, int mode);
CVAPI int cv_calib3d_stereoSGBMGetP1(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMSetP1(void *sgbm, int P1);
CVAPI int cv_calib3d_stereoSGBMGetP2(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMSetP2(void *sgbm, int P2);
CVAPI int cv_calib3d_stereoSGBMGetMinDisparity(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMSetMinDisparity(void *sgbm, int minDisparity);
CVAPI int cv_calib3d_stereoSGBMGetNumDisparities(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMSetNumDisparities(void *sgbm, int numDisparities);
CVAPI int cv_calib3d_stereoSGBMGetUniquenessRatio(void *sgbm);
CVAPI int cv_calib3d_stereoSGBMSetUniquenessRatio(void *sgbm, int uniquenessRatio);

#endif
