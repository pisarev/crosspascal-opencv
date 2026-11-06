/* Copyright (c) 2026 Yuriy Pisarev                 */


#ifndef CV_IMGPROC_H
#define CV_IMGPROC_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/imgproc.hpp>


CVAPI int cv_imgproc_convertColor(cv::Mat *src, cv::Mat **pDst, int code);


CVAPI int cv_imgproc_bilateralFilter(cv::Mat *src, cv::Mat **pDst, int d, double sigmaColor, double sigmaSpace, int borderType);
CVAPI int cv_imgproc_blur(cv::Mat *src, cv::Mat **pDst, CVSize kSize, int borderType);
CVAPI int cv_imgproc_gaussianBlur(cv::Mat *src, cv::Mat **pDst, CVSize kSize, double sigmaX, double sigmaY, int borderType);
CVAPI int cv_imgproc_medianBlur(cv::Mat *src, cv::Mat **pDst, int kSize);
CVAPI int cv_imgproc_boxFilter(cv::Mat *src, cv::Mat **pDst, int ddepth, CVSize kSize, CVPoint anchor, int normalize, int borderType);
CVAPI int cv_imgproc_sqrBoxFilter(cv::Mat *src, cv::Mat **pDst, int ddepth, CVSize kSize, CVPoint anchor, int normalize, int borderType);
CVAPI int cv_imgproc_filter2D(cv::Mat *src, cv::Mat **pDst, int ddepth, cv::Mat *kernel, CVPoint anchor, double delta, int borderType);
CVAPI int cv_imgproc_sepFilter2D(cv::Mat *src, cv::Mat **pDst, int ddepth, cv::Mat *kernelX, cv::Mat *kernelY, CVPoint anchor, double delta, int borderType);
CVAPI int cv_imgproc_getGaborKernel(CVSize kSize, double sigma, double theta, double lambd, double gamma, double psi, int kType, cv::Mat **pDst);


CVAPI int cv_imgproc_sobel(cv::Mat *src, cv::Mat **pDst, int ddepth, int dx, int dy, int kSize, double scale, double delta, int borderType);
CVAPI int cv_imgproc_scharr(cv::Mat *src, cv::Mat **pDst, int ddepth, int dx, int dy, double scale, double delta, int borderType);
CVAPI int cv_imgproc_laplacian(cv::Mat *src, cv::Mat **pDst, int ddepth, int kSize, double scale, double delta, int borderType);
CVAPI int cv_imgproc_canny(cv::Mat *src, cv::Mat **pDst, double threshold1, double threshold2, int apertureSize, int L2gradient);


CVAPI int cv_imgproc_erode(cv::Mat *src, cv::Mat **pDst, cv::Mat *kernel, int iterations, int borderType);
CVAPI int cv_imgproc_dilate(cv::Mat *src, cv::Mat **pDst, cv::Mat *kernel, int iterations, int borderType);
CVAPI int cv_imgproc_morphologyEx(cv::Mat *src, cv::Mat **pDst, int op, cv::Mat *kernel, int iterations, int borderType);
CVAPI int cv_imgproc_createStructuringElement(int shape, CVSize kSize, CVPoint anchor, cv::Mat **pDst);


CVAPI int cv_imgproc_threshold(cv::Mat *src, cv::Mat **pDst, double thresh, double maxval, int type);
CVAPI int cv_imgproc_adaptiveThreshold(cv::Mat *src, cv::Mat **pDst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C);


CVAPI int cv_imgproc_resizeImage(cv::Mat *src, cv::Mat **pDst, CVSize dSize, double fx, double fy, int interpolation);
CVAPI int cv_imgproc_rotateImage(cv::Mat *src, cv::Mat **pDst, int rotateCode);
CVAPI int cv_imgproc_deskew(cv::Mat *src, cv::Mat **pDst, double angle);
CVAPI int cv_imgproc_warpAffine(cv::Mat *src, cv::Mat **pDst, cv::Mat *M, CVSize dSize, int flags, int borderMode, CVScalar borderValue);
CVAPI int cv_imgproc_warpPerspective(cv::Mat *src, cv::Mat **pDst, cv::Mat *M, CVSize dSize, int flags, int borderMode, CVScalar borderValue);
CVAPI int cv_imgproc_remap(cv::Mat *src, cv::Mat **pDst, cv::Mat *map1, cv::Mat *map2, int interpolation, int borderMode, CVScalar borderValue);
CVAPI int cv_imgproc_getRotationMatrix2D(CVPoint2f center, double angle, double scale, cv::Mat **pDst);
CVAPI int cv_imgproc_getAffineTransform(CVPoint2f *src, CVPoint2f *dst, cv::Mat **pResult);
CVAPI int cv_imgproc_getPerspectiveTransform(CVPoint2f *src, CVPoint2f *dst, cv::Mat **pResult);


CVAPI int cv_imgproc_houghLinesP(cv::Mat *src, double rho, double theta, int threshold, int minLineLength, int maxLineGap, GetData get, void *data);
CVAPI int cv_imgproc_houghLines(cv::Mat *src, double rho, double theta, int threshold, double srn, double stn, GetData get, void *data);
CVAPI int cv_imgproc_houghCircles(cv::Mat *src, int method, double dp, double minDist, double param1, double param2, int minRadius, int maxRadius, GetData get, void *data);


CVAPI int cv_imgproc_denoise(cv::Mat *src, cv::Mat **pDst, double h, int templateWindowSize, int searchWindowSize);
CVAPI int cv_imgproc_reverse(cv::Mat *src, cv::Mat **pDst);
CVAPI int cv_imgproc_adjustGamma(cv::Mat *src, cv::Mat **pDst, double gamma);
CVAPI int cv_imgproc_equalizeHist(cv::Mat *src, cv::Mat **pDst);


CVAPI int cv_imgproc_findContours(cv::Mat *src, int mode, int method, CVPoint offset, GetData get, void *data);
typedef void (GetDataParent)(int count, void *from, int parent, void *data);
CVAPI int cv_imgproc_findContoursHierarchy(cv::Mat *src, int mode, int method, CVPoint offset, GetDataParent get, void *data);
CVAPI int cv_imgproc_drawContours(cv::Mat **pImage, cv::Mat *contours, int contourIdx, CVScalar color, int thickness, int lineType);
CVAPI int cv_imgproc_boundingRect(cv::Mat *contour, CVRect *result);
CVAPI int cv_imgproc_contourArea(cv::Mat *contour, int oriented, double *area);
CVAPI int cv_imgproc_arcLength(cv::Mat *curve, int closed, double *length);
CVAPI int cv_imgproc_convexHull(cv::Mat *src, cv::Mat **pDst, int clockwise);
CVAPI int cv_imgproc_fitEllipse(cv::Mat *points, CVRotatedRect *result);
CVAPI int cv_imgproc_fitLine(cv::Mat *points, cv::Mat **pDst, int distType, double param, double reps, double aeps);
CVAPI int cv_imgproc_matchShapes(cv::Mat *contour1, cv::Mat *contour2, int method, double parameter, double *result);
CVAPI int cv_imgproc_moments(cv::Mat *src, int binaryImage, CVMoments *result);


CVAPI int cv_imgproc_straightenCurve(cv::Mat *src, cv::Mat **pDst, SetData set, void *data,
                                     int thickness, int interpolation, int borderType, double borderValue);
CVAPI int cv_imgproc_approximateCurve(cv::Mat *curve, cv::Mat **pDst, double epsilon, int closed);


CVAPI int cv_imgproc_watershed(cv::Mat *image, cv::Mat **pMarkers);
CVAPI int cv_imgproc_grabCut(cv::Mat *img, cv::Mat **pMask, CVRect rect, cv::Mat **pBgdModel, cv::Mat **pFgdModel, int iterCount, int mode);
CVAPI int cv_imgproc_connectedComponents(cv::Mat *image, cv::Mat **pLabels, int connectivity, int ltype);
CVAPI int cv_imgproc_connectedComponentsWithStats(cv::Mat *image, cv::Mat **pLabels, cv::Mat **pStats, cv::Mat **pCentroids, int connectivity, int ltype);


CVAPI int cv_imgproc_pyrUp(cv::Mat *src, cv::Mat **pDst, CVSize dSize, int borderType);
CVAPI int cv_imgproc_pyrDown(cv::Mat *src, cv::Mat **pDst, CVSize dSize, int borderType);
CVAPI int cv_imgproc_pyrMeanShiftFiltering(cv::Mat *src, cv::Mat **pDst, double sp, double sr, int maxLevel);


CVAPI int cv_imgproc_distanceTransform(cv::Mat *src, cv::Mat **pDst, int distanceType, int maskSize);
CVAPI int cv_imgproc_floodFill(cv::Mat **pImage, cv::Mat **pMask, CVPoint seedPoint, CVScalar newVal, CVScalar loDiff, CVScalar upDiff, int flags);
CVAPI int cv_imgproc_integral(cv::Mat *src, cv::Mat **pSum, cv::Mat **pSqSum, cv::Mat **pTilted, int sDepth, int sqDepth);


CVAPI int cv_imgproc_calcHist(cv::Mat *image, int channel, cv::Mat *mask, cv::Mat **pHist, int histSize, float rangeMin, float rangeMax, int accumulate);
CVAPI int cv_imgproc_compareHist(cv::Mat *H1, cv::Mat *H2, int method, double *result);
CVAPI int cv_imgproc_calcBackProject(cv::Mat *image, int channel, cv::Mat *hist, cv::Mat **pDst, float rangeMin, float rangeMax, double scale);


CVAPI int cv_imgproc_drawLine(cv::Mat **pImg, CVPoint pt1, CVPoint pt2, CVScalar color, int thickness, int lineType);
CVAPI int cv_imgproc_drawRectangle(cv::Mat **pImg, CVRect rect, CVScalar color, int thickness, int lineType);
CVAPI int cv_imgproc_drawCircle(cv::Mat **pImg, CVPoint center, int radius, CVScalar color, int thickness, int lineType);
CVAPI int cv_imgproc_drawEllipse(cv::Mat **pImg, CVPoint center, CVSize axes, double angle, double startAngle, double endAngle, CVScalar color, int thickness, int lineType);
CVAPI int cv_imgproc_drawPolylines(cv::Mat **pImg, CVPoint *pts, int *npts, int nCurves, int isClosed, CVScalar color, int thickness, int lineType);
CVAPI int cv_imgproc_drawPolylinesShift(cv::Mat **pImg, CVPoint *pts, int *npts, int nCurves, int isClosed, CVScalar color, int thickness, int lineType, int shift);
CVAPI int cv_imgproc_fillPoly(cv::Mat **pImg, CVPoint *pts, int *npts, int nCurves, CVScalar color, int lineType);
CVAPI int cv_imgproc_putText(cv::Mat **pImg, const char *text, CVPoint org, int fontFace, double fontScale, CVScalar color, int thickness, int lineType, int bottomLeftOrigin);
CVAPI int cv_imgproc_getTextSize(const char *text, int fontFace, double fontScale, int thickness, int *baseLine, CVSize *result);
CVAPI int cv_imgproc_arrowedLine(cv::Mat **pImg, CVPoint pt1, CVPoint pt2, CVScalar color, int thickness, int lineType, double tipLength);
CVAPI int cv_imgproc_drawMarker(cv::Mat **pImg, CVPoint position, CVScalar color, int markerType, int markerSize, int thickness, int lineType);


CVAPI int cv_imgproc_cornerHarris(cv::Mat *src, cv::Mat **pDst, int blockSize, int ksize, double k, int borderType);
CVAPI int cv_imgproc_cornerMinEigenVal(cv::Mat *src, cv::Mat **pDst, int blockSize, int ksize, int borderType);
CVAPI int cv_imgproc_preCornerDetect(cv::Mat *src, cv::Mat **pDst, int ksize, int borderType);
CVAPI int cv_imgproc_cornerSubPix(cv::Mat *image, cv::Mat **pCorners, CVSize winSize, CVSize zeroZone, int maxCount, double epsilon);


CVAPI int cv_imgproc_matchTemplate(cv::Mat *image, cv::Mat *templ, cv::Mat **pResult, int method, cv::Mat *mask);
CVAPI int cv_imgproc_phaseCorrelate(cv::Mat *src1, cv::Mat *src2, cv::Mat *window, double *response, CVPoint2f *shift);


CVAPI int cv_imgproc_cvtColorTwoPlane(cv::Mat *src1, cv::Mat *src2, cv::Mat **pDst, int code);


CVAPI int cv_imgproc_logPolar(cv::Mat *src, cv::Mat **pDst, CVPoint2f center, double M, int flags);
CVAPI int cv_imgproc_linearPolar(cv::Mat *src, cv::Mat **pDst, CVPoint2f center, double maxRadius, int flags);
CVAPI int cv_imgproc_warpPolar(cv::Mat *src, cv::Mat **pDst, int dstW, int dstH, CVPoint2f center, double maxRadius, int flags);


CVAPI int cv_imgproc_accumulate(cv::Mat *src, cv::Mat **pDst, cv::Mat *mask);
CVAPI int cv_imgproc_accumulateSquare(cv::Mat *src, cv::Mat **pDst, cv::Mat *mask);
CVAPI int cv_imgproc_accumulateProduct(cv::Mat *src1, cv::Mat *src2, cv::Mat **pDst, cv::Mat *mask);
CVAPI int cv_imgproc_accumulateWeighted(cv::Mat *src, cv::Mat **pDst, double alpha, cv::Mat *mask);
CVAPI int cv_imgproc_createHanningWindow(cv::Mat **pDst, int winW, int winH, int type);


CVAPI int cv_imgproc_minEnclosingCircle(cv::Mat *points, CVPoint2f *center, float *radius);
CVAPI int cv_imgproc_minEnclosingTriangle(cv::Mat *points, cv::Mat **pTriangle);
CVAPI double cv_imgproc_pointPolygonTest(cv::Mat *contour, CVPoint2f pt, int measureDist);
CVAPI int cv_imgproc_isContourConvex(cv::Mat *contour);
CVAPI int cv_imgproc_approxPolyDP(cv::Mat *curve, cv::Mat **pApproxCurve, double epsilon, int closed);
CVAPI int cv_imgproc_HuMoments(CVMoments *moments, double *hu);


// Allocate maxlevel + 1 output slots. On success count reports the written slots.
CVAPI int cv_imgproc_buildPyramid(cv::Mat *src, cv::Mat **pDst, int *count, int maxlevel, int borderType);


CVAPI int cv_imgproc_invertAffineTransform(cv::Mat *M, cv::Mat **pIM);
CVAPI int cv_imgproc_clipLine(int imgW, int imgH, CVPoint *pt1, CVPoint *pt2);
CVAPI int cv_imgproc_ellipse2Poly(CVPoint center, CVSize axes, int angle, int arcStart, int arcEnd, int delta, CVPoint *pts, int *count, int maxCount);


CVAPI int cv_imgproc_getGaussianKernel(int ksize, double sigma, int ktype, cv::Mat **pDst);
CVAPI int cv_imgproc_convertMaps(cv::Mat *map1, cv::Mat *map2, cv::Mat **pDstmap1, cv::Mat **pDstmap2, int dstmap1type, int nninterpolation);


CVAPI void *cv_imgproc_createLineSegmentDetector(int refine, double scale, double sigma_scale, double quant, double ang_th, double log_eps, double density_th, int n_bins);
CVAPI int cv_imgproc_deleteLineSegmentDetector(void *lsd);
CVAPI int cv_imgproc_lsdDetect(void *lsd, cv::Mat *image, cv::Mat **pLines);


CVAPI int cv_imgproc_goodFeaturesToTrack(cv::Mat *image, cv::Mat **pCorners, int maxCorners, double qualityLevel, double minDistance, cv::Mat *mask, int blockSize, int useHarrisDetector, double k);


CVAPI int cv_imgproc_stackBlur(cv::Mat *src, cv::Mat **pDst, int kW, int kH);


CVAPI int cv_imgproc_spatialGradient(cv::Mat *src, cv::Mat **pDx, cv::Mat **pDy, int ksize, int borderType);


CVAPI int cv_imgproc_cornerEigenValsAndVecs(cv::Mat *src, cv::Mat **pDst, int blockSize, int apertureSize, int borderType);


CVAPI int cv_imgproc_getDerivKernels(cv::Mat **pKx, cv::Mat **pKy, int dx, int dy, int ksize, int normalize, int ktype);


CVAPI int cv_imgproc_getRectSubPix(cv::Mat *image, int patchW, int patchH, CVPoint2f center, cv::Mat **pPatch, int patchType);


CVAPI int cv_imgproc_fillConvexPoly(cv::Mat **pImg, CVPoint *pts, int npts, CVScalar color, int lineType, int shift);


CVAPI int cv_imgproc_convexityDefects(cv::Mat *contour, cv::Mat *convexhull, cv::Mat **pConvexityDefects);
CVAPI int cv_imgproc_intersectConvexConvex(cv::Mat *p1, cv::Mat *p2, cv::Mat **pP12, int handleNested);
CVAPI int cv_imgproc_rotatedRectangleIntersection(CVRotatedRect *rect1, CVRotatedRect *rect2, cv::Mat **pIntersectingRegion);


CVAPI int cv_imgproc_applyColorMap(cv::Mat *src, cv::Mat **pDst, int colormap);


CVAPI int cv_imgproc_demosaicing(cv::Mat *src, cv::Mat **pDst, int code, int dstCn);


CVAPI int cv_imgproc_integral2(cv::Mat *src, cv::Mat **pSum, cv::Mat **pSqSum, int sdepth, int sqdepth);
CVAPI int cv_imgproc_integral3(cv::Mat *src, cv::Mat **pSum, cv::Mat **pSqSum, cv::Mat **pTilted, int sdepth, int sqdepth);


CVAPI double cv_imgproc_getFontScaleFromHeight(int fontFace, int pixelHeight, int thickness);


CVAPI void *cv_imgproc_createGeneralizedHoughBallard();
CVAPI void *cv_imgproc_createGeneralizedHoughGuil();
CVAPI int cv_imgproc_deleteGeneralizedHough(void *hough);


CVAPI int cv_imgproc_blendLinear(cv::Mat *src1, cv::Mat *src2, cv::Mat *weights1, cv::Mat *weights2, cv::Mat **pDst);


// Pass null contours to query the count. Otherwise supply capacity in *contourCount.
// A short buffer stays unchanged and the call returns zero and the required count.
CVAPI int cv_imgproc_findContoursLinkRuns(cv::Mat *image, cv::Mat **pContours, int *contourCount);


CVAPI int cv_imgproc_fitEllipseAMS(cv::Mat *points, CVRotatedRect *result);
CVAPI int cv_imgproc_fitEllipseDirect(cv::Mat *points, CVRotatedRect *result);


CVAPI int cv_imgproc_goodFeaturesToTrackWithQuality(cv::Mat *image, cv::Mat **pCorners, int maxCorners, double qualityLevel, double minDistance, cv::Mat *mask, cv::Mat **pCornersQuality, int blockSize, int gradientSize, int useHarrisDetector, double k);


CVAPI int cv_imgproc_HoughLinesPointSet(cv::Mat *point, cv::Mat **pLines, int lines_max, int threshold, double min_rho, double max_rho, double rho_step, double min_theta, double max_theta, double theta_step);


CVAPI float cv_imgproc_EMD(cv::Mat *signature1, cv::Mat *signature2, int distType, cv::Mat *cost, float *lowerBound, cv::Mat **pFlow);


CVAPI int cv_imgproc_getStructuringElementEx(int shape, int kW, int kH, int anchorX, int anchorY, cv::Mat **pDst);


CVAPI int cv_imgproc_lsdDrawSegments(cv::Mat **pImage, cv::Mat *lines, CVScalar color);
CVAPI int cv_imgproc_lsdCompareSegments(int width, int height, cv::Mat *lines1, cv::Mat *lines2, cv::Mat **pImage);


CVAPI CVScalar cv_imgproc_morphologyDefaultBorderValue();


CVAPI int cv_imgproc_phaseCorrelateResult(cv::Mat *src1, cv::Mat *src2, cv::Mat *window, double *response, double *shiftX, double *shiftY);


CVAPI void *cv_imgproc_createSubdiv2D(int x, int y, int width, int height);
CVAPI int cv_imgproc_deleteSubdiv2D(void *subdiv);
CVAPI int cv_imgproc_subdiv2DInitDelaunay(void *subdiv, int x, int y, int width, int height);
CVAPI int cv_imgproc_subdiv2DInsert(void *subdiv, float x, float y);
CVAPI int cv_imgproc_subdiv2DInsertMulti(void *subdiv, CVPoint2f *pts, int count);
CVAPI int cv_imgproc_subdiv2DLocate(void *subdiv, float x, float y, int *edge, int *vertex);
CVAPI int cv_imgproc_subdiv2DFindNearest(void *subdiv, float x, float y, float *nearestX, float *nearestY);
CVAPI int cv_imgproc_subdiv2DGetEdgeList(void *subdiv, float *edges, int *count, int maxCount);
CVAPI int cv_imgproc_subdiv2DGetLeadingEdgeList(void *subdiv, int *leadingEdges, int *count, int maxCount);
CVAPI int cv_imgproc_subdiv2DGetTriangleList(void *subdiv, float *triangles, int *count, int maxCount);
CVAPI int cv_imgproc_subdiv2DGetVoronoiFacetList(void *subdiv, int *idx, int idxCount, CVPoint2f *facetCenters, int *facetCount, int maxFacets);
CVAPI int cv_imgproc_subdiv2DGetVertex(void *subdiv, int vertex, int *firstEdge, float *ptX, float *ptY);
CVAPI int cv_imgproc_subdiv2DGetEdge(void *subdiv, int edge, int nextEdgeType);
CVAPI int cv_imgproc_subdiv2DNextEdge(void *subdiv, int edge);
CVAPI int cv_imgproc_subdiv2DRotateEdge(void *subdiv, int edge, int rotate);
CVAPI int cv_imgproc_subdiv2DSymEdge(void *subdiv, int edge);
CVAPI int cv_imgproc_subdiv2DEdgeOrg(void *subdiv, int edge, float *ptX, float *ptY);
CVAPI int cv_imgproc_subdiv2DEdgeDst(void *subdiv, int edge, float *ptX, float *ptY);


CVAPI void cv_imgproc_generalizedHoughSetTemplate(void *hough, cv::Mat *templ, CVPoint templCenter);
CVAPI void cv_imgproc_generalizedHoughSetTemplateWithEdges(void *hough, cv::Mat *edges, cv::Mat *dx, cv::Mat *dy, CVPoint templCenter);
CVAPI void cv_imgproc_generalizedHoughDetect(void *hough, cv::Mat *image, cv::Mat **pPositions, cv::Mat **pVotes);
CVAPI void cv_imgproc_generalizedHoughDetectWithEdges(void *hough, cv::Mat *edges, cv::Mat *dx, cv::Mat *dy, cv::Mat **pPositions, cv::Mat **pVotes);
CVAPI double cv_imgproc_generalizedHoughGetCannyLowThresh(void *hough);
CVAPI void cv_imgproc_generalizedHoughSetCannyLowThresh(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGetCannyHighThresh(void *hough);
CVAPI void cv_imgproc_generalizedHoughSetCannyHighThresh(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGetMinDist(void *hough);
CVAPI void cv_imgproc_generalizedHoughSetMinDist(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGetDp(void *hough);
CVAPI void cv_imgproc_generalizedHoughSetDp(void *hough, double value);
CVAPI int cv_imgproc_generalizedHoughGetMaxBufferSize(void *hough);
CVAPI void cv_imgproc_generalizedHoughSetMaxBufferSize(void *hough, int value);


CVAPI int cv_imgproc_generalizedHoughBallardGetLevels(void *hough);
CVAPI void cv_imgproc_generalizedHoughBallardSetLevels(void *hough, int value);
CVAPI int cv_imgproc_generalizedHoughBallardGetVotesThreshold(void *hough);
CVAPI void cv_imgproc_generalizedHoughBallardSetVotesThreshold(void *hough, int value);


CVAPI double cv_imgproc_generalizedHoughGuilGetMinAngle(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetMinAngle(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGuilGetMaxAngle(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetMaxAngle(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGuilGetAngleStep(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetAngleStep(void *hough, double value);
CVAPI int cv_imgproc_generalizedHoughGuilGetAngleThresh(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetAngleThresh(void *hough, int value);
CVAPI double cv_imgproc_generalizedHoughGuilGetMinScale(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetMinScale(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGuilGetMaxScale(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetMaxScale(void *hough, double value);
CVAPI double cv_imgproc_generalizedHoughGuilGetScaleStep(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetScaleStep(void *hough, double value);
CVAPI int cv_imgproc_generalizedHoughGuilGetScaleThresh(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetScaleThresh(void *hough, int value);
CVAPI int cv_imgproc_generalizedHoughGuilGetPosThresh(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetPosThresh(void *hough, int value);
CVAPI double cv_imgproc_generalizedHoughGuilGetXi(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetXi(void *hough, double value);
CVAPI int cv_imgproc_generalizedHoughGuilGetLevels(void *hough);
CVAPI void cv_imgproc_generalizedHoughGuilSetLevels(void *hough, int value);


CVAPI int cv_imgproc_lsdGetLines(void *lsd, cv::Mat **pLines);

#endif
