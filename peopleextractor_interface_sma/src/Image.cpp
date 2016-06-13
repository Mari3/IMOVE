#include "Image.hpp"

using namespace peopleextractor_interface_sma;

Image::Image(unsigned int width, unsigned int height, boost::interprocess::managed_shared_memory* segment) : width(width), height(height) {
	const RowColumnGreySMA row_column_grey_sma(segment->get_segment_manager());
	this->row_column_rgb = segment->construct<RowColumnGrey>(boost::interprocess::anonymous_instance)(row_column_grey_sma);
	for (unsigned int x = 0; x < this->width; ++x) {
		for (unsigned int y = 0; y < this->height; ++y) {
			this->row_column_rgb->push_back(0);
			this->row_column_rgb->push_back(0);
			this->row_column_rgb->push_back(0);
		}
	}
}

