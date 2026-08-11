//
// Created by sloath on 06-Aug-26.
//

#ifndef CLION_GAME_PROGRAMMING_ACTOR_H
#define CLION_GAME_PROGRAMMING_ACTOR_H
#include <vector>
#include "Math.h"

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

    // getters/setters
    [[nodiscard]] const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }

    [[nodiscard]] float GetScale() const { return mScale; }
    void SetScale(const float scale) { mScale = scale; }

    [[nodiscard]] float GetRotation() const { return mRotation; }
    void SetRotation(const float rotation) { mRotation = rotation; }

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
    std::vector<class Component*> mComponents;
    class Game* mGame;
};
#endif //CLION_GAME_PROGRAMMING_ACTOR_H
