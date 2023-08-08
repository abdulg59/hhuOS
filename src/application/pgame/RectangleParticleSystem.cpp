//
// Created by root on 07.08.23.
//

#include "RectangleParticleSystem.h"

RectangleParticleSystem::RectangleParticleSystem() : ParticleSystem(30,1000,Util::Game::Sprite("/initrd/dino/ground.bmp", 0.1, 0.1)){
    rectangleHeight =1;
    rectangleWidth = 1;
    this->particlePosition = Util::Math::Vector2D(0.3,0.3);
    this->position = Util::Math::Vector2D(0.3, 0.3);
};

void RectangleParticleSystem::updateParticleSystem(double delta) {
}
