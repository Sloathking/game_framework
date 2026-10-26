//
// Created by sloath on 06-Aug-26.
//

#ifndef ACTOR_H
#define ACTOR_H

#include "Math.h"
#include <vector>

class Actor
{
public:
    // used to track state of Actor
    enum State
    {
        EActive,
        EPaused,
        EDead
    };

    // constructor/destructor
    explicit Actor(class Engine* game);
    virtual ~Actor();

    // update function called from Game (not overridable)
    virtual void Update(float deltaTime) = 0;

    // updates all the components attached to the actor (not overridable)
    void UpdateComponents(float deltaTime) const;

    // Actors specific Update (overridable)
    virtual void UpdateActor(float deltaTime);

    // called from game, passes event to comps
    void ProcessInput(const struct InputState& state);

    // actor-specific handling
    virtual void ActorInput(const InputState& state);

    // add/remove components
    virtual void AddComponent(class Component* component);
    virtual void RemoveComponent(const Component* component);

    // getters/setters
    [[nodiscard]] State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }

    [[nodiscard]] float GetScale() const { return mScale; }
    virtual void SetScale(float scale) = 0;

    [[nodiscard]] Engine* GetGame() const { return mGame; }

protected:
    // Actor's state
    State mState{EActive};

    // components held by actor
    std::vector<Component*> mComponents;
    Engine* mGame;

    float mScale{1.0f};

private:

};

#endif //ACTOR_H
