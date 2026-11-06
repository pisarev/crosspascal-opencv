{ ************************************************************************** }
{                                                                            }
{ OpenCV.XFeatures2D                                                         }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev (ypisareff@outlook.com)               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.XFeatures2D;

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
  TCVXFeatures2DModule = record
  public
    type
      TCreateSURF = function(HessianThreshold: Double; NOctaves, NOctaveLayers: Integer;
        Extended, Upright: LongBool): Pointer; cdecl;
      TDeleteSURF = function(Surf: Pointer): LongBool; cdecl;
      TSurfDetectAndCompute = function(Surf: Pointer; Image, Mask, KeyPoints, Descriptors: PMat;
        UseProvidedKeypoints: LongBool): LongBool; cdecl;
      TSurfGetHessianThreshold = function(Surf: Pointer): Double; cdecl;
      TSurfSetHessianThreshold = function(Surf: Pointer; Threshold: Double): LongBool; cdecl;
      TSurfGetNOctaves = function(Surf: Pointer): Integer; cdecl;
      TSurfSetNOctaves = function(Surf: Pointer; NOctaves: Integer): LongBool; cdecl;
      TSurfGetNOctaveLayers = function(Surf: Pointer): Integer; cdecl;
      TSurfSetNOctaveLayers = function(Surf: Pointer; NOctaveLayers: Integer): LongBool; cdecl;
      TSurfGetExtended = function(Surf: Pointer): Integer; cdecl;
      TSurfSetExtended = function(Surf: Pointer; Extended: LongBool): LongBool; cdecl;
      TSurfGetUpright = function(Surf: Pointer): Integer; cdecl;
      TSurfSetUpright = function(Surf: Pointer; Upright: LongBool): LongBool; cdecl;
      TCreateFREAK = function(OrientationNormalized, ScaleNormalized: LongBool; PatternScale: Single;
        NOctaves: Integer): Pointer; cdecl;
      TDeleteFREAK = function(Freak: Pointer): LongBool; cdecl;
      TFreakCompute = function(Freak: Pointer; Image, KeyPoints, Descriptors: PMat): LongBool; cdecl;
      TCreateDAISY = function(Radius: Single; QRadius, QTheta, QHist, Norm: Integer; H: PMat;
        Interpolation, UseOrientation: LongBool): Pointer; cdecl;
      TDeleteDAISY = function(Daisy: Pointer): LongBool; cdecl;
      TDaisyCompute = function(Daisy: Pointer; Image, KeyPoints, Descriptors: PMat): LongBool; cdecl;
      TCreateBRIEF = function(Bytes: Integer; UseOrientation: LongBool): Pointer; cdecl;
      TDeleteBRIEF = function(Brief: Pointer): LongBool; cdecl;
      TBriefCompute = function(Brief: Pointer; Image, KeyPoints, Descriptors: PMat): LongBool; cdecl;
      TCreateLATCH = function(Bytes: Integer; RotationInvariance: LongBool; HalfSsdSize: Integer;
        Sigma: Double): Pointer; cdecl;
      TDeleteLATCH = function(Latch: Pointer): LongBool; cdecl;
      TLatchCompute = function(Latch: Pointer; Image, KeyPoints, Descriptors: PMat): LongBool; cdecl;
      TCreateBEBLID = function(ScaleFactor: Single; NBits: Integer): Pointer; cdecl;
      TDeleteBEBLID = function(Beblid: Pointer): LongBool; cdecl;
      TBeblidCompute = function(Beblid: Pointer; Image, KeyPoints, Descriptors: PMat): LongBool; cdecl;
      TCreateStarDetector = function(MaxSize, ResponseThreshold, LineThresholdProjected, LineThresholdBinarized, SuppressNonmaxSize: Integer): Pointer; cdecl;
      TDeleteStarDetector = function(Detector: Pointer): LongBool; cdecl;
      TStarDetectorDetect = function(Detector: Pointer; Image, KeyPoints, Mask: PMat): LongBool; cdecl;
      TMatchGMS = function(Size1W, Size1H, Size2W, Size2H: Integer;
        KeyPoints1, KeyPoints2, Matches1to2, MatchesGMS: PMat; WithRotation, WithScale: LongBool;
        ThresholdFactor: Double): LongBool; cdecl;
      TCreatePCTSignatures = function(InitSampleCount, InitSeedCount, PointDistribution: Integer): Pointer; cdecl;
      TDeletePCTSignatures = function(Pct: Pointer): LongBool; cdecl;
      TPctComputeSignature = function(Pct: Pointer; Image, Signature: PMat): LongBool; cdecl;
      TPctDrawSignature = function(Source, Signature, Result: PMat; RadiusToShorterSideRatio: Single;
        BorderThickness: Integer): LongBool; cdecl;
    var
      CreateSURF: TCreateSURF;
      DeleteSURF: TDeleteSURF;
      SurfDetectAndCompute: TSurfDetectAndCompute;
      SurfGetHessianThreshold: TSurfGetHessianThreshold;
      SurfSetHessianThreshold: TSurfSetHessianThreshold;
      SurfGetNOctaves: TSurfGetNOctaves;
      SurfSetNOctaves: TSurfSetNOctaves;
      SurfGetNOctaveLayers: TSurfGetNOctaveLayers;
      SurfSetNOctaveLayers: TSurfSetNOctaveLayers;
      SurfGetExtended: TSurfGetExtended;
      SurfSetExtended: TSurfSetExtended;
      SurfGetUpright: TSurfGetUpright;
      SurfSetUpright: TSurfSetUpright;
      CreateFREAK: TCreateFREAK;
      DeleteFREAK: TDeleteFREAK;
      FreakCompute: TFreakCompute;
      CreateDAISY: TCreateDAISY;
      DeleteDAISY: TDeleteDAISY;
      DaisyCompute: TDaisyCompute;
      CreateBRIEF: TCreateBRIEF;
      DeleteBRIEF: TDeleteBRIEF;
      BriefCompute: TBriefCompute;
      CreateLATCH: TCreateLATCH;
      DeleteLATCH: TDeleteLATCH;
      LatchCompute: TLatchCompute;
      CreateBEBLID: TCreateBEBLID;
      DeleteBEBLID: TDeleteBEBLID;
      BeblidCompute: TBeblidCompute;
      CreateStarDetector: TCreateStarDetector;
      DeleteStarDetector: TDeleteStarDetector;
      StarDetectorDetect: TStarDetectorDetect;
      MatchGMS: TMatchGMS;
      CreatePCTSignatures: TCreatePCTSignatures;
      DeletePCTSignatures: TDeletePCTSignatures;
      PctComputeSignature: TPctComputeSignature;
      PctDrawSignature: TPctDrawSignature;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVXFeatures2DModule.Initialize(const Handle: TLibHandle);
begin
  CreateSURF := CVBind(Handle, 'cv_xfeatures2d_createSURF');
  DeleteSURF := CVBind(Handle, 'cv_xfeatures2d_deleteSURF');
  SurfDetectAndCompute := CVBind(Handle, 'cv_xfeatures2d_surfDetectAndCompute');
  SurfGetHessianThreshold := CVBind(Handle, 'cv_xfeatures2d_surfGetHessianThreshold');
  SurfSetHessianThreshold := CVBind(Handle, 'cv_xfeatures2d_surfSetHessianThreshold');
  SurfGetNOctaves := CVBind(Handle, 'cv_xfeatures2d_surfGetNOctaves');
  SurfSetNOctaves := CVBind(Handle, 'cv_xfeatures2d_surfSetNOctaves');
  SurfGetNOctaveLayers := CVBind(Handle, 'cv_xfeatures2d_surfGetNOctaveLayers');
  SurfSetNOctaveLayers := CVBind(Handle, 'cv_xfeatures2d_surfSetNOctaveLayers');
  SurfGetExtended := CVBind(Handle, 'cv_xfeatures2d_surfGetExtended');
  SurfSetExtended := CVBind(Handle, 'cv_xfeatures2d_surfSetExtended');
  SurfGetUpright := CVBind(Handle, 'cv_xfeatures2d_surfGetUpright');
  SurfSetUpright := CVBind(Handle, 'cv_xfeatures2d_surfSetUpright');
  CreateFREAK := CVBind(Handle, 'cv_xfeatures2d_createFREAK');
  DeleteFREAK := CVBind(Handle, 'cv_xfeatures2d_deleteFREAK');
  FreakCompute := CVBind(Handle, 'cv_xfeatures2d_freakCompute');
  CreateDAISY := CVBind(Handle, 'cv_xfeatures2d_createDAISY');
  DeleteDAISY := CVBind(Handle, 'cv_xfeatures2d_deleteDAISY');
  DaisyCompute := CVBind(Handle, 'cv_xfeatures2d_daisyCompute');
  CreateBRIEF := CVBind(Handle, 'cv_xfeatures2d_createBRIEF');
  DeleteBRIEF := CVBind(Handle, 'cv_xfeatures2d_deleteBRIEF');
  BriefCompute := CVBind(Handle, 'cv_xfeatures2d_briefCompute');
  CreateLATCH := CVBind(Handle, 'cv_xfeatures2d_createLATCH');
  DeleteLATCH := CVBind(Handle, 'cv_xfeatures2d_deleteLATCH');
  LatchCompute := CVBind(Handle, 'cv_xfeatures2d_latchCompute');
  CreateBEBLID := CVBind(Handle, 'cv_xfeatures2d_createBEBLID');
  DeleteBEBLID := CVBind(Handle, 'cv_xfeatures2d_deleteBEBLID');
  BeblidCompute := CVBind(Handle, 'cv_xfeatures2d_beblidCompute');
  CreateStarDetector := CVBind(Handle, 'cv_xfeatures2d_createStarDetector');
  DeleteStarDetector := CVBind(Handle, 'cv_xfeatures2d_deleteStarDetector');
  StarDetectorDetect := CVBind(Handle, 'cv_xfeatures2d_starDetectorDetect');
  MatchGMS := CVBind(Handle, 'cv_xfeatures2d_matchGMS');
  CreatePCTSignatures := CVBind(Handle, 'cv_xfeatures2d_createPCTSignatures');
  DeletePCTSignatures := CVBind(Handle, 'cv_xfeatures2d_deletePCTSignatures');
  PctComputeSignature := CVBind(Handle, 'cv_xfeatures2d_pctComputeSignature');
  PctDrawSignature := CVBind(Handle, 'cv_xfeatures2d_pctDrawSignature');
end;

end.
