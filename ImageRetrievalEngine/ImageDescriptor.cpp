//
//  ImageDescriptor.cpp
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-2-27.
//  Copyright (c) 2015年 XuRui. All rights reserved.
//

#include "ImageDescriptor.h"

void ColorAutoCorrelogram::CreateColorAutoCorrelogram(const cv::Mat& img, std::vector<double>& correlogram) {
    cv::Mat img_HSV;
    const int distance = 5;
    const int color_num = 90;
    std::vector<int> pix_num(color_num, 0);
    std::vector<cv::Mat> splited;
    cv::cvtColor(img, img_HSV, CV_BGR2HSV);
    cv::split(img_HSV, splited);
    cv::Mat img_H = splited[0];
    cv::Mat img_S = splited[1];
    
    for (int i = 0; i < img.rows; ++i) {
        uchar *data_H = img_H.ptr<uchar>(i);
        uchar *data_S = img_S.ptr<uchar>(i);
        for (int j = 0; j < img.cols; ++j) {
            int color_H = (int)data_H[j] / 2;
            int color_S = (int)data_S[j] / 3;
            pix_num[color_H]++;
            for (int d = 1; d <= 2 * distance; d = d + 2) {
                int samecolor_num = 0;
                int total_num = 0;
                //distance = max{|x1 - x2|, |y1 - y2|}
                //up boundary
                for (int up_row = i - d, col = j - d; col < j + d; ++col) {
                    if (up_row < 0) {
                        break;
                    } if (col < 0 || col >= img_H.cols) {
                        continue;
                    }
                    uchar color_H_uchar = img_H.at<uchar>(up_row, col);
                    uchar color_S_uchar = img_S.at<uchar>(up_row, col);
                    int color_H_d = ((int) color_H_uchar) / 2;
                    int color_S_d = ((int) color_S_uchar) / 3;
                    if (abs(color_H - color_H_d) < 3 && abs(color_S - color_S_d) < 3) {
                        samecolor_num++;
                    }
                    total_num++;
                }
                //down boudary
                for (int down_row = i + d, col = j - d; col < j + d; ++col) {
                    if (down_row >= img_H.rows) {
                        break;
                    } if (col < 0 || col >= img_H.cols) {
                        continue;
                    }
                    uchar color_H_uchar = img_H.at<uchar>(down_row, col);
                    uchar color_S_uchar = img_S.at<uchar>(down_row, col);
                    int color_H_d = ((int) color_H_uchar) / 2;
                    int color_S_d = ((int) color_S_uchar) / 3;
                    if (abs(color_H - color_H_d) < 3 && abs(color_S - color_S_d) < 3) {
                        samecolor_num++;
                    }
                    total_num++;
                }
                //left boudary
                for (int row = i - d, left_col = j - d; row < i + d; ++row) {
                    if (left_col < 0) {
                        break;
                    } if (row < 0 || row >= img_H.rows) {
                        continue;
                    }
                    uchar color_H_uchar = img_H.at<uchar>(row, left_col);
                    uchar color_S_uchar = img_S.at<uchar>(row, left_col);
                    int color_H_d = ((int) color_H_uchar) / 2;
                    int color_S_d = ((int) color_S_uchar) / 3;
                    if (abs(color_H - color_H_d) < 3 && abs(color_S - color_S_d) < 3) {
                        samecolor_num++;
                    }
                    total_num++;
                }
                //right boudary
                for (int row = i - d, right_col = j + d; row < i + d; ++row) {
                    if (right_col >= img_H.cols) {
                        break;
                    } if (row < 0 || row >= img_H.rows) {
                        continue;
                    }
                    uchar color_H_uchar = img_H.at<uchar>(row, right_col);
                    uchar color_S_uchar = img_S.at<uchar>(row, right_col);
                    int color_H_d = ((int) color_H_uchar) / 2;
                    int color_S_d = ((int) color_S_uchar) / 3;
                    if (abs(color_H - color_H_d) < 3&& abs(color_S - color_S_d) < 3) {
                        samecolor_num++;
                    }
                    total_num++;
                }
                correlogram[(d / 2 - 1) * color_num + color_H] += (double)samecolor_num / (double)total_num;
            }
        }
    }
    for(int correlogram_row = 0; correlogram_row < distance; ++correlogram_row) {
        for(int correlogram_col = 0; correlogram_col < color_num; ++correlogram_col) {
            if (pix_num[correlogram_col] != 0) {
                correlogram[correlogram_row * color_num + correlogram_col] = correlogram[correlogram_row * color_num + correlogram_col] / pix_num[correlogram_col];
            }
        }
    }
}

double ColorAutoCorrelogram::CorrelogramMatching(const std::vector<double>& correlogram1, const std::vector<double>& correlogram2) {
    const int distance = 5;
    const int color_num = 90;
    double confidenceValue = 0;
    for(int i = 0; i < distance; i++) {
        for(int j = 0; j < color_num; j++) {
            double value = (std::abs) ( (correlogram1[i * color_num + j] - correlogram2[i * color_num + j])  /  (1 + correlogram1[i * color_num + j] + correlogram1[i * color_num + j]) );
            confidenceValue = confidenceValue + value;
        }
    }
    return confidenceValue;
}
