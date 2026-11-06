{ ************************************************************************** }
{                                                                            }
{ OpenCV.XImgProc                                                            }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev (ypisareff@outlook.com)               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.XImgProc;

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
  TCVXImgProcModule = record
  public
    type
      TGetData = procedure(Count: Integer; From, Data: Pointer); cdecl;
      TThinning = function(Source: TMat; Target: PMat; ThinningType: Integer): LongBool; cdecl;
      TLineDetect = function(Source: TMat; Get: TGetData; Data: Pointer;
        Scale, SigmaScale, Quant, AngTh, LogEps, DensityTh: Double; NBins: Integer): LongBool; cdecl;
      TNiBlackThreshold = function(Source: TMat; Target: PMat; MaxValue: Double; &Type: Integer;
        BlockSize: Integer; K: Double; BinarizationMethod: Integer): LongBool; cdecl;
      TCreateSuperpixelSLIC = function(Image: TMat; Algorithm, RegionSize: Integer; Ruler: Single;
        Handle: PPointer): LongBool; cdecl;
      TDeleteSuperpixelSLIC = function(Handle: Pointer): LongBool; cdecl;
      TCreateEdgeDrawing = function: Pointer; cdecl;
      TDeleteEdgeDrawing = function(Handle: Pointer): LongBool; cdecl;
      TCreateStructuredEdgeDetection = function(Model: PAnsiChar): Pointer; cdecl;
      TDeleteStructuredEdgeDetection = function(Handle: Pointer): LongBool; cdecl;
      TAnisotropicDiffusion = function(Source: TMat; Target: PMat; Alpha, K: Single;
        NIters: Integer): LongBool; cdecl;
      TCreateDTFilter = function(Guide: TMat; SigmaSpatial, SigmaColor: Double;
        Mode, NumIters: Integer): Pointer; cdecl;
      TDeleteDTFilter = procedure(Filter: Pointer); cdecl;
      TDTFilterFilter = procedure(Filter: Pointer; Src: TMat; Dst: PMat); cdecl;
      TDTFilterStandalone = procedure(Guide: TMat; Src: TMat; Dst: PMat; SigmaSpatial, SigmaColor: Double;
        Mode, NumIters: Integer); cdecl;
      TCreateGuidedFilter = function(Guide: TMat; Radius: Integer; Eps: Double): Pointer; cdecl;
      TDeleteGuidedFilter = procedure(Filter: Pointer); cdecl;
      TGuidedFilterFilter = procedure(Filter: Pointer; Src: TMat; Dst: PMat); cdecl;
      TGuidedFilterStandalone = procedure(Guide: TMat; Src: TMat; Dst: PMat; Radius: Integer;
        Eps: Double); cdecl;
      TCreateFastGlobalSmootherFilter = function(Guide: TMat; Lambda, SigmaColor: Double): Pointer; cdecl;
      TDeleteFastGlobalSmootherFilter = procedure(Filter: Pointer); cdecl;
      TFastGlobalSmootherFilterFilter = procedure(Filter: Pointer; Src: TMat; Dst: PMat); cdecl;
      TFastGlobalSmootherFilterStandalone = procedure(Guide: TMat; Src: TMat; Dst: PMat;
        Lambda, SigmaColor: Double); cdecl;
      TRollingGuidanceFilter = procedure(Src: TMat; Dst: PMat; D: Integer; SigmaColor, SigmaSpace: Double;
        NumOfIter: Integer); cdecl;
      TJointBilateralFilter = procedure(Joint: TMat; Src: TMat; Dst: PMat; D: Integer;
        SigmaColor, SigmaSpace: Double); cdecl;
      TBilateralTextureFilter = procedure(Src: TMat; Dst: PMat; Fr, NumIter: Integer;
        SigmaAlpha, SigmaAvg: Double); cdecl;
      TWeightedMedianFilter = procedure(Joint: TMat; Src: TMat; Dst: PMat; R: Integer; Sigma: Double;
        WeightType: Integer); cdecl;
      TAdaptiveManifoldFilter = procedure(Src: TMat; Dst: PMat; Sigma_s, Sigma_r: Double); cdecl;
      TCreateFastLineDetector = function(LengthThreshold: Integer; DistanceThreshold: Single;
        CannyTh1, CannyTh2: Double; CannyApertureSize: Integer; DoMerge: LongBool): Pointer; cdecl;
      TDeleteFastLineDetector = procedure(Detector: Pointer); cdecl;
      TFastLineDetectorDetect = procedure(Detector: Pointer; Image: TMat; Lines: PMat); cdecl;
      TFastLineDetectorDrawSegments = procedure(Detector: Pointer; Image: PMat; Lines: TMat); cdecl;
      TFastLineDetectorDrawSegmentsEx = procedure(Detector: Pointer; Image: PMat; Lines: TMat;
        DrawArrow: LongBool; Thickness: Integer); cdecl;
      TCreateEdgeBoxes = function(Alpha, Beta, Eta, MinScore: Single; MaxBoxes: Integer;
        EdgeMinMag, EdgeMergeThr, ClusterMinMag, MaxAspectRatio, MinBoxArea, Gamma, Kappa: Single): Pointer; cdecl;
      TDeleteEdgeBoxes = procedure(EdgeBoxes: Pointer); cdecl;
      // Pass nil for Boxes to query the count. Otherwise initialize Count^ with the buffer capacity.
      // If capacity is too small, Count^ receives the required count and Boxes stays unchanged.
      TEdgeBoxesGetBoundingBoxes = procedure(EdgeBoxes: Pointer; EdgeMap: TMat; OrientationMap: TMat;
        Boxes: POCVRect; Count: PInteger); cdecl;
      TEdgeBoxesGetAlpha = function(EdgeBoxes: Pointer): Single; cdecl;
      TEdgeBoxesSetAlpha = procedure(EdgeBoxes: Pointer; Value: Single); cdecl;
      TEdgeBoxesGetBeta = function(EdgeBoxes: Pointer): Single; cdecl;
      TEdgeBoxesSetBeta = procedure(EdgeBoxes: Pointer; Value: Single); cdecl;
      TCreateGraphSegmentation = function(Sigma: Double; K: Single; MinSize: Integer): Pointer; cdecl;
      TDeleteGraphSegmentation = procedure(GS: Pointer); cdecl;
      TGraphSegmentationProcessImage = procedure(GS: Pointer; Src: TMat; Dst: PMat); cdecl;
      TGraphSegmentationGetK = function(GS: Pointer): Single; cdecl;
      TGraphSegmentationSetK = procedure(GS: Pointer; Value: Single); cdecl;
      TCreateSelectiveSearchSegmentation = function: Pointer; cdecl;
      TDeleteSelectiveSearchSegmentation = procedure(SS: Pointer); cdecl;
      TSelectiveSearchSetBaseImage = procedure(SS: Pointer; Image: TMat); cdecl;
      TSelectiveSearchSwitchToSingleStrategy = procedure(SS: Pointer; K: Integer; Sigma: Single); cdecl;
      TSelectiveSearchSwitchToSelectiveSearchFast = procedure(SS: Pointer; BaseK, IncK: Integer;
        Sigma: Single); cdecl;
      TSelectiveSearchSwitchToSelectiveSearchQuality = procedure(SS: Pointer; BaseK, IncK: Integer;
        Sigma: Single); cdecl;
      // Uses the same count and capacity contract as TEdgeBoxesGetBoundingBoxes.
      TSelectiveSearchProcess = procedure(SS: Pointer; Rects: POCVRect; Count: PInteger); cdecl;
      TSelectiveSearchAddImage = procedure(SS: Pointer; Image: TMat); cdecl;
      TCreateSuperpixelSEEDS = function(ImageWidth, ImageHeight, ImageChannels, NumSuperpixels, NumLevels, Prior, HistogramBins: Integer;
        DoubleStep: LongBool): Pointer; cdecl;
      TDeleteSuperpixelSEEDS = procedure(Seeds: Pointer); cdecl;
      TSuperpixelSEEDSIterate = procedure(Seeds: Pointer; Image: TMat; NumIterations: Integer); cdecl;
      TSuperpixelSEEDSGetLabels = procedure(Seeds: Pointer; Labels: PMat); cdecl;
      TSuperpixelSEEDSGetNumberOfSuperpixels = function(Seeds: Pointer): Integer; cdecl;
      TSuperpixelSEEDSGetLabelContourMask = procedure(Seeds: Pointer; Mask: PMat; ThickLine: LongBool); cdecl;
      TCreateSuperpixelLSC = function(Image: TMat; RegionSize: Integer; Ratio: Single): Pointer; cdecl;
      TDeleteSuperpixelLSC = procedure(LSC: Pointer); cdecl;
      TSuperpixelLSCIterate = procedure(LSC: Pointer; NumIterations: Integer); cdecl;
      TSuperpixelLSCGetLabels = procedure(LSC: Pointer; Labels: PMat); cdecl;
      TSuperpixelLSCGetNumberOfSuperpixels = function(LSC: Pointer): Integer; cdecl;
      TSuperpixelLSCGetLabelContourMask = procedure(LSC: Pointer; Mask: PMat; ThickLine: LongBool); cdecl;
      TSuperpixelLSCEnforceLabelConnectivity = procedure(LSC: Pointer; MinElementSize: Integer); cdecl;
      TPeiLinNormalization = procedure(I: TMat; T: PMat); cdecl;
      TFourierDescriptor = procedure(Src: TMat; Dst: PMat; NbElt, NbFD: Integer); cdecl;
      TContourSampling = procedure(Src: TMat; Out_: PMat; NbElt: Integer); cdecl;
      TColorMatchTemplate = procedure(Img: TMat; Templ: TMat; &Result: PMat); cdecl;
    var
      Thinning: TThinning;
      LineDetect: TLineDetect;
      NiBlackThreshold: TNiBlackThreshold;
      CreateSuperpixelSLIC: TCreateSuperpixelSLIC;
      DeleteSuperpixelSLIC: TDeleteSuperpixelSLIC;
      CreateEdgeDrawing: TCreateEdgeDrawing;
      DeleteEdgeDrawing: TDeleteEdgeDrawing;
      CreateStructuredEdgeDetection: TCreateStructuredEdgeDetection;
      DeleteStructuredEdgeDetection: TDeleteStructuredEdgeDetection;
      AnisotropicDiffusion: TAnisotropicDiffusion;
      CreateDTFilter: TCreateDTFilter;
      DeleteDTFilter: TDeleteDTFilter;
      DTFilterFilter: TDTFilterFilter;
      DTFilterStandalone: TDTFilterStandalone;
      CreateGuidedFilter: TCreateGuidedFilter;
      DeleteGuidedFilter: TDeleteGuidedFilter;
      GuidedFilterFilter: TGuidedFilterFilter;
      GuidedFilterStandalone: TGuidedFilterStandalone;
      CreateFastGlobalSmootherFilter: TCreateFastGlobalSmootherFilter;
      DeleteFastGlobalSmootherFilter: TDeleteFastGlobalSmootherFilter;
      FastGlobalSmootherFilterFilter: TFastGlobalSmootherFilterFilter;
      FastGlobalSmootherFilterStandalone: TFastGlobalSmootherFilterStandalone;
      RollingGuidanceFilter: TRollingGuidanceFilter;
      JointBilateralFilter: TJointBilateralFilter;
      BilateralTextureFilter: TBilateralTextureFilter;
      WeightedMedianFilter: TWeightedMedianFilter;
      AdaptiveManifoldFilter: TAdaptiveManifoldFilter;
      CreateFastLineDetector: TCreateFastLineDetector;
      DeleteFastLineDetector: TDeleteFastLineDetector;
      FastLineDetectorDetect: TFastLineDetectorDetect;
      FastLineDetectorDrawSegments: TFastLineDetectorDrawSegments;
      FastLineDetectorDrawSegmentsEx: TFastLineDetectorDrawSegmentsEx;
      CreateEdgeBoxes: TCreateEdgeBoxes;
      DeleteEdgeBoxes: TDeleteEdgeBoxes;
      EdgeBoxesGetBoundingBoxes: TEdgeBoxesGetBoundingBoxes;
      EdgeBoxesGetAlpha: TEdgeBoxesGetAlpha;
      EdgeBoxesSetAlpha: TEdgeBoxesSetAlpha;
      EdgeBoxesGetBeta: TEdgeBoxesGetBeta;
      EdgeBoxesSetBeta: TEdgeBoxesSetBeta;
      CreateGraphSegmentation: TCreateGraphSegmentation;
      DeleteGraphSegmentation: TDeleteGraphSegmentation;
      GraphSegmentationProcessImage: TGraphSegmentationProcessImage;
      GraphSegmentationGetK: TGraphSegmentationGetK;
      GraphSegmentationSetK: TGraphSegmentationSetK;
      CreateSelectiveSearchSegmentation: TCreateSelectiveSearchSegmentation;
      DeleteSelectiveSearchSegmentation: TDeleteSelectiveSearchSegmentation;
      SelectiveSearchSetBaseImage: TSelectiveSearchSetBaseImage;
      SelectiveSearchSwitchToSingleStrategy: TSelectiveSearchSwitchToSingleStrategy;
      SelectiveSearchSwitchToSelectiveSearchFast: TSelectiveSearchSwitchToSelectiveSearchFast;
      SelectiveSearchSwitchToSelectiveSearchQuality: TSelectiveSearchSwitchToSelectiveSearchQuality;
      SelectiveSearchProcess: TSelectiveSearchProcess;
      SelectiveSearchAddImage: TSelectiveSearchAddImage;
      CreateSuperpixelSEEDS: TCreateSuperpixelSEEDS;
      DeleteSuperpixelSEEDS: TDeleteSuperpixelSEEDS;
      SuperpixelSEEDSIterate: TSuperpixelSEEDSIterate;
      SuperpixelSEEDSGetLabels: TSuperpixelSEEDSGetLabels;
      SuperpixelSEEDSGetNumberOfSuperpixels: TSuperpixelSEEDSGetNumberOfSuperpixels;
      SuperpixelSEEDSGetLabelContourMask: TSuperpixelSEEDSGetLabelContourMask;
      CreateSuperpixelLSC: TCreateSuperpixelLSC;
      DeleteSuperpixelLSC: TDeleteSuperpixelLSC;
      SuperpixelLSCIterate: TSuperpixelLSCIterate;
      SuperpixelLSCGetLabels: TSuperpixelLSCGetLabels;
      SuperpixelLSCGetNumberOfSuperpixels: TSuperpixelLSCGetNumberOfSuperpixels;
      SuperpixelLSCGetLabelContourMask: TSuperpixelLSCGetLabelContourMask;
      SuperpixelLSCEnforceLabelConnectivity: TSuperpixelLSCEnforceLabelConnectivity;
      PeiLinNormalization: TPeiLinNormalization;
      FourierDescriptor: TFourierDescriptor;
      ContourSampling: TContourSampling;
      ColorMatchTemplate: TColorMatchTemplate;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVXImgProcModule.Initialize(const Handle: TLibHandle);
begin
  Thinning := CVBind(Handle, 'cv_ximgproc_thinning');
  LineDetect := CVBind(Handle, 'cv_ximgproc_lineDetect');
  NiBlackThreshold := CVBind(Handle, 'cv_ximgproc_niBlackThreshold');
  CreateSuperpixelSLIC := CVBind(Handle, 'cv_ximgproc_createSuperpixelSLIC');
  DeleteSuperpixelSLIC := CVBind(Handle, 'cv_ximgproc_deleteSuperpixelSLIC');
  CreateEdgeDrawing := CVBind(Handle, 'cv_ximgproc_createEdgeDrawing');
  DeleteEdgeDrawing := CVBind(Handle, 'cv_ximgproc_deleteEdgeDrawing');
  CreateStructuredEdgeDetection := CVBind(Handle, 'cv_ximgproc_createStructuredEdgeDetection');
  DeleteStructuredEdgeDetection := CVBind(Handle, 'cv_ximgproc_deleteStructuredEdgeDetection');
  AnisotropicDiffusion := CVBind(Handle, 'cv_ximgproc_anisotropicDiffusion');
  CreateDTFilter := CVBind(Handle, 'cv_ximgproc_createDTFilter');
  DeleteDTFilter := CVBind(Handle, 'cv_ximgproc_deleteDTFilter');
  DTFilterFilter := CVBind(Handle, 'cv_ximgproc_dtFilterFilter');
  DTFilterStandalone := CVBind(Handle, 'cv_ximgproc_dtFilter');
  CreateGuidedFilter := CVBind(Handle, 'cv_ximgproc_createGuidedFilter');
  DeleteGuidedFilter := CVBind(Handle, 'cv_ximgproc_deleteGuidedFilter');
  GuidedFilterFilter := CVBind(Handle, 'cv_ximgproc_guidedFilterFilter');
  GuidedFilterStandalone := CVBind(Handle, 'cv_ximgproc_guidedFilter');
  CreateFastGlobalSmootherFilter := CVBind(Handle, 'cv_ximgproc_createFastGlobalSmootherFilter');
  DeleteFastGlobalSmootherFilter := CVBind(Handle, 'cv_ximgproc_deleteFastGlobalSmootherFilter');
  FastGlobalSmootherFilterFilter := CVBind(Handle, 'cv_ximgproc_fastGlobalSmootherFilterFilter');
  FastGlobalSmootherFilterStandalone := CVBind(Handle, 'cv_ximgproc_fastGlobalSmootherFilter');
  RollingGuidanceFilter := CVBind(Handle, 'cv_ximgproc_rollingGuidanceFilter');
  JointBilateralFilter := CVBind(Handle, 'cv_ximgproc_jointBilateralFilter');
  BilateralTextureFilter := CVBind(Handle, 'cv_ximgproc_bilateralTextureFilter');
  WeightedMedianFilter := CVBind(Handle, 'cv_ximgproc_weightedMedianFilter');
  AdaptiveManifoldFilter := CVBind(Handle, 'cv_ximgproc_adaptiveManifoldFilter');
  CreateFastLineDetector := CVBind(Handle, 'cv_ximgproc_createFastLineDetector');
  DeleteFastLineDetector := CVBind(Handle, 'cv_ximgproc_deleteFastLineDetector');
  FastLineDetectorDetect := CVBind(Handle, 'cv_ximgproc_fastLineDetectorDetect');
  FastLineDetectorDrawSegments := CVBind(Handle, 'cv_ximgproc_fastLineDetectorDrawSegments');
  FastLineDetectorDrawSegmentsEx := CVBind(Handle, 'cv_ximgproc_fastLineDetectorDrawSegmentsEx');
  CreateEdgeBoxes := CVBind(Handle, 'cv_ximgproc_createEdgeBoxes');
  DeleteEdgeBoxes := CVBind(Handle, 'cv_ximgproc_deleteEdgeBoxes');
  EdgeBoxesGetBoundingBoxes := CVBind(Handle, 'cv_ximgproc_edgeBoxesGetBoundingBoxes');
  EdgeBoxesGetAlpha := CVBind(Handle, 'cv_ximgproc_edgeBoxesGetAlpha');
  EdgeBoxesSetAlpha := CVBind(Handle, 'cv_ximgproc_edgeBoxesSetAlpha');
  EdgeBoxesGetBeta := CVBind(Handle, 'cv_ximgproc_edgeBoxesGetBeta');
  EdgeBoxesSetBeta := CVBind(Handle, 'cv_ximgproc_edgeBoxesSetBeta');
  CreateGraphSegmentation := CVBind(Handle, 'cv_ximgproc_createGraphSegmentation');
  DeleteGraphSegmentation := CVBind(Handle, 'cv_ximgproc_deleteGraphSegmentation');
  GraphSegmentationProcessImage := CVBind(Handle, 'cv_ximgproc_graphSegmentationProcessImage');
  GraphSegmentationGetK := CVBind(Handle, 'cv_ximgproc_graphSegmentationGetK');
  GraphSegmentationSetK := CVBind(Handle, 'cv_ximgproc_graphSegmentationSetK');
  CreateSelectiveSearchSegmentation := CVBind(Handle, 'cv_ximgproc_createSelectiveSearchSegmentation');
  DeleteSelectiveSearchSegmentation := CVBind(Handle, 'cv_ximgproc_deleteSelectiveSearchSegmentation');
  SelectiveSearchSetBaseImage := CVBind(Handle, 'cv_ximgproc_selectiveSearchSetBaseImage');
  SelectiveSearchSwitchToSingleStrategy := CVBind(Handle,
    'cv_ximgproc_selectiveSearchSwitchToSingleStrategy');
  SelectiveSearchSwitchToSelectiveSearchFast := CVBind(Handle,
    'cv_ximgproc_selectiveSearchSwitchToSelectiveSearchFast');
  SelectiveSearchSwitchToSelectiveSearchQuality := CVBind(Handle,
    'cv_ximgproc_selectiveSearchSwitchToSelectiveSearchQuality');
  SelectiveSearchProcess := CVBind(Handle, 'cv_ximgproc_selectiveSearchProcess');
  SelectiveSearchAddImage := CVBind(Handle, 'cv_ximgproc_selectiveSearchAddImage');
  CreateSuperpixelSEEDS := CVBind(Handle, 'cv_ximgproc_createSuperpixelSEEDS');
  DeleteSuperpixelSEEDS := CVBind(Handle, 'cv_ximgproc_deleteSuperpixelSEEDS');
  SuperpixelSEEDSIterate := CVBind(Handle, 'cv_ximgproc_superpixelSEEDSIterate');
  SuperpixelSEEDSGetLabels := CVBind(Handle, 'cv_ximgproc_superpixelSEEDSGetLabels');
  SuperpixelSEEDSGetNumberOfSuperpixels := CVBind(Handle,
    'cv_ximgproc_superpixelSEEDSGetNumberOfSuperpixels');
  SuperpixelSEEDSGetLabelContourMask := CVBind(Handle, 'cv_ximgproc_superpixelSEEDSGetLabelContourMask');
  CreateSuperpixelLSC := CVBind(Handle, 'cv_ximgproc_createSuperpixelLSC');
  DeleteSuperpixelLSC := CVBind(Handle, 'cv_ximgproc_deleteSuperpixelLSC');
  SuperpixelLSCIterate := CVBind(Handle, 'cv_ximgproc_superpixelLSCIterate');
  SuperpixelLSCGetLabels := CVBind(Handle, 'cv_ximgproc_superpixelLSCGetLabels');
  SuperpixelLSCGetNumberOfSuperpixels := CVBind(Handle, 'cv_ximgproc_superpixelLSCGetNumberOfSuperpixels');
  SuperpixelLSCGetLabelContourMask := CVBind(Handle, 'cv_ximgproc_superpixelLSCGetLabelContourMask');
  SuperpixelLSCEnforceLabelConnectivity := CVBind(Handle,
    'cv_ximgproc_superpixelLSCEnforceLabelConnectivity');
  PeiLinNormalization := CVBind(Handle, 'cv_ximgproc_PeiLinNormalization');
  FourierDescriptor := CVBind(Handle, 'cv_ximgproc_fourierDescriptor');
  ContourSampling := CVBind(Handle, 'cv_ximgproc_contourSampling');
  ColorMatchTemplate := CVBind(Handle, 'cv_ximgproc_colorMatchTemplate');
end;

end.
