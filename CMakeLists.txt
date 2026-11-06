# Copyright (C) 2026 Yuriy Pisarev. SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.16)
project(crosscv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV 4.10 REQUIRED)

set(_OPENCV_TRANSITIVE_DEPS
    Eigen3::Eigen
    TBB::tbb
    Iconv::Iconv
    ade
    quirc::quirc
)

find_package(Eigen3 QUIET)
find_package(TBB QUIET)

foreach(_dep ${_OPENCV_TRANSITIVE_DEPS})
    if(NOT TARGET ${_dep})
        add_library(${_dep} INTERFACE IMPORTED)
    endif()
endforeach()

set(SOURCES
    cpp/main.cpp
    cpp/helper.cpp
    cpp/cv_core.cpp
    cpp/cv_imgproc.cpp
    cpp/cv_imgcodecs.cpp
    cpp/cv_photo.cpp
    cpp/cv_video.cpp
    cpp/cv_videoio.cpp
    cpp/cv_objdetect.cpp
    cpp/cv_dnn.cpp
    cpp/cv_ml.cpp
    cpp/cv_tracking.cpp
    cpp/cv_features2d.cpp
    cpp/cv_calib3d.cpp
    cpp/cv_highgui.cpp
    cpp/cv_ximgproc.cpp
    cpp/cv_bioinspired.cpp
    cpp/cv_custom.cpp
    cpp/cv_stitching.cpp
    cpp/cv_aruco.cpp
    cpp/cv_xfeatures2d.cpp
    cpp/cv_optflow.cpp
    cpp/cv_face.cpp
    cpp/cv_xphoto.cpp
)

add_library(crosscv SHARED ${SOURCES})

if(NOT MINGW)
    set_target_properties(crosscv PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON)
endif()

if(MINGW)
    set_target_properties(crosscv PROPERTIES PREFIX "")

    target_sources(crosscv PRIVATE ${CMAKE_SOURCE_DIR}/cpp/crosscv.def)
endif()

target_include_directories(crosscv PRIVATE
    ${CMAKE_SOURCE_DIR}/cpp
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(crosscv PRIVATE ${OpenCV_LIBS})

if(AVIF_LIB)
    target_link_libraries(crosscv PRIVATE ${AVIF_LIB})
endif()
if(DAV1D_LIB)
    target_link_libraries(crosscv PRIVATE ${DAV1D_LIB})
endif()

if(UNIX AND NOT APPLE)
    target_link_options(crosscv PRIVATE
        -Wl,--exclude-libs,ALL
    )

    target_link_libraries(crosscv PRIVATE pthread dl)
endif()

if(WIN32)
    if(MINGW)
        target_link_options(crosscv PRIVATE
            -static-libgcc
            -static-libstdc++
        )

        target_link_libraries(crosscv PRIVATE -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,-Bdynamic,--no-whole-archive)
    endif()

    target_link_libraries(crosscv PRIVATE
        ws2_32 ole32 oleaut32 uuid comdlg32 gdi32 advapi32 user32
        setupapi shlwapi
    )
endif()

install(TARGETS crosscv
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
