{ ************************************************************************** }
{                                                                            }
{ OpenCV.Custom                                                              }
{                                                                            }
{ Copyright © 2025, 2026 Yuriy Pisarev               }
{                                                                            }
{ ************************************************************************** }

unit OpenCV.Custom;

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
  TCVCustomModule = record
  public
    type
      TSetData = function(Count: Integer; Data: Pointer): Pointer; cdecl;
      TSetMat = function(var Scale, Angle: Double; Place: TOCVPlace; Image, Slice: PMat;
        Index, Count: Integer; Data: Pointer): Integer; cdecl;
      TToDoxaImage = function(Source: TMat; Target: PPointer): LongBool; cdecl;
      TFromDoxaImage = function(Source: Pointer; Target: PMat): LongBool; cdecl;
      TDeleteDoxaImage = function(Source: Pointer): LongBool; cdecl;
      TDoxaThreshold = function(Source: Pointer; Target: Pointer; Algorithm: Integer;
        K, Window, R: Double): LongBool; cdecl;
      TLocateTemplate = function(Source, Template: TMat; Threshold: Double; Method: Integer; Mask: TMat;
        &Set: TSetData; Data: Pointer): LongBool; cdecl;
      TSearchTemplate = function(Source, Template: TMat; Threshold: Double; Method: Integer; Mask: TMat;
        MaxResults: Integer; SetMat: TSetMat; Data: Pointer): LongBool; cdecl;
      TCreateCLAHE = function(ClipLimit: Double; TilesGridSize: TOCVSize; Handle: PPointer): LongBool; cdecl;
      TDeleteCLAHE = function(Handle: Pointer): LongBool; cdecl;
      TSetClipLimit = function(Handle: Pointer; ClipLimit: Double): LongBool; cdecl;
      TGetClipLimit = function(Handle: Pointer; ClipLimit: PDouble): LongBool; cdecl;
      TSetTilesGridSize = function(Handle: Pointer; TilesGridSize: TOCVSize): LongBool; cdecl;
      TGetTilesGridSize = function(Handle: Pointer; TilesGridSize: POCVSize): LongBool; cdecl;
      TCollectGarbage = function(Handle: Pointer): LongBool; cdecl;
      TClaheApply = function(Handle: Pointer; Source: TMat; Target: PMat): LongBool; cdecl;
      TVarianceOfLaplacian = function(Source: TMat; Value: PDouble): LongBool; cdecl;
      TTenengrad = function(Source: TMat; KSize: Integer; Value: PDouble): LongBool; cdecl;
      TNormalizedGrayLevelVariance = function(Source: TMat; Value: PDouble): LongBool; cdecl;
      TCreateBGSSubtractor = function(Algorithm: Integer; Handle: PPointer): LongBool; cdecl;
      TDeleteBGSSubtractor = function(Handle: Pointer): LongBool; cdecl;
      TSubtractorBGSApply = function(Handle: Pointer; Image: TMat; FgMask: PMat): LongBool; cdecl;
      TResizeWithAspectRatio = procedure(Src: TMat; Dst: PMat; Width, Height, Interpolation: Integer); cdecl;
      TDrawCrosshair = procedure(Img: PMat; Center: TOCVPoint; Size: Integer; Color: TOCVScalar;
        Thickness: Integer); cdecl;
      TMatToArray = procedure(Mat: TMat; Data: PSingle; Count: PInteger); cdecl;
      TArrayToMat = procedure(Data: PSingle; Rows, Cols, &Type: Integer; Mat: PMat); cdecl;
      TConcatHorizontal = procedure(Src1, Src2: TMat; Dst: PMat); cdecl;
      TConcatVertical = procedure(Src1, Src2: TMat; Dst: PMat); cdecl;
      TDrawGrid = procedure(Img: PMat; Rows, Cols: Integer; Color: TOCVScalar; Thickness: Integer); cdecl;
      TCalculateHistogramImage = procedure(Src: TMat; HistImg: PMat; Width, Height: Integer); cdecl;
      TMaskOverlay = procedure(Src: TMat; Mask: TMat; Dst: PMat; Color: TOCVScalar; Alpha: Double); cdecl;
      TDrawDetections = procedure(Img: PMat; Rects: POCVRect; Count: Integer; Color: TOCVScalar;
        Thickness: Integer); cdecl;
    var
      ToDoxaImage: TToDoxaImage;
      FromDoxaImage: TFromDoxaImage;
      DeleteDoxaImage: TDeleteDoxaImage;
      DoxaThreshold: TDoxaThreshold;
      LocateTemplate: TLocateTemplate;
      SearchTemplate: TSearchTemplate;
      CreateCLAHE: TCreateCLAHE;
      DeleteCLAHE: TDeleteCLAHE;
      SetClipLimit: TSetClipLimit;
      GetClipLimit: TGetClipLimit;
      SetTilesGridSize: TSetTilesGridSize;
      GetTilesGridSize: TGetTilesGridSize;
      CollectGarbage: TCollectGarbage;
      ClaheApply: TClaheApply;
      VarianceOfLaplacian: TVarianceOfLaplacian;
      Tenengrad: TTenengrad;
      NormalizedGrayLevelVariance: TNormalizedGrayLevelVariance;
      CreateBGSSubtractor: TCreateBGSSubtractor;
      DeleteBGSSubtractor: TDeleteBGSSubtractor;
      SubtractorBGSApply: TSubtractorBGSApply;
      ResizeWithAspectRatio: TResizeWithAspectRatio;
      DrawCrosshair: TDrawCrosshair;
      MatToArray: TMatToArray;
      ArrayToMat: TArrayToMat;
      ConcatHorizontal: TConcatHorizontal;
      ConcatVertical: TConcatVertical;
      DrawGrid: TDrawGrid;
      CalculateHistogramImage: TCalculateHistogramImage;
      MaskOverlay: TMaskOverlay;
      DrawDetections: TDrawDetections;
    procedure Initialize(const Handle: TLibHandle);
  end;

implementation

procedure TCVCustomModule.Initialize(const Handle: TLibHandle);
begin
  ToDoxaImage := CVBind(Handle, 'cv_custom_toDoxaImage');
  FromDoxaImage := CVBind(Handle, 'cv_custom_fromDoxaImage');
  DeleteDoxaImage := CVBind(Handle, 'cv_custom_deleteDoxaImage');
  DoxaThreshold := CVBind(Handle, 'cv_custom_doxaThreshold');
  LocateTemplate := CVBind(Handle, 'cv_custom_locateTemplate');
  SearchTemplate := CVBind(Handle, 'cv_custom_searchTemplate');
  CreateCLAHE := CVBind(Handle, 'cv_custom_createCLAHE');
  DeleteCLAHE := CVBind(Handle, 'cv_custom_deleteCLAHE');
  SetClipLimit := CVBind(Handle, 'cv_custom_setClipLimit');
  GetClipLimit := CVBind(Handle, 'cv_custom_getClipLimit');
  SetTilesGridSize := CVBind(Handle, 'cv_custom_setTilesGridSize');
  GetTilesGridSize := CVBind(Handle, 'cv_custom_getTilesGridSize');
  CollectGarbage := CVBind(Handle, 'cv_custom_collectGarbage');
  ClaheApply := CVBind(Handle, 'cv_custom_claheApply');
  VarianceOfLaplacian := CVBind(Handle, 'cv_custom_varianceOfLaplacian');
  Tenengrad := CVBind(Handle, 'cv_custom_tenengrad');
  NormalizedGrayLevelVariance := CVBind(Handle, 'cv_custom_normalizedGrayLevelVariance');
  CreateBGSSubtractor := CVBind(Handle, 'cv_custom_createBGSSubtractor');
  DeleteBGSSubtractor := CVBind(Handle, 'cv_custom_deleteBGSSubtractor');
  SubtractorBGSApply := CVBind(Handle, 'cv_custom_subtractorBGSApply');
  ResizeWithAspectRatio := CVBind(Handle, 'cv_custom_resizeWithAspectRatio');
  DrawCrosshair := CVBind(Handle, 'cv_custom_drawCrosshair');
  MatToArray := CVBind(Handle, 'cv_custom_matToArray');
  ArrayToMat := CVBind(Handle, 'cv_custom_arrayToMat');
  ConcatHorizontal := CVBind(Handle, 'cv_custom_concatHorizontal');
  ConcatVertical := CVBind(Handle, 'cv_custom_concatVertical');
  DrawGrid := CVBind(Handle, 'cv_custom_drawGrid');
  CalculateHistogramImage := CVBind(Handle, 'cv_custom_calculateHistogramImage');
  MaskOverlay := CVBind(Handle, 'cv_custom_maskOverlay');
  DrawDetections := CVBind(Handle, 'cv_custom_drawDetections');
end;

end.
