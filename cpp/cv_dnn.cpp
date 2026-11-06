
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_dnn.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

CVAPI int cv_dnn_createNet(const char *configFile, const char *weightsFile, void **handle)
{
    cv_clear_error();

    try {
        cv::dnn::Net net;
        if (configFile && strlen(configFile) > 0) {
            net = cv::dnn::readNet(weightsFile ? weightsFile : "", configFile ? configFile : "");
        }
        auto *ptr = new cv::dnn::Net(net);
        *handle = ptr;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_deleteNet(void *net)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
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

CVAPI int cv_dnn_createDarknet(const char *cfgFile, const char *weightsFile, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromDarknet(cfgFile, weightsFile ? weightsFile : ""));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_createOpenVINO(const char *modelFile, const char *configFile, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromModelOptimizer(modelFile, configFile));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_readNetFromONNX(const char *onnxFile, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromONNX(onnxFile));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_readNetFromTensorflow(const char *model, const char *config, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromTensorflow(model, config ? config : ""));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_readNetFromCaffe(const char *prototxt, const char *caffeModel, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromCaffe(prototxt, caffeModel ? caffeModel : ""));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netSetInput(void *net, cv::Mat *blob, const char *name)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        ptr->setInput(*blob, name ? name : "");
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netForward(void *net, const char *outputName, cv::Mat **target)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        cv::Mat *dst = new cv::Mat(ptr->forward(outputName ? outputName : ""));
        *target = dst;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netGetLayerNames(void *net, SetData set, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        std::vector<cv::String> layerNames = ptr->getLayerNames();
        if (set) {

            int count = (int)layerNames.size();
            void *buf = set(count, data);
            if (buf) {
                char **names = static_cast<char**>(buf);
                for (int i = 0; i < count; i++) {
                    if (names[i]) {
                        strncpy(names[i], layerNames[i].c_str(), 255);
                    }
                }
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

CVAPI int cv_dnn_blobFromImage(cv::Mat *image, cv::Mat **target, double scaleFactor, CVSize size, CVScalar *mean, int swapRB, int crop, int ddepth)
{
    cv_clear_error();

    try {
        cv::Mat *dst = new cv::Mat(cv::dnn::blobFromImage(*image, scaleFactor,
            cv::Size(size.cx, size.cy),
            cv::Scalar(mean->v0, mean->v1, mean->v2, mean->v3),
            swapRB != 0, crop != 0, ddepth));
        *target = dst;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

static void parseDarknetOutput(cv::dnn::Net &net, cv::Mat &image,
    std::vector<int> &classIds, std::vector<float> &confidences,
    std::vector<cv::Rect> &boxes, float confThreshold, float nmsThreshold)
{
    std::vector<cv::String> outNames = net.getUnconnectedOutLayersNames();
    std::vector<cv::Mat> outs;
    net.forward(outs, outNames);

    int imgW = image.cols;
    int imgH = image.rows;

    std::vector<int> tmpClassIds;
    std::vector<float> tmpConfidences;
    std::vector<cv::Rect> tmpBoxes;

    for (size_t i = 0; i < outs.size(); i++) {
        float *data = (float *)outs[i].data;
        for (int j = 0; j < outs[i].rows; j++, data += outs[i].cols) {
            int numClasses = outs[i].cols - 5;
            if (numClasses <= 0) continue;
            float objectness = data[4];
            if (objectness < confThreshold) continue;
            cv::Mat scores(1, numClasses, CV_32F, data + 5);
            cv::Point classIdPoint;
            double maxClassScore;
            cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);
            float confidence = objectness * (float)maxClassScore;
            if (confidence < confThreshold) continue;
            int cx = (int)(data[0] * imgW);
            int cy = (int)(data[1] * imgH);
            int w = (int)(data[2] * imgW);
            int h = (int)(data[3] * imgH);
            int left = cx - w / 2;
            int top = cy - h / 2;
            tmpClassIds.push_back(classIdPoint.x);
            tmpConfidences.push_back(confidence);
            tmpBoxes.push_back(cv::Rect(left, top, w, h));
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(tmpBoxes, tmpConfidences, confThreshold, nmsThreshold, indices);

    for (size_t i = 0; i < indices.size(); i++) {
        int idx = indices[i];
        classIds.push_back(tmpClassIds[idx]);
        confidences.push_back(tmpConfidences[idx]);
        boxes.push_back(tmpBoxes[idx]);
    }
}


static void parseOnnxOutput(cv::dnn::Net &net, cv::Mat &image,
    std::vector<int> &classIds, std::vector<float> &confidences,
    std::vector<cv::Rect> &boxes, float confThreshold, float nmsThreshold)
{
    cv::Mat output = net.forward();
    int imgW = image.cols;
    int imgH = image.rows;

    std::vector<int> tmpClassIds;
    std::vector<float> tmpConfidences;
    std::vector<cv::Rect> tmpBoxes;

    int rows = output.size[1];
    int cols = output.size[2];

    if (cols < rows && cols >= 5) {
        cv::Mat reshaped = output.reshape(1, {rows, cols});
        cv::transpose(reshaped, reshaped);
        rows = reshaped.rows;
        cols = reshaped.cols;

        float *data = (float *)reshaped.data;
        int numClasses = cols - 4;
        bool hasObjectness = (numClasses == cols - 5);

        for (int i = 0; i < rows; i++) {
            float *row = data + i * cols;
            if (hasObjectness) {
                float objectness = row[4];
                if (objectness < confThreshold) continue;
                numClasses = cols - 5;
                cv::Mat scores(1, numClasses, CV_32F, row + 5);
                cv::Point classIdPoint;
                double maxClassScore;
                cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);
                float confidence = objectness * (float)maxClassScore;
                if (confidence < confThreshold) continue;
                float cx = row[0], cy = row[1], w = row[2], h = row[3];
                int left = (int)((cx - w / 2.0f) * imgW);
                int top = (int)((cy - h / 2.0f) * imgH);
                tmpClassIds.push_back(classIdPoint.x);
                tmpConfidences.push_back(confidence);
                tmpBoxes.push_back(cv::Rect(left, top, (int)(w * imgW), (int)(h * imgH)));
            } else {
                numClasses = cols - 4;
                cv::Mat scores(1, numClasses, CV_32F, row + 4);
                cv::Point classIdPoint;
                double maxClassScore;
                cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);
                if ((float)maxClassScore < confThreshold) continue;
                float cx = row[0], cy = row[1], w = row[2], h = row[3];
                int left = (int)((cx - w / 2.0f) * imgW);
                int top = (int)((cy - h / 2.0f) * imgH);
                tmpClassIds.push_back(classIdPoint.x);
                tmpConfidences.push_back((float)maxClassScore);
                tmpBoxes.push_back(cv::Rect(left, top, (int)(w * imgW), (int)(h * imgH)));
            }
        }
    } else {
        float *data = (float *)output.ptr<float>(0);
        int numClasses = cols - 5;
        if (numClasses <= 0) {
            if (output.dims == 4 && output.size[3] == 7) {
                int numDetections = output.size[2];
                float *detData = (float *)output.data;
                for (int i = 0; i < numDetections; i++) {
                    float conf = detData[i * 7 + 2];
                    if (conf < confThreshold) continue;
                    int classId = (int)detData[i * 7 + 1];
                    int left = (int)(detData[i * 7 + 3] * imgW);
                    int top = (int)(detData[i * 7 + 4] * imgH);
                    int right = (int)(detData[i * 7 + 5] * imgW);
                    int bottom = (int)(detData[i * 7 + 6] * imgH);
                    tmpClassIds.push_back(classId);
                    tmpConfidences.push_back(conf);
                    tmpBoxes.push_back(cv::Rect(left, top, right - left, bottom - top));
                }
            }
        } else {
            for (int i = 0; i < rows; i++, data += cols) {
                float objectness = data[4];
                if (objectness < confThreshold) continue;
                cv::Mat scores(1, numClasses, CV_32F, data + 5);
                cv::Point classIdPoint;
                double maxClassScore;
                cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);
                float confidence = objectness * (float)maxClassScore;
                if (confidence < confThreshold) continue;
                float cx = data[0], cy = data[1], w = data[2], h = data[3];
                int left = (int)((cx - w / 2.0f) * imgW);
                int top = (int)((cy - h / 2.0f) * imgH);
                tmpClassIds.push_back(classIdPoint.x);
                tmpConfidences.push_back(confidence);
                tmpBoxes.push_back(cv::Rect(left, top, (int)(w * imgW), (int)(h * imgH)));
            }
        }
    }

    std::vector<int> indices;
    if (!tmpBoxes.empty()) {
        cv::dnn::NMSBoxes(tmpBoxes, tmpConfidences, confThreshold, nmsThreshold, indices);
    }

    for (size_t i = 0; i < indices.size(); i++) {
        int idx = indices[i];
        classIds.push_back(tmpClassIds[idx]);
        confidences.push_back(tmpConfidences[idx]);
        boxes.push_back(tmpBoxes[idx]);
    }
}

CVAPI int cv_dnn_onnxDetect(void *net, cv::Mat *image, float confThreshold, float nmsThreshold, SetData set, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        cv::Mat blob = cv::dnn::blobFromImage(*image, 1.0 / 255.0, cv::Size(640, 640),
            cv::Scalar(0, 0, 0), true, false);
        ptr->setInput(blob);

        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;
        parseOnnxOutput(*ptr, *image, classIds, confidences, boxes, confThreshold, nmsThreshold);

        if (set) {
            int n = (int)classIds.size();
            void *buf = set(n, data);
            if (buf) {
                CVObject *objects = static_cast<CVObject*>(buf);
                for (int i = 0; i < n; i++) {
                    objects[i].rect.x = boxes[i].x;
                    objects[i].rect.y = boxes[i].y;
                    objects[i].rect.hSize = boxes[i].width;
                    objects[i].rect.vSize = boxes[i].height;
                    objects[i].id = classIds[i];
                    objects[i].confidence = confidences[i];
                }
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

CVAPI int cv_dnn_darknetDetect(void *net, cv::Mat *image, float confThreshold, float nmsThreshold, SetData set, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        cv::Mat blob = cv::dnn::blobFromImage(*image, 1.0 / 255.0, cv::Size(416, 416),
            cv::Scalar(0, 0, 0), true, false);
        ptr->setInput(blob);

        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;
        parseDarknetOutput(*ptr, *image, classIds, confidences, boxes, confThreshold, nmsThreshold);

        if (set) {
            int n = (int)classIds.size();
            void *buf = set(n, data);
            if (buf) {
                CVObject *objects = static_cast<CVObject*>(buf);
                for (int i = 0; i < n; i++) {
                    objects[i].rect.x = boxes[i].x;
                    objects[i].rect.y = boxes[i].y;
                    objects[i].rect.hSize = boxes[i].width;
                    objects[i].rect.vSize = boxes[i].height;
                    objects[i].id = classIds[i];
                    objects[i].confidence = confidences[i];
                }
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

CVAPI int cv_dnn_detectSceneBox(void *net, cv::Mat *image, float confThreshold, float nmsThreshold, SetData set, void *data)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        cv::Mat blob = cv::dnn::blobFromImage(*image, 1.0 / 255.0, cv::Size(640, 640),
            cv::Scalar(0, 0, 0), true, false);
        ptr->setInput(blob);

        cv::Mat output = ptr->forward();
        int imgW = image->cols;
        int imgH = image->rows;

        std::vector<float> tmpConfidences;
        std::vector<cv::RotatedRect> tmpRotRects;

        int rows = output.size[1];
        int cols = output.size[2];
        float *odata = (float *)output.ptr<float>(0);

        for (int i = 0; i < rows; i++, odata += cols) {
            float conf = odata[4];
            if (conf < confThreshold) continue;
            float cx = odata[0] * imgW;
            float cy = odata[1] * imgH;
            float w = odata[2] * imgW;
            float h = odata[3] * imgH;
            float angle = (cols > 5) ? odata[5] : 0.0f;
            tmpConfidences.push_back(conf);
            tmpRotRects.push_back(cv::RotatedRect(cv::Point2f(cx, cy), cv::Size2f(w, h), angle));
        }

        std::vector<int> indices;
        if (!tmpRotRects.empty()) {
            std::vector<cv::Rect> boundingBoxes;
            for (const auto &rr : tmpRotRects) {
                boundingBoxes.push_back(rr.boundingRect());
            }
            cv::dnn::NMSBoxes(boundingBoxes, tmpConfidences, confThreshold, nmsThreshold, indices);
        }

        if (set) {
            int n = (int)indices.size();
            void *buf = set(n, data);
            if (buf) {
                CVBox *boxes = static_cast<CVBox*>(buf);
                for (int i = 0; i < n; i++) {
                    int idx = indices[i];
                    boxes[i].confidence = tmpConfidences[idx];
                    cv::Point2f pts[4];
                    tmpRotRects[idx].points(pts);
                    for (int j = 0; j < 4; j++) {
                        boxes[i].vertex[j] = pts[j];
                    }
                }
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

CVAPI int cv_dnn_nmsBoxes(void *boxes, void *scores, int count, float scoreThreshold, float nmsThreshold, int *indices, int *indicesCount, float eta, int topK)
{
    cv_clear_error();

    try {
        CVRect *bboxes = static_cast<CVRect*>(boxes);
        float *scoreArr = static_cast<float*>(scores);
        std::vector<cv::Rect> cvBoxes(count);
        std::vector<float> scoresVec(scoreArr, scoreArr + count);

        for (int i = 0; i < count; i++) {
            cvBoxes[i] = cv::Rect(bboxes[i].x, bboxes[i].y, bboxes[i].hSize, bboxes[i].vSize);
        }

        std::vector<int> result;
        cv::dnn::NMSBoxes(cvBoxes, scoresVec, scoreThreshold, nmsThreshold, result, eta, topK);

        int n = (int)result.size();
        for (int i = 0; i < n; i++) {
            indices[i] = result[i];
        }
        *indicesCount = n;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_readNet(const char *model, const char *config, const char *framework, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNet(model,
            config ? config : "",
            framework ? framework : ""));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_readNetFromTorch(const char *model, int isBinary, int evaluate, void **handle)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromTorch(model, isBinary != 0, evaluate != 0));
        *handle = net;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netSetPreferableBackend(void *net, int backendId)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        ptr->setPreferableBackend(backendId);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netSetPreferableTarget(void *net, int targetId)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        ptr->setPreferableTarget(targetId);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netEnableFusion(void *net, int fusion)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        ptr->enableFusion(fusion != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netGetUnconnectedOutLayers(void *net, int *layers, int *count, int maxCount)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        std::vector<int> outLayers = ptr->getUnconnectedOutLayers();
        int n = std::min((int)outLayers.size(), maxCount);
        for (int i = 0; i < n; i++) {
            layers[i] = outLayers[i];
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

CVAPI int cv_dnn_netGetUnconnectedOutLayersNames(void *net, char **names, int *count, int maxCount)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        std::vector<cv::String> outNames = ptr->getUnconnectedOutLayersNames();
        int n = std::min((int)outNames.size(), maxCount);
        for (int i = 0; i < n; i++) {
            if (names[i]) {
                strncpy(names[i], outNames[i].c_str(), 255);
            }
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

CVAPI int cv_dnn_blobFromImages(cv::Mat **images, int imageCount, cv::Mat **blob, double scaleFactor, int hSize, int vSize, CVScalar *mean, int swapRB, int crop, int ddepth)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> imgs;
        imgs.reserve(imageCount);
        for (int i = 0; i < imageCount; i++) {
            imgs.push_back(*images[i]);
        }
        cv::Mat *dst = new cv::Mat(cv::dnn::blobFromImages(imgs, scaleFactor, cv::Size(hSize, vSize),
            cv::Scalar(mean->v0, mean->v1, mean->v2, mean->v3), swapRB != 0, crop != 0, ddepth));
        *blob = dst;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_imagesFromBlob(cv::Mat *blob, cv::Mat **images, int *count, int maxCount)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> imgs;
        cv::dnn::imagesFromBlob(*blob, imgs);
        int n = std::min((int)imgs.size(), maxCount);
        for (int i = 0; i < n; i++) {
            imgs[i].copyTo(*images[i]);
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

CVAPI int cv_dnn_netEmpty(void *net)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        return ptr->empty() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netGetLayerCount(void *net)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        return (int)ptr->getLayerNames().size();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netDump(void *net, char *buffer, int maxLen)
{
    cv_clear_error();
    if (!buffer || maxLen <= 0) {
        cv_set_error_literal("Output buffer must have positive capacity");
        return -1;
    }

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        std::string dump = ptr->dump();
        int len = std::min((int)dump.size(), maxLen - 1);
        memcpy(buffer, dump.c_str(), len);
        buffer[len] = '\0';
        return len;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netGetPerfProfile(void *net, double *timings)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        std::vector<double> layersTimes;
        double total = ptr->getPerfProfile(layersTimes);
        if (timings) {
            *timings = total;
        }
        return (int)total;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_netEnableWinograd(void *net, int useWinograd)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        ptr->enableWinograd(useWinograd != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_dnn_readNetFromDarknet(const char *cfgFile, const char *darknetModel)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromDarknet(cfgFile, darknetModel ? darknetModel : ""));
        return net;
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

CVAPI void *cv_dnn_readNetFromModelOptimizer(const char *xml, const char *bin)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromModelOptimizer(xml, bin));
        return net;
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

CVAPI void *cv_dnn_readNetFromTFLite(const char *model)
{
    cv_clear_error();

    try {
        auto *net = new cv::dnn::Net(cv::dnn::readNetFromTFLite(model));
        return net;
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

CVAPI int cv_dnn_NMSBoxesBatched(void *bboxes, float *scores, int *classIds, int count, float scoreThreshold, float nmsThreshold, int *indices, int *indicesCount, float eta, int topK)
{
    cv_clear_error();

    try {
        CVRect *rects = static_cast<CVRect*>(bboxes);
        std::vector<cv::Rect> boxes(count);
        std::vector<float> scoresVec(scores, scores + count);
        std::vector<int> classIdsVec(classIds, classIds + count);

        for (int i = 0; i < count; i++) {
            boxes[i] = cv::Rect(rects[i].x, rects[i].y, rects[i].hSize, rects[i].vSize);
        }

        std::vector<int> result;
        cv::dnn::NMSBoxesBatched(boxes, scoresVec, classIdsVec, scoreThreshold, nmsThreshold, result, eta, topK);

        int n = (int)result.size();
        for (int i = 0; i < n; i++) {
            indices[i] = result[i];
        }
        *indicesCount = n;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_NMSBoxesRotated(void *bboxes, float *scores, int count, float scoreThreshold, float nmsThreshold, int *indices, int *indicesCount, float eta, int topK)
{
    cv_clear_error();

    try {
        CVRotatedRect *rects = static_cast<CVRotatedRect*>(bboxes);
        std::vector<cv::RotatedRect> boxes(count);
        std::vector<float> scoresVec(scores, scores + count);

        for (int i = 0; i < count; i++) {
            boxes[i] = cv::RotatedRect(
                cv::Point2f(rects[i].center.x, rects[i].center.y),
                cv::Size2f(rects[i].size.x, rects[i].size.y),
                rects[i].angle);
        }

        std::vector<int> result;
        cv::dnn::NMSBoxes(boxes, scoresVec, scoreThreshold, nmsThreshold, result, eta, topK);

        int n = (int)result.size();
        for (int i = 0; i < n; i++) {
            indices[i] = result[i];
        }
        *indicesCount = n;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_dnn_createDetectionModel(const char *model, const char *config)
{
    cv_clear_error();

    try {
        auto *dm = new cv::dnn::DetectionModel(model, config ? config : "");
        return dm;
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

CVAPI void *cv_dnn_createDetectionModelFromNet(void *net)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        auto *dm = new cv::dnn::DetectionModel(*ptr);
        return dm;
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

CVAPI int cv_dnn_deleteDetectionModel(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
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

CVAPI int cv_dnn_detectionModelDetect(void *model, cv::Mat *frame, int *classIds, float *confidences, void *boxes, int *count, int maxCount, float confThreshold, float nmsThreshold)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
        CVRect *outBoxes = static_cast<CVRect*>(boxes);

        std::vector<int> tmpClassIds;
        std::vector<float> tmpConfidences;
        std::vector<cv::Rect> tmpBoxes;

        ptr->detect(*frame, tmpClassIds, tmpConfidences, tmpBoxes, confThreshold, nmsThreshold);

        int n = std::min((int)tmpClassIds.size(), maxCount);
        for (int i = 0; i < n; i++) {
            classIds[i] = tmpClassIds[i];
            confidences[i] = tmpConfidences[i];
            outBoxes[i].x = tmpBoxes[i].x;
            outBoxes[i].y = tmpBoxes[i].y;
            outBoxes[i].hSize = tmpBoxes[i].width;
            outBoxes[i].vSize = tmpBoxes[i].height;
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

CVAPI int cv_dnn_detectionModelSetInputSize(void *model, int width, int height)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
        ptr->setInputSize(cv::Size(width, height));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_detectionModelSetInputScale(void *model, double scale)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
        ptr->setInputScale(scale);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_detectionModelSetInputMean(void *model, CVScalar mean)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
        ptr->setInputMean(cv::Scalar(mean.v0, mean.v1, mean.v2, mean.v3));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_detectionModelSetInputSwapRB(void *model, int swapRB)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
        ptr->setInputSwapRB(swapRB != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_detectionModelSetInputCrop(void *model, int crop)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::DetectionModel *>(model);
        ptr->setInputCrop(crop != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_dnn_createClassificationModel(const char *model, const char *config)
{
    cv_clear_error();

    try {
        auto *cm = new cv::dnn::ClassificationModel(model, config ? config : "");
        return cm;
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

CVAPI void *cv_dnn_createClassificationModelFromNet(void *net)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        auto *cm = new cv::dnn::ClassificationModel(*ptr);
        return cm;
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

CVAPI int cv_dnn_deleteClassificationModel(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::ClassificationModel *>(model);
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

CVAPI int cv_dnn_classificationModelClassify(void *model, cv::Mat *frame, int *classId, float *conf)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::ClassificationModel *>(model);
        int tmpClassId;
        float tmpConf;
        ptr->classify(*frame, tmpClassId, tmpConf);
        *classId = tmpClassId;
        *conf = tmpConf;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_classificationModelSetInputSize(void *model, int width, int height)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::ClassificationModel *>(model);
        ptr->setInputSize(cv::Size(width, height));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_classificationModelSetInputScale(void *model, double scale)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::ClassificationModel *>(model);
        ptr->setInputScale(scale);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_classificationModelSetInputMean(void *model, CVScalar mean)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::ClassificationModel *>(model);
        ptr->setInputMean(cv::Scalar(mean.v0, mean.v1, mean.v2, mean.v3));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_classificationModelSetInputSwapRB(void *model, int swapRB)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::ClassificationModel *>(model);
        ptr->setInputSwapRB(swapRB != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_dnn_createSegmentationModel(const char *model, const char *config)
{
    cv_clear_error();

    try {
        auto *sm = new cv::dnn::SegmentationModel(model, config ? config : "");
        return sm;
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

CVAPI void *cv_dnn_createSegmentationModelFromNet(void *net)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::Net *>(net);
        auto *sm = new cv::dnn::SegmentationModel(*ptr);
        return sm;
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

CVAPI int cv_dnn_deleteSegmentationModel(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::SegmentationModel *>(model);
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

CVAPI int cv_dnn_segmentationModelSegment(void *model, cv::Mat *frame, cv::Mat **mask)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::SegmentationModel *>(model);
        cv::Mat *dst = new cv::Mat();
        ptr->segment(*frame, *dst);
        *mask = dst;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_segmentationModelSetInputSize(void *model, int width, int height)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::SegmentationModel *>(model);
        ptr->setInputSize(cv::Size(width, height));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_segmentationModelSetInputScale(void *model, double scale)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::SegmentationModel *>(model);
        ptr->setInputScale(scale);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_segmentationModelSetInputMean(void *model, CVScalar mean)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::SegmentationModel *>(model);
        ptr->setInputMean(cv::Scalar(mean.v0, mean.v1, mean.v2, mean.v3));
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_segmentationModelSetInputSwapRB(void *model, int swapRB)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::SegmentationModel *>(model);
        ptr->setInputSwapRB(swapRB != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_dnn_createTextRecognitionModel(const char *model, const char *config)
{
    cv_clear_error();

    try {
        auto *trm = new cv::dnn::TextRecognitionModel(model, config ? config : "");
        return trm;
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

CVAPI int cv_dnn_deleteTextRecognitionModel(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::TextRecognitionModel *>(model);
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

CVAPI int cv_dnn_textRecognitionModelRecognize(void *model, cv::Mat *frame, char *result, int maxLen)
{
    cv_clear_error();
    if (!result || maxLen <= 0) {
        cv_set_error_literal("Output buffer must have positive capacity");
        return -1;
    }

    try {
        auto *ptr = static_cast<cv::dnn::TextRecognitionModel *>(model);
        std::string text = ptr->recognize(*frame);
        int len = std::min((int)text.size(), maxLen - 1);
        memcpy(result, text.c_str(), len);
        result[len] = '\0';
        return len;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_textRecognitionModelSetVocabulary(void *model, const char *vocabulary)
{
    cv_clear_error();

    try {
        auto *ptr = static_cast<cv::dnn::TextRecognitionModel *>(model);
        std::string vocabStr(vocabulary);
        std::vector<std::string> vocab;
        vocab.reserve(vocabStr.size());
        for (size_t i = 0; i < vocabStr.size(); i++) {
            vocab.push_back(std::string(1, vocabStr[i]));
        }
        ptr->setVocabulary(vocab);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_dnn_getAvailableTargets(int backend, int *targets, int *count, int maxCount)
{
    cv_clear_error();

    try {
        std::vector<std::pair<cv::dnn::Backend, cv::dnn::Target>> backendsTargets = cv::dnn::getAvailableBackends();
        int n = 0;
        for (size_t i = 0; i < backendsTargets.size() && n < maxCount; i++) {
            if ((int)backendsTargets[i].first == backend) {
                targets[n] = (int)backendsTargets[i].second;
                n++;
            }
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
