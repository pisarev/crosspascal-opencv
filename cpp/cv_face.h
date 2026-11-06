
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_FACE_H
#define CV_FACE_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/face.hpp>

CVAPI void *cv_face_createEigenFaceRecognizer(int numComponents, double threshold);
CVAPI int cv_face_deleteEigenFaceRecognizer(void *recognizer);

CVAPI void *cv_face_createFisherFaceRecognizer(int numComponents, double threshold);
CVAPI int cv_face_deleteFisherFaceRecognizer(void *recognizer);

CVAPI void *cv_face_createLBPHFaceRecognizer(int radius, int neighbors, int gridX, int gridY, double threshold);
CVAPI int cv_face_deleteLBPHFaceRecognizer(void *recognizer);
CVAPI int cv_face_lbphGetGridX(void *recognizer);
CVAPI int cv_face_lbphSetGridX(void *recognizer, int val);
CVAPI int cv_face_lbphGetGridY(void *recognizer);
CVAPI int cv_face_lbphSetGridY(void *recognizer, int val);
CVAPI int cv_face_lbphGetRadius(void *recognizer);
CVAPI int cv_face_lbphSetRadius(void *recognizer, int val);
CVAPI int cv_face_lbphGetNeighbors(void *recognizer);
CVAPI int cv_face_lbphSetNeighbors(void *recognizer, int val);
CVAPI double cv_face_lbphGetThreshold(void *recognizer);
CVAPI int cv_face_lbphSetThreshold(void *recognizer, double val);
CVAPI int cv_face_lbphGetHistograms(void *recognizer, cv::Mat **histograms);
CVAPI int cv_face_lbphGetLabels(void *recognizer, cv::Mat **labels);

CVAPI int cv_face_recognizerTrain(void *recognizer, cv::Mat **images, int *labels, int count);
CVAPI int cv_face_recognizerUpdate(void *recognizer, cv::Mat **images, int *labels, int count);
CVAPI int cv_face_recognizerPredict(void *recognizer, cv::Mat **src, int *label, double *confidence);
CVAPI int cv_face_recognizerSave(void *recognizer, const char *filename);
CVAPI int cv_face_recognizerLoad(void *recognizer, const char *filename);
CVAPI int cv_face_recognizerSetLabelInfo(void *recognizer, int label, const char *strInfo);
CVAPI int cv_face_recognizerGetLabelInfo(void *recognizer, int label, char *strInfo, int maxLen);
CVAPI double cv_face_recognizerGetThreshold(void *recognizer);
CVAPI int cv_face_recognizerSetThreshold(void *recognizer, double val);

CVAPI void *cv_face_createFacemarkLBF();
CVAPI void *cv_face_createFacemarkAAM();
CVAPI int cv_face_deleteFacemark(void *facemark);
CVAPI int cv_face_facemarkLoadModel(void *facemark, const char *model);
CVAPI int cv_face_facemarkFit(void *facemark, cv::Mat **image, CVRect *faces, int faceCount, cv::Mat **landmarks, int *landmarkCount);
CVAPI int cv_face_drawFacemarks(cv::Mat **image, cv::Mat **points, CVScalar color);

#endif
