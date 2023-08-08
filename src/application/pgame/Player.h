/*
 * Copyright (C) 2018-2023 Heinrich-Heine-Universitaet Duesseldorf,
 * Institute of Computer Science, Department Operating Systems
 * Burak Akguel, Christian Gesse, Fabian Ruhland, Filip Krakowski, Michael Schoettner
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef HHUOS_PLAYER_H
#define HHUOS_PLAYER_H

#include <cstdint>

#include "lib/util/game/SpriteAnimation.h"
#include "lib/util/game/entity/Entity.h"
#include "lib/util/game/particleSystem/ParticleSystem.h"


namespace Util {
    namespace Math {
        class Vector2D;
    }  // namespace Math

    namespace Game {
        class Graphics2D;
        class CollisionEvent;
        class TranslationEvent;
    }  // namespace Game
}  // namespace Util

class Player : public Util::Game::Entity {

public:
    /**
     * Default Constructor.
     */
    Player(const Util::Math::Vector2D &position);

    /**
     * Copy Constructor.
     */
    Player(const Player &other) = delete;

    /**
     * Assignment operator.
     */
    Player &operator=(const Player &other) = delete;

    /**
     * Destructor.
     */
    ~Player() override = default;

    void initialize() override;

    void onUpdate(double delta) override;


    void reset();

    void moveRight();

    void moveLeft();

    void onTranslationEvent(Util::Game::TranslationEvent &event) override;

    void onCollisionEvent(Util::Game::CollisionEvent &event) override;

    void draw(Util::Game::Graphics2D &graphics) override;

    static const constexpr uint32_t TAG = 0;

private:
    bool hatching = false;
    bool dying = false;
    bool hatched = false;
    bool dead = false;
    bool onGround = false;
    bool directionLeft = false;

    const double speed = 0.1;
    double time = 0;
    Util::Game::Sprite sprite;
    Util::Game::ParticleSystem* psystem;

    static const constexpr double JUMP_VELOCITY = 0.75;
};

#endif