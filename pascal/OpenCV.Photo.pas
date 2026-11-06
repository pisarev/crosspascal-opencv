{ ************************************************************************** }
{                                                                            }
{ OpenCV.Photo                                                               }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Photo;

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
  TCVPhotoModule = record
  public
    type
      TInpaint = function(Source, InpaintMask: TMat; Target: PMat; InpaintRadius: Double;
        Flags: Integer): LongBool; cdecl;
      TFastNlMeansDenoising = function(Source: TMat; Target: PMat; H: Single;
        TemplateWindowSize, SearchWindowSize: Integer): LongBool; cdecl;
      TFastNlMeansDenoisingColored = function(Source: TMat; Target: PMat; H, HForColorComponents: Single;
        TemplateWindowSize, SearchWindowSize: Integer): LongBool; cdecl;
      TSeamlessClone = function(Source, Destination, Mask: TMat; Center: TOCVPoint; Target: PMat;
        Flags: Integer): LongBool; cdecl;
      TFastNlMeansDenoisingMulti = function(Sources: PMat;
        Count, ImgToDenoiseIndex, TemporalWindowSize: Integer; Target: PMat; H: Single;
        TemplateWindowSize, SearchWindowSize: Integer): LongBool; cdecl;
      TFastNlMeansDenoisingColoredMulti = function(Sources: PMat;
        Count, ImgToDenoiseIndex, TemporalWindowSize: Integer; Target: PMat; H, HForColorComponents: Single;
        TemplateWindowSize, SearchWindowSize: Integer): LongBool; cdecl;
      TEdgePreservingFilter = function(Source: TMat; Target: PMat; Flags: Integer;
        SigmaS, SigmaR: Single): LongBool; cdecl;
      TDetailEnhance = function(Source: TMat; Target: PMat; SigmaS, SigmaR: Single): LongBool; cdecl;
      TPencilSketch = function(Source: TMat; Target1, Target2: PMat; SigmaS, SigmaR: Single;
        ShadeFactor: Single): LongBool; cdecl;
      TStylization = function(Source: TMat; Target: PMat; SigmaS, SigmaR: Single): LongBool; cdecl;
      TColorChange = function(Source, Mask: TMat; Target: PMat;
        RedMul, GreenMul, BlueMul: Single): LongBool; cdecl;
      TIlluminationChange = function(Source, Mask: TMat; Target: PMat; Alpha, Beta: Single): LongBool; cdecl;
      TTextureFlattening = function(Source, Mask: TMat; Target: PMat; LowThreshold, HighThreshold: Single;
        KernelSize: Integer): LongBool; cdecl;
      TCreateMergeMertens = function(ContrastWeight, SaturationWeight, ExposureWeight: Single;
        Handle: PPointer): LongBool; cdecl;
      TCreateMergeDebevec = function(Handle: PPointer): LongBool; cdecl;
      TCreateAlignMTB = function(MaxBits, ExcludeRange: Integer; Cut: LongBool;
        Handle: PPointer): LongBool; cdecl;
      TCreateTonemapDrago = function(Gamma, Saturation, Bias: Single; Handle: PPointer): LongBool; cdecl;
      TCreateTonemapReinhard = function(Gamma, Intensity, LightAdapt, ColorAdapt: Single;
        Handle: PPointer): LongBool; cdecl;
      TCreateMergeRobertson = function: Pointer; cdecl;
      TCreateTonemapMantiuk = function(Gamma, Scale, Saturation: Single): Pointer; cdecl;
      TCreateCalibrateDebevec = function(Samples: Integer; Lambda: Single; Random: LongBool): Pointer; cdecl;
      TCreateCalibrateRobertson = function(MaxIter: Integer; Threshold: Single): Pointer; cdecl;
      TDecolor = function(Source: TMat; Grayscale, ColorBoost: PMat): LongBool; cdecl;
      TDenoiseTVL1 = function(Observations: PMat; Count: Integer; Result: PMat; Lambda: Double;
        NIters: Integer): LongBool; cdecl;
      TCreateTonemap = function(Gamma: Single): Pointer; cdecl;
      TDeleteTonemap = function(Handle: Pointer): LongBool; cdecl;
      TTonemapProcess = function(Handle: Pointer; Source: TMat; Target: PMat): LongBool; cdecl;
      TTonemapGetGamma = function(Handle: Pointer; Gamma: PSingle): LongBool; cdecl;
      TTonemapSetGamma = function(Handle: Pointer; Gamma: Single): LongBool; cdecl;
      TDeleteTonemapDrago = function(Handle: Pointer): LongBool; cdecl;
      TTonemapDragoProcess = function(Handle: Pointer; Source: TMat; Target: PMat): LongBool; cdecl;
      TTonemapDragoGetSaturation = function(Handle: Pointer; Saturation: PSingle): LongBool; cdecl;
      TTonemapDragoSetSaturation = function(Handle: Pointer; Saturation: Single): LongBool; cdecl;
      TTonemapDragoGetBias = function(Handle: Pointer; Bias: PSingle): LongBool; cdecl;
      TTonemapDragoSetBias = function(Handle: Pointer; Bias: Single): LongBool; cdecl;
      TDeleteTonemapReinhard = function(Handle: Pointer): LongBool; cdecl;
      TTonemapReinhardProcess = function(Handle: Pointer; Source: TMat; Target: PMat): LongBool; cdecl;
      TTonemapReinhardGetIntensity = function(Handle: Pointer; Intensity: PSingle): LongBool; cdecl;
      TTonemapReinhardSetIntensity = function(Handle: Pointer; Intensity: Single): LongBool; cdecl;
      TTonemapReinhardGetLightAdaptation = function(Handle: Pointer; LightAdapt: PSingle): LongBool; cdecl;
      TTonemapReinhardSetLightAdaptation = function(Handle: Pointer; LightAdapt: Single): LongBool; cdecl;
      TTonemapReinhardGetColorAdaptation = function(Handle: Pointer; ColorAdapt: PSingle): LongBool; cdecl;
      TTonemapReinhardSetColorAdaptation = function(Handle: Pointer; ColorAdapt: Single): LongBool; cdecl;
      TDeleteTonemapMantiuk = function(Handle: Pointer): LongBool; cdecl;
      TTonemapMantiukProcess = function(Handle: Pointer; Source: TMat; Target: PMat): LongBool; cdecl;
      TTonemapMantiukGetScale = function(Handle: Pointer; Scale: PSingle): LongBool; cdecl;
      TTonemapMantiukSetScale = function(Handle: Pointer; Scale: Single): LongBool; cdecl;
      TTonemapMantiukGetSaturation = function(Handle: Pointer; Saturation: PSingle): LongBool; cdecl;
      TTonemapMantiukSetSaturation = function(Handle: Pointer; Saturation: Single): LongBool; cdecl;
      TDeleteMergeMertens = function(Handle: Pointer): LongBool; cdecl;
      TMergeMertensProcess = function(Handle: Pointer; Sources: PMat; Count: Integer;
        Target: PMat): LongBool; cdecl;
      TMergeMertensGetContrastWeight = function(Handle: Pointer; Weight: PSingle): LongBool; cdecl;
      TMergeMertensSetContrastWeight = function(Handle: Pointer; Weight: Single): LongBool; cdecl;
      TMergeMertensGetSaturationWeight = function(Handle: Pointer; Weight: PSingle): LongBool; cdecl;
      TMergeMertensSetSaturationWeight = function(Handle: Pointer; Weight: Single): LongBool; cdecl;
      TMergeMertensGetExposureWeight = function(Handle: Pointer; Weight: PSingle): LongBool; cdecl;
      TMergeMertensSetExposureWeight = function(Handle: Pointer; Weight: Single): LongBool; cdecl;
      TDeleteMergeDebevec = function(Handle: Pointer): LongBool; cdecl;
      TMergeDebevecProcess = function(Handle: Pointer; Sources: PMat; Count: Integer; Times: TMat;
        Target: PMat): LongBool; cdecl;
      TDeleteMergeRobertson = function(Handle: Pointer): LongBool; cdecl;
      TMergeRobertsonProcess = function(Handle: Pointer; Sources: PMat; Count: Integer; Times: TMat;
        Target: PMat): LongBool; cdecl;
      TDeleteAlignMTB = function(Handle: Pointer): LongBool; cdecl;
      TAlignMTBProcess = function(Handle: Pointer; Sources: PMat; Count: Integer;
        Targets: PMat): LongBool; cdecl;
      TAlignMTBGetMaxBits = function(Handle: Pointer; MaxBits: PInteger): LongBool; cdecl;
      TAlignMTBSetMaxBits = function(Handle: Pointer; MaxBits: Integer): LongBool; cdecl;
      TAlignMTBGetExcludeRange = function(Handle: Pointer; ExcludeRange: PInteger): LongBool; cdecl;
      TAlignMTBSetExcludeRange = function(Handle: Pointer; ExcludeRange: Integer): LongBool; cdecl;
      TAlignMTBGetCut = function(Handle: Pointer; Cut: PLongBool): LongBool; cdecl;
      TAlignMTBSetCut = function(Handle: Pointer; Cut: LongBool): LongBool; cdecl;
      TDeleteCalibrateDebevec = function(Handle: Pointer): LongBool; cdecl;
      TCalibrateDebevecProcess = function(Handle: Pointer; Sources: PMat; Count: Integer; Times: TMat;
        Target: PMat): LongBool; cdecl;
      TCalibrateDebevecGetSamples = function(Handle: Pointer; Samples: PInteger): LongBool; cdecl;
      TCalibrateDebevecSetSamples = function(Handle: Pointer; Samples: Integer): LongBool; cdecl;
      TCalibrateDebevecGetLambda = function(Handle: Pointer; Lambda: PSingle): LongBool; cdecl;
      TCalibrateDebevecSetLambda = function(Handle: Pointer; Lambda: Single): LongBool; cdecl;
      TCalibrateDebevecGetRandom = function(Handle: Pointer; Random: PLongBool): LongBool; cdecl;
      TCalibrateDebevecSetRandom = function(Handle: Pointer; Random: LongBool): LongBool; cdecl;
      TDeleteCalibrateRobertson = function(Handle: Pointer): LongBool; cdecl;
      TCalibrateRobertsonProcess = function(Handle: Pointer; Sources: PMat; Count: Integer; Times: TMat;
        Target: PMat): LongBool; cdecl;
      TCalibrateRobertsonGetMaxIter = function(Handle: Pointer; MaxIter: PInteger): LongBool; cdecl;
      TCalibrateRobertsonSetMaxIter = function(Handle: Pointer; MaxIter: Integer): LongBool; cdecl;
      TCalibrateRobertsonGetThreshold = function(Handle: Pointer; Threshold: PSingle): LongBool; cdecl;
      TCalibrateRobertsonSetThreshold = function(Handle: Pointer; Threshold: Single): LongBool; cdecl;
    var
      Inpaint: TInpaint;
      FastNlMeansDenoising: TFastNlMeansDenoising;
      FastNlMeansDenoisingColored: TFastNlMeansDenoisingColored;
      SeamlessClone: TSeamlessClone;
      FastNlMeansDenoisingMulti: TFastNlMeansDenoisingMulti;
      FastNlMeansDenoisingColoredMulti: TFastNlMeansDenoisingColoredMulti;
      EdgePreservingFilter: TEdgePreservingFilter;
      DetailEnhance: TDetailEnhance;
      PencilSketch: TPencilSketch;
      Stylization: TStylization;
      ColorChange: TColorChange;
      IlluminationChange: TIlluminationChange;
      TextureFlattening: TTextureFlattening;
      CreateMergeMertens: TCreateMergeMertens;
      CreateMergeDebevec: TCreateMergeDebevec;
      CreateAlignMTB: TCreateAlignMTB;
      CreateTonemapDrago: TCreateTonemapDrago;
      CreateTonemapReinhard: TCreateTonemapReinhard;
      CreateMergeRobertson: TCreateMergeRobertson;
      CreateTonemapMantiuk: TCreateTonemapMantiuk;
      CreateCalibrateDebevec: TCreateCalibrateDebevec;
      CreateCalibrateRobertson: TCreateCalibrateRobertson;
      Decolor: TDecolor;
      DenoiseTVL1: TDenoiseTVL1;
      CreateTonemap: TCreateTonemap;
      DeleteTonemap: TDeleteTonemap;
      TonemapProcess: TTonemapProcess;
      TonemapGetGamma: TTonemapGetGamma;
      TonemapSetGamma: TTonemapSetGamma;
      DeleteTonemapDrago: TDeleteTonemapDrago;
      TonemapDragoProcess: TTonemapDragoProcess;
      TonemapDragoGetSaturation: TTonemapDragoGetSaturation;
      TonemapDragoSetSaturation: TTonemapDragoSetSaturation;
      TonemapDragoGetBias: TTonemapDragoGetBias;
      TonemapDragoSetBias: TTonemapDragoSetBias;
      DeleteTonemapReinhard: TDeleteTonemapReinhard;
      TonemapReinhardProcess: TTonemapReinhardProcess;
      TonemapReinhardGetIntensity: TTonemapReinhardGetIntensity;
      TonemapReinhardSetIntensity: TTonemapReinhardSetIntensity;
      TonemapReinhardGetLightAdaptation: TTonemapReinhardGetLightAdaptation;
      TonemapReinhardSetLightAdaptation: TTonemapReinhardSetLightAdaptation;
      TonemapReinhardGetColorAdaptation: TTonemapReinhardGetColorAdaptation;
      TonemapReinhardSetColorAdaptation: TTonemapReinhardSetColorAdaptation;
      DeleteTonemapMantiuk: TDeleteTonemapMantiuk;
      TonemapMantiukProcess: TTonemapMantiukProcess;
      TonemapMantiukGetScale: TTonemapMantiukGetScale;
      TonemapMantiukSetScale: TTonemapMantiukSetScale;
      TonemapMantiukGetSaturation: TTonemapMantiukGetSaturation;
      TonemapMantiukSetSaturation: TTonemapMantiukSetSaturation;
      DeleteMergeMertens: TDeleteMergeMertens;
      MergeMertensProcess: TMergeMertensProcess;
      MergeMertensGetContrastWeight: TMergeMertensGetContrastWeight;
      MergeMertensSetContrastWeight: TMergeMertensSetContrastWeight;
      MergeMertensGetSaturationWeight: TMergeMertensGetSaturationWeight;
      MergeMertensSetSaturationWeight: TMergeMertensSetSaturationWeight;
      MergeMertensGetExposureWeight: TMergeMertensGetExposureWeight;
      MergeMertensSetExposureWeight: TMergeMertensSetExposureWeight;
      DeleteMergeDebevec: TDeleteMergeDebevec;
      MergeDebevecProcess: TMergeDebevecProcess;
      DeleteMergeRobertson: TDeleteMergeRobertson;
      MergeRobertsonProcess: TMergeRobertsonProcess;
      DeleteAlignMTB: TDeleteAlignMTB;
      AlignMTBProcess: TAlignMTBProcess;
      AlignMTBGetMaxBits: TAlignMTBGetMaxBits;
      AlignMTBSetMaxBits: TAlignMTBSetMaxBits;
      AlignMTBGetExcludeRange: TAlignMTBGetExcludeRange;
      AlignMTBSetExcludeRange: TAlignMTBSetExcludeRange;
      AlignMTBGetCut: TAlignMTBGetCut;
      AlignMTBSetCut: TAlignMTBSetCut;
      DeleteCalibrateDebevec: TDeleteCalibrateDebevec;
      CalibrateDebevecProcess: TCalibrateDebevecProcess;
      CalibrateDebevecGetSamples: TCalibrateDebevecGetSamples;
      CalibrateDebevecSetSamples: TCalibrateDebevecSetSamples;
      CalibrateDebevecGetLambda: TCalibrateDebevecGetLambda;
      CalibrateDebevecSetLambda: TCalibrateDebevecSetLambda;
      CalibrateDebevecGetRandom: TCalibrateDebevecGetRandom;
      CalibrateDebevecSetRandom: TCalibrateDebevecSetRandom;
      DeleteCalibrateRobertson: TDeleteCalibrateRobertson;
      CalibrateRobertsonProcess: TCalibrateRobertsonProcess;
      CalibrateRobertsonGetMaxIter: TCalibrateRobertsonGetMaxIter;
      CalibrateRobertsonSetMaxIter: TCalibrateRobertsonSetMaxIter;
      CalibrateRobertsonGetThreshold: TCalibrateRobertsonGetThreshold;
      CalibrateRobertsonSetThreshold: TCalibrateRobertsonSetThreshold;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVPhotoModule.Initialize(const Handle: TLibHandle);
begin
  Inpaint := CVBind(Handle, 'cv_photo_inpaint');
  FastNlMeansDenoising := CVBind(Handle, 'cv_photo_fastNlMeansDenoising');
  FastNlMeansDenoisingColored := CVBind(Handle, 'cv_photo_fastNlMeansDenoisingColored');
  SeamlessClone := CVBind(Handle, 'cv_photo_seamlessClone');
  FastNlMeansDenoisingMulti := CVBind(Handle, 'cv_photo_fastNlMeansDenoisingMulti');
  FastNlMeansDenoisingColoredMulti := CVBind(Handle, 'cv_photo_fastNlMeansDenoisingColoredMulti');
  EdgePreservingFilter := CVBind(Handle, 'cv_photo_edgePreservingFilter');
  DetailEnhance := CVBind(Handle, 'cv_photo_detailEnhance');
  PencilSketch := CVBind(Handle, 'cv_photo_pencilSketch');
  Stylization := CVBind(Handle, 'cv_photo_stylization');
  ColorChange := CVBind(Handle, 'cv_photo_colorChange');
  IlluminationChange := CVBind(Handle, 'cv_photo_illuminationChange');
  TextureFlattening := CVBind(Handle, 'cv_photo_textureFlattening');
  CreateMergeMertens := CVBind(Handle, 'cv_photo_createMergeMertens');
  CreateMergeDebevec := CVBind(Handle, 'cv_photo_createMergeDebevec');
  CreateAlignMTB := CVBind(Handle, 'cv_photo_createAlignMTB');
  CreateTonemapDrago := CVBind(Handle, 'cv_photo_createTonemapDrago');
  CreateTonemapReinhard := CVBind(Handle, 'cv_photo_createTonemapReinhard');
  CreateMergeRobertson := CVBind(Handle, 'cv_photo_createMergeRobertson');
  CreateTonemapMantiuk := CVBind(Handle, 'cv_photo_createTonemapMantiuk');
  CreateCalibrateDebevec := CVBind(Handle, 'cv_photo_createCalibrateDebevec');
  CreateCalibrateRobertson := CVBind(Handle, 'cv_photo_createCalibrateRobertson');
  Decolor := CVBind(Handle, 'cv_photo_decolor');
  DenoiseTVL1 := CVBind(Handle, 'cv_photo_denoise_TVL1');
  CreateTonemap := CVBind(Handle, 'cv_photo_createTonemap');
  DeleteTonemap := CVBind(Handle, 'cv_photo_deleteTonemap');
  TonemapProcess := CVBind(Handle, 'cv_photo_tonemapProcess');
  TonemapGetGamma := CVBind(Handle, 'cv_photo_tonemapGetGamma');
  TonemapSetGamma := CVBind(Handle, 'cv_photo_tonemapSetGamma');
  DeleteTonemapDrago := CVBind(Handle, 'cv_photo_deleteTonemapDrago');
  TonemapDragoProcess := CVBind(Handle, 'cv_photo_tonemapDragoProcess');
  TonemapDragoGetSaturation := CVBind(Handle, 'cv_photo_tonemapDragoGetSaturation');
  TonemapDragoSetSaturation := CVBind(Handle, 'cv_photo_tonemapDragoSetSaturation');
  TonemapDragoGetBias := CVBind(Handle, 'cv_photo_tonemapDragoGetBias');
  TonemapDragoSetBias := CVBind(Handle, 'cv_photo_tonemapDragoSetBias');
  DeleteTonemapReinhard := CVBind(Handle, 'cv_photo_deleteTonemapReinhard');
  TonemapReinhardProcess := CVBind(Handle, 'cv_photo_tonemapReinhardProcess');
  TonemapReinhardGetIntensity := CVBind(Handle, 'cv_photo_tonemapReinhardGetIntensity');
  TonemapReinhardSetIntensity := CVBind(Handle, 'cv_photo_tonemapReinhardSetIntensity');
  TonemapReinhardGetLightAdaptation := CVBind(Handle, 'cv_photo_tonemapReinhardGetLightAdaptation');
  TonemapReinhardSetLightAdaptation := CVBind(Handle, 'cv_photo_tonemapReinhardSetLightAdaptation');
  TonemapReinhardGetColorAdaptation := CVBind(Handle, 'cv_photo_tonemapReinhardGetColorAdaptation');
  TonemapReinhardSetColorAdaptation := CVBind(Handle, 'cv_photo_tonemapReinhardSetColorAdaptation');
  DeleteTonemapMantiuk := CVBind(Handle, 'cv_photo_deleteTonemapMantiuk');
  TonemapMantiukProcess := CVBind(Handle, 'cv_photo_tonemapMantiukProcess');
  TonemapMantiukGetScale := CVBind(Handle, 'cv_photo_tonemapMantiukGetScale');
  TonemapMantiukSetScale := CVBind(Handle, 'cv_photo_tonemapMantiukSetScale');
  TonemapMantiukGetSaturation := CVBind(Handle, 'cv_photo_tonemapMantiukGetSaturation');
  TonemapMantiukSetSaturation := CVBind(Handle, 'cv_photo_tonemapMantiukSetSaturation');
  DeleteMergeMertens := CVBind(Handle, 'cv_photo_deleteMergeMertens');
  MergeMertensProcess := CVBind(Handle, 'cv_photo_mergeMertensProcess');
  MergeMertensGetContrastWeight := CVBind(Handle, 'cv_photo_mergeMertensGetContrastWeight');
  MergeMertensSetContrastWeight := CVBind(Handle, 'cv_photo_mergeMertensSetContrastWeight');
  MergeMertensGetSaturationWeight := CVBind(Handle, 'cv_photo_mergeMertensGetSaturationWeight');
  MergeMertensSetSaturationWeight := CVBind(Handle, 'cv_photo_mergeMertensSetSaturationWeight');
  MergeMertensGetExposureWeight := CVBind(Handle, 'cv_photo_mergeMertensGetExposureWeight');
  MergeMertensSetExposureWeight := CVBind(Handle, 'cv_photo_mergeMertensSetExposureWeight');
  DeleteMergeDebevec := CVBind(Handle, 'cv_photo_deleteMergeDebevec');
  MergeDebevecProcess := CVBind(Handle, 'cv_photo_mergeDebevecProcess');
  DeleteMergeRobertson := CVBind(Handle, 'cv_photo_deleteMergeRobertson');
  MergeRobertsonProcess := CVBind(Handle, 'cv_photo_mergeRobertsonProcess');
  DeleteAlignMTB := CVBind(Handle, 'cv_photo_deleteAlignMTB');
  AlignMTBProcess := CVBind(Handle, 'cv_photo_alignMTBProcess');
  AlignMTBGetMaxBits := CVBind(Handle, 'cv_photo_alignMTBGetMaxBits');
  AlignMTBSetMaxBits := CVBind(Handle, 'cv_photo_alignMTBSetMaxBits');
  AlignMTBGetExcludeRange := CVBind(Handle, 'cv_photo_alignMTBGetExcludeRange');
  AlignMTBSetExcludeRange := CVBind(Handle, 'cv_photo_alignMTBSetExcludeRange');
  AlignMTBGetCut := CVBind(Handle, 'cv_photo_alignMTBGetCut');
  AlignMTBSetCut := CVBind(Handle, 'cv_photo_alignMTBSetCut');
  DeleteCalibrateDebevec := CVBind(Handle, 'cv_photo_deleteCalibrateDebevec');
  CalibrateDebevecProcess := CVBind(Handle, 'cv_photo_calibrateDebevecProcess');
  CalibrateDebevecGetSamples := CVBind(Handle, 'cv_photo_calibrateDebevecGetSamples');
  CalibrateDebevecSetSamples := CVBind(Handle, 'cv_photo_calibrateDebevecSetSamples');
  CalibrateDebevecGetLambda := CVBind(Handle, 'cv_photo_calibrateDebevecGetLambda');
  CalibrateDebevecSetLambda := CVBind(Handle, 'cv_photo_calibrateDebevecSetLambda');
  CalibrateDebevecGetRandom := CVBind(Handle, 'cv_photo_calibrateDebevecGetRandom');
  CalibrateDebevecSetRandom := CVBind(Handle, 'cv_photo_calibrateDebevecSetRandom');
  DeleteCalibrateRobertson := CVBind(Handle, 'cv_photo_deleteCalibrateRobertson');
  CalibrateRobertsonProcess := CVBind(Handle, 'cv_photo_calibrateRobertsonProcess');
  CalibrateRobertsonGetMaxIter := CVBind(Handle, 'cv_photo_calibrateRobertsonGetMaxIter');
  CalibrateRobertsonSetMaxIter := CVBind(Handle, 'cv_photo_calibrateRobertsonSetMaxIter');
  CalibrateRobertsonGetThreshold := CVBind(Handle, 'cv_photo_calibrateRobertsonGetThreshold');
  CalibrateRobertsonSetThreshold := CVBind(Handle, 'cv_photo_calibrateRobertsonSetThreshold');
end;

end.
