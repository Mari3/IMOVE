//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_ACTION_H
#define IMOVE_ACTION_H

//Interface
class Action {
public:
    virtual bool isDone(Action*& followUp) = 0;
    virtual void execute(float dt) = 0;
    virtual ~Action(){}
};


#endif //IMOVE_ACTION_H
