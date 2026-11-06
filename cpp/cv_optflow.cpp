
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_optflow.h"
#include <vector>

CVAPI void *cv_optflow_createOptFlow_DualTVL1()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *p =
            new cv::Ptr<cv::optflow::DualTVL1OpticalFlow>(cv::optflow::DualTVL1OpticalFlow::create());
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

CVAPI int cv_optflow_deleteDualTVL1(void *flow)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1Calc(void *flow, cv::Mat *I0, cv::Mat *I1, cv::Mat **flowMat)
{
    cv_clear_error();

    try {
        auto *p = static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow);
        cv::Mat result;
        (*p)->calc(*I0, *I1, result);
        *flowMat = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_optflow_dualTVL1GetTau(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getTau();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetTau(void *flow, double val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setTau(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_optflow_dualTVL1GetLambda(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getLambda();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetLambda(void *flow, double val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setLambda(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_optflow_dualTVL1GetTheta(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getTheta();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetTheta(void *flow, double val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setTheta(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_optflow_dualTVL1GetGamma(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getGamma();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetGamma(void *flow, double val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setGamma(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1GetScalesNumber(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getScalesNumber();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetScalesNumber(void *flow, int val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setScalesNumber(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1GetWarpingsNumber(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getWarpingsNumber();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetWarpingsNumber(void *flow, int val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setWarpingsNumber(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_optflow_dualTVL1GetEpsilon(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getEpsilon();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetEpsilon(void *flow, double val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setEpsilon(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1GetInnerIterations(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getInnerIterations();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetInnerIterations(void *flow, int val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setInnerIterations(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1GetOuterIterations(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getOuterIterations();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetOuterIterations(void *flow, int val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setOuterIterations(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1GetMedianFiltering(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getMedianFiltering();
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetMedianFiltering(void *flow, int val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setMedianFiltering(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1GetUseInitialFlow(void *flow)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->getUseInitialFlow() ? 1 : 0;
    } catch (const cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_dualTVL1SetUseInitialFlow(void *flow, int val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::optflow::DualTVL1OpticalFlow> *>(flow))->setUseInitialFlow(val != 0); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_optflow_createOptFlow_DeepFlow()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::DenseOpticalFlow> *p = new cv::Ptr<cv::DenseOpticalFlow>(
            cv::optflow::createOptFlow_DeepFlow());
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

CVAPI void *cv_optflow_createOptFlow_SimpleFlow()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::DenseOpticalFlow> *p = new cv::Ptr<cv::DenseOpticalFlow>(
            cv::optflow::createOptFlow_SimpleFlow());
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

CVAPI void *cv_optflow_createOptFlow_PCAFlow()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::DenseOpticalFlow> *p = new cv::Ptr<cv::DenseOpticalFlow>(
            cv::optflow::createOptFlow_PCAFlow());
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

CVAPI void *cv_optflow_createOptFlow_SparseToDense()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::DenseOpticalFlow> *p = new cv::Ptr<cv::DenseOpticalFlow>(
            cv::optflow::createOptFlow_SparseToDense());
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

CVAPI int cv_optflow_deleteOptFlow(void *flow)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::DenseOpticalFlow> *>(flow);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_calcOpticalFlowSF(cv::Mat *from, cv::Mat *to, cv::Mat **flow,
    int layers, int averagingBlockSize, int maxFlow)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::optflow::calcOpticalFlowSF(*from, *to, result, layers, averagingBlockSize, maxFlow);
        *flow = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_optflow_calcOpticalFlowSparseToDense(cv::Mat *from, cv::Mat *to, cv::Mat **flow,
    int gridStep, int k, float sigma, int usePostProc, float fgsLambda, float fgsSigma)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::optflow::calcOpticalFlowSparseToDense(*from, *to, result,
            gridStep, k, sigma, usePostProc != 0, fgsLambda, fgsSigma);
        *flow = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
