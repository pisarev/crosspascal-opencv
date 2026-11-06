
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/core.hpp>
#include <cstdio>
#include <cstring>

static thread_local char cv_errorTextBuf[CV_ERROR_TEXT_MAX] = {0};

static void cv_store_error(const char *text) noexcept
{
    if (!text) {
        cv_errorTextBuf[0] = 0;
        return;
    }
    size_t n = 0;
    while (n + 1 < CV_ERROR_TEXT_MAX && text[n]) {
        cv_errorTextBuf[n] = text[n];
        n++;
    }
    cv_errorTextBuf[n] = 0;
}

void cv_set_error_cstr(const char *text) noexcept
{
    cv_store_error(text);
}

void cv_set_error_literal(const char *text) noexcept
{
    cv_store_error(text);
}

void cv_clear_error() noexcept
{
    cv_errorTextBuf[0] = 0;
}

const char *cv_error_text() noexcept
{
    return cv_errorTextBuf;
}

int cv_error_size() noexcept
{
    size_t n = 0;
    while (n < CV_ERROR_TEXT_MAX && cv_errorTextBuf[n])
        n++;
    return (int)n;
}

#define CROSSCV_ABI_VERSION 3

CVAPI int crosscv_get_abi_version()
{

    cv_clear_error();
    return CROSSCV_ABI_VERSION;
}

CVAPI int crosscv_runtime_identity_4F2C9A7E()
{

    cv_clear_error();
    return 1;
}

CVAPI int cv_core_getErrorSize()
{
    return cv_error_size() + 1;
}

CVAPI int cv_core_getErrorText(char *dst, size_t capacity)
{
    const char *src = cv_error_text();
    int n = cv_error_size();
    size_t needed = (size_t)n + 1;
    if (dst && capacity > 0)
    {
        size_t fits = needed <= capacity ? needed : capacity;
        memcpy(dst, src, fits);
        dst[fits - 1] = '\0';
    }
    return (int)needed;
}


