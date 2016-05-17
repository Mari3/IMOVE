//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_REPOSITORY_H
#define IMOVE_REPOSITORY_H


template<class T>
class Repository {
public:
    virtual void add(const T& item) = 0;
    virtual void remove(const T& item) = 0;
    virtual void update(const T& item) = 0;
    virtual const T get(int id) = 0;
    const T operator[](int id) {
            return get(id);
    }

    //For iteration, TODO replace with safer system later
    virtual T* begin() = 0;
    virtual T* end() = 0;
};


#endif //IMOVE_REPOSITORY_H
