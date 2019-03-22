//#include "pch.h"
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::ifstream;
using std::string;

using LandmarksVector = vector<vector<cv::Point2f>>;


bool detectFacesLandmarks( const cv::Mat& image
	                     , LandmarksVector& resultVector);

void getFacesBoundaries( const cv::Mat& image
	                   , LandmarksVector& resultVector);

void getTriangulateGridIndices( const cv::Rect& rect
                              , const LandmarksVector& landmarks
                              , vector<vector<cv::Vec3i>>& indices );

void applyAffineTransform( cv::Mat& warpImage
	                     , cv::Mat& src
	                     , vector<cv::Point2f>& srcTri
	                     , vector<cv::Point2f>& dstTri );

void warpTriangle( const cv::Mat& img1
	             , cv::Mat& img2
	             , vector<cv::Point2f>& t1
	             , vector<cv::Point2f>& t2 );

void substituteFace( const cv::Mat& sourceImage
	               , const vector<cv::Point2f>& sourceFaceLandmarks
                   , const cv::Mat& targetImage
                   , const vector<cv::Point2f>& targetFaceLandmarks
                   , cv::Mat& output);


int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Bad arguments count!" << std::endl;
		return -1;
	}

	try {
		cv::Mat image = cv::imread(argv[1]);
		cv::imshow("Before", image);

		cv::Mat output = image.clone();

		LandmarksVector faces;
		detectFacesLandmarks(image, faces);

		for (int i = 0, size = faces.size(); i < size; ++i) {
			substituteFace(image, faces[i], output, faces[(i + 1) % size], output);
		}

		cv::imshow("After", output);
		cv::waitKey();
	}
	catch (cv::Exception ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}


bool detectFacesLandmarks(const cv::Mat& image, LandmarksVector& resultVector)
{
	cv::CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");

	cv::Ptr<cv::face::Facemark> facemark = cv::face::FacemarkLBF::create();
	facemark->loadModel("lbfmodel.yaml");

	cv::Mat semitone;
	cv::cvtColor(image, semitone, cv::COLOR_BGR2GRAY);

	vector<cv::Rect> detectedFacesZones;
	faceDetector.detectMultiScale(semitone, detectedFacesZones);

	return facemark->fit(image, detectedFacesZones, resultVector);
}

void getFacesBoundaries(const cv::Mat& image, LandmarksVector& resultVector)
{
	if (resultVector.size() > 0) {
		resultVector.clear();
	}

	LandmarksVector allLandmarks;
	detectFacesLandmarks(image, allLandmarks);

	for (auto& faceLandmarks : allLandmarks) {
		vector<cv::Point2f> facesBoundaries;
		cv::convexHull(faceLandmarks, facesBoundaries);

		resultVector.push_back(std::move(facesBoundaries));
	}
}

void getTriangulateGridIndices(const cv::Rect& rect, const LandmarksVector& landmarksVec, vector<vector<cv::Vec3i>>& indicesVec) 
{
	if (indicesVec.size() > 0) {
		indicesVec.clear();
	}

	for (auto& landmarks : landmarksVec) {
		cv::Subdiv2D subdiv{ rect };
		subdiv.insert(landmarks);

		vector<cv::Vec6f> triangleList;
		subdiv.getTriangleList(triangleList);

		vector<cv::Point2f> pt(3);
		cv::Vec3i ind;

		indicesVec.push_back({});
		vector<cv::Vec3i>& indices = indicesVec[indicesVec.size() - 1];

		for (size_t i = 0; i < triangleList.size(); i++)
		{
			cv::Vec6f t = triangleList[i];
			pt[0] = cv::Point2f(t[0], t[1]);
			pt[1] = cv::Point2f(t[2], t[3]);
			pt[2] = cv::Point2f(t[4], t[5]);

			if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])) {
				for (int j = 0; j < 3; j++) {
					for (size_t k = 0; k < landmarks.size(); k++) {
						if (abs(pt[j].x - landmarks[k].x) < 1.0 && abs(pt[j].y - landmarks[k].y) < 1) {
							ind[j] = k;
							
						}
					}
				}

				indices.push_back(ind);
			}
		}
	}
}

void applyAffineTransform(cv::Mat& warpImage, cv::Mat& src, vector<cv::Point2f>& srcTri, vector<cv::Point2f>& dstTri)
{
	cv::Mat warpMat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, warpImage, warpMat, warpImage.size(), cv::INTER_LINEAR, cv::BORDER_REFLECT_101);
}

void warpTriangle(const cv::Mat& img1, cv::Mat& img2, vector<cv::Point2f>& t1, vector<cv::Point2f>& t2)
{
	cv::Rect r1 = boundingRect(t1);
	cv::Rect r2 = boundingRect(t2);

	vector<cv::Point2f> t1Rect, t2Rect;
	vector<cv::Point> t2RectInt;
	for (int i = 0; i < 3; i++)
	{

		t1Rect.push_back(cv::Point2f(t1[i].x - r1.x, t1[i].y - r1.y));
		t2Rect.push_back(cv::Point2f(t2[i].x - r2.x, t2[i].y - r2.y));
		t2RectInt.push_back(cv::Point(t2[i].x - r2.x, t2[i].y - r2.y));

	}

	cv::Mat mask = cv::Mat::zeros(r2.height, r2.width, CV_32FC3);
	fillConvexPoly(mask, t2RectInt, cv::Scalar(1.0, 1.0, 1.0), 16, 0);

	cv::Mat img1Rect;
	img1(r1).copyTo(img1Rect);

	cv::Mat img2Rect = cv::Mat::zeros(r2.height, r2.width, img1Rect.type());

	applyAffineTransform(img2Rect, img1Rect, t1Rect, t2Rect);

	cv::multiply(img2Rect, mask, img2Rect);
	cv::multiply(img2(r2), cv::Scalar(1.0, 1.0, 1.0) - mask, img2(r2));
	img2(r2) = img2(r2) + img2Rect;
}


void substituteFace( const cv::Mat& sourceImage
	               , const vector<cv::Point2f>& sourceFaceLandmarks
	               , const cv::Mat& targetImage
	               , const vector<cv::Point2f>& targetFaceLandmarks
	               , cv::Mat& output)
{
	cv::Mat sourceImageBase = sourceImage.clone();
	cv::Mat sourceImageWarped = sourceImage.clone();
	sourceImageBase.convertTo(sourceImageBase, CV_32F);
	sourceImageWarped.convertTo(sourceImageWarped, CV_32F);

	vector<cv::Point2f> hull1;
	vector<cv::Point2f> hull2;
	vector<int> hullIndex;

	convexHull(targetFaceLandmarks, hullIndex, false, false);

	for (int i = 0; i < hullIndex.size(); i++) {
		hull1.push_back(sourceFaceLandmarks[hullIndex[i]]);
		hull2.push_back(targetFaceLandmarks[hullIndex[i]]);
	}

	vector<vector<int>> dt;
	cv::Rect rect{ 0, 0, sourceImageWarped.cols, sourceImageWarped.rows };
	cv::Subdiv2D subdiv(rect);

	subdiv.insert(hull2);

	vector<cv::Vec6f> triangleList;
	subdiv.getTriangleList(triangleList);
	vector<cv::Point2f> pt(3);
	vector<int> ind(3);

	for (size_t i = 0; i < triangleList.size(); i++)
	{
		cv::Vec6f t = triangleList[i];
		pt[0] = cv::Point2f(t[0], t[1]);
		pt[1] = cv::Point2f(t[2], t[3]);
		pt[2] = cv::Point2f(t[4], t[5]);

		if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])) {
			for (int j = 0; j < 3; j++)
				for (size_t k = 0; k < hull2.size(); k++)
					if (abs(pt[j].x - hull2[k].x) < 1.0 && abs(pt[j].y - hull2[k].y) < 1)
						ind[j] = k;

			dt.push_back(ind);
		}
	}

	for (size_t i = 0; i < dt.size(); i++)
	{
		vector<cv::Point2f> t1, t2;

		for (size_t j = 0; j < 3; j++)
		{
			t1.push_back(hull1[dt[i][j]]);
			t2.push_back(hull2[dt[i][j]]);
		}

		warpTriangle(sourceImageBase, sourceImageWarped, t1, t2);

	}

	vector<cv::Point> hull8U;
	for (int i = 0; i < hull2.size(); i++)
	{
		cv::Point pt(hull2[i].x, hull2[i].y);
		hull8U.push_back(pt);
	}

	cv::Mat mask = cv::Mat::zeros(targetImage.rows, targetImage.cols, targetImage.depth());
	fillConvexPoly(mask, &hull8U[0], hull8U.size(), cv::Scalar(255, 255, 255));

	cv::Rect r = boundingRect(hull2);
	cv::Point center = (r.tl() + r.br()) / 2;

	sourceImageWarped.convertTo(sourceImageWarped, CV_8UC3);
	seamlessClone(sourceImageWarped, targetImage, mask, center, output, cv::NORMAL_CLONE);
}
