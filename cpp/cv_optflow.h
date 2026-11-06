
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_OPTFLOW_H
#define CV_OPTFLOW_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/optflow.hpp>

CVAPI void *cv_optflow_createOptFlow_DualTVL1();
CVAPI int cv_optflow_deleteDualTVL1(void *flow);
CVAPI int cv_optflow_dualTVL1Calc(void *flow, cv::Mat *I0, cv::Mat *I1, cv::Mat **flowMat);
CVAPI double cv_optflow_dualTVL1GetTau(void *flow);
CVAPI int cv_optflow_dualTVL1SetTau(void *flow, double val);
CVAPI double cv_optflow_dualTVL1GetLambda(void *flow);
CVAPI int cv_optflow_dualTVL1SetLambda(void *flow, double val);
CVAPI double cv_optflow_dualTVL1GetTheta(void *flow);
CVAPI int cv_optflow_dualTVL1SetTheta(void *flow, double val);
CVAPI double cv_optflow_dualTVL1GetGamma(void *flow);
CVAPI int cv_optflow_dualTVL1SetGamma(void *flow, double val);
CVAPI int cv_optflow_dualTVL1GetScalesNumber(void *flow);
CVAPI int cv_optflow_dualTVL1SetScalesNumber(void *flow, int val);
CVAPI int cv_optflow_dualTVL1GetWarpingsNumber(void *flow);
CVAPI int cv_optflow_dualTVL1SetWarpingsNumber(void *flow, int val);
CVAPI double cv_optflow_dualTVL1GetEpsilon(void *flow);
CVAPI int cv_optflow_dualTVL1SetEpsilon(void *flow, double val);
CVAPI int cv_optflow_dualTVL1GetInnerIterations(void *flow);
CVAPI int cv_optflow_dualTVL1SetInnerIterations(void *flow, int val);
CVAPI int cv_optflow_dualTVL1GetOuterIterations(void *flow);
CVAPI int cv_optflow_dualTVL1SetOuterIterations(void *flow, int val);
CVAPI int cv_optflow_dualTVL1GetMedianFiltering(void *flow);
CVAPI int cv_optflow_dualTVL1SetMedianFiltering(void *flow, int val);
CVAPI int cv_optflow_dualTVL1GetUseInitialFlow(void *flow);
CVAPI int cv_optflow_dualTVL1SetUseInitialFlow(void *flow, int val);

CVAPI void *cv_optflow_createOptFlow_DeepFlow();
CVAPI void *cv_optflow_createOptFlow_SimpleFlow();
CVAPI void *cv_optflow_createOptFlow_PCAFlow();
CVAPI void *cv_optflow_createOptFlow_SparseToDense();
CVAPI int cv_optflow_deleteOptFlow(void *flow);

CVAPI int cv_optflow_calcOpticalFlowSF(cv::Mat *from, cv::Mat *to, cv::Mat **flow, int layers, int averagingBlockSize, int maxFlow);
CVAPI int cv_optflow_calcOpticalFlowSparseToDense(cv::Mat *from, cv::Mat *to, cv::Mat **flow, int gridStep, int k, float sigma, int usePostProc, float fgsLambda, float fgsSigma);

#endif
