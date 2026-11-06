

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_ml.h"
#include <memory>
#include <vector>
#include <string>


using ModelHandle = cv::Ptr<cv::ml::StatModel>;

static ModelHandle *makeModelHandle(const ModelHandle &model)
{
    if (!model)
        CV_Error(cv::Error::StsError, "OpenCV returned no model");
    return new ModelHandle(model);
}

template <class Model>
static Model *getModel(void *handle)
{
    auto *stored = static_cast<ModelHandle *>(handle);
    auto *model = stored ? dynamic_cast<Model *>(stored->get()) : nullptr;
    if (!model)
        CV_Error(cv::Error::StsBadArg, "Invalid or incompatible model handle");
    return model;
}

static int trainingResult(bool trained)
{
    if (!trained)
        cv_set_error_literal("OpenCV could not train the model");
    return trained ? 1 : 0;
}

CVAPI int cv_ml_createSVM(int kernelType, int svmType, double C, double gamma, double degree, double coef0, double nu, double p, void **handle)
{
    cv_clear_error();

    try {
        auto svm = cv::ml::SVM::create();
        svm->setKernel(kernelType);
        svm->setType(svmType);
        svm->setC(C);
        svm->setGamma(gamma);
        svm->setDegree(degree);
        svm->setCoef0(coef0);
        svm->setNu(nu);
        svm->setP(p);
        auto *ptr = makeModelHandle(svm);
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

CVAPI int cv_ml_deleteSVM(void *svm)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(svm);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_saveSVM(void *svm, const char *filename)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->save(filename);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_trainSVM(void *svm, cv::Mat *trainData, cv::Mat *labels)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return trainingResult(ptr->train(*trainData, cv::ml::ROW_SAMPLE, *labels));
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_predict(void *svm, cv::Mat *sample, double *result)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        float res = ptr->predict(*sample);
        if (result) *result = (double)res;
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_predictArray(void *svm, cv::Mat *samples, cv::Mat **results, int flags)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        auto res = std::make_unique<cv::Mat>();
        ptr->predict(*samples, *res, flags);
        *results = res.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_createSVMModel(const char *filename, void **handle)
{
    cv_clear_error();
    try {
        cv_set_error_literal("libSVM not linked");
        *handle = nullptr;
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

CVAPI int cv_ml_deleteSVMModel(void *model)
{
    cv_clear_error();
    try {
        cv_set_error_literal("libSVM not linked");
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

CVAPI int cv_ml_computeScore(void *model, cv::Mat *testData, cv::Mat *testLabels, double *score)
{
    cv_clear_error();
    try {
        cv_set_error_literal("libSVM not linked");
        if (score) *score = 0.0;
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

CVAPI int cv_ml_trainSVMModel(void *model, cv::Mat *trainData, cv::Mat *labels, GetData get, void *data)
{
    cv_clear_error();
    try {
        cv_set_error_literal("libSVM not linked");
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


CVAPI void *cv_ml_createKNearest()
{
    cv_clear_error();

    try {
        auto knn = cv::ml::KNearest::create();
        auto *ptr = makeModelHandle(knn);
        return ptr;
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

CVAPI int cv_ml_deleteKNearest(void *knearest)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(knearest);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_kNearestFindNearest(void *knearest, cv::Mat *samples, int k, cv::Mat **results, cv::Mat **neighborResponses, cv::Mat **dist)
{
    cv_clear_error();
    if (!results || results == neighborResponses || results == dist
        || (neighborResponses && neighborResponses == dist)) {
        cv_set_error_literal("Invalid KNearest output pointers");
        return 0;
    }

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        auto res = std::make_unique<cv::Mat>();
        auto neigh = neighborResponses ? std::make_unique<cv::Mat>() : nullptr;
        auto d = dist ? std::make_unique<cv::Mat>() : nullptr;
        ptr->findNearest(*samples, k, *res,
            neigh ? *neigh : cv::noArray(),
            d ? *d : cv::noArray());
        *results = res.release();
        if (neighborResponses) *neighborResponses = neigh.release();
        if (dist) *dist = d.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_kNearestTrain(void *knearest, cv::Mat *samples, int layout, cv::Mat *responses)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        return trainingResult(ptr->train(*samples, layout, *responses));
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_kNearestSetDefaultK(void *knearest, int k)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        ptr->setDefaultK(k);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createDTrees()
{
    cv_clear_error();

    try {
        auto dtrees = cv::ml::DTrees::create();
        auto *ptr = makeModelHandle(dtrees);
        return ptr;
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

CVAPI int cv_ml_deleteDTrees(void *dtrees)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(dtrees);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createRTrees()
{
    cv_clear_error();

    try {
        auto rtrees = cv::ml::RTrees::create();
        auto *ptr = makeModelHandle(rtrees);
        return ptr;
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

CVAPI int cv_ml_deleteRTrees(void *rtrees)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(rtrees);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createBoost()
{
    cv_clear_error();

    try {
        auto boost = cv::ml::Boost::create();
        auto *ptr = makeModelHandle(boost);
        return ptr;
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

CVAPI int cv_ml_deleteBoost(void *boost)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(boost);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createANN_MLP()
{
    cv_clear_error();

    try {
        auto ann = cv::ml::ANN_MLP::create();
        auto *ptr = makeModelHandle(ann);
        return ptr;
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

CVAPI int cv_ml_deleteANN_MLP(void *ann)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(ann);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetLayerSizes(void *ann, cv::Mat *layerSizes)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setLayerSizes(*layerSizes);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetActivationFunction(void *ann, int type, double param1, double param2)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setActivationFunction(type, param1, param2);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createLogisticRegression()
{
    cv_clear_error();

    try {
        auto lr = cv::ml::LogisticRegression::create();
        auto *ptr = makeModelHandle(lr);
        return ptr;
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

CVAPI int cv_ml_deleteLogisticRegression(void *lr)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(lr);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createNormalBayesClassifier()
{
    cv_clear_error();

    try {
        auto nbc = cv::ml::NormalBayesClassifier::create();
        auto *ptr = makeModelHandle(nbc);
        return ptr;
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

CVAPI int cv_ml_deleteNormalBayesClassifier(void *nbc)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(nbc);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_statModelTrain(void *model, cv::Mat *samples, int layout, cv::Mat *responses)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
        return trainingResult(ptr->train(*samples, layout, *responses));
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_ml_statModelPredict(void *model, cv::Mat *samples, cv::Mat **results, int flags)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
        if (results) {
            auto res = std::make_unique<cv::Mat>();
            float ret = ptr->predict(*samples, *res, flags);
            *results = res.release();
            return ret;
        } else {
            return ptr->predict(*samples, cv::noArray(), flags);
        }
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0f;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_statModelIsTrained(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
        return ptr->isTrained() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_statModelIsClassifier(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
        return ptr->isClassifier() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_statModelGetVarCount(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
        return ptr->getVarCount();
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

CVAPI int cv_ml_statModelEmpty(void *model)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
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

CVAPI int cv_ml_statModelSave(void *model, const char *filename)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::StatModel>(model);
        ptr->save(filename);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_ml_statModelLoad(const char *filename, const char *modelType)
{
    cv_clear_error();

    try {
        if (!filename || !modelType) {
            cv_set_error_literal("A model file and type are required");
            return nullptr;
        }
        std::string type(modelType);
        if (type == "SVM") {
            auto model = cv::ml::SVM::load(filename);
            return makeModelHandle(model);
        } else if (type == "KNearest") {
            auto model = cv::ml::KNearest::load(filename);
            return makeModelHandle(model);
        } else if (type == "DTrees") {
            auto model = cv::ml::DTrees::load(filename);
            return makeModelHandle(model);
        } else if (type == "RTrees") {
            auto model = cv::ml::RTrees::load(filename);
            return makeModelHandle(model);
        } else if (type == "Boost") {
            auto model = cv::ml::Boost::load(filename);
            return makeModelHandle(model);
        } else if (type == "ANN_MLP") {
            auto model = cv::ml::ANN_MLP::load(filename);
            return makeModelHandle(model);
        } else if (type == "LogisticRegression") {
            auto model = cv::ml::LogisticRegression::load(filename);
            return makeModelHandle(model);
        } else if (type == "NormalBayesClassifier") {
            auto model = cv::ml::NormalBayesClassifier::load(filename);
            return makeModelHandle(model);
        } else if (type == "EM") {
            auto model = cv::ml::EM::load(filename);
            return makeModelHandle(model);
        } else if (type == "SVMSGD") {
            auto model = cv::ml::SVMSGD::load(filename);
            return makeModelHandle(model);
        } else {
            cv_set_error_cstr(("Unknown model type: " + type).c_str());
            return nullptr;
        }
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


CVAPI int cv_ml_svmGetType(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getType();
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

CVAPI int cv_ml_svmSetType(void *svm, int type)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setType(type);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmGetKernelType(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getKernelType();
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

CVAPI int cv_ml_svmSetKernel(void *svm, int kernelType)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setKernel(kernelType);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_svmGetC(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getC();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmSetC(void *svm, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setC(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_svmGetGamma(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getGamma();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmSetGamma(void *svm, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setGamma(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_svmGetDegree(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getDegree();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmSetDegree(void *svm, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setDegree(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_svmGetCoef0(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getCoef0();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmSetCoef0(void *svm, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setCoef0(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_svmGetNu(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getNu();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmSetNu(void *svm, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setNu(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_svmGetP(void *svm)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        return ptr->getP();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmSetP(void *svm, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        ptr->setP(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmTrainAuto(void *svm, cv::Mat *samples, int layout, cv::Mat *responses, int kFold, int balanced)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        auto trainData = cv::ml::TrainData::create(*samples, layout, *responses);
        using SVM = cv::ml::SVM;
        return trainingResult(ptr->trainAuto(trainData, kFold,
            SVM::getDefaultGrid(SVM::C), SVM::getDefaultGrid(SVM::GAMMA),
            SVM::getDefaultGrid(SVM::P), SVM::getDefaultGrid(SVM::NU),
            SVM::getDefaultGrid(SVM::COEF), SVM::getDefaultGrid(SVM::DEGREE),
            balanced != 0));
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmGetSupportVectors(void *svm, cv::Mat **sv)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->getSupportVectors();
        *sv = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmGetDecisionFunction(void *svm, int i, cv::Mat **alpha, cv::Mat **svidx)
{
    cv_clear_error();
    if (!alpha || !svidx || alpha == svidx) {
        cv_set_error_literal("Invalid decision function output pointers");
        return 0;
    }

    try {
        auto *ptr = getModel<cv::ml::SVM>(svm);
        auto a = std::make_unique<cv::Mat>();
        auto s = std::make_unique<cv::Mat>();
        ptr->getDecisionFunction(i, *a, *s);
        *alpha = a.release();
        *svidx = s.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_kNearestGetDefaultK(void *knearest)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        return ptr->getDefaultK();
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

CVAPI int cv_ml_kNearestSetIsClassifier(void *knearest, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        ptr->setIsClassifier(val != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_kNearestGetIsClassifier(void *knearest)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        return ptr->getIsClassifier() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_kNearestGetEmax(void *knearest)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        return ptr->getEmax();
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

CVAPI int cv_ml_kNearestSetEmax(void *knearest, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        ptr->setEmax(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_kNearestGetAlgorithmType(void *knearest)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        return ptr->getAlgorithmType();
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

CVAPI int cv_ml_kNearestSetAlgorithmType(void *knearest, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::KNearest>(knearest);
        ptr->setAlgorithmType(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_dTreesGetMaxDepth(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getMaxDepth();
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

CVAPI int cv_ml_dTreesSetMaxDepth(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setMaxDepth(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesGetMinSampleCount(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getMinSampleCount();
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

CVAPI int cv_ml_dTreesSetMinSampleCount(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setMinSampleCount(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesGetMaxCategories(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getMaxCategories();
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

CVAPI int cv_ml_dTreesSetMaxCategories(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setMaxCategories(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesGetCVFolds(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getCVFolds();
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

CVAPI int cv_ml_dTreesSetCVFolds(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setCVFolds(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesGetUseSurrogates(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getUseSurrogates() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesSetUseSurrogates(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setUseSurrogates(val != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesGetUse1SERule(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getUse1SERule() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesSetUse1SERule(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setUse1SERule(val != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesGetTruncatePrunedTree(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getTruncatePrunedTree() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesSetTruncatePrunedTree(void *dtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setTruncatePrunedTree(val != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_ml_dTreesGetRegressionAccuracy(void *dtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        return ptr->getRegressionAccuracy();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0f;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_dTreesSetRegressionAccuracy(void *dtrees, float val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::DTrees>(dtrees);
        ptr->setRegressionAccuracy(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_rTreesGetActiveVarCount(void *rtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::RTrees>(rtrees);
        return ptr->getActiveVarCount();
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

CVAPI int cv_ml_rTreesSetActiveVarCount(void *rtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::RTrees>(rtrees);
        ptr->setActiveVarCount(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_rTreesGetCalculateVarImportance(void *rtrees)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::RTrees>(rtrees);
        return ptr->getCalculateVarImportance() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_rTreesSetCalculateVarImportance(void *rtrees, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::RTrees>(rtrees);
        ptr->setCalculateVarImportance(val != 0);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_rTreesGetVarImportance(void *rtrees, cv::Mat **varImportance)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::RTrees>(rtrees);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->getVarImportance();
        *varImportance = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_boostGetBoostType(void *boost)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::Boost>(boost);
        return ptr->getBoostType();
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

CVAPI int cv_ml_boostSetBoostType(void *boost, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::Boost>(boost);
        ptr->setBoostType(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_boostGetWeakCount(void *boost)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::Boost>(boost);
        return ptr->getWeakCount();
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

CVAPI int cv_ml_boostSetWeakCount(void *boost, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::Boost>(boost);
        ptr->setWeakCount(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_boostGetWeightTrimRate(void *boost)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::Boost>(boost);
        return ptr->getWeightTrimRate();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_boostSetWeightTrimRate(void *boost, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::Boost>(boost);
        ptr->setWeightTrimRate(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_annGetTrainMethod(void *ann)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        return ptr->getTrainMethod();
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

CVAPI int cv_ml_annSetTrainMethod(void *ann, int method, double param1, double param2)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setTrainMethod(method, param1, param2);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_annGetBackpropWeightScale(void *ann)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        return ptr->getBackpropWeightScale();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetBackpropWeightScale(void *ann, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setBackpropWeightScale(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_annGetBackpropMomentumScale(void *ann)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        return ptr->getBackpropMomentumScale();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetBackpropMomentumScale(void *ann, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setBackpropMomentumScale(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_annGetRpropDW0(void *ann)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        return ptr->getRpropDW0();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetRpropDW0(void *ann, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setRpropDW0(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_annGetRpropDWPlus(void *ann)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        return ptr->getRpropDWPlus();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetRpropDWPlus(void *ann, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setRpropDWPlus(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_ml_annGetRpropDWMinus(void *ann)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        return ptr->getRpropDWMinus();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annSetRpropDWMinus(void *ann, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        ptr->setRpropDWMinus(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_annGetWeights(void *ann, int layerIdx, cv::Mat **weights)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::ANN_MLP>(ann);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->getWeights(layerIdx);
        *weights = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createEM()
{
    cv_clear_error();

    try {
        auto em = cv::ml::EM::create();
        auto *ptr = makeModelHandle(em);
        return ptr;
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

CVAPI int cv_ml_deleteEM(void *em)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(em);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_emTrainEM(void *em, cv::Mat *samples, cv::Mat **logLikelihoods, cv::Mat **labels, cv::Mat **probs)
{
    cv_clear_error();
    if ((logLikelihoods && (logLikelihoods == labels || logLikelihoods == probs))
        || (labels && labels == probs)) {
        cv_set_error_literal("EM outputs require distinct storage");
        return 0;
    }

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        auto ll = logLikelihoods ? std::make_unique<cv::Mat>() : nullptr;
        auto lb = labels ? std::make_unique<cv::Mat>() : nullptr;
        auto pr = probs ? std::make_unique<cv::Mat>() : nullptr;
        if (!ptr->trainEM(*samples,
                ll ? *ll : cv::noArray(),
                lb ? *lb : cv::noArray(),
                pr ? *pr : cv::noArray()))
            return trainingResult(false);
        if (logLikelihoods) *logLikelihoods = ll.release();
        if (labels) *labels = lb.release();
        if (probs) *probs = pr.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_emPredict(void *em, cv::Mat *sample, cv::Mat **probs, double *result)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        auto pr = probs ? std::make_unique<cv::Mat>() : nullptr;
        cv::Vec2d res = ptr->predict2(*sample, pr ? *pr : cv::noArray());
        if (result) {
            result[0] = res[0];
            result[1] = res[1];
        }
        if (probs) *probs = pr.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_emGetClustersNumber(void *em)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        return ptr->getClustersNumber();
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

CVAPI int cv_ml_emSetClustersNumber(void *em, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        ptr->setClustersNumber(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_emGetCovarianceMatrixType(void *em)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        return ptr->getCovarianceMatrixType();
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

CVAPI int cv_ml_emSetCovarianceMatrixType(void *em, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        ptr->setCovarianceMatrixType(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_emGetMeans(void *em, cv::Mat **means)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->getMeans();
        *means = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_emGetWeights(void *em, cv::Mat **weights)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::EM>(em);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->getWeights();
        *weights = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_ml_createSVMSGD()
{
    cv_clear_error();

    try {
        auto svmsgd = cv::ml::SVMSGD::create();
        auto *ptr = makeModelHandle(svmsgd);
        return ptr;
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

CVAPI int cv_ml_deleteSVMSGD(void *svmsgd)
{
    cv_clear_error();

    try {
        delete static_cast<ModelHandle *>(svmsgd);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmsgdGetSvmsgdType(void *svmsgd)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        return ptr->getSvmsgdType();
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

CVAPI int cv_ml_svmsgdSetSvmsgdType(void *svmsgd, int svmsgdType)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        ptr->setSvmsgdType(svmsgdType);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmsgdGetMarginType(void *svmsgd)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        return ptr->getMarginType();
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

CVAPI int cv_ml_svmsgdSetMarginType(void *svmsgd, int marginType)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        ptr->setMarginType(marginType);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_ml_svmsgdGetMarginRegularization(void *svmsgd)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        return ptr->getMarginRegularization();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0f;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmsgdSetMarginRegularization(void *svmsgd, float val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        ptr->setMarginRegularization(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_ml_svmsgdGetInitialStepSize(void *svmsgd)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        return ptr->getInitialStepSize();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0f;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmsgdSetInitialStepSize(void *svmsgd, float val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        ptr->setInitialStepSize(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_ml_svmsgdGetStepDecreasingPower(void *svmsgd)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        return ptr->getStepDecreasingPower();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0f;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmsgdSetStepDecreasingPower(void *svmsgd, float val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        ptr->setStepDecreasingPower(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_svmsgdGetWeights(void *svmsgd, cv::Mat **weights)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->getWeights();
        *weights = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_ml_svmsgdGetShift(void *svmsgd)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::SVMSGD>(svmsgd);
        return ptr->getShift();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0.0f;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI double cv_ml_logRegGetLearningRate(void *logreg)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        return ptr->getLearningRate();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_logRegSetLearningRate(void *logreg, double val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        ptr->setLearningRate(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_logRegGetIterations(void *logreg)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        return ptr->getIterations();
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

CVAPI int cv_ml_logRegSetIterations(void *logreg, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        ptr->setIterations(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_logRegGetRegularization(void *logreg)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        return ptr->getRegularization();
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

CVAPI int cv_ml_logRegSetRegularization(void *logreg, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        ptr->setRegularization(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_logRegGetTrainMethod(void *logreg)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        return ptr->getTrainMethod();
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

CVAPI int cv_ml_logRegSetTrainMethod(void *logreg, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        ptr->setTrainMethod(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_logRegGetMiniBatchSize(void *logreg)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        return ptr->getMiniBatchSize();
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

CVAPI int cv_ml_logRegSetMiniBatchSize(void *logreg, int val)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        ptr->setMiniBatchSize(val);
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_ml_logRegGetLearntThetas(void *logreg, cv::Mat **thetas)
{
    cv_clear_error();

    try {
        auto *ptr = getModel<cv::ml::LogisticRegression>(logreg);
        auto result = std::make_unique<cv::Mat>();
        *result = ptr->get_learnt_thetas();
        *thetas = result.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_ml_bayesPredictProb(void *bayes, cv::Mat *inputs, cv::Mat **outputs, cv::Mat **outputProbs)
{
    cv_clear_error();
    if (!outputs || !outputProbs || outputs == outputProbs) {
        cv_set_error_literal("Invalid Bayes output pointers");
        return 0;
    }

    try {
        auto *ptr = getModel<cv::ml::NormalBayesClassifier>(bayes);
        auto out = std::make_unique<cv::Mat>();
        auto outProbs = std::make_unique<cv::Mat>();
        ptr->predictProb(*inputs, *out, *outProbs);
        *outputs = out.release();
        *outputProbs = outProbs.release();
        return 1;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
