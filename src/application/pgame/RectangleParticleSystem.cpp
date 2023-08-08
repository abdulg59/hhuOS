//
// Created by root on 07.08.23.
//

#include "RectangleParticleSystem.h"

RectangleParticleSystem::RectangleParticleSystem() : ParticleSystem(30,1000,Util::Game::Sprite("/initrd/dino/ground.bmp", 0.1, 0.1)){
    rectangleHeight =1;
    rectangleWidth = 1;
    this->particlePosition = Util::Math::Vector2D(0.5,0.5);
    this->position = Util::Math::Vector2D(0.5, 0.5);
};

void RectangleParticleSystem::updateParticleSystem(double delta) {
    double newPosX = dmod(random.nextRandomNumber(), rectangleWidth);
    double newPosY = dmod(random.nextRandomNumber(), rectangleHeight);
}

double RectangleParticleSystem::dmod(double x, double y) {
    return x - (int)(x/y) * y;
}
