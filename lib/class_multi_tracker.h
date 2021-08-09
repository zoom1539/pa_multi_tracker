#pragma once

#include "opencv2/opencv.hpp"
#include "class_tracker.h"

const int ClassNum = 3;

class MultiTracker
{
public:
    explicit MultiTracker();
    ~MultiTracker();

public:
    bool init(const std::string &engine_path_);
    bool run(const cv::Mat &img_, 
             std::vector<std::vector<TrackedBox> > &vec_rects_tracked_);
    

private:
    MultiTracker(const MultiTracker &);
    const MultiTracker &operator=(const MultiTracker &);

    class Impl;
    Impl *_impl;
};
