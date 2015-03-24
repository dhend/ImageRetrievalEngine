#include "ImageIndexBuilding.h"
#include "ImageQuery.h"
#include <math.h>
#include <fstream>

using namespace std;
using namespace cv;

int main() {
	const int query_num = 5;
	std::string query_img_name;
	std::string img_dataset_path;
	string index_file = "index.txt";
	int search_flag = 0;
	std::cout << "1.build index library, 2.search the image" << std::endl;
	std::cin >> search_flag;
	if (search_flag == 1) {
		std::cout << "Please input the name of image document:" << std::endl;
		std::cin >> img_dataset_path;
		ImageIndexBuilding build_index;
		build_index.BuildingIndex(img_dataset_path, index_file);
	} else if (search_flag == 2) {
		std::cout << "Please input the name of query image:" << std::endl;
		std::cin >> query_img_name;
		Mat query_img = imread(query_img_name);
		ImageQuery search_img;
		search_img.QueryImage(query_img, query_num, index_file);
	} else
		std::cout << "error, please input again..." << std::endl;
	return 0;
}
