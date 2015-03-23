//
//  ImageIndexBuilding.cpp
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-22.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//

#include "ImageIndexBuilding.h"
#include "ImageDescriptor.h"
#include "ImagePreProcess.h"

void ImageIndexBuilding::BuildingIndex(const std::string& img_path, std::string& index_file){
	ImagePreProcess img_preprocess;
	ColorAutoCorrelogram img_match;
	cv::glob(img_path + "/*.jpg", image_dataset);
	std::ofstream outfile;
	outfile.open(index_file);
	for (int i = 0; i < image_dataset.size(); i++) {
		candidate_img = cv::imread(image_dataset[i]);
		outfile << image_dataset[i] << " ";
		std::vector<double> correlogram(360, 0.0);
		img_preprocess.ImgResizeProcess(candidate_img, resized_img);
		cvtColor(resized_img, hsv_img, CV_BGR2HSV);
		img_preprocess.HSVimgQuantization(hsv_img, qua_img);
		img_match.CreateColorAutoCorrelogram(qua_img, correlogram);
		for (std::vector<double>::iterator iter = correlogram.begin(); iter < correlogram.end(); ++iter) {
			outfile << *iter << " ";
		}
		std::cout << "Building " << i << " index" << std::endl;
	}
}