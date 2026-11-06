{ ************************************************************************** }
{                                                                            }
{ OpenCV.Tracking                                                            }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Tracking;

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
  TCVTrackingModule = record
  public
    type
      TCreateTracker = function(Handle: PPointer): LongBool; cdecl;
      TDeleteTracker = function(Handle: Pointer): LongBool; cdecl;
      TTrackerInit = function(Handle: Pointer; Image: TMat; BoundingBox: TOCVRect): LongBool; cdecl;
      TTrackerUpdate = function(Handle: Pointer; Image: TMat; BoundingBox: POCVRect): LongBool; cdecl;
    var
      CreateBoostingTracker: TCreateTracker;
      CreateMOSSETracker: TCreateTracker;
      CreateMILTracker: TCreateTracker;
      CreateKCFTracker: TCreateTracker;
      CreateTLDTracker: TCreateTracker;
      CreateMedianFlowTracker: TCreateTracker;
      CreateGOTURNTracker: TCreateTracker;
      CreateCSRTTracker: TCreateTracker;
      DeleteTracker: TDeleteTracker;
      TrackerInit: TTrackerInit;
      TrackerUpdate: TTrackerUpdate;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVTrackingModule.Initialize(const Handle: TLibHandle);
begin
  CreateBoostingTracker := CVBind(Handle, 'cv_tracking_createBoostingTracker');
  CreateMOSSETracker := CVBind(Handle, 'cv_tracking_createMOSSETracker');
  CreateMILTracker := CVBind(Handle, 'cv_tracking_createMILTracker');
  CreateKCFTracker := CVBind(Handle, 'cv_tracking_createKCFTracker');
  CreateTLDTracker := CVBind(Handle, 'cv_tracking_createTLDTracker');
  CreateMedianFlowTracker := CVBind(Handle, 'cv_tracking_createMedianFlowTracker');
  CreateGOTURNTracker := CVBind(Handle, 'cv_tracking_createGOTURNTracker');
  CreateCSRTTracker := CVBind(Handle, 'cv_tracking_createCSRTTracker');
  DeleteTracker := CVBind(Handle, 'cv_tracking_deleteTracker');
  TrackerInit := CVBind(Handle, 'cv_tracking_trackerInit');
  TrackerUpdate := CVBind(Handle, 'cv_tracking_trackerUpdate');
end;

end.
