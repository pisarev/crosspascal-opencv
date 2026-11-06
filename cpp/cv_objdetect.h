
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_OBJDETECT_H
#define CV_OBJDETECT_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/objdetect.hpp>

CVAPI int cv_objdetect_createHOG(CVSize winSize, CVSize blockSize, CVSize blockStride, CVSize cellSize, int nbins, void **handle);
CVAPI int cv_objdetect_deleteHOG(void *hog);
CVAPI int cv_objdetect_calcHistogram(void *hog, cv::Mat *image, CVSize winStride, CVSize padding, GetData get, void *data);

CVAPI int cv_objdetect_createCascadeClassifier(const char *filename, void **handle);
CVAPI int cv_objdetect_deleteCascadeClassifier(void *classifier);
CVAPI int cv_objdetect_cascadeDetectMultiScale(void *classifier, cv::Mat *image, double scaleFactor, int minNeighbors, int flags, CVSize minSize, CVSize maxSize, GetData get, void *data);
CVAPI int cv_objdetect_hogDetectMultiScale(void *hog, cv::Mat *image, double hitThreshold, CVSize winStride, CVSize padding, double scale, double finalThreshold, int useMeanShiftGrouping, GetData get, void *data);
CVAPI int cv_objdetect_hogSetSVMDetector(void *hog, void *detector, int count);

CVAPI int cv_objdetect_createQRCodeDetector(void **handle);
CVAPI int cv_objdetect_deleteQRCodeDetector(void *detector);
CVAPI int cv_objdetect_qrCodeDetect(void *detector, cv::Mat *image, cv::Mat **points, int *detected);
CVAPI int cv_objdetect_qrCodeDetectAndDecode(void *detector, cv::Mat *image, cv::Mat **points, char *decodedInfo, int *maxLen);

CVAPI int cv_objdetect_hogCompute(void *hog, cv::Mat *image, cv::Mat **descriptors, int winStrideW, int winStrideH, int paddingW, int paddingH);
CVAPI int cv_objdetect_hogGetDefaultPeopleDetector(cv::Mat **detector);

CVAPI int cv_objdetect_cascadeClassifierLoad(void *classifier, const char *filename);
CVAPI int cv_objdetect_cascadeClassifierEmpty(void *classifier);

CVAPI int cv_objdetect_qrCodeDetectMulti(void *detector, cv::Mat *image, cv::Mat **points);
CVAPI int cv_objdetect_qrCodeDecodeCurved(void *detector, cv::Mat *image, cv::Mat **points, char *result, int resultMaxLen, cv::Mat **straightQrCode);

CVAPI int cv_objdetect_groupRectangles(CVRect *rectList, int *count, int groupThreshold, double eps);
CVAPI void *cv_objdetect_createFaceDetectorYN(const char *model, const char *config, int inputW, int inputH, float scoreThreshold, float nmsThreshold, int topK, int backendId, int targetId);
CVAPI int cv_objdetect_deleteFaceDetectorYN(void *detector);
CVAPI int cv_objdetect_faceDetectorYNDetect(void *detector, cv::Mat *image, cv::Mat **faces);
CVAPI void *cv_objdetect_createFaceRecognizerSF(const char *model, const char *config, int backendId, int targetId);

CVAPI int cv_objdetect_hogDetect(void *hog, cv::Mat *image, double hitThreshold, CVSize winStride, CVSize padding, GetData get, void *data);
CVAPI int cv_objdetect_hogGetWinSize(void *hog, CVSize *value);
CVAPI int cv_objdetect_hogSetWinSize(void *hog, CVSize value);
CVAPI int cv_objdetect_hogGetBlockSize(void *hog, CVSize *value);
CVAPI int cv_objdetect_hogSetBlockSize(void *hog, CVSize value);
CVAPI int cv_objdetect_hogGetBlockStride(void *hog, CVSize *value);
CVAPI int cv_objdetect_hogSetBlockStride(void *hog, CVSize value);
CVAPI int cv_objdetect_hogGetCellSize(void *hog, CVSize *value);
CVAPI int cv_objdetect_hogSetCellSize(void *hog, CVSize value);
CVAPI int cv_objdetect_hogGetNbins(void *hog, int *value);
CVAPI int cv_objdetect_hogSetNbins(void *hog, int value);
CVAPI int cv_objdetect_hogGetWinSigma(void *hog, double *value);
CVAPI int cv_objdetect_hogSetWinSigma(void *hog, double value);
CVAPI int cv_objdetect_hogGetL2HysThreshold(void *hog, double *value);
CVAPI int cv_objdetect_hogSetL2HysThreshold(void *hog, double value);
CVAPI int cv_objdetect_hogGetGammaCorrection(void *hog, int *value);
CVAPI int cv_objdetect_hogSetGammaCorrection(void *hog, int value);
CVAPI int cv_objdetect_hogGetNlevels(void *hog, int *value);
CVAPI int cv_objdetect_hogSetNlevels(void *hog, int value);
CVAPI int cv_objdetect_hogGetSignedGradient(void *hog, int *value);
CVAPI int cv_objdetect_hogSetSignedGradient(void *hog, int value);
CVAPI int cv_objdetect_hogSetSVMDetectorDefault(void *hog);
CVAPI int cv_objdetect_hogSave(void *hog, const char *filename);
CVAPI int cv_objdetect_hogLoad(void *hog, const char *filename);

CVAPI int cv_objdetect_faceDetectorYNSetInputSize(void *detector, int width, int height);
CVAPI int cv_objdetect_faceDetectorYNGetScoreThreshold(void *detector, float *value);
CVAPI int cv_objdetect_faceDetectorYNSetScoreThreshold(void *detector, float value);
CVAPI int cv_objdetect_faceDetectorYNGetNMSThreshold(void *detector, float *value);
CVAPI int cv_objdetect_faceDetectorYNSetNMSThreshold(void *detector, float value);
CVAPI int cv_objdetect_faceDetectorYNGetTopK(void *detector, int *value);
CVAPI int cv_objdetect_faceDetectorYNSetTopK(void *detector, int value);

CVAPI int cv_objdetect_deleteFaceRecognizerSF(void *recognizer);
CVAPI int cv_objdetect_faceRecognizerSFAlignCrop(void *recognizer, cv::Mat *srcImg, cv::Mat **faceBox, cv::Mat **alignedImg);
CVAPI int cv_objdetect_faceRecognizerSFFeature(void *recognizer, cv::Mat *alignedImg, cv::Mat **faceFeature);
CVAPI int cv_objdetect_faceRecognizerSFMatch(void *recognizer, cv::Mat *faceFeature1, cv::Mat *faceFeature2, int disType, double *distance);

#endif
