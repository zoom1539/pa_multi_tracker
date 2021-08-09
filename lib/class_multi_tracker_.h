#pragma once

// std
#include <opencv2/opencv.hpp>
#include "class_tracker.h"
#include "class_detector.h"

#include "class_multi_tracker.h"

class _MultiTracker
{
public:
    _MultiTracker();
    ~_MultiTracker();

public:
    bool init(const std::string &engine_path_);
    bool run(const cv::Mat &img_, 
             std::vector<std::vector<TrackedBox> > &vec_rects_tracked_);
    

private:
    Detector _detector;
    Tracker _tracker[ClassNum];

};
