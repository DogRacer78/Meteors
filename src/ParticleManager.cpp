#include <raylib.h>

#include "ParticleManager.hpp"
#include "Particle.hpp"
#include "SinParticle.hpp"

void ParticleManager::AddParticles(Particle* p){
    particles.push_back(p);
}

void ParticleManager::Draw(){
    for (Particle* p : particles){
        p->Draw();
    }
}

void ParticleManager::Update(float& dt){
    for (int i = 0; i < particles.size(); i++){
        if (!particles[i]->GetDead())
            particles[i]->Update(dt);
        else{
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void ParticleManager::Reset(){
    for (int i = 0; i < particles.size(); i++){
        delete particles[i];
    }
    particles.clear();
}