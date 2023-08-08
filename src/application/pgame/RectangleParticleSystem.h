//
// Created by root on 07.08.23.
//

#ifndef HHUOS_RECTANGLEPARTICLESYSTEM_H
#define HHUOS_RECTANGLEPARTICLESYSTEM_H

#include "lib/util/game/particleSystem/ParticleSystem.h"
#include "lib/util/math/Random.h"


class RectangleParticleSystem : public Util::Game::ParticleSystem{
public:
    RectangleParticleSystem();
    void updateParticleSystem(double delta) override;

private:
    Util::Math::Random random;
    double rectangleWidth;
    double rectangleHeight;
};


#endif //HHUOS_RECTANGLEPARTICLESYSTEM_H
