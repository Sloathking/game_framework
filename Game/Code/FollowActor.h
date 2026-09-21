//
// Created by sloath on 18-Sep-26.
//

#ifndef FOLLOWACTOR_H
#define FOLLOWACTOR_H

#include <Engine/include/Actor.h>

class FollowActor : public Actor
{
public:
    explicit FollowActor(class Game* game);

    void ActorInput(const InputState& state) override;

    void SetVisible(bool visible) const;

private:
    class MoveComponent* mMoveComp{};
    class FollowCamera* mCam{};
    class MeshComponent* mMesh{};

};


#endif //FOLLOWACTOR_H
