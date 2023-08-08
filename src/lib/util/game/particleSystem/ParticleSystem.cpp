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
        velocity = Math::Vector2D(0.001,0.001);
        acceleration = Math::Vector2D(0.001,0.001);

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
        int curentTTL = particle->getTTL();
        particle->setTTL(curentTTL-1);

        Math::Vector2D currentVelocity = particle->getVelocity();
        Math::Vector2D currentAcceleration = particle->getAcceleration();
        Math::Vector2D currentPosition = particle->getPosition();

        Math::Vector2D newVelocity = velocity+ (currentAcceleration*delta);
        particle->setVelocity(newVelocity);
        particle->setPosition(currentPosition+velocity);
    }


    /**
    * initialize a Particle
    */
    void ParticleSystem::generateParticle(){
        Particle *part = freeParticles.get(0);
        part->initializeParticle(particlePosition, velocity, acceleration, ttl, sprite);
        freeParticles.removeIndex(0);

    }


    /**
    * Draw all active Particles in particles list
    */
    void ParticleSystem::drawParticles(Graphics2D &graphics) {
        for(int i = 0; i< numberOfParticles; i++){
            if(particles[i].isActive()) {
                particles[i].draw(graphics);
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
            if(particles[i].isActive()){
                updateParticle(delta, &particles[i]);
            }else{
                if(!freeParticles.contains(&particles[i])){
                    freeParticles.add(&particles[i]);
                }
            }
        }

    }


    /*   void ParticleSystem::updateSystem(Math::Vector2D pos, Math::Vector2D velo, Math::Vector2D ace) {
           position = pos;
           velocity = velo;
           acceleration = ace;
       }*/


}