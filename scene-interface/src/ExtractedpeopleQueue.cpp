#include "ExtractedpeopleQueue.hpp"

ExtractedpeopleQueue::ExtractedpeopleQueue(unsigned int size) : size(size) {}
		
bool ExtractedpeopleQueue::empty() const {
	return this->head == this->tail;
}

bool ExtractedpeopleQueue::full() const {
	return ((this->head + 1) % this->size) == this->tail;
}

void ExtractedpeopleQueue::push(boost::interprocess::offset_ptr<Person> item) {
	if (this->full()) {
		std::cerr << "todo assert" << std::endl;
	}
	std::cout << "push: " << this->head << std::endl;
	items[this->head] = item;
	this->head = (this->head + 1) % this->size;
}

boost::interprocess::offset_ptr<Person> ExtractedpeopleQueue::pop() {
	if (this->empty()) {
		std::cerr << "todo assert" << std::endl;
	}
	std::cout << "pop: " << this->tail << std::endl;
	boost::interprocess::offset_ptr<Person> item = items[this->tail];
	this->tail = (this->tail + 1) % this->size;
	return item;
}
