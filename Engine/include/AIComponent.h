//
// Created by sloath on 19-Aug-26.
//

#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include <string>
#include <unordered_map>

#include "Component.h"

class AIComponent : public Component
{
public:
    explicit AIComponent(Actor* owner);

    void Update(float deltaTime) override;
    void ChangeState(const std::string& name);

    // add a new state to the map
    void RegisterState(class AIState* state);

private:
    std::unordered_map<std::string, AIState*> mStateMap;

    AIState* mCurrState;

};


#endif //AICOMPONENT_H
