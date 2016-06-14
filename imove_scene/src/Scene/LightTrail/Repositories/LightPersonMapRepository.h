//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_LIGHTPERSONMAPREPOSITORY_H
#define IMOVE_LIGHTPERSONMAPREPOSITORY_H


#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <assert.h>
#include "../LightPerson.h"
#include "../../Util/Repository.h"

class LightPersonMapRepository : public Repository<LightPerson> {
private:
    std::map<int,std::shared_ptr<LightPerson>> map;
    std::vector<int> scheduledForRemoval;

public:
    LightPersonMapRepository(){
    }

    void add(const std::shared_ptr<LightPerson>& item) override {
        assert(item);
        map[item->getId()] = item;
    }

    void scheduleForRemoval(const std::shared_ptr<LightPerson>& item) override {
        scheduledForRemoval.push_back(item->getId());
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

    std::shared_ptr<LightPerson> &get(unsigned long id) override {
        return map[id];
    }

    virtual void for_each(const std::function<void(std::shared_ptr<LightPerson>)> &f) override {
        for(auto &pair : map){
            f(pair.second);
        }
    }


};


#endif //IMOVE_LIGHTPERSONMAPREPOSITORY_H
