
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_xphoto.h"
#include <vector>

CVAPI void *cv_xphoto_createSimpleWB()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xphoto::SimpleWB> *p = new cv::Ptr<cv::xphoto::SimpleWB>(
            cv::xphoto::createSimpleWB());
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

CVAPI int cv_xphoto_deleteSimpleWB(void *wb)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_simpleWBBalanceWhite(void *wb, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();

    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->balanceWhite(*src, result);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_xphoto_simpleWBGetInputMin(void *wb)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->getInputMin();
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

CVAPI int cv_xphoto_simpleWBSetInputMin(void *wb, float val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->setInputMin(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_xphoto_simpleWBGetInputMax(void *wb)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->getInputMax();
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

CVAPI int cv_xphoto_simpleWBSetInputMax(void *wb, float val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->setInputMax(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_xphoto_simpleWBGetOutputMin(void *wb)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->getOutputMin();
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

CVAPI int cv_xphoto_simpleWBSetOutputMin(void *wb, float val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->setOutputMin(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_xphoto_simpleWBGetOutputMax(void *wb)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->getOutputMax();
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

CVAPI int cv_xphoto_simpleWBSetOutputMax(void *wb, float val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xphoto::SimpleWB> *>(wb))->setOutputMax(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_xphoto_createGrayworldWB()
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xphoto::GrayworldWB> *p = new cv::Ptr<cv::xphoto::GrayworldWB>(
            cv::xphoto::createGrayworldWB());
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

CVAPI int cv_xphoto_deleteGrayworldWB(void *wb)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xphoto::GrayworldWB> *>(wb); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_grayworldWBBalanceWhite(void *wb, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();

    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::xphoto::GrayworldWB> *>(wb))->balanceWhite(*src, result);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI float cv_xphoto_grayworldWBGetSaturationThreshold(void *wb)
{
    cv_clear_error();
    try {
        return (*static_cast<cv::Ptr<cv::xphoto::GrayworldWB> *>(wb))->getSaturationThreshold();
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

CVAPI int cv_xphoto_grayworldWBSetSaturationThreshold(void *wb, float val)
{
    cv_clear_error();

    try { (*static_cast<cv::Ptr<cv::xphoto::GrayworldWB> *>(wb))->setSaturationThreshold(val); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI void *cv_xphoto_createLearningBasedWB(const char *pathToModel)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::xphoto::LearningBasedWB> *p = new cv::Ptr<cv::xphoto::LearningBasedWB>(
            cv::xphoto::createLearningBasedWB(
                (pathToModel && pathToModel[0]) ? std::string(pathToModel) : cv::String()));
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

CVAPI int cv_xphoto_deleteLearningBasedWB(void *wb)
{
    cv_clear_error();

    try { delete static_cast<cv::Ptr<cv::xphoto::LearningBasedWB> *>(wb); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_learningBasedWBBalanceWhite(void *wb, cv::Mat *src, cv::Mat **dst)
{
    cv_clear_error();

    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::xphoto::LearningBasedWB> *>(wb))->balanceWhite(*src, result);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_bm3dDenoising(cv::Mat *src, cv::Mat **dst, float h,
    int templateWindowSize, int searchWindowSize,
    int blockMatchingStep1, int blockMatchingStep2,
    int groupSize, int slidingStep, float beta,
    int normType, int step, int transformType)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::xphoto::bm3dDenoising(*src, result, h, templateWindowSize, searchWindowSize,
            blockMatchingStep1, blockMatchingStep2, groupSize, slidingStep, beta,
            normType, step, transformType);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_dctDenoising(cv::Mat *src, cv::Mat **dst, double sigma, int psize)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::xphoto::dctDenoising(*src, result, sigma, psize);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_applyChannelGains(cv::Mat *src, cv::Mat **dst, float gainB, float gainG, float gainR)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::xphoto::applyChannelGains(*src, result, gainB, gainG, gainR);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_oilPainting(cv::Mat *src, cv::Mat **dst, int size, int dynRatio, int code)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::xphoto::oilPainting(*src, result, size, dynRatio, code);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_xphoto_inpaint(cv::Mat *src, cv::Mat *mask, cv::Mat **dst, int algorithmType)
{
    cv_clear_error();

    try {
        cv::Mat result;
        cv::xphoto::inpaint(*src, *mask, result, algorithmType);
        *dst = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
