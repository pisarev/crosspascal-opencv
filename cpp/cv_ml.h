
/* Copyright (c) 2026 Yuriy Pisarev                 */

#ifndef CV_ML_H
#define CV_ML_H

#include "cv_export.h"
#include "cv_types.h"
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>


struct svm_model;

CVAPI int cv_ml_createSVM(int kernelType, int svmType, double C, double gamma, double degree, double coef0, double nu, double p, void **handle);
CVAPI int cv_ml_deleteSVM(void *svm);
CVAPI int cv_ml_saveSVM(void *svm, const char *filename);
CVAPI int cv_ml_trainSVM(void *svm, cv::Mat *trainData, cv::Mat *labels);
CVAPI int cv_ml_predict(void *svm, cv::Mat *sample, double *result);
CVAPI int cv_ml_predictArray(void *svm, cv::Mat *samples, cv::Mat **results, int flags);

CVAPI int cv_ml_createSVMModel(const char *filename, void **handle);
CVAPI int cv_ml_deleteSVMModel(void *model);
CVAPI int cv_ml_computeScore(void *model, cv::Mat *testData, cv::Mat *testLabels, double *score);
CVAPI int cv_ml_trainSVMModel(void *model, cv::Mat *trainData, cv::Mat *labels, GetData get, void *data);

CVAPI void *cv_ml_createKNearest();
CVAPI int cv_ml_deleteKNearest(void *knearest);
CVAPI int cv_ml_kNearestFindNearest(void *knearest, cv::Mat *samples, int k, cv::Mat **results, cv::Mat **neighborResponses, cv::Mat **dist);
CVAPI int cv_ml_kNearestTrain(void *knearest, cv::Mat *samples, int layout, cv::Mat *responses);
CVAPI int cv_ml_kNearestSetDefaultK(void *knearest, int k);

CVAPI void *cv_ml_createDTrees();
CVAPI int cv_ml_deleteDTrees(void *dtrees);

CVAPI void *cv_ml_createRTrees();
CVAPI int cv_ml_deleteRTrees(void *rtrees);

CVAPI void *cv_ml_createBoost();
CVAPI int cv_ml_deleteBoost(void *boost);

CVAPI void *cv_ml_createANN_MLP();
CVAPI int cv_ml_deleteANN_MLP(void *ann);
CVAPI int cv_ml_annSetLayerSizes(void *ann, cv::Mat *layerSizes);
CVAPI int cv_ml_annSetActivationFunction(void *ann, int type, double param1, double param2);

CVAPI void *cv_ml_createLogisticRegression();
CVAPI int cv_ml_deleteLogisticRegression(void *lr);

CVAPI void *cv_ml_createNormalBayesClassifier();
CVAPI int cv_ml_deleteNormalBayesClassifier(void *nbc);

CVAPI int cv_ml_statModelTrain(void *model, cv::Mat *samples, int layout, cv::Mat *responses);
CVAPI float cv_ml_statModelPredict(void *model, cv::Mat *samples, cv::Mat **results, int flags);

CVAPI int cv_ml_statModelIsTrained(void *model);
CVAPI int cv_ml_statModelIsClassifier(void *model);
CVAPI int cv_ml_statModelGetVarCount(void *model);
CVAPI int cv_ml_statModelEmpty(void *model);
CVAPI int cv_ml_statModelSave(void *model, const char *filename);
CVAPI void *cv_ml_statModelLoad(const char *filename, const char *modelType);

CVAPI int cv_ml_svmGetType(void *svm);
CVAPI int cv_ml_svmSetType(void *svm, int type);
CVAPI int cv_ml_svmGetKernelType(void *svm);
CVAPI int cv_ml_svmSetKernel(void *svm, int kernelType);
CVAPI double cv_ml_svmGetC(void *svm);
CVAPI int cv_ml_svmSetC(void *svm, double val);
CVAPI double cv_ml_svmGetGamma(void *svm);
CVAPI int cv_ml_svmSetGamma(void *svm, double val);
CVAPI double cv_ml_svmGetDegree(void *svm);
CVAPI int cv_ml_svmSetDegree(void *svm, double val);
CVAPI double cv_ml_svmGetCoef0(void *svm);
CVAPI int cv_ml_svmSetCoef0(void *svm, double val);
CVAPI double cv_ml_svmGetNu(void *svm);
CVAPI int cv_ml_svmSetNu(void *svm, double val);
CVAPI double cv_ml_svmGetP(void *svm);
CVAPI int cv_ml_svmSetP(void *svm, double val);
CVAPI int cv_ml_svmTrainAuto(void *svm, cv::Mat *samples, int layout, cv::Mat *responses, int kFold, int balanced);
CVAPI int cv_ml_svmGetSupportVectors(void *svm, cv::Mat **sv);
CVAPI int cv_ml_svmGetDecisionFunction(void *svm, int i, cv::Mat **alpha, cv::Mat **svidx);

CVAPI int cv_ml_kNearestGetDefaultK(void *knearest);
CVAPI int cv_ml_kNearestSetIsClassifier(void *knearest, int val);
CVAPI int cv_ml_kNearestGetIsClassifier(void *knearest);
CVAPI int cv_ml_kNearestGetEmax(void *knearest);
CVAPI int cv_ml_kNearestSetEmax(void *knearest, int val);
CVAPI int cv_ml_kNearestGetAlgorithmType(void *knearest);
CVAPI int cv_ml_kNearestSetAlgorithmType(void *knearest, int val);

CVAPI int cv_ml_dTreesGetMaxDepth(void *dtrees);
CVAPI int cv_ml_dTreesSetMaxDepth(void *dtrees, int val);
CVAPI int cv_ml_dTreesGetMinSampleCount(void *dtrees);
CVAPI int cv_ml_dTreesSetMinSampleCount(void *dtrees, int val);
CVAPI int cv_ml_dTreesGetMaxCategories(void *dtrees);
CVAPI int cv_ml_dTreesSetMaxCategories(void *dtrees, int val);
CVAPI int cv_ml_dTreesGetCVFolds(void *dtrees);
CVAPI int cv_ml_dTreesSetCVFolds(void *dtrees, int val);
CVAPI int cv_ml_dTreesGetUseSurrogates(void *dtrees);
CVAPI int cv_ml_dTreesSetUseSurrogates(void *dtrees, int val);
CVAPI int cv_ml_dTreesGetUse1SERule(void *dtrees);
CVAPI int cv_ml_dTreesSetUse1SERule(void *dtrees, int val);
CVAPI int cv_ml_dTreesGetTruncatePrunedTree(void *dtrees);
CVAPI int cv_ml_dTreesSetTruncatePrunedTree(void *dtrees, int val);
CVAPI float cv_ml_dTreesGetRegressionAccuracy(void *dtrees);
CVAPI int cv_ml_dTreesSetRegressionAccuracy(void *dtrees, float val);

CVAPI int cv_ml_rTreesGetActiveVarCount(void *rtrees);
CVAPI int cv_ml_rTreesSetActiveVarCount(void *rtrees, int val);
CVAPI int cv_ml_rTreesGetCalculateVarImportance(void *rtrees);
CVAPI int cv_ml_rTreesSetCalculateVarImportance(void *rtrees, int val);
CVAPI int cv_ml_rTreesGetVarImportance(void *rtrees, cv::Mat **varImportance);

CVAPI int cv_ml_boostGetBoostType(void *boost);
CVAPI int cv_ml_boostSetBoostType(void *boost, int val);
CVAPI int cv_ml_boostGetWeakCount(void *boost);
CVAPI int cv_ml_boostSetWeakCount(void *boost, int val);
CVAPI double cv_ml_boostGetWeightTrimRate(void *boost);
CVAPI int cv_ml_boostSetWeightTrimRate(void *boost, double val);

CVAPI int cv_ml_annGetTrainMethod(void *ann);
CVAPI int cv_ml_annSetTrainMethod(void *ann, int method, double param1, double param2);
CVAPI double cv_ml_annGetBackpropWeightScale(void *ann);
CVAPI int cv_ml_annSetBackpropWeightScale(void *ann, double val);
CVAPI double cv_ml_annGetBackpropMomentumScale(void *ann);
CVAPI int cv_ml_annSetBackpropMomentumScale(void *ann, double val);
CVAPI double cv_ml_annGetRpropDW0(void *ann);
CVAPI int cv_ml_annSetRpropDW0(void *ann, double val);
CVAPI double cv_ml_annGetRpropDWPlus(void *ann);
CVAPI int cv_ml_annSetRpropDWPlus(void *ann, double val);
CVAPI double cv_ml_annGetRpropDWMinus(void *ann);
CVAPI int cv_ml_annSetRpropDWMinus(void *ann, double val);
CVAPI int cv_ml_annGetWeights(void *ann, int layerIdx, cv::Mat **weights);

CVAPI void *cv_ml_createEM();
CVAPI int cv_ml_deleteEM(void *em);
CVAPI int cv_ml_emTrainEM(void *em, cv::Mat *samples, cv::Mat **logLikelihoods, cv::Mat **labels, cv::Mat **probs);
CVAPI int cv_ml_emPredict(void *em, cv::Mat *sample, cv::Mat **probs, double *result);
CVAPI int cv_ml_emGetClustersNumber(void *em);
CVAPI int cv_ml_emSetClustersNumber(void *em, int val);
CVAPI int cv_ml_emGetCovarianceMatrixType(void *em);
CVAPI int cv_ml_emSetCovarianceMatrixType(void *em, int val);
CVAPI int cv_ml_emGetMeans(void *em, cv::Mat **means);
CVAPI int cv_ml_emGetWeights(void *em, cv::Mat **weights);

CVAPI void *cv_ml_createSVMSGD();
CVAPI int cv_ml_deleteSVMSGD(void *svmsgd);
CVAPI int cv_ml_svmsgdGetSvmsgdType(void *svmsgd);
CVAPI int cv_ml_svmsgdSetSvmsgdType(void *svmsgd, int svmsgdType);
CVAPI int cv_ml_svmsgdGetMarginType(void *svmsgd);
CVAPI int cv_ml_svmsgdSetMarginType(void *svmsgd, int marginType);
CVAPI float cv_ml_svmsgdGetMarginRegularization(void *svmsgd);
CVAPI int cv_ml_svmsgdSetMarginRegularization(void *svmsgd, float val);
CVAPI float cv_ml_svmsgdGetInitialStepSize(void *svmsgd);
CVAPI int cv_ml_svmsgdSetInitialStepSize(void *svmsgd, float val);
CVAPI float cv_ml_svmsgdGetStepDecreasingPower(void *svmsgd);
CVAPI int cv_ml_svmsgdSetStepDecreasingPower(void *svmsgd, float val);
CVAPI int cv_ml_svmsgdGetWeights(void *svmsgd, cv::Mat **weights);
CVAPI float cv_ml_svmsgdGetShift(void *svmsgd);

CVAPI double cv_ml_logRegGetLearningRate(void *logreg);
CVAPI int cv_ml_logRegSetLearningRate(void *logreg, double val);
CVAPI int cv_ml_logRegGetIterations(void *logreg);
CVAPI int cv_ml_logRegSetIterations(void *logreg, int val);
CVAPI int cv_ml_logRegGetRegularization(void *logreg);
CVAPI int cv_ml_logRegSetRegularization(void *logreg, int val);
CVAPI int cv_ml_logRegGetTrainMethod(void *logreg);
CVAPI int cv_ml_logRegSetTrainMethod(void *logreg, int val);
CVAPI int cv_ml_logRegGetMiniBatchSize(void *logreg);
CVAPI int cv_ml_logRegSetMiniBatchSize(void *logreg, int val);
CVAPI int cv_ml_logRegGetLearntThetas(void *logreg, cv::Mat **thetas);

CVAPI int cv_ml_bayesPredictProb(void *bayes, cv::Mat *inputs, cv::Mat **outputs, cv::Mat **outputProbs);

#endif
