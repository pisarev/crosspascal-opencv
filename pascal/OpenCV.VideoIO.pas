{ ************************************************************************** }
{                                                                            }
{ OpenCV.VideoIO                                                             }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev                                             }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.VideoIO;

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
  TCVVideoIOModule = record
  public
    type
      TCreateVideoCapture = function(FileName: PAnsiChar; ApiPreference: Integer;
        Handle: PPointer): LongBool; cdecl;
      TDeleteVideoCapture = function(Handle: Pointer): LongBool; cdecl;
      TVideoCaptureIsOpened = function(Handle: Pointer; Opened: PInteger): LongBool; cdecl;
      TVideoCaptureGet = function(Handle: Pointer; PropId: Integer; Value: PDouble): LongBool; cdecl;
      TVideoCaptureSet = function(Handle: Pointer; PropId: Integer; Value: Double): LongBool; cdecl;
      TVideoCaptureGrab = function(Handle: Pointer): LongBool; cdecl;
      TVideoCaptureRead = function(Handle: Pointer; Target: PMat): LongBool; cdecl;
      TVideoCaptureRetrieve = function(Handle: Pointer; Target: PMat; Flag: Integer): LongBool; cdecl;
      TVideoCaptureGetFrame = function(Handle: Pointer; Target: PMat): LongBool; cdecl;
      TCreateVideoCaptureFromDevice = function(DeviceIndex, ApiPreference: Integer;
        Handle: PPointer): LongBool; cdecl;
      TCreateVideoWriter = function(FileName: PAnsiChar; FourCC: Integer; Fps: Double; FrameSize: TOCVSize;
        IsColor: LongBool; Handle: PPointer): LongBool; cdecl;
      TDeleteVideoWriter = function(Handle: Pointer): LongBool; cdecl;
      TVideoWriterIsOpened = function(Handle: Pointer; Opened: PInteger): LongBool; cdecl;
      TVideoWriterWrite = function(Handle: Pointer; Image: TMat): LongBool; cdecl;
      TVideoWriterRelease = function(Handle: Pointer): LongBool; cdecl;
      TVideoWriterGet = function(Handle: Pointer; PropId: Integer): Double; cdecl;
      TVideoWriterSet = function(Handle: Pointer; PropId: Integer; Value: Double): LongBool; cdecl;
      TVideoCaptureRelease = function(Handle: Pointer): LongBool; cdecl;
      TVideoCaptureFourCC = function(C1, C2, C3, C4: AnsiChar): Integer; cdecl;
      TVideoCaptureGetBackendName = function(Handle: Pointer; Name: PAnsiChar;
        MaxLen: Integer): LongBool; cdecl;
      TVideoCaptureGetExceptionMode = function(Handle: Pointer; Mode: PLongBool): LongBool; cdecl;
      TVideoCaptureSetExceptionMode = function(Handle: Pointer; Mode: LongBool): LongBool; cdecl;
      TVideoWriterGetBackendName = function(Handle: Pointer; Name: PAnsiChar;
        MaxLen: Integer): LongBool; cdecl;
      TVideoWriterFourcc = function(C1, C2, C3, C4: AnsiChar): Integer; cdecl;
    var
      CreateVideoCapture: TCreateVideoCapture;
      DeleteVideoCapture: TDeleteVideoCapture;
      VideoCaptureIsOpened: TVideoCaptureIsOpened;
      VideoCaptureGet: TVideoCaptureGet;
      VideoCaptureSet: TVideoCaptureSet;
      VideoCaptureGrab: TVideoCaptureGrab;
      VideoCaptureRead: TVideoCaptureRead;
      VideoCaptureRetrieve: TVideoCaptureRetrieve;
      VideoCaptureGetFrame: TVideoCaptureGetFrame;
      CreateVideoCaptureFromDevice: TCreateVideoCaptureFromDevice;
      CreateVideoWriter: TCreateVideoWriter;
      DeleteVideoWriter: TDeleteVideoWriter;
      VideoWriterIsOpened: TVideoWriterIsOpened;
      VideoWriterWrite: TVideoWriterWrite;
      VideoWriterRelease: TVideoWriterRelease;
      VideoWriterGet: TVideoWriterGet;
      VideoWriterSet: TVideoWriterSet;
      VideoCaptureRelease: TVideoCaptureRelease;
      VideoCaptureFourCC: TVideoCaptureFourCC;
      VideoCaptureGetBackendName: TVideoCaptureGetBackendName;
      VideoCaptureGetExceptionMode: TVideoCaptureGetExceptionMode;
      VideoCaptureSetExceptionMode: TVideoCaptureSetExceptionMode;
      VideoWriterGetBackendName: TVideoWriterGetBackendName;
      VideoWriterFourcc: TVideoWriterFourcc;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVVideoIOModule.Initialize(const Handle: TLibHandle);
begin
  CreateVideoCapture := CVBind(Handle, 'cv_videoio_createVideoCapture');
  DeleteVideoCapture := CVBind(Handle, 'cv_videoio_deleteVideoCapture');
  VideoCaptureIsOpened := CVBind(Handle, 'cv_videoio_videoCaptureIsOpened');
  VideoCaptureGet := CVBind(Handle, 'cv_videoio_videoCaptureGet');
  VideoCaptureSet := CVBind(Handle, 'cv_videoio_videoCaptureSet');
  VideoCaptureGrab := CVBind(Handle, 'cv_videoio_videoCaptureGrab');
  VideoCaptureRead := CVBind(Handle, 'cv_videoio_videoCaptureRead');
  VideoCaptureRetrieve := CVBind(Handle, 'cv_videoio_videoCaptureRetrieve');
  VideoCaptureGetFrame := CVBind(Handle, 'cv_videoio_videoCaptureGetFrame');
  CreateVideoCaptureFromDevice := CVBind(Handle, 'cv_videoio_createVideoCaptureFromDevice');
  CreateVideoWriter := CVBind(Handle, 'cv_videoio_createVideoWriter');
  DeleteVideoWriter := CVBind(Handle, 'cv_videoio_deleteVideoWriter');
  VideoWriterIsOpened := CVBind(Handle, 'cv_videoio_videoWriterIsOpened');
  VideoWriterWrite := CVBind(Handle, 'cv_videoio_videoWriterWrite');
  VideoWriterRelease := CVBind(Handle, 'cv_videoio_videoWriterRelease');
  VideoWriterGet := CVBind(Handle, 'cv_videoio_videoWriterGet');
  VideoWriterSet := CVBind(Handle, 'cv_videoio_videoWriterSet');
  VideoCaptureRelease := CVBind(Handle, 'cv_videoio_videoCaptureRelease');
  VideoCaptureFourCC := CVBind(Handle, 'cv_videoio_videoCaptureFourCC');
  VideoCaptureGetBackendName := CVBind(Handle, 'cv_videoio_videoCaptureGetBackendName');
  VideoCaptureGetExceptionMode := CVBind(Handle, 'cv_videoio_videoCaptureGetExceptionMode');
  VideoCaptureSetExceptionMode := CVBind(Handle, 'cv_videoio_videoCaptureSetExceptionMode');
  VideoWriterGetBackendName := CVBind(Handle, 'cv_videoio_videoWriterGetBackendName');
  VideoWriterFourcc := CVBind(Handle, 'cv_videoio_videoWriterFourcc');
end;

end.
