
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_DNN_H
#define CV_DNN_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/dnn.hpp>

CVAPI int cv_dnn_createNet(const char *configFile, const char *weightsFile, void **handle);
CVAPI int cv_dnn_deleteNet(void *net);
CVAPI int cv_dnn_createDarknet(const char *cfgFile, const char *weightsFile, void **handle);
CVAPI int cv_dnn_createOpenVINO(const char *modelFile, const char *configFile, void **handle);
CVAPI int cv_dnn_readNetFromONNX(const char *onnxFile, void **handle);
CVAPI int cv_dnn_readNetFromTensorflow(const char *model, const char *config, void **handle);
CVAPI int cv_dnn_readNetFromCaffe(const char *prototxt, const char *caffeModel, void **handle);

CVAPI int cv_dnn_netSetInput(void *net, cv::Mat *blob, const char *name);
CVAPI int cv_dnn_netForward(void *net, const char *outputName, cv::Mat **target);
CVAPI int cv_dnn_netGetLayerNames(void *net, SetData set, void *data);

CVAPI int cv_dnn_blobFromImage(cv::Mat *image, cv::Mat **target, double scaleFactor, CVSize size, CVScalar *mean, int swapRB, int crop, int ddepth);

CVAPI int cv_dnn_onnxDetect(void *net, cv::Mat *image, float confThreshold, float nmsThreshold, SetData set, void *data);
CVAPI int cv_dnn_darknetDetect(void *net, cv::Mat *image, float confThreshold, float nmsThreshold, SetData set, void *data);
CVAPI int cv_dnn_detectSceneBox(void *net, cv::Mat *image, float confThreshold, float nmsThreshold, SetData set, void *data);

CVAPI int cv_dnn_nmsBoxes(void *boxes, void *scores, int count, float scoreThreshold, float nmsThreshold, int *indices, int *indicesCount, float eta, int topK);

CVAPI int cv_dnn_readNet(const char *model, const char *config, const char *framework, void **handle);
CVAPI int cv_dnn_readNetFromTorch(const char *model, int isBinary, int evaluate, void **handle);

CVAPI int cv_dnn_netSetPreferableBackend(void *net, int backendId);
CVAPI int cv_dnn_netSetPreferableTarget(void *net, int targetId);
CVAPI int cv_dnn_netEnableFusion(void *net, int fusion);
CVAPI int cv_dnn_netGetUnconnectedOutLayers(void *net, int *layers, int *count, int maxCount);
CVAPI int cv_dnn_netGetUnconnectedOutLayersNames(void *net, char **names, int *count, int maxCount);

CVAPI int cv_dnn_blobFromImages(cv::Mat **images, int imageCount, cv::Mat **blob, double scaleFactor, int hSize, int vSize, CVScalar *mean, int swapRB, int crop, int ddepth);
CVAPI int cv_dnn_imagesFromBlob(cv::Mat *blob, cv::Mat **images, int *count, int maxCount);

CVAPI int cv_dnn_netEmpty(void *net);

CVAPI int cv_dnn_netGetLayerCount(void *net);
CVAPI int cv_dnn_netDump(void *net, char *buffer, int maxLen);
CVAPI int cv_dnn_netGetPerfProfile(void *net, double *timings);
CVAPI int cv_dnn_netEnableWinograd(void *net, int useWinograd);

CVAPI void *cv_dnn_readNetFromDarknet(const char *cfgFile, const char *darknetModel);
CVAPI void *cv_dnn_readNetFromModelOptimizer(const char *xml, const char *bin);
CVAPI void *cv_dnn_readNetFromTFLite(const char *model);

CVAPI int cv_dnn_NMSBoxesBatched(void *bboxes, float *scores, int *classIds, int count, float scoreThreshold, float nmsThreshold, int *indices, int *indicesCount, float eta, int topK);
CVAPI int cv_dnn_NMSBoxesRotated(void *bboxes, float *scores, int count, float scoreThreshold, float nmsThreshold, int *indices, int *indicesCount, float eta, int topK);

CVAPI void *cv_dnn_createDetectionModel(const char *model, const char *config);
CVAPI void *cv_dnn_createDetectionModelFromNet(void *net);
CVAPI int cv_dnn_deleteDetectionModel(void *model);
CVAPI int cv_dnn_detectionModelDetect(void *model, cv::Mat *frame, int *classIds, float *confidences, void *boxes, int *count, int maxCount, float confThreshold, float nmsThreshold);
CVAPI int cv_dnn_detectionModelSetInputSize(void *model, int width, int height);
CVAPI int cv_dnn_detectionModelSetInputScale(void *model, double scale);
CVAPI int cv_dnn_detectionModelSetInputMean(void *model, CVScalar mean);
CVAPI int cv_dnn_detectionModelSetInputSwapRB(void *model, int swapRB);
CVAPI int cv_dnn_detectionModelSetInputCrop(void *model, int crop);

CVAPI void *cv_dnn_createClassificationModel(const char *model, const char *config);
CVAPI void *cv_dnn_createClassificationModelFromNet(void *net);
CVAPI int cv_dnn_deleteClassificationModel(void *model);
CVAPI int cv_dnn_classificationModelClassify(void *model, cv::Mat *frame, int *classId, float *conf);
CVAPI int cv_dnn_classificationModelSetInputSize(void *model, int width, int height);
CVAPI int cv_dnn_classificationModelSetInputScale(void *model, double scale);
CVAPI int cv_dnn_classificationModelSetInputMean(void *model, CVScalar mean);
CVAPI int cv_dnn_classificationModelSetInputSwapRB(void *model, int swapRB);

CVAPI void *cv_dnn_createSegmentationModel(const char *model, const char *config);
CVAPI void *cv_dnn_createSegmentationModelFromNet(void *net);
CVAPI int cv_dnn_deleteSegmentationModel(void *model);
CVAPI int cv_dnn_segmentationModelSegment(void *model, cv::Mat *frame, cv::Mat **mask);
CVAPI int cv_dnn_segmentationModelSetInputSize(void *model, int width, int height);
CVAPI int cv_dnn_segmentationModelSetInputScale(void *model, double scale);
CVAPI int cv_dnn_segmentationModelSetInputMean(void *model, CVScalar mean);
CVAPI int cv_dnn_segmentationModelSetInputSwapRB(void *model, int swapRB);

CVAPI void *cv_dnn_createTextRecognitionModel(const char *model, const char *config);
CVAPI int cv_dnn_deleteTextRecognitionModel(void *model);
CVAPI int cv_dnn_textRecognitionModelRecognize(void *model, cv::Mat *frame, char *result, int maxLen);
CVAPI int cv_dnn_textRecognitionModelSetVocabulary(void *model, const char *vocabulary);

CVAPI int cv_dnn_getAvailableTargets(int backend, int *targets, int *count, int maxCount);

#endif
