{ ************************************************************************** }
{                                                                            }
{ OpenCVTypes                                                                }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCVTypes;

{$B-}
{$IFDEF FPC}
  {$MODE DELPHI}
{$ENDIF}

interface

uses
  {$IFDEF FPC}
  Types, DynLibs, OpenCVConsts;
  {$ELSE}
  WinApi.Windows, System.Types, OpenCVConsts;
  {$ENDIF}

{$IFNDEF FPC}
type
  TLibHandle = THandle;
{$ENDIF}

type
  PHistogram = ^THistogram;
  THistogram = TArray<Single>;
  THistogramNormType = (L2Hys = 0);

  PMat = ^TMat;
  TMat = type Pointer;
  PNet = ^TNet;
  TNet = type Pointer;
  PHog = ^THog;
  THog = type Pointer;
  PSvm = ^TSvm;
  TSvm = type Pointer;
  PSvmArray = ^TSvmArray;
  TSvmArray = array of TSvm;
  PSvmModel = ^TSvmModel;
  TSvmModel = type Pointer;
  PVideoCapture = ^TVideoCapture;
  TVideoCapture = type Pointer;
  PBGSSubtractor = ^TBGSSubtractor;
  TBGSSubtractor = type Pointer;
  PBackgroundSubtractor = ^TBackgroundSubtractor;
  TBackgroundSubtractor = type Pointer;
  PTracker = ^TTracker;
  TTracker = type Pointer;
  PClahe = ^TClahe;
  TClahe = type Pointer;
  PDoxaImage = ^TDoxaImage;
  TDoxaImage = type Pointer;
  PRetina = ^TRetina;
  TRetina = type Pointer;

  PVideoWriter = ^TVideoWriter;
  TVideoWriter = type Pointer;
  PCascadeClassifier = ^TCascadeClassifier;
  TCascadeClassifier = type Pointer;
  PQRCodeDetector = ^TQRCodeDetector;
  TQRCodeDetector = type Pointer;
  PFeatureDetector = ^TFeatureDetector;
  TFeatureDetector = type Pointer;
  PDescriptorMatcher = ^TDescriptorMatcher;
  TDescriptorMatcher = type Pointer;
  PSuperpixelSLIC = ^TSuperpixelSLIC;
  TSuperpixelSLIC = type Pointer;
  PMergeMertens = ^TMergeMertens;
  TMergeMertens = type Pointer;
  PMergeDebevec = ^TMergeDebevec;
  TMergeDebevec = type Pointer;
  PAlignMTB = ^TAlignMTB;
  TAlignMTB = type Pointer;
  PTonemapDrago = ^TTonemapDrago;
  TTonemapDrago = type Pointer;
  PTonemapReinhard = ^TTonemapReinhard;
  TTonemapReinhard = type Pointer;

  PStitcher = ^TStitcher;
  TStitcher = type Pointer;
  PDISOpticalFlow = ^TDISOpticalFlow;
  TDISOpticalFlow = type Pointer;
  PKNearest = ^TKNearest;
  TKNearest = type Pointer;
  PDTrees = ^TDTrees;
  TDTrees = type Pointer;
  PRTrees = ^TRTrees;
  TRTrees = type Pointer;
  PBoost = ^TBoost;
  TBoost = type Pointer;
  PANN_MLP = ^TANN_MLP;
  TANN_MLP = type Pointer;
  PLogisticRegression = ^TLogisticRegression;
  TLogisticRegression = type Pointer;
  PNormalBayesClassifier = ^TNormalBayesClassifier;
  TNormalBayesClassifier = type Pointer;
  PEdgeDrawing = ^TEdgeDrawing;
  TEdgeDrawing = type Pointer;
  PStructuredEdgeDetection = ^TStructuredEdgeDetection;
  TStructuredEdgeDetection = type Pointer;
  PMergeRobertson = ^TMergeRobertson;
  TMergeRobertson = type Pointer;
  PTonemapMantiuk = ^TTonemapMantiuk;
  TTonemapMantiuk = type Pointer;
  PCalibrateDebevec = ^TCalibrateDebevec;
  TCalibrateDebevec = type Pointer;
  PCalibrateRobertson = ^TCalibrateRobertson;
  TCalibrateRobertson = type Pointer;
  PLineSegmentDetector = ^TLineSegmentDetector;
  TLineSegmentDetector = type Pointer;
  PStereoBM = ^TStereoBM;
  TStereoBM = type Pointer;
  PStereoSGBM = ^TStereoSGBM;
  TStereoSGBM = type Pointer;
  PSubdiv2D = ^TSubdiv2D;
  TSubdiv2D = type Pointer;
  PKalmanFilter = ^TKalmanFilter;
  TKalmanFilter = type Pointer;
  PFileStorage = ^TFileStorage;
  TFileStorage = type Pointer;
  PFileNode = ^TFileNode;
  TFileNode = type Pointer;
  PGeneralizedHoughBallard = ^TGeneralizedHoughBallard;
  TGeneralizedHoughBallard = type Pointer;
  PGeneralizedHoughGuil = ^TGeneralizedHoughGuil;
  TGeneralizedHoughGuil = type Pointer;
  PMSERDetector = ^TMSERDetector;
  TMSERDetector = type Pointer;
  PGFTTDetector = ^TGFTTDetector;
  TGFTTDetector = type Pointer;
  PFastFeatureDetector = ^TFastFeatureDetector;
  TFastFeatureDetector = type Pointer;
  PAgastFeatureDetector = ^TAgastFeatureDetector;
  TAgastFeatureDetector = type Pointer;
  PKAZE = ^TKAZE;
  TKAZE = type Pointer;
  PBOWKMeansTrainer = ^TBOWKMeansTrainer;
  TBOWKMeansTrainer = type Pointer;
  PBOWImgDescriptorExtractor = ^TBOWImgDescriptorExtractor;
  TBOWImgDescriptorExtractor = type Pointer;
  PEM = ^TEM;
  TEM = type Pointer;
  PSVMSGD = ^TSVMSGD;
  TSVMSGD = type Pointer;
  PTrainData = ^TTrainData;
  TTrainData = type Pointer;

  PDetectionModel = ^TDetectionModel;
  TDetectionModel = type Pointer;
  PClassificationModel = ^TClassificationModel;
  TClassificationModel = type Pointer;
  PSegmentationModel = ^TSegmentationModel;
  TSegmentationModel = type Pointer;
  PTextRecognitionModel = ^TTextRecognitionModel;
  TTextRecognitionModel = type Pointer;

  PArucoDetector = ^TArucoDetector;
  TArucoDetector = type Pointer;
  PCharucoDetector = ^TCharucoDetector;
  TCharucoDetector = type Pointer;
  PArucoBoard = ^TArucoBoard;
  TArucoBoard = type Pointer;
  PArucoDictionary = ^TArucoDictionary;
  TArucoDictionary = type Pointer;
  PArucoDetectorParameters = ^TArucoDetectorParameters;
  TArucoDetectorParameters = type Pointer;

  PSURF = ^TSURF;
  TSURF = type Pointer;
  PFREAK = ^TFREAK;
  TFREAK = type Pointer;
  PDAISY = ^TDAISY;
  TDAISY = type Pointer;
  PBRIEF = ^TBRIEF;
  TBRIEF = type Pointer;
  PLATCH = ^TLATCH;
  TLATCH = type Pointer;
  PBEBLID = ^TBEBLID;
  TBEBLID = type Pointer;
  PStarDetector = ^TStarDetector;
  TStarDetector = type Pointer;
  PPCTSignatures = ^TPCTSignatures;
  TPCTSignatures = type Pointer;

  PDualTVL1OpticalFlow = ^TDualTVL1OpticalFlow;
  TDualTVL1OpticalFlow = type Pointer;

  PEigenFaceRecognizer = ^TEigenFaceRecognizer;
  TEigenFaceRecognizer = type Pointer;
  PFisherFaceRecognizer = ^TFisherFaceRecognizer;
  TFisherFaceRecognizer = type Pointer;
  PLBPHFaceRecognizer = ^TLBPHFaceRecognizer;
  TLBPHFaceRecognizer = type Pointer;
  PFacemark = ^TFacemark;
  TFacemark = type Pointer;

  PSimpleWB = ^TSimpleWB;
  TSimpleWB = type Pointer;
  PGrayworldWB = ^TGrayworldWB;
  TGrayworldWB = type Pointer;
  PLearningBasedWB = ^TLearningBasedWB;
  TLearningBasedWB = type Pointer;

  PSimpleBlobDetector = ^TSimpleBlobDetector;
  TSimpleBlobDetector = type Pointer;

  PFaceDetectorYN = ^TFaceDetectorYN;
  TFaceDetectorYN = type Pointer;
  PFaceRecognizerSF = ^TFaceRecognizerSF;
  TFaceRecognizerSF = type Pointer;

  PTonemap = ^TTonemap;
  TTonemap = type Pointer;

  PFarnebackOpticalFlow = ^TFarnebackOpticalFlow;
  TFarnebackOpticalFlow = type Pointer;
  PSparsePyrLKOpticalFlow = ^TSparsePyrLKOpticalFlow;
  TSparsePyrLKOpticalFlow = type Pointer;
  PVariationalRefinement = ^TVariationalRefinement;
  TVariationalRefinement = type Pointer;

  PDTFilter = ^TDTFilter;
  TDTFilter = type Pointer;
  PGuidedFilter = ^TGuidedFilter;
  TGuidedFilter = type Pointer;
  PFastGlobalSmootherFilter = ^TFastGlobalSmootherFilter;
  TFastGlobalSmootherFilter = type Pointer;
  PFastLineDetector = ^TFastLineDetector;
  TFastLineDetector = type Pointer;
  PEdgeBoxes = ^TEdgeBoxes;
  TEdgeBoxes = type Pointer;
  PGraphSegmentation = ^TGraphSegmentation;
  TGraphSegmentation = type Pointer;
  PSelectiveSearchSegmentation = ^TSelectiveSearchSegmentation;
  TSelectiveSearchSegmentation = type Pointer;
  PSuperpixelSEEDS = ^TSuperpixelSEEDS;
  TSuperpixelSEEDS = type Pointer;
  PSuperpixelLSC = ^TSuperpixelLSC;
  TSuperpixelLSC = type Pointer;

  POCVPoint2f = ^TOCVPoint2f;
  TOCVPoint2f = packed record
    X: Single;
    Y: Single;
  end;
  POCVPoint2fArray = ^TOCVPoint2fArray;
  TOCVPoint2fArray = TArray<TOCVPoint2f>;

  POCVFlowPoint2f = ^TOCVFlowPoint2f;
  TOCVFlowPoint2f = packed record
    Status: AnsiChar;
    Err: Single;
    X: Single;
    Y: Single;
  end;
  POCVFlowPoint2fArray = ^TOCVFlowPoint2fArray;
  TOCVFlowPoint2fArray = array of TOCVFlowPoint2f;

  POCVBox = ^TOCVBox;
  TOCVBox = packed record
  public
    type
      TPoint2f = record
        X: Single;
        Y: Single;
      end;
    var
      Confidence: Single;
      case Byte of
        1: (Vertex: array[0..3] of TPoint2f);
        2: (A, B, C, D: TPoint2f);
  end;

  POCVBoxArray = ^TOCVBoxArray;
  TOCVBoxArray = TArray<TOCVBox>;

  POCVRect = ^TOCVRect;
  TOCVRect = packed record
    X: Integer;
    Y: Integer;
    HSize: Integer;
    VSize: Integer;
  end;

  POCVObject = ^TOCVObject;
  TOCVObject = packed record
    Rect: TOCVRect;
    Id: Integer;
    Confidence: Single;
  end;

  POCVObjectArray = ^TOCVObjectArray;
  TOCVObjectArray = TArray<TOCVObject>;

  POCVMean = ^TOCVMean;
  TOCVMean = packed record
    R: Single;
    G: Single;
    B: Single;
  end;

  POCVSize = ^TOCVSize;
  TOCVSize = packed record
    cx: Integer;
    cy: Integer;
  end;

  POCVPoint = ^TOCVPoint;
  TOCVPoint = packed record
    X: Integer;
    Y: Integer;
  end;

  POCVPointArray = ^TOCVPointArray;
  TOCVPointArray = TArray<TOCVPoint>;

  POCVLine = ^TOCVLine;
  TOCVLine = packed record
    A: TOCVPoint;
    B: TOCVPoint;
  end;

  POCVLineArray = ^TOCVLineArray;
  TOCVLineArray = TArray<TOCVLine>;

  POCVPlace = ^TOCVPlace;
  TOCVPlace = packed record
    A: TOCVPoint;
    B: TOCVPoint;
    Value: Double;
  end;
  POCVPlaceArray = ^TOCVPlaceArray;
  TOCVPlaceArray = TArray<TOCVPlace>;

  POCVColor = ^TOCVColor;
  TOCVColor = packed record
    R: Byte;
    G: Byte;
    B: Byte;
    A: Byte;
  end;

  POCVScalar = ^TOCVScalar;
  TOCVScalar = packed record
  case Byte of
    0: (V0, V1, V2, V3: Double);
    1: (A: array[0..3] of Double);
  end;

  POCVMoments = ^TOCVMoments;
  TOCVMoments = packed record
    M00: Double;
    M10: Double;
    M01: Double;
    M20: Double;
    M11: Double;
    M02: Double;
    M30: Double;
    M21: Double;
    M12: Double;
    M03: Double;
    Mu20: Double;
    Mu11: Double;
    Mu02: Double;
    Mu30: Double;
    Mu21: Double;
    Mu12: Double;
    Mu03: Double;
    Nu20: Double;
    Nu11: Double;
    Nu02: Double;
    Nu30: Double;
    Nu21: Double;
    Nu12: Double;
    Nu03: Double;
  end;

  POCVKeyPoint = ^TOCVKeyPoint;
  TOCVKeyPoint = packed record
    X: Single;
    Y: Single;
    Size: Single;
    Angle: Single;
    Response: Single;
    Octave: Integer;
    ClassId: Integer;
  end;

  POCVDMatch = ^TOCVDMatch;
  TOCVDMatch = packed record
    QueryIdx: Integer;
    TrainIdx: Integer;
    ImgIdx: Integer;
    Distance: Single;
  end;

  POCVRotatedRect = ^TOCVRotatedRect;
  TOCVRotatedRect = packed record
    CenterX: Single;
    CenterY: Single;
    Width: Single;
    Height: Single;
    Angle: Single;
  end;

  POCVHuMoments = ^TOCVHuMoments;
  TOCVHuMoments = packed record
    Hu: array[0..6] of Double;
  end;

  POCVCircle = ^TOCVCircle;
  TOCVCircle = packed record
    CenterX: Single;
    CenterY: Single;
    Radius: Single;
  end;

  POCVKeyPointArray = ^TOCVKeyPointArray;
  TOCVKeyPointArray = TArray<TOCVKeyPoint>;

  POCVDMatchArray = ^TOCVDMatchArray;
  TOCVDMatchArray = TArray<TOCVDMatch>;

  TThresholdKind = (tkNikblack, tkSauvola, tkWolfJolion);
  TDoxaThresholdKind = (dtkOtsu, dtkBernsen, dtkNiblack, dtkSauvola, dtkWolf, dtkGatos, dtkNick, dtkSu,
    dtkTRSingh, dtkBataineh, dtkISauvola, dtkWan);
  TOperationKind = (okSubtract, okAdd, okMultiply, okDivide, okAnd, okOr, okXor);

function CV_MAT_DEPTH(const Flags: Integer): Integer;
function CV_MAKETYPE(Depth, Cn: Integer): Integer;

function CVBind(const Handle: TLibHandle; const Name: AnsiString): Pointer;
procedure CVBindReset;
function CVBindMissingCount: Integer;
function CVBindMissingNames(const Limit: Integer): string;

function OCVPoint2f(const X, Y: Single): TOCVPoint2f;
function OCVFlowPoint2f(const Status: AnsiChar; const Err, X, Y: Single): TOCVFlowPoint2f;
function OCVRect(const X, Y, HSize, VSize: Integer): TOCVRect;
function OCVObject(const Rect: TOCVRect; const Id: Integer; const Confidence: Single): TOCVObject;
function OCVMean(const R, G, B: Single): TOCVMean;
function OCVSize(const cx, cy: Integer): TOCVSize; overload;
function OCVSize(const Size: TSize): TOCVSize; overload;
function OCVPoint(const X, Y: Integer): TOCVPoint; overload;
function OCVPoint(const Point: TPoint): TOCVPoint; overload;
function OCVPlace(const A, B: TOCVPoint; const Value: Double): TOCVPlace;
function OCVColor(const R, G, B, A: Byte): TOCVColor;
function OCVScalar(const V0, V1, V2, V3: Double): TOCVScalar;
function OCVKeyPoint(const X, Y, Size, Angle, Response: Single; const Octave, ClassId: Integer): TOCVKeyPoint;
function OCVDMatch(const QueryIdx, TrainIdx, ImgIdx: Integer; const Distance: Single): TOCVDMatch;
function OCVMoments(const M00, M10, M01, M20, M11, M02, M30, M21, M12, M03: Double): TOCVMoments;

const
  OCVWhite: TOCVColor = (R: 255; G: 255; B: 255; A: 255);
  OCVBlack: TOCVColor = (R: 0; G: 0; B: 0; A: 0);
  OCVZMean: TOCVMean = (R: 0; G: 0; B: 0);

implementation

var
  BindMissing: array of string;

function CVBind(const Handle: TLibHandle; const Name: AnsiString): Pointer;
begin
  {$IFDEF FPC}
  Result := GetProcAddress(Handle, Name);
  {$ELSE}
  Result := Pointer(GetProcAddress(Handle, PAnsiChar(Name)));
  {$ENDIF}
  if Result = nil then
  begin
    SetLength(BindMissing, Length(BindMissing) + 1);
    BindMissing[High(BindMissing)] := string(Name);
  end;
end;

procedure CVBindReset;
begin
  SetLength(BindMissing, 0);
end;

function CVBindMissingCount: Integer;
begin
  Result := Length(BindMissing);
end;

function CVBindMissingNames(const Limit: Integer): string;
var
  I, N: Integer;
begin
  N := Length(BindMissing);
  if N > Limit then
    N := Limit;
  Result := '';
  for I := 0 to N - 1 do
  begin
    if I > 0 then
      Result := Result + ', ';
    Result := Result + BindMissing[I];
  end;
  if Length(BindMissing) > N then
    Result := Result + ', ...';
end;

function CV_MAT_DEPTH(const Flags: Integer): Integer;
begin
  Result := Flags and CV_MAT_DEPTH_MASK;
end;

function CV_MAKETYPE(Depth, Cn: Integer): Integer;
begin
  Result := (CV_MAT_DEPTH(Depth) + (((Cn) - 1) shl CV_CN_SHIFT));
end;

function OCVPoint2f(const X, Y: Single): TOCVPoint2f;
begin
  FillChar(Result, SizeOf(TOCVPoint2f), 0);
  Result.X := X;
  Result.Y := Y;
end;

function OCVFlowPoint2f(const Status: AnsiChar; const Err, X, Y: Single): TOCVFlowPoint2f;
begin
  FillChar(Result, SizeOf(TOCVFlowPoint2f), 0);
  Result.Status := Status;
  Result.Err := Err;
  Result.X := X;
  Result.Y := Y;
end;

function OCVRect(const X, Y, HSize, VSize: Integer): TOCVRect;
begin
  FillChar(Result, SizeOf(TOCVRect), 0);
  Result.X := X;
  Result.Y := Y;
  Result.HSize := HSize;
  Result.VSize := VSize;
end;

function OCVObject(const Rect: TOCVRect; const Id: Integer; const Confidence: Single): TOCVObject;
begin
  FillChar(Result, SizeOf(TOCVObject), 0);
  Result.Rect := Rect;
  Result.Id := Id;
  Result.Confidence := Confidence;
end;

function OCVMean(const R, G, B: Single): TOCVMean;
begin
  FillChar(Result, SizeOf(TOCVMean), 0);
  Result.R := R;
  Result.G := G;
  Result.B := B;
end;

function OCVSize(const cx, cy: Integer): TOCVSize;
begin
  FillChar(Result, SizeOf(TOCVSize), 0);
  Result.cx := cx;
  Result.cy := cy;
end;

function OCVSize(const Size: TSize): TOCVSize;
begin
  FillChar(Result, SizeOf(TOCVSize), 0);
  Result.cx := Size.cx;
  Result.cy := Size.cy;
end;

function OCVPoint(const X, Y: Integer): TOCVPoint;
begin
  FillChar(Result, SizeOf(TOCVPoint), 0);
  Result.X := X;
  Result.Y := Y;
end;

function OCVPoint(const Point: TPoint): TOCVPoint;
begin
  FillChar(Result, SizeOf(TOCVPoint), 0);
  Result.X := Point.X;
  Result.Y := Point.Y;
end;

function OCVPlace(const A, B: TOCVPoint; const Value: Double): TOCVPlace;
begin
  FillChar(Result, SizeOf(TOCVPlace), 0);
  Result.A := A;
  Result.B := B;
  Result.Value := Value;
end;

function OCVColor(const R, G, B, A: Byte): TOCVColor;
begin
  FillChar(Result, SizeOf(TOCVColor), 0);
  Result.R := R;
  Result.G := G;
  Result.B := B;
  Result.A := A;
end;

function OCVScalar(const V0, V1, V2, V3: Double): TOCVScalar;
begin
  FillChar(Result, SizeOf(TOCVScalar), 0);
  Result.V0 := V0;
  Result.V1 := V1;
  Result.V2 := V2;
  Result.V3 := V3;
end;

function OCVKeyPoint(const X, Y, Size, Angle, Response: Single; const Octave, ClassId: Integer): TOCVKeyPoint;
begin
  FillChar(Result, SizeOf(TOCVKeyPoint), 0);
  Result.X := X;
  Result.Y := Y;
  Result.Size := Size;
  Result.Angle := Angle;
  Result.Response := Response;
  Result.Octave := Octave;
  Result.ClassId := ClassId;
end;

function OCVDMatch(const QueryIdx, TrainIdx, ImgIdx: Integer; const Distance: Single): TOCVDMatch;
begin
  FillChar(Result, SizeOf(TOCVDMatch), 0);
  Result.QueryIdx := QueryIdx;
  Result.TrainIdx := TrainIdx;
  Result.ImgIdx := ImgIdx;
  Result.Distance := Distance;
end;

function OCVMoments(const M00, M10, M01, M20, M11, M02, M30, M21, M12, M03: Double): TOCVMoments;
begin
  FillChar(Result, SizeOf(TOCVMoments), 0);
  Result.M00 := M00;
  Result.M10 := M10;
  Result.M01 := M01;
  Result.M20 := M20;
  Result.M11 := M11;
  Result.M02 := M02;
  Result.M30 := M30;
  Result.M21 := M21;
  Result.M12 := M12;
  Result.M03 := M03;
end;

end.
