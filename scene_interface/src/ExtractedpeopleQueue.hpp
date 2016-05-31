#include <boost/interprocess/offset_ptr.hpp>
#include <vector>

#include "Person.hpp"

namespace scene_interface {
	class ExtractedpeopleQueue {
		public:
			ExtractedpeopleQueue(unsigned int size);
			
			bool empty() const;
			bool full() const;
	
			void push(boost::interprocess::offset_ptr<std::vector<boost::interprocess::offset_ptr<scene_interface::Person> > >& item);
	
			boost::interprocess::offset_ptr<std::vector<boost::interprocess::offset_ptr<scene_interface::Person> > > pop();
		private:
			unsigned int size;
			unsigned int head = 0;
			unsigned int tail = 0;
			boost::interprocess::offset_ptr<std::vector<boost::interprocess::offset_ptr<scene_interface::Person> > > items [128]; //todo fix static size
	};
}
