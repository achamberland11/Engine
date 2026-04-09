#pragma once

#include "../../Component.h"


class GColliderComponent2D : public GComponent
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(true, true, true, true)
    
    GColliderComponent2D()
    {
        Name = "Collider2D";
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
   
    EColliderType2D ColliderType2D = EColliderType2D::Rectangle;
};
