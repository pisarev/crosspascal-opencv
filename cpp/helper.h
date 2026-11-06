
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_HELPER_H
#define CV_HELPER_H

#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "cv_types.h"

std::string to_text(float a);
std::string to_text(double a);
std::string to_text(int a);
std::string to_text(unsigned int a);
std::string to_text(std::string a, float b);
std::string to_text(std::string a, int b);
std::string to_text(std::string a, std::string b);

cv::Mat decode_image(void *imageData, int imageSize, int flags = cv::IMREAD_UNCHANGED);
char *to_cstr(std::string text);
void show_image(std::string name, cv::Mat mat, ShowImage show);
void read_image(cv::Mat *mat, ReadImage read, int depth, int n, void *data);

#endif
