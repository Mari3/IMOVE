#ifndef IMOVE_CIRCLEREPOSITORY_H
#define IMOVE_CIRCLEREPOSITORY_H

#include <map>
#include <vector>
#include <memory>
#include <assert.h>
//#include <Color.hpp>
#include "../Util/Repository.h"
#include "../../../../util/src/Vector2.h"


struct Circle {
	Vector2 location;
	sf::Color color;
	unsigned int id;
	Circle(unsigned int id, Vector2 location, sf::Color color){
		this->location = location;
		this->id = id;
		this->color = color;
	}
};

class CircleRepository : public Repository<Circle> {
private:
    // Map to store circles based on id's of the corresponding person
    std::map<int,std::shared_ptr<Circle>> map;
    // Vector containing id's of circles that need to be removed
    std::vector<int> scheduledForRemoval;

public:
    CircleRepository(){}

    // Add new circle to repository
    void add(const std::shared_ptr<Circle>& item) override {
        assert(item);
        map[item->id] = item;
    }

    // Add circle that needs to be deleted to the scheduledForRemoval vector
    void scheduleForRemoval(const std::shared_ptr<Circle>& item) override {
        scheduledForRemoval.push_back(item->id);
    }

    // Remove circles that were scheduled for removal
    void removeAll() override {
        for(auto &i : scheduledForRemoval){
            if(map.count(i) > 0){
                map.erase(i);
            }
        }
    }

    // Get size of map
    unsigned long size() override {
        return map.size();
    }

    // Check if map contains a circle with a given id
    bool has(unsigned long id) override {
        return map.count(id) > 0;
    }

    // Get the (pointer to the) circle with the id provided
    std::shared_ptr<Circle> &get(unsigned long id) override {
        return map[id];
    }

    // Apply a function to each of the circles in the map
    virtual void for_each(const std::function<void(std::shared_ptr<Circle>)> &f) override {
        for(auto &pair : map){
            f(pair.second);
        }
    }
};

#endif //IMOVE_CIRCLEREPOSITORY_H
