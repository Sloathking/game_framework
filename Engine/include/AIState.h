//
// Created by sloath on 19-Aug-26.
//

#ifndef AISTATE_H
#define AISTATE_H


class AIState
{
public:
    explicit AIState(class AIComponent* owner) : mOwner{owner} {}
    virtual ~AIState() = default;

    // state specific behavior
    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;

    // getter for string name of state
    [[nodiscard]] virtual const char* GetName() const;

protected:
    AIComponent* mOwner;

};

class AIPatrol : public AIState
{
public:
    explicit AIPatrol(AIComponent* owner);

    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    [[nodiscard]] const char* GetName() const override { return "Patrol"; }
};

#endif //AISTATE_H
