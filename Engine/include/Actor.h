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
    void Update(float deltaTime);

    // updates all the components attached to the actor (not overridable)
    void UpdateComponents(float deltaTime) const;
    // Actors specific Update (overridable)
    virtual void UpdateActor(float deltaTime);

    // called from game, passes event to comps
    void ProcessInput(const struct InputState& state);

    // actor-specific handling
    virtual void ActorInput(const InputState& state);

    // add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(const Component* component);

    // getters/setters
    [[nodiscard]] State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }

    // Updates World Scale, Rotation, and Location
    void ComputeWorldTransform();
    [[nodiscard]] Matrix4 GetWorldTransform() const { return mWorldTransform; }

    [[nodiscard]] Quaternion GetRotation() const { return mRotation; }
    void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

    [[nodiscard]] const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

    [[nodiscard]] Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
    [[nodiscard]] float GetScale() const { return mScale; }
    void SetScale(const float scale) { mScale = scale; mRecomputeWorldTransform = true; }

    [[nodiscard]] Engine* GetGame() const { return mGame; }


private:
    // Actor's state
    State mState{EActive};

    // components held by actor
    std::vector<Component*> mComponents;
    Engine* mGame;

    Matrix4 mWorldTransform{Matrix4::Identity};
    bool mRecomputeWorldTransform{true};

    // transform properties
    Quaternion mRotation{Quaternion::Identity};
    Vector3 mPosition{Vector3::Zero};
    float mScale{1.0f};         		// uniforms scale of actor

};

#endif //ACTOR_H
