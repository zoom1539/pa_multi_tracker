#include "class_multi_tracker_.h"

_MultiTracker::_MultiTracker() 
{
	
}
_MultiTracker::~_MultiTracker() 
{
   
}
bool _MultiTracker::init(const std::string &engine_path_)
{
	return _detector.init(engine_path_);
}

bool _MultiTracker::run(const cv::Mat &img_, 
             			std::vector<std::vector<TrackedBox> > &vec_rects_tracked_)
{
	//detect
	std::vector<cv::Mat> imgs;
	imgs.push_back(img_);

	std::vector<std::vector<Detection> > vec_detections;
	bool is_detect = _detector.detect(imgs, vec_detections);
	if (!is_detect || (0 == vec_detections.size()))
	{
		return false;
	}

	// track
	std::vector<Detection> detections = vec_detections[0];

	std::vector<cv::Rect> rects[ClassNum];
	for (int i = 0; i < detections.size(); i++)
	{
		rects[int(detections[i].class_id)].push_back(detections[i].rect);
	}

	for (int i = 0; i < ClassNum; i++)
	{
		std::vector<TrackedBox> rects_tracked;
		_tracker[i].run(rects[i], img_.size(), rects_tracked);
		vec_rects_tracked_.push_back(rects_tracked);
	}

	return true;
}