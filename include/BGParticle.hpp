#pragma once

#include <raylib.h>

#include "Particle.hpp"

class BGParticle : public Particle{
public:
    BGParticle(float x, float y, float w, float h, Texture2D* tex, float _lifetime);
    void Update(float& dt);
private:
};