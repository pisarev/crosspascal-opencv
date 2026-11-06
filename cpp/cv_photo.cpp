

/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_photo.h"
#include <memory>
#include <vector>


CVAPI int cv_photo_inpaint(cv::Mat *src, cv::Mat *inpaintMask, cv::Mat **pDst, double inpaintRadius, int flags)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::inpaint(*src, *inpaintMask, *dst, inpaintRadius, flags);
        *pDst = dst.release();
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


CVAPI int cv_photo_fastNlMeansDenoising(cv::Mat *src, cv::Mat **pDst, float h, int templateWindowSize, int searchWindowSize)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::fastNlMeansDenoising(*src, *dst, h, templateWindowSize, searchWindowSize);
        *pDst = dst.release();
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

CVAPI int cv_photo_fastNlMeansDenoisingColored(cv::Mat *src, cv::Mat **pDst, float h, float hForColorComponents, int templateWindowSize, int searchWindowSize)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::fastNlMeansDenoisingColored(*src, *dst, h, hForColorComponents, templateWindowSize, searchWindowSize);
        *pDst = dst.release();
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

CVAPI int cv_photo_fastNlMeansDenoisingMulti(cv::Mat **srcImgs, int srcCount, int imgToDenoiseIndex, int temporalWindowSize, cv::Mat **pDst, float h, int templateWindowSize, int searchWindowSize)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*srcImgs[i]);
        auto dst = std::make_unique<cv::Mat>();
        cv::fastNlMeansDenoisingMulti(imgs, *dst, imgToDenoiseIndex, temporalWindowSize, h, templateWindowSize, searchWindowSize);
        *pDst = dst.release();
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

CVAPI int cv_photo_fastNlMeansDenoisingColoredMulti(cv::Mat **srcImgs, int srcCount, int imgToDenoiseIndex, int temporalWindowSize, cv::Mat **pDst, float h, float hForColorComponents, int templateWindowSize, int searchWindowSize)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*srcImgs[i]);
        auto dst = std::make_unique<cv::Mat>();
        cv::fastNlMeansDenoisingColoredMulti(imgs, *dst, imgToDenoiseIndex, temporalWindowSize, h, hForColorComponents, templateWindowSize, searchWindowSize);
        *pDst = dst.release();
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


CVAPI int cv_photo_seamlessClone(cv::Mat *src, cv::Mat *destination, cv::Mat *mask, CVPoint center, cv::Mat **pDst, int flags)
{
    cv_clear_error();

    try {
        cv::Point pt(center.x, center.y);
        auto dst = std::make_unique<cv::Mat>();
        cv::seamlessClone(*src, *destination, *mask, pt, *dst, flags);
        *pDst = dst.release();
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


CVAPI int cv_photo_edgePreservingFilter(cv::Mat *src, cv::Mat **pDst, int flags, float sigma_s, float sigma_r)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::edgePreservingFilter(*src, *dst, flags, sigma_s, sigma_r);
        *pDst = dst.release();
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

CVAPI int cv_photo_detailEnhance(cv::Mat *src, cv::Mat **pDst, float sigma_s, float sigma_r)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::detailEnhance(*src, *dst, sigma_s, sigma_r);
        *pDst = dst.release();
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

CVAPI int cv_photo_pencilSketch(cv::Mat *src, cv::Mat **pDst1, cv::Mat **pDst2, float sigma_s, float sigma_r, float shade_factor)
{
    cv_clear_error();

    try {
        auto dst1 = std::make_unique<cv::Mat>();
        auto dst2 = std::make_unique<cv::Mat>();
        cv::pencilSketch(*src, *dst1, *dst2, sigma_s, sigma_r, shade_factor);
        *pDst1 = dst1.release();
        *pDst2 = dst2.release();
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

CVAPI int cv_photo_stylization(cv::Mat *src, cv::Mat **pDst, float sigma_s, float sigma_r)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::stylization(*src, *dst, sigma_s, sigma_r);
        *pDst = dst.release();
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

CVAPI int cv_photo_colorChange(cv::Mat *src, cv::Mat *mask, cv::Mat **pDst, float red_mul, float green_mul, float blue_mul)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::colorChange(*src, *mask, *dst, red_mul, green_mul, blue_mul);
        *pDst = dst.release();
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

CVAPI int cv_photo_illuminationChange(cv::Mat *src, cv::Mat *mask, cv::Mat **pDst, float alpha, float beta)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::illuminationChange(*src, *mask, *dst, alpha, beta);
        *pDst = dst.release();
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

CVAPI int cv_photo_textureFlattening(cv::Mat *src, cv::Mat *mask, cv::Mat **pDst, float low_threshold, float high_threshold, int kernel_size)
{
    cv_clear_error();

    try {
        auto dst = std::make_unique<cv::Mat>();
        cv::textureFlattening(*src, *mask, *dst, low_threshold, high_threshold, kernel_size);
        *pDst = dst.release();
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


CVAPI int cv_photo_createMergeMertens(float contrast_weight, float saturation_weight, float exposure_weight, void **handle)
{
    cv_clear_error();

    try {
        *handle = new cv::Ptr<cv::MergeMertens>(cv::createMergeMertens(contrast_weight, saturation_weight, exposure_weight));
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

CVAPI int cv_photo_createMergeDebevec(void **handle)
{
    cv_clear_error();

    try {
        *handle = new cv::Ptr<cv::MergeDebevec>(cv::createMergeDebevec());
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

CVAPI int cv_photo_createAlignMTB(int max_bits, int exclude_range, int cut, void **handle)
{
    cv_clear_error();

    try {
        *handle = new cv::Ptr<cv::AlignMTB>(cv::createAlignMTB(max_bits, exclude_range, cut != 0));
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

CVAPI int cv_photo_createTonemapDrago(float gamma, float saturation, float bias, void **handle)
{
    cv_clear_error();

    try {
        *handle = new cv::Ptr<cv::TonemapDrago>(cv::createTonemapDrago(gamma, saturation, bias));
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

CVAPI int cv_photo_createTonemapReinhard(float gamma, float intensity, float light_adapt, float color_adapt, void **handle)
{
    cv_clear_error();

    try {
        *handle = new cv::Ptr<cv::TonemapReinhard>(cv::createTonemapReinhard(gamma, intensity, light_adapt, color_adapt));
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


CVAPI void *cv_photo_createMergeRobertson()
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::MergeRobertson>(cv::createMergeRobertson());
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

CVAPI void *cv_photo_createTonemapMantiuk(float gamma, float scale, float saturation)
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::TonemapMantiuk>(cv::createTonemapMantiuk(gamma, scale, saturation));
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

CVAPI void *cv_photo_createCalibrateDebevec(int samples, float lambda, int random)
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::CalibrateDebevec>(cv::createCalibrateDebevec(samples, lambda, random != 0));
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

CVAPI void *cv_photo_createCalibrateRobertson(int max_iter, float threshold)
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::CalibrateRobertson>(cv::createCalibrateRobertson(max_iter, threshold));
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


CVAPI int cv_photo_decolor(cv::Mat *src, cv::Mat **pGrayscale, cv::Mat **pColorBoost)
{
    cv_clear_error();

    try {
        auto grayscale = std::make_unique<cv::Mat>();
        auto colorBoost = std::make_unique<cv::Mat>();
        cv::decolor(*src, *grayscale, *colorBoost);
        *pGrayscale = grayscale.release();
        *pColorBoost = colorBoost.release();
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


CVAPI int cv_photo_denoise_TVL1(cv::Mat **observations, int count, cv::Mat **pResult, double lambda, int niters)
{
    cv_clear_error();

    try {
        std::vector<cv::Mat> obs;
        for (int i = 0; i < count; i++) obs.push_back(*observations[i]);
        auto result = std::make_unique<cv::Mat>();
        cv::denoise_TVL1(obs, *result, lambda, niters);
        *pResult = result.release();
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

CVAPI void *cv_photo_createTonemap(float gamma)
{
    cv_clear_error();

    try {
        return new cv::Ptr<cv::Tonemap>(cv::createTonemap(gamma));
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

CVAPI int cv_photo_deleteTonemap(void *tonemap)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::Tonemap>*>(tonemap);
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

CVAPI int cv_photo_tonemapProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::Tonemap>*>(tonemap);
        auto dst = std::make_unique<cv::Mat>();
        (*tm)->process(*src, *dst);
        *pDst = dst.release();
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

CVAPI int cv_photo_tonemapGetGamma(void *tonemap, float *gamma)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::Tonemap>*>(tonemap);
        *gamma = (*tm)->getGamma();
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

CVAPI int cv_photo_tonemapSetGamma(void *tonemap, float gamma)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::Tonemap>*>(tonemap);
        (*tm)->setGamma(gamma);
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


CVAPI int cv_photo_deleteTonemapDrago(void *tonemap)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::TonemapDrago>*>(tonemap);
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

CVAPI int cv_photo_tonemapDragoProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapDrago>*>(tonemap);
        auto dst = std::make_unique<cv::Mat>();
        (*tm)->process(*src, *dst);
        *pDst = dst.release();
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

CVAPI int cv_photo_tonemapDragoGetSaturation(void *tonemap, float *saturation)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapDrago>*>(tonemap);
        *saturation = (*tm)->getSaturation();
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

CVAPI int cv_photo_tonemapDragoSetSaturation(void *tonemap, float saturation)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapDrago>*>(tonemap);
        (*tm)->setSaturation(saturation);
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

CVAPI int cv_photo_tonemapDragoGetBias(void *tonemap, float *bias)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapDrago>*>(tonemap);
        *bias = (*tm)->getBias();
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

CVAPI int cv_photo_tonemapDragoSetBias(void *tonemap, float bias)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapDrago>*>(tonemap);
        (*tm)->setBias(bias);
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


CVAPI int cv_photo_deleteTonemapReinhard(void *tonemap)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
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

CVAPI int cv_photo_tonemapReinhardProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        auto dst = std::make_unique<cv::Mat>();
        (*tm)->process(*src, *dst);
        *pDst = dst.release();
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

CVAPI int cv_photo_tonemapReinhardGetIntensity(void *tonemap, float *intensity)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        *intensity = (*tm)->getIntensity();
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

CVAPI int cv_photo_tonemapReinhardSetIntensity(void *tonemap, float intensity)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        (*tm)->setIntensity(intensity);
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

CVAPI int cv_photo_tonemapReinhardGetLightAdaptation(void *tonemap, float *lightAdapt)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        *lightAdapt = (*tm)->getLightAdaptation();
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

CVAPI int cv_photo_tonemapReinhardSetLightAdaptation(void *tonemap, float lightAdapt)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        (*tm)->setLightAdaptation(lightAdapt);
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

CVAPI int cv_photo_tonemapReinhardGetColorAdaptation(void *tonemap, float *colorAdapt)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        *colorAdapt = (*tm)->getColorAdaptation();
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

CVAPI int cv_photo_tonemapReinhardSetColorAdaptation(void *tonemap, float colorAdapt)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapReinhard>*>(tonemap);
        (*tm)->setColorAdaptation(colorAdapt);
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


CVAPI int cv_photo_deleteTonemapMantiuk(void *tonemap)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::TonemapMantiuk>*>(tonemap);
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

CVAPI int cv_photo_tonemapMantiukProcess(void *tonemap, cv::Mat *src, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapMantiuk>*>(tonemap);
        auto dst = std::make_unique<cv::Mat>();
        (*tm)->process(*src, *dst);
        *pDst = dst.release();
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

CVAPI int cv_photo_tonemapMantiukGetScale(void *tonemap, float *scale)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapMantiuk>*>(tonemap);
        *scale = (*tm)->getScale();
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

CVAPI int cv_photo_tonemapMantiukSetScale(void *tonemap, float scale)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapMantiuk>*>(tonemap);
        (*tm)->setScale(scale);
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

CVAPI int cv_photo_tonemapMantiukGetSaturation(void *tonemap, float *saturation)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapMantiuk>*>(tonemap);
        *saturation = (*tm)->getSaturation();
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

CVAPI int cv_photo_tonemapMantiukSetSaturation(void *tonemap, float saturation)
{
    cv_clear_error();

    try {
        auto* tm = static_cast<cv::Ptr<cv::TonemapMantiuk>*>(tonemap);
        (*tm)->setSaturation(saturation);
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


CVAPI int cv_photo_deleteMergeMertens(void *merge)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
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

CVAPI int cv_photo_mergeMertensProcess(void *merge, cv::Mat **src, int srcCount, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*src[i]);
        auto dst = std::make_unique<cv::Mat>();
        (*mm)->process(imgs, *dst);
        *pDst = dst.release();
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

CVAPI int cv_photo_mergeMertensGetContrastWeight(void *merge, float *weight)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        *weight = (*mm)->getContrastWeight();
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

CVAPI int cv_photo_mergeMertensSetContrastWeight(void *merge, float weight)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        (*mm)->setContrastWeight(weight);
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

CVAPI int cv_photo_mergeMertensGetSaturationWeight(void *merge, float *weight)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        *weight = (*mm)->getSaturationWeight();
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

CVAPI int cv_photo_mergeMertensSetSaturationWeight(void *merge, float weight)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        (*mm)->setSaturationWeight(weight);
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

CVAPI int cv_photo_mergeMertensGetExposureWeight(void *merge, float *weight)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        *weight = (*mm)->getExposureWeight();
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

CVAPI int cv_photo_mergeMertensSetExposureWeight(void *merge, float weight)
{
    cv_clear_error();

    try {
        auto* mm = static_cast<cv::Ptr<cv::MergeMertens>*>(merge);
        (*mm)->setExposureWeight(weight);
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


CVAPI int cv_photo_deleteMergeDebevec(void *merge)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::MergeDebevec>*>(merge);
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

CVAPI int cv_photo_mergeDebevecProcess(void *merge, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* md = static_cast<cv::Ptr<cv::MergeDebevec>*>(merge);
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*src[i]);
        auto dst = std::make_unique<cv::Mat>();
        (*md)->process(imgs, *dst, *times);
        *pDst = dst.release();
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


CVAPI int cv_photo_deleteMergeRobertson(void *merge)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::MergeRobertson>*>(merge);
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

CVAPI int cv_photo_mergeRobertsonProcess(void *merge, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* mr = static_cast<cv::Ptr<cv::MergeRobertson>*>(merge);
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*src[i]);
        auto dst = std::make_unique<cv::Mat>();
        (*mr)->process(imgs, *dst, *times);
        *pDst = dst.release();
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


CVAPI int cv_photo_deleteAlignMTB(void *align)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::AlignMTB>*>(align);
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

CVAPI int cv_photo_alignMTBProcess(void *align, cv::Mat **src, int srcCount, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*src[i]);
        std::vector<cv::Mat> result;
        (*am)->process(imgs, result);
        std::vector<std::unique_ptr<cv::Mat>> outputs;
        outputs.reserve(result.size());
        for (const auto &image : result)
            outputs.push_back(std::make_unique<cv::Mat>(image.clone()));
        for (std::size_t i = 0; i < outputs.size(); i++)
            pDst[i] = outputs[i].release();
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

CVAPI int cv_photo_alignMTBGetMaxBits(void *align, int *maxBits)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        *maxBits = (*am)->getMaxBits();
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

CVAPI int cv_photo_alignMTBSetMaxBits(void *align, int maxBits)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        (*am)->setMaxBits(maxBits);
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

CVAPI int cv_photo_alignMTBGetExcludeRange(void *align, int *excludeRange)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        *excludeRange = (*am)->getExcludeRange();
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

CVAPI int cv_photo_alignMTBSetExcludeRange(void *align, int excludeRange)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        (*am)->setExcludeRange(excludeRange);
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

CVAPI int cv_photo_alignMTBGetCut(void *align, int *cut)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        *cut = (*am)->getCut() ? 1 : 0;
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

CVAPI int cv_photo_alignMTBSetCut(void *align, int cut)
{
    cv_clear_error();

    try {
        auto* am = static_cast<cv::Ptr<cv::AlignMTB>*>(align);
        (*am)->setCut(cut != 0);
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


CVAPI int cv_photo_deleteCalibrateDebevec(void *calibrate)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
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

CVAPI int cv_photo_calibrateDebevecProcess(void *calibrate, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*src[i]);
        auto dst = std::make_unique<cv::Mat>();
        (*cd)->process(imgs, *dst, *times);
        *pDst = dst.release();
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

CVAPI int cv_photo_calibrateDebevecGetSamples(void *calibrate, int *samples)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        *samples = (*cd)->getSamples();
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

CVAPI int cv_photo_calibrateDebevecSetSamples(void *calibrate, int samples)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        (*cd)->setSamples(samples);
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

CVAPI int cv_photo_calibrateDebevecGetLambda(void *calibrate, float *lambda)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        *lambda = (*cd)->getLambda();
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

CVAPI int cv_photo_calibrateDebevecSetLambda(void *calibrate, float lambda)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        (*cd)->setLambda(lambda);
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

CVAPI int cv_photo_calibrateDebevecGetRandom(void *calibrate, int *random)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        *random = (*cd)->getRandom() ? 1 : 0;
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

CVAPI int cv_photo_calibrateDebevecSetRandom(void *calibrate, int random)
{
    cv_clear_error();

    try {
        auto* cd = static_cast<cv::Ptr<cv::CalibrateDebevec>*>(calibrate);
        (*cd)->setRandom(random != 0);
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


CVAPI int cv_photo_deleteCalibrateRobertson(void *calibrate)
{
    cv_clear_error();

    try {
        delete static_cast<cv::Ptr<cv::CalibrateRobertson>*>(calibrate);
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

CVAPI int cv_photo_calibrateRobertsonProcess(void *calibrate, cv::Mat **src, int srcCount, cv::Mat *times, cv::Mat **pDst)
{
    cv_clear_error();

    try {
        auto* cr = static_cast<cv::Ptr<cv::CalibrateRobertson>*>(calibrate);
        std::vector<cv::Mat> imgs;
        for (int i = 0; i < srcCount; i++) imgs.push_back(*src[i]);
        auto dst = std::make_unique<cv::Mat>();
        (*cr)->process(imgs, *dst, *times);
        *pDst = dst.release();
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

CVAPI int cv_photo_calibrateRobertsonGetMaxIter(void *calibrate, int *maxIter)
{
    cv_clear_error();

    try {
        auto* cr = static_cast<cv::Ptr<cv::CalibrateRobertson>*>(calibrate);
        *maxIter = (*cr)->getMaxIter();
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

CVAPI int cv_photo_calibrateRobertsonSetMaxIter(void *calibrate, int maxIter)
{
    cv_clear_error();

    try {
        auto* cr = static_cast<cv::Ptr<cv::CalibrateRobertson>*>(calibrate);
        (*cr)->setMaxIter(maxIter);
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

CVAPI int cv_photo_calibrateRobertsonGetThreshold(void *calibrate, float *threshold)
{
    cv_clear_error();

    try {
        auto* cr = static_cast<cv::Ptr<cv::CalibrateRobertson>*>(calibrate);
        *threshold = (*cr)->getThreshold();
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

CVAPI int cv_photo_calibrateRobertsonSetThreshold(void *calibrate, float threshold)
{
    cv_clear_error();

    try {
        auto* cr = static_cast<cv::Ptr<cv::CalibrateRobertson>*>(calibrate);
        (*cr)->setThreshold(threshold);
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
