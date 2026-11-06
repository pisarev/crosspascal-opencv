{ ************************************************************************** }
{                                                                            }
{ OpenCV.ImgCodecs                                                           }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.ImgCodecs;

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
  TCVImgCodecsModule = record
  public
    type
      TOpenMat = function(FileName: PAnsiChar; Flags: Integer; Target: PMat): LongBool; cdecl;
      TSaveMat = function(FileName: PAnsiChar; Image: TMat): LongBool; cdecl;
      TImDecode = function(Data: Pointer; DataSize, Flags: Integer; Target: PMat): LongBool; cdecl;
      TImEncode = function(Ext: PAnsiChar; Image: TMat; Data: PPointer; DataSize: PInteger;
        Quality: Integer): LongBool; cdecl;
      TFreeBuf = function(Data: Pointer): LongBool; cdecl;
      TImReadMulti = function(FileName: PAnsiChar; Flags: Integer; Targets: PMat;
        Count: PInteger): LongBool; cdecl;
      TImCount = function(FileName: PAnsiChar; Flags: Integer; Count: PInteger): LongBool; cdecl;
      THaveImageReader = function(FileName: PAnsiChar): LongBool; cdecl;
      THaveImageWriter = function(FileName: PAnsiChar): LongBool; cdecl;
    var
      OpenMat: TOpenMat;
      SaveMat: TSaveMat;
      ImDecode: TImDecode;
      ImEncode: TImEncode;
      FreeBuf: TFreeBuf;
      ImReadMulti: TImReadMulti;
      ImCount: TImCount;
      HaveImageReader: THaveImageReader;
      HaveImageWriter: THaveImageWriter;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVImgCodecsModule.Initialize(const Handle: TLibHandle);
begin
  OpenMat := CVBind(Handle, 'cv_imgcodecs_openMat');
  SaveMat := CVBind(Handle, 'cv_imgcodecs_saveMat');
  ImDecode := CVBind(Handle, 'cv_imgcodecs_imDecode');
  ImEncode := CVBind(Handle, 'cv_imgcodecs_imEncode');
  FreeBuf := CVBind(Handle, 'cv_imgcodecs_freeBuf');
  ImReadMulti := CVBind(Handle, 'cv_imgcodecs_imReadMulti');
  ImCount := CVBind(Handle, 'cv_imgcodecs_imCount');
  HaveImageReader := CVBind(Handle, 'cv_imgcodecs_haveImageReader');
  HaveImageWriter := CVBind(Handle, 'cv_imgcodecs_haveImageWriter');
end;

end.
