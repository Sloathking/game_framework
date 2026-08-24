//
// Created by sloath on 06-Aug-26.
//

#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "Math.h"
#include <SDL3/SDL_events.h>

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
    explicit Actor(class Game* game);
    virtual ~Actor();

    // update function called from Game (not overridable)
    void Update(float deltaTime);

    // updates all the components attached to the actor (not overridable)
    void UpdateComponents(float deltaTime) const;

    // any Actor-specific update code (overridable)
    virtual void UpdateActor(float deltaTime);

    // called from game, passes event to comps
    void ProcessInput(const struct InputState& state);

    // actor-specific handling
    virtual void ActorInput(const InputState& state);

    // getters/setters
    [[nodiscard]] const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }

    [[nodiscard]] float GetScale() const { return mScale; }
    void SetScale(const float scale) { mScale = scale; }

    [[nodiscard]] float GetRotation() const { return mRotation; }
    void SetRotation(const float rotation) { mRotation = rotation; }

    [[nodiscard]] Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

    [[nodiscard]] State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }

    [[nodiscard]] class Game* GetGame() const { return mGame; }

    // add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(Component* component);

private:
    // Actor's state
    State mState;

    // Transform
    Vector2 mPosition;	// center position of Actor
    float mScale;		// uniforms scale of actor
    float mRotation;	// rotation angle (in radians)

    // components held by actor
    std::vector<Component*> mComponents;
    Game* mGame;

    // forward vector
    Vector2 mForward{Vector2(0,0)};
};
#endif //ACTOR_H
