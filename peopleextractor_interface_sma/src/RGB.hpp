#ifndef PEOPLEEXTRACTORINTERFACESMA_RGB_H
#define PEOPLEEXTRACTORINTERFACESMA_RGB_H

namespace peopleextractor_interface_sma {
	class RGB {
	 public:
	    RGB(const unsigned char red, const unsigned char green, const unsigned char blue);
	 
			unsigned char red;
			unsigned char green;
			unsigned char blue;

			const unsigned char getRed() const;
			const unsigned char getGreen() const;
			const unsigned char getBlue() const;
	};
}

#endif //PEOPLEEXTRACTORINTERFACESMA_RGB_H
