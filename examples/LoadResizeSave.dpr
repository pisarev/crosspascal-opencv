program LoadResizeSave;

{$IFDEF FPC}
{$MODE DELPHIUNICODE}
{$ENDIF}

{$APPTYPE CONSOLE}

uses
  {$IFDEF FPC}Interfaces, SysUtils, Classes, Forms, Dialogs, {$ELSE}
  System.SysUtils, System.Classes, Vcl.Forms, Vcl.Dialogs, {$ENDIF} OpenCV,
  OpenCVTypes, OpenCVConsts;

function ReadImageBytes(const Path: string): TBytes;
var
  Stream: TFileStream;
begin
  Stream := TFileStream.Create(Path, fmOpenRead or fmShareDenyWrite);
  try
    if (Stream.Size < 1) or (Stream.Size > High(Integer)) then
      raise Exception.Create('The selected image has an invalid size.');
    SetLength(Result, Integer(Stream.Size));
    Stream.ReadBuffer(Result[0], Length(Result));
  finally
    Stream.Free;
  end;
end;

procedure ConvertImage(const InputName, OutputName: string);
var
  Source, Resized: TMat;
  InputBytes: TBytes;
  Encoded: Pointer;
  EncodedSize: Integer;
  OutputStream: TFileStream;
  LibraryPath: string;
begin
  Source := nil;
  Resized := nil;
  Encoded := nil;
  LibraryPath := ExtractFilePath(ParamStr(0)) + 'crosscv.dll';
  if not FileExists(LibraryPath) then
    LibraryPath := ExpandFileName(ExtractFilePath(ParamStr(0)) + '..\..\..\bin\crosscv.dll');
  if not CVInitialize(LibraryPath) then
    raise Exception.Create('Cannot load crosscv.dll: ' + CV.Module.Error);
  try
    if CVLibraryAbiVersion <> CVSupportedAbiVersion then
      raise Exception.Create('The native library and Pascal bindings have different ABI versions.');
    InputBytes := ReadImageBytes(InputName);
    if Length(InputBytes) = 0 then
      raise Exception.Create('The selected image file is empty.');
    if not CV.ImgCodecs.ImDecode(@InputBytes[0], Length(InputBytes), IMREAD_COLOR, @Source) then
      raise Exception.Create('Cannot decode the selected image: ' + CV.GetError);
    try
      if not CV.ImgProc.ResizeImage(Source, @Resized, OCVSize(640, 480), 0, 0, INTER_LINEAR) then
        raise Exception.Create('Cannot resize the image: ' + CV.GetError);
      if not CV.ImgCodecs.ImEncode('.png', Resized, @Encoded, @EncodedSize, -1) then
        raise Exception.Create('Cannot encode the PNG image: ' + CV.GetError);
      if (Encoded = nil) or (EncodedSize <= 0) then
        raise Exception.Create('The PNG encoder returned an empty result.');
      OutputStream := TFileStream.Create(OutputName, fmCreate);
      try
        OutputStream.WriteBuffer(Encoded^, EncodedSize);
      finally
        OutputStream.Free;
      end;
    finally
      if Encoded <> nil then
        CV.ImgCodecs.FreeBuf(Encoded);
      if Resized <> nil then
        CV.Core.DeleteMat(@Resized);
      if Source <> nil then
        CV.Core.DeleteMat(@Source);
    end;
  finally
    if not CVFinalize then
      raise Exception.Create('Cannot release the OpenCV bridge: ' + CV.Module.Error);
  end;
  Writeln('Loaded: ', InputName);
  Writeln('Resized to 640 x 480 pixels.');
  Writeln('Saved PNG: ', OutputName);
  Writeln('LOAD_RESIZE_SAVE_PASS');
end;

procedure RunExample;
var
  OpenDialog: TOpenDialog;
  SaveDialog: TSaveDialog;
begin
  OpenDialog := TOpenDialog.Create(nil);
  SaveDialog := TSaveDialog.Create(nil);
  try
    OpenDialog.Title := 'Choose an image to resize';
    OpenDialog.Filter := 'Image files|*.png;*.jpg;*.jpeg;*.bmp;*.tif;*.tiff;*.webp|All files|*.*';
    OpenDialog.Options := [ofFileMustExist, ofPathMustExist, ofEnableSizing];
    if not OpenDialog.Execute then
    begin
      Writeln('Cancelled.');
      Exit;
    end;
    SaveDialog.Title := 'Save the resized PNG image';
    SaveDialog.Filter := 'PNG image|*.png';
    SaveDialog.DefaultExt := 'png';
    SaveDialog.FileName := 'resized-640x480.png';
    SaveDialog.Options := [ofOverwritePrompt, ofPathMustExist, ofEnableSizing];
    if not SaveDialog.Execute then
    begin
      Writeln('Cancelled.');
      Exit;
    end;
    ConvertImage(OpenDialog.FileName, SaveDialog.FileName);
  finally
    SaveDialog.Free;
    OpenDialog.Free;
  end;
end;

begin
  ExitCode := 0;
  Application.Initialize;
  try
    RunExample;
  except
    on E: Exception do
    begin
      Writeln('Error: ', E.Message);
      ExitCode := 2;
    end;
  end;
  Writeln;
  Writeln('Press Enter to close this example.');
  Readln;
end.
