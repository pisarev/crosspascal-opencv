/* Copyright (c) 2026 Yuriy Pisarev                 */


#include "cv_aruco.h"
#include <vector>
#include <opencv2/calib3d.hpp>


CVAPI void *cv_aruco_getPredefinedDictionary(int dict)
{
    cv_clear_error();

    try {
        cv::aruco::Dictionary *d = new cv::aruco::Dictionary(
            cv::aruco::getPredefinedDictionary(static_cast<cv::aruco::PredefinedDictionaryType>(dict)));
        return d;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI void *cv_aruco_extendDictionary(int nMarkers, int markerSize, void *baseDictionary, int randomSeed)
{
    cv_clear_error();

    try {
        cv::aruco::Dictionary base;
        if (baseDictionary)
            base = *static_cast<cv::aruco::Dictionary *>(baseDictionary);
        cv::aruco::Dictionary *d = new cv::aruco::Dictionary(
            cv::aruco::extendDictionary(nMarkers, markerSize, base, randomSeed));
        return d;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_aruco_deleteDictionary(void *dictionary)
{
    cv_clear_error();

    try {
        delete static_cast<cv::aruco::Dictionary *>(dictionary);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_aruco_generateImageMarker(void *dictionary, int id, int sidePixels, cv::Mat **img, int borderBits)
{
    cv_clear_error();

    try {
        cv::aruco::Dictionary *dict = static_cast<cv::aruco::Dictionary *>(dictionary);
        cv::Mat result;
        cv::aruco::generateImageMarker(*dict, id, sidePixels, result, borderBits);
        *img = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_aruco_createArucoDetector(void *dictionary, void *parameters)
{
    cv_clear_error();

    try {
        cv::aruco::Dictionary dict = *static_cast<cv::aruco::Dictionary *>(dictionary);
        cv::aruco::DetectorParameters params;
        if (parameters)
            params = *static_cast<cv::aruco::DetectorParameters *>(parameters);
        return new cv::aruco::ArucoDetector(dict, params);
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_aruco_deleteArucoDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::aruco::ArucoDetector *>(detector);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_detectMarkers(void *detector, cv::Mat **image,
    cv::Mat **corners, int *cornerCount,
    cv::Mat **ids,
    cv::Mat **rejectedImgPoints, int *rejectedCount)
{
    cv_clear_error();

    try {
        cv::aruco::ArucoDetector *det = static_cast<cv::aruco::ArucoDetector *>(detector);
        std::vector<std::vector<cv::Point2f>> vecCorners;
        cv::Mat idsOut;
        std::vector<std::vector<cv::Point2f>> vecRejected;

        det->detectMarkers(**image, vecCorners, idsOut, vecRejected);

        if (ids)
            *ids = new cv::Mat(idsOut);

        if (cornerCount)
            *cornerCount = (int)vecCorners.size();
        if (corners) {
            for (int i = 0; i < (int)vecCorners.size(); i++) {
                corners[i] = new cv::Mat(cv::Mat(vecCorners[i], true).reshape(2, 1));
            }
        }

        if (rejectedCount)
            *rejectedCount = (int)vecRejected.size();
        if (rejectedImgPoints) {
            for (int i = 0; i < (int)vecRejected.size(); i++) {
                rejectedImgPoints[i] = new cv::Mat(cv::Mat(vecRejected[i], true).reshape(2, 1));
            }
        }

        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


static std::vector<std::vector<cv::Point2f>> matArrayToVecOfVecPoint2f(cv::Mat **mats, int count)
{
    std::vector<std::vector<cv::Point2f>> result;
    for (int i = 0; i < count; i++) {
        std::vector<cv::Point2f> pts;
        cv::Mat c = *mats[i];
        for (int j = 0; j < c.cols * c.rows; j++)
            pts.push_back(c.at<cv::Point2f>(j));
        result.push_back(pts);
    }
    return result;
}

CVAPI int cv_aruco_drawDetectedMarkers(cv::Mat **image, cv::Mat **corners, int cornerCount, cv::Mat **ids, CVScalar borderColor)
{
    cv_clear_error();

    try {
        auto vecCorners = matArrayToVecOfVecPoint2f(corners, cornerCount);
        cv::Scalar color(borderColor.v0, borderColor.v1, borderColor.v2, borderColor.v3);
        if (ids && *ids && !(*ids)->empty())
            cv::aruco::drawDetectedMarkers(**image, vecCorners, **ids, color);
        else
            cv::aruco::drawDetectedMarkers(**image, vecCorners, cv::noArray(), color);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_drawDetectedCornersCharuco(cv::Mat **image, cv::Mat **charucoCorners, cv::Mat **charucoIds, CVScalar cornerColor)
{
    cv_clear_error();

    try {
        cv::Scalar color(cornerColor.v0, cornerColor.v1, cornerColor.v2, cornerColor.v3);
        cv::aruco::drawDetectedCornersCharuco(**image, **charucoCorners,
            (charucoIds && *charucoIds && !(*charucoIds)->empty()) ? **charucoIds : cv::noArray(), color);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_drawDetectedDiamonds(cv::Mat **image, cv::Mat **diamondCorners, int count, cv::Mat **diamondIds, CVScalar borderColor)
{
    cv_clear_error();

    try {
        auto vecCorners = matArrayToVecOfVecPoint2f(diamondCorners, count);
        cv::Scalar color(borderColor.v0, borderColor.v1, borderColor.v2, borderColor.v3);
        if (diamondIds && *diamondIds && !(*diamondIds)->empty())
            cv::aruco::drawDetectedDiamonds(**image, vecCorners, **diamondIds, color);
        else
            cv::aruco::drawDetectedDiamonds(**image, vecCorners, cv::noArray(), color);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_aruco_createGridBoard(int markersX, int markersY, float markerLength, float markerSeparation, void *dictionary, cv::Mat **ids)
{
    cv_clear_error();

    try {
        cv::aruco::Dictionary dict = *static_cast<cv::aruco::Dictionary *>(dictionary);
        if (ids && *ids && !(*ids)->empty())
            return new cv::aruco::GridBoard(cv::Size(markersX, markersY), markerLength, markerSeparation, dict, **ids);
        else
            return new cv::aruco::GridBoard(cv::Size(markersX, markersY), markerLength, markerSeparation, dict);
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI void *cv_aruco_createCharucoBoard(int squaresX, int squaresY, float squareLength, float markerLength, void *dictionary)
{
    cv_clear_error();

    try {
        cv::aruco::Dictionary dict = *static_cast<cv::aruco::Dictionary *>(dictionary);
        return new cv::aruco::CharucoBoard(cv::Size(squaresX, squaresY), squareLength, markerLength, dict);
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_aruco_deleteBoard(void *board)
{
    cv_clear_error();

    try {
        delete static_cast<cv::aruco::Board *>(board);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_drawPlanarBoard(void *board, int outW, int outH, cv::Mat **img, int marginSize, int borderBits)
{
    cv_clear_error();

    try {
        cv::Mat result;
        static_cast<cv::aruco::Board *>(board)->generateImage(cv::Size(outW, outH), result, marginSize, borderBits);
        *img = new cv::Mat(result);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_aruco_createCharucoDetector(void *board, void *detectorParams)
{
    cv_clear_error();

    try {
        cv::aruco::CharucoBoard *b = static_cast<cv::aruco::CharucoBoard *>(board);
        cv::aruco::CharucoParameters charucoParams;
        cv::aruco::DetectorParameters detParams;
        if (detectorParams)
            detParams = *static_cast<cv::aruco::DetectorParameters *>(detectorParams);
        return new cv::aruco::CharucoDetector(*b, charucoParams, detParams);
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_aruco_deleteCharucoDetector(void *detector)
{
    cv_clear_error();

    try {
        delete static_cast<cv::aruco::CharucoDetector *>(detector);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_detectCharucoDiamond(cv::Mat **image,
    cv::Mat **markerCorners, int markerCount, cv::Mat **markerIds,
    float squareMarkerLengthRate,
    cv::Mat **diamondCorners, int *diamondCount, cv::Mat **diamondIds,
    cv::Mat **cameraMatrix, cv::Mat **distCoeffs)
{
    cv_clear_error();

    try {
        auto vecMarkerCorners = matArrayToVecOfVecPoint2f(markerCorners, markerCount);

        std::vector<std::vector<cv::Point2f>> vecDiamondCorners;
        cv::Mat vecDiamondIds;

        cv::aruco::detectCharucoDiamond(**image, vecMarkerCorners, **markerIds,
            squareMarkerLengthRate, vecDiamondCorners, vecDiamondIds,
            (cameraMatrix && *cameraMatrix && !(*cameraMatrix)->empty()) ? **cameraMatrix : cv::noArray(),
            (distCoeffs && *distCoeffs && !(*distCoeffs)->empty()) ? **distCoeffs : cv::noArray());

        if (diamondCount)
            *diamondCount = (int)vecDiamondCorners.size();
        if (diamondCorners) {
            for (int i = 0; i < (int)vecDiamondCorners.size(); i++) {
                diamondCorners[i] = new cv::Mat(cv::Mat(vecDiamondCorners[i], true).reshape(2, 1));
            }
        }
        if (diamondIds)
            *diamondIds = new cv::Mat(vecDiamondIds);

        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI int cv_aruco_estimatePoseSingleMarkers(cv::Mat **corners, int cornerCount,
    float markerLength, cv::Mat **cameraMatrix, cv::Mat **distCoeffs,
    cv::Mat **rvecs, cv::Mat **tvecs)
{
    cv_clear_error();

    try {
        auto vecCorners = matArrayToVecOfVecPoint2f(corners, cornerCount);

        float half = markerLength / 2.0f;
        std::vector<cv::Point3f> objPoints = {
            {-half,  half, 0},
            { half,  half, 0},
            { half, -half, 0},
            {-half, -half, 0}
        };

        cv::Mat rvecsMat(cornerCount, 3, CV_64F);
        cv::Mat tvecsMat(cornerCount, 3, CV_64F);

        for (int i = 0; i < cornerCount; i++) {
            cv::Mat rvec, tvec;
            cv::solvePnP(objPoints, vecCorners[i], **cameraMatrix, **distCoeffs, rvec, tvec);
            rvec.reshape(1, 1).copyTo(rvecsMat.row(i));
            tvec.reshape(1, 1).copyTo(tvecsMat.row(i));
        }

        *rvecs = new cv::Mat(rvecsMat);
        *tvecs = new cv::Mat(tvecsMat);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_estimatePoseBoard(cv::Mat **corners, int cornerCount, cv::Mat **ids,
    void *board, cv::Mat **cameraMatrix, cv::Mat **distCoeffs,
    cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess)
{
    cv_clear_error();

    try {
        auto vecCorners = matArrayToVecOfVecPoint2f(corners, cornerCount);
        cv::aruco::Board *b = static_cast<cv::aruco::Board *>(board);

        std::vector<cv::Point3f> objPoints;
        std::vector<cv::Point2f> imgPoints;
        b->matchImagePoints(vecCorners, **ids, objPoints, imgPoints);

        if (objPoints.empty())
            return 0;

        cv::solvePnP(objPoints, imgPoints, **cameraMatrix, **distCoeffs,
            **rvec, **tvec, useExtrinsicGuess != 0);
        return (int)objPoints.size();
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_estimatePoseCharucoBoard(cv::Mat **charucoCorners, cv::Mat **charucoIds,
    void *board, cv::Mat **cameraMatrix, cv::Mat **distCoeffs,
    cv::Mat **rvec, cv::Mat **tvec, int useExtrinsicGuess)
{
    cv_clear_error();

    try {
        cv::aruco::CharucoBoard *b = static_cast<cv::aruco::CharucoBoard *>(board);
        std::vector<cv::Point3f> boardObjPoints = b->getChessboardCorners();

        std::vector<cv::Point2f> vecCorners;
        (*charucoCorners)->copyTo(vecCorners);
        std::vector<int> vecIds;
        (*charucoIds)->copyTo(vecIds);

        std::vector<cv::Point3f> objPoints;
        std::vector<cv::Point2f> imgPoints;
        for (int i = 0; i < (int)vecIds.size(); i++) {
            int id = vecIds[i];
            if (id >= 0 && id < (int)boardObjPoints.size()) {
                objPoints.push_back(boardObjPoints[id]);
                imgPoints.push_back(vecCorners[i]);
            }
        }

        if (objPoints.size() < 4)
            return 0;

        bool valid = cv::solvePnP(objPoints, imgPoints, **cameraMatrix, **distCoeffs,
            **rvec, **tvec, useExtrinsicGuess != 0);
        return valid ? 1 : 0;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI double cv_aruco_calibrateCameraAruco(cv::Mat **corners, cv::Mat **ids, cv::Mat **counter,
    void *board, int imageW, int imageH,
    cv::Mat **cameraMatrix, cv::Mat **distCoeffs,
    cv::Mat **rvecs, cv::Mat **tvecs, int flags)
{
    cv_clear_error();

    try {
        cv::aruco::Board *b = static_cast<cv::aruco::Board *>(board);

        std::vector<int> markerCountPerFrame;
        (*counter)->copyTo(markerCountPerFrame);

        std::vector<int> allIds;
        (*ids)->copyTo(allIds);


        std::vector<std::vector<cv::Point3f>> objPointsPerView;
        std::vector<std::vector<cv::Point2f>> imgPointsPerView;

        int idx = 0;
        for (int f = 0; f < (int)markerCountPerFrame.size(); f++) {
            std::vector<std::vector<cv::Point2f>> frameCorners;
            std::vector<int> frameIds;
            for (int m = 0; m < markerCountPerFrame[f]; m++) {
                std::vector<cv::Point2f> pts;
                cv::Mat c = *corners[idx];
                for (int j = 0; j < c.cols * c.rows; j++)
                    pts.push_back(c.at<cv::Point2f>(j));
                frameCorners.push_back(pts);
                frameIds.push_back(allIds[idx]);
                idx++;
            }

            std::vector<cv::Point3f> objPts;
            std::vector<cv::Point2f> imgPts;
            cv::Mat frameIdsMat(frameIds);
            b->matchImagePoints(frameCorners, frameIdsMat, objPts, imgPts);

            if (!objPts.empty()) {
                objPointsPerView.push_back(objPts);
                imgPointsPerView.push_back(imgPts);
            }
        }

        std::vector<cv::Mat> rvecsOut, tvecsOut;
        double repErr = cv::calibrateCamera(objPointsPerView, imgPointsPerView,
            cv::Size(imageW, imageH), **cameraMatrix, **distCoeffs,
            rvecsOut, tvecsOut, flags);

        if (rvecs) {
            for (int i = 0; i < (int)rvecsOut.size(); i++)
                rvecs[i] = new cv::Mat(rvecsOut[i]);
        }
        if (tvecs) {
            for (int i = 0; i < (int)tvecsOut.size(); i++)
                tvecs[i] = new cv::Mat(tvecsOut[i]);
        }

        return repErr;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI double cv_aruco_calibrateCameraCharuco(cv::Mat **charucoCorners, cv::Mat **charucoIds,
    int imageCount, void *board, int imageW, int imageH,
    cv::Mat **cameraMatrix, cv::Mat **distCoeffs,
    cv::Mat **rvecs, cv::Mat **tvecs, int flags)
{
    cv_clear_error();

    try {
        cv::aruco::CharucoBoard *b = static_cast<cv::aruco::CharucoBoard *>(board);
        std::vector<cv::Point3f> boardObjPoints = b->getChessboardCorners();

        std::vector<std::vector<cv::Point3f>> objPointsPerView;
        std::vector<std::vector<cv::Point2f>> imgPointsPerView;

        for (int f = 0; f < imageCount; f++) {
            std::vector<cv::Point2f> cornersVec;
            charucoCorners[f]->copyTo(cornersVec);
            std::vector<int> idsVec;
            charucoIds[f]->copyTo(idsVec);

            std::vector<cv::Point3f> objPts;
            std::vector<cv::Point2f> imgPts;
            for (int i = 0; i < (int)idsVec.size(); i++) {
                int id = idsVec[i];
                if (id >= 0 && id < (int)boardObjPoints.size()) {
                    objPts.push_back(boardObjPoints[id]);
                    imgPts.push_back(cornersVec[i]);
                }
            }
            if (objPts.size() >= 4) {
                objPointsPerView.push_back(objPts);
                imgPointsPerView.push_back(imgPts);
            }
        }

        std::vector<cv::Mat> rvecsOut, tvecsOut;
        double repErr = cv::calibrateCamera(objPointsPerView, imgPointsPerView,
            cv::Size(imageW, imageH), **cameraMatrix, **distCoeffs,
            rvecsOut, tvecsOut, flags);

        if (rvecs) {
            for (int i = 0; i < (int)rvecsOut.size(); i++)
                rvecs[i] = new cv::Mat(rvecsOut[i]);
        }
        if (tvecs) {
            for (int i = 0; i < (int)tvecsOut.size(); i++)
                tvecs[i] = new cv::Mat(tvecsOut[i]);
        }

        return repErr;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return -1.0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}


CVAPI void *cv_aruco_createDetectorParameters()
{
    cv_clear_error();

    try {
        return new cv::aruco::DetectorParameters();
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return nullptr;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return nullptr;
    }
}

CVAPI int cv_aruco_deleteDetectorParameters(void *params)
{
    cv_clear_error();

    try {
        delete static_cast<cv::aruco::DetectorParameters *>(params);
        return 1;
    } catch (cv::Exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshWinSizeMin(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->adaptiveThreshWinSizeMin = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshWinSizeMax(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->adaptiveThreshWinSizeMax = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshWinSizeStep(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->adaptiveThreshWinSizeStep = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersAdaptiveThreshConstant(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->adaptiveThreshConstant = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMinMarkerPerimeterRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->minMarkerPerimeterRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMaxMarkerPerimeterRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->maxMarkerPerimeterRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersPolygonalApproxAccuracyRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->polygonalApproxAccuracyRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMinCornerDistanceRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->minCornerDistanceRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMinDistanceToBorder(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->minDistanceToBorder = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMinMarkerDistanceRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->minMarkerDistanceRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersCornerRefinementMethod(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->cornerRefinementMethod = static_cast<cv::aruco::CornerRefineMethod>(value); return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersCornerRefinementWinSize(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->cornerRefinementWinSize = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersCornerRefinementMaxIterations(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->cornerRefinementMaxIterations = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersCornerRefinementMinAccuracy(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->cornerRefinementMinAccuracy = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMarkerBorderBits(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->markerBorderBits = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersPerspectiveRemovePixelPerCell(void *params, int value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->perspectiveRemovePixelPerCell = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersPerspectiveRemoveIgnoredMarginPerCell(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->perspectiveRemoveIgnoredMarginPerCell = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMaxErroneousBitsInBorderRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->maxErroneousBitsInBorderRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersMinOtsuStdDev(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->minOtsuStdDev = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}

CVAPI int cv_aruco_setDetectorParametersErrorCorrectionRate(void *params, double value)
{
    cv_clear_error();

    try { static_cast<cv::aruco::DetectorParameters *>(params)->errorCorrectionRate = value; return 1; }
    catch (cv::Exception &e) { cv_set_error_cstr(e.what()); return 0; } catch (const std::exception &e) {
        cv_set_error_cstr(e.what());
        return 0;
    } catch (...) {
        cv_set_error_literal("unknown error");
        return 0;
    }
}
