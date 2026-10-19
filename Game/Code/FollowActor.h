//
// Created by sloath on 18-Sep-26.
//

#ifndef FOLLOWACTOR_H
#define FOLLOWACTOR_H

#include <Engine/include/Actor3D.h>

class FollowActor : public Actor3D
{
public:
    explicit FollowActor(class Game* game);

    void ActorInput(const InputState& state) override;

    void SetVisible(bool visible) const;

private:
    class MoveComponent3D* mMoveComp{};
    class FollowCamera* mCam{};
    class MeshComponent* mMesh{};

};


#endif //FOLLOWACTOR_H
