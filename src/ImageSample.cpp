#include "ImageSample.h"

ImageSample::ImageSample()
{
}

ImageSample::~ImageSample()
{
}

void ImageSample::get()
{
	if (idx == 0) {
		Sample = img1;
	}
	else {
		Sample = img2;
	}
}

void ImageSample::set()
{
	Sample.update();

	if (idx == 0) {
		img1 = Sample;
	}
	else {
		img2 = Sample;
	}
}
