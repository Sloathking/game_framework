//
// Created by sloath on 27-Aug-26.
//

#ifndef DOT_H
#define DOT_H

#include "../Engine/include/Actor.h"

class Dot : public Actor
{
public:
    explicit Dot(Game* game);

    void ActorInput(const InputState& state) override;

private:

};


#endif //DOT_H
