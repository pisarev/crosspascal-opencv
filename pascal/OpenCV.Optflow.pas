{ ************************************************************************** }
{                                                                            }
{ OpenCV.Optflow                                                             }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Optflow;

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
  TCVOptFlowModule = record
  public
    type
      TCreateOptFlow_DualTVL1 = function: Pointer; cdecl;
      TDeleteDualTVL1 = function(Flow: Pointer): LongBool; cdecl;
      TDualTVL1Calc = function(Flow: Pointer; I0, I1, FlowMat: PMat): LongBool; cdecl;
      TDualTVL1GetTau = function(Flow: Pointer): Double; cdecl;
      TDualTVL1SetTau = function(Flow: Pointer; Val: Double): LongBool; cdecl;
      TDualTVL1GetLambda = function(Flow: Pointer): Double; cdecl;
      TDualTVL1SetLambda = function(Flow: Pointer; Val: Double): LongBool; cdecl;
      TDualTVL1GetTheta = function(Flow: Pointer): Double; cdecl;
      TDualTVL1SetTheta = function(Flow: Pointer; Val: Double): LongBool; cdecl;
      TDualTVL1GetGamma = function(Flow: Pointer): Double; cdecl;
      TDualTVL1SetGamma = function(Flow: Pointer; Val: Double): LongBool; cdecl;
      TDualTVL1GetScalesNumber = function(Flow: Pointer): Integer; cdecl;
      TDualTVL1SetScalesNumber = function(Flow: Pointer; Val: Integer): LongBool; cdecl;
      TDualTVL1GetWarpingsNumber = function(Flow: Pointer): Integer; cdecl;
      TDualTVL1SetWarpingsNumber = function(Flow: Pointer; Val: Integer): LongBool; cdecl;
      TDualTVL1GetEpsilon = function(Flow: Pointer): Double; cdecl;
      TDualTVL1SetEpsilon = function(Flow: Pointer; Val: Double): LongBool; cdecl;
      TDualTVL1GetInnerIterations = function(Flow: Pointer): Integer; cdecl;
      TDualTVL1SetInnerIterations = function(Flow: Pointer; Val: Integer): LongBool; cdecl;
      TDualTVL1GetOuterIterations = function(Flow: Pointer): Integer; cdecl;
      TDualTVL1SetOuterIterations = function(Flow: Pointer; Val: Integer): LongBool; cdecl;
      TDualTVL1GetMedianFiltering = function(Flow: Pointer): Integer; cdecl;
      TDualTVL1SetMedianFiltering = function(Flow: Pointer; Val: Integer): LongBool; cdecl;
      TDualTVL1GetUseInitialFlow = function(Flow: Pointer): Integer; cdecl;
      TDualTVL1SetUseInitialFlow = function(Flow: Pointer; Val: LongBool): LongBool; cdecl;
      TCreateOptFlow_DeepFlow = function: Pointer; cdecl;
      TCreateOptFlow_SimpleFlow = function: Pointer; cdecl;
      TCreateOptFlow_PCAFlow = function: Pointer; cdecl;
      TCreateOptFlow_SparseToDense = function: Pointer; cdecl;
      TDeleteOptFlow = function(Flow: Pointer): LongBool; cdecl;
      TCalcOpticalFlowSF = function(From, &To, Flow: PMat;
        Layers, AveragingBlockSize, MaxFlow: Integer): LongBool; cdecl;
      TCalcOpticalFlowSparseToDense = function(From, &To, Flow: PMat; GridStep, K: Integer; Sigma: Single;
        UsePostProc: LongBool; FgsLambda, FgsSigma: Single): LongBool; cdecl;
    var
      CreateOptFlow_DualTVL1: TCreateOptFlow_DualTVL1;
      DeleteDualTVL1: TDeleteDualTVL1;
      DualTVL1Calc: TDualTVL1Calc;
      DualTVL1GetTau: TDualTVL1GetTau;
      DualTVL1SetTau: TDualTVL1SetTau;
      DualTVL1GetLambda: TDualTVL1GetLambda;
      DualTVL1SetLambda: TDualTVL1SetLambda;
      DualTVL1GetTheta: TDualTVL1GetTheta;
      DualTVL1SetTheta: TDualTVL1SetTheta;
      DualTVL1GetGamma: TDualTVL1GetGamma;
      DualTVL1SetGamma: TDualTVL1SetGamma;
      DualTVL1GetScalesNumber: TDualTVL1GetScalesNumber;
      DualTVL1SetScalesNumber: TDualTVL1SetScalesNumber;
      DualTVL1GetWarpingsNumber: TDualTVL1GetWarpingsNumber;
      DualTVL1SetWarpingsNumber: TDualTVL1SetWarpingsNumber;
      DualTVL1GetEpsilon: TDualTVL1GetEpsilon;
      DualTVL1SetEpsilon: TDualTVL1SetEpsilon;
      DualTVL1GetInnerIterations: TDualTVL1GetInnerIterations;
      DualTVL1SetInnerIterations: TDualTVL1SetInnerIterations;
      DualTVL1GetOuterIterations: TDualTVL1GetOuterIterations;
      DualTVL1SetOuterIterations: TDualTVL1SetOuterIterations;
      DualTVL1GetMedianFiltering: TDualTVL1GetMedianFiltering;
      DualTVL1SetMedianFiltering: TDualTVL1SetMedianFiltering;
      DualTVL1GetUseInitialFlow: TDualTVL1GetUseInitialFlow;
      DualTVL1SetUseInitialFlow: TDualTVL1SetUseInitialFlow;
      CreateOptFlow_DeepFlow: TCreateOptFlow_DeepFlow;
      CreateOptFlow_SimpleFlow: TCreateOptFlow_SimpleFlow;
      CreateOptFlow_PCAFlow: TCreateOptFlow_PCAFlow;
      CreateOptFlow_SparseToDense: TCreateOptFlow_SparseToDense;
      DeleteOptFlow: TDeleteOptFlow;
      CalcOpticalFlowSF: TCalcOpticalFlowSF;
      CalcOpticalFlowSparseToDense: TCalcOpticalFlowSparseToDense;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVOptFlowModule.Initialize(const Handle: TLibHandle);
begin
  CreateOptFlow_DualTVL1 := CVBind(Handle, 'cv_optflow_createOptFlow_DualTVL1');
  DeleteDualTVL1 := CVBind(Handle, 'cv_optflow_deleteDualTVL1');
  DualTVL1Calc := CVBind(Handle, 'cv_optflow_dualTVL1Calc');
  DualTVL1GetTau := CVBind(Handle, 'cv_optflow_dualTVL1GetTau');
  DualTVL1SetTau := CVBind(Handle, 'cv_optflow_dualTVL1SetTau');
  DualTVL1GetLambda := CVBind(Handle, 'cv_optflow_dualTVL1GetLambda');
  DualTVL1SetLambda := CVBind(Handle, 'cv_optflow_dualTVL1SetLambda');
  DualTVL1GetTheta := CVBind(Handle, 'cv_optflow_dualTVL1GetTheta');
  DualTVL1SetTheta := CVBind(Handle, 'cv_optflow_dualTVL1SetTheta');
  DualTVL1GetGamma := CVBind(Handle, 'cv_optflow_dualTVL1GetGamma');
  DualTVL1SetGamma := CVBind(Handle, 'cv_optflow_dualTVL1SetGamma');
  DualTVL1GetScalesNumber := CVBind(Handle, 'cv_optflow_dualTVL1GetScalesNumber');
  DualTVL1SetScalesNumber := CVBind(Handle, 'cv_optflow_dualTVL1SetScalesNumber');
  DualTVL1GetWarpingsNumber := CVBind(Handle, 'cv_optflow_dualTVL1GetWarpingsNumber');
  DualTVL1SetWarpingsNumber := CVBind(Handle, 'cv_optflow_dualTVL1SetWarpingsNumber');
  DualTVL1GetEpsilon := CVBind(Handle, 'cv_optflow_dualTVL1GetEpsilon');
  DualTVL1SetEpsilon := CVBind(Handle, 'cv_optflow_dualTVL1SetEpsilon');
  DualTVL1GetInnerIterations := CVBind(Handle, 'cv_optflow_dualTVL1GetInnerIterations');
  DualTVL1SetInnerIterations := CVBind(Handle, 'cv_optflow_dualTVL1SetInnerIterations');
  DualTVL1GetOuterIterations := CVBind(Handle, 'cv_optflow_dualTVL1GetOuterIterations');
  DualTVL1SetOuterIterations := CVBind(Handle, 'cv_optflow_dualTVL1SetOuterIterations');
  DualTVL1GetMedianFiltering := CVBind(Handle, 'cv_optflow_dualTVL1GetMedianFiltering');
  DualTVL1SetMedianFiltering := CVBind(Handle, 'cv_optflow_dualTVL1SetMedianFiltering');
  DualTVL1GetUseInitialFlow := CVBind(Handle, 'cv_optflow_dualTVL1GetUseInitialFlow');
  DualTVL1SetUseInitialFlow := CVBind(Handle, 'cv_optflow_dualTVL1SetUseInitialFlow');
  CreateOptFlow_DeepFlow := CVBind(Handle, 'cv_optflow_createOptFlow_DeepFlow');
  CreateOptFlow_SimpleFlow := CVBind(Handle, 'cv_optflow_createOptFlow_SimpleFlow');
  CreateOptFlow_PCAFlow := CVBind(Handle, 'cv_optflow_createOptFlow_PCAFlow');
  CreateOptFlow_SparseToDense := CVBind(Handle, 'cv_optflow_createOptFlow_SparseToDense');
  DeleteOptFlow := CVBind(Handle, 'cv_optflow_deleteOptFlow');
  CalcOpticalFlowSF := CVBind(Handle, 'cv_optflow_calcOpticalFlowSF');
  CalcOpticalFlowSparseToDense := CVBind(Handle, 'cv_optflow_calcOpticalFlowSparseToDense');
end;

end.
