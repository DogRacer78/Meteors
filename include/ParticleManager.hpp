#pragma once

#include <raylib.h>
#include <vector>

#include "Particle.hpp"

class ParticleManager{
public:
    void AddParticles(const Particle& p);
    void RemoveParticle();
    void Draw();
    void Update(float& dt);
private:
    std::vector<Particle> particles;
};