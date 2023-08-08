//
// Created by abdul on 16.07.23.
//

#ifndef HHUOS_PARTICLESYSTEM_H
#define HHUOS_PARTICLESYSTEM_H

#include "lib/util/collection/ArrayList.h"
#include "lib/util/game/SpriteAnimation.h"
#include "lib/util/game/Graphics2D.h"


struct Particle
{
    int ttl;
    bool isActive;
    Util::Math::Vector2D position;
    Util::Math::Vector2D velocity;
    Util::Math::Vector2D acceleration;
    Util::Graphic::Color color;
    int alpha;
    double scale;
};


namespace Util::Game {
    class ParticleSystem {

    public:
        /*   ParticleSystem(const Math::Vector2D &position, const Math::Vector2D &velocity, int numberOfParticles);*/
        virtual ~ParticleSystem() = default;

        ParticleSystem();

        ParticleSystem(int emissionRate, int ttl, Util::Game::Sprite sprite);

        void update(double delta);

        void drawParticles(Graphics2D &graphics);

        virtual void updateParticleSystem(double delta) = 0;

        virtual void updateParticle(double delta, Particle *particle);

/*
        void updateSystem(Math::Vector2D pos, Math::Vector2D velo, Math::Vector2D ace);
*/

    private:
        void generateParticle();

        /**
         * Attributes of the particle system
         */
        // interval, in which particles should be created
        int emissionRate;
        // first element of the free list
        ArrayList<Particle*> freeParticles;
        // Particle pool
        Particle *particles;
        // variable to track time since last particle creation
        int time;

    protected:
        void initializeParticle(Particle *particle, Math::Vector2D position, Math::Vector2D velocity, Math::Vector2D acceleration, int ttl, int alpha, Graphic::Color color, double scale);

        Util::Game::Sprite sprite{};
        /**
  * Attributes of individual particles
  */
        Math::Vector2D velocity{};
        Math::Vector2D particlePosition{};
        Math::Vector2D acceleration{};
        int ttl;
        // start end end color for color interpolation
        Graphic::Color startColor;
        Graphic::Color endColor;
        // start and end color for size interpolation
        double startSize;
        double endSize;
        //start and end alpha-value for transperency interpolation
        int alphaStart;
        int alphaEnd;
        int numberOfParticles;
        // current position of the particle system
        Math::Vector2D systemPosition{};
        double startscale;
    };
}
#endif //HHUOS_PARTICLESYSTEM_H