#ifndef PEOPLEEXTRACTORINTERFACESMA_IMAGE_H
#define PEOPLEEXTRACTORINTERFACESMA_IMAGE_H

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "RGB.hpp"

namespace peopleextractor_interface_sma {
	//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
	//This allocator will allow placing containers in the segment
	typedef boost::interprocess::allocator<unsigned char, boost::interprocess::managed_shared_memory::segment_manager> RowColumnGreySMA;
	
	//Alias a vector that uses the previous STL-like allocator so that allocates its values from the segment
	typedef boost::interprocess::vector<unsigned char, RowColumnGreySMA> RowColumnGrey;
	
	class Image {
	 public:
	    Image(unsigned int width, unsigned int height, boost::interprocess::managed_shared_memory* segment);
	
			inline const unsigned int getWidth() const {
				return this->width;
			}
			inline const unsigned int getHeight() const {
				return this->height;
			}
			
			inline const unsigned char getRed(unsigned int x, unsigned int y) const {
				return this->row_column_rgb->at((x * this->height + y) * 3);
			}
			inline const unsigned char getGreen(unsigned int x, unsigned int y) const {
				return this->row_column_rgb->at((x * this->height + y) * 3 + 1);
			}
			inline const unsigned char getBlue(unsigned int x, unsigned int y) const {
				return this->row_column_rgb->at((x * this->height + y) * 3 + 2);
			}
			
			inline void setRGB(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue) {
				unsigned int offset = (x * this->height + y) * 3;
				this->row_column_rgb->at(offset) = red;
				this->row_column_rgb->at(offset + 1) = green;
				this->row_column_rgb->at(offset + 2) = blue;
			}
	 
	 private:
			// all pixels
	    boost::interprocess::offset_ptr<RowColumnGrey> row_column_rgb;
	
	    // dimensions
	    const unsigned int width;
	    const unsigned int height;
	};
}

#endif //PEOPLEEXTRACTORINTERFACESMA_IMAGE_H
