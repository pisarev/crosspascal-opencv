
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_EXPORT_H
#define CV_EXPORT_H

#ifdef _WIN32
  #define CVAPI extern "C" __declspec(dllexport)
#else
  #define CVAPI extern "C" __attribute__((visibility("default")))
#endif

#include <cstddef>

#define CV_ERROR_TEXT_MAX 1024

void cv_set_error_cstr(const char *text) noexcept;
void cv_set_error_literal(const char *text) noexcept;
void cv_clear_error() noexcept;
const char *cv_error_text() noexcept;
int cv_error_size() noexcept;

#endif
