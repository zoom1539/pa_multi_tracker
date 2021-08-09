#include "class_multi_tracker.h"
#include <sstream>

#define CNUM (20)
int main()
{
	//
	cv::RNG rng(0xFFFFFFFF);
	cv::Scalar_<int> randColor[CNUM];
	for (int i = 0; i < CNUM; i++)
		rng.fill(randColor[i], cv::RNG::UNIFORM, 0, 256);
	
	//
	MultiTracker multi_tracker;

	std::string engine_path = "../lib/extra/detector/lib/mine_car.engine";
	multi_tracker.init(engine_path);

	cv::VideoCapture cap;
	cap.open("../data/test1.mp4");

	cv::Mat img;
	int cnt = 0;
	while (cap.read(img))
    {
        std::vector<std::vector<TrackedBox> > vec_rects_tracked;
		multi_tracker.run(img, vec_rects_tracked);

		for (int i = 0; i < ClassNum; i++)
		{
			for (int j = 0; j < vec_rects_tracked[i].size(); j++)
			{
				cv::rectangle(img, vec_rects_tracked[i][j].rect, randColor[i], 2);
				cv::putText(img, std::to_string(i) + " " + std::to_string((int)vec_rects_tracked[i][j].id), 
							cv::Point(vec_rects_tracked[i][j].rect.x, vec_rects_tracked[i][j].rect.y - 1), 
							cv::FONT_HERSHEY_PLAIN, 1.2, randColor[i], 2);
			}
		}
		{
				std::stringstream ss;
				// ss << "../data/output/" << i * 15 << ".jpg";
				ss << "../data/output/0.jpg";
				cv::imwrite(ss.str(), img);
				std::cout << cnt++ << std::endl;
				std::cin.get();
			}
    }
	return 0;
}