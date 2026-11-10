{ ************************************************************************** }
{                                                                            }
{ OpenCV.ObjDetect                                                           }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev (ypisareff@outlook.com)                     }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.ObjDetect;

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
  TCVObjDetectModule = record
  public
    type
      TGetData = procedure(Count: Integer; From, Data: Pointer); cdecl;
      TCreateHOG = function(WinSize, BlockSize, BlockStride, CellSize: TOCVSize; NBins: Integer;
        Handle: PPointer): LongBool; cdecl;
      TDeleteHOG = function(Handle: Pointer): LongBool; cdecl;
      TCalcHistogram = function(Handle: Pointer; Image: TMat; WinStride, Padding: TOCVSize; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TCreateCascadeClassifier = function(FileName: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TDeleteCascadeClassifier = function(Handle: Pointer): LongBool; cdecl;
      TCascadeDetectMultiScale = function(Handle: Pointer; Image: TMat; ScaleFactor: Double;
        MinNeighbors, Flags: Integer; MinSize, MaxSize: TOCVSize; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      THogDetectMultiScale = function(Handle: Pointer; Image: TMat; HitThreshold: Double;
        WinStride, Padding: TOCVSize; Scale: Double; FinalThreshold: Double; UseMeanShiftGrouping: LongBool;
        Get: TGetData; Data: Pointer): LongBool; cdecl;
      THogSetSVMDetector = function(Handle: Pointer; Detector: Pointer; Count: Integer): LongBool; cdecl;
      TCreateQRCodeDetector = function(Handle: PPointer): LongBool; cdecl;
      TDeleteQRCodeDetector = function(Handle: Pointer): LongBool; cdecl;
      TQRCodeDetect = function(Handle: Pointer; Image: TMat; Points: PMat;
        Detected: PInteger): LongBool; cdecl;
      TQRCodeDetectAndDecode = function(Handle: Pointer; Image: TMat; Points: PMat; DecodedInfo: PAnsiChar;
        MaxLen: PInteger): LongBool; cdecl;
      THogCompute = function(Handle: Pointer; Image: TMat; Descriptors: PMat;
        WinStrideW, WinStrideH, PaddingW, PaddingH: Integer): LongBool; cdecl;
      THogGetDefaultPeopleDetector = function(Detector: PMat): LongBool; cdecl;
      TCascadeClassifierLoad = function(Handle: Pointer; FileName: PAnsiChar): LongBool; cdecl;
      TCascadeClassifierEmpty = function(Handle: Pointer): LongBool; cdecl;
      TQrCodeDetectMulti = function(Handle: Pointer; Image: TMat; Points: PMat): LongBool; cdecl;
      TQrCodeDecodeCurved = function(Handle: Pointer; Image: TMat; Points: PMat; Result: PAnsiChar;
        ResultMaxLen: Integer; StraightQrCode: PMat): LongBool; cdecl;
      TGroupRectangles = function(RectList: POCVRect; Count: PInteger; GroupThreshold: Integer;
        Eps: Double): LongBool; cdecl;
      TCreateFaceDetectorYN = function(Model, Config: PAnsiChar; InputW, InputH: Integer;
        ScoreThreshold, NmsThreshold: Single; TopK, BackendId, TargetId: Integer): Pointer; cdecl;
      TDeleteFaceDetectorYN = function(Handle: Pointer): LongBool; cdecl;
      TFaceDetectorYNDetect = function(Handle: Pointer; Image: TMat; Faces: PMat): LongBool; cdecl;
      TCreateFaceRecognizerSF = function(Model, Config: PAnsiChar;
        BackendId, TargetId: Integer): Pointer; cdecl;
      THogDetect = function(Handle: Pointer; Image: TMat; HitThreshold: Double; WinStride, Padding: TOCVSize;
        Get: TGetData; Data: Pointer): LongBool; cdecl;
      THogGetWinSize = function(Handle: Pointer; out Value: TOCVSize): LongBool; cdecl;
      THogSetWinSize = function(Handle: Pointer; Value: TOCVSize): LongBool; cdecl;
      THogGetBlockSize = function(Handle: Pointer; out Value: TOCVSize): LongBool; cdecl;
      THogSetBlockSize = function(Handle: Pointer; Value: TOCVSize): LongBool; cdecl;
      THogGetBlockStride = function(Handle: Pointer; out Value: TOCVSize): LongBool; cdecl;
      THogSetBlockStride = function(Handle: Pointer; Value: TOCVSize): LongBool; cdecl;
      THogGetCellSize = function(Handle: Pointer; out Value: TOCVSize): LongBool; cdecl;
      THogSetCellSize = function(Handle: Pointer; Value: TOCVSize): LongBool; cdecl;
      THogGetNbins = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      THogSetNbins = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      THogGetWinSigma = function(Handle: Pointer; out Value: Double): LongBool; cdecl;
      THogSetWinSigma = function(Handle: Pointer; Value: Double): LongBool; cdecl;
      THogGetL2HysThreshold = function(Handle: Pointer; out Value: Double): LongBool; cdecl;
      THogSetL2HysThreshold = function(Handle: Pointer; Value: Double): LongBool; cdecl;
      THogGetGammaCorrection = function(Handle: Pointer; out Value: LongBool): LongBool; cdecl;
      THogSetGammaCorrection = function(Handle: Pointer; Value: LongBool): LongBool; cdecl;
      THogGetNlevels = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      THogSetNlevels = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      THogGetSignedGradient = function(Handle: Pointer; out Value: LongBool): LongBool; cdecl;
      THogSetSignedGradient = function(Handle: Pointer; Value: LongBool): LongBool; cdecl;
      THogSetSVMDetectorDefault = function(Handle: Pointer): LongBool; cdecl;
      THogSave = function(Handle: Pointer; FileName: PAnsiChar): LongBool; cdecl;
      THogLoad = function(Handle: Pointer; FileName: PAnsiChar): LongBool; cdecl;
      TFaceDetectorYNSetInputSize = function(Handle: Pointer; Width, Height: Integer): LongBool; cdecl;
      TFaceDetectorYNGetScoreThreshold = function(Handle: Pointer; out Value: Single): LongBool; cdecl;
      TFaceDetectorYNSetScoreThreshold = function(Handle: Pointer; Value: Single): LongBool; cdecl;
      TFaceDetectorYNGetNMSThreshold = function(Handle: Pointer; out Value: Single): LongBool; cdecl;
      TFaceDetectorYNSetNMSThreshold = function(Handle: Pointer; Value: Single): LongBool; cdecl;
      TFaceDetectorYNGetTopK = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TFaceDetectorYNSetTopK = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TDeleteFaceRecognizerSF = function(Handle: Pointer): LongBool; cdecl;
      TFaceRecognizerSFAlignCrop = function(Handle: Pointer; SrcImg: TMat;
        FaceBox, AlignedImg: PMat): LongBool; cdecl;
      TFaceRecognizerSFFeature = function(Handle: Pointer; AlignedImg: TMat;
        FaceFeature: PMat): LongBool; cdecl;
      TFaceRecognizerSFMatch = function(Handle: Pointer; FaceFeature1, FaceFeature2: TMat; DisType: Integer;
        out Distance: Double): LongBool; cdecl;
    var
      CreateHOG: TCreateHOG;
      DeleteHOG: TDeleteHOG;
      CalcHistogram: TCalcHistogram;
      CreateCascadeClassifier: TCreateCascadeClassifier;
      DeleteCascadeClassifier: TDeleteCascadeClassifier;
      CascadeDetectMultiScale: TCascadeDetectMultiScale;
      HogDetectMultiScale: THogDetectMultiScale;
      HogSetSVMDetector: THogSetSVMDetector;
      CreateQRCodeDetector: TCreateQRCodeDetector;
      DeleteQRCodeDetector: TDeleteQRCodeDetector;
      QRCodeDetect: TQRCodeDetect;
      QRCodeDetectAndDecode: TQRCodeDetectAndDecode;
      HogCompute: THogCompute;
      HogGetDefaultPeopleDetector: THogGetDefaultPeopleDetector;
      CascadeClassifierLoad: TCascadeClassifierLoad;
      CascadeClassifierEmpty: TCascadeClassifierEmpty;
      QrCodeDetectMulti: TQrCodeDetectMulti;
      QrCodeDecodeCurved: TQrCodeDecodeCurved;
      GroupRectangles: TGroupRectangles;
      CreateFaceDetectorYN: TCreateFaceDetectorYN;
      DeleteFaceDetectorYN: TDeleteFaceDetectorYN;
      FaceDetectorYNDetect: TFaceDetectorYNDetect;
      CreateFaceRecognizerSF: TCreateFaceRecognizerSF;
      HogDetect: THogDetect;
      HogGetWinSize: THogGetWinSize;
      HogSetWinSize: THogSetWinSize;
      HogGetBlockSize: THogGetBlockSize;
      HogSetBlockSize: THogSetBlockSize;
      HogGetBlockStride: THogGetBlockStride;
      HogSetBlockStride: THogSetBlockStride;
      HogGetCellSize: THogGetCellSize;
      HogSetCellSize: THogSetCellSize;
      HogGetNbins: THogGetNbins;
      HogSetNbins: THogSetNbins;
      HogGetWinSigma: THogGetWinSigma;
      HogSetWinSigma: THogSetWinSigma;
      HogGetL2HysThreshold: THogGetL2HysThreshold;
      HogSetL2HysThreshold: THogSetL2HysThreshold;
      HogGetGammaCorrection: THogGetGammaCorrection;
      HogSetGammaCorrection: THogSetGammaCorrection;
      HogGetNlevels: THogGetNlevels;
      HogSetNlevels: THogSetNlevels;
      HogGetSignedGradient: THogGetSignedGradient;
      HogSetSignedGradient: THogSetSignedGradient;
      HogSetSVMDetectorDefault: THogSetSVMDetectorDefault;
      HogSave: THogSave;
      HogLoad: THogLoad;
      FaceDetectorYNSetInputSize: TFaceDetectorYNSetInputSize;
      FaceDetectorYNGetScoreThreshold: TFaceDetectorYNGetScoreThreshold;
      FaceDetectorYNSetScoreThreshold: TFaceDetectorYNSetScoreThreshold;
      FaceDetectorYNGetNMSThreshold: TFaceDetectorYNGetNMSThreshold;
      FaceDetectorYNSetNMSThreshold: TFaceDetectorYNSetNMSThreshold;
      FaceDetectorYNGetTopK: TFaceDetectorYNGetTopK;
      FaceDetectorYNSetTopK: TFaceDetectorYNSetTopK;
      DeleteFaceRecognizerSF: TDeleteFaceRecognizerSF;
      FaceRecognizerSFAlignCrop: TFaceRecognizerSFAlignCrop;
      FaceRecognizerSFFeature: TFaceRecognizerSFFeature;
      FaceRecognizerSFMatch: TFaceRecognizerSFMatch;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVObjDetectModule.Initialize(const Handle: TLibHandle);
begin
  CreateHOG := CVBind(Handle, 'cv_objdetect_createHOG');
  DeleteHOG := CVBind(Handle, 'cv_objdetect_deleteHOG');
  CalcHistogram := CVBind(Handle, 'cv_objdetect_calcHistogram');
  CreateCascadeClassifier := CVBind(Handle, 'cv_objdetect_createCascadeClassifier');
  DeleteCascadeClassifier := CVBind(Handle, 'cv_objdetect_deleteCascadeClassifier');
  CascadeDetectMultiScale := CVBind(Handle, 'cv_objdetect_cascadeDetectMultiScale');
  HogDetectMultiScale := CVBind(Handle, 'cv_objdetect_hogDetectMultiScale');
  HogSetSVMDetector := CVBind(Handle, 'cv_objdetect_hogSetSVMDetector');
  CreateQRCodeDetector := CVBind(Handle, 'cv_objdetect_createQRCodeDetector');
  DeleteQRCodeDetector := CVBind(Handle, 'cv_objdetect_deleteQRCodeDetector');
  QRCodeDetect := CVBind(Handle, 'cv_objdetect_qrCodeDetect');
  QRCodeDetectAndDecode := CVBind(Handle, 'cv_objdetect_qrCodeDetectAndDecode');
  HogCompute := CVBind(Handle, 'cv_objdetect_hogCompute');
  HogGetDefaultPeopleDetector := CVBind(Handle, 'cv_objdetect_hogGetDefaultPeopleDetector');
  CascadeClassifierLoad := CVBind(Handle, 'cv_objdetect_cascadeClassifierLoad');
  CascadeClassifierEmpty := CVBind(Handle, 'cv_objdetect_cascadeClassifierEmpty');
  QrCodeDetectMulti := CVBind(Handle, 'cv_objdetect_qrCodeDetectMulti');
  QrCodeDecodeCurved := CVBind(Handle, 'cv_objdetect_qrCodeDecodeCurved');
  GroupRectangles := CVBind(Handle, 'cv_objdetect_groupRectangles');
  CreateFaceDetectorYN := CVBind(Handle, 'cv_objdetect_createFaceDetectorYN');
  DeleteFaceDetectorYN := CVBind(Handle, 'cv_objdetect_deleteFaceDetectorYN');
  FaceDetectorYNDetect := CVBind(Handle, 'cv_objdetect_faceDetectorYNDetect');
  CreateFaceRecognizerSF := CVBind(Handle, 'cv_objdetect_createFaceRecognizerSF');
  HogDetect := CVBind(Handle, 'cv_objdetect_hogDetect');
  HogGetWinSize := CVBind(Handle, 'cv_objdetect_hogGetWinSize');
  HogSetWinSize := CVBind(Handle, 'cv_objdetect_hogSetWinSize');
  HogGetBlockSize := CVBind(Handle, 'cv_objdetect_hogGetBlockSize');
  HogSetBlockSize := CVBind(Handle, 'cv_objdetect_hogSetBlockSize');
  HogGetBlockStride := CVBind(Handle, 'cv_objdetect_hogGetBlockStride');
  HogSetBlockStride := CVBind(Handle, 'cv_objdetect_hogSetBlockStride');
  HogGetCellSize := CVBind(Handle, 'cv_objdetect_hogGetCellSize');
  HogSetCellSize := CVBind(Handle, 'cv_objdetect_hogSetCellSize');
  HogGetNbins := CVBind(Handle, 'cv_objdetect_hogGetNbins');
  HogSetNbins := CVBind(Handle, 'cv_objdetect_hogSetNbins');
  HogGetWinSigma := CVBind(Handle, 'cv_objdetect_hogGetWinSigma');
  HogSetWinSigma := CVBind(Handle, 'cv_objdetect_hogSetWinSigma');
  HogGetL2HysThreshold := CVBind(Handle, 'cv_objdetect_hogGetL2HysThreshold');
  HogSetL2HysThreshold := CVBind(Handle, 'cv_objdetect_hogSetL2HysThreshold');
  HogGetGammaCorrection := CVBind(Handle, 'cv_objdetect_hogGetGammaCorrection');
  HogSetGammaCorrection := CVBind(Handle, 'cv_objdetect_hogSetGammaCorrection');
  HogGetNlevels := CVBind(Handle, 'cv_objdetect_hogGetNlevels');
  HogSetNlevels := CVBind(Handle, 'cv_objdetect_hogSetNlevels');
  HogGetSignedGradient := CVBind(Handle, 'cv_objdetect_hogGetSignedGradient');
  HogSetSignedGradient := CVBind(Handle, 'cv_objdetect_hogSetSignedGradient');
  HogSetSVMDetectorDefault := CVBind(Handle, 'cv_objdetect_hogSetSVMDetectorDefault');
  HogSave := CVBind(Handle, 'cv_objdetect_hogSave');
  HogLoad := CVBind(Handle, 'cv_objdetect_hogLoad');
  FaceDetectorYNSetInputSize := CVBind(Handle, 'cv_objdetect_faceDetectorYNSetInputSize');
  FaceDetectorYNGetScoreThreshold := CVBind(Handle, 'cv_objdetect_faceDetectorYNGetScoreThreshold');
  FaceDetectorYNSetScoreThreshold := CVBind(Handle, 'cv_objdetect_faceDetectorYNSetScoreThreshold');
  FaceDetectorYNGetNMSThreshold := CVBind(Handle, 'cv_objdetect_faceDetectorYNGetNMSThreshold');
  FaceDetectorYNSetNMSThreshold := CVBind(Handle, 'cv_objdetect_faceDetectorYNSetNMSThreshold');
  FaceDetectorYNGetTopK := CVBind(Handle, 'cv_objdetect_faceDetectorYNGetTopK');
  FaceDetectorYNSetTopK := CVBind(Handle, 'cv_objdetect_faceDetectorYNSetTopK');
  DeleteFaceRecognizerSF := CVBind(Handle, 'cv_objdetect_deleteFaceRecognizerSF');
  FaceRecognizerSFAlignCrop := CVBind(Handle, 'cv_objdetect_faceRecognizerSFAlignCrop');
  FaceRecognizerSFFeature := CVBind(Handle, 'cv_objdetect_faceRecognizerSFFeature');
  FaceRecognizerSFMatch := CVBind(Handle, 'cv_objdetect_faceRecognizerSFMatch');
end;

end.
