
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_face.h"
#include <vector>

CVAPI void *cv_face_createEigenFaceRecognizer(int numComponents, double threshold)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::face::EigenFaceRecognizer> *p = new cv::Ptr<cv::face::EigenFaceRecognizer>(
            cv::face::EigenFaceRecognizer::create(numComponents, threshold));
        return p;
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

CVAPI int cv_face_deleteEigenFaceRecognizer(void *recognizer)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::face::EigenFaceRecognizer> *>(recognizer); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_face_createFisherFaceRecognizer(int numComponents, double threshold)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::face::FisherFaceRecognizer> *p = new cv::Ptr<cv::face::FisherFaceRecognizer>(
            cv::face::FisherFaceRecognizer::create(numComponents, threshold));
        return p;
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

CVAPI int cv_face_deleteFisherFaceRecognizer(void *recognizer)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::face::FisherFaceRecognizer> *>(recognizer); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_face_createLBPHFaceRecognizer(int radius, int neighbors, int gridX, int gridY, double threshold)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::face::LBPHFaceRecognizer> *p = new cv::Ptr<cv::face::LBPHFaceRecognizer>(
            cv::face::LBPHFaceRecognizer::create(radius, neighbors, gridX, gridY, threshold));
        return p;
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

CVAPI int cv_face_deleteLBPHFaceRecognizer(void *recognizer)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::face::LBPHFaceRecognizer> *>(recognizer); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


static cv::Ptr<cv::face::LBPHFaceRecognizer> &getLBPH(void *recognizer)
{
    return *static_cast<cv::Ptr<cv::face::LBPHFaceRecognizer> *>(recognizer);
}

CVAPI int cv_face_lbphGetGridX(void *recognizer) {
    cv_clear_error();
    try {
     return getLBPH(recognizer)->getGridX();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphSetGridX(void *recognizer, int val)
{
    cv_clear_error();

    try { getLBPH(recognizer)->setGridX(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphGetGridY(void *recognizer) {
    cv_clear_error();
    try {
     return getLBPH(recognizer)->getGridY();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphSetGridY(void *recognizer, int val)
{
    cv_clear_error();

    try { getLBPH(recognizer)->setGridY(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphGetRadius(void *recognizer) {
    cv_clear_error();
    try {
     return getLBPH(recognizer)->getRadius();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphSetRadius(void *recognizer, int val)
{
    cv_clear_error();

    try { getLBPH(recognizer)->setRadius(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphGetNeighbors(void *recognizer) {
    cv_clear_error();
    try {
     return getLBPH(recognizer)->getNeighbors();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphSetNeighbors(void *recognizer, int val)
{
    cv_clear_error();

    try { getLBPH(recognizer)->setNeighbors(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_face_lbphGetThreshold(void *recognizer)
{
    cv_clear_error();
    try {
        return getLBPH(recognizer)->getThreshold();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphSetThreshold(void *recognizer, double val)
{
    cv_clear_error();

    try { getLBPH(recognizer)->setThreshold(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphGetHistograms(void *recognizer, cv::Mat **histograms)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> hists = getLBPH(recognizer)->getHistograms();
        if (histograms && !hists.empty()) {

            cv::Mat result;
            cv::vconcat(hists, result);
            *histograms = new cv::Mat(result);
        }
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_lbphGetLabels(void *recognizer, cv::Mat **labels)
{
    cv_clear_error();

    try {
        cv::Mat l = getLBPH(recognizer)->getLabels();
        if (labels) *labels = new cv::Mat(l);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

static cv::Ptr<cv::face::FaceRecognizer> getRecognizer(void *recognizer)
{
    return *static_cast<cv::Ptr<cv::face::FaceRecognizer> *>(recognizer);
}

CVAPI int cv_face_recognizerTrain(void *recognizer, cv::Mat **images, int *labels, int count)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> imgs;
        std::vector<int> lbls;
        for (int i = 0; i < count; i++) {
            imgs.push_back(*images[i]);
            lbls.push_back(labels[i]);
        }
        getRecognizer(recognizer)->train(imgs, lbls);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerUpdate(void *recognizer, cv::Mat **images, int *labels, int count)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> imgs;
        std::vector<int> lbls;
        for (int i = 0; i < count; i++) {
            imgs.push_back(*images[i]);
            lbls.push_back(labels[i]);
        }
        getRecognizer(recognizer)->update(imgs, lbls);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerPredict(void *recognizer, cv::Mat **src, int *label, double *confidence)
{
    cv_clear_error();

    try {
        int l = -1;
        double c = 0.0;
        getRecognizer(recognizer)->predict(**src, l, c);
        if (label) *label = l;
        if (confidence) *confidence = c;
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerSave(void *recognizer, const char *filename)
{
    cv_clear_error();

    try { getRecognizer(recognizer)->write(std::string(filename)); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerLoad(void *recognizer, const char *filename)
{
    cv_clear_error();

    try { getRecognizer(recognizer)->read(std::string(filename)); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerSetLabelInfo(void *recognizer, int label, const char *strInfo)
{
    cv_clear_error();

    try { getRecognizer(recognizer)->setLabelInfo(label, std::string(strInfo)); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerGetLabelInfo(void *recognizer, int label, char *strInfo, int maxLen)
{
    cv_clear_error();

    try {
        std::string info = getRecognizer(recognizer)->getLabelInfo(label);
        if (strInfo && maxLen > 0) {
            int len = (int)info.size();
            if (len >= maxLen) len = maxLen - 1;
            memcpy(strInfo, info.c_str(), len);
            strInfo[len] = '\0';
        }
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_face_recognizerGetThreshold(void *recognizer)
{
    cv_clear_error();
    try {
        return getRecognizer(recognizer)->getThreshold();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_recognizerSetThreshold(void *recognizer, double val)
{
    cv_clear_error();

    try { getRecognizer(recognizer)->setThreshold(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_face_createFacemarkLBF()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::face::Facemark> *p = new cv::Ptr<cv::face::Facemark>(
            cv::face::FacemarkLBF::create());
        return p;
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

CVAPI void *cv_face_createFacemarkAAM()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::face::Facemark> *p = new cv::Ptr<cv::face::Facemark>(
            cv::face::FacemarkAAM::create());
        return p;
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

CVAPI int cv_face_deleteFacemark(void *facemark)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::face::Facemark> *>(facemark); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_facemarkLoadModel(void *facemark, const char *model)
{
    cv_clear_error();

    try {
        (*static_cast<cv::Ptr<cv::face::Facemark> *>(facemark))->loadModel(std::string(model));
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_facemarkFit(void *facemark, cv::Mat **image, CVRect *faces, int faceCount,
    cv::Mat **landmarks, int *landmarkCount)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::face::Facemark> *>(facemark);


        std::vector<cv::Rect> faceRects;
        for (int i = 0; i < faceCount; i++)
            faceRects.push_back(cv::Rect(faces[i].x, faces[i].y, faces[i].hSize, faces[i].vSize));

        std::vector<std::vector<cv::Point2f>> landmarksOut;
        bool ok = (*p)->fit(**image, faceRects, landmarksOut);

        if (landmarkCount)
            *landmarkCount = (int)landmarksOut.size();

        if (landmarks) {
            for (int i = 0; i < (int)landmarksOut.size(); i++) {
                landmarks[i] = new cv::Mat(landmarksOut[i], true);
            }
        }

        return ok ? 1 : 0;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_face_drawFacemarks(cv::Mat **image, cv::Mat **points, CVScalar color)
{
    cv_clear_error();

    try {
        std::vector<cv::Point2f> pts;
        (*points)->copyTo(pts);
        cv::Scalar c(color.v0, color.v1, color.v2, color.v3);
        cv::face::drawFacemarks(**image, pts, c);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
