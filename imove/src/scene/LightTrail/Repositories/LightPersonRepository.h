//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_LIGHTPERSONREPOSITORY_H
#define IMOVE_LIGHTPERSONREPOSITORY_H


#include <map>
#include <vector>
#include "../LightPerson.h"
#include "../../../util/Repository.h"

class LightPersonRepository : Repository<LightPerson> {
private:
    std::map<int,LightPerson*> map;
    vector<int> scheduledForRemoval;

    static LightPersonRepository *_instance;
    LightPersonRepository(){}

public:
    static LightPersonRepository * getInstance();

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

    std::map<int,LightPerson*>::iterator begin(){
        return map.begin();
    }

    std::map<int,LightPerson*>::iterator end(){
        return map.end();
    }
};


#endif //IMOVE_LIGHTPERSONREPOSITORY_H
