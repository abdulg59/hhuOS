//
// Created by abdul on 16.07.23.
//

#include "Particle.h"
#include "lib/util/graphic/Image.h"

namespace Util::Game {
    Particle::Particle(const Math::Vector2D &position, Math::Vector2D velocity, const int TTL, const Sprite sprite) : sprite(sprite),  TTL(TTL), position(position), velocity(velocity){}

    Particle::Particle(){};


    void Particle::update(double delta) {
        scale -= 0.005;
/*
        startAlpha -= 1;
*/
        TTL -= 1;

        if(TTL <= 0 || startAlpha<=0){
            return;
        }else{
            velocity = velocity+acceleration*delta;
            position = position + velocity;
        }
    }

    void Particle::draw(Util::Game::Graphics2D &graphics) {
        if(scale != 1) {
            graphics.drawImageScaled(position, sprite.getImage(), false, currentColor,
                                     sprite.getWidth() * scale, sprite.getHeight() * scale);
        }else{
            graphics.drawImageInColor(position, sprite.getImage(), false, currentColor);
        }
/*
        graphics.drawImageInColor(position,sprite.getImage(), false, Graphic::Color(0,0,0, startAlpha));
*/
    }

    bool Particle::isActive(){
        return (TTL>0 && startAlpha>0 && scale>0);
    }


    void Particle::initializeParticle(const Math::Vector2D &position, const Math::Vector2D velocity, const Math::Vector2D acceleration, int totalTTL,
                                       const Sprite sprite) {
        startAlpha = 255;
        this->position = position;
        this->acceleration = acceleration;
        this->velocity = velocity;
        TTL = totalTTL;
        this->sprite = sprite;
        scale = 1.0;
    }

    void Particle::initializeParticle(const Math::Vector2D &position, const Math::Vector2D velocity, const Math::Vector2D acceleration, int totalTTL,
                                      int alpha, const Sprite sprite) {
        this->startAlpha = alpha;
        this->position = position;
        this->acceleration = acceleration;
        this->velocity = velocity;
        TTL = totalTTL;
        this->sprite = sprite;
    }


}