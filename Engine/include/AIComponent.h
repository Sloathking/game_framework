//
// Created by sloath on 19-Aug-26.
//

#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include <string>
#include <unordered_map>

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

    AIState* mCurrState{nullptr};

};


#endif //AICOMPONENT_H
