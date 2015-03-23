#include "ImageIndexBuilding.h"
#include "ImageQuery.h"
#include <math.h>
#include <fstream>

using namespace std;
using namespace cv;

int main() {
	const int query_num = 5;
	Mat query_img = imread("jpg\\100201.jpg");
	string index_file = "index1.txt";
	string img_dataset_path = "jpg";
	ImageIndexBuilding build_index;
	ImageQuery search_img;
//	build_index.BuildingIndex(img_dataset_path, index_file);
	search_img.QueryImage(query_img, query_num, index_file);
	return 0;
}