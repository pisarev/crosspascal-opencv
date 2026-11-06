
/* Copyright (c) 2026 Yuriy Pisarev                 */

#include "helper.h"
#include <sstream>
#include <vector>

std::string to_text(float a) { std::ostringstream ss; ss << a; return ss.str(); }
std::string to_text(double a) { std::ostringstream ss; ss << a; return ss.str(); }
std::string to_text(int a) { return std::to_string(a); }
std::string to_text(unsigned int a) { return std::to_string(a); }
std::string to_text(std::string a, float b) { return a + to_text(b); }
std::string to_text(std::string a, int b) { return a + to_text(b); }
std::string to_text(std::string a, std::string b) { return a + b; }

cv::Mat decode_image(void *imageData, int imageSize, int flags)
{
    std::vector<uchar> buf((uchar *)imageData, (uchar *)imageData + imageSize);
    return cv::imdecode(buf, flags);
}

char *to_cstr(std::string text)
{
    char *result = new char[text.size() + 1];
    memcpy(result, text.c_str(), text.size() + 1);
    return result;
}

void show_image(std::string name, cv::Mat mat, ShowImage show)
{
    if (!show) return;
    std::vector<uchar> buf;
    cv::imencode(".bmp", mat, buf);
    show((char *)name.c_str(), buf.data(), (int)buf.size());
}

void read_image(cv::Mat *mat, ReadImage read, int depth, int n, void *data)
{
    if (!read || !mat || mat->empty()) return;
    std::vector<uchar> buf;
    cv::imencode(".bmp", *mat, buf);
    read(buf.data(), (int)buf.size(), n, mat->type(), data);
}
