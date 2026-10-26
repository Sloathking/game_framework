//
// Created by sloath on 10/26/26.
//

#ifndef COMPONENT2D_H
#define COMPONENT2D_H

#include "Component.h"
#include "Actor2D.h"

class Component2D : public Component
{
public:
    [[nodiscard]] Actor2D* GetOwner() const override { return mOwner; }
    void Update(float deltaTime) override;

protected:
    explicit Component2D(Actor2D* owner, int updateOrder = 100);
    Actor2D* mOwner;

};

#endif // COMPONENT2D_H
