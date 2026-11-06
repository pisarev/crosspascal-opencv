
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_stitching.h"
#include <vector>


struct StitcherHolder {
    cv::Ptr<cv::Stitcher> stitcher;
    bool canCompose = false;
    StitcherHolder(cv::Ptr<cv::Stitcher> s) : stitcher(s) {}
};

CVAPI void *cv_stitching_createStitcher(int mode)
{
    cv_clear_error();

    try {
        cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(static_cast<cv::Stitcher::Mode>(mode));
        if (stitcher.empty()) {
            cv_set_error_literal("Failed to create Stitcher");
            return nullptr;
        }
        return new StitcherHolder(stitcher);
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_stitching_deleteStitcher(void *stitcher)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        delete holder;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_stitch(void *stitcher, cv::Mat **images, int imageCount, cv::Mat **pano)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->canCompose = false;
        std::vector<cv::Mat> imgs;
        imgs.reserve(imageCount);
        for (int i = 0; i < imageCount; i++) {
            imgs.push_back(*images[i]);
        }
        cv::Mat result;
        cv::Stitcher::Status status = holder->stitcher->stitch(imgs, result);
        if (status != cv::Stitcher::OK) {
            cv_set_error_cstr(("Stitching failed with status: " + std::to_string((int)status)).c_str());
            return 0;
        }
        *pano = new cv::Mat(result);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_estimateTransform(void *stitcher, cv::Mat **images, int imageCount)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->canCompose = false;
        std::vector<cv::Mat> imgs;
        imgs.reserve(imageCount);
        for (int i = 0; i < imageCount; i++) {
            imgs.push_back(*images[i]);
        }
        cv::Stitcher::Status status = holder->stitcher->estimateTransform(imgs);
        if (status != cv::Stitcher::OK) {
            cv_set_error_cstr(("estimateTransform failed with status: " + std::to_string((int)status)).c_str());
            return 0;
        }
        holder->canCompose = true;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_setPanoConfidenceThresh(void *stitcher, double confThresh)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setPanoConfidenceThresh(confThresh);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_getPanoConfidenceThresh(void *stitcher, double *confThresh)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        *confThresh = holder->stitcher->panoConfidenceThresh();
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_composePanorama(void *stitcher, cv::Mat **pano)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return -1;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        if (!pano || !holder->canCompose) {
            cv_set_error_literal("Compose requires an output and a successful transform estimate");
            return -1;
        }
        holder->canCompose = false;
        cv::Mat result;
        cv::Stitcher::Status status = holder->stitcher->composePanorama(result);
        if (status != cv::Stitcher::OK) {
            cv_set_error_cstr(("composePanorama failed with status: " + std::to_string((int)status)).c_str());
            return (int)status;
        }
        *pano = new cv::Mat(result);
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1;
    }
}

CVAPI int cv_stitching_setRegistrationResol(void *stitcher, double resol)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setRegistrationResol(resol);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_setSeamEstimationResol(void *stitcher, double resol)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setSeamEstimationResol(resol);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_setCompositingResol(void *stitcher, double resol)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setCompositingResol(resol);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_getWaveCorrection(void *stitcher, int *val)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        *val = holder->stitcher->waveCorrection() ? 1 : 0;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_setWaveCorrection(void *stitcher, int val)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setWaveCorrection(val != 0);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_getWaveCorrectKind(void *stitcher, int *kind)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        *kind = static_cast<int>(holder->stitcher->waveCorrectKind());
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_setWaveCorrectKind(void *stitcher, int kind)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setWaveCorrectKind(static_cast<cv::detail::WaveCorrectKind>(kind));
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_getInterpolationFlags(void *stitcher, int *flags)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        *flags = holder->stitcher->interpolationFlags();
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_setInterpolationFlags(void *stitcher, int flags)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        holder->stitcher->setInterpolationFlags(static_cast<cv::InterpolationFlags>(flags));
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_stitcherComponent(void *stitcher, int *indices, int *count)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        std::vector<int> comp = holder->stitcher->component();
        int n = (int)comp.size();
        if (n > *count) n = *count;
        for (int i = 0; i < n; i++) {
            indices[i] = comp[i];
        }
        *count = n;
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_stitching_stitcherResultMask(void *stitcher, cv::Mat **mask)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return 0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        cv::UMat resultMask = holder->stitcher->resultMask();
        cv::Mat tmp;
        resultMask.copyTo(tmp);
        *mask = new cv::Mat(tmp);
        return 1;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_stitching_stitcherWorkScale(void *stitcher)
{
    cv_clear_error();

    try {
        if (!stitcher) {
            cv_set_error_literal("Stitcher pointer is null");
            return -1.0;
        }
        StitcherHolder *holder = static_cast<StitcherHolder *>(stitcher);
        return holder->stitcher->workScale();
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return -1.0;
    }
}
