{ ************************************************************************** }
{                                                                            }
{ OpenCV                                                                     }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev                                             }
{                                                                            }
{ ************************************************************************** }

unit OpenCV;

{$B-}
{$IFDEF FPC}
  {$MODE DELPHI}
{$ENDIF}

interface

uses
  {$IFDEF FPC}
  {$IFDEF MSWINDOWS}
  Windows,
  {$ENDIF}
  DynLibs,
  {$ELSE}
  WinApi.Windows,
  {$ENDIF}
  SysUtils, OpenCVTypes, OpenCV.Core, OpenCV.ImgProc, OpenCV.ImgCodecs,
  OpenCV.Photo, OpenCV.Video, OpenCV.VideoIO, OpenCV.ObjDetect, OpenCV.Dnn, OpenCV.Ml,
  OpenCV.Tracking, OpenCV.Features2D, OpenCV.Calib3D, OpenCV.HighGui, OpenCV.XImgProc,
  OpenCV.Bioinspired, OpenCV.Custom, OpenCV.Stitching, OpenCV.Aruco, OpenCV.XFeatures2D,
  OpenCV.Optflow, OpenCV.Face, OpenCV.XPhoto;

type
  TCV = record
  public
    type
      TModule = record
        Handle: TLibHandle;
        LibraryPath: string;
        Error: string;
        Loaded: Boolean;
      end;
    var
      Core: TCVCoreModule;
      ImgProc: TCVImgProcModule;
      ImgCodecs: TCVImgCodecsModule;
      Photo: TCVPhotoModule;
      Video: TCVVideoModule;
      VideoIO: TCVVideoIOModule;
      ObjDetect: TCVObjDetectModule;
      Dnn: TCVDnnModule;
      Ml: TCVMlModule;
      Tracking: TCVTrackingModule;
      Features2D: TCVFeatures2DModule;
      Calib3D: TCVCalib3DModule;
      HighGui: TCVHighGuiModule;
      XImgProc: TCVXImgProcModule;
      Bioinspired: TCVBioinspiredModule;
      Custom: TCVCustomModule;
      Stitching: TCVStitchingModule;
      Aruco: TCVArucoModule;
      XFeatures2D: TCVXFeatures2DModule;
      Optflow: TCVOptFlowModule;
      Face: TCVFaceModule;
      XPhoto: TCVXPhotoModule;
      Module: TModule;
    function GetError: string;
  end;

const
  CVSupportedAbiVersion = 3;
  CVIdentityExport = 'crosscv_runtime_identity_4F2C9A7E';

var
  CV: TCV;

function CVInitialize(const LibraryPath: string): Boolean;

function CVFinalize: Boolean;

function CVRuntimeGeneration: Cardinal;

procedure CVObjectCreated;
procedure CVObjectDestroyed;
function CVLiveObjects: Integer;

const
  CVFaultAccountingUnderflow = 1;
  CVFaultMissingDestroy = 2;
  CVFaultDestroyFailed = 4;

procedure CVLifecycleFault(const Kind: Integer);
function CVLifecycleFaults: Integer;
function CVAccountingFaulted: Boolean;

function CVLibraryAbiVersion: Integer;

implementation

function TCV.GetError: string;
var
  Size: Integer;
  Buffer: array of AnsiChar;
begin
  if not Module.Loaded then
    Exit(Module.Error);
  Size := Core.GetErrorSize;
  if Size <= 1 then
    Exit('');
  SetLength(Buffer, Size);
  FillChar(Buffer[0], Length(Buffer), 0);
  Core.GetErrorText(@Buffer[0], Length(Buffer));
  Result := string(PAnsiChar(@Buffer[0]));
end;

type
  TAbiVersionProc = function: Integer; cdecl;

var
  LibraryAbiVersion: Integer = 0;
  RuntimeGeneration: Cardinal = 0;
  LiveObjects: Integer = 0;
  LifecycleFault: Integer = 0;

function CVLibraryAbiVersion: Integer;
begin
  Result := LibraryAbiVersion;
end;

function CVRuntimeGeneration: Cardinal;
begin
  Result := RuntimeGeneration;
end;

procedure CVObjectCreated;
begin
  InterlockedIncrement(LiveObjects);
end;

procedure CVObjectDestroyed;
begin
  if InterlockedDecrement(LiveObjects) < 0 then
  begin
    InterlockedIncrement(LiveObjects);
    CVLifecycleFault(CVFaultAccountingUnderflow);
  end;
end;

procedure CVLifecycleFault(const Kind: Integer);
var
  Was: Integer;
begin
  repeat
    Was := LifecycleFault;
  until InterlockedCompareExchange(LifecycleFault, Was or Kind, Was) = Was;
end;

function CVLifecycleFaults: Integer;
begin
  Result := LifecycleFault;
end;

function CVLiveObjects: Integer;
begin
  Result := LiveObjects;
end;

function CVAccountingFaulted: Boolean;
begin
  Result := LifecycleFault <> 0;
end;

{$IFDEF MSWINDOWS}

function ModulePathOf(const Handle: TLibHandle; out Path, Failure: string): Boolean;
const
  PathCharsLimit = 32768;
var
  Capacity, Copied: DWORD;
  Buffer: string;
begin
  Path := '';
  Failure := '';
  Capacity := MAX_PATH;
  while True do
  begin
    SetLength(Buffer, Capacity);
    SetLastError(0);
    Copied := GetModuleFileName(HMODULE(Handle), PChar(Buffer), Capacity);
    if Copied = 0 then
    begin
      Failure := 'the module path could not be read (error ' + IntToStr(GetLastError) + ')';
      Exit(False);
    end;
    if (Copied < Capacity) and (GetLastError <> ERROR_INSUFFICIENT_BUFFER) then
    begin
      SetLength(Buffer, Copied);
      Path := Buffer;
      Exit(True);
    end;
    if Capacity >= PathCharsLimit then
    begin
      Failure := 'the module path is longer than ' + IntToStr(PathCharsLimit) + ' characters';
      Exit(False);
    end;
    Capacity := Capacity * 2;
    if Capacity > PathCharsLimit then
      Capacity := PathCharsLimit;
  end;
end;

function SamePathText(const A, B: string): Boolean;
begin
  Result := SameText(ExcludeTrailingPathDelimiter(ExpandFileName(A)),
    ExcludeTrailingPathDelimiter(ExpandFileName(B)));
end;

const
  GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS = $00000004;

function GetModuleHandleExW(Flags: DWORD; ModuleName: Pointer;
  var Module: HMODULE): BOOL; stdcall; external 'kernel32.dll';

function K32EnumProcessModules(Process: THandle; Modules: Pointer; Size: DWORD;
  var Needed: DWORD): BOOL; stdcall; external 'kernel32.dll';

function FindOtherRuntime(const Own: TLibHandle; out OtherPath, Failure: string): Boolean;
var
  Needed, SizeBytes: DWORD;
  Modules: array of HMODULE;
  I, Attempt: Integer;
  Pinned: HMODULE;
  Ignored: string;
begin
  Result := False;
  OtherPath := '';
  Failure := '';
  SizeBytes := 512 * SizeOf(HMODULE);
  Needed := 0;
  for Attempt := 1 to 8 do
  begin
    SetLength(Modules, SizeBytes div SizeOf(HMODULE));
    Needed := 0;
    if not K32EnumProcessModules(GetCurrentProcess, @Modules[0], SizeBytes, Needed) then
    begin
      Failure := Format('the process module list could not be read on attempt %d (error %d)',
        [Attempt, GetLastError]);
      Exit(False);
    end;
    if Needed <= SizeBytes then
      Break;
    if Attempt = 8 then
    begin
      Failure := Format('the process module list kept growing over %d attempts ' +
        '(last size needed %d bytes)',
        [Attempt, Needed]);
      Exit(False);
    end;
    SizeBytes := Needed;
  end;
  for I := 0 to Integer(Needed div SizeOf(HMODULE)) - 1 do
  begin
    if Modules[I] = HMODULE(Own) then
      Continue;
    Pinned := 0;
    if not GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, Pointer(Modules[I]), Pinned) then
    begin
      Failure := 'the process module list went stale while it was being ' +
        'examined (a module was unloaded from another thread)';
      Exit(False);
    end;
    try
      if GetProcAddress(Pinned, CVIdentityExport) <> nil then
      begin
        if not ModulePathOf(TLibHandle(Pinned), OtherPath, Ignored) then
          OtherPath := '<path unavailable>';
        Exit(True);
      end;
    finally
      FreeLibrary(Pinned);
    end;
  end;
end;
{$ENDIF}

procedure UnloadCandidate(const Candidate: TLibHandle);
begin
  if Candidate <> {$IFDEF FPC}DynLibs.NilHandle{$ELSE}0{$ENDIF} then
    FreeLibrary(Candidate);
  FillChar(CV.Core, SizeOf(CV.Core), 0);
  FillChar(CV.ImgProc, SizeOf(CV.ImgProc), 0);
  FillChar(CV.ImgCodecs, SizeOf(CV.ImgCodecs), 0);
  FillChar(CV.Photo, SizeOf(CV.Photo), 0);
  FillChar(CV.Video, SizeOf(CV.Video), 0);
  FillChar(CV.VideoIO, SizeOf(CV.VideoIO), 0);
  FillChar(CV.ObjDetect, SizeOf(CV.ObjDetect), 0);
  FillChar(CV.Dnn, SizeOf(CV.Dnn), 0);
  FillChar(CV.Ml, SizeOf(CV.Ml), 0);
  FillChar(CV.Tracking, SizeOf(CV.Tracking), 0);
  FillChar(CV.Features2D, SizeOf(CV.Features2D), 0);
  FillChar(CV.Calib3D, SizeOf(CV.Calib3D), 0);
  FillChar(CV.HighGui, SizeOf(CV.HighGui), 0);
  FillChar(CV.XImgProc, SizeOf(CV.XImgProc), 0);
  FillChar(CV.Bioinspired, SizeOf(CV.Bioinspired), 0);
  FillChar(CV.Custom, SizeOf(CV.Custom), 0);
  FillChar(CV.Stitching, SizeOf(CV.Stitching), 0);
  FillChar(CV.Aruco, SizeOf(CV.Aruco), 0);
  FillChar(CV.XFeatures2D, SizeOf(CV.XFeatures2D), 0);
  FillChar(CV.Optflow, SizeOf(CV.Optflow), 0);
  FillChar(CV.Face, SizeOf(CV.Face), 0);
  FillChar(CV.XPhoto, SizeOf(CV.XPhoto), 0);
  CV.Module.Error := '';
  CV.Module.LibraryPath := '';
  FillChar(CV.Module, SizeOf(CV.Module), 0);
  LibraryAbiVersion := 0;
  CVBindReset;
end;

procedure UnloadRuntime;
begin
  UnloadCandidate(CV.Module.Handle);
  CV.Module.Handle := {$IFDEF FPC}DynLibs.NilHandle{$ELSE}0{$ENDIF};
  CV.Module.Loaded := False;
end;

function CVInitialize(const LibraryPath: string): Boolean;
var
  Handle: TLibHandle;
  AbiVersion: TAbiVersionProc;
  Complaint: string;
  {$IFDEF MSWINDOWS}
  OtherPath, ActivePath, Failure: string;
  {$ENDIF}
begin
  CV.Module.Error := '';
  if CV.Module.Loaded then
  begin
    {$IFDEF MSWINDOWS}
    if not ModulePathOf(CV.Module.Handle, ActivePath, Failure) then
    begin
      CV.Module.Error := 'Refusing to reuse the active runtime: ' + Failure +
        '. Without its path a repeated call for the same file cannot be told ' +
        'apart from a request to switch libraries: ' + LibraryPath;
      Exit(False);
    end;
    if SamePathText(ActivePath, LibraryPath) then
      Exit(True);
    {$ELSE}
    if CV.Module.LibraryPath = LibraryPath then
      Exit(True);
    {$ENDIF}
    CV.Module.Error := 'Another library is already active in this process, loaded from ' +
      CV.Module.LibraryPath + '. Objects created by it stay ' +
      'valid only while it is loaded, so switching is refused: call ' +
      'CVFinalize first, once nothing of it is alive. Requested: ' + LibraryPath;
    Exit(False);
  end;
  Handle := LoadLibrary(PChar(LibraryPath));
  if Handle = {$IFDEF FPC}DynLibs.NilHandle{$ELSE}0{$ENDIF} then
  begin
    {$IFDEF FPC}
    Complaint := GetLoadErrorStr;
    {$ELSE}
    Complaint := SysErrorMessage(GetLastError);
    {$ENDIF}
    CV.Module.Error := 'Failed to load library: ' + LibraryPath;
    if Complaint <> '' then
      CV.Module.Error := CV.Module.Error + ' (' + Trim(Complaint) + ')';
    Exit(False);
  end;
  if GetProcAddress(Handle, CVIdentityExport) = nil then
  begin
    FreeLibrary(Handle);
    CV.Module.Error := 'The library exports no ' + CVIdentityExport + ', so it ' +
      'is not a crosscv runtime this binding may own: another binding would ' +
      'not recognize it and would load a second copy alongside: ' + LibraryPath;
    Exit(False);
  end;
  {$IFDEF MSWINDOWS}
  if FindOtherRuntime(Handle, OtherPath, Failure) then
  begin
    Complaint := 'Another crosscv runtime is already loaded in this process, ' +
      'from ' + OtherPath +
      '. Two runtimes mean two OpenCV heaps, and an ' +
      'object made by one and released by the other corrupts memory. Reuse ' +
      'the already loaded library instead of ' + LibraryPath;
    FreeLibrary(Handle);
    CV.Module.Error := Complaint;
    Exit(False);
  end;
  if Failure <> '' then
  begin
    FreeLibrary(Handle);
    CV.Module.Error := 'Refusing to initialize: ' + Failure + '. Without that ' +
      'list a second copy of the runtime cannot be ruled out: ' + LibraryPath;
    Exit(False);
  end;
  {$ENDIF}
  AbiVersion := TAbiVersionProc(GetProcAddress(Handle, 'crosscv_get_abi_version'));
  if not Assigned(AbiVersion) then
  begin
    FreeLibrary(Handle);
    CV.Module.Error := 'The library exports no crosscv_get_abi_version: it is ' +
      'older than the contract version ' + IntToStr(CVSupportedAbiVersion) +
      ' this binding is written against: ' + LibraryPath;
    CV.Module.Loaded := False;
    Exit(False);
  end;
  LibraryAbiVersion := AbiVersion;
  if LibraryAbiVersion <> CVSupportedAbiVersion then
  begin
    FreeLibrary(Handle);
    CV.Module.Error := Format('Contract version mismatch: the library reports %d, ' +
      'this binding is written against %d: %s',
      [LibraryAbiVersion, CVSupportedAbiVersion, LibraryPath]);
    LibraryAbiVersion := 0;
    CV.Module.Loaded := False;
    Exit(False);
  end;
  CVBindReset;
  CV.Core.Initialize(Handle);
  CV.ImgProc.Initialize(Handle);
  CV.ImgCodecs.Initialize(Handle);
  CV.Photo.Initialize(Handle);
  CV.Video.Initialize(Handle);
  CV.VideoIO.Initialize(Handle);
  CV.ObjDetect.Initialize(Handle);
  CV.Dnn.Initialize(Handle);
  CV.Ml.Initialize(Handle);
  CV.Tracking.Initialize(Handle);
  CV.Features2D.Initialize(Handle);
  CV.Calib3D.Initialize(Handle);
  CV.HighGui.Initialize(Handle);
  CV.XImgProc.Initialize(Handle);
  CV.Bioinspired.Initialize(Handle);
  CV.Custom.Initialize(Handle);
  CV.Stitching.Initialize(Handle);
  CV.Aruco.Initialize(Handle);
  CV.XFeatures2D.Initialize(Handle);
  CV.Optflow.Initialize(Handle);
  CV.Face.Initialize(Handle);
  CV.XPhoto.Initialize(Handle);
  if CVBindMissingCount > 0 then
  begin
    Complaint := Format('The library reports contract version %d but does not ' +
      'export %d of the functions this binding needs (%s): %s',
      [LibraryAbiVersion, CVBindMissingCount, CVBindMissingNames(5), LibraryPath]);
    UnloadCandidate(Handle);
    CV.Module.Error := Complaint;
    Exit(False);
  end;
  CVBindReset;
  Inc(RuntimeGeneration);
  CV.Module.Handle := Handle;
  CV.Module.LibraryPath := LibraryPath;
  CV.Module.Loaded := True;
  Result := True;
end;

function CVFinalize: Boolean;
begin
  CV.Module.Error := '';
  if LifecycleFault <> 0 then
  begin
    CV.Module.Error := '';
    if (LifecycleFault and CVFaultAccountingUnderflow) <> 0 then
      CV.Module.Error := 'Refusing to unload: live-object accounting underflow ' +
        'was detected. The counter can no longer prove that no ' +
        'runtime-dependent objects are alive. ';
    if (LifecycleFault and CVFaultDestroyFailed) <> 0 then
      CV.Module.Error := CV.Module.Error + 'Refusing to unload: releasing an ' +
        'owning object did not confirm success, so its native lifetime can no ' +
        'longer be proven. ';
    if (LifecycleFault and CVFaultMissingDestroy) <> 0 then
      CV.Module.Error := CV.Module.Error + 'Refusing to unload: an owning ' +
        'object could not be released because its destroy entry was missing, ' +
        'so native memory was leaked while the runtime was still loaded.';
    Exit(False);
  end;
  if LiveObjects > 0 then
  begin
    CV.Module.Error := Format(
      'Refusing to unload the runtime: %d object(s) ' +
      'created by it are still alive. Their destructors would call into an ' +
      'unloaded library. Release them first; note that the compiler may hold ' +
      'an interface reference of its own until the enclosing scope ends.',
      [LiveObjects]
    );
    Exit(False);
  end;
  UnloadRuntime;
  Result := True;
end;

initialization
  FillChar(CV, SizeOf(TCV), 0);

end.
