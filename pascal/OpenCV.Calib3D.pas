{ ************************************************************************** }
{                                                                            }
{ OpenCV.Calib3D                                                             }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev (ypisareff@outlook.com)               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Calib3D;

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
  TCVCalib3DModule = record
  public
    type
      TCalibrateCamera = function(ObjectPoints, ImagePoints: PMat; ImageCount: Integer; ImageSize: TOCVSize;
        CameraMatrix, DistCoeffs, Rvecs, Tvecs: PMat; Flags: Integer; ReprojError: PDouble): LongBool; cdecl;
      TFindChessboardCorners = function(Image: TMat; PatternSize: TOCVSize; Corners: PMat; Flags: Integer;
        Found: PInteger): LongBool; cdecl;
      TDrawChessboardCorners = function(Image: PMat; PatternSize: TOCVSize; Corners: TMat;
        PatternWasFound: LongBool): LongBool; cdecl;
      TSolvePnP = function(ObjectPoints, ImagePoints: TMat; CameraMatrix, DistCoeffs: TMat; Rvec, Tvec: PMat;
        UseExtrinsicGuess: LongBool; Flags: Integer): LongBool; cdecl;
      TSolvePnPRansac = function(ObjectPoints, ImagePoints: TMat; CameraMatrix, DistCoeffs: TMat;
        Rvec, Tvec: PMat; UseExtrinsicGuess: LongBool; IterationsCount: Integer; ReprojectionError: Single;
        Confidence: Double; Inliers: PMat; Flags: Integer): LongBool; cdecl;
      TProjectPoints = function(ObjectPoints: TMat; Rvec, Tvec, CameraMatrix, DistCoeffs: TMat;
        ImagePoints: PMat): LongBool; cdecl;
      TRodrigues = function(Source: TMat; Target, Jacobian: PMat): LongBool; cdecl;
      TStereoCalibrate = function(ObjectPoints, ImagePoints1, ImagePoints2: PMat; ImageCount: Integer;
        CameraMatrix1, DistCoeffs1, CameraMatrix2, DistCoeffs2: PMat; ImageSize: TOCVSize; R, T, E, F: PMat;
        Flags: Integer; ReprojError: PDouble): LongBool; cdecl;
      TStereoRectify = function(CameraMatrix1, DistCoeffs1, CameraMatrix2, DistCoeffs2: TMat;
        ImageSize: TOCVSize; R, T: TMat; R1, R2, P1, P2, Q: PMat; Flags: Integer; Alpha: Double;
        NewImageSize: TOCVSize): LongBool; cdecl;
      TInitUndistortRectifyMap = function(CameraMatrix, DistCoeffs, R, NewCameraMatrix: TMat; Size: TOCVSize;
        M1Type: Integer; Map1, Map2: PMat): LongBool; cdecl;
      TUndistort = function(Source: TMat; Target: PMat; CameraMatrix, DistCoeffs: TMat;
        NewCameraMatrix: TMat): LongBool; cdecl;
      TFindFundamentalMat = function(Points1, Points2: TMat; Target: PMat; Method: Integer;
        RansacReprojThreshold, Confidence: Double; Mask: PMat): LongBool; cdecl;
      TFindEssentialMat = function(Points1, Points2: TMat; CameraMatrix: TMat; Method: Integer;
        Prob, Threshold: Double; Mask: PMat; Target: PMat): LongBool; cdecl;
      TDecomposeEssentialMat = function(E: TMat; R1, R2, T: PMat): LongBool; cdecl;
      TTriangulatePoints = function(ProjMatr1, ProjMatr2, ProjPoints1, ProjPoints2: TMat;
        Points4D: PMat): LongBool; cdecl;
      TFindChessboardCornersSB = function(Image: TMat; PatternW, PatternH: Integer; Corners: PMat;
        Flags: Integer): LongBool; cdecl;
      TFindCirclesGrid = function(Image: TMat; PatternW, PatternH: Integer; Centers: PMat;
        Flags: Integer): LongBool; cdecl;
      TRecoverPose = function(E, Points1, Points2, CameraMatrix: TMat; R, T, Mask: PMat): LongBool; cdecl;
      TComputeCorrespondEpilines = function(Points: TMat; WhichImage: Integer; F: TMat;
        Lines: PMat): LongBool; cdecl;
      TConvertPointsFromHomogeneous = function(Source: TMat; Target: PMat): LongBool; cdecl;
      TConvertPointsToHomogeneous = function(Source: TMat; Target: PMat): LongBool; cdecl;
      TUndistortPoints = function(Source: TMat; Target: PMat;
        CameraMatrix, DistCoeffs, R, P: TMat): LongBool; cdecl;
      TEstimateAffine3D = function(Source, Target: TMat; Out_, Inliers: PMat;
        RansacThreshold, Confidence: Double): LongBool; cdecl;
      TEstimateAffine2D = function(Source, Target: TMat; Inliers: PMat; Method: Integer;
        RansacReprojThreshold: Double; MaxIters: Integer; Confidence: Double;
        RefineIters: Integer): LongBool; cdecl;
      TEstimateAffine2DWithTransform = function(Source, Target: TMat; Inliers: PMat; Method: Integer;
        RansacReprojThreshold: Double; MaxIters: Integer; Confidence: Double; RefineIters: Integer;
        Output: PMat): LongBool; cdecl;
      TGetOptimalNewCameraMatrix = function(CameraMatrix, DistCoeffs: TMat; ImageW, ImageH: Integer;
        Alpha: Double; NewImageW, NewImageH: Integer; ValidPixROI: POCVRect; CenterPrincipalPoint: LongBool;
        Result: PMat): LongBool; cdecl;
      TCalibrateCameraExtended = function(ObjectPoints, ImagePoints: PMat; ImageCount, HSize, VSize: Integer;
        CameraMatrix, DistCoeffs: PMat; Rvecs, Tvecs: PMat;
        StdDeviationsIntrinsics, StdDeviationsExtrinsics, PerViewErrors: PMat;
        Flags: Integer): LongBool; cdecl;
      TCalibrateHandEye = function(R_Gripper2Base, T_Gripper2Base, R_Target2Cam, T_Target2Cam: PMat;
        Count: Integer; R_Cam2Gripper, T_Cam2Gripper: PMat; Method: Integer): LongBool; cdecl;
      TCalibrateRobotWorldHandEye = function(R_World2Cam, T_World2Cam, R_Base2Gripper, T_Base2Gripper: PMat;
        Count: Integer; R_Base2World, T_Base2World, R_Gripper2Cam, T_Gripper2Cam: PMat;
        Method: Integer): LongBool; cdecl;
      TComposeRT = function(Rvec1, Tvec1, Rvec2, Tvec2: TMat; Rvec3, Tvec3: PMat): LongBool; cdecl;
      TDecomposeHomographyMat = function(H, K: TMat; Rotations, Translations, Normals: PMat;
        Count: PInteger): LongBool; cdecl;
      TDecomposeProjectionMatrix = function(ProjMatrix: TMat;
        CameraMatrix, RotMatrix, TransVect: PMat): LongBool; cdecl;
      TDrawFrameAxes = function(Image: PMat; CameraMatrix, DistCoeffs, Rvec, Tvec: TMat; Length: Single;
        Thickness: Integer): LongBool; cdecl;
      TEstimateAffinePartial2D = function(Source, Target: TMat; Inliers: PMat; Method: Integer;
        RansacReprojThreshold: Double; MaxIters: Integer; Confidence: Double; RefineIters: Integer;
        Output: PMat): LongBool; cdecl;
      TEstimateTranslation3D = function(Source, Target: TMat; Out_, Inliers: PMat;
        RansacThreshold, Confidence: Double): LongBool; cdecl;
      TFilterSpeckles = function(Image: PMat; NewVal: Double; MaxSpeckleSize: Integer; MaxDiff: Double;
        Buf: PMat): LongBool; cdecl;
      TFind4QuadCornerSubpix = function(Image: TMat; Corners: PMat;
        RegionSizeW, RegionSizeH: Integer): LongBool; cdecl;
      TFindTransformECC = function(TemplateImage, InputImage: TMat; WarpMatrix: PMat;
        MotionType, MaxCount: Integer; Epsilon: Double; InputMask: TMat;
        GaussFiltSize: Integer): LongBool; cdecl;
      TInitCameraMatrix2D = function(ObjectPoints, ImagePoints: PMat; Count, HSize, VSize: Integer;
        AspectRatio: Double; CameraMatrix: PMat): LongBool; cdecl;
      TInitInverseRectificationMap = function(CameraMatrix, DistCoeffs, R, NewCameraMatrix: TMat;
        HSize, VSize, M1Type: Integer; Map1, Map2: PMat): LongBool; cdecl;
      TMatMulDeriv = function(A, B: TMat; DABdA, DABdB: PMat): LongBool; cdecl;
      TRQDecomp3x3 = function(Source: TMat; MtxR, MtxQ, Qx, Qy, Qz: PMat): LongBool; cdecl;
      TReprojectImageTo3D = function(Disparity: TMat; Image3D: PMat; Q: TMat; HandleMissingValues: LongBool;
        DDepth: Integer): LongBool; cdecl;
      TSampsonDistance = function(Pt1, Pt2, F: TMat; Distance: PDouble): LongBool; cdecl;
      TStereoRectifyUncalibrated = function(Points1, Points2, F: TMat; ImgW, ImgH: Integer; H1, H2: PMat;
        Threshold: Double): LongBool; cdecl;
      TStereoCalibrateExtended = function(ObjectPoints, ImagePoints1, ImagePoints2: PMat; Count: Integer;
        CameraMatrix1, DistCoeffs1, CameraMatrix2, DistCoeffs2: PMat; HSize, VSize: Integer;
        R, T, E, F, PerViewErrors: PMat; Flags: Integer): LongBool; cdecl;
      TSolveP3P = function(ObjectPoints, ImagePoints: TMat; CameraMatrix, DistCoeffs: TMat;
        Rvecs, Tvecs: PMat; SolutionCount: PInteger; Flags: Integer): LongBool; cdecl;
      TSolvePnPGeneric = function(ObjectPoints, ImagePoints: TMat; CameraMatrix, DistCoeffs: TMat;
        Rvecs, Tvecs: PMat; SolutionCount: PInteger; UseExtrinsicGuess: LongBool; Flags: Integer;
        Rvec, Tvec, ReprojectionError: PMat): LongBool; cdecl;
      TSolvePnPRefineLM = function(ObjectPoints, ImagePoints: TMat; CameraMatrix, DistCoeffs: TMat;
        Rvec, Tvec: PMat): LongBool; cdecl;
      TSolvePnPRefineVVS = function(ObjectPoints, ImagePoints: TMat; CameraMatrix, DistCoeffs: TMat;
        Rvec, Tvec: PMat; Lambda: Double; MaxCount: Integer; Epsilon: Double): LongBool; cdecl;
      TValidateDisparity = function(Disparity, Cost: PMat;
        MinDisparity, NumberOfDisparities, Disp12MaxDiff: Integer): LongBool; cdecl;
      TCreateStereoBM = function(NumDisparities, BlockSize: Integer): Pointer; cdecl;
      TDeleteStereoBM = function(Handle: Pointer): LongBool; cdecl;
      TStereoBMCompute = function(Handle: Pointer; Left, Right: TMat; Disparity: PMat): LongBool; cdecl;
      TStereoBMGetMinDisparity = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetMinDisparity = function(Handle: Pointer; MinDisparity: Integer): LongBool; cdecl;
      TStereoBMGetNumDisparities = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetNumDisparities = function(Handle: Pointer; NumDisparities: Integer): LongBool; cdecl;
      TStereoBMGetBlockSize = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetBlockSize = function(Handle: Pointer; BlockSize: Integer): LongBool; cdecl;
      TStereoBMGetSpeckleWindowSize = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetSpeckleWindowSize = function(Handle: Pointer; SpeckleWindowSize: Integer): LongBool; cdecl;
      TStereoBMGetSpeckleRange = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetSpeckleRange = function(Handle: Pointer; SpeckleRange: Integer): LongBool; cdecl;
      TStereoBMGetDisp12MaxDiff = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetDisp12MaxDiff = function(Handle: Pointer; Disp12MaxDiff: Integer): LongBool; cdecl;
      TStereoBMGetPreFilterType = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetPreFilterType = function(Handle: Pointer; PreFilterType: Integer): LongBool; cdecl;
      TStereoBMGetPreFilterSize = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetPreFilterSize = function(Handle: Pointer; PreFilterSize: Integer): LongBool; cdecl;
      TStereoBMGetPreFilterCap = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetPreFilterCap = function(Handle: Pointer; PreFilterCap: Integer): LongBool; cdecl;
      TStereoBMGetTextureThreshold = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetTextureThreshold = function(Handle: Pointer; TextureThreshold: Integer): LongBool; cdecl;
      TStereoBMGetUniquenessRatio = function(Handle: Pointer): Integer; cdecl;
      TStereoBMSetUniquenessRatio = function(Handle: Pointer; UniquenessRatio: Integer): LongBool; cdecl;
      TCreateStereoSGBM = function(MinDisparity, NumDisparities, BlockSize, P1, P2, Disp12MaxDiff, PreFilterCap, UniquenessRatio, SpeckleWindowSize, SpeckleRange, Mode: Integer): Pointer; cdecl;
      TDeleteStereoSGBM = function(Handle: Pointer): LongBool; cdecl;
      TStereoSGBMCompute = function(Handle: Pointer; Left, Right: TMat; Disparity: PMat): LongBool; cdecl;
      TStereoSGBMGetMode = function(Handle: Pointer): Integer; cdecl;
      TStereoSGBMSetMode = function(Handle: Pointer; Mode: Integer): LongBool; cdecl;
      TStereoSGBMGetP1 = function(Handle: Pointer): Integer; cdecl;
      TStereoSGBMSetP1 = function(Handle: Pointer; P1: Integer): LongBool; cdecl;
      TStereoSGBMGetP2 = function(Handle: Pointer): Integer; cdecl;
      TStereoSGBMSetP2 = function(Handle: Pointer; P2: Integer): LongBool; cdecl;
      TStereoSGBMGetMinDisparity = function(Handle: Pointer): Integer; cdecl;
      TStereoSGBMSetMinDisparity = function(Handle: Pointer; MinDisparity: Integer): LongBool; cdecl;
      TStereoSGBMGetNumDisparities = function(Handle: Pointer): Integer; cdecl;
      TStereoSGBMSetNumDisparities = function(Handle: Pointer; NumDisparities: Integer): LongBool; cdecl;
      TStereoSGBMGetUniquenessRatio = function(Handle: Pointer): Integer; cdecl;
      TStereoSGBMSetUniquenessRatio = function(Handle: Pointer; UniquenessRatio: Integer): LongBool; cdecl;
    var
      CalibrateCamera: TCalibrateCamera;
      FindChessboardCorners: TFindChessboardCorners;
      DrawChessboardCorners: TDrawChessboardCorners;
      SolvePnP: TSolvePnP;
      SolvePnPRansac: TSolvePnPRansac;
      ProjectPoints: TProjectPoints;
      Rodrigues: TRodrigues;
      StereoCalibrate: TStereoCalibrate;
      StereoRectify: TStereoRectify;
      InitUndistortRectifyMap: TInitUndistortRectifyMap;
      Undistort: TUndistort;
      FindFundamentalMat: TFindFundamentalMat;
      FindEssentialMat: TFindEssentialMat;
      DecomposeEssentialMat: TDecomposeEssentialMat;
      TriangulatePoints: TTriangulatePoints;
      FindChessboardCornersSB: TFindChessboardCornersSB;
      FindCirclesGrid: TFindCirclesGrid;
      RecoverPose: TRecoverPose;
      ComputeCorrespondEpilines: TComputeCorrespondEpilines;
      ConvertPointsFromHomogeneous: TConvertPointsFromHomogeneous;
      ConvertPointsToHomogeneous: TConvertPointsToHomogeneous;
      UndistortPoints: TUndistortPoints;
      EstimateAffine3D: TEstimateAffine3D;
      EstimateAffine2D: TEstimateAffine2D; { Inliers only. }
      GetOptimalNewCameraMatrix: TGetOptimalNewCameraMatrix;
      CalibrateCameraExtended: TCalibrateCameraExtended;
      CalibrateHandEye: TCalibrateHandEye;
      CalibrateRobotWorldHandEye: TCalibrateRobotWorldHandEye;
      ComposeRT: TComposeRT;
      DecomposeHomographyMat: TDecomposeHomographyMat;
      DecomposeProjectionMatrix: TDecomposeProjectionMatrix;
      DrawFrameAxes: TDrawFrameAxes;
      EstimateAffinePartial2D: TEstimateAffinePartial2D;
      EstimateTranslation3D: TEstimateTranslation3D;
      FilterSpeckles: TFilterSpeckles;
      Find4QuadCornerSubpix: TFind4QuadCornerSubpix;
      FindTransformECC: TFindTransformECC;
      InitCameraMatrix2D: TInitCameraMatrix2D;
      InitInverseRectificationMap: TInitInverseRectificationMap;
      MatMulDeriv: TMatMulDeriv;
      RQDecomp3x3: TRQDecomp3x3;
      ReprojectImageTo3D: TReprojectImageTo3D;
      SampsonDistance: TSampsonDistance;
      StereoRectifyUncalibrated: TStereoRectifyUncalibrated;
      StereoCalibrateExtended: TStereoCalibrateExtended;
      SolveP3P: TSolveP3P;
      SolvePnPGeneric: TSolvePnPGeneric;
      SolvePnPRefineLM: TSolvePnPRefineLM;
      SolvePnPRefineVVS: TSolvePnPRefineVVS;
      ValidateDisparity: TValidateDisparity;
      CreateStereoBM: TCreateStereoBM;
      DeleteStereoBM: TDeleteStereoBM;
      StereoBMCompute: TStereoBMCompute;
      StereoBMGetMinDisparity: TStereoBMGetMinDisparity;
      StereoBMSetMinDisparity: TStereoBMSetMinDisparity;
      StereoBMGetNumDisparities: TStereoBMGetNumDisparities;
      StereoBMSetNumDisparities: TStereoBMSetNumDisparities;
      StereoBMGetBlockSize: TStereoBMGetBlockSize;
      StereoBMSetBlockSize: TStereoBMSetBlockSize;
      StereoBMGetSpeckleWindowSize: TStereoBMGetSpeckleWindowSize;
      StereoBMSetSpeckleWindowSize: TStereoBMSetSpeckleWindowSize;
      StereoBMGetSpeckleRange: TStereoBMGetSpeckleRange;
      StereoBMSetSpeckleRange: TStereoBMSetSpeckleRange;
      StereoBMGetDisp12MaxDiff: TStereoBMGetDisp12MaxDiff;
      StereoBMSetDisp12MaxDiff: TStereoBMSetDisp12MaxDiff;
      StereoBMGetPreFilterType: TStereoBMGetPreFilterType;
      StereoBMSetPreFilterType: TStereoBMSetPreFilterType;
      StereoBMGetPreFilterSize: TStereoBMGetPreFilterSize;
      StereoBMSetPreFilterSize: TStereoBMSetPreFilterSize;
      StereoBMGetPreFilterCap: TStereoBMGetPreFilterCap;
      StereoBMSetPreFilterCap: TStereoBMSetPreFilterCap;
      StereoBMGetTextureThreshold: TStereoBMGetTextureThreshold;
      StereoBMSetTextureThreshold: TStereoBMSetTextureThreshold;
      StereoBMGetUniquenessRatio: TStereoBMGetUniquenessRatio;
      StereoBMSetUniquenessRatio: TStereoBMSetUniquenessRatio;
      CreateStereoSGBM: TCreateStereoSGBM;
      DeleteStereoSGBM: TDeleteStereoSGBM;
      StereoSGBMCompute: TStereoSGBMCompute;
      StereoSGBMGetMode: TStereoSGBMGetMode;
      StereoSGBMSetMode: TStereoSGBMSetMode;
      StereoSGBMGetP1: TStereoSGBMGetP1;
      StereoSGBMSetP1: TStereoSGBMSetP1;
      StereoSGBMGetP2: TStereoSGBMGetP2;
      StereoSGBMSetP2: TStereoSGBMSetP2;
      StereoSGBMGetMinDisparity: TStereoSGBMGetMinDisparity;
      StereoSGBMSetMinDisparity: TStereoSGBMSetMinDisparity;
      StereoSGBMGetNumDisparities: TStereoSGBMGetNumDisparities;
      StereoSGBMSetNumDisparities: TStereoSGBMSetNumDisparities;
      StereoSGBMGetUniquenessRatio: TStereoSGBMGetUniquenessRatio;
      StereoSGBMSetUniquenessRatio: TStereoSGBMSetUniquenessRatio;
      { On success, release both the inlier mask and transform with Core.DeleteMat. }
      { Available when the OpenCV bridge exports the extended function. }
      EstimateAffine2DWithTransform: TEstimateAffine2DWithTransform;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVCalib3DModule.Initialize(const Handle: TLibHandle);
begin
  CalibrateCamera := CVBind(Handle, 'cv_calib3d_calibrateCamera');
  FindChessboardCorners := CVBind(Handle, 'cv_calib3d_findChessboardCorners');
  DrawChessboardCorners := CVBind(Handle, 'cv_calib3d_drawChessboardCorners');
  SolvePnP := CVBind(Handle, 'cv_calib3d_solvePnP');
  SolvePnPRansac := CVBind(Handle, 'cv_calib3d_solvePnPRansac');
  ProjectPoints := CVBind(Handle, 'cv_calib3d_projectPoints');
  Rodrigues := CVBind(Handle, 'cv_calib3d_rodrigues');
  StereoCalibrate := CVBind(Handle, 'cv_calib3d_stereoCalibrate');
  StereoRectify := CVBind(Handle, 'cv_calib3d_stereoRectify');
  InitUndistortRectifyMap := CVBind(Handle, 'cv_calib3d_initUndistortRectifyMap');
  Undistort := CVBind(Handle, 'cv_calib3d_undistort');
  FindFundamentalMat := CVBind(Handle, 'cv_calib3d_findFundamentalMat');
  FindEssentialMat := CVBind(Handle, 'cv_calib3d_findEssentialMat');
  DecomposeEssentialMat := CVBind(Handle, 'cv_calib3d_decomposeEssentialMat');
  TriangulatePoints := CVBind(Handle, 'cv_calib3d_triangulatePoints');
  FindChessboardCornersSB := CVBind(Handle, 'cv_calib3d_findChessboardCornersSB');
  FindCirclesGrid := CVBind(Handle, 'cv_calib3d_findCirclesGrid');
  RecoverPose := CVBind(Handle, 'cv_calib3d_recoverPose');
  ComputeCorrespondEpilines := CVBind(Handle, 'cv_calib3d_computeCorrespondEpilines');
  ConvertPointsFromHomogeneous := CVBind(Handle, 'cv_calib3d_convertPointsFromHomogeneous');
  ConvertPointsToHomogeneous := CVBind(Handle, 'cv_calib3d_convertPointsToHomogeneous');
  UndistortPoints := CVBind(Handle, 'cv_calib3d_undistortPoints');
  EstimateAffine3D := CVBind(Handle, 'cv_calib3d_estimateAffine3D');
  EstimateAffine2D := CVBind(Handle, 'cv_calib3d_estimateAffine2D');
  {$IFDEF FPC}
  EstimateAffine2DWithTransform := GetProcAddress(Handle, 'cv_calib3d_estimateAffine2DWithTransform');
  {$ELSE}
  EstimateAffine2DWithTransform := Pointer(GetProcAddress(Handle,
    'cv_calib3d_estimateAffine2DWithTransform'));
  {$ENDIF}
  GetOptimalNewCameraMatrix := CVBind(Handle, 'cv_calib3d_getOptimalNewCameraMatrix');
  CalibrateCameraExtended := CVBind(Handle, 'cv_calib3d_calibrateCameraExtended');
  CalibrateHandEye := CVBind(Handle, 'cv_calib3d_calibrateHandEye');
  CalibrateRobotWorldHandEye := CVBind(Handle, 'cv_calib3d_calibrateRobotWorldHandEye');
  ComposeRT := CVBind(Handle, 'cv_calib3d_composeRT');
  DecomposeHomographyMat := CVBind(Handle, 'cv_calib3d_decomposeHomographyMat');
  DecomposeProjectionMatrix := CVBind(Handle, 'cv_calib3d_decomposeProjectionMatrix');
  DrawFrameAxes := CVBind(Handle, 'cv_calib3d_drawFrameAxes');
  EstimateAffinePartial2D := CVBind(Handle, 'cv_calib3d_estimateAffinePartial2D');
  EstimateTranslation3D := CVBind(Handle, 'cv_calib3d_estimateTranslation3D');
  FilterSpeckles := CVBind(Handle, 'cv_calib3d_filterSpeckles');
  Find4QuadCornerSubpix := CVBind(Handle, 'cv_calib3d_find4QuadCornerSubpix');
  FindTransformECC := CVBind(Handle, 'cv_calib3d_findTransformECC');
  InitCameraMatrix2D := CVBind(Handle, 'cv_calib3d_initCameraMatrix2D');
  InitInverseRectificationMap := CVBind(Handle, 'cv_calib3d_initInverseRectificationMap');
  MatMulDeriv := CVBind(Handle, 'cv_calib3d_matMulDeriv');
  RQDecomp3x3 := CVBind(Handle, 'cv_calib3d_RQDecomp3x3');
  ReprojectImageTo3D := CVBind(Handle, 'cv_calib3d_reprojectImageTo3D');
  SampsonDistance := CVBind(Handle, 'cv_calib3d_sampsonDistance');
  StereoRectifyUncalibrated := CVBind(Handle, 'cv_calib3d_stereoRectifyUncalibrated');
  StereoCalibrateExtended := CVBind(Handle, 'cv_calib3d_stereoCalibrateExtended');
  SolveP3P := CVBind(Handle, 'cv_calib3d_solveP3P');
  SolvePnPGeneric := CVBind(Handle, 'cv_calib3d_solvePnPGeneric');
  SolvePnPRefineLM := CVBind(Handle, 'cv_calib3d_solvePnPRefineLM');
  SolvePnPRefineVVS := CVBind(Handle, 'cv_calib3d_solvePnPRefineVVS');
  ValidateDisparity := CVBind(Handle, 'cv_calib3d_validateDisparity');
  CreateStereoBM := CVBind(Handle, 'cv_calib3d_createStereoBM');
  DeleteStereoBM := CVBind(Handle, 'cv_calib3d_deleteStereoBM');
  StereoBMCompute := CVBind(Handle, 'cv_calib3d_stereoBMCompute');
  StereoBMGetMinDisparity := CVBind(Handle, 'cv_calib3d_stereoBMGetMinDisparity');
  StereoBMSetMinDisparity := CVBind(Handle, 'cv_calib3d_stereoBMSetMinDisparity');
  StereoBMGetNumDisparities := CVBind(Handle, 'cv_calib3d_stereoBMGetNumDisparities');
  StereoBMSetNumDisparities := CVBind(Handle, 'cv_calib3d_stereoBMSetNumDisparities');
  StereoBMGetBlockSize := CVBind(Handle, 'cv_calib3d_stereoBMGetBlockSize');
  StereoBMSetBlockSize := CVBind(Handle, 'cv_calib3d_stereoBMSetBlockSize');
  StereoBMGetSpeckleWindowSize := CVBind(Handle, 'cv_calib3d_stereoBMGetSpeckleWindowSize');
  StereoBMSetSpeckleWindowSize := CVBind(Handle, 'cv_calib3d_stereoBMSetSpeckleWindowSize');
  StereoBMGetSpeckleRange := CVBind(Handle, 'cv_calib3d_stereoBMGetSpeckleRange');
  StereoBMSetSpeckleRange := CVBind(Handle, 'cv_calib3d_stereoBMSetSpeckleRange');
  StereoBMGetDisp12MaxDiff := CVBind(Handle, 'cv_calib3d_stereoBMGetDisp12MaxDiff');
  StereoBMSetDisp12MaxDiff := CVBind(Handle, 'cv_calib3d_stereoBMSetDisp12MaxDiff');
  StereoBMGetPreFilterType := CVBind(Handle, 'cv_calib3d_stereoBMGetPreFilterType');
  StereoBMSetPreFilterType := CVBind(Handle, 'cv_calib3d_stereoBMSetPreFilterType');
  StereoBMGetPreFilterSize := CVBind(Handle, 'cv_calib3d_stereoBMGetPreFilterSize');
  StereoBMSetPreFilterSize := CVBind(Handle, 'cv_calib3d_stereoBMSetPreFilterSize');
  StereoBMGetPreFilterCap := CVBind(Handle, 'cv_calib3d_stereoBMGetPreFilterCap');
  StereoBMSetPreFilterCap := CVBind(Handle, 'cv_calib3d_stereoBMSetPreFilterCap');
  StereoBMGetTextureThreshold := CVBind(Handle, 'cv_calib3d_stereoBMGetTextureThreshold');
  StereoBMSetTextureThreshold := CVBind(Handle, 'cv_calib3d_stereoBMSetTextureThreshold');
  StereoBMGetUniquenessRatio := CVBind(Handle, 'cv_calib3d_stereoBMGetUniquenessRatio');
  StereoBMSetUniquenessRatio := CVBind(Handle, 'cv_calib3d_stereoBMSetUniquenessRatio');
  CreateStereoSGBM := CVBind(Handle, 'cv_calib3d_createStereoSGBM');
  DeleteStereoSGBM := CVBind(Handle, 'cv_calib3d_deleteStereoSGBM');
  StereoSGBMCompute := CVBind(Handle, 'cv_calib3d_stereoSGBMCompute');
  StereoSGBMGetMode := CVBind(Handle, 'cv_calib3d_stereoSGBMGetMode');
  StereoSGBMSetMode := CVBind(Handle, 'cv_calib3d_stereoSGBMSetMode');
  StereoSGBMGetP1 := CVBind(Handle, 'cv_calib3d_stereoSGBMGetP1');
  StereoSGBMSetP1 := CVBind(Handle, 'cv_calib3d_stereoSGBMSetP1');
  StereoSGBMGetP2 := CVBind(Handle, 'cv_calib3d_stereoSGBMGetP2');
  StereoSGBMSetP2 := CVBind(Handle, 'cv_calib3d_stereoSGBMSetP2');
  StereoSGBMGetMinDisparity := CVBind(Handle, 'cv_calib3d_stereoSGBMGetMinDisparity');
  StereoSGBMSetMinDisparity := CVBind(Handle, 'cv_calib3d_stereoSGBMSetMinDisparity');
  StereoSGBMGetNumDisparities := CVBind(Handle, 'cv_calib3d_stereoSGBMGetNumDisparities');
  StereoSGBMSetNumDisparities := CVBind(Handle, 'cv_calib3d_stereoSGBMSetNumDisparities');
  StereoSGBMGetUniquenessRatio := CVBind(Handle, 'cv_calib3d_stereoSGBMGetUniquenessRatio');
  StereoSGBMSetUniquenessRatio := CVBind(Handle, 'cv_calib3d_stereoSGBMSetUniquenessRatio');
end;

end.
