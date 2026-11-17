# Prepare and run an example

Download [Prepare-CrossCVHello-CPU-ea023.zip](https://github.com/pisarev/crosspascal/releases/download/early-access-023/Prepare-CrossCVHello-CPU-ea023.zip), extract it, and run **Prepare.cmd**.
Prepare downloads the current Windows x64 SDK, the matching native libraries,
and sample files. Downloads are checked with SHA-256. No Python or GitHub
account is required.

Wait for **READY**, then open the supplied `.dproj` in Delphi 13.2 or `.lpi`
in Lazarus 4.8 / FPC 3.2.2. Select Windows 64-bit / Release, build, and run.
The installed SDK includes ready Lazarus executables. Keep its folders together.

The default installation is `%LOCALAPPDATA%/CrossPascal/early-access-023`.
Set `CROSSPASCAL_PREPARE_HOME` before starting Prepare to choose another drive.
Repeating preparation reuses verified downloads and preserves local source edits.

See the [complete preparation guide](https://github.com/pisarev/crosspascal/blob/main/docs/PREPARE-EXAMPLES.md)
for installation settings, optional GitHub request-limit recovery, model choices,
CPU/CUDA requirements, and licenses. The [separate vision starters](https://github.com/pisarev/crosspascal/blob/main/docs/VISION-DOWNLOADS.md)
select one vision model and device.
