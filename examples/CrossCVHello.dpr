program CrossCVHello;

{$IFDEF FPC}
{$MODE DELPHIUNICODE}
{$ENDIF}

{$APPTYPE CONSOLE}

uses
  {$IFDEF FPC}SysUtils, Windows,{$ELSE}System.SysUtils, Winapi.Windows,{$ENDIF}
  OpenCV, OpenCVTypes, OpenCVConsts, ExampleDefaults;

procedure RunExample;
var
  Mat: TMat;
  Color, Total: TOCVScalar;
  Nonzero: Integer;
  Buffer: array [0..32767] of Char;
  Chars: DWORD;
  LibraryPath: string;
begin
  LibraryPath := ExtractFilePath(ParamStr(0)) + 'crosscv.dll';
  if not FileExists(LibraryPath) then
    LibraryPath := ExpandFileName(ExtractFilePath(ParamStr(0)) + '..\..\..\bin\crosscv.dll');
  LibraryPath := PreparedPath('opencv', LibraryPath);
  if not CVInitialize(LibraryPath) then
    raise Exception.Create('Cannot load crosscv.dll: ' + CV.Module.Error);
  try
    Chars := GetModuleFileNameW(HMODULE(CV.Module.Handle), @Buffer[0], Length(Buffer));
    if Chars = 0 then
      RaiseLastOSError;
    Writeln('Loaded library: ', string(Buffer));
    Writeln('OpenCV bridge ABI: ', CVLibraryAbiVersion);
    if CVLibraryAbiVersion <> CVSupportedAbiVersion then
      raise Exception.Create('The native library and Pascal bindings use different ABI versions.');
    Mat := CV.Core.MakeMat(4, 3, CV_MAKETYPE(CV_8U, 1));
    if Mat = nil then
      raise Exception.Create('Cannot create the sample image: ' + CV.GetError);
    try
      Color := OCVScalar(7.0, 0.0, 0.0, 0.0);
      if not CV.Core.SetTo(@Mat, Color, nil) then
        raise Exception.Create('Cannot fill the image: ' + CV.GetError);
      if not CV.Core.Sum(Mat, @Total) then
        raise Exception.Create('Cannot calculate the pixel sum: ' + CV.GetError);
      if not CV.Core.CountNonZero(Mat, @Nonzero) then
        raise Exception.Create('Cannot count nonzero pixels: ' + CV.GetError);
      Writeln('Pixel sum: ', Round(Total.V0), ' (expected 84)');
      Writeln('Nonzero pixels: ', Nonzero, ' (expected 12)');
      if (Round(Total.V0) <> 84) or (Nonzero <> 12) then
        raise Exception.Create('The sample image returned an unexpected result.');
    finally
      CV.Core.DeleteMat(@Mat);
    end;
  finally
    if not CVFinalize then
      raise Exception.Create('Cannot release the OpenCV bridge: ' + CV.Module.Error);
  end;
  Writeln('CROSSCV_HELLO_PASS');
end;

begin
  ExitCode := 0;
  try
    RunExample;
  except
    on E: Exception do
    begin
      Writeln('Error: ', E.Message);
      ExitCode := 2;
    end;
  end;
  if not FindCmdLineSwitch('no-pause', ['-'], True) then
  begin
    Writeln;
    Writeln('Press Enter to close this example.');
    Readln;
  end;
end.
