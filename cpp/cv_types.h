
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_TYPES_H
#define CV_TYPES_H

#include <cstdint>
#include <opencv2/core.hpp>

#pragma pack(push, 1)

struct CVPoint {
    int x;
    int y;
};

struct CVPoint2f {
    float x;
    float y;
};

struct CVSize {
    int cx;
    int cy;
};

struct CVRect {
    int x;
    int y;
    int hSize;
    int vSize;
};

struct CVColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct CVScalar {
    double v0;
    double v1;
    double v2;
    double v3;
};

struct CVLine {
    CVPoint a;
    CVPoint b;
};

struct CVPlace {
    CVPoint a;
    CVPoint b;
    double value;
};

struct CVObject {
    CVRect rect;
    int id;
    float confidence;
};

struct CVBox {
    float confidence;
    cv::Point2f vertex[4];
};

struct CVMean {
    float r;
    float g;
    float b;
};

struct CVFlowPoint2f {
    unsigned char status;
    float err;
    float x;
    float y;
};

struct CVMoments {
    double m00, m10, m01, m20, m11, m02, m30, m21, m12, m03;
    double mu20, mu11, mu02, mu30, mu21, mu12, mu03;
    double nu20, nu11, nu02, nu30, nu21, nu12, nu03;
};

struct CVKeyPoint {
    float x;
    float y;
    float size;
    float angle;
    float response;
    int octave;
    int classId;
};

struct CVDMatch {
    int queryIdx;
    int trainIdx;
    int imgIdx;
    float distance;
};

struct CVRotatedRect {
    CVPoint2f center;
    CVPoint2f size;
    float angle;
};

struct CVHuMoments {
    double hu[7];
};

struct CVCircle {
    CVPoint2f center;
    float radius;
};

#pragma pack(pop)

typedef void (*ReadImage)(void *imageData, int imageSize, int n, int type, void *data);
typedef void (*ShowImage)(char *imageName, void *imageData, int imageSize);
typedef void (GetData)(int count, void *from, void *data);
typedef void *(SetData)(int count, void *data);
typedef int (SetMat)(double &scale, double &angle, CVPlace place, cv::Mat **image, cv::Mat **slice, int index, int count, void *data);

#endif
