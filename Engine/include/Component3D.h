//
// Created by sloath on 10/26/26.
//

#ifndef COMPONENT3D_H
#define COMPONENT3D_H

#include "Component.h"
#include "Actor3D.h"

class Component3D : public Component
{
public:
    [[nodiscard]] Actor3D* GetOwner() const override { return mOwner; }
    void Update(float deltaTime) override;

    virtual void OnUpdateWorldTransform() const {}

protected:
    explicit Component3D(Actor3D* owner, int updateOrder = 100);
    Actor3D* mOwner;

};

#endif // COMPONENT3D_H
