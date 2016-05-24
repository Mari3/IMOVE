//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_LIGHTPERSONMAPREPOSITORY_H
#define IMOVE_LIGHTPERSONMAPREPOSITORY_H


#include <map>
#include <vector>
#include "../LightPerson.h"
#include "../../../util/Repository.h"

class LightPersonMapRepository : public Repository<LightPerson> {
private:
    std::map<int,LightPerson> map;
    vector<int> scheduledForRemoval;

    static LightPersonMapRepository *_instance;
    LightPersonMapRepository(){}

public:
    static LightPersonMapRepository * getInstance();

    void add(LightPerson *item) override {
        map[item->getId()] = item;
    }

    void add(LightPerson *item, unsigned long id) override {
        add(item);
    }

    void scheduleForRemoval(LightPerson *item) override {
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

    LightPerson *get(unsigned long id) override {
        return map[id];
    }

    std::vector<LightPerson*>::iterator begin() override{
        std::vector<LightPerson*> items;
        //items.reserve(map.size());
        for(auto pair : map){
            items.push_back(pair.second);
        }
        return items.begin();
    }

    std::vector<LightPerson*>::iterator end() override{
        std::vector<LightPerson*> items;
        //items.reserve(map.size());
        for(auto &pair : map){
            items.push_back(pair.second);
        }
        return items.end();
    }
};


#endif //IMOVE_LIGHTPERSONMAPREPOSITORY_H
