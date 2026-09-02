//
// Created by sloath on 06-Aug-26.
//

#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    // constructor (the lower the update order, the earlier the component updates)
    explicit Component(class Actor* owner, int updateOrder = 100);

    // destructor
    virtual ~Component();

    // update this component by delta time
    virtual void Update(float deltaTime);

    virtual void ProcessInput(const struct InputState& state) {}

    [[nodiscard]] Actor* GetOwner() const { return mOwner; }

    [[nodiscard]] bool GetUpdateState() const { return mUpdate; }
    void SetUpdateState(const bool update) { mUpdate = update; }

    [[nodiscard]] int GetUpdateOrder() const { return mUpdateOrder; }

protected:
    // owning Actor
    Actor* mOwner;

    // update order of component
    int mUpdateOrder;

    // whether this component should Update
    bool mUpdate{true};
};

#endif //COMPONENT_H