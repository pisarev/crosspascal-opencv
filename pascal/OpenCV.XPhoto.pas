{ ************************************************************************** }
{                                                                            }
{ OpenCV.XPhoto                                                              }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.XPhoto;

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
  TCVXPhotoModule = record
  public
    type
      TCreateSimpleWB = function: Pointer; cdecl;
      TDeleteSimpleWB = function(WB: Pointer): LongBool; cdecl;
      TSimpleWBBalanceWhite = function(WB: Pointer; Src, Dst: PMat): LongBool; cdecl;
      TSimpleWBGetInputMin = function(WB: Pointer): Single; cdecl;
      TSimpleWBSetInputMin = function(WB: Pointer; Val: Single): LongBool; cdecl;
      TSimpleWBGetInputMax = function(WB: Pointer): Single; cdecl;
      TSimpleWBSetInputMax = function(WB: Pointer; Val: Single): LongBool; cdecl;
      TSimpleWBGetOutputMin = function(WB: Pointer): Single; cdecl;
      TSimpleWBSetOutputMin = function(WB: Pointer; Val: Single): LongBool; cdecl;
      TSimpleWBGetOutputMax = function(WB: Pointer): Single; cdecl;
      TSimpleWBSetOutputMax = function(WB: Pointer; Val: Single): LongBool; cdecl;
      TCreateGrayworldWB = function: Pointer; cdecl;
      TDeleteGrayworldWB = function(WB: Pointer): LongBool; cdecl;
      TGrayworldWBBalanceWhite = function(WB: Pointer; Src, Dst: PMat): LongBool; cdecl;
      TGrayworldWBGetSaturationThreshold = function(WB: Pointer): Single; cdecl;
      TGrayworldWBSetSaturationThreshold = function(WB: Pointer; Val: Single): LongBool; cdecl;
      TCreateLearningBasedWB = function(PathToModel: PAnsiChar): Pointer; cdecl;
      TDeleteLearningBasedWB = function(WB: Pointer): LongBool; cdecl;
      TLearningBasedWBBalanceWhite = function(WB: Pointer; Src, Dst: PMat): LongBool; cdecl;
      TBm3dDenoising = function(Src, Dst: PMat; H: Single;
        TemplateWindowSize, SearchWindowSize, BlockMatchingStep1, BlockMatchingStep2, GroupSize, SlidingStep: Integer;
        Beta: Single; NormType, Step, TransformType: Integer): LongBool; cdecl;
      TDctDenoising = function(Src, Dst: PMat; Sigma: Double; PSize: Integer): LongBool; cdecl;
      TApplyChannelGains = function(Src, Dst: PMat; GainB, GainG, GainR: Single): LongBool; cdecl;
      TOilPainting = function(Src, Dst: PMat; Size, DynRatio, Code: Integer): LongBool; cdecl;
      TInpaint = function(Src, Mask, Dst: PMat; AlgorithmType: Integer): LongBool; cdecl;
    var
      CreateSimpleWB: TCreateSimpleWB;
      DeleteSimpleWB: TDeleteSimpleWB;
      SimpleWBBalanceWhite: TSimpleWBBalanceWhite;
      SimpleWBGetInputMin: TSimpleWBGetInputMin;
      SimpleWBSetInputMin: TSimpleWBSetInputMin;
      SimpleWBGetInputMax: TSimpleWBGetInputMax;
      SimpleWBSetInputMax: TSimpleWBSetInputMax;
      SimpleWBGetOutputMin: TSimpleWBGetOutputMin;
      SimpleWBSetOutputMin: TSimpleWBSetOutputMin;
      SimpleWBGetOutputMax: TSimpleWBGetOutputMax;
      SimpleWBSetOutputMax: TSimpleWBSetOutputMax;
      CreateGrayworldWB: TCreateGrayworldWB;
      DeleteGrayworldWB: TDeleteGrayworldWB;
      GrayworldWBBalanceWhite: TGrayworldWBBalanceWhite;
      GrayworldWBGetSaturationThreshold: TGrayworldWBGetSaturationThreshold;
      GrayworldWBSetSaturationThreshold: TGrayworldWBSetSaturationThreshold;
      CreateLearningBasedWB: TCreateLearningBasedWB;
      DeleteLearningBasedWB: TDeleteLearningBasedWB;
      LearningBasedWBBalanceWhite: TLearningBasedWBBalanceWhite;
      Bm3dDenoising: TBm3dDenoising;
      DctDenoising: TDctDenoising;
      ApplyChannelGains: TApplyChannelGains;
      OilPainting: TOilPainting;
      Inpaint: TInpaint;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVXPhotoModule.Initialize(const Handle: TLibHandle);
begin
  CreateSimpleWB := CVBind(Handle, 'cv_xphoto_createSimpleWB');
  DeleteSimpleWB := CVBind(Handle, 'cv_xphoto_deleteSimpleWB');
  SimpleWBBalanceWhite := CVBind(Handle, 'cv_xphoto_simpleWBBalanceWhite');
  SimpleWBGetInputMin := CVBind(Handle, 'cv_xphoto_simpleWBGetInputMin');
  SimpleWBSetInputMin := CVBind(Handle, 'cv_xphoto_simpleWBSetInputMin');
  SimpleWBGetInputMax := CVBind(Handle, 'cv_xphoto_simpleWBGetInputMax');
  SimpleWBSetInputMax := CVBind(Handle, 'cv_xphoto_simpleWBSetInputMax');
  SimpleWBGetOutputMin := CVBind(Handle, 'cv_xphoto_simpleWBGetOutputMin');
  SimpleWBSetOutputMin := CVBind(Handle, 'cv_xphoto_simpleWBSetOutputMin');
  SimpleWBGetOutputMax := CVBind(Handle, 'cv_xphoto_simpleWBGetOutputMax');
  SimpleWBSetOutputMax := CVBind(Handle, 'cv_xphoto_simpleWBSetOutputMax');
  CreateGrayworldWB := CVBind(Handle, 'cv_xphoto_createGrayworldWB');
  DeleteGrayworldWB := CVBind(Handle, 'cv_xphoto_deleteGrayworldWB');
  GrayworldWBBalanceWhite := CVBind(Handle, 'cv_xphoto_grayworldWBBalanceWhite');
  GrayworldWBGetSaturationThreshold := CVBind(Handle, 'cv_xphoto_grayworldWBGetSaturationThreshold');
  GrayworldWBSetSaturationThreshold := CVBind(Handle, 'cv_xphoto_grayworldWBSetSaturationThreshold');
  CreateLearningBasedWB := CVBind(Handle, 'cv_xphoto_createLearningBasedWB');
  DeleteLearningBasedWB := CVBind(Handle, 'cv_xphoto_deleteLearningBasedWB');
  LearningBasedWBBalanceWhite := CVBind(Handle, 'cv_xphoto_learningBasedWBBalanceWhite');
  Bm3dDenoising := CVBind(Handle, 'cv_xphoto_bm3dDenoising');
  DctDenoising := CVBind(Handle, 'cv_xphoto_dctDenoising');
  ApplyChannelGains := CVBind(Handle, 'cv_xphoto_applyChannelGains');
  OilPainting := CVBind(Handle, 'cv_xphoto_oilPainting');
  Inpaint := CVBind(Handle, 'cv_xphoto_inpaint');
end;

end.
