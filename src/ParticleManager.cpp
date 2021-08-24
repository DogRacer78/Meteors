#include <raylib.h>

#include "ParticleManager.hpp"
#include "Particle.hpp"

void ParticleManager::AddParticles(const Particle& p){
    particles.push_back(p);
}

void ParticleManager::Draw(){
    for (Particle& p : particles){
        p.Draw();
    }
}

void ParticleManager::Update(float& dt){
    for (int i = 0; i < particles.size(); i++){
        if (!particles[i].GetDead())
            particles[i].Update(dt);
        else{
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}