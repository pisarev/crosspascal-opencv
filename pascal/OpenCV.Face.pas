{ ************************************************************************** }
{                                                                            }
{ OpenCV.Face                                                                }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev (ypisareff@outlook.com)                     }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Face;

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
  TCVFaceModule = record
  public
    type
      TCreateEigenFaceRecognizer = function(NumComponents: Integer; Threshold: Double): Pointer; cdecl;
      TDeleteEigenFaceRecognizer = function(Recognizer: Pointer): LongBool; cdecl;
      TCreateFisherFaceRecognizer = function(NumComponents: Integer; Threshold: Double): Pointer; cdecl;
      TDeleteFisherFaceRecognizer = function(Recognizer: Pointer): LongBool; cdecl;
      TCreateLBPHFaceRecognizer = function(Radius, Neighbors, GridX, GridY: Integer;
        Threshold: Double): Pointer; cdecl;
      TDeleteLBPHFaceRecognizer = function(Recognizer: Pointer): LongBool; cdecl;
      TLbphGetGridX = function(Recognizer: Pointer): Integer; cdecl;
      TLbphSetGridX = function(Recognizer: Pointer; Val: Integer): LongBool; cdecl;
      TLbphGetGridY = function(Recognizer: Pointer): Integer; cdecl;
      TLbphSetGridY = function(Recognizer: Pointer; Val: Integer): LongBool; cdecl;
      TLbphGetRadius = function(Recognizer: Pointer): Integer; cdecl;
      TLbphSetRadius = function(Recognizer: Pointer; Val: Integer): LongBool; cdecl;
      TLbphGetNeighbors = function(Recognizer: Pointer): Integer; cdecl;
      TLbphSetNeighbors = function(Recognizer: Pointer; Val: Integer): LongBool; cdecl;
      TLbphGetThreshold = function(Recognizer: Pointer): Double; cdecl;
      TLbphSetThreshold = function(Recognizer: Pointer; Val: Double): LongBool; cdecl;
      TLbphGetHistograms = function(Recognizer: Pointer; Histograms: PMat): LongBool; cdecl;
      TLbphGetLabels = function(Recognizer: Pointer; Labels: PMat): LongBool; cdecl;
      TRecognizerTrain = function(Recognizer: Pointer; Images: PMat; Labels: PInteger;
        Count: Integer): LongBool; cdecl;
      TRecognizerUpdate = function(Recognizer: Pointer; Images: PMat; Labels: PInteger;
        Count: Integer): LongBool; cdecl;
      TRecognizerPredict = function(Recognizer: Pointer; Src: PMat; &Label: PInteger;
        Confidence: PDouble): LongBool; cdecl;
      TRecognizerSave = function(Recognizer: Pointer; Filename: PAnsiChar): LongBool; cdecl;
      TRecognizerLoad = function(Recognizer: Pointer; Filename: PAnsiChar): LongBool; cdecl;
      TRecognizerSetLabelInfo = function(Recognizer: Pointer; &Label: Integer;
        StrInfo: PAnsiChar): LongBool; cdecl;
      TRecognizerGetLabelInfo = function(Recognizer: Pointer; &Label: Integer; StrInfo: PAnsiChar;
        MaxLen: Integer): LongBool; cdecl;
      TRecognizerGetThreshold = function(Recognizer: Pointer): Double; cdecl;
      TRecognizerSetThreshold = function(Recognizer: Pointer; Val: Double): LongBool; cdecl;
      TCreateFacemarkLBF = function: Pointer; cdecl;
      TCreateFacemarkAAM = function: Pointer; cdecl;
      TDeleteFacemark = function(Facemark: Pointer): LongBool; cdecl;
      TFacemarkLoadModel = function(Facemark: Pointer; Model: PAnsiChar): LongBool; cdecl;
      TFacemarkFit = function(Facemark: Pointer; Image: PMat; Faces: POCVRect; FaceCount: Integer;
        Landmarks: PMat; LandmarkCount: PInteger): LongBool; cdecl;
      TDrawFacemarks = function(Image: PMat; Points: PMat; Color: TOCVScalar): LongBool; cdecl;
    var
      CreateEigenFaceRecognizer: TCreateEigenFaceRecognizer;
      DeleteEigenFaceRecognizer: TDeleteEigenFaceRecognizer;
      CreateFisherFaceRecognizer: TCreateFisherFaceRecognizer;
      DeleteFisherFaceRecognizer: TDeleteFisherFaceRecognizer;
      CreateLBPHFaceRecognizer: TCreateLBPHFaceRecognizer;
      DeleteLBPHFaceRecognizer: TDeleteLBPHFaceRecognizer;
      LbphGetGridX: TLbphGetGridX;
      LbphSetGridX: TLbphSetGridX;
      LbphGetGridY: TLbphGetGridY;
      LbphSetGridY: TLbphSetGridY;
      LbphGetRadius: TLbphGetRadius;
      LbphSetRadius: TLbphSetRadius;
      LbphGetNeighbors: TLbphGetNeighbors;
      LbphSetNeighbors: TLbphSetNeighbors;
      LbphGetThreshold: TLbphGetThreshold;
      LbphSetThreshold: TLbphSetThreshold;
      LbphGetHistograms: TLbphGetHistograms;
      LbphGetLabels: TLbphGetLabels;
      RecognizerTrain: TRecognizerTrain;
      RecognizerUpdate: TRecognizerUpdate;
      RecognizerPredict: TRecognizerPredict;
      RecognizerSave: TRecognizerSave;
      RecognizerLoad: TRecognizerLoad;
      RecognizerSetLabelInfo: TRecognizerSetLabelInfo;
      RecognizerGetLabelInfo: TRecognizerGetLabelInfo;
      RecognizerGetThreshold: TRecognizerGetThreshold;
      RecognizerSetThreshold: TRecognizerSetThreshold;
      CreateFacemarkLBF: TCreateFacemarkLBF;
      CreateFacemarkAAM: TCreateFacemarkAAM;
      DeleteFacemark: TDeleteFacemark;
      FacemarkLoadModel: TFacemarkLoadModel;
      FacemarkFit: TFacemarkFit;
      DrawFacemarks: TDrawFacemarks;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVFaceModule.Initialize(const Handle: TLibHandle);
begin
  CreateEigenFaceRecognizer := CVBind(Handle, 'cv_face_createEigenFaceRecognizer');
  DeleteEigenFaceRecognizer := CVBind(Handle, 'cv_face_deleteEigenFaceRecognizer');
  CreateFisherFaceRecognizer := CVBind(Handle, 'cv_face_createFisherFaceRecognizer');
  DeleteFisherFaceRecognizer := CVBind(Handle, 'cv_face_deleteFisherFaceRecognizer');
  CreateLBPHFaceRecognizer := CVBind(Handle, 'cv_face_createLBPHFaceRecognizer');
  DeleteLBPHFaceRecognizer := CVBind(Handle, 'cv_face_deleteLBPHFaceRecognizer');
  LbphGetGridX := CVBind(Handle, 'cv_face_lbphGetGridX');
  LbphSetGridX := CVBind(Handle, 'cv_face_lbphSetGridX');
  LbphGetGridY := CVBind(Handle, 'cv_face_lbphGetGridY');
  LbphSetGridY := CVBind(Handle, 'cv_face_lbphSetGridY');
  LbphGetRadius := CVBind(Handle, 'cv_face_lbphGetRadius');
  LbphSetRadius := CVBind(Handle, 'cv_face_lbphSetRadius');
  LbphGetNeighbors := CVBind(Handle, 'cv_face_lbphGetNeighbors');
  LbphSetNeighbors := CVBind(Handle, 'cv_face_lbphSetNeighbors');
  LbphGetThreshold := CVBind(Handle, 'cv_face_lbphGetThreshold');
  LbphSetThreshold := CVBind(Handle, 'cv_face_lbphSetThreshold');
  LbphGetHistograms := CVBind(Handle, 'cv_face_lbphGetHistograms');
  LbphGetLabels := CVBind(Handle, 'cv_face_lbphGetLabels');
  RecognizerTrain := CVBind(Handle, 'cv_face_recognizerTrain');
  RecognizerUpdate := CVBind(Handle, 'cv_face_recognizerUpdate');
  RecognizerPredict := CVBind(Handle, 'cv_face_recognizerPredict');
  RecognizerSave := CVBind(Handle, 'cv_face_recognizerSave');
  RecognizerLoad := CVBind(Handle, 'cv_face_recognizerLoad');
  RecognizerSetLabelInfo := CVBind(Handle, 'cv_face_recognizerSetLabelInfo');
  RecognizerGetLabelInfo := CVBind(Handle, 'cv_face_recognizerGetLabelInfo');
  RecognizerGetThreshold := CVBind(Handle, 'cv_face_recognizerGetThreshold');
  RecognizerSetThreshold := CVBind(Handle, 'cv_face_recognizerSetThreshold');
  CreateFacemarkLBF := CVBind(Handle, 'cv_face_createFacemarkLBF');
  CreateFacemarkAAM := CVBind(Handle, 'cv_face_createFacemarkAAM');
  DeleteFacemark := CVBind(Handle, 'cv_face_deleteFacemark');
  FacemarkLoadModel := CVBind(Handle, 'cv_face_facemarkLoadModel');
  FacemarkFit := CVBind(Handle, 'cv_face_facemarkFit');
  DrawFacemarks := CVBind(Handle, 'cv_face_drawFacemarks');
end;

end.
