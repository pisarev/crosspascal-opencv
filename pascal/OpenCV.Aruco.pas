{ ************************************************************************** }
{                                                                            }
{ OpenCV.Aruco                                                               }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev (ypisareff@outlook.com)                     }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Aruco;

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
  TCVArucoModule = record
  public
    type
      TGetPredefinedDictionary = function(Dict: Integer): Pointer; cdecl;
      TExtendDictionary = function(NMarkers, MarkerSize: Integer; BaseDictionary: Pointer;
        RandomSeed: Integer): Pointer; cdecl;
      TDeleteDictionary = function(Dictionary: Pointer): LongBool; cdecl;
      TGenerateImageMarker = function(Dictionary: Pointer; Id, SidePixels: Integer; Img: PMat;
        BorderBits: Integer): LongBool; cdecl;
      TCreateArucoDetector = function(Dictionary: Pointer; Parameters: Pointer): Pointer; cdecl;
      TDeleteArucoDetector = function(Detector: Pointer): LongBool; cdecl;
      TDetectMarkers = function(Detector: Pointer; Image: PMat; Corners: PMat; CornerCount: PInteger;
        Ids: PMat; RejectedImgPoints: PMat; RejectedCount: PInteger): LongBool; cdecl;
      TDrawDetectedMarkers = function(Image: PMat; Corners: PMat; CornerCount: Integer; Ids: PMat;
        BorderColor: TOCVScalar): LongBool; cdecl;
      TDrawDetectedCornersCharuco = function(Image: PMat; CharucoCorners: PMat; CharucoIds: PMat;
        CornerColor: TOCVScalar): LongBool; cdecl;
      TDrawDetectedDiamonds = function(Image: PMat; DiamondCorners: PMat; Count: Integer; DiamondIds: PMat;
        BorderColor: TOCVScalar): LongBool; cdecl;
      TCreateGridBoard = function(MarkersX, MarkersY: Integer; MarkerLength, MarkerSeparation: Single;
        Dictionary: Pointer; Ids: PMat): Pointer; cdecl;
      TCreateCharucoBoard = function(SquaresX, SquaresY: Integer; SquareLength, MarkerLength: Single;
        Dictionary: Pointer): Pointer; cdecl;
      TDeleteBoard = function(Board: Pointer): LongBool; cdecl;
      TDrawPlanarBoard = function(Board: Pointer; OutW, OutH: Integer; Img: PMat;
        MarginSize, BorderBits: Integer): LongBool; cdecl;
      TCreateCharucoDetector = function(Board: Pointer; DetectorParams: Pointer): Pointer; cdecl;
      TDeleteCharucoDetector = function(Detector: Pointer): LongBool; cdecl;
      TDetectCharucoDiamond = function(Image: PMat; MarkerCorners: PMat; MarkerCount: Integer;
        MarkerIds: PMat; SquareMarkerLengthRate: Single; DiamondCorners: PMat; DiamondCount: PInteger;
        DiamondIds: PMat; CameraMatrix: PMat; DistCoeffs: PMat): LongBool; cdecl;
      TEstimatePoseSingleMarkers = function(Corners: PMat; CornerCount: Integer; MarkerLength: Single;
        CameraMatrix: PMat; DistCoeffs: PMat; Rvecs: PMat; Tvecs: PMat): LongBool; cdecl;
      TEstimatePoseBoard = function(Corners: PMat; CornerCount: Integer; Ids: PMat; Board: Pointer;
        CameraMatrix: PMat; DistCoeffs: PMat; Rvec: PMat; Tvec: PMat;
        UseExtrinsicGuess: LongBool): LongBool; cdecl;
      TEstimatePoseCharucoBoard = function(CharucoCorners: PMat; CharucoIds: PMat; Board: Pointer;
        CameraMatrix: PMat; DistCoeffs: PMat; Rvec: PMat; Tvec: PMat;
        UseExtrinsicGuess: LongBool): LongBool; cdecl;
      TCalibrateCameraAruco = function(Corners: PMat; Ids: PMat; Counter: PMat; Board: Pointer;
        ImageW, ImageH: Integer; CameraMatrix: PMat; DistCoeffs: PMat; Rvecs: PMat; Tvecs: PMat;
        Flags: Integer): Double; cdecl;
      TCalibrateCameraCharuco = function(CharucoCorners: PMat; CharucoIds: PMat; ImageCount: Integer;
        Board: Pointer; ImageW, ImageH: Integer; CameraMatrix: PMat; DistCoeffs: PMat; Rvecs: PMat;
        Tvecs: PMat; Flags: Integer): Double; cdecl;
      TCreateDetectorParameters = function: Pointer; cdecl;
      TDeleteDetectorParameters = function(Params: Pointer): LongBool; cdecl;
      TSetDetectorParametersAdaptiveThreshWinSizeMin = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersAdaptiveThreshWinSizeMax = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersAdaptiveThreshWinSizeStep = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersAdaptiveThreshConstant = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersMinMarkerPerimeterRate = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersMaxMarkerPerimeterRate = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersPolygonalApproxAccuracyRate = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersMinCornerDistanceRate = function(Params: Pointer; Value: Double): LongBool; cdecl;
      TSetDetectorParametersMinDistanceToBorder = function(Params: Pointer; Value: Integer): LongBool; cdecl;
      TSetDetectorParametersMinMarkerDistanceRate = function(Params: Pointer; Value: Double): LongBool; cdecl;
      TSetDetectorParametersCornerRefinementMethod = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersCornerRefinementWinSize = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersCornerRefinementMaxIterations = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersCornerRefinementMinAccuracy = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersMarkerBorderBits = function(Params: Pointer; Value: Integer): LongBool; cdecl;
      TSetDetectorParametersPerspectiveRemovePixelPerCell = function(Params: Pointer;
        Value: Integer): LongBool; cdecl;
      TSetDetectorParametersPerspectiveRemoveIgnoredMarginPerCell = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersMaxErroneousBitsInBorderRate = function(Params: Pointer;
        Value: Double): LongBool; cdecl;
      TSetDetectorParametersMinOtsuStdDev = function(Params: Pointer; Value: Double): LongBool; cdecl;
      TSetDetectorParametersErrorCorrectionRate = function(Params: Pointer; Value: Double): LongBool; cdecl;
    var
      GetPredefinedDictionary: TGetPredefinedDictionary;
      ExtendDictionary: TExtendDictionary;
      DeleteDictionary: TDeleteDictionary;
      GenerateImageMarker: TGenerateImageMarker;
      CreateArucoDetector: TCreateArucoDetector;
      DeleteArucoDetector: TDeleteArucoDetector;
      DetectMarkers: TDetectMarkers;
      DrawDetectedMarkers: TDrawDetectedMarkers;
      DrawDetectedCornersCharuco: TDrawDetectedCornersCharuco;
      DrawDetectedDiamonds: TDrawDetectedDiamonds;
      CreateGridBoard: TCreateGridBoard;
      CreateCharucoBoard: TCreateCharucoBoard;
      DeleteBoard: TDeleteBoard;
      DrawPlanarBoard: TDrawPlanarBoard;
      CreateCharucoDetector: TCreateCharucoDetector;
      DeleteCharucoDetector: TDeleteCharucoDetector;
      DetectCharucoDiamond: TDetectCharucoDiamond;
      EstimatePoseSingleMarkers: TEstimatePoseSingleMarkers;
      EstimatePoseBoard: TEstimatePoseBoard;
      EstimatePoseCharucoBoard: TEstimatePoseCharucoBoard;
      CalibrateCameraAruco: TCalibrateCameraAruco;
      CalibrateCameraCharuco: TCalibrateCameraCharuco;
      CreateDetectorParameters: TCreateDetectorParameters;
      DeleteDetectorParameters: TDeleteDetectorParameters;
      SetDetectorParametersAdaptiveThreshWinSizeMin: TSetDetectorParametersAdaptiveThreshWinSizeMin;
      SetDetectorParametersAdaptiveThreshWinSizeMax: TSetDetectorParametersAdaptiveThreshWinSizeMax;
      SetDetectorParametersAdaptiveThreshWinSizeStep: TSetDetectorParametersAdaptiveThreshWinSizeStep;
      SetDetectorParametersAdaptiveThreshConstant: TSetDetectorParametersAdaptiveThreshConstant;
      SetDetectorParametersMinMarkerPerimeterRate: TSetDetectorParametersMinMarkerPerimeterRate;
      SetDetectorParametersMaxMarkerPerimeterRate: TSetDetectorParametersMaxMarkerPerimeterRate;
      SetDetectorParametersPolygonalApproxAccuracyRate: TSetDetectorParametersPolygonalApproxAccuracyRate;
      SetDetectorParametersMinCornerDistanceRate: TSetDetectorParametersMinCornerDistanceRate;
      SetDetectorParametersMinDistanceToBorder: TSetDetectorParametersMinDistanceToBorder;
      SetDetectorParametersMinMarkerDistanceRate: TSetDetectorParametersMinMarkerDistanceRate;
      SetDetectorParametersCornerRefinementMethod: TSetDetectorParametersCornerRefinementMethod;
      SetDetectorParametersCornerRefinementWinSize: TSetDetectorParametersCornerRefinementWinSize;
      SetDetectorParametersCornerRefinementMaxIterations: TSetDetectorParametersCornerRefinementMaxIterations;
      SetDetectorParametersCornerRefinementMinAccuracy: TSetDetectorParametersCornerRefinementMinAccuracy;
      SetDetectorParametersMarkerBorderBits: TSetDetectorParametersMarkerBorderBits;
      SetDetectorParametersPerspectiveRemovePixelPerCell: TSetDetectorParametersPerspectiveRemovePixelPerCell;
      SetDetectorParametersPerspectiveRemoveIgnoredMarginPerCell: TSetDetectorParametersPerspectiveRemoveIgnoredMarginPerCell;
      SetDetectorParametersMaxErroneousBitsInBorderRate: TSetDetectorParametersMaxErroneousBitsInBorderRate;
      SetDetectorParametersMinOtsuStdDev: TSetDetectorParametersMinOtsuStdDev;
      SetDetectorParametersErrorCorrectionRate: TSetDetectorParametersErrorCorrectionRate;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVArucoModule.Initialize(const Handle: TLibHandle);
begin
  GetPredefinedDictionary := CVBind(Handle, 'cv_aruco_getPredefinedDictionary');
  ExtendDictionary := CVBind(Handle, 'cv_aruco_extendDictionary');
  DeleteDictionary := CVBind(Handle, 'cv_aruco_deleteDictionary');
  GenerateImageMarker := CVBind(Handle, 'cv_aruco_generateImageMarker');
  CreateArucoDetector := CVBind(Handle, 'cv_aruco_createArucoDetector');
  DeleteArucoDetector := CVBind(Handle, 'cv_aruco_deleteArucoDetector');
  DetectMarkers := CVBind(Handle, 'cv_aruco_detectMarkers');
  DrawDetectedMarkers := CVBind(Handle, 'cv_aruco_drawDetectedMarkers');
  DrawDetectedCornersCharuco := CVBind(Handle, 'cv_aruco_drawDetectedCornersCharuco');
  DrawDetectedDiamonds := CVBind(Handle, 'cv_aruco_drawDetectedDiamonds');
  CreateGridBoard := CVBind(Handle, 'cv_aruco_createGridBoard');
  CreateCharucoBoard := CVBind(Handle, 'cv_aruco_createCharucoBoard');
  DeleteBoard := CVBind(Handle, 'cv_aruco_deleteBoard');
  DrawPlanarBoard := CVBind(Handle, 'cv_aruco_drawPlanarBoard');
  CreateCharucoDetector := CVBind(Handle, 'cv_aruco_createCharucoDetector');
  DeleteCharucoDetector := CVBind(Handle, 'cv_aruco_deleteCharucoDetector');
  DetectCharucoDiamond := CVBind(Handle, 'cv_aruco_detectCharucoDiamond');
  EstimatePoseSingleMarkers := CVBind(Handle, 'cv_aruco_estimatePoseSingleMarkers');
  EstimatePoseBoard := CVBind(Handle, 'cv_aruco_estimatePoseBoard');
  EstimatePoseCharucoBoard := CVBind(Handle, 'cv_aruco_estimatePoseCharucoBoard');
  CalibrateCameraAruco := CVBind(Handle, 'cv_aruco_calibrateCameraAruco');
  CalibrateCameraCharuco := CVBind(Handle, 'cv_aruco_calibrateCameraCharuco');
  CreateDetectorParameters := CVBind(Handle, 'cv_aruco_createDetectorParameters');
  DeleteDetectorParameters := CVBind(Handle, 'cv_aruco_deleteDetectorParameters');
  SetDetectorParametersAdaptiveThreshWinSizeMin := CVBind(Handle,
    'cv_aruco_setDetectorParametersAdaptiveThreshWinSizeMin');
  SetDetectorParametersAdaptiveThreshWinSizeMax := CVBind(Handle,
    'cv_aruco_setDetectorParametersAdaptiveThreshWinSizeMax');
  SetDetectorParametersAdaptiveThreshWinSizeStep := CVBind(Handle,
    'cv_aruco_setDetectorParametersAdaptiveThreshWinSizeStep');
  SetDetectorParametersAdaptiveThreshConstant := CVBind(Handle,
    'cv_aruco_setDetectorParametersAdaptiveThreshConstant');
  SetDetectorParametersMinMarkerPerimeterRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersMinMarkerPerimeterRate');
  SetDetectorParametersMaxMarkerPerimeterRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersMaxMarkerPerimeterRate');
  SetDetectorParametersPolygonalApproxAccuracyRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersPolygonalApproxAccuracyRate');
  SetDetectorParametersMinCornerDistanceRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersMinCornerDistanceRate');
  SetDetectorParametersMinDistanceToBorder := CVBind(Handle,
    'cv_aruco_setDetectorParametersMinDistanceToBorder');
  SetDetectorParametersMinMarkerDistanceRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersMinMarkerDistanceRate');
  SetDetectorParametersCornerRefinementMethod := CVBind(Handle,
    'cv_aruco_setDetectorParametersCornerRefinementMethod');
  SetDetectorParametersCornerRefinementWinSize := CVBind(Handle,
    'cv_aruco_setDetectorParametersCornerRefinementWinSize');
  SetDetectorParametersCornerRefinementMaxIterations := CVBind(Handle,
    'cv_aruco_setDetectorParametersCornerRefinementMaxIterations');
  SetDetectorParametersCornerRefinementMinAccuracy := CVBind(Handle,
    'cv_aruco_setDetectorParametersCornerRefinementMinAccuracy');
  SetDetectorParametersMarkerBorderBits := CVBind(Handle, 'cv_aruco_setDetectorParametersMarkerBorderBits');
  SetDetectorParametersPerspectiveRemovePixelPerCell := CVBind(Handle,
    'cv_aruco_setDetectorParametersPerspectiveRemovePixelPerCell');
  SetDetectorParametersPerspectiveRemoveIgnoredMarginPerCell := CVBind(Handle,
    'cv_aruco_setDetectorParametersPerspectiveRemoveIgnoredMarginPerCell');
  SetDetectorParametersMaxErroneousBitsInBorderRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersMaxErroneousBitsInBorderRate');
  SetDetectorParametersMinOtsuStdDev := CVBind(Handle, 'cv_aruco_setDetectorParametersMinOtsuStdDev');
  SetDetectorParametersErrorCorrectionRate := CVBind(Handle,
    'cv_aruco_setDetectorParametersErrorCorrectionRate');
end;

end.
