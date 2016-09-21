#ifndef IMOVE_PONGPERSON_H
#define IMOVE_PONGPERSON_H

#include "../../../../scene_interface/src/Person.h"
#include "../../../../util/src/Vector2.h"
#include <map>
#include <vector>
#include <memory>
#include <assert.h>
#include "../Util/Repository.h"

struct PongPerson {
	Vector2 location;
	scene_interface::Person::PersonType person_type;
	unsigned int id;
	PongPerson(unsigned int id, Vector2 location, scene_interface::Person::PersonType person_type){
		this->location = location;
		this->id = id;
		this->person_type = person_type;
	}
};

class PongPersonMapRepository : public Repository<PongPerson> {
private:
    std::map<int,std::shared_ptr<PongPerson>> map;
    std::vector<int> scheduledForRemoval;

public:
    PongPersonMapRepository(){
    }

    void add(const std::shared_ptr<PongPerson>& item) override {
        assert(item);
        map[item->id] = item;
    }

    void scheduleForRemoval(const std::shared_ptr<PongPerson>& item) override {
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

    std::shared_ptr<PongPerson> &get(unsigned long id) override {
        return map[id];
    }

    virtual void for_each(const std::function<void(std::shared_ptr<PongPerson>)> &f) override {
        for(auto &pair : map){
            f(pair.second);
        }
    }


};


#endif //IMOVE_PONGPERSON_H