# Build the OpenCV bridge

Download the matching `opencv-windows-x64` source asset from [CrossPascal Releases](https://github.com/pisarev/crosspascal/releases) and extract it. Open its README for the standalone Docker build. For the full SDK, the [Windows setup guide](https://github.com/pisarev/crosspascal/blob/main/docs/WINDOWS-EARLY-ACCESS.md) also shows the installer command.

The source asset contains the CrossCV bridge, OpenCV and contrib 4.10.0, FFmpeg 6.1.1, dav1d 1.3.0, libavif 1.0.4, and the associated notices. To verify its source inventory, run the following from the extracted asset with Python 3.10 or later:

```text
python -B tools/verify-source.py
```

The host fetcher obtains the 112 pinned Ubuntu packages. The portable Docker build verifies the package hashes and installs them from a local apt repository in the build context. Use a Linux Docker engine. Compiler packages and OCI layers are downloaded as build inputs.

Copy the resulting `crosscv.dll` into this repository's `bin` directory and follow the [installation guide](INSTALL.md) for Delphi and Lazarus examples.

## Rebuild with modified FFmpeg

See `RELINKING.md` and `Dockerfile.ffmpeg-relink.example` in the companion asset. The procedure rebuilds FFmpeg and the consuming bridge. A modified-FFmpeg rebuild preserved the bridge's 1,338 exports and passed a Windows video write/read check.

The OpenCV build enables `OPENCV_ENABLE_NONFREE`. FFmpeg's GPL, version 3, and nonfree options are disabled. See [third-party notices](THIRD-PARTY-NOTICES.md).
