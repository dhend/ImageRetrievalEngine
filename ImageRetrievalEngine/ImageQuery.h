//
//  ImageQuery.h
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-22.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//


#ifndef __ImageRetrievalEngine__ImageQuery__
#define __ImageRetrievalEngine__ImageQuery__

#include <math.h>
#include <fstream>
#include <opencv2/opencv.hpp>

class ImageQuery {
public:
	void QueryImage(const cv::Mat& img, const int& query_num, const std::string& index_file);
private:
	cv::Mat resized_query_img;
	cv::Mat hsv_query_img;
	cv::Mat qua_query_img;
	cv::Mat res_img;
	std::vector<double> correlogram_target;
	std::vector<std::pair<double, std::string> > index_map;
	double data, match_res;
	std::string file_name;
};

#endif /* defined(__ImageRetrievalEngine__ImageQuery__) */
