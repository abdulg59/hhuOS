//
// Created by abdul on 16.07.23.
//

#include "ParticleSystem.h"
#include "lib/util/game/entity/Entity.h"


namespace Util::Game {
    /**
    * Default Constructor.
    */
    ParticleSystem::ParticleSystem() {}

    /**
    * Constructor creates pool for Particles and initializes the s
    */



    ParticleSystem::ParticleSystem(int emissionrate, int ttl, Util::Game::Sprite sprite){
        this->ttl = ttl;
        this->emissionRate = emissionrate;
        time= emissionrate;

        numberOfParticles = ttl/emissionrate;
        this->sprite = sprite;
        particles = new Particle[numberOfParticles];

        for (int i = 0; i < numberOfParticles - 1; i++) {
            freeParticles.add(&particles[i]);
        }


    }

    void ParticleSystem::updateParticle(double delta, Particle *particle) {
        particle->ttl = (particle->ttl) - 1;
        if (particle->ttl <= 0){
            particle->isActive = false;
            return;
        }

        Math::Vector2D currentVelocity = particle->velocity;
        Math::Vector2D currentAcceleration = particle->acceleration;
        Math::Vector2D currentPosition = particle->position;

        Math::Vector2D newVelocity = currentVelocity;
        particle->velocity = newVelocity;
        particle->position = currentPosition+newVelocity;
    }


    /**
    * initialize a Particle
    */
    void ParticleSystem::generateParticle(){
        Particle *part = freeParticles.get(0);
        initializeParticle(part, particlePosition, velocity, acceleration, ttl, alphaStart, startColor, startscale);
        freeParticles.removeIndex(0);
    }


    /**
    * Draw all active Particles in particles list
    */
    void ParticleSystem::drawParticles(Graphics2D &graphics) {
        for(int i = 0; i< numberOfParticles; i++){
            if(particles[i].isActive) {
                graphics.drawImageInColor(particles[i].position, sprite.getImage(), false, particles[i].color);
            }
        }
    }

    /**
    * Call Particle::update() on all active Particles and manage the free list
    */
    void ParticleSystem::update(double delta){
        updateParticleSystem(delta);
        time++;
        if(time>emissionRate) {
            if (!freeParticles.isEmpty()) {
                generateParticle();
                time = 0;
            }
        }

        for(int i = 0; i<numberOfParticles; i++){
            if(particles[i].isActive){
                updateParticle(delta, &particles[i]);
            }else{
                if(!freeParticles.contains(&particles[i])){
                    freeParticles.add(&particles[i]);
                }
            }
        }

    }

    void ParticleSystem::initializeParticle(Particle *particle,Math::Vector2D position, Math::Vector2D velocity, Math::Vector2D acceleration,
                                       int ttl, int alpha, Graphic::Color color, double scale) {
        particle->isActive = true;
        particle->position = position;
        particle->velocity = velocity;
        particle->acceleration = acceleration;
        particle->ttl = ttl;
        particle->alpha = alpha;
        particle->scale = scale;
        particle->color = color;
    }


}