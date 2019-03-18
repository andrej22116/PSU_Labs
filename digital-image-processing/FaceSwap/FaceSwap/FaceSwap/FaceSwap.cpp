//#include "pch.h"
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>

#include <vector>

struct SourceImages {
	cv::Mat firstInputImage;
	cv::Mat secondInputImage;

	SourceImages(std::string_view first, std::string_view second) :
		firstInputImage(cv::imread(cv::String(first), cv::IMREAD_COLOR)),
		secondInputImage(cv::imread(cv::String(second), cv::IMREAD_COLOR))
	{}

	operator bool() {
		return firstInputImage.data && secondInputImage.data;
	}
};


int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	SourceImages sourceImages{ argv[1], argv[1] };
	if ( !sourceImages ) {
		std::cout << "Could not open or find images" << std::endl;
		return -2;
	}

	auto frontalFaceDetector = dlib::get_frontal_face_detector();
	auto firstImageFaceRects = frontalFaceDetector(dlib::cv_image<dlib::bgr_pixel>(sourceImages.firstInputImage));
	auto secondImageFaceRects = frontalFaceDetector(dlib::cv_image<dlib::bgr_pixel>(sourceImages.secondInputImage));

	std::vector<int> firstImageFacePoints{
		firstImageFaceRects[0].top(),
		firstImageFaceRects[0].right(),
		firstImageFaceRects[0].bottom(),
		firstImageFaceRects[0].left()
	};
	std::vector<int> secondImageFacePoints{
		secondImageFaceRects[0].top(),
		secondImageFaceRects[0].right(),
		secondImageFaceRects[0].bottom(),
		secondImageFaceRects[0].left()
	};
	std::vector<int> firstFaceHullPointsSet{};
	std::vector<int> secondFaceHullPointsSet{};
	cv::convexHull(firstImageFacePoints, firstFaceHullPointsSet, false, false);
	cv::convexHull(secondImageFacePoints, secondFaceHullPointsSet, false, false);


	static std::string firstNameWindowOfResult = "First result image";
	static std::string secondNameWindowOfResult = "Second result image";
	cv::namedWindow(firstNameWindowOfResult, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(secondNameWindowOfResult, cv::WINDOW_AUTOSIZE);
	imshow(firstNameWindowOfResult, sourceImages.firstInputImage);
	imshow(secondNameWindowOfResult, sourceImages.secondInputImage);

	cv::waitKey(0);
	return 0;
}
