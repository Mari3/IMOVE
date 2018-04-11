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
    std::map<int,std::shared_ptr<Circle>> map;
    std::vector<int> scheduledForRemoval;

public:
    CircleRepository(){
    }

    void add(const std::shared_ptr<Circle>& item) override {
        assert(item);
        map[item->id] = item;
    }

    void scheduleForRemoval(const std::shared_ptr<Circle>& item) override {
        scheduledForRemoval.push_back(item->id);
    }

    void removeAll() override {
        for(auto &i : scheduledForRemoval){
            if(map.count(i) > 0){
                map.erase(i);
            }
        }
    }

    unsigned long size() override {
        return map.size();
    }

    bool has(unsigned long id) override {
        return map.count(id) > 0;
    }

    std::shared_ptr<Circle> &get(unsigned long id) override {
        return map[id];
    }

    virtual void for_each(const std::function<void(std::shared_ptr<Circle>)> &f) override {
        for(auto &pair : map){
            f(pair.second);
        }
    }
};

#endif //IMOVE_CIRCLEREPOSITORY_H
