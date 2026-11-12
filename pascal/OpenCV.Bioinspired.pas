{ ************************************************************************** }
{                                                                            }
{ OpenCV.Bioinspired                                                         }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev                                             }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Bioinspired;

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
  TCVBioinspiredModule = record
  public
    type
      TCreateRetina = function(InputSize: TOCVSize; ColorMode: LongBool; ColorSamplingMethod: Integer;
        UseRetinaLogSampling: LongBool; ReductionFactor, SamplingStrength: Single;
        Handle: PPointer): LongBool; cdecl;
      TDeleteRetina = function(Handle: Pointer): LongBool; cdecl;
      TRunRetina = function(Handle: Pointer; Image: TMat): LongBool; cdecl;
      TGetParvoOutput = function(Handle: Pointer; Target: PMat): LongBool; cdecl;
      TGetMagnoOutput = function(Handle: Pointer; Target: PMat): LongBool; cdecl;
    var
      CreateRetina: TCreateRetina;
      DeleteRetina: TDeleteRetina;
      RunRetina: TRunRetina;
      GetParvoOutput: TGetParvoOutput;
      GetMagnoOutput: TGetMagnoOutput;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVBioinspiredModule.Initialize(const Handle: TLibHandle);
begin
  CreateRetina := CVBind(Handle, 'cv_bioinspired_createRetina');
  DeleteRetina := CVBind(Handle, 'cv_bioinspired_deleteRetina');
  RunRetina := CVBind(Handle, 'cv_bioinspired_runRetina');
  GetParvoOutput := CVBind(Handle, 'cv_bioinspired_getParvoOutput');
  GetMagnoOutput := CVBind(Handle, 'cv_bioinspired_getMagnoOutput');
end;

end.
