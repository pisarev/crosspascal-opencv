# OpenCV build-cache input terms

These six files are the exact cache inputs supplied in the matching OpenCV native-source companion. Their cache paths, sizes and SHA-256 values are recorded in VENDOR-SOURCES.json in that companion. The Windows SDK's own Pascal bindings and C++ bridge use the project MIT license. The cached upstream code and model files retain the terms identified below.

## Exact files

Cache paths below are relative to the native-source companion, not the main SDK directory.

| Cache file under opencv-download-cache/ | Bytes | Terms | SHA-256 |
| --- | ---: | --- | --- |
| ade/dbb095a8bf3008e91edbbf45d8d34885-v0.1.2d.zip | 168110 | Apache-2.0; source A | 586fc6b9d56990ed7490e261a0a5c5323ebbda4820bf2458088a5ecda977c1c1 |
| data/7505c44ca4eb54b4ab1e4777cb96ac05-face_landmark_model.dat | 72368157 | BSD-3-Clause; source F | eeab592db2861a6c94d592a48456cf59945d31483ce94a6bc4d3a4e318049ba3 |
| wechat_qrcode/238e2b2d6f3c18d6c3a30de0c31e23cf-detect.caffemodel | 965430 | Apache-2.0; source W | cc49b8c9babaf45f3037610fe499df38c8819ebda29e90ca9f2e33270f6ef809 |
| wechat_qrcode/6fb4976b32695f9f5c6305c19f12537d-detect.prototxt | 42656 | Apache-2.0; source W | e8acfc395caf443a47f15686a9b9207b36cb8f7e6ceb8fbaf6466665e68a9466 |
| wechat_qrcode/cbfcd60361a73beb8c583eea7e8e6664-sr.caffemodel | 23929 | Apache-2.0; source W | e5d36889d8e6ef2f1c1f515f807cec03979320ac81792cd8fb927c31fd658ae3 |
| wechat_qrcode/69db99927a70df953b471daaba03fbef-sr.prototxt | 5984 | Apache-2.0; source W | 8ae41acba97e8b4a8e741ee350481e49b8e01d787193f470a4c95ee1c02d5b61 |

## Source A: ADE v0.1.2d

The matching OpenCV source, commit 71d3237a093b60a27601c20e9ee6c3e52154e8b1, selects this exact ZIP and MD5 in modules/gapi/cmake/DownloadADE.cmake. Its upstream location is [opencv/ade v0.1.2d](https://github.com/opencv/ade/tree/v0.1.2d).

The supplied ZIP contains ade-0.1.2d/LICENSE and README.md. Both identify Apache 2.0. The embedded license is 11358 bytes, SHA-256 cfc7749b96f63bd31c3c42b5c471bf756814053e847c10f3eb003417bc523d30; its text is identical to the separately supplied [Apache 2.0 text](licenses/opencv/LICENSE). Preserve the ZIP's source copyright and license notices when redistributing its sources. No ADE NOTICE file was present in the inspected ZIP.

## Source F: face landmark model

The matching OpenCV contrib source selects [opencv/opencv_3rdparty commit 8afa57abc8229d611c4937165d20e2a2d9fc5a12](https://github.com/opencv/opencv_3rdparty/tree/8afa57abc8229d611c4937165d20e2a2d9fc5a12) and MD5 7505c44ca4eb54b4ab1e4777cb96ac05. That snapshot contains the model and a README that supplies its BSD 3-Clause terms and expressly describes the trained landmark model.

The supplied model matches upstream Git blob e6bc8842648e296370a7560725ecb21bddc29b79. The publisher's exact [README and notice](licenses/opencv_3rdparty/face_landmark/README.md) is included unchanged: 2415 bytes, SHA-256 84487df25bc6f44ad6bfcffab374fa11155eaa856eaa082da4b8e68c784bc81d. Retain its copyright list, conditions and disclaimer in distributions; do not imply endorsement by the listed holders. This attribution comes from the model's own publisher snapshot.

## Source W: WeChat QRCode detector and super-resolution models

The matching OpenCV contrib source, commit 1ed3dd2c53888e3289afdb22ec4e9ebbff3dba87, selects the four files from [WeChatCV/opencv_3rdparty commit a8b69ccc738421293254aec5ddb38bd523503252](https://github.com/WeChatCV/opencv_3rdparty/tree/a8b69ccc738421293254aec5ddb38bd523503252), with the MD5 values retained in the cache filenames.

The publisher subsequently added the model repository's license in [commit 3487ef7cde71d93c6a01bb0b84aa0f22c6128f6b](https://github.com/WeChatCV/opencv_3rdparty/commit/3487ef7cde71d93c6a01bb0b84aa0f22c6128f6b). All four supplied files have the same Git blob identities in the original snapshot and in that licensed snapshot:

| File | Git blob SHA-1 in both snapshots and the supplied cache |
| --- | --- |
| detect.caffemodel | 453126c7b0415490197cf4f050ff5fc166a41437 |
| detect.prototxt | bd2417c96ba8ba6e9048cac1c0f43523fd14ddb2 |
| sr.caffemodel | 168b54d43ec27a3782da14c6a03d3f7bb61bdda3 |
| sr.prototxt | e85caa177d54e8f23306bf12de1b7c3fe9a1da83 |

The existing [Tencent/WeChat QRCode license](licenses/opencv_contrib/modules/wechat_qrcode/LICENSE) supplies Apache 2.0 and the stated third-party attribution. Its text matches the publisher's model-repository license; the latter adds one final line-feed byte. Preserve this notice and the included Apache terms. No weights were replaced or converted to establish this attribution.

## Scope

These records establish the six cache inputs' publisher license attribution and exact file identity. They do not assert model accuracy, accept another model, alter the runtime build, or establish that the new portable rebuild/relink instructions have been executed. The static FFmpeg terms, corresponding sources and relink route remain described in [third-party notices](THIRD-PARTY-NOTICES.md).
