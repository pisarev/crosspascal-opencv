{ ************************************************************************** }
{                                                                            }
{ OpenCV.HighGui                                                             }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev (ypisareff@outlook.com)               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.HighGui;

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
  TCVHighGuiModule = record
  public
    type
      TTrackbarCallback = procedure(Pos: Integer; UserData: Pointer); cdecl;
      TNamedWindow = function(WinName: PAnsiChar; Flags: Integer): LongBool; cdecl;
      TDestroyWindow = function(WinName: PAnsiChar): LongBool; cdecl;
      TDestroyAllWindows = function: LongBool; cdecl;
      TImShow = function(WinName: PAnsiChar; Image: TMat): LongBool; cdecl;
      TWaitKey = function(Delay: Integer; Key: PInteger): LongBool; cdecl;
      TWaitKeyEx = function(Delay: Integer; Key: PInteger): LongBool; cdecl;
      TCreateTrackbar = function(TrackbarName, WinName: PAnsiChar; Value: PInteger; Count: Integer;
        OnChange: TTrackbarCallback; UserData: Pointer): LongBool; cdecl;
      TGetTrackbarPos = function(TrackbarName, WinName: PAnsiChar; Pos: PInteger): LongBool; cdecl;
      TMouseCallback = procedure(Event, X, Y, Flags: Integer; UserData: Pointer); cdecl;
      TMoveWindow = function(WinName: PAnsiChar; X, Y: Integer): LongBool; cdecl;
      TResizeWindow = function(WinName: PAnsiChar; Width, Height: Integer): LongBool; cdecl;
      TSetWindowProperty = function(WinName: PAnsiChar; PropId: Integer; PropValue: Double): LongBool; cdecl;
      TGetWindowProperty = function(WinName: PAnsiChar; PropId: Integer): Double; cdecl;
      TSetWindowTitle = function(WinName: PAnsiChar; Title: PAnsiChar): LongBool; cdecl;
      TPollKey = function: Integer; cdecl;
      TSelectROI = function(WinName: PAnsiChar; Image: TMat; Result: POCVRect;
        ShowCrosshair, FromCenter: LongBool): LongBool; cdecl;
      TSetMouseCallback = function(WinName: PAnsiChar; OnMouse: TMouseCallback;
        UserData: Pointer): LongBool; cdecl;
      TGetWindowImageRect = function(WinName: PAnsiChar; Result: POCVRect): LongBool; cdecl;
      TSetTrackbarPos = function(TrackbarName, WinName: PAnsiChar; Pos: Integer): LongBool; cdecl;
      TSetTrackbarMin = function(TrackbarName, WinName: PAnsiChar; MinVal: Integer): LongBool; cdecl;
      TSetTrackbarMax = function(TrackbarName, WinName: PAnsiChar; MaxVal: Integer): LongBool; cdecl;
      TSelectROIs = function(WinName: PAnsiChar; Image: TMat; ROIs: POCVRect; Count: PInteger;
        MaxCount: Integer; ShowCrosshair, FromCenter: LongBool): LongBool; cdecl;
    var
      NamedWindow: TNamedWindow;
      DestroyWindow: TDestroyWindow;
      DestroyAllWindows: TDestroyAllWindows;
      ImShow: TImShow;
      WaitKey: TWaitKey;
      WaitKeyEx: TWaitKeyEx;
      CreateTrackbar: TCreateTrackbar;
      GetTrackbarPos: TGetTrackbarPos;
      MoveWindow: TMoveWindow;
      ResizeWindow: TResizeWindow;
      SetWindowProperty: TSetWindowProperty;
      GetWindowProperty: TGetWindowProperty;
      SetWindowTitle: TSetWindowTitle;
      PollKey: TPollKey;
      SelectROI: TSelectROI;
      SetMouseCallback: TSetMouseCallback;
      GetWindowImageRect: TGetWindowImageRect;
      SetTrackbarPos: TSetTrackbarPos;
      SetTrackbarMin: TSetTrackbarMin;
      SetTrackbarMax: TSetTrackbarMax;
      SelectROIs: TSelectROIs;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVHighGuiModule.Initialize(const Handle: TLibHandle);
begin
  NamedWindow := CVBind(Handle, 'cv_highgui_namedWindow');
  DestroyWindow := CVBind(Handle, 'cv_highgui_destroyWindow');
  DestroyAllWindows := CVBind(Handle, 'cv_highgui_destroyAllWindows');
  ImShow := CVBind(Handle, 'cv_highgui_imShow');
  WaitKey := CVBind(Handle, 'cv_highgui_waitKey');
  WaitKeyEx := CVBind(Handle, 'cv_highgui_waitKeyEx');
  CreateTrackbar := CVBind(Handle, 'cv_highgui_createTrackbar');
  GetTrackbarPos := CVBind(Handle, 'cv_highgui_getTrackbarPos');
  MoveWindow := CVBind(Handle, 'cv_highgui_moveWindow');
  ResizeWindow := CVBind(Handle, 'cv_highgui_resizeWindow');
  SetWindowProperty := CVBind(Handle, 'cv_highgui_setWindowProperty');
  GetWindowProperty := CVBind(Handle, 'cv_highgui_getWindowProperty');
  SetWindowTitle := CVBind(Handle, 'cv_highgui_setWindowTitle');
  PollKey := CVBind(Handle, 'cv_highgui_pollKey');
  SelectROI := CVBind(Handle, 'cv_highgui_selectROI');
  SetMouseCallback := CVBind(Handle, 'cv_highgui_setMouseCallback');
  GetWindowImageRect := CVBind(Handle, 'cv_highgui_getWindowImageRect');
  SetTrackbarPos := CVBind(Handle, 'cv_highgui_setTrackbarPos');
  SetTrackbarMin := CVBind(Handle, 'cv_highgui_setTrackbarMin');
  SetTrackbarMax := CVBind(Handle, 'cv_highgui_setTrackbarMax');
  SelectROIs := CVBind(Handle, 'cv_highgui_selectROIs');
end;

end.
