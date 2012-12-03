#ifndef _OBTSHAPES_SHAPE_H
#define _OBTSHAPES_SHAPE_H

#include <vector>
#include <cv.h>

namespace obt {

class Shape {
public:
	virtual cv::Point2f centroid() const = 0;
	virtual cv::Rect boundingRect() const = 0;
	virtual cv::RotatedRect boundingRotatedRect() const = 0;

	virtual void getPixels(std::vector<cv::Point>& result) const = 0;
};

}

#endif