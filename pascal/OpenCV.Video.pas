{ ************************************************************************** }
{                                                                            }
{ OpenCV.Video                                                               }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev                                             }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Video;

{$B-}
{$IFDEF FPC}
  {$MODE DELPHI}
{$ENDIF}

interface

uses
  {$IFDEF FPC}
  DynLibs,
  {$ELSE}
  WinApi.Windows,
  {$ENDIF}
  OpenCVTypes;

type
  TCVVideoModule = record
  public
    type
      TSetData = function(Count: Integer; Data: Pointer): Pointer; cdecl;
      TGoodFeaturesToTrack = function(Image: TMat; MaxCorners: Integer; QualityLevel, MinDistance: Double;
        Mask: TMat; BlockSize: Integer; UseHarrisDetector: LongBool; K: Double; &Set: TSetData;
        Data: Pointer): LongBool; cdecl;
      TCalcOpticalFlowPyrLK = function(PrevImg, NextImg: TMat; PrevPts: Pointer; PrevCount: Integer;
        WinSize: TOCVSize; MaxLevel: Integer; MaxCount: Integer; Epsilon: Double; &Set: TSetData;
        Data: Pointer): LongBool; cdecl;
      TCalcOpticalFlowFarneback = function(Prev, Next: TMat; Flow: PMat; PyrScale: Double;
        Levels, WinSize, Iterations, PolyN: Integer; PolySigma: Double; Flags: Integer): LongBool; cdecl;
      TCalcOpticalFlowDeepFlow = function(Prev, Next: TMat; Flow: PMat): LongBool; cdecl;
      TFindHomography = function(SrcPoints, DstPoints: Pointer; Count, Method: Integer;
        RansacReprojThreshold: Double; Target: PMat): LongBool; cdecl;
      TPerspectiveTransform = function(Source: TMat; Target: PMat; Transform: TMat): LongBool; cdecl;
      TCreateMOG2Subtractor = function(History: Integer; VarThreshold: Double; DetectShadows: LongBool;
        Handle: PPointer): LongBool; cdecl;
      TCreateKNNSubtractor = function(History: Integer; Dist2Threshold: Double; DetectShadows: LongBool;
        Handle: PPointer): LongBool; cdecl;
      TDeleteSubtractor = function(Handle: Pointer): LongBool; cdecl;
      TSubtractorApply = function(Handle: Pointer; Image: TMat; FgMask: PMat;
        LearningRate: Double): LongBool; cdecl;
      TBlockMatchingFlow = function(Prev, Next: TMat; Flow: PMat;
        BlockSize, ShiftSize, MaxRange: Integer): LongBool; cdecl;
      TBlockFlowTracking = function(Prev, Next: TMat; Flow: PMat; BlockSize, ShiftSize, MaxRange: Integer;
        &Set: TSetData; Data: Pointer): LongBool; cdecl;
      TBuildOpticalFlowPyramid = function(Image: TMat; Pyramid: PMat; WinSize: TOCVSize; MaxLevel: Integer;
        WithDerivatives: LongBool; PyrBorder, DerivBorder: Integer; Levels: PInteger): LongBool; cdecl;
      TCamShift = function(ProbImage: TMat; Window: POCVRect; MaxCount: Integer; Epsilon: Double;
        RotatedRect: POCVRotatedRect): LongBool; cdecl;
      TMeanShift = function(ProbImage: TMat; Window: POCVRect; MaxCount: Integer;
        Epsilon: Double): LongBool; cdecl;
      TSubtractorGetBackgroundImage = function(Handle: Pointer; BackgroundImage: PMat): LongBool; cdecl;
      TCreateDISOpticalFlow = function(Preset: Integer): Pointer; cdecl;
      TDeleteDISOpticalFlow = function(Handle: Pointer): LongBool; cdecl;
      TDISOpticalFlowCalc = function(Handle: Pointer; Prev, Next: TMat; Flow: PMat): LongBool; cdecl;
      TDISOpticalFlowSetFinestScale = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TReadOpticalFlow = function(Path: PAnsiChar; Flow: PMat): LongBool; cdecl;
      TWriteOpticalFlow = function(Path: PAnsiChar; Flow: TMat): LongBool; cdecl;
      TFindTransformECC = function(TemplateImage, InputImage: TMat; WarpMatrix: PMat;
        MotionType, MaxCount: Integer; Epsilon: Double; InputMask: TMat;
        GaussFiltSize: Integer): LongBool; cdecl;
      TEstimateRigidTransform = function(Source, Target: TMat; M: PMat;
        FullAffine: LongBool): LongBool; cdecl;
      TComputeECC = function(TemplateImage, InputImage: TMat; InputMask: TMat;
        Result: PDouble): LongBool; cdecl;
      TCreateKalmanFilter = function(DynamParams, MeasureParams, ControlParams, &Type: Integer): Pointer; cdecl;
      TDeleteKalmanFilter = function(Handle: Pointer): LongBool; cdecl;
      TKalmanPredict = function(Handle: Pointer; Control: TMat; Result: PMat): LongBool; cdecl;
      TKalmanCorrect = function(Handle: Pointer; Measurement: TMat; Result: PMat): LongBool; cdecl;
      TKalmanGetStatePre = function(Handle: Pointer; Dst: PMat): LongBool; cdecl;
      TKalmanSetStatePre = function(Handle: Pointer; Src: TMat): LongBool; cdecl;
      TKalmanGetStatePost = function(Handle: Pointer; Dst: PMat): LongBool; cdecl;
      TKalmanSetStatePost = function(Handle: Pointer; Src: TMat): LongBool; cdecl;
      TKalmanGetTransitionMatrix = function(Handle: Pointer; Dst: PMat): LongBool; cdecl;
      TKalmanSetTransitionMatrix = function(Handle: Pointer; Src: TMat): LongBool; cdecl;
      TMOG2GetHistory = function(Handle: Pointer): Integer; cdecl;
      TMOG2SetHistory = function(Handle: Pointer; History: Integer): LongBool; cdecl;
      TMOG2GetNMixtures = function(Handle: Pointer): Integer; cdecl;
      TMOG2SetNMixtures = function(Handle: Pointer; NMixtures: Integer): LongBool; cdecl;
      TMOG2GetBackgroundRatio = function(Handle: Pointer): Double; cdecl;
      TMOG2SetBackgroundRatio = function(Handle: Pointer; Ratio: Double): LongBool; cdecl;
      TMOG2GetVarThreshold = function(Handle: Pointer): Double; cdecl;
      TMOG2SetVarThreshold = function(Handle: Pointer; VarThreshold: Double): LongBool; cdecl;
      TMOG2GetVarThresholdGen = function(Handle: Pointer): Double; cdecl;
      TMOG2SetVarThresholdGen = function(Handle: Pointer; VarThresholdGen: Double): LongBool; cdecl;
      TMOG2GetDetectShadows = function(Handle: Pointer): LongBool; cdecl;
      TMOG2SetDetectShadows = function(Handle: Pointer; DetectShadows: LongBool): LongBool; cdecl;
      TKNNGetHistory = function(Handle: Pointer): Integer; cdecl;
      TKNNSetHistory = function(Handle: Pointer; History: Integer): LongBool; cdecl;
      TKNNGetNSamples = function(Handle: Pointer): Integer; cdecl;
      TKNNSetNSamples = function(Handle: Pointer; NSamples: Integer): LongBool; cdecl;
      TKNNGetDist2Threshold = function(Handle: Pointer): Double; cdecl;
      TKNNSetDist2Threshold = function(Handle: Pointer; Dist2Threshold: Double): LongBool; cdecl;
      TKNNGetDetectShadows = function(Handle: Pointer): LongBool; cdecl;
      TKNNSetDetectShadows = function(Handle: Pointer; DetectShadows: LongBool): LongBool; cdecl;
      TKNNGetShadowValue = function(Handle: Pointer): Integer; cdecl;
      TKNNSetShadowValue = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TDISOpticalFlowGetFinestScale = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TDISOpticalFlowGetPatchSize = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TDISOpticalFlowSetPatchSize = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TDISOpticalFlowGetPatchStride = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TDISOpticalFlowSetPatchStride = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TDISOpticalFlowGetGradientDescentIterations = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TDISOpticalFlowSetGradientDescentIterations = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TDISOpticalFlowGetVariationalRefinementIterations = function(Handle: Pointer;
        Val: PInteger): LongBool; cdecl;
      TDISOpticalFlowSetVariationalRefinementIterations = function(Handle: Pointer;
        Val: Integer): LongBool; cdecl;
      TDISOpticalFlowGetVariationalRefinementAlpha = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TDISOpticalFlowSetVariationalRefinementAlpha = function(Handle: Pointer; Val: Single): LongBool; cdecl;
      TDISOpticalFlowGetVariationalRefinementDelta = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TDISOpticalFlowSetVariationalRefinementDelta = function(Handle: Pointer; Val: Single): LongBool; cdecl;
      TDISOpticalFlowGetVariationalRefinementGamma = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TDISOpticalFlowSetVariationalRefinementGamma = function(Handle: Pointer; Val: Single): LongBool; cdecl;
      TDISOpticalFlowGetUseMeanNormalization = function(Handle: Pointer; Val: PLongBool): LongBool; cdecl;
      TDISOpticalFlowSetUseMeanNormalization = function(Handle: Pointer; Val: LongBool): LongBool; cdecl;
      TDISOpticalFlowGetUseSpatialPropagation = function(Handle: Pointer; Val: PLongBool): LongBool; cdecl;
      TDISOpticalFlowSetUseSpatialPropagation = function(Handle: Pointer; Val: LongBool): LongBool; cdecl;
      TCreateFarnebackOpticalFlow = function: Pointer; cdecl;
      TDeleteFarnebackOpticalFlow = function(Handle: Pointer): LongBool; cdecl;
      TFarnebackOpticalFlowCalc = function(Handle: Pointer; Prev, Next: TMat; Flow: PMat): LongBool; cdecl;
      TFarnebackOpticalFlowGetNumLevels = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TFarnebackOpticalFlowSetNumLevels = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TFarnebackOpticalFlowGetPyrScale = function(Handle: Pointer; Val: PDouble): LongBool; cdecl;
      TFarnebackOpticalFlowSetPyrScale = function(Handle: Pointer; Val: Double): LongBool; cdecl;
      TFarnebackOpticalFlowGetFastPyramids = function(Handle: Pointer; Val: PLongBool): LongBool; cdecl;
      TFarnebackOpticalFlowSetFastPyramids = function(Handle: Pointer; Val: LongBool): LongBool; cdecl;
      TFarnebackOpticalFlowGetWinSize = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TFarnebackOpticalFlowSetWinSize = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TFarnebackOpticalFlowGetNumIters = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TFarnebackOpticalFlowSetNumIters = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TFarnebackOpticalFlowGetPolyN = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TFarnebackOpticalFlowSetPolyN = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TFarnebackOpticalFlowGetPolySigma = function(Handle: Pointer; Val: PDouble): LongBool; cdecl;
      TFarnebackOpticalFlowSetPolySigma = function(Handle: Pointer; Val: Double): LongBool; cdecl;
      TFarnebackOpticalFlowGetFlags = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TFarnebackOpticalFlowSetFlags = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TCreateSparsePyrLKOpticalFlow = function: Pointer; cdecl;
      TDeleteSparsePyrLKOpticalFlow = function(Handle: Pointer): LongBool; cdecl;
      TSparsePyrLKCalc = function(Handle: Pointer; PrevImg, NextImg: TMat;
        PrevPts, NextPts, Status, Err: PMat): LongBool; cdecl;
      TSparsePyrLKGetWinSizeW = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TSparsePyrLKSetWinSizeW = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TSparsePyrLKGetWinSizeH = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TSparsePyrLKSetWinSizeH = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TSparsePyrLKGetMaxLevel = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TSparsePyrLKSetMaxLevel = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TSparsePyrLKGetFlags = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TSparsePyrLKSetFlags = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TSparsePyrLKGetMinEigThreshold = function(Handle: Pointer; Val: PDouble): LongBool; cdecl;
      TSparsePyrLKSetMinEigThreshold = function(Handle: Pointer; Val: Double): LongBool; cdecl;
      TCreateVariationalRefinement = function: Pointer; cdecl;
      TDeleteVariationalRefinement = function(Handle: Pointer): LongBool; cdecl;
      TVariationalRefinementCalc = function(Handle: Pointer; I0, I1: TMat; Flow: PMat): LongBool; cdecl;
      TVariationalRefinementGetFixedPointIterations = function(Handle: Pointer;
        Val: PInteger): LongBool; cdecl;
      TVariationalRefinementSetFixedPointIterations = function(Handle: Pointer;
        Val: Integer): LongBool; cdecl;
      TVariationalRefinementGetSorIterations = function(Handle: Pointer; Val: PInteger): LongBool; cdecl;
      TVariationalRefinementSetSorIterations = function(Handle: Pointer; Val: Integer): LongBool; cdecl;
      TVariationalRefinementGetOmega = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TVariationalRefinementSetOmega = function(Handle: Pointer; Val: Single): LongBool; cdecl;
      TVariationalRefinementGetAlpha = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TVariationalRefinementSetAlpha = function(Handle: Pointer; Val: Single): LongBool; cdecl;
      TVariationalRefinementGetDelta = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TVariationalRefinementSetDelta = function(Handle: Pointer; Val: Single): LongBool; cdecl;
      TVariationalRefinementGetGamma = function(Handle: Pointer; Val: PSingle): LongBool; cdecl;
      TVariationalRefinementSetGamma = function(Handle: Pointer; Val: Single): LongBool; cdecl;
    var
      GoodFeaturesToTrack: TGoodFeaturesToTrack;
      CalcOpticalFlowPyrLK: TCalcOpticalFlowPyrLK;
      CalcOpticalFlowFarneback: TCalcOpticalFlowFarneback;
      CalcOpticalFlowDeepFlow: TCalcOpticalFlowDeepFlow;
      FindHomography: TFindHomography;
      PerspectiveTransform: TPerspectiveTransform;
      CreateMOG2Subtractor: TCreateMOG2Subtractor;
      CreateKNNSubtractor: TCreateKNNSubtractor;
      DeleteSubtractor: TDeleteSubtractor;
      SubtractorApply: TSubtractorApply;
      BlockMatchingFlow: TBlockMatchingFlow;
      BlockFlowTracking: TBlockFlowTracking;
      BuildOpticalFlowPyramid: TBuildOpticalFlowPyramid;
      CamShift: TCamShift;
      MeanShift: TMeanShift;
      SubtractorGetBackgroundImage: TSubtractorGetBackgroundImage;
      CreateDISOpticalFlow: TCreateDISOpticalFlow;
      DeleteDISOpticalFlow: TDeleteDISOpticalFlow;
      DISOpticalFlowCalc: TDISOpticalFlowCalc;
      DISOpticalFlowSetFinestScale: TDISOpticalFlowSetFinestScale;
      ReadOpticalFlow: TReadOpticalFlow;
      WriteOpticalFlow: TWriteOpticalFlow;
      FindTransformECC: TFindTransformECC;
      EstimateRigidTransform: TEstimateRigidTransform;
      ComputeECC: TComputeECC;
      CreateKalmanFilter: TCreateKalmanFilter;
      DeleteKalmanFilter: TDeleteKalmanFilter;
      KalmanPredict: TKalmanPredict;
      KalmanCorrect: TKalmanCorrect;
      KalmanGetStatePre: TKalmanGetStatePre;
      KalmanSetStatePre: TKalmanSetStatePre;
      KalmanGetStatePost: TKalmanGetStatePost;
      KalmanSetStatePost: TKalmanSetStatePost;
      KalmanGetTransitionMatrix: TKalmanGetTransitionMatrix;
      KalmanSetTransitionMatrix: TKalmanSetTransitionMatrix;
      MOG2GetHistory: TMOG2GetHistory;
      MOG2SetHistory: TMOG2SetHistory;
      MOG2GetNMixtures: TMOG2GetNMixtures;
      MOG2SetNMixtures: TMOG2SetNMixtures;
      MOG2GetBackgroundRatio: TMOG2GetBackgroundRatio;
      MOG2SetBackgroundRatio: TMOG2SetBackgroundRatio;
      MOG2GetVarThreshold: TMOG2GetVarThreshold;
      MOG2SetVarThreshold: TMOG2SetVarThreshold;
      MOG2GetVarThresholdGen: TMOG2GetVarThresholdGen;
      MOG2SetVarThresholdGen: TMOG2SetVarThresholdGen;
      MOG2GetDetectShadows: TMOG2GetDetectShadows;
      MOG2SetDetectShadows: TMOG2SetDetectShadows;
      KNNGetHistory: TKNNGetHistory;
      KNNSetHistory: TKNNSetHistory;
      KNNGetNSamples: TKNNGetNSamples;
      KNNSetNSamples: TKNNSetNSamples;
      KNNGetDist2Threshold: TKNNGetDist2Threshold;
      KNNSetDist2Threshold: TKNNSetDist2Threshold;
      KNNGetDetectShadows: TKNNGetDetectShadows;
      KNNSetDetectShadows: TKNNSetDetectShadows;
      KNNGetShadowValue: TKNNGetShadowValue;
      KNNSetShadowValue: TKNNSetShadowValue;
      DISOpticalFlowGetFinestScale: TDISOpticalFlowGetFinestScale;
      DISOpticalFlowGetPatchSize: TDISOpticalFlowGetPatchSize;
      DISOpticalFlowSetPatchSize: TDISOpticalFlowSetPatchSize;
      DISOpticalFlowGetPatchStride: TDISOpticalFlowGetPatchStride;
      DISOpticalFlowSetPatchStride: TDISOpticalFlowSetPatchStride;
      DISOpticalFlowGetGradientDescentIterations: TDISOpticalFlowGetGradientDescentIterations;
      DISOpticalFlowSetGradientDescentIterations: TDISOpticalFlowSetGradientDescentIterations;
      DISOpticalFlowGetVariationalRefinementIterations: TDISOpticalFlowGetVariationalRefinementIterations;
      DISOpticalFlowSetVariationalRefinementIterations: TDISOpticalFlowSetVariationalRefinementIterations;
      DISOpticalFlowGetVariationalRefinementAlpha: TDISOpticalFlowGetVariationalRefinementAlpha;
      DISOpticalFlowSetVariationalRefinementAlpha: TDISOpticalFlowSetVariationalRefinementAlpha;
      DISOpticalFlowGetVariationalRefinementDelta: TDISOpticalFlowGetVariationalRefinementDelta;
      DISOpticalFlowSetVariationalRefinementDelta: TDISOpticalFlowSetVariationalRefinementDelta;
      DISOpticalFlowGetVariationalRefinementGamma: TDISOpticalFlowGetVariationalRefinementGamma;
      DISOpticalFlowSetVariationalRefinementGamma: TDISOpticalFlowSetVariationalRefinementGamma;
      DISOpticalFlowGetUseMeanNormalization: TDISOpticalFlowGetUseMeanNormalization;
      DISOpticalFlowSetUseMeanNormalization: TDISOpticalFlowSetUseMeanNormalization;
      DISOpticalFlowGetUseSpatialPropagation: TDISOpticalFlowGetUseSpatialPropagation;
      DISOpticalFlowSetUseSpatialPropagation: TDISOpticalFlowSetUseSpatialPropagation;
      CreateFarnebackOpticalFlow: TCreateFarnebackOpticalFlow;
      DeleteFarnebackOpticalFlow: TDeleteFarnebackOpticalFlow;
      FarnebackOpticalFlowCalc: TFarnebackOpticalFlowCalc;
      FarnebackOpticalFlowGetNumLevels: TFarnebackOpticalFlowGetNumLevels;
      FarnebackOpticalFlowSetNumLevels: TFarnebackOpticalFlowSetNumLevels;
      FarnebackOpticalFlowGetPyrScale: TFarnebackOpticalFlowGetPyrScale;
      FarnebackOpticalFlowSetPyrScale: TFarnebackOpticalFlowSetPyrScale;
      FarnebackOpticalFlowGetFastPyramids: TFarnebackOpticalFlowGetFastPyramids;
      FarnebackOpticalFlowSetFastPyramids: TFarnebackOpticalFlowSetFastPyramids;
      FarnebackOpticalFlowGetWinSize: TFarnebackOpticalFlowGetWinSize;
      FarnebackOpticalFlowSetWinSize: TFarnebackOpticalFlowSetWinSize;
      FarnebackOpticalFlowGetNumIters: TFarnebackOpticalFlowGetNumIters;
      FarnebackOpticalFlowSetNumIters: TFarnebackOpticalFlowSetNumIters;
      FarnebackOpticalFlowGetPolyN: TFarnebackOpticalFlowGetPolyN;
      FarnebackOpticalFlowSetPolyN: TFarnebackOpticalFlowSetPolyN;
      FarnebackOpticalFlowGetPolySigma: TFarnebackOpticalFlowGetPolySigma;
      FarnebackOpticalFlowSetPolySigma: TFarnebackOpticalFlowSetPolySigma;
      FarnebackOpticalFlowGetFlags: TFarnebackOpticalFlowGetFlags;
      FarnebackOpticalFlowSetFlags: TFarnebackOpticalFlowSetFlags;
      CreateSparsePyrLKOpticalFlow: TCreateSparsePyrLKOpticalFlow;
      DeleteSparsePyrLKOpticalFlow: TDeleteSparsePyrLKOpticalFlow;
      SparsePyrLKCalc: TSparsePyrLKCalc;
      SparsePyrLKGetWinSizeW: TSparsePyrLKGetWinSizeW;
      SparsePyrLKSetWinSizeW: TSparsePyrLKSetWinSizeW;
      SparsePyrLKGetWinSizeH: TSparsePyrLKGetWinSizeH;
      SparsePyrLKSetWinSizeH: TSparsePyrLKSetWinSizeH;
      SparsePyrLKGetMaxLevel: TSparsePyrLKGetMaxLevel;
      SparsePyrLKSetMaxLevel: TSparsePyrLKSetMaxLevel;
      SparsePyrLKGetFlags: TSparsePyrLKGetFlags;
      SparsePyrLKSetFlags: TSparsePyrLKSetFlags;
      SparsePyrLKGetMinEigThreshold: TSparsePyrLKGetMinEigThreshold;
      SparsePyrLKSetMinEigThreshold: TSparsePyrLKSetMinEigThreshold;
      CreateVariationalRefinement: TCreateVariationalRefinement;
      DeleteVariationalRefinement: TDeleteVariationalRefinement;
      VariationalRefinementCalc: TVariationalRefinementCalc;
      VariationalRefinementGetFixedPointIterations: TVariationalRefinementGetFixedPointIterations;
      VariationalRefinementSetFixedPointIterations: TVariationalRefinementSetFixedPointIterations;
      VariationalRefinementGetSorIterations: TVariationalRefinementGetSorIterations;
      VariationalRefinementSetSorIterations: TVariationalRefinementSetSorIterations;
      VariationalRefinementGetOmega: TVariationalRefinementGetOmega;
      VariationalRefinementSetOmega: TVariationalRefinementSetOmega;
      VariationalRefinementGetAlpha: TVariationalRefinementGetAlpha;
      VariationalRefinementSetAlpha: TVariationalRefinementSetAlpha;
      VariationalRefinementGetDelta: TVariationalRefinementGetDelta;
      VariationalRefinementSetDelta: TVariationalRefinementSetDelta;
      VariationalRefinementGetGamma: TVariationalRefinementGetGamma;
      VariationalRefinementSetGamma: TVariationalRefinementSetGamma;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVVideoModule.Initialize(const Handle: TLibHandle);
begin
  GoodFeaturesToTrack := CVBind(Handle, 'cv_video_goodFeaturesToTrack');
  CalcOpticalFlowPyrLK := CVBind(Handle, 'cv_video_calcOpticalFlowPyrLK');
  CalcOpticalFlowFarneback := CVBind(Handle, 'cv_video_calcOpticalFlowFarneback');
  CalcOpticalFlowDeepFlow := CVBind(Handle, 'cv_video_calcOpticalFlowDeepFlow');
  FindHomography := CVBind(Handle, 'cv_video_findHomography');
  PerspectiveTransform := CVBind(Handle, 'cv_video_perspectiveTransform');
  CreateMOG2Subtractor := CVBind(Handle, 'cv_video_createMOG2Subtractor');
  CreateKNNSubtractor := CVBind(Handle, 'cv_video_createKNNSubtractor');
  DeleteSubtractor := CVBind(Handle, 'cv_video_deleteSubtractor');
  SubtractorApply := CVBind(Handle, 'cv_video_subtractorApply');
  BlockMatchingFlow := CVBind(Handle, 'cv_video_blockMatchingFlow');
  BlockFlowTracking := CVBind(Handle, 'cv_video_blockFlowTracking');
  BuildOpticalFlowPyramid := CVBind(Handle, 'cv_video_buildOpticalFlowPyramid');
  CamShift := CVBind(Handle, 'cv_video_camShift');
  MeanShift := CVBind(Handle, 'cv_video_meanShift');
  SubtractorGetBackgroundImage := CVBind(Handle, 'cv_video_subtractorGetBackgroundImage');
  CreateDISOpticalFlow := CVBind(Handle, 'cv_video_createDISOpticalFlow');
  DeleteDISOpticalFlow := CVBind(Handle, 'cv_video_deleteDISOpticalFlow');
  DISOpticalFlowCalc := CVBind(Handle, 'cv_video_DISOpticalFlowCalc');
  DISOpticalFlowSetFinestScale := CVBind(Handle, 'cv_video_DISOpticalFlowSetFinestScale');
  ReadOpticalFlow := CVBind(Handle, 'cv_video_readOpticalFlow');
  WriteOpticalFlow := CVBind(Handle, 'cv_video_writeOpticalFlow');
  FindTransformECC := CVBind(Handle, 'cv_video_findTransformECC');
  EstimateRigidTransform := CVBind(Handle, 'cv_video_estimateRigidTransform');
  ComputeECC := CVBind(Handle, 'cv_video_computeECC');
  CreateKalmanFilter := CVBind(Handle, 'cv_video_createKalmanFilter');
  DeleteKalmanFilter := CVBind(Handle, 'cv_video_deleteKalmanFilter');
  KalmanPredict := CVBind(Handle, 'cv_video_kalmanPredict');
  KalmanCorrect := CVBind(Handle, 'cv_video_kalmanCorrect');
  KalmanGetStatePre := CVBind(Handle, 'cv_video_kalmanGetStatePre');
  KalmanSetStatePre := CVBind(Handle, 'cv_video_kalmanSetStatePre');
  KalmanGetStatePost := CVBind(Handle, 'cv_video_kalmanGetStatePost');
  KalmanSetStatePost := CVBind(Handle, 'cv_video_kalmanSetStatePost');
  KalmanGetTransitionMatrix := CVBind(Handle, 'cv_video_kalmanGetTransitionMatrix');
  KalmanSetTransitionMatrix := CVBind(Handle, 'cv_video_kalmanSetTransitionMatrix');
  MOG2GetHistory := CVBind(Handle, 'cv_video_mog2GetHistory');
  MOG2SetHistory := CVBind(Handle, 'cv_video_mog2SetHistory');
  MOG2GetNMixtures := CVBind(Handle, 'cv_video_mog2GetNMixtures');
  MOG2SetNMixtures := CVBind(Handle, 'cv_video_mog2SetNMixtures');
  MOG2GetBackgroundRatio := CVBind(Handle, 'cv_video_mog2GetBackgroundRatio');
  MOG2SetBackgroundRatio := CVBind(Handle, 'cv_video_mog2SetBackgroundRatio');
  MOG2GetVarThreshold := CVBind(Handle, 'cv_video_mog2GetVarThreshold');
  MOG2SetVarThreshold := CVBind(Handle, 'cv_video_mog2SetVarThreshold');
  MOG2GetVarThresholdGen := CVBind(Handle, 'cv_video_mog2GetVarThresholdGen');
  MOG2SetVarThresholdGen := CVBind(Handle, 'cv_video_mog2SetVarThresholdGen');
  MOG2GetDetectShadows := CVBind(Handle, 'cv_video_mog2GetDetectShadows');
  MOG2SetDetectShadows := CVBind(Handle, 'cv_video_mog2SetDetectShadows');
  KNNGetHistory := CVBind(Handle, 'cv_video_knnGetHistory');
  KNNSetHistory := CVBind(Handle, 'cv_video_knnSetHistory');
  KNNGetNSamples := CVBind(Handle, 'cv_video_knnGetNSamples');
  KNNSetNSamples := CVBind(Handle, 'cv_video_knnSetNSamples');
  KNNGetDist2Threshold := CVBind(Handle, 'cv_video_knnGetDist2Threshold');
  KNNSetDist2Threshold := CVBind(Handle, 'cv_video_knnSetDist2Threshold');
  KNNGetDetectShadows := CVBind(Handle, 'cv_video_knnGetDetectShadows');
  KNNSetDetectShadows := CVBind(Handle, 'cv_video_knnSetDetectShadows');
  KNNGetShadowValue := CVBind(Handle, 'cv_video_knnGetShadowValue');
  KNNSetShadowValue := CVBind(Handle, 'cv_video_knnSetShadowValue');
  DISOpticalFlowGetFinestScale := CVBind(Handle, 'cv_video_DISOpticalFlowGetFinestScale');
  DISOpticalFlowGetPatchSize := CVBind(Handle, 'cv_video_DISOpticalFlowGetPatchSize');
  DISOpticalFlowSetPatchSize := CVBind(Handle, 'cv_video_DISOpticalFlowSetPatchSize');
  DISOpticalFlowGetPatchStride := CVBind(Handle, 'cv_video_DISOpticalFlowGetPatchStride');
  DISOpticalFlowSetPatchStride := CVBind(Handle, 'cv_video_DISOpticalFlowSetPatchStride');
  DISOpticalFlowGetGradientDescentIterations := CVBind(Handle,
    'cv_video_DISOpticalFlowGetGradientDescentIterations');
  DISOpticalFlowSetGradientDescentIterations := CVBind(Handle,
    'cv_video_DISOpticalFlowSetGradientDescentIterations');
  DISOpticalFlowGetVariationalRefinementIterations := CVBind(Handle,
    'cv_video_DISOpticalFlowGetVariationalRefinementIterations');
  DISOpticalFlowSetVariationalRefinementIterations := CVBind(Handle,
    'cv_video_DISOpticalFlowSetVariationalRefinementIterations');
  DISOpticalFlowGetVariationalRefinementAlpha := CVBind(Handle,
    'cv_video_DISOpticalFlowGetVariationalRefinementAlpha');
  DISOpticalFlowSetVariationalRefinementAlpha := CVBind(Handle,
    'cv_video_DISOpticalFlowSetVariationalRefinementAlpha');
  DISOpticalFlowGetVariationalRefinementDelta := CVBind(Handle,
    'cv_video_DISOpticalFlowGetVariationalRefinementDelta');
  DISOpticalFlowSetVariationalRefinementDelta := CVBind(Handle,
    'cv_video_DISOpticalFlowSetVariationalRefinementDelta');
  DISOpticalFlowGetVariationalRefinementGamma := CVBind(Handle,
    'cv_video_DISOpticalFlowGetVariationalRefinementGamma');
  DISOpticalFlowSetVariationalRefinementGamma := CVBind(Handle,
    'cv_video_DISOpticalFlowSetVariationalRefinementGamma');
  DISOpticalFlowGetUseMeanNormalization := CVBind(Handle, 'cv_video_DISOpticalFlowGetUseMeanNormalization');
  DISOpticalFlowSetUseMeanNormalization := CVBind(Handle, 'cv_video_DISOpticalFlowSetUseMeanNormalization');
  DISOpticalFlowGetUseSpatialPropagation := CVBind(Handle, 'cv_video_DISOpticalFlowGetUseSpatialPropagation');
  DISOpticalFlowSetUseSpatialPropagation := CVBind(Handle, 'cv_video_DISOpticalFlowSetUseSpatialPropagation');
  CreateFarnebackOpticalFlow := CVBind(Handle, 'cv_video_createFarnebackOpticalFlow');
  DeleteFarnebackOpticalFlow := CVBind(Handle, 'cv_video_deleteFarnebackOpticalFlow');
  FarnebackOpticalFlowCalc := CVBind(Handle, 'cv_video_farnebackOpticalFlowCalc');
  FarnebackOpticalFlowGetNumLevels := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetNumLevels');
  FarnebackOpticalFlowSetNumLevels := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetNumLevels');
  FarnebackOpticalFlowGetPyrScale := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetPyrScale');
  FarnebackOpticalFlowSetPyrScale := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetPyrScale');
  FarnebackOpticalFlowGetFastPyramids := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetFastPyramids');
  FarnebackOpticalFlowSetFastPyramids := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetFastPyramids');
  FarnebackOpticalFlowGetWinSize := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetWinSize');
  FarnebackOpticalFlowSetWinSize := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetWinSize');
  FarnebackOpticalFlowGetNumIters := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetNumIters');
  FarnebackOpticalFlowSetNumIters := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetNumIters');
  FarnebackOpticalFlowGetPolyN := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetPolyN');
  FarnebackOpticalFlowSetPolyN := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetPolyN');
  FarnebackOpticalFlowGetPolySigma := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetPolySigma');
  FarnebackOpticalFlowSetPolySigma := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetPolySigma');
  FarnebackOpticalFlowGetFlags := CVBind(Handle, 'cv_video_farnebackOpticalFlowGetFlags');
  FarnebackOpticalFlowSetFlags := CVBind(Handle, 'cv_video_farnebackOpticalFlowSetFlags');
  CreateSparsePyrLKOpticalFlow := CVBind(Handle, 'cv_video_createSparsePyrLKOpticalFlow');
  DeleteSparsePyrLKOpticalFlow := CVBind(Handle, 'cv_video_deleteSparsePyrLKOpticalFlow');
  SparsePyrLKCalc := CVBind(Handle, 'cv_video_sparsePyrLKCalc');
  SparsePyrLKGetWinSizeW := CVBind(Handle, 'cv_video_sparsePyrLKGetWinSizeW');
  SparsePyrLKSetWinSizeW := CVBind(Handle, 'cv_video_sparsePyrLKSetWinSizeW');
  SparsePyrLKGetWinSizeH := CVBind(Handle, 'cv_video_sparsePyrLKGetWinSizeH');
  SparsePyrLKSetWinSizeH := CVBind(Handle, 'cv_video_sparsePyrLKSetWinSizeH');
  SparsePyrLKGetMaxLevel := CVBind(Handle, 'cv_video_sparsePyrLKGetMaxLevel');
  SparsePyrLKSetMaxLevel := CVBind(Handle, 'cv_video_sparsePyrLKSetMaxLevel');
  SparsePyrLKGetFlags := CVBind(Handle, 'cv_video_sparsePyrLKGetFlags');
  SparsePyrLKSetFlags := CVBind(Handle, 'cv_video_sparsePyrLKSetFlags');
  SparsePyrLKGetMinEigThreshold := CVBind(Handle, 'cv_video_sparsePyrLKGetMinEigThreshold');
  SparsePyrLKSetMinEigThreshold := CVBind(Handle, 'cv_video_sparsePyrLKSetMinEigThreshold');
  CreateVariationalRefinement := CVBind(Handle, 'cv_video_createVariationalRefinement');
  DeleteVariationalRefinement := CVBind(Handle, 'cv_video_deleteVariationalRefinement');
  VariationalRefinementCalc := CVBind(Handle, 'cv_video_variationalRefinementCalc');
  VariationalRefinementGetFixedPointIterations := CVBind(Handle,
    'cv_video_variationalRefinementGetFixedPointIterations');
  VariationalRefinementSetFixedPointIterations := CVBind(Handle,
    'cv_video_variationalRefinementSetFixedPointIterations');
  VariationalRefinementGetSorIterations := CVBind(Handle, 'cv_video_variationalRefinementGetSorIterations');
  VariationalRefinementSetSorIterations := CVBind(Handle, 'cv_video_variationalRefinementSetSorIterations');
  VariationalRefinementGetOmega := CVBind(Handle, 'cv_video_variationalRefinementGetOmega');
  VariationalRefinementSetOmega := CVBind(Handle, 'cv_video_variationalRefinementSetOmega');
  VariationalRefinementGetAlpha := CVBind(Handle, 'cv_video_variationalRefinementGetAlpha');
  VariationalRefinementSetAlpha := CVBind(Handle, 'cv_video_variationalRefinementSetAlpha');
  VariationalRefinementGetDelta := CVBind(Handle, 'cv_video_variationalRefinementGetDelta');
  VariationalRefinementSetDelta := CVBind(Handle, 'cv_video_variationalRefinementSetDelta');
  VariationalRefinementGetGamma := CVBind(Handle, 'cv_video_variationalRefinementGetGamma');
  VariationalRefinementSetGamma := CVBind(Handle, 'cv_video_variationalRefinementSetGamma');
end;

end.
