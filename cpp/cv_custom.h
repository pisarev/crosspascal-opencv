
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_CUSTOM_H
#define CV_CUSTOM_H

#include "cv_export.h"
#include "cv_types.h"


namespace Doxa { class Image; }
struct svm_model;

enum ThresholdKind {
    TK_NIBLACK    = 0,
    TK_SAUVOLA    = 1,
    TK_WOLFJOLION = 2
};

enum DoxaThresholdKind {
    DTK_OTSU        = 0,
    DTK_BERNSEN     = 1,
    DTK_NIBLACK     = 2,
    DTK_SAUVOLA     = 3,
    DTK_WOLF        = 4,
    DTK_NICK        = 5,
    DTK_SU          = 6,
    DTK_TRSINGH     = 7,
    DTK_BATAINEH    = 8,
    DTK_ISAUVOLA    = 9,
    DTK_WAN         = 10
};

enum OperationKind {
    OK_SUBTRACT = 0,
    OK_ADD      = 1,
    OK_MULTIPLY = 2,
    OK_DIVIDE   = 3,
    OK_AND      = 4,
    OK_OR       = 5,
    OK_XOR      = 6
};

CVAPI int cv_custom_toDoxaImage(cv::Mat *mat, void **target);
CVAPI int cv_custom_fromDoxaImage(void *image, cv::Mat **mat);
CVAPI int cv_custom_deleteDoxaImage(void *image);
CVAPI int cv_custom_doxaThreshold(void *image, void *dst, int algorithm, double k, double window, double r);

CVAPI int cv_custom_locateTemplate(cv::Mat *source, cv::Mat *templ, double threshold, int method, cv::Mat *mask, SetData *setData, void *data);
CVAPI int cv_custom_searchTemplate(cv::Mat *source, cv::Mat *templ, double threshold, int method, cv::Mat *mask, int maxResults, SetMat *setMat, void *data);

CVAPI int cv_custom_createCLAHE(double clipLimit, CVSize tilesGridSize, void **handle);
CVAPI int cv_custom_deleteCLAHE(void *clahe);
CVAPI int cv_custom_setClipLimit(void *clahe, double clipLimit);
CVAPI int cv_custom_getClipLimit(void *clahe, double *clipLimit);
CVAPI int cv_custom_setTilesGridSize(void *clahe, CVSize tilesGridSize);
CVAPI int cv_custom_getTilesGridSize(void *clahe, CVSize *tilesGridSize);
CVAPI int cv_custom_collectGarbage(void *clahe);
CVAPI int cv_custom_claheApply(void *clahe, cv::Mat *src, cv::Mat **dst);

CVAPI int cv_custom_varianceOfLaplacian(cv::Mat *src, double *value);
CVAPI int cv_custom_tenengrad(cv::Mat *src, int kSize, double *value);
CVAPI int cv_custom_normalizedGrayLevelVariance(cv::Mat *src, double *value);

CVAPI int cv_custom_createBGSSubtractor(int algorithmType, void **handle);
CVAPI int cv_custom_deleteBGSSubtractor(void *subtractor);
CVAPI int cv_custom_subtractorBGSApply(void *subtractor, cv::Mat *image, cv::Mat **fgmask);

CVAPI void cv_custom_resizeWithAspectRatio(cv::Mat *src, cv::Mat **dst, int width, int height, int interpolation);
CVAPI void cv_custom_drawCrosshair(cv::Mat **img, CVPoint center, int size, CVScalar color, int thickness);
CVAPI void cv_custom_matToArray(cv::Mat *mat, float *data, int *count);
CVAPI void cv_custom_arrayToMat(float *data, int rows, int cols, int type, cv::Mat **mat);
CVAPI void cv_custom_concatHorizontal(cv::Mat *src1, cv::Mat *src2, cv::Mat **dst);
CVAPI void cv_custom_concatVertical(cv::Mat *src1, cv::Mat *src2, cv::Mat **dst);
CVAPI void cv_custom_drawGrid(cv::Mat **img, int rows, int cols, CVScalar color, int thickness);
CVAPI void cv_custom_calculateHistogramImage(cv::Mat *src, cv::Mat **histImg, int width, int height);
CVAPI void cv_custom_maskOverlay(cv::Mat *src, cv::Mat *mask, cv::Mat **dst, CVScalar color, double alpha);
CVAPI void cv_custom_drawDetections(cv::Mat **img, CVRect *rects, int count, CVScalar color, int thickness);

#endif
