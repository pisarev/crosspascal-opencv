
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_CORE_H
#define CV_CORE_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/core.hpp>

CVAPI int cv_core_getErrorSize();

CVAPI int cv_core_getErrorText(char *dst, size_t capacity);

CVAPI cv::Mat *cv_core_makeMat(int hSize, int vSize, int type);
CVAPI cv::Mat *cv_core_createMat(void *imageData, int imageSize, int flags);
CVAPI int cv_core_deleteMat(cv::Mat **pmat);
CVAPI int cv_core_createRoi(cv::Mat *mat, CVRect rect, cv::Mat **target);
CVAPI int cv_core_copyTo(cv::Mat *src, cv::Mat **target, cv::Mat *mask);
CVAPI int cv_core_clone(cv::Mat *src, cv::Mat **target);
CVAPI int cv_core_setTo(cv::Mat **pmat, CVScalar value, cv::Mat *mask);
CVAPI int cv_core_setRandom(cv::Mat **pmat, CVScalar low, CVScalar high);

CVAPI int cv_core_getMatHSize(cv::Mat *mat, int *hSize);
CVAPI int cv_core_getMatVSize(cv::Mat *mat, int *vSize);
CVAPI int cv_core_getMatDepth(cv::Mat *mat, int *depth);
CVAPI int cv_core_getMatData(cv::Mat *mat, void **data);
CVAPI int cv_core_getMatStep(cv::Mat *mat, int *step);
CVAPI int cv_core_getMatFormat(cv::Mat *mat, int *format);
CVAPI int cv_core_getMatType(cv::Mat *mat, int *type);
CVAPI int cv_core_getMatTotal(cv::Mat *mat, int *total);
CVAPI int cv_core_getMatElemSize(cv::Mat *mat, int *elemSize);
CVAPI int cv_core_getMatEmpty(cv::Mat *mat, int *empty);

CVAPI int cv_core_readMat(cv::Mat *mat, ReadImage read, int depth, int n, void *data);
CVAPI int cv_core_convertType(cv::Mat *src, cv::Mat **target, int rtype, double alpha, double beta);
CVAPI int cv_core_convertScaleAbs(cv::Mat *src, cv::Mat **target, double alpha, double beta);

CVAPI int cv_core_invert(cv::Mat *src, cv::Mat **target, int flags);
CVAPI int cv_core_bitwiseAnd(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask);
CVAPI int cv_core_bitwiseNot(cv::Mat *src, cv::Mat **target, cv::Mat *mask);
CVAPI int cv_core_bitwiseOr(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask);
CVAPI int cv_core_bitwiseXor(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask);
CVAPI int cv_core_operation(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, double alpha, double beta, double gamma, int dtype);
CVAPI int cv_core_normalize(cv::Mat *src, cv::Mat **target, double alpha, double beta, int normType, int dtype, cv::Mat *mask);
CVAPI int cv_core_meanStdDev(cv::Mat *src, cv::Mat **mean, cv::Mat **stddev, cv::Mat *mask);
CVAPI int cv_core_minAreaRect(cv::Mat *points, CVRotatedRect *result);

CVAPI int cv_core_add(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask, int dtype);
CVAPI int cv_core_subtract(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, cv::Mat *mask, int dtype);
CVAPI int cv_core_multiply(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, double scale, int dtype);
CVAPI int cv_core_divide(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, double scale, int dtype);
CVAPI int cv_core_absdiff(cv::Mat *src1, cv::Mat *src2, cv::Mat **target);
CVAPI int cv_core_min(cv::Mat *src1, cv::Mat *src2, cv::Mat **target);
CVAPI int cv_core_max(cv::Mat *src1, cv::Mat *src2, cv::Mat **target);

CVAPI int cv_core_merge(cv::Mat **mv, int count, cv::Mat **target);
CVAPI int cv_core_split(cv::Mat *src, cv::Mat **mv);

CVAPI int cv_core_flip(cv::Mat *src, cv::Mat **target, int flipCode);
CVAPI int cv_core_transpose(cv::Mat *src, cv::Mat **target);
CVAPI int cv_core_vconcat(cv::Mat *src1, cv::Mat *src2, cv::Mat **target);
CVAPI int cv_core_hconcat(cv::Mat *src1, cv::Mat *src2, cv::Mat **target);

CVAPI int cv_core_pow(cv::Mat *src, double power, cv::Mat **target);
CVAPI int cv_core_sqrt(cv::Mat *src, cv::Mat **target);
CVAPI int cv_core_exp(cv::Mat *src, cv::Mat **target);
CVAPI int cv_core_log(cv::Mat *src, cv::Mat **target);
CVAPI int cv_core_magnitude(cv::Mat *x, cv::Mat *y, cv::Mat **target);
CVAPI int cv_core_phase(cv::Mat *x, cv::Mat *y, cv::Mat **target, int angleInDegrees);

CVAPI int cv_core_compare(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, int cmpop);
CVAPI int cv_core_countNonZero(cv::Mat *src, int *count);
CVAPI int cv_core_sum(cv::Mat *src, CVScalar *result);
CVAPI int cv_core_trace(cv::Mat *src, CVScalar *result);
CVAPI int cv_core_determinant(cv::Mat *src, double *value);
CVAPI int cv_core_solve(cv::Mat *src1, cv::Mat *src2, cv::Mat **target, int flags);
CVAPI int cv_core_eigen(cv::Mat *src, cv::Mat **eigenvalues, cv::Mat **eigenvectors);

CVAPI int cv_core_kmeans(cv::Mat *data, int K, int attempts, int flags, cv::Mat **labels, cv::Mat **centers);

CVAPI int cv_core_setIdentity(cv::Mat **pmat, CVScalar value);
CVAPI int cv_core_reduce(cv::Mat *src, cv::Mat **target, int dim, int rtype, int dtype);

CVAPI int cv_core_minMaxLoc(cv::Mat *src, double *minVal, double *maxVal, CVPoint *minLoc, CVPoint *maxLoc, cv::Mat *mask);
CVAPI double cv_core_norm(cv::Mat *src, int normType, cv::Mat *mask);

CVAPI int cv_core_addWeighted(cv::Mat *src1, double alpha, cv::Mat *src2, double beta, double gamma, cv::Mat **target, int dtype);
CVAPI int cv_core_scaleAdd(cv::Mat *src1, double alpha, cv::Mat *src2, cv::Mat **target);
CVAPI int cv_core_gemm(cv::Mat *src1, cv::Mat *src2, double alpha, cv::Mat *src3, double beta, cv::Mat **target, int flags);
CVAPI int cv_core_mulTransposed(cv::Mat *src, cv::Mat **target, int aTa, cv::Mat *delta, double scale, int dtype);
CVAPI int cv_core_transform(cv::Mat *src, cv::Mat **target, cv::Mat *m);
CVAPI int cv_core_perspectiveTransformMat(cv::Mat *src, cv::Mat **target, cv::Mat *m);

CVAPI int cv_core_inRange(cv::Mat *src, CVScalar lowerb, CVScalar upperb, cv::Mat **target);
CVAPI int cv_core_LUT(cv::Mat *src, cv::Mat *lut, cv::Mat **target);

CVAPI int cv_core_repeat(cv::Mat *src, int ny, int nx, cv::Mat **target);
CVAPI int cv_core_rotate(cv::Mat *src, cv::Mat **target, int rotateCode);
CVAPI int cv_core_copyMakeBorder(cv::Mat *src, cv::Mat **target, int top, int bottom, int left, int right, int borderType, CVScalar value);

CVAPI int cv_core_mean(cv::Mat *src, cv::Mat *mask, CVScalar *result);
CVAPI int cv_core_minMaxIdx(cv::Mat *src, double *minVal, double *maxVal, int *minIdx, int *maxIdx, cv::Mat *mask);
CVAPI int cv_core_findNonZero(cv::Mat *src, cv::Mat **idx);

CVAPI int cv_core_sort(cv::Mat *src, cv::Mat **target, int flags);
CVAPI int cv_core_sortIdx(cv::Mat *src, cv::Mat **target, int flags);

CVAPI int cv_core_completeSymm(cv::Mat **pmat, int lowerToUpper);
CVAPI int cv_core_patchNaNs(cv::Mat **pmat, double val);
CVAPI int cv_core_randShuffle(cv::Mat **pmat, double iterFactor);

CVAPI int cv_core_dft(cv::Mat *src, cv::Mat **target, int flags, int nonzeroRows);
CVAPI int cv_core_idft(cv::Mat *src, cv::Mat **target, int flags, int nonzeroRows);
CVAPI int cv_core_dct(cv::Mat *src, cv::Mat **target, int flags);
CVAPI int cv_core_idct(cv::Mat *src, cv::Mat **target, int flags);
CVAPI int cv_core_getOptimalDFTSize(int vecsize);
CVAPI int cv_core_mulSpectrums(cv::Mat *a, cv::Mat *b, cv::Mat **c, int flags, int conjB);

CVAPI int cv_core_calcCovarMatrix(cv::Mat *samples, cv::Mat **covar, cv::Mat **mean, int flags, int ctype);
CVAPI double cv_core_Mahalanobis(cv::Mat *v1, cv::Mat *v2, cv::Mat *icovar);

CVAPI int cv_core_getMatChannels(cv::Mat *mat);
CVAPI int cv_core_convertFp16(cv::Mat *src, cv::Mat **target);
CVAPI int cv_core_borderInterpolate(int p, int len, int borderType);

CVAPI int cv_core_PCACompute(cv::Mat *data, cv::Mat *mean, cv::Mat *eigenvectors, int maxComponents);
CVAPI int cv_core_PCAProject(cv::Mat *data, cv::Mat *mean, cv::Mat *eigenvectors, cv::Mat **result);
CVAPI int cv_core_PCABackProject(cv::Mat *data, cv::Mat *mean, cv::Mat *eigenvectors, cv::Mat **result);

CVAPI int cv_core_SVDecomp(cv::Mat *src, cv::Mat **w, cv::Mat **u, cv::Mat **vt, int flags);
CVAPI int cv_core_SVBackSubst(cv::Mat *w, cv::Mat *u, cv::Mat *vt, cv::Mat *rhs, cv::Mat **target);

CVAPI double cv_core_PSNR(cv::Mat *src1, cv::Mat *src2, double R);

CVAPI int cv_core_polarToCart(cv::Mat *magnitude, cv::Mat *angle, cv::Mat **x, cv::Mat **y, int angleInDegrees);
CVAPI int cv_core_cartToPolar(cv::Mat *x, cv::Mat *y, cv::Mat **magnitude, cv::Mat **angle, int angleInDegrees);

CVAPI int cv_core_checkRange(cv::Mat *a, int quiet, int *pos_x, int *pos_y, double minVal, double maxVal);

CVAPI int cv_core_eigenNonSymmetric(cv::Mat *src, cv::Mat **eigenvalues, cv::Mat **eigenvectors);

CVAPI int cv_core_solveCubic(cv::Mat *coeffs, cv::Mat **roots);
CVAPI double cv_core_solvePoly(cv::Mat *coeffs, cv::Mat **roots, int maxIters);

CVAPI int cv_core_mixChannels(cv::Mat **src, int nsrcs, cv::Mat **dst, int ndsts, const int *fromTo, int npairs);
CVAPI int cv_core_extractChannel(cv::Mat *src, cv::Mat **target, int coi);
CVAPI int cv_core_insertChannel(cv::Mat *src, cv::Mat **target, int coi);

CVAPI int cv_core_flipND(cv::Mat *src, cv::Mat **target, int axis);
CVAPI int cv_core_transposeND(cv::Mat *src, cv::Mat **target, int *order, int orderSize);
CVAPI int cv_core_broadcast(cv::Mat *src, int *shape, int shapeSize, cv::Mat **target);

CVAPI int cv_core_reduceArgMin(cv::Mat *src, cv::Mat **target, int axis, int lastIndex);
CVAPI int cv_core_reduceArgMax(cv::Mat *src, cv::Mat **target, int axis, int lastIndex);
CVAPI int cv_core_hasNonZero(cv::Mat *src);

CVAPI int cv_core_batchDistance(cv::Mat *src1, cv::Mat *src2, cv::Mat **dist, int dtype, cv::Mat **nidx, int normType, int K);

CVAPI int cv_core_divSpectrums(cv::Mat *a, cv::Mat *b, cv::Mat **c, int flags, int conjB);

CVAPI int cv_core_randn(cv::Mat **pmat, double mean, double stddev);
CVAPI int cv_core_randu(cv::Mat **pmat, double low, double high);
CVAPI void cv_core_setRNGSeed(int seed);

CVAPI int64_t cv_core_getTickCount();
CVAPI double cv_core_getTickFrequency();

CVAPI int cv_core_getNumThreads();
CVAPI void cv_core_setNumThreads(int nthreads);

CVAPI const char* cv_core_getBuildInformation();
CVAPI const char* cv_core_getVersionString();

CVAPI int cv_core_solveLP(cv::Mat *Func, cv::Mat *Constr, cv::Mat **z);

CVAPI float cv_core_cubeRoot(float val);
CVAPI float cv_core_fastAtan2(float y, float x);

CVAPI int cv_core_copyToMasked(cv::Mat *src, cv::Mat **target, cv::Mat *mask);

CVAPI void *cv_core_createFileStorage(const char *filename, int flags, const char *encoding);
CVAPI void cv_core_deleteFileStorage(void *fs);
CVAPI int cv_core_fileStorageOpen(void *fs, const char *filename, int flags, const char *encoding);
CVAPI void cv_core_fileStorageRelease(void *fs);
CVAPI int cv_core_fileStorageIsOpened(void *fs);
CVAPI void cv_core_fileStorageWriteInt(void *fs, const char *name, int value);
CVAPI void cv_core_fileStorageWriteDouble(void *fs, const char *name, double value);
CVAPI void cv_core_fileStorageWriteString(void *fs, const char *name, const char *value);
CVAPI void cv_core_fileStorageWriteMat(void *fs, const char *name, cv::Mat *mat);
CVAPI int cv_core_fileStorageReadInt(void *fs, const char *name, int defaultValue);
CVAPI double cv_core_fileStorageReadDouble(void *fs, const char *name, double defaultValue);
CVAPI int cv_core_fileStorageReadString(void *fs, const char *name, const char *defaultValue, char *buf, int bufSize);
CVAPI void cv_core_fileStorageReadMat(void *fs, const char *name, cv::Mat **pmat);
CVAPI void cv_core_fileStorageStartWriteStruct(void *fs, const char *name, int flags, const char *typeName);
CVAPI void cv_core_fileStorageEndWriteStruct(void *fs);
CVAPI int cv_core_fileStorageGetFormat(void *fs);

#endif
