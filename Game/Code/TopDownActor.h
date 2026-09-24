//
// Created by sloath on 24-Sep-26.
//

#ifndef TOPDOWNACTOR_H
#define TOPDOWNACTOR_H

#include <Engine/include/Actor.h>


class TopDownActor : public Actor
{
public:
    explicit TopDownActor(class Game* game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const InputState& state) override;

    void SetVisible(bool visible) const;

private:
    class Camera2D* mCam{};
    class MoveComponent* mMoveComp;
    Vector3 mCamOffset{Vector3(0.0f, 0.0f, 100.0f)};
    float mZoomScale{50.0f};

};

#endif //TOPDOWNACTOR_H
