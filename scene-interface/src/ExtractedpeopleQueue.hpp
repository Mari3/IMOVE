#include <boost/interprocess/offset_ptr.hpp>

#include "Person.hpp"

class ExtractedpeopleQueue {
	public:
		ExtractedpeopleQueue(unsigned int size);
		
		bool empty() const;
		bool full() const;

		void push(boost::interprocess::offset_ptr<Person> item);

		boost::interprocess::offset_ptr<Person> pop();
	private:
		unsigned int size;
		unsigned int head = 0;
		unsigned int tail = 0;
		boost::interprocess::offset_ptr<Person> items [128]; //todo fix static size
};
