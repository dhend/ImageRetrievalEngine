//
//  ImageQuery.cpp
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-22.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//

#include "ImageQuery.h"
#include "ImageDescriptor.h"
#include "ImagePreProcess.h"

void ImageQuery::QueryImage(const cv::Mat& img, const int& query_num, const std::string& index_file) {
	ImagePreProcess img_preprocess;
	ColorAutoCorrelogram img_match;
	std::vector<double> correlogram_target(360, 0.0);
	std::ifstream infile(index_file);
	img_preprocess.ImgResizeProcess(img, resized_query_img);
	cvtColor(resized_query_img, hsv_query_img, CV_BGR2HSV);
	img_preprocess.HSVimgQuantization(hsv_query_img, qua_query_img);
	img_match.CreateColorAutoCorrelogram(qua_query_img, correlogram_target);
	while (infile.good()) {
		infile >> file_name;
		std::vector<double> correlogram_candidates;
		correlogram_candidates.clear();
		for (int j = 0; j < 360; ++j) {
			infile >> data;
			correlogram_candidates.push_back(data);
		}
		match_res = img_match.CorrelogramMatching(correlogram_target, correlogram_candidates);
		index_map.push_back(std::make_pair(match_res, file_name));
	}
	sort(index_map.begin(), index_map.end());
	for (int i = 0; i < query_num; ++i) {
		res_img = cv::imread(index_map[i].second);
		imwrite("res\\" + index_map[i].second, res_img);
	}
}