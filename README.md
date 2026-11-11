# CrossPascal OpenCV

## Prepare and Run

Download [Prepare-CrossCVHello-ea019.zip](https://github.com/pisarev/crosspascal/releases/download/early-access-019/Prepare-CrossCVHello-ea019.zip), extract it, and double-click **Prepare.cmd**. It downloads the matched dependencies and sample data, then opens the prepared project folder. Open the **.dproj** in Delphi 13.2 or the **.lpi** in Lazarus 4.8, and press **Run**. See the [complete preparation guide](https://github.com/pisarev/crosspascal/blob/main/docs/PREPARE-EXAMPLES.md) for public downloads and optional GitHub request-limit recovery, model sizes and the other examples.

Use [Prepare-LoadResizeSave-ea019.zip](https://github.com/pisarev/crosspascal/releases/download/early-access-019/Prepare-LoadResizeSave-ea019.zip) for the image-resizing example. The native companion retains its complete matching source and licences.


Use OpenCV from Object Pascal to load and transform images, manage native image buffers, and add video I/O to a Windows application. The component includes bindings for OpenCV 4.10.0, the CrossCV bridge source, and an interface that manages the lifetime of native Mat objects.

## Try it on Windows x64

1. Build the Windows x64 `crosscv.dll` from the matching native source asset using its README. Place the resulting DLL in this repository's `bin` directory.
2. In Delphi 13.2, open `examples\CrossCVHello.dproj` and select Windows 64-bit. In Lazarus 4.8 with FPC 3.2.2, open `examples\CrossCVHello.lpi` and build for Windows x64.
3. Build and run the project. It prints the loaded DLL path, the bridge ABI, a pixel sum of **84**, and **12** nonzero pixels.
4. Open the corresponding `LoadResizeSave` project, choose a photograph, and save a 640 × 480 PNG.

Both examples use the relative unit paths in their project files. The Lazarus build has its own output directory. A standalone install needs this repository and its matching native source asset. Model conversion and TVM are separate.

Use the Delphi or Lazarus runtime package in [packages](packages/) for reusable bindings. Read [the build notes](BUILD.md), [known issues](KNOWN-ISSUES.md), and [third-party notices](THIRD-PARTY-NOTICES.md) for the matching bridge, build settings, upstream notices, and component limits.

## Work with image regions

- `Crop` and `ExtractRegion` return an independent copy of the requested rectangle.
- `RegionView` shares pixels with the original matrix. Writing to the view updates the original.
- `CopyRegionInto` writes into an existing nonempty target of the same type and the exact region size. To place the copy at an offset, pass a `RegionView` of the destination as the target. The function returns `False` if the region or target is invalid.
- `Reduce` collapses rows with dimension 0 and columns with dimension 1. Reduction codes are 0 for sum, 1 for average, 2 for maximum, and 3 for minimum.
