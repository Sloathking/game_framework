//
// Created by sloath on 06-Aug-26.
//

#ifndef ACTOR_H
#define ACTOR_H

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

    // // Updates World Scale, Rotation, and Location
    virtual void ComputeWorldTransform() = 0;

    // updates all the components attached to the actor (not overridable)
    void UpdateComponents(float deltaTime) const;

    // called from game, passes event to comps
    void ProcessInput(const struct InputState& state);

    // actor-specific handling
    virtual void ActorInput(const InputState& state);

    // getters/setters
    [[nodiscard]] float GetScale() const { return mScale; }
    virtual void SetScale(const float scale) { mScale = scale; }

    [[nodiscard]] State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }

    [[nodiscard]] Engine* GetGame() const { return mGame; }

    // add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(const Component* component);

protected:
    // Actor's state
    State mState{EActive};

    // components held by actor
    std::vector<Component*> mComponents;
    Engine* mGame;

    // Transform
    float mScale{1.0f};         		// uniforms scale of actor

private:

};
#endif //ACTOR_H
