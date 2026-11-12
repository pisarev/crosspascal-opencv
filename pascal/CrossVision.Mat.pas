{ ************************************************************************** }
{                                                                            }
{ CrossVision.Mat                                                            }
{                                                                            }
{ Copyright © 2026 Yuriy Pisarev                                             }
{                                                                            }
{ ************************************************************************** }

unit CrossVision.Mat;

interface

uses OpenCVTypes, OpenCVConsts;

type
  IMat = interface;
  TIMatArray = array of IMat;

  IMat = interface
    ['{7C2A1B30-9D4E-4F1A-8B2C-1E3F5A6D7C80}']
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetChannels: Integer;
    function GetDepth: Integer;
    function GetMatType: Integer;
    function GetTotal: Integer;
    function GetElemSize: Integer;
    function GetStep: Integer;
    function IsEmpty: Boolean;
    function Raw: TMat;
    function DataPtr: Pointer;
    function Pixel(const X, Y: Integer): Byte;
    function ToGray: IMat;
    function CvtColor(const Code: Integer): IMat;
    function Clone: IMat;
    function ConvertTo(const NewType: Integer; const Alpha: Double = 1; const Beta: Double = 0): IMat;
    function ConvertScaleAbs(const Alpha: Double = 1; const Beta: Double = 0): IMat;
    function Fill(const V0: Double; const V1: Double = 0; const V2: Double = 0; const V3: Double = 0): IMat;
    function Crop(const X, Y, W, H: Integer): IMat;
    function Add(const Other: IMat): IMat;
    function Subtract(const Other: IMat): IMat;
    function Multiply(const Other: IMat): IMat;
    function Divide(const Other: IMat): IMat;
    function AbsDiff(const Other: IMat): IMat;
    function Min(const Other: IMat): IMat;
    function Max(const Other: IMat): IMat;
    function AddWeighted(const Alpha: Double; const Other: IMat; const Beta, Gamma: Double): IMat;
    function ScaleAdd(const Alpha: Double; const Other: IMat): IMat;
    function Pow(const Power: Double): IMat;
    function Sqrt: IMat;
    function Exp: IMat;
    function Log: IMat;
    function BitwiseNot: IMat;
    function BitwiseAnd(const Other: IMat): IMat;
    function BitwiseOr(const Other: IMat): IMat;
    function BitwiseXor(const Other: IMat): IMat;
    function Threshold(const Thresh: Integer): IMat;
    function ThresholdEx(const Thresh, MaxVal: Double; const ThreshType: Integer): IMat;
    function AdaptiveThreshold(const BlockSize: Integer; const C: Double): IMat;
    function Compare(const Other: IMat; const CmpOp: Integer): IMat;
    function InRange(const Lo, Hi: TOCVScalar): IMat;
    function CountNonZero: Integer;
    function MinValue: Double;
    function MaxValue: Double;
    function MinMaxLoc(out MinV, MaxV: Double; out MinLoc, MaxLoc: TOCVPoint): Boolean;
    function SumScalar: TOCVScalar;
    function MeanScalar: TOCVScalar;
    function MeanValue: Double;
    function Norm(const NormType: Integer = 4): Double;
    function Normalize(const Alpha, Beta: Double; const NormType: Integer = 32): IMat;
    function Reduce(const Dim, ReduceType: Integer): IMat;
    function Transpose: IMat;
    function Invert(const Flags: Integer = 0): IMat;
    function Determinant: Double;
    function Trace: TOCVScalar;
    function MatMul(const Other: IMat): IMat;
    function Split: TIMatArray;
    function ExtractChannel(const Index: Integer): IMat;
    function Resize(const NewWidth, NewHeight: Integer; const Interpolation: Integer = INTER_LINEAR): IMat;
    function Flip(const FlipCode: Integer): IMat;
    function Tile(const Ny, Nx: Integer): IMat;
    function Rotate90(const RotateCode: Integer): IMat;
    function CopyMakeBorder(const Top, Bottom, Left, Right: Integer; const BorderType: Integer = 0): IMat;
    function HConcat(const Other: IMat): IMat;
    function VConcat(const Other: IMat): IMat;
    function WarpAffine(const M: IMat; const W, H: Integer): IMat;
    function WarpPerspective(const M: IMat; const W, H: Integer): IMat;
    function GaussianBlur(const KernelSize: Integer): IMat;
    function MedianBlur(const KernelSize: Integer): IMat;
    function Blur(const KernelSize: Integer): IMat;
    function BilateralFilter(const Diameter: Integer; const SigmaColor, SigmaSpace: Double): IMat;
    function Canny(const Threshold1, Threshold2: Integer): IMat;
    function Sobel(const Dx, Dy: Integer; const KernelSize: Integer = 3): IMat;
    function Scharr(const Dx, Dy: Integer): IMat;
    function Laplacian(const KernelSize: Integer = 1): IMat;
    function Erode(const Iterations: Integer = 1): IMat;
    function Dilate(const Iterations: Integer = 1): IMat;
    function MorphologyEx(const Op: Integer; const Iterations: Integer = 1): IMat;
    function ApplyLUT(const Lut: IMat): IMat;
    function Save(const Path: string): Boolean;
    property Width: Integer read GetWidth;
    property Height: Integer read GetHeight;
    property Channels: Integer read GetChannels;
    property Depth: Integer read GetDepth;
    property MatType: Integer read GetMatType;
    property Total: Integer read GetTotal;
    property ElemSize: Integer read GetElemSize;
    property Step: Integer read GetStep;
  end;

function LoadMat(const Path: string; const Color: Boolean = True): IMat;

function WrapMat(const Handle: TMat; const OwnsHandle: Boolean = True): IMat;

function NewMat(const Width, Height, MatType: Integer): IMat;

function ZerosMat(const Width, Height, MatType: Integer): IMat;

function MergeMats(const Mats: array of IMat): IMat;

function CopyRegionInto(const Source: IMat; const X, Y, W, H: Integer; const Target: IMat): Boolean;

function CopyInto(const Source, Target: IMat): Boolean;
function ExtractRegion(const Source: IMat; const X, Y, W, H: Integer): IMat;
function RegionView(const Source: IMat; const X, Y, W, H: Integer): IMat;

function MeanDarkAcross(const Source: IMat; const Horizontal: Boolean;
  const Position, Lo, Hi, Threshold: Integer): Integer;

function DarkBandBounds(const EdgeA, EdgeB, MaxWidth, Limit: Integer; out Lo, Hi: Integer): Boolean;

function ExtendDarkRun(const Source: IMat; const Horizontal: Boolean;
  const Lo, Hi, Limit, Threshold: Integer; var First, Last: Integer): Boolean;

type
  TFigureKind = (figCircle, figRectangle);

function HammingDistance64(const A, B: UInt64): Integer;

function AverageHash64(const Source: IMat): UInt64;

function BuildFigureMask(const Width, Height: Integer; const Kind: TFigureKind): IMat;

function MatchFigureShape(const Source: IMat; const Kind: TFigureKind): Double;

function AdjustContrastAroundPivot(const Value, Increment, Pivot: Integer): Integer;

function DualBandClampToBW(const Source: IMat;
  const BlackMin, BlackMax, WhiteMin, WhiteMax: Integer): IMat;

function LocalNeighborhoodMean(const Source: IMat; const X, Y, HalfW, HalfH: Integer): Integer;

function RaiseBrightness(const Value, Increment: Integer): Integer;

function BrightnessBoostForWhiteFraction(const Values: TArray<Byte>; const WhiteBorder: Integer;
  const TargetFraction: Double; const Step, MaxBoost: Integer): Integer;

function MeanOfChannels(const Values: array of Byte): Integer;

type
  TByteRange = record
    Min: Byte;
    Max: Byte;
  end;
  TByteRangeArray = array of TByteRange;

  TRangeTally = record
    Count: Integer;
    Ratio: Double;
  end;
  TRangeTallyArray = array of TRangeTally;

function BrightnessRangeTally(const Source: IMat; const Ranges: TByteRangeArray): TRangeTallyArray;

function ColorConversionCode(const FromChannels, ToChannels: Integer): Integer;

function ConvertChannels(const Source: IMat; const Channels: Integer): IMat;

type
  TChannelPattern = array[0..3] of Integer;

function CopyIntoIgnoring(const Source, Target: IMat; const Ignore: array of TChannelPattern;
  const Tolerance: Integer): Boolean;

implementation

uses
  {$IFDEF FPC}SysUtils{$ELSE}System.SysUtils{$ENDIF},
  OpenCV;

type
  TMatImpl = class(TInterfacedObject, IMat)
  private
    FHandle: TMat;
    FGeneration: Cardinal;
    FCounted: Boolean;
    FOwns: Boolean;
  public
    constructor Create(const AHandle: TMat; const AOwns: Boolean);
    destructor Destroy; override;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetChannels: Integer;
    function GetDepth: Integer;
    function GetMatType: Integer;
    function GetTotal: Integer;
    function GetElemSize: Integer;
    function GetStep: Integer;
    function IsEmpty: Boolean;
    function Raw: TMat;
    function DataPtr: Pointer;
    function Pixel(const X, Y: Integer): Byte;
    function ToGray: IMat;
    function CvtColor(const Code: Integer): IMat;
    function Clone: IMat;
    function ConvertTo(const NewType: Integer; const Alpha, Beta: Double): IMat;
    function ConvertScaleAbs(const Alpha, Beta: Double): IMat;
    function Fill(const V0, V1, V2, V3: Double): IMat;
    function Crop(const X, Y, W, H: Integer): IMat;
    function Add(const Other: IMat): IMat;
    function Subtract(const Other: IMat): IMat;
    function Multiply(const Other: IMat): IMat;
    function Divide(const Other: IMat): IMat;
    function AbsDiff(const Other: IMat): IMat;
    function Min(const Other: IMat): IMat;
    function Max(const Other: IMat): IMat;
    function AddWeighted(const Alpha: Double; const Other: IMat; const Beta, Gamma: Double): IMat;
    function ScaleAdd(const Alpha: Double; const Other: IMat): IMat;
    function Pow(const Power: Double): IMat;
    function Sqrt: IMat;
    function Exp: IMat;
    function Log: IMat;
    function BitwiseNot: IMat;
    function BitwiseAnd(const Other: IMat): IMat;
    function BitwiseOr(const Other: IMat): IMat;
    function BitwiseXor(const Other: IMat): IMat;
    function Threshold(const Thresh: Integer): IMat;
    function ThresholdEx(const Thresh, MaxVal: Double; const ThreshType: Integer): IMat;
    function AdaptiveThreshold(const BlockSize: Integer; const C: Double): IMat;
    function Compare(const Other: IMat; const CmpOp: Integer): IMat;
    function InRange(const Lo, Hi: TOCVScalar): IMat;
    function CountNonZero: Integer;
    function MinValue: Double;
    function MaxValue: Double;
    function MinMaxLoc(out MinV, MaxV: Double; out MinLoc, MaxLoc: TOCVPoint): Boolean;
    function SumScalar: TOCVScalar;
    function MeanScalar: TOCVScalar;
    function MeanValue: Double;
    function Norm(const NormType: Integer): Double;
    function Normalize(const Alpha, Beta: Double; const NormType: Integer): IMat;
    function Reduce(const Dim, ReduceType: Integer): IMat;
    function Transpose: IMat;
    function Invert(const Flags: Integer): IMat;
    function Determinant: Double;
    function Trace: TOCVScalar;
    function MatMul(const Other: IMat): IMat;
    function Split: TIMatArray;
    function ExtractChannel(const Index: Integer): IMat;
    function Resize(const NewWidth, NewHeight: Integer; const Interpolation: Integer = INTER_LINEAR): IMat;
    function Flip(const FlipCode: Integer): IMat;
    function Tile(const Ny, Nx: Integer): IMat;
    function Rotate90(const RotateCode: Integer): IMat;
    function CopyMakeBorder(const Top, Bottom, Left, Right, BorderType: Integer): IMat;
    function HConcat(const Other: IMat): IMat;
    function VConcat(const Other: IMat): IMat;
    function WarpAffine(const M: IMat; const W, H: Integer): IMat;
    function WarpPerspective(const M: IMat; const W, H: Integer): IMat;
    function GaussianBlur(const KernelSize: Integer): IMat;
    function MedianBlur(const KernelSize: Integer): IMat;
    function Blur(const KernelSize: Integer): IMat;
    function BilateralFilter(const Diameter: Integer; const SigmaColor, SigmaSpace: Double): IMat;
    function Canny(const Threshold1, Threshold2: Integer): IMat;
    function Sobel(const Dx, Dy, KernelSize: Integer): IMat;
    function Scharr(const Dx, Dy: Integer): IMat;
    function Laplacian(const KernelSize: Integer): IMat;
    function Erode(const Iterations: Integer): IMat;
    function Dilate(const Iterations: Integer): IMat;
    function MorphologyEx(const Op, Iterations: Integer): IMat;
    function ApplyLUT(const Lut: IMat): IMat;
    function Save(const Path: string): Boolean;
  end;

function OddKernel(const K: Integer): Integer;
begin
  Result := K;
  if Result < 1 then Result := 1;
  if (Result and 1) = 0 then Inc(Result);
end;

function Rect3x3Kernel: IMat;
begin
  Result := ZerosMat(3, 3, 0);
  Result.Fill(1, 0, 0, 0);
end;

constructor TMatImpl.Create(const AHandle: TMat; const AOwns: Boolean);
begin
  inherited Create;
  FHandle := AHandle;
  FOwns := False;
  FGeneration := CVRuntimeGeneration;
  FCounted := True;
  CVObjectCreated;
  FOwns := AOwns;
end;

destructor TMatImpl.Destroy;
begin
  try
    if FOwns and Assigned(FHandle) and (FGeneration = CVRuntimeGeneration) and Assigned(CV.Core.DeleteMat) then
      if not CV.Core.DeleteMat(@FHandle) then
        CVLifecycleFault(CVFaultDestroyFailed)
      else if Assigned(FHandle) then
          CVLifecycleFault(CVFaultDestroyFailed);
  finally
    if FCounted then
    begin
      if FOwns and Assigned(FHandle) and (FGeneration = CVRuntimeGeneration) and not Assigned(CV.Core.DeleteMat) then
        CVLifecycleFault(CVFaultMissingDestroy);
      if FGeneration = CVRuntimeGeneration then
        CVObjectDestroyed;
      FCounted := False;
    end;
  end;
  inherited;
end;

function TMatImpl.GetWidth: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatHSize(FHandle, @Result);
end;

function TMatImpl.GetHeight: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatVSize(FHandle, @Result);
end;

function TMatImpl.GetChannels: Integer;
var
  T: Integer;
begin
  if not Assigned(FHandle) then Exit(0);
  T := 0;
  CV.Core.GetMatType(FHandle, @T);
  Result := ((T shr 3) and 511) + 1;
end;

function TMatImpl.GetDepth: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatDepth(FHandle, @Result);
end;

function TMatImpl.GetMatType: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatType(FHandle, @Result);
end;

function TMatImpl.GetTotal: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatTotal(FHandle, @Result);
end;

function TMatImpl.GetElemSize: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatElemSize(FHandle, @Result);
end;

function TMatImpl.GetStep: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.GetMatStep(FHandle, @Result);
end;

function TMatImpl.IsEmpty: Boolean;
begin
  Result := (not Assigned(FHandle)) or (GetWidth <= 0) or (GetHeight <= 0);
end;

function TMatImpl.Raw: TMat;
begin
  Result := FHandle;
end;

function TMatImpl.DataPtr: Pointer;
begin
  Result := nil;
  if Assigned(FHandle) then
    CV.Core.GetMatData(FHandle, @Result);
end;

function TMatImpl.Pixel(const X, Y: Integer): Byte;
var
  W, H, St, Ch: Integer;
  P: Pointer;
begin
  Result := 0;
  if not Assigned(FHandle) then Exit;
  W := GetWidth;
  H := GetHeight;
  if (X < 0) or (Y < 0) or (X >= W) or (Y >= H) then Exit;
  St := 0;
  P := nil;
  CV.Core.GetMatStep(FHandle, @St);
  CV.Core.GetMatData(FHandle, @P);
  if P = nil then Exit;
  Ch := GetChannels;
  Result := PByte(NativeUInt(P) + NativeUInt(Y * St + X * Ch))^;
end;

function TMatImpl.ToGray: IMat;
var
  Dst: TMat;
begin
  if GetChannels = 1 then Exit(Self);
  Dst := nil;
  if CV.ImgProc.ConvertColor(FHandle, @Dst, COLOR_BGR2GRAY) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.CvtColor(const Code: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.ConvertColor(FHandle, @Dst, Code) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Clone: IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Clone(FHandle, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.ConvertTo(const NewType: Integer; const Alpha, Beta: Double): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.ConvertType(FHandle, @Dst, NewType, Alpha, Beta) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.ConvertScaleAbs(const Alpha, Beta: Double): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.ConvertScaleAbs(FHandle, @Dst, Alpha, Beta) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Fill(const V0, V1, V2, V3: Double): IMat;
begin
  if Assigned(FHandle) then
    CV.Core.SetTo(@FHandle, OCVScalar(V0, V1, V2, V3), nil);
  Result := Self;
end;

function TMatImpl.Crop(const X, Y, W, H: Integer): IMat;
var
  Roi, Dst: TMat;
begin
  Roi := nil;
  Dst := nil;
  if CV.Core.CreateRoi(FHandle, OCVRect(X, Y, W, H), @Roi) then
  begin
    if CV.Core.Clone(Roi, @Dst) then
      Result := WrapMat(Dst, True)
    else
      Result := WrapMat(nil, False);
    CV.Core.DeleteMat(@Roi);
  end
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Add(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Add(FHandle, Other.Raw, @Dst, nil, -1) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Subtract(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Subtract(FHandle, Other.Raw, @Dst, nil, -1) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Multiply(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Multiply(FHandle, Other.Raw, @Dst, 1, -1) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Divide(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Divide(FHandle, Other.Raw, @Dst, 1, -1) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.AbsDiff(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Absdiff(FHandle, Other.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Min(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Min(FHandle, Other.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Max(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Max(FHandle, Other.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.AddWeighted(const Alpha: Double; const Other: IMat; const Beta, Gamma: Double): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.AddWeighted(FHandle, Alpha, Other.Raw, Beta, Gamma, @Dst, -1) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.ScaleAdd(const Alpha: Double; const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.ScaleAdd(FHandle, Alpha, Other.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Pow(const Power: Double): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Pow(FHandle, Power, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Sqrt: IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Sqrt(FHandle, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Exp: IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Exp(FHandle, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Log: IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Log(FHandle, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.BitwiseNot: IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.BitwiseNot(FHandle, @Dst, nil) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.BitwiseAnd(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.BitwiseAnd(FHandle, Other.Raw, @Dst, nil) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.BitwiseOr(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.BitwiseOr(FHandle, Other.Raw, @Dst, nil) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.BitwiseXor(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.BitwiseXor(FHandle, Other.Raw, @Dst, nil) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Threshold(const Thresh: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.Threshold(FHandle, @Dst, Thresh, 255, THRESH_BINARY) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.ThresholdEx(const Thresh, MaxVal: Double; const ThreshType: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.Threshold(FHandle, @Dst, Thresh, MaxVal, ThreshType) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.AdaptiveThreshold(const BlockSize: Integer; const C: Double): IMat;
var
  Dst: TMat;
  B: Integer;
begin
  B := BlockSize;
  if B < 3 then B := 3;
  if (B and 1) = 0 then Inc(B);
  Dst := nil;
  if CV.ImgProc.AdaptiveThreshold(FHandle, @Dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, B, C) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Compare(const Other: IMat; const CmpOp: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Compare(FHandle, Other.Raw, @Dst, CmpOp) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.InRange(const Lo, Hi: TOCVScalar): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.InRange(FHandle, Lo, Hi, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.CountNonZero: Integer;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.CountNonZero(FHandle, @Result);
end;

function TMatImpl.MinValue: Double;
var
  MinV, MaxV: Double;
begin
  MinV := 0;
  MaxV := 0;
  if Assigned(FHandle) then
    CV.Core.MinMaxLoc(FHandle, @MinV, @MaxV, nil, nil, nil);
  Result := MinV;
end;

function TMatImpl.MaxValue: Double;
var
  MinV, MaxV: Double;
begin
  MinV := 0;
  MaxV := 0;
  if Assigned(FHandle) then
    CV.Core.MinMaxLoc(FHandle, @MinV, @MaxV, nil, nil, nil);
  Result := MaxV;
end;

function TMatImpl.MinMaxLoc(out MinV, MaxV: Double; out MinLoc, MaxLoc: TOCVPoint): Boolean;
begin
  MinV := 0;
  MaxV := 0;
  FillChar(MinLoc, SizeOf(MinLoc), 0);
  FillChar(MaxLoc, SizeOf(MaxLoc), 0);
  Result := Assigned(FHandle) and CV.Core.MinMaxLoc(FHandle, @MinV, @MaxV, @MinLoc, @MaxLoc, nil);
end;

function TMatImpl.SumScalar: TOCVScalar;
begin
  FillChar(Result, SizeOf(Result), 0);
  if Assigned(FHandle) then
    CV.Core.Sum(FHandle, @Result);
end;

function TMatImpl.MeanScalar: TOCVScalar;
begin
  FillChar(Result, SizeOf(Result), 0);
  if Assigned(FHandle) then
    CV.Core.Mean(FHandle, nil, @Result);
end;

function TMatImpl.MeanValue: Double;
begin
  Result := MeanScalar.V0;
end;

function TMatImpl.Norm(const NormType: Integer): Double;
begin
  Result := 0;
  if Assigned(FHandle) then
    Result := CV.Core.Norm(FHandle, NormType, nil);
end;

function TMatImpl.Normalize(const Alpha, Beta: Double; const NormType: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Normalize(FHandle, @Dst, Alpha, Beta, NormType, -1, nil) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Reduce(const Dim, ReduceType: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Reduce(FHandle, @Dst, Dim, ReduceType, -1) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Transpose: IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Transpose(FHandle, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Invert(const Flags: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Invert(FHandle, @Dst, Flags) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Determinant: Double;
begin
  Result := 0;
  if Assigned(FHandle) then
    CV.Core.Determinant(FHandle, @Result);
end;

function TMatImpl.Trace: TOCVScalar;
begin
  FillChar(Result, SizeOf(Result), 0);
  if Assigned(FHandle) then
    CV.Core.Trace(FHandle, @Result);
end;

function TMatImpl.MatMul(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Gemm(FHandle, Other.Raw, 1, nil, 0, @Dst, 0) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Split: TIMatArray;
var
  Ch, I: Integer;
  Arr: array of TMat;
begin
  Ch := GetChannels;
  if (Ch <= 0) or (not Assigned(FHandle)) then Exit(nil);
  SetLength(Arr, Ch);
  for I := 0 to Ch - 1 do Arr[I] := nil;
  if CV.Core.Split(FHandle, @Arr[0]) then
  begin
    SetLength(Result, Ch);
    for I := 0 to Ch - 1 do Result[I] := WrapMat(Arr[I], True);
  end
  else
    Result := nil;
end;

function TMatImpl.ExtractChannel(const Index: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.ExtractChannel(FHandle, @Dst, Index) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Resize(const NewWidth, NewHeight, Interpolation: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.ResizeImage(FHandle, @Dst, OCVSize(NewWidth, NewHeight), 0, 0, Interpolation) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Flip(const FlipCode: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Flip(FHandle, @Dst, FlipCode) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Tile(const Ny, Nx: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.&Repeat(FHandle, Ny, Nx, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Rotate90(const RotateCode: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Rotate(FHandle, @Dst, RotateCode) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.CopyMakeBorder(const Top, Bottom, Left, Right, BorderType: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.CopyMakeBorder(FHandle, @Dst, Top, Bottom, Left, Right, BorderType, OCVScalar(0, 0, 0, 0)) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.HConcat(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Hconcat(FHandle, Other.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.VConcat(const Other: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.Vconcat(FHandle, Other.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.WarpAffine(const M: IMat; const W, H: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.WarpAffine(FHandle, @Dst, M.Raw, OCVSize(W, H), INTER_LINEAR, 0, OCVScalar(0, 0, 0, 0)) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.WarpPerspective(const M: IMat; const W, H: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.WarpPerspective(FHandle, @Dst, M.Raw, OCVSize(W, H), INTER_LINEAR, 0,
    OCVScalar(0, 0, 0, 0)) then
      Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.GaussianBlur(const KernelSize: Integer): IMat;
var
  Dst: TMat;
  K: Integer;
begin
  K := OddKernel(KernelSize);
  Dst := nil;
  if CV.ImgProc.GaussianBlur(FHandle, @Dst, OCVSize(K, K), 0, 0, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.MedianBlur(const KernelSize: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.MedianBlur(FHandle, @Dst, OddKernel(KernelSize)) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Blur(const KernelSize: Integer): IMat;
var
  Dst: TMat;
  K: Integer;
begin
  K := KernelSize;
  if K < 1 then K := 1;
  Dst := nil;
  if CV.ImgProc.Blur(FHandle, @Dst, OCVSize(K, K), BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.BilateralFilter(const Diameter: Integer; const SigmaColor, SigmaSpace: Double): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.BilateralFilter(FHandle, @Dst, Diameter, SigmaColor, SigmaSpace, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Canny(const Threshold1, Threshold2: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.Canny(FHandle, @Dst, Threshold1, Threshold2, 3, False) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Sobel(const Dx, Dy, KernelSize: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.Sobel(FHandle, @Dst, -1, Dx, Dy, KernelSize, 1, 0, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Scharr(const Dx, Dy: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.Scharr(FHandle, @Dst, -1, Dx, Dy, 1, 0, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Laplacian(const KernelSize: Integer): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.ImgProc.Laplacian(FHandle, @Dst, -1, OddKernel(KernelSize), 1, 0, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Erode(const Iterations: Integer): IMat;
var
  Dst: TMat;
  Kern: IMat;
begin
  Kern := Rect3x3Kernel;
  Dst := nil;
  if CV.ImgProc.Erode(FHandle, @Dst, Kern.Raw, Iterations, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Dilate(const Iterations: Integer): IMat;
var
  Dst: TMat;
  Kern: IMat;
begin
  Kern := Rect3x3Kernel;
  Dst := nil;
  if CV.ImgProc.Dilate(FHandle, @Dst, Kern.Raw, Iterations, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.MorphologyEx(const Op, Iterations: Integer): IMat;
var
  Dst: TMat;
  Kern: IMat;
begin
  Kern := Rect3x3Kernel;
  Dst := nil;
  if CV.ImgProc.MorphologyEx(FHandle, @Dst, Op, Kern.Raw, Iterations, BORDER_DEFAULT) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.ApplyLUT(const Lut: IMat): IMat;
var
  Dst: TMat;
begin
  Dst := nil;
  if CV.Core.LUT(FHandle, Lut.Raw, @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function TMatImpl.Save(const Path: string): Boolean;
begin
  Result := Assigned(FHandle) and CV.ImgCodecs.SaveMat(PAnsiChar(AnsiString(Path)), FHandle);
end;

function LoadMat(const Path: string; const Color: Boolean): IMat;
var
  Handle: TMat;
  Flags: Integer;
begin
  Handle := nil;
  if Color then
    Flags := IMREAD_COLOR
  else
    Flags := IMREAD_GRAYSCALE;
  if CV.ImgCodecs.OpenMat(PAnsiChar(AnsiString(Path)), Flags, @Handle) then
    Result := WrapMat(Handle, True)
  else
    Result := WrapMat(nil, False);
end;

function WrapMat(const Handle: TMat; const OwnsHandle: Boolean): IMat;
begin
  if not CV.Module.Loaded then
    raise Exception.Create('Cannot create an OpenCV wrapper: no runtime is loaded. ' +
      'Every wrapper depends on the runtime - its methods go through the ' +
      'function table whether it holds a handle or not - so one made before a ' +
      'runtime is active could never be accounted for correctly.');
  Result := TMatImpl.Create(Handle, OwnsHandle);
end;

function NewMat(const Width, Height, MatType: Integer): IMat;
begin
  Result := WrapMat(CV.Core.MakeMat(Width, Height, MatType), True);
end;

function ZerosMat(const Width, Height, MatType: Integer): IMat;
begin
  Result := NewMat(Width, Height, MatType);
  Result.Fill(0, 0, 0, 0);
end;

function MergeMats(const Mats: array of IMat): IMat;
var
  Arr: array of TMat;
  I: Integer;
  Dst: TMat;
begin
  if Length(Mats) = 0 then Exit(WrapMat(nil, False));
  SetLength(Arr, Length(Mats));
  for I := 0 to High(Mats) do Arr[I] := Mats[I].Raw;
  Dst := nil;
  if CV.Core.Merge(@Arr[0], Length(Mats), @Dst) then
    Result := WrapMat(Dst, True)
  else
    Result := WrapMat(nil, False);
end;

function RegionView(const Source: IMat; const X, Y, W, H: Integer): IMat;
var
  Roi: TMat;
begin
  if (Source = nil) or Source.IsEmpty then Exit(WrapMat(nil, False));
  Roi := nil;
  if CV.Core.CreateRoi(Source.Raw, OCVRect(X, Y, W, H), @Roi) then
    Result := WrapMat(Roi, True)
  else
    Result := WrapMat(nil, False);
end;

function CopyCompatible(const Source, Target: IMat): Boolean;
begin
  Result := (Source <> nil) and (Target <> nil) and
    not Source.IsEmpty and not Target.IsEmpty and
    (Source.MatType = Target.MatType) and
    (Source.DataPtr <> nil) and (Target.DataPtr <> nil);
end;

function CopyRegionInto(const Source: IMat; const X, Y, W, H: Integer; const Target: IMat): Boolean;
var
  View: IMat;
  I, RowBytes: Integer;
  Src, Dst: PByte;
begin
  Result := False;
  if not CopyCompatible(Source, Target) then Exit;
  if (Target.Width <> W) or (Target.Height <> H) then Exit;
  View := RegionView(Source, X, Y, W, H);
  if (View = nil) or View.IsEmpty then Exit;
  RowBytes := W * Source.ElemSize;
  for I := 0 to H - 1 do
  begin
    Src := PByte(View.DataPtr);
    Dst := PByte(Target.DataPtr);
    if (Src = nil) or (Dst = nil) then Exit;
    Inc(Src, I * View.Step);
    Inc(Dst, I * Target.Step);
    Move(Src^, Dst^, RowBytes);
  end;
  Result := True;
end;

function CopyIntoIgnoring(const Source, Target: IMat; const Ignore: array of TChannelPattern;
  const Tolerance: Integer): Boolean;

  function Matches(const Pixel: PByte; const Pattern: TChannelPattern;
    const ChannelCount: Integer): Boolean;
  var
    K: Integer;
    Comp: PByte;
  begin
    Comp := Pixel;
    for K := 0 to ChannelCount - 1 do
    begin
      if Pattern[K] >= 0 then
        if Abs(Integer(Comp^) - Pattern[K]) > Tolerance then Exit(False);
      Inc(Comp);
    end;
    Result := True;
  end;

var
  X, Y, I, ChannelCount: Integer;
  Src, Dst: PByte;
  Skip: Boolean;
begin
  Result := False;
  if not CopyCompatible(Source, Target) then Exit;
  if (Source.Width <> Target.Width) or (Source.Height <> Target.Height) then Exit;
  if Source.Depth <> CV_8U then Exit;
  ChannelCount := Source.Channels;
  if ChannelCount > 4 then Exit;
  for Y := 0 to Source.Height - 1 do
  begin
    Src := PByte(Source.DataPtr);
    Inc(Src, Y * Source.Step);
    Dst := PByte(Target.DataPtr);
    Inc(Dst, Y * Target.Step);
    for X := 0 to Source.Width - 1 do
    begin
      Skip := False;
      for I := Low(Ignore) to High(Ignore) do
        if Matches(Src, Ignore[I], ChannelCount) then
        begin
          Skip := True;
          Break;
        end;
      if not Skip then
        Move(Src^, Dst^, ChannelCount);
      Inc(Src, ChannelCount);
      Inc(Dst, ChannelCount);
    end;
  end;
  Result := True;
end;

function CopyInto(const Source, Target: IMat): Boolean;
begin
  Result := (Source <> nil) and not Source.IsEmpty and
    CopyRegionInto(Source, 0, 0, Source.Width, Source.Height, Target);
end;

function MeanDarkAcross(const Source: IMat; const Horizontal: Boolean;
  const Position, Lo, Hi, Threshold: Integer): Integer;
var
  I, Sum, Count, W, H: Integer;
  IsDark: Boolean;
begin
  Result := -1;
  if (Source = nil) or Source.IsEmpty or (Source.Channels <> 1) then Exit;
  W := Source.Width;
  H := Source.Height;
  Sum := 0;
  Count := 0;
  for I := Lo to Hi do
  begin
    if Horizontal then
      IsDark := (Position >= 0) and (Position < W) and (I >= 0) and (I < H) and
        (Source.Pixel(Position, I) <= Threshold)
    else
      IsDark := (I >= 0) and (I < W) and (Position >= 0) and (Position < H) and
        (Source.Pixel(I, Position) <= Threshold);
    if IsDark then
    begin
      Inc(Sum, I);
      Inc(Count);
    end;
  end;
  if Count > 0 then Result := Sum div Count;
end;

function DarkBandBounds(const EdgeA, EdgeB, MaxWidth, Limit: Integer; out Lo, Hi: Integer): Boolean;
var
  MinOf, MaxOf: Integer;
begin
  Lo := 0;
  Hi := -1;
  Result := Limit >= 0;
  if not Result then Exit;
  if EdgeA < EdgeB then
  begin
    MinOf := EdgeA;
    MaxOf := EdgeB;
  end
  else begin
    MinOf := EdgeB;
    MaxOf := EdgeA;
  end;
  Lo := MinOf - MaxWidth div 2;
  Hi := MaxOf + MaxWidth div 2;
  if Lo < 0 then Lo := 0;
  if Hi > Limit then Hi := Limit;
  Result := Lo <= Hi;
  if not Result then
  begin
    Lo := 0;
    Hi := -1;
  end;
end;

function ExtendDarkRun(const Source: IMat; const Horizontal: Boolean;
  const Lo, Hi, Limit, Threshold: Integer; var First, Last: Integer): Boolean;
var
  I, HadFirst, HadLast: Integer;
begin
  Result := False;
  if (Source = nil) or Source.IsEmpty or (Source.Channels <> 1) then Exit;
  HadFirst := First;
  HadLast := Last;
  for I := First - 1 downto 0 do
  begin
    if MeanDarkAcross(Source, Horizontal, I, Lo, Hi, Threshold) < 0 then Break;
    First := I;
  end;
  for I := Last + 1 to Limit do
  begin
    if MeanDarkAcross(Source, Horizontal, I, Lo, Hi, Threshold) < 0 then Break;
    Last := I;
  end;
  Result := (First <> HadFirst) or (Last <> HadLast);
end;

function HammingDistance64(const A, B: UInt64): Integer;
var
  Diff: UInt64;
begin
  Result := 0;
  Diff := A xor B;
  while Diff <> 0 do
  begin
    Inc(Result, Integer(Diff and 1));
    Diff := Diff shr 1;
  end;
end;

function AverageHash64(const Source: IMat): UInt64;
var
  Gray, Small: IMat;
  Mean: Double;
  Row, Col, Idx: Integer;
begin
  Result := 0;
  if (Source = nil) or Source.IsEmpty then Exit;
  Gray := ConvertChannels(Source, 1);
  if (Gray = nil) or Gray.IsEmpty then Exit;
  Small := Gray.Resize(8, 8);
  if (Small = nil) or Small.IsEmpty then Exit;
  Mean := Small.MeanValue;
  for Row := 0 to 7 do
    for Col := 0 to 7 do
    begin
      Idx := Row * 8 + Col;
      if Small.Pixel(Col, Row) > Mean then
        Result := Result or (UInt64(1) shl Idx);
    end;
end;

function BuildFigureMask(const Width, Height: Integer; const Kind: TFigureKind): IMat;
var
  Cx, Cy, R, X, Y: Integer;
  Row: PByte;
begin
  Result := WrapMat(nil, False);
  if (Width <= 0) or (Height <= 0) then Exit;
  Result := NewMat(Width, Height, CV_MAKETYPE(CV_8U, 1));
  if Result.IsEmpty or (Result.DataPtr = nil) then
  begin
    Result := WrapMat(nil, False);
    Exit;
  end;
  if Kind = figRectangle then
  begin
    Result.Fill(0);
    Exit;
  end;
  Result.Fill(255);
  Cx := Width div 2;
  Cy := Height div 2;
  if Width < Height then
    R := Width div 2
  else
    R := Height div 2;
  for Y := 0 to Height - 1 do
  begin
    Row := PByte(NativeUInt(Result.DataPtr) + NativeUInt(Y * Result.Step));
    for X := 0 to Width - 1 do
    begin
      if Sqr(X - Cx) + Sqr(Y - Cy) <= Sqr(R) then
        PByte(NativeUInt(Row) + NativeUInt(X))^ := 0;
    end;
  end;
end;

function MatchFigureShape(const Source: IMat; const Kind: TFigureKind): Double;
var
  Reference: IMat;
  Dist: Integer;
begin
  Result := 0;
  if (Source = nil) or Source.IsEmpty then Exit;
  Reference := BuildFigureMask(Source.Width, Source.Height, Kind);
  if (Reference = nil) or Reference.IsEmpty then Exit;
  Dist := HammingDistance64(AverageHash64(Source), AverageHash64(Reference));
  Result := 1 - Dist / 64;
end;

function AdjustContrastAroundPivot(const Value, Increment, Pivot: Integer): Integer;
begin
  Result := Value + (Value - Pivot) * Increment div 255;
  if Result < 0 then Result := 0;
  if Result > 255 then Result := 255;
end;

function DualBandClampToBW(const Source: IMat;
  const BlackMin, BlackMax, WhiteMin, WhiteMax: Integer): IMat;
var
  X, Y: Integer;
  Px: PByte;
  Level: Integer;
begin
  Result := WrapMat(nil, False);
  if (Source = nil) or Source.IsEmpty or (Source.Channels <> 1) then Exit;
  if Source.Depth <> CV_8U then Exit;
  Result := Source.Clone;
  if Result.IsEmpty or (Result.DataPtr = nil) then
  begin
    Result := WrapMat(nil, False);
    Exit;
  end;
  for Y := 0 to Result.Height - 1 do
    for X := 0 to Result.Width - 1 do
    begin
      Px := PByte(NativeUInt(Result.DataPtr) + NativeUInt(Y * Result.Step + X));
      Level := Px^;
      if (Level >= BlackMin) and (Level <= BlackMax) then
      begin
        Px^ := 0;
        Level := 0;
      end;
      if (Level >= WhiteMin) and (Level <= WhiteMax) then
        Px^ := 255;
    end;
end;

function LocalNeighborhoodMean(const Source: IMat; const X, Y, HalfW, HalfH: Integer): Integer;
var
  FromX, ToX, FromY, ToY, I, J, Sum, Count: Integer;
begin
  Result := -1;
  if (Source = nil) or Source.IsEmpty or (Source.Channels <> 1) then Exit;
  if (X < 0) or (Y < 0) or (X >= Source.Width) or (Y >= Source.Height) then Exit;
  if (HalfW < 0) or (HalfH < 0) then Exit;
  FromX := X - HalfW;
  if FromX < 0 then FromX := 0;
  ToX := X + HalfW;
  if ToX > Source.Width - 1 then ToX := Source.Width - 1;
  FromY := Y - HalfH;
  if FromY < 0 then FromY := 0;
  ToY := Y + HalfH;
  if ToY > Source.Height - 1 then ToY := Source.Height - 1;
  Sum := 0;
  Count := 0;
  for I := FromY to ToY do
    for J := FromX to ToX do
      if (J <> X) or (I <> Y) then
      begin
        Inc(Sum, Source.Pixel(J, I));
        Inc(Count);
      end;
  if Count > 0 then Result := Sum div Count;
end;

function RaiseBrightness(const Value, Increment: Integer): Integer;
begin
  Result := Value + Increment;
  if Result < 0 then Result := 0;
  if Result > 255 then Result := 255;
end;

function BrightnessBoostForWhiteFraction(const Values: TArray<Byte>; const WhiteBorder: Integer;
  const TargetFraction: Double; const Step, MaxBoost: Integer): Integer;
var
  Boost, I, WhiteCount: Integer;
begin
  Result := -1;
  if Length(Values) = 0 then Exit;
  if (Step <= 0) or (MaxBoost < 0) then Exit;
  Boost := 0;
  while Boost <= MaxBoost do
  begin
    WhiteCount := 0;
    for I := Low(Values) to High(Values) do
      if RaiseBrightness(Values[I], Boost) >= WhiteBorder then Inc(WhiteCount);
    if WhiteCount / Length(Values) >= TargetFraction then Exit(Boost);
    Inc(Boost, Step);
  end;
end;

function MeanOfChannels(const Values: array of Byte): Integer;
var
  Sum, I: Integer;
begin
  Result := 0;
  if Length(Values) = 0 then Exit;
  Sum := 0;
  for I := Low(Values) to High(Values) do Inc(Sum, Values[I]);
  Result := Sum div Length(Values);
end;

function BrightnessRangeTally(const Source: IMat; const Ranges: TByteRangeArray): TRangeTallyArray;
var
  X, Y, I, W, H, Total: Integer;
  Level: Integer;
begin
  Result := nil;
  if Length(Ranges) = 0 then Exit;
  if not Assigned(Source) or Source.IsEmpty then Exit;
  W := Source.Width;
  H := Source.Height;
  if (W <= 0) or (H <= 0) then Exit;
  SetLength(Result, Length(Ranges));
  for I := Low(Result) to High(Result) do
  begin
    Result[I].Count := 0;
    Result[I].Ratio := 0;
  end;
  for Y := 0 to H - 1 do
    for X := 0 to W - 1 do
    begin
      Level := Source.Pixel(X, Y);
      for I := Low(Ranges) to High(Ranges) do
        if (Level >= Ranges[I].Min) and (Level <= Ranges[I].Max) then
        begin
          Inc(Result[I].Count);
          Break;
        end;
    end;
  Total := W * H;
  for I := Low(Result) to High(Result) do
    Result[I].Ratio := Result[I].Count / Total;
end;

function ColorConversionCode(const FromChannels, ToChannels: Integer): Integer;
begin
  Result := -1;
  if FromChannels = ToChannels then Exit;
  case FromChannels of
    1:
      case ToChannels of
        3: Result := COLOR_GRAY2BGR;
        4: Result := COLOR_GRAY2BGRA;
      end;
    3:
      case ToChannels of
        1: Result := COLOR_BGR2GRAY;
        4: Result := COLOR_BGR2BGRA;
      end;
    4:
      case ToChannels of
        1: Result := COLOR_BGRA2GRAY;
        3: Result := COLOR_BGRA2BGR;
      end;
  end;
end;

function ConvertChannels(const Source: IMat; const Channels: Integer): IMat;
var
  Code: Integer;
begin
  if (Source = nil) or Source.IsEmpty then Exit(WrapMat(nil, False));
  if Source.Channels = Channels then Exit(Source);
  Code := ColorConversionCode(Source.Channels, Channels);
  if Code < 0 then Exit(WrapMat(nil, False));
  Result := Source.CvtColor(Code);
end;

function ExtractRegion(const Source: IMat; const X, Y, W, H: Integer): IMat;
begin
  if (Source = nil) or Source.IsEmpty then Exit(WrapMat(nil, False));
  Result := Source.Crop(X, Y, W, H);
end;

end.
