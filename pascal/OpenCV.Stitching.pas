{ ************************************************************************** }
{                                                                            }
{ OpenCV.Stitching                                                           }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev (ypisareff@outlook.com)               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Stitching;

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
  TCVStitchingModule = record
  public
    type
      TCreateStitcher = function(Mode: Integer): Pointer; cdecl;
      TDeleteStitcher = function(Handle: Pointer): LongBool; cdecl;
      TStitch = function(Handle: Pointer; Images: PMat; ImageCount: Integer; Pano: PMat): LongBool; cdecl;
      TEstimateTransform = function(Handle: Pointer; Images: PMat; ImageCount: Integer): LongBool; cdecl;
      TSetPanoConfidenceThresh = function(Handle: Pointer; ConfThresh: Double): LongBool; cdecl;
      TGetPanoConfidenceThresh = function(Handle: Pointer; ConfThresh: PDouble): LongBool; cdecl;
      TComposePanorama = function(Handle: Pointer; Pano: PMat): Integer; cdecl;
      TSetRegistrationResol = function(Handle: Pointer; Resol: Double): LongBool; cdecl;
      TSetSeamEstimationResol = function(Handle: Pointer; Resol: Double): LongBool; cdecl;
      TSetCompositingResol = function(Handle: Pointer; Resol: Double): LongBool; cdecl;
      TGetWaveCorrection = function(Handle: Pointer; Val: PLongBool): LongBool; cdecl;
      TSetWaveCorrection = function(Handle: Pointer; Val: LongBool): LongBool; cdecl;
      TGetWaveCorrectKind = function(Handle: Pointer; Kind: PInteger): LongBool; cdecl;
      TSetWaveCorrectKind = function(Handle: Pointer; Kind: Integer): LongBool; cdecl;
      TGetInterpolationFlags = function(Handle: Pointer; Flags: PInteger): LongBool; cdecl;
      TSetInterpolationFlags = function(Handle: Pointer; Flags: Integer): LongBool; cdecl;
      TStitcherComponent = function(Handle: Pointer; Indices: PInteger; Count: PInteger): LongBool; cdecl;
      TStitcherResultMask = function(Handle: Pointer; Mask: PMat): LongBool; cdecl;
      TStitcherWorkScale = function(Handle: Pointer): Double; cdecl;
    var
      CreateStitcher: TCreateStitcher;
      DeleteStitcher: TDeleteStitcher;
      Stitch: TStitch;
      EstimateTransform: TEstimateTransform;
      SetPanoConfidenceThresh: TSetPanoConfidenceThresh;
      GetPanoConfidenceThresh: TGetPanoConfidenceThresh;
      ComposePanorama: TComposePanorama;
      SetRegistrationResol: TSetRegistrationResol;
      SetSeamEstimationResol: TSetSeamEstimationResol;
      SetCompositingResol: TSetCompositingResol;
      GetWaveCorrection: TGetWaveCorrection;
      SetWaveCorrection: TSetWaveCorrection;
      GetWaveCorrectKind: TGetWaveCorrectKind;
      SetWaveCorrectKind: TSetWaveCorrectKind;
      GetInterpolationFlags: TGetInterpolationFlags;
      SetInterpolationFlags: TSetInterpolationFlags;
      StitcherComponent: TStitcherComponent;
      StitcherResultMask: TStitcherResultMask;
      StitcherWorkScale: TStitcherWorkScale;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVStitchingModule.Initialize(const Handle: TLibHandle);
begin
  CreateStitcher := CVBind(Handle, 'cv_stitching_createStitcher');
  DeleteStitcher := CVBind(Handle, 'cv_stitching_deleteStitcher');
  Stitch := CVBind(Handle, 'cv_stitching_stitch');
  EstimateTransform := CVBind(Handle, 'cv_stitching_estimateTransform');
  SetPanoConfidenceThresh := CVBind(Handle, 'cv_stitching_setPanoConfidenceThresh');
  GetPanoConfidenceThresh := CVBind(Handle, 'cv_stitching_getPanoConfidenceThresh');
  ComposePanorama := CVBind(Handle, 'cv_stitching_composePanorama');
  SetRegistrationResol := CVBind(Handle, 'cv_stitching_setRegistrationResol');
  SetSeamEstimationResol := CVBind(Handle, 'cv_stitching_setSeamEstimationResol');
  SetCompositingResol := CVBind(Handle, 'cv_stitching_setCompositingResol');
  GetWaveCorrection := CVBind(Handle, 'cv_stitching_getWaveCorrection');
  SetWaveCorrection := CVBind(Handle, 'cv_stitching_setWaveCorrection');
  GetWaveCorrectKind := CVBind(Handle, 'cv_stitching_getWaveCorrectKind');
  SetWaveCorrectKind := CVBind(Handle, 'cv_stitching_setWaveCorrectKind');
  GetInterpolationFlags := CVBind(Handle, 'cv_stitching_getInterpolationFlags');
  SetInterpolationFlags := CVBind(Handle, 'cv_stitching_setInterpolationFlags');
  StitcherComponent := CVBind(Handle, 'cv_stitching_stitcherComponent');
  StitcherResultMask := CVBind(Handle, 'cv_stitching_stitcherResultMask');
  StitcherWorkScale := CVBind(Handle, 'cv_stitching_stitcherWorkScale');
end;

end.
