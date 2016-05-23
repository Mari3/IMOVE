//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_VECTORREPOSITORY_H
#define IMOVE_VECTORREPOSITORY_H

#include <vector>
#include "Repository.h"
#include <algorithm>

template<typename T>
class VectorRepository : Repository<T>
{
private:
    typename std::vector<T*> items;
    std::vector<long> scheduledForRemoval;

public:
    void add(T* item) override
    {
        items.push_back(item);
    }

    void add(T* item, unsigned long id) override
    {
        //TODO give warning that id is being ignored
        add(item);
    }

    void scheduleForRemoval(T* item) override
    {
        typename std::vector<T*>::iterator pos = std::find(items.begin(),items.end(),item);
        if(pos > items.end())
        {
            //TODO throw error
            return;
        }
        scheduledForRemoval.push_back(pos - items.begin());
    }

    void removeAll() override
    {
        int modifier = 0;
        for(auto &index : scheduledForRemoval)
        {
            items.erase(items.cbegin()+index+modifier);
            modifier--;
        }
        scheduledForRemoval.clear();
    }

    unsigned long size() override
    {
        return items.size();
    }

    bool has(unsigned long id) override
    {
        return id > 0 && id <= items.size();
    }

    T* get(unsigned long id) override
    {
        return items[id];
    }

    typename std::vector<T*>::iterator begin()
    {
        return items.begin();
    }

    typename std::vector<T*>::iterator end()
    {
        return items.end();
    }
};


#endif //IMOVE_VECTORREPOSITORY_H
