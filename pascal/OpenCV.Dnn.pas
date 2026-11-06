{ ************************************************************************** }
{                                                                            }
{ OpenCV.Dnn                                                                 }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Dnn;

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
  TCVDnnModule = record
  public
    type
      TSetData = function(Count: Integer; Data: Pointer): Pointer; cdecl;
      TCreateNet = function(ConfigFile, WeightsFile: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TDeleteNet = function(Handle: Pointer): LongBool; cdecl;
      TCreateDarknet = function(CfgFile, WeightsFile: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TOnnxDetect = function(Handle: Pointer; Image: TMat; ConfThreshold, NmsThreshold: Single;
        &Set: TSetData; Data: Pointer): LongBool; cdecl;
      TDarknetDetect = function(Handle: Pointer; Image: TMat; ConfThreshold, NmsThreshold: Single;
        &Set: TSetData; Data: Pointer): LongBool; cdecl;
      TDetectSceneBox = function(Handle: Pointer; Image: TMat; ConfThreshold, NmsThreshold: Single;
        &Set: TSetData; Data: Pointer): LongBool; cdecl;
      TCreateOpenVINO = function(ModelFile, ConfigFile: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TReadNetFromONNX = function(OnnxFile: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TReadNetFromTensorflow = function(Model, Config: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TReadNetFromCaffe = function(Prototxt, CaffeModel: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TNetForward = function(Handle: Pointer; OutputName: PAnsiChar; Target: PMat): LongBool; cdecl;
      TNetSetInput = function(Handle: Pointer; Blob: TMat; Name: PAnsiChar): LongBool; cdecl;
      TNetGetLayerNames = function(Handle: Pointer; &Set: TSetData; Data: Pointer): LongBool; cdecl;
      TBlobFromImage = function(Image: TMat; Target: PMat; ScaleFactor: Double; Size: TOCVSize;
        Mean: POCVScalar; SwapRB, Crop: LongBool; DDepth: Integer): LongBool; cdecl;
      TNMSBoxes = function(Boxes: Pointer; Scores: Pointer; Count: Integer;
        ScoreThreshold, NmsThreshold: Single; Indices: PInteger; IndicesCount: PInteger; Eta: Single;
        TopK: Integer): LongBool; cdecl;
      TReadNet = function(Model, Config, Framework: PAnsiChar; Handle: PPointer): LongBool; cdecl;
      TReadNetFromTorch = function(Model: PAnsiChar; IsBinary, Evaluate: LongBool;
        Handle: PPointer): LongBool; cdecl;
      TNetSetPreferableBackend = function(Handle: Pointer; BackendId: Integer): LongBool; cdecl;
      TNetSetPreferableTarget = function(Handle: Pointer; TargetId: Integer): LongBool; cdecl;
      TNetEnableFusion = function(Handle: Pointer; Fusion: LongBool): LongBool; cdecl;
      TNetGetUnconnectedOutLayers = function(Handle: Pointer; Layers: PInteger; Count: PInteger;
        MaxCount: Integer): LongBool; cdecl;
      TNetGetUnconnectedOutLayersNames = function(Handle: Pointer; Names: PPAnsiChar; Count: PInteger;
        MaxCount: Integer): LongBool; cdecl;
      TBlobFromImages = function(Images: PMat; ImageCount: Integer; Blob: PMat; ScaleFactor: Double;
        HSize, VSize: Integer; Mean: POCVScalar; SwapRB, Crop: LongBool; DDepth: Integer): LongBool; cdecl;
      TImagesFromBlob = function(Blob: TMat; Images: PMat; Count: PInteger;
        MaxCount: Integer): LongBool; cdecl;
      TNetEmpty = function(Handle: Pointer): LongBool; cdecl;
      TNetGetLayerCount = function(Handle: Pointer): Integer; cdecl;
      TNetDump = function(Handle: Pointer; Buffer: PAnsiChar; MaxLen: Integer): Integer; cdecl;
      TNetGetPerfProfile = function(Handle: Pointer; Timings: PDouble): Integer; cdecl;
      TNetEnableWinograd = function(Handle: Pointer; UseWinograd: LongBool): Integer; cdecl;
      TReadNetFromDarknet = function(CfgFile, DarknetModel: PAnsiChar): Pointer; cdecl;
      TReadNetFromModelOptimizer = function(Xml, Bin: PAnsiChar): Pointer; cdecl;
      TReadNetFromTFLite = function(Model: PAnsiChar): Pointer; cdecl;
      TNMSBoxesBatched = function(Bboxes: Pointer; Scores: PSingle; ClassIds: PInteger; Count: Integer;
        ScoreThreshold, NmsThreshold: Single; Indices, IndicesCount: PInteger; Eta: Single;
        TopK: Integer): Integer; cdecl;
      TNMSBoxesRotated = function(Bboxes: Pointer; Scores: PSingle; Count: Integer;
        ScoreThreshold, NmsThreshold: Single; Indices, IndicesCount: PInteger; Eta: Single;
        TopK: Integer): Integer; cdecl;
      TCreateDetectionModel = function(Model, Config: PAnsiChar): Pointer; cdecl;
      TCreateDetectionModelFromNet = function(Net: Pointer): Pointer; cdecl;
      TDeleteDetectionModel = function(Handle: Pointer): Integer; cdecl;
      TDetectionModelDetect = function(Handle: Pointer; Frame: TMat; ClassIds: PInteger; Confidences: PSingle;
        Boxes: Pointer; Count: PInteger; MaxCount: Integer;
        ConfThreshold, NmsThreshold: Single): Integer; cdecl;
      TDetectionModelSetInputSize = function(Handle: Pointer; Width, Height: Integer): Integer; cdecl;
      TDetectionModelSetInputScale = function(Handle: Pointer; Scale: Double): Integer; cdecl;
      TDetectionModelSetInputMean = function(Handle: Pointer; Mean: TOCVScalar): Integer; cdecl;
      TDetectionModelSetInputSwapRB = function(Handle: Pointer; SwapRB: LongBool): Integer; cdecl;
      TDetectionModelSetInputCrop = function(Handle: Pointer; Crop: LongBool): Integer; cdecl;
      TCreateClassificationModel = function(Model, Config: PAnsiChar): Pointer; cdecl;
      TCreateClassificationModelFromNet = function(Net: Pointer): Pointer; cdecl;
      TDeleteClassificationModel = function(Handle: Pointer): Integer; cdecl;
      TClassificationModelClassify = function(Handle: Pointer; Frame: TMat; ClassId: PInteger;
        Conf: PSingle): Integer; cdecl;
      TClassificationModelSetInputSize = function(Handle: Pointer; Width, Height: Integer): Integer; cdecl;
      TClassificationModelSetInputScale = function(Handle: Pointer; Scale: Double): Integer; cdecl;
      TClassificationModelSetInputMean = function(Handle: Pointer; Mean: TOCVScalar): Integer; cdecl;
      TClassificationModelSetInputSwapRB = function(Handle: Pointer; SwapRB: LongBool): Integer; cdecl;
      TCreateSegmentationModel = function(Model, Config: PAnsiChar): Pointer; cdecl;
      TCreateSegmentationModelFromNet = function(Net: Pointer): Pointer; cdecl;
      TDeleteSegmentationModel = function(Handle: Pointer): Integer; cdecl;
      TSegmentationModelSegment = function(Handle: Pointer; Frame: TMat; Mask: PMat): Integer; cdecl;
      TSegmentationModelSetInputSize = function(Handle: Pointer; Width, Height: Integer): Integer; cdecl;
      TSegmentationModelSetInputScale = function(Handle: Pointer; Scale: Double): Integer; cdecl;
      TSegmentationModelSetInputMean = function(Handle: Pointer; Mean: TOCVScalar): Integer; cdecl;
      TSegmentationModelSetInputSwapRB = function(Handle: Pointer; SwapRB: LongBool): Integer; cdecl;
      TCreateTextRecognitionModel = function(Model, Config: PAnsiChar): Pointer; cdecl;
      TDeleteTextRecognitionModel = function(Handle: Pointer): Integer; cdecl;
      TTextRecognitionModelRecognize = function(Handle: Pointer; Frame: TMat; Result: PAnsiChar;
        MaxLen: Integer): Integer; cdecl;
      TTextRecognitionModelSetVocabulary = function(Handle: Pointer; Vocabulary: PAnsiChar): Integer; cdecl;
      TGetAvailableTargets = function(Backend: Integer; Targets, Count: PInteger;
        MaxCount: Integer): Integer; cdecl;
    var
      CreateNet: TCreateNet;
      DeleteNet: TDeleteNet;
      CreateDarknet: TCreateDarknet;
      OnnxDetect: TOnnxDetect;
      DarknetDetect: TDarknetDetect;
      DetectSceneBox: TDetectSceneBox;
      CreateOpenVINO: TCreateOpenVINO;
      ReadNetFromONNX: TReadNetFromONNX;
      ReadNetFromTensorflow: TReadNetFromTensorflow;
      ReadNetFromCaffe: TReadNetFromCaffe;
      NetForward: TNetForward;
      NetSetInput: TNetSetInput;
      NetGetLayerNames: TNetGetLayerNames;
      BlobFromImage: TBlobFromImage;
      NMSBoxes: TNMSBoxes;
      ReadNet: TReadNet;
      ReadNetFromTorch: TReadNetFromTorch;
      NetSetPreferableBackend: TNetSetPreferableBackend;
      NetSetPreferableTarget: TNetSetPreferableTarget;
      NetEnableFusion: TNetEnableFusion;
      NetGetUnconnectedOutLayers: TNetGetUnconnectedOutLayers;
      NetGetUnconnectedOutLayersNames: TNetGetUnconnectedOutLayersNames;
      BlobFromImages: TBlobFromImages;
      ImagesFromBlob: TImagesFromBlob;
      NetEmpty: TNetEmpty;
      NetGetLayerCount: TNetGetLayerCount;
      NetDump: TNetDump;
      NetGetPerfProfile: TNetGetPerfProfile;
      NetEnableWinograd: TNetEnableWinograd;
      ReadNetFromDarknet: TReadNetFromDarknet;
      ReadNetFromModelOptimizer: TReadNetFromModelOptimizer;
      ReadNetFromTFLite: TReadNetFromTFLite;
      NMSBoxesBatched: TNMSBoxesBatched;
      NMSBoxesRotated: TNMSBoxesRotated;
      CreateDetectionModel: TCreateDetectionModel;
      CreateDetectionModelFromNet: TCreateDetectionModelFromNet;
      DeleteDetectionModel: TDeleteDetectionModel;
      DetectionModelDetect: TDetectionModelDetect;
      DetectionModelSetInputSize: TDetectionModelSetInputSize;
      DetectionModelSetInputScale: TDetectionModelSetInputScale;
      DetectionModelSetInputMean: TDetectionModelSetInputMean;
      DetectionModelSetInputSwapRB: TDetectionModelSetInputSwapRB;
      DetectionModelSetInputCrop: TDetectionModelSetInputCrop;
      CreateClassificationModel: TCreateClassificationModel;
      CreateClassificationModelFromNet: TCreateClassificationModelFromNet;
      DeleteClassificationModel: TDeleteClassificationModel;
      ClassificationModelClassify: TClassificationModelClassify;
      ClassificationModelSetInputSize: TClassificationModelSetInputSize;
      ClassificationModelSetInputScale: TClassificationModelSetInputScale;
      ClassificationModelSetInputMean: TClassificationModelSetInputMean;
      ClassificationModelSetInputSwapRB: TClassificationModelSetInputSwapRB;
      CreateSegmentationModel: TCreateSegmentationModel;
      CreateSegmentationModelFromNet: TCreateSegmentationModelFromNet;
      DeleteSegmentationModel: TDeleteSegmentationModel;
      SegmentationModelSegment: TSegmentationModelSegment;
      SegmentationModelSetInputSize: TSegmentationModelSetInputSize;
      SegmentationModelSetInputScale: TSegmentationModelSetInputScale;
      SegmentationModelSetInputMean: TSegmentationModelSetInputMean;
      SegmentationModelSetInputSwapRB: TSegmentationModelSetInputSwapRB;
      CreateTextRecognitionModel: TCreateTextRecognitionModel;
      DeleteTextRecognitionModel: TDeleteTextRecognitionModel;
      TextRecognitionModelRecognize: TTextRecognitionModelRecognize;
      TextRecognitionModelSetVocabulary: TTextRecognitionModelSetVocabulary;
      GetAvailableTargets: TGetAvailableTargets;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVDnnModule.Initialize(const Handle: TLibHandle);
begin
  CreateNet := CVBind(Handle, 'cv_dnn_createNet');
  DeleteNet := CVBind(Handle, 'cv_dnn_deleteNet');
  CreateDarknet := CVBind(Handle, 'cv_dnn_createDarknet');
  OnnxDetect := CVBind(Handle, 'cv_dnn_onnxDetect');
  DarknetDetect := CVBind(Handle, 'cv_dnn_darknetDetect');
  DetectSceneBox := CVBind(Handle, 'cv_dnn_detectSceneBox');
  CreateOpenVINO := CVBind(Handle, 'cv_dnn_createOpenVINO');
  ReadNetFromONNX := CVBind(Handle, 'cv_dnn_readNetFromONNX');
  ReadNetFromTensorflow := CVBind(Handle, 'cv_dnn_readNetFromTensorflow');
  ReadNetFromCaffe := CVBind(Handle, 'cv_dnn_readNetFromCaffe');
  NetForward := CVBind(Handle, 'cv_dnn_netForward');
  NetSetInput := CVBind(Handle, 'cv_dnn_netSetInput');
  NetGetLayerNames := CVBind(Handle, 'cv_dnn_netGetLayerNames');
  BlobFromImage := CVBind(Handle, 'cv_dnn_blobFromImage');
  NMSBoxes := CVBind(Handle, 'cv_dnn_nmsBoxes');
  ReadNet := CVBind(Handle, 'cv_dnn_readNet');
  ReadNetFromTorch := CVBind(Handle, 'cv_dnn_readNetFromTorch');
  NetSetPreferableBackend := CVBind(Handle, 'cv_dnn_netSetPreferableBackend');
  NetSetPreferableTarget := CVBind(Handle, 'cv_dnn_netSetPreferableTarget');
  NetEnableFusion := CVBind(Handle, 'cv_dnn_netEnableFusion');
  NetGetUnconnectedOutLayers := CVBind(Handle, 'cv_dnn_netGetUnconnectedOutLayers');
  NetGetUnconnectedOutLayersNames := CVBind(Handle, 'cv_dnn_netGetUnconnectedOutLayersNames');
  BlobFromImages := CVBind(Handle, 'cv_dnn_blobFromImages');
  ImagesFromBlob := CVBind(Handle, 'cv_dnn_imagesFromBlob');
  NetEmpty := CVBind(Handle, 'cv_dnn_netEmpty');
  NetGetLayerCount := CVBind(Handle, 'cv_dnn_netGetLayerCount');
  NetDump := CVBind(Handle, 'cv_dnn_netDump');
  NetGetPerfProfile := CVBind(Handle, 'cv_dnn_netGetPerfProfile');
  NetEnableWinograd := CVBind(Handle, 'cv_dnn_netEnableWinograd');
  ReadNetFromDarknet := CVBind(Handle, 'cv_dnn_readNetFromDarknet');
  ReadNetFromModelOptimizer := CVBind(Handle, 'cv_dnn_readNetFromModelOptimizer');
  ReadNetFromTFLite := CVBind(Handle, 'cv_dnn_readNetFromTFLite');
  NMSBoxesBatched := CVBind(Handle, 'cv_dnn_NMSBoxesBatched');
  NMSBoxesRotated := CVBind(Handle, 'cv_dnn_NMSBoxesRotated');
  CreateDetectionModel := CVBind(Handle, 'cv_dnn_createDetectionModel');
  CreateDetectionModelFromNet := CVBind(Handle, 'cv_dnn_createDetectionModelFromNet');
  DeleteDetectionModel := CVBind(Handle, 'cv_dnn_deleteDetectionModel');
  DetectionModelDetect := CVBind(Handle, 'cv_dnn_detectionModelDetect');
  DetectionModelSetInputSize := CVBind(Handle, 'cv_dnn_detectionModelSetInputSize');
  DetectionModelSetInputScale := CVBind(Handle, 'cv_dnn_detectionModelSetInputScale');
  DetectionModelSetInputMean := CVBind(Handle, 'cv_dnn_detectionModelSetInputMean');
  DetectionModelSetInputSwapRB := CVBind(Handle, 'cv_dnn_detectionModelSetInputSwapRB');
  DetectionModelSetInputCrop := CVBind(Handle, 'cv_dnn_detectionModelSetInputCrop');
  CreateClassificationModel := CVBind(Handle, 'cv_dnn_createClassificationModel');
  CreateClassificationModelFromNet := CVBind(Handle, 'cv_dnn_createClassificationModelFromNet');
  DeleteClassificationModel := CVBind(Handle, 'cv_dnn_deleteClassificationModel');
  ClassificationModelClassify := CVBind(Handle, 'cv_dnn_classificationModelClassify');
  ClassificationModelSetInputSize := CVBind(Handle, 'cv_dnn_classificationModelSetInputSize');
  ClassificationModelSetInputScale := CVBind(Handle, 'cv_dnn_classificationModelSetInputScale');
  ClassificationModelSetInputMean := CVBind(Handle, 'cv_dnn_classificationModelSetInputMean');
  ClassificationModelSetInputSwapRB := CVBind(Handle, 'cv_dnn_classificationModelSetInputSwapRB');
  CreateSegmentationModel := CVBind(Handle, 'cv_dnn_createSegmentationModel');
  CreateSegmentationModelFromNet := CVBind(Handle, 'cv_dnn_createSegmentationModelFromNet');
  DeleteSegmentationModel := CVBind(Handle, 'cv_dnn_deleteSegmentationModel');
  SegmentationModelSegment := CVBind(Handle, 'cv_dnn_segmentationModelSegment');
  SegmentationModelSetInputSize := CVBind(Handle, 'cv_dnn_segmentationModelSetInputSize');
  SegmentationModelSetInputScale := CVBind(Handle, 'cv_dnn_segmentationModelSetInputScale');
  SegmentationModelSetInputMean := CVBind(Handle, 'cv_dnn_segmentationModelSetInputMean');
  SegmentationModelSetInputSwapRB := CVBind(Handle, 'cv_dnn_segmentationModelSetInputSwapRB');
  CreateTextRecognitionModel := CVBind(Handle, 'cv_dnn_createTextRecognitionModel');
  DeleteTextRecognitionModel := CVBind(Handle, 'cv_dnn_deleteTextRecognitionModel');
  TextRecognitionModelRecognize := CVBind(Handle, 'cv_dnn_textRecognitionModelRecognize');
  TextRecognitionModelSetVocabulary := CVBind(Handle, 'cv_dnn_textRecognitionModelSetVocabulary');
  GetAvailableTargets := CVBind(Handle, 'cv_dnn_getAvailableTargets');
end;

end.
