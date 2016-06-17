#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <opencv2/core/persistence.hpp>
#include <assert.h>

// Class for reading configuration from yml node
class Configuration {
	public:
		/**
		 * Setup properties for configuration.
		 **/
		Configuration();
	
	protected:
		/**
		 * Reads an unsigned int from configuration node using given name. assert fails when < 0
		 * 
		 * @param fn       opencv yml configuration node
		 * @param name_yml name of unsigned int property in yml configuration
		 **/
		static inline unsigned int read(cv::FileStorage fn, char const* name_yml) {
				signed int   signed_int;
		  unsigned int unsigned_int;
			assert(!fn[name_yml].isNone());
			fn[name_yml] >> signed_int;
			// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
			assert(signed_int >= 0);
			unsigned_int = (unsigned int) signed_int;
			return unsigned_int;
		}

		/**
		 * Creates an unsigned int from configuration node using given name and if not exists use default. 0 when < 0
		 *
		 * @param fn                   opencv yml configuration node
		 * @param name_yml             name of unsigned int property in yml configuration
		 * @param default_unsigned_int if not given returns this default unsigned int
		 **/
		static inline unsigned int create(cv::FileStorage fn, char const* name_yml, unsigned int default_unsigned_int) {
				signed int   signed_int;
		  unsigned int unsigned_int;
			if (fn[name_yml].isNone()) {
				unsigned_int = default_unsigned_int;
			} else {
				fn[name_yml] >> signed_int;
				// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
				if (signed_int < 0) {
					unsigned_int = 0;
				} else {
					unsigned_int = (unsigned int) signed_int;
				}
			}
			return unsigned_int;
		}
};

#endif // CONFIGURATION_H
