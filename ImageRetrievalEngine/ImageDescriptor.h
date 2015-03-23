//
//  ImageDescriptor.h
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-2-27.
//  Copyright (c) 2015�� XuRui. All rights reserved.
//

#ifndef __ImageRetrievalEngine__ImageDescriptor__
#define __ImageRetrievalEngine__ImageDescriptor__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#endif /* defined(__ImageRetrievalEngine__ImageDescriptor__) */

class ColorAutoCorrelogram{
public:
    void CreateColorAutoCorrelogram(const cv::Mat& img, std::vector<double>& correlogram);
    double CorrelogramMatching(const std::vector<double>& correlogram1, const std::vector<double>& correlogram2);
};
