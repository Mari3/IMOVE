//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_LIGHTPERSONMAPREPOSITORY_H
#define IMOVE_LIGHTPERSONMAPREPOSITORY_H


#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include "../LightPerson.h"
#include "../../../util/Repository.h"

class LightPersonMapRepository : public Repository<LightPerson> {
private:
    std::map<int,std::shared_ptr<LightPerson>> map;
    vector<int> scheduledForRemoval;

public:
    LightPersonMapRepository(){
    }

    void add(const std::shared_ptr<LightPerson>& item) override {
        if(item)
            map[item->getId()] = item;
        else
            cout << "Warning: Tried to add null pointer to " << this << endl;
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

    std::vector<std::shared_ptr<LightPerson>>::iterator begin() override{
        std::vector<shared_ptr<LightPerson>> items;
        //items.reserve(map.size());
        for(auto &pair : map){
            items.push_back(pair.second);
        }
        return items.begin();
    }

    std::vector<std::shared_ptr<LightPerson>>::iterator end() override{
        std::vector<shared_ptr<LightPerson>> items;
        //items.reserve(map.size());
        for(auto &pair : map){
            items.push_back(pair.second);
        }
        return items.end();
    }

    virtual void for_each(const std::function<void(std::shared_ptr<LightPerson>)> &f) override {
        for(auto &pair : map){
            f(pair.second);
        }
    }


};


#endif //IMOVE_LIGHTPERSONMAPREPOSITORY_H
