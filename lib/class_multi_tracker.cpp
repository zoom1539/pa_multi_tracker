#include "class_multi_tracker.h"
#include "class_multi_tracker_.h"

class MultiTracker::Impl
{
public:
    _MultiTracker _multi_tracker;
};

MultiTracker::MultiTracker() : _impl(new MultiTracker::Impl())
{
}

MultiTracker::~MultiTracker()
{
    delete _impl;
    _impl = NULL;
}

bool MultiTracker::init(const std::string &engine_path_)
{
    return _impl->_multi_tracker.init(engine_path_);
}

bool MultiTracker::run(const cv::Mat &img_, 
             std::vector<std::vector<TrackedBox> > &vec_rects_tracked_)
{
    return _impl->_multi_tracker.run(img_, vec_rects_tracked_);
}

