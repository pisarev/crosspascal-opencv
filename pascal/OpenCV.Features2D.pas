{ ************************************************************************** }
{                                                                            }
{ OpenCV.Features2D                                                          }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev (ypisareff@outlook.com)               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Features2D;

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
  TCVFeatures2DModule = record
  public
    type
      TGetData = procedure(Count: Integer; From, Data: Pointer); cdecl;
      TCreateORB = function(NFeatures: Integer; ScaleFactor: Double;
        NLevels, EdgeThreshold, FirstLevel, WTA_K, ScoreType, PatchSize, FastThreshold: Integer;
        Handle: PPointer): LongBool; cdecl;
      TDeleteORB = function(Handle: Pointer): LongBool; cdecl;
      TOrbDetectAndCompute = function(Handle: Pointer; Image, Mask: TMat; Descriptors: PMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TCreateSIFT = function(NFeatures: Integer; NOctaveLayers: Integer;
        ContrastThreshold, EdgeThreshold, Sigma: Double; Handle: PPointer): LongBool; cdecl;
      TDeleteSIFT = function(Handle: Pointer): LongBool; cdecl;
      TSiftDetectAndCompute = function(Handle: Pointer; Image, Mask: TMat; Descriptors: PMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TCreateBRISK = function(Thresh, Octaves: Integer; PatternScale: Single;
        Handle: PPointer): LongBool; cdecl;
      TDeleteBRISK = function(Handle: Pointer): LongBool; cdecl;
      TBriskDetectAndCompute = function(Handle: Pointer; Image, Mask: TMat; Descriptors: PMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TCreateAKAZE = function(DescriptorType, DescriptorSize, DescriptorChannels: Integer; Threshold: Single;
        NOctaves, NOctaveLayers, Diffusivity: Integer; Handle: PPointer): LongBool; cdecl;
      TDeleteAKAZE = function(Handle: Pointer): LongBool; cdecl;
      TAkazeDetectAndCompute = function(Handle: Pointer; Image, Mask: TMat; Descriptors: PMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TCreateBFMatcher = function(NormType: Integer; CrossCheck: LongBool; Handle: PPointer): LongBool; cdecl;
      TDeleteBFMatcher = function(Handle: Pointer): LongBool; cdecl;
      TBFMatch = function(Handle: Pointer; QueryDescriptors, TrainDescriptors: TMat; Mask: TMat;
        Get: TGetData; Data: Pointer): LongBool; cdecl;
      TBFKnnMatch = function(Handle: Pointer; QueryDescriptors, TrainDescriptors: TMat; K: Integer;
        Mask: TMat; Get: TGetData; Data: Pointer): LongBool; cdecl;
      TCreateFlannMatcher = function(Handle: PPointer): LongBool; cdecl;
      TDeleteFlannMatcher = function(Handle: Pointer): LongBool; cdecl;
      TFlannMatch = function(Handle: Pointer; QueryDescriptors, TrainDescriptors: TMat; Mask: TMat;
        Get: TGetData; Data: Pointer): LongBool; cdecl;
      TDrawMatches = function(Img1: TMat; KeyPoints1: Pointer; KpCount1: Integer; Img2: TMat;
        KeyPoints2: Pointer; KpCount2: Integer; Matches: Pointer; MatchCount: Integer; Target: PMat;
        MatchColor, SinglePointColor: TOCVScalar; Flags: Integer): LongBool; cdecl;
      TDrawKeypoints = function(Image: TMat; KeyPoints: Pointer; KpCount: Integer; Target: PMat;
        Color: TOCVScalar; Flags: Integer): LongBool; cdecl;
      TDrawMatchesKnn = function(Img1: TMat; Kp1: Pointer; Kp1Count: Integer; Img2: TMat; Kp2: Pointer;
        Kp2Count: Integer; Matches1to2: Pointer; MatchCounts: PInteger; MatchGroupCount: Integer;
        Target: PMat; MatchColor, SinglePointColor: TOCVScalar; Flags: Integer): LongBool; cdecl;
      TCreateSimpleBlobDetector = function(Handle: PPointer): LongBool; cdecl;
      TDeleteSimpleBlobDetector = function(Handle: Pointer): LongBool; cdecl;
      TSimpleBlobDetectorDetect = function(Handle: Pointer; Image: TMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TSimpleBlobDetectorGetMinThreshold = function(Handle: Pointer; out Value: Single): LongBool; cdecl;
      TSimpleBlobDetectorSetMinThreshold = function(Handle: Pointer; Value: Single): LongBool; cdecl;
      TSimpleBlobDetectorGetMaxThreshold = function(Handle: Pointer; out Value: Single): LongBool; cdecl;
      TSimpleBlobDetectorSetMaxThreshold = function(Handle: Pointer; Value: Single): LongBool; cdecl;
      TSimpleBlobDetectorGetMinArea = function(Handle: Pointer; out Value: Single): LongBool; cdecl;
      TSimpleBlobDetectorSetMinArea = function(Handle: Pointer; Value: Single): LongBool; cdecl;
      TCreateMSER = function(Delta, MinArea, MaxArea: Integer; MaxVariation, MinDiversity: Double;
        Handle: PPointer): LongBool; cdecl;
      TDeleteMSER = function(Handle: Pointer): LongBool; cdecl;
      TMserDetectRegions = function(Handle: Pointer; Image: TMat; Msers, Bboxes: PMat): LongBool; cdecl;
      TMserGetDelta = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TMserSetDelta = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TMserGetMinArea = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TMserSetMinArea = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TMserGetMaxArea = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TMserSetMaxArea = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TCreateGFTTDetector = function(MaxCorners: Integer; QualityLevel, MinDistance: Double;
        BlockSize: Integer; UseHarris: LongBool; K: Double; Handle: PPointer): LongBool; cdecl;
      TDeleteGFTTDetector = function(Handle: Pointer): LongBool; cdecl;
      TGfttDetectorDetect = function(Handle: Pointer; Image: TMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TGfttDetectorGetMaxCorners = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TGfttDetectorSetMaxCorners = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TGfttDetectorGetQualityLevel = function(Handle: Pointer; out Value: Double): LongBool; cdecl;
      TGfttDetectorSetQualityLevel = function(Handle: Pointer; Value: Double): LongBool; cdecl;
      TGfttDetectorGetMinDistance = function(Handle: Pointer; out Value: Double): LongBool; cdecl;
      TGfttDetectorSetMinDistance = function(Handle: Pointer; Value: Double): LongBool; cdecl;
      TCreateFastFeatureDetector = function(Threshold: Integer; NonmaxSuppression: LongBool; &Type: Integer;
        Handle: PPointer): LongBool; cdecl;
      TDeleteFastFeatureDetector = function(Handle: Pointer): LongBool; cdecl;
      TFastFeatureDetectorDetect = function(Handle: Pointer; Image: TMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TFastFeatureDetectorGetThreshold = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TFastFeatureDetectorSetThreshold = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TFastFeatureDetectorGetNonmaxSuppression = function(Handle: Pointer;
        out Value: LongBool): LongBool; cdecl;
      TFastFeatureDetectorSetNonmaxSuppression = function(Handle: Pointer; Value: LongBool): LongBool; cdecl;
      TCreateAgastFeatureDetector = function(Threshold: Integer; NonmaxSuppression: LongBool; &Type: Integer;
        Handle: PPointer): LongBool; cdecl;
      TDeleteAgastFeatureDetector = function(Handle: Pointer): LongBool; cdecl;
      TAgastFeatureDetectorDetect = function(Handle: Pointer; Image: TMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TAgastFeatureDetectorGetThreshold = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TAgastFeatureDetectorSetThreshold = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TAgastFeatureDetectorGetNonmaxSuppression = function(Handle: Pointer;
        out Value: LongBool): LongBool; cdecl;
      TAgastFeatureDetectorSetNonmaxSuppression = function(Handle: Pointer; Value: LongBool): LongBool; cdecl;
      TCreateKAZE = function(Extended, Upright: LongBool; Threshold: Single;
        NOctaves, NOctaveLayers, Diffusivity: Integer; Handle: PPointer): LongBool; cdecl;
      TDeleteKAZE = function(Handle: Pointer): LongBool; cdecl;
      TKazeDetectAndCompute = function(Handle: Pointer; Image, Mask: TMat; Descriptors: PMat; Get: TGetData;
        Data: Pointer): LongBool; cdecl;
      TKazeGetExtended = function(Handle: Pointer; out Value: LongBool): LongBool; cdecl;
      TKazeSetExtended = function(Handle: Pointer; Value: LongBool): LongBool; cdecl;
      TKazeGetUpright = function(Handle: Pointer; out Value: LongBool): LongBool; cdecl;
      TKazeSetUpright = function(Handle: Pointer; Value: LongBool): LongBool; cdecl;
      TKazeGetThreshold = function(Handle: Pointer; out Value: Single): LongBool; cdecl;
      TKazeSetThreshold = function(Handle: Pointer; Value: Single): LongBool; cdecl;
      TKazeGetNOctaves = function(Handle: Pointer; out Value: Integer): LongBool; cdecl;
      TKazeSetNOctaves = function(Handle: Pointer; Value: Integer): LongBool; cdecl;
      TCreateBOWKMeansTrainer = function(ClusterCount: Integer; Handle: PPointer): LongBool; cdecl;
      TDeleteBOWKMeansTrainer = function(Handle: Pointer): LongBool; cdecl;
      TBowKMeansTrainerAdd = function(Handle: Pointer; Descriptors: TMat): LongBool; cdecl;
      TBowKMeansTrainerCluster = function(Handle: Pointer; Result: PMat): LongBool; cdecl;
      TBowKMeansTrainerGetDescriptors = function(Handle: Pointer; Result: PMat): LongBool; cdecl;
      TBowKMeansTrainerDescriptorsCount = function(Handle: Pointer; out Count: Integer): LongBool; cdecl;
      TCreateBOWImgDescriptorExtractor = function(DMatcher: Pointer; Handle: PPointer): LongBool; cdecl;
      TDeleteBOWImgDescriptorExtractor = function(Handle: Pointer): LongBool; cdecl;
      TBowImgDescriptorExtractorSetVocabulary = function(Handle: Pointer; Vocabulary: TMat): LongBool; cdecl;
      TBowImgDescriptorExtractorCompute = function(Handle: Pointer; Image: TMat; KeyPoints: Pointer;
        KeyPointCount: Integer; ImgDescriptor: PMat): LongBool; cdecl;
      TBowImgDescriptorExtractorVocabularyEmpty = function(Handle: Pointer;
        out Empty: LongBool): LongBool; cdecl;
    var
      CreateORB: TCreateORB;
      DeleteORB: TDeleteORB;
      OrbDetectAndCompute: TOrbDetectAndCompute;
      CreateSIFT: TCreateSIFT;
      DeleteSIFT: TDeleteSIFT;
      SiftDetectAndCompute: TSiftDetectAndCompute;
      CreateBRISK: TCreateBRISK;
      DeleteBRISK: TDeleteBRISK;
      BriskDetectAndCompute: TBriskDetectAndCompute;
      CreateAKAZE: TCreateAKAZE;
      DeleteAKAZE: TDeleteAKAZE;
      AkazeDetectAndCompute: TAkazeDetectAndCompute;
      CreateBFMatcher: TCreateBFMatcher;
      DeleteBFMatcher: TDeleteBFMatcher;
      BFMatch: TBFMatch;
      BFKnnMatch: TBFKnnMatch;
      CreateFlannMatcher: TCreateFlannMatcher;
      DeleteFlannMatcher: TDeleteFlannMatcher;
      FlannMatch: TFlannMatch;
      DrawMatches: TDrawMatches;
      DrawKeypoints: TDrawKeypoints;
      DrawMatchesKnn: TDrawMatchesKnn;
      CreateSimpleBlobDetector: TCreateSimpleBlobDetector;
      DeleteSimpleBlobDetector: TDeleteSimpleBlobDetector;
      SimpleBlobDetectorDetect: TSimpleBlobDetectorDetect;
      SimpleBlobDetectorGetMinThreshold: TSimpleBlobDetectorGetMinThreshold;
      SimpleBlobDetectorSetMinThreshold: TSimpleBlobDetectorSetMinThreshold;
      SimpleBlobDetectorGetMaxThreshold: TSimpleBlobDetectorGetMaxThreshold;
      SimpleBlobDetectorSetMaxThreshold: TSimpleBlobDetectorSetMaxThreshold;
      SimpleBlobDetectorGetMinArea: TSimpleBlobDetectorGetMinArea;
      SimpleBlobDetectorSetMinArea: TSimpleBlobDetectorSetMinArea;
      CreateMSER: TCreateMSER;
      DeleteMSER: TDeleteMSER;
      MserDetectRegions: TMserDetectRegions;
      MserGetDelta: TMserGetDelta;
      MserSetDelta: TMserSetDelta;
      MserGetMinArea: TMserGetMinArea;
      MserSetMinArea: TMserSetMinArea;
      MserGetMaxArea: TMserGetMaxArea;
      MserSetMaxArea: TMserSetMaxArea;
      CreateGFTTDetector: TCreateGFTTDetector;
      DeleteGFTTDetector: TDeleteGFTTDetector;
      GfttDetectorDetect: TGfttDetectorDetect;
      GfttDetectorGetMaxCorners: TGfttDetectorGetMaxCorners;
      GfttDetectorSetMaxCorners: TGfttDetectorSetMaxCorners;
      GfttDetectorGetQualityLevel: TGfttDetectorGetQualityLevel;
      GfttDetectorSetQualityLevel: TGfttDetectorSetQualityLevel;
      GfttDetectorGetMinDistance: TGfttDetectorGetMinDistance;
      GfttDetectorSetMinDistance: TGfttDetectorSetMinDistance;
      CreateFastFeatureDetector: TCreateFastFeatureDetector;
      DeleteFastFeatureDetector: TDeleteFastFeatureDetector;
      FastFeatureDetectorDetect: TFastFeatureDetectorDetect;
      FastFeatureDetectorGetThreshold: TFastFeatureDetectorGetThreshold;
      FastFeatureDetectorSetThreshold: TFastFeatureDetectorSetThreshold;
      FastFeatureDetectorGetNonmaxSuppression: TFastFeatureDetectorGetNonmaxSuppression;
      FastFeatureDetectorSetNonmaxSuppression: TFastFeatureDetectorSetNonmaxSuppression;
      CreateAgastFeatureDetector: TCreateAgastFeatureDetector;
      DeleteAgastFeatureDetector: TDeleteAgastFeatureDetector;
      AgastFeatureDetectorDetect: TAgastFeatureDetectorDetect;
      AgastFeatureDetectorGetThreshold: TAgastFeatureDetectorGetThreshold;
      AgastFeatureDetectorSetThreshold: TAgastFeatureDetectorSetThreshold;
      AgastFeatureDetectorGetNonmaxSuppression: TAgastFeatureDetectorGetNonmaxSuppression;
      AgastFeatureDetectorSetNonmaxSuppression: TAgastFeatureDetectorSetNonmaxSuppression;
      CreateKAZE: TCreateKAZE;
      DeleteKAZE: TDeleteKAZE;
      KazeDetectAndCompute: TKazeDetectAndCompute;
      KazeGetExtended: TKazeGetExtended;
      KazeSetExtended: TKazeSetExtended;
      KazeGetUpright: TKazeGetUpright;
      KazeSetUpright: TKazeSetUpright;
      KazeGetThreshold: TKazeGetThreshold;
      KazeSetThreshold: TKazeSetThreshold;
      KazeGetNOctaves: TKazeGetNOctaves;
      KazeSetNOctaves: TKazeSetNOctaves;
      CreateBOWKMeansTrainer: TCreateBOWKMeansTrainer;
      DeleteBOWKMeansTrainer: TDeleteBOWKMeansTrainer;
      BowKMeansTrainerAdd: TBowKMeansTrainerAdd;
      BowKMeansTrainerCluster: TBowKMeansTrainerCluster;
      BowKMeansTrainerGetDescriptors: TBowKMeansTrainerGetDescriptors;
      BowKMeansTrainerDescriptorsCount: TBowKMeansTrainerDescriptorsCount;
      CreateBOWImgDescriptorExtractor: TCreateBOWImgDescriptorExtractor;
      DeleteBOWImgDescriptorExtractor: TDeleteBOWImgDescriptorExtractor;
      BowImgDescriptorExtractorSetVocabulary: TBowImgDescriptorExtractorSetVocabulary;
      BowImgDescriptorExtractorCompute: TBowImgDescriptorExtractorCompute;
      BowImgDescriptorExtractorVocabularyEmpty: TBowImgDescriptorExtractorVocabularyEmpty;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVFeatures2DModule.Initialize(const Handle: TLibHandle);
begin
  CreateORB := CVBind(Handle, 'cv_features2d_createORB');
  DeleteORB := CVBind(Handle, 'cv_features2d_deleteORB');
  OrbDetectAndCompute := CVBind(Handle, 'cv_features2d_orbDetectAndCompute');
  CreateSIFT := CVBind(Handle, 'cv_features2d_createSIFT');
  DeleteSIFT := CVBind(Handle, 'cv_features2d_deleteSIFT');
  SiftDetectAndCompute := CVBind(Handle, 'cv_features2d_siftDetectAndCompute');
  CreateBRISK := CVBind(Handle, 'cv_features2d_createBRISK');
  DeleteBRISK := CVBind(Handle, 'cv_features2d_deleteBRISK');
  BriskDetectAndCompute := CVBind(Handle, 'cv_features2d_briskDetectAndCompute');
  CreateAKAZE := CVBind(Handle, 'cv_features2d_createAKAZE');
  DeleteAKAZE := CVBind(Handle, 'cv_features2d_deleteAKAZE');
  AkazeDetectAndCompute := CVBind(Handle, 'cv_features2d_akazeDetectAndCompute');
  CreateBFMatcher := CVBind(Handle, 'cv_features2d_createBFMatcher');
  DeleteBFMatcher := CVBind(Handle, 'cv_features2d_deleteBFMatcher');
  BFMatch := CVBind(Handle, 'cv_features2d_bfMatch');
  BFKnnMatch := CVBind(Handle, 'cv_features2d_bfKnnMatch');
  CreateFlannMatcher := CVBind(Handle, 'cv_features2d_createFlannMatcher');
  DeleteFlannMatcher := CVBind(Handle, 'cv_features2d_deleteFlannMatcher');
  FlannMatch := CVBind(Handle, 'cv_features2d_flannMatch');
  DrawMatches := CVBind(Handle, 'cv_features2d_drawMatches');
  DrawKeypoints := CVBind(Handle, 'cv_features2d_drawKeypoints');
  DrawMatchesKnn := CVBind(Handle, 'cv_features2d_drawMatchesKnn');
  CreateSimpleBlobDetector := CVBind(Handle, 'cv_features2d_createSimpleBlobDetector');
  DeleteSimpleBlobDetector := CVBind(Handle, 'cv_features2d_deleteSimpleBlobDetector');
  SimpleBlobDetectorDetect := CVBind(Handle, 'cv_features2d_simpleBlobDetectorDetect');
  SimpleBlobDetectorGetMinThreshold := CVBind(Handle, 'cv_features2d_simpleBlobDetectorGetMinThreshold');
  SimpleBlobDetectorSetMinThreshold := CVBind(Handle, 'cv_features2d_simpleBlobDetectorSetMinThreshold');
  SimpleBlobDetectorGetMaxThreshold := CVBind(Handle, 'cv_features2d_simpleBlobDetectorGetMaxThreshold');
  SimpleBlobDetectorSetMaxThreshold := CVBind(Handle, 'cv_features2d_simpleBlobDetectorSetMaxThreshold');
  SimpleBlobDetectorGetMinArea := CVBind(Handle, 'cv_features2d_simpleBlobDetectorGetMinArea');
  SimpleBlobDetectorSetMinArea := CVBind(Handle, 'cv_features2d_simpleBlobDetectorSetMinArea');
  CreateMSER := CVBind(Handle, 'cv_features2d_createMSER');
  DeleteMSER := CVBind(Handle, 'cv_features2d_deleteMSER');
  MserDetectRegions := CVBind(Handle, 'cv_features2d_mserDetectRegions');
  MserGetDelta := CVBind(Handle, 'cv_features2d_mserGetDelta');
  MserSetDelta := CVBind(Handle, 'cv_features2d_mserSetDelta');
  MserGetMinArea := CVBind(Handle, 'cv_features2d_mserGetMinArea');
  MserSetMinArea := CVBind(Handle, 'cv_features2d_mserSetMinArea');
  MserGetMaxArea := CVBind(Handle, 'cv_features2d_mserGetMaxArea');
  MserSetMaxArea := CVBind(Handle, 'cv_features2d_mserSetMaxArea');
  CreateGFTTDetector := CVBind(Handle, 'cv_features2d_createGFTTDetector');
  DeleteGFTTDetector := CVBind(Handle, 'cv_features2d_deleteGFTTDetector');
  GfttDetectorDetect := CVBind(Handle, 'cv_features2d_gfttDetectorDetect');
  GfttDetectorGetMaxCorners := CVBind(Handle, 'cv_features2d_gfttDetectorGetMaxCorners');
  GfttDetectorSetMaxCorners := CVBind(Handle, 'cv_features2d_gfttDetectorSetMaxCorners');
  GfttDetectorGetQualityLevel := CVBind(Handle, 'cv_features2d_gfttDetectorGetQualityLevel');
  GfttDetectorSetQualityLevel := CVBind(Handle, 'cv_features2d_gfttDetectorSetQualityLevel');
  GfttDetectorGetMinDistance := CVBind(Handle, 'cv_features2d_gfttDetectorGetMinDistance');
  GfttDetectorSetMinDistance := CVBind(Handle, 'cv_features2d_gfttDetectorSetMinDistance');
  CreateFastFeatureDetector := CVBind(Handle, 'cv_features2d_createFastFeatureDetector');
  DeleteFastFeatureDetector := CVBind(Handle, 'cv_features2d_deleteFastFeatureDetector');
  FastFeatureDetectorDetect := CVBind(Handle, 'cv_features2d_fastFeatureDetectorDetect');
  FastFeatureDetectorGetThreshold := CVBind(Handle, 'cv_features2d_fastFeatureDetectorGetThreshold');
  FastFeatureDetectorSetThreshold := CVBind(Handle, 'cv_features2d_fastFeatureDetectorSetThreshold');
  FastFeatureDetectorGetNonmaxSuppression := CVBind(Handle,
    'cv_features2d_fastFeatureDetectorGetNonmaxSuppression');
  FastFeatureDetectorSetNonmaxSuppression := CVBind(Handle,
    'cv_features2d_fastFeatureDetectorSetNonmaxSuppression');
  CreateAgastFeatureDetector := CVBind(Handle, 'cv_features2d_createAgastFeatureDetector');
  DeleteAgastFeatureDetector := CVBind(Handle, 'cv_features2d_deleteAgastFeatureDetector');
  AgastFeatureDetectorDetect := CVBind(Handle, 'cv_features2d_agastFeatureDetectorDetect');
  AgastFeatureDetectorGetThreshold := CVBind(Handle, 'cv_features2d_agastFeatureDetectorGetThreshold');
  AgastFeatureDetectorSetThreshold := CVBind(Handle, 'cv_features2d_agastFeatureDetectorSetThreshold');
  AgastFeatureDetectorGetNonmaxSuppression := CVBind(Handle,
    'cv_features2d_agastFeatureDetectorGetNonmaxSuppression');
  AgastFeatureDetectorSetNonmaxSuppression := CVBind(Handle,
    'cv_features2d_agastFeatureDetectorSetNonmaxSuppression');
  CreateKAZE := CVBind(Handle, 'cv_features2d_createKAZE');
  DeleteKAZE := CVBind(Handle, 'cv_features2d_deleteKAZE');
  KazeDetectAndCompute := CVBind(Handle, 'cv_features2d_kazeDetectAndCompute');
  KazeGetExtended := CVBind(Handle, 'cv_features2d_kazeGetExtended');
  KazeSetExtended := CVBind(Handle, 'cv_features2d_kazeSetExtended');
  KazeGetUpright := CVBind(Handle, 'cv_features2d_kazeGetUpright');
  KazeSetUpright := CVBind(Handle, 'cv_features2d_kazeSetUpright');
  KazeGetThreshold := CVBind(Handle, 'cv_features2d_kazeGetThreshold');
  KazeSetThreshold := CVBind(Handle, 'cv_features2d_kazeSetThreshold');
  KazeGetNOctaves := CVBind(Handle, 'cv_features2d_kazeGetNOctaves');
  KazeSetNOctaves := CVBind(Handle, 'cv_features2d_kazeSetNOctaves');
  CreateBOWKMeansTrainer := CVBind(Handle, 'cv_features2d_createBOWKMeansTrainer');
  DeleteBOWKMeansTrainer := CVBind(Handle, 'cv_features2d_deleteBOWKMeansTrainer');
  BowKMeansTrainerAdd := CVBind(Handle, 'cv_features2d_bowKMeansTrainerAdd');
  BowKMeansTrainerCluster := CVBind(Handle, 'cv_features2d_bowKMeansTrainerCluster');
  BowKMeansTrainerGetDescriptors := CVBind(Handle, 'cv_features2d_bowKMeansTrainerGetDescriptors');
  BowKMeansTrainerDescriptorsCount := CVBind(Handle, 'cv_features2d_bowKMeansTrainerDescriptorsCount');
  CreateBOWImgDescriptorExtractor := CVBind(Handle, 'cv_features2d_createBOWImgDescriptorExtractor');
  DeleteBOWImgDescriptorExtractor := CVBind(Handle, 'cv_features2d_deleteBOWImgDescriptorExtractor');
  BowImgDescriptorExtractorSetVocabulary := CVBind(Handle,
    'cv_features2d_bowImgDescriptorExtractorSetVocabulary');
  BowImgDescriptorExtractorCompute := CVBind(Handle, 'cv_features2d_bowImgDescriptorExtractorCompute');
  BowImgDescriptorExtractorVocabularyEmpty := CVBind(Handle,
    'cv_features2d_bowImgDescriptorExtractorVocabularyEmpty');
end;

end.
