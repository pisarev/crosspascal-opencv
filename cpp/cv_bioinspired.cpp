
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_bioinspired.h"

CVAPI int cv_bioinspired_createRetina(CVSize inputSize, int colorMode, int colorSamplingMethod, int useRetinaLogSampling, float reductionFactor, float samplingStrength, void **handle)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::bioinspired::Retina> *p = new cv::Ptr<cv::bioinspired::Retina>(
            cv::bioinspired::Retina::create(
                cv::Size(inputSize.cx, inputSize.cy), colorMode != 0,
                colorSamplingMethod,
                useRetinaLogSampling != 0, reductionFactor, samplingStrength));
        *handle = p;
        return 1;
    } catch (cv::Exception &e) {
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

CVAPI int cv_bioinspired_deleteRetina(void *retina)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::bioinspired::Retina> *>(retina);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_bioinspired_runRetina(void *retina, cv::Mat *inputImage)
{
    cv_clear_error();

    try {
        (*static_cast<cv::Ptr<cv::bioinspired::Retina> *>(retina))->run(*inputImage);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_bioinspired_getParvoOutput(void *retina, cv::Mat **retinaOutput)
{
    cv_clear_error();

    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::bioinspired::Retina> *>(retina))->getParvo(result);
        *retinaOutput = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_bioinspired_getMagnoOutput(void *retina, cv::Mat **retinaOutput)
{
    cv_clear_error();

    try {
        cv::Mat result;
        (*static_cast<cv::Ptr<cv::bioinspired::Retina> *>(retina))->getMagno(result);
        *retinaOutput = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
