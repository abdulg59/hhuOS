//
// Created by abdul on 16.07.23.
//

#include "lib/util/game/Drawable.h"
#include "lib/util/game/Sprite.h"


#ifndef HHUOS_PARTICLE_H
#define HHUOS_PARTICLE_H

namespace Util::Game {
    class Particle : public Drawable {

    public:
        Particle(const Math::Vector2D &position, Math::Vector2D velocity, const int totalTTL, const Sprite sprite);

        Particle();


        ~Particle() override = default;

        void initializeParticle(const Math::Vector2D &position, const Math::Vector2D velocity, const Math::Vector2D acceleration, int totalTTL,  const Sprite sprite);


        void draw(Util::Game::Graphics2D &graphics) override;

        bool isActive();

        int getTTL();

        void setTTL(int newTTL);

        Math::Vector2D getAcceleration();
        Math::Vector2D getVelocity();

        Math::Vector2D getPosition();
        void setPosition(Math::Vector2D newPos);

        void setVelocity(Math::Vector2D newVelocity);

    private:
        double scale = 1;
        Util::Game::Sprite sprite;
        int TTL;

        int currentAlpha;
        int startAlpha;
        int endAlpha;

        Graphic::Color currentColor;
        Graphic::Color startColor;
        Graphic::Color endColor;

        Math::Vector2D position{};
        Math::Vector2D velocity{};
        Math::Vector2D acceleration{};

        void initializeParticle(const Math::Vector2D &position, const Math::Vector2D velocity,
                           const Math::Vector2D acceleration,
                           int totalTTL, int alpha, const Sprite sprite);
    };
}

#endif //HHUOS_PARTICLE_H