//
// Created by root on 07.08.23.
//

#include "RectangleParticleSystem.h"

RectangleParticleSystem::RectangleParticleSystem() : ParticleSystem(30,1000,Util::Game::Sprite("/initrd/dino/ground.bmp", 0.1, 0.1)){
    rectangleHeight =1;
    rectangleWidth = 1;
    particlePosition = Util::Math::Vector2D(0.3,0.3);
    velocity = Util::Math::Vector2D(0.005, 0.005);
    acceleration = Util::Math::Vector2D(0.001, 0.001);
    ttl = 300;
    alphaStart = 255;
    startscale = 1;
    startColor = Util::Graphic::Colors::BLACK;
};

void RectangleParticleSystem::updateParticleSystem(double delta) {
    time++;
}

void RectangleParticleSystem::updateParticle(double delta,Particle *particle) {
    if(time == 300) {
        particle->color = Util::Graphic::Colors::BLUE;
        particle->velocity = Util::Math::Vector2D(-0,-0.1);
    }
    ParticleSystem::updateParticle(delta, particle);

}
