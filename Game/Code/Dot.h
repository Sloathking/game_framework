//
// Created by sloath on 27-Aug-26.
//

#ifndef DOT_H
#define DOT_H

#include <Engine/include/Actor2D.h>

class Dot : public Actor2D
{
public:
    explicit Dot(class Game* game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const InputState& state) override;

private:

};


#endif //DOT_H
