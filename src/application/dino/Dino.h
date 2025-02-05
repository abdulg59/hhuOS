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

#ifndef HHUOS_DINO_H
#define HHUOS_DINO_H

#include <cstdint>

#include "lib/util/game/SpriteAnimation.h"
#include "lib/util/game/entity/Entity.h"

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

class Dino : public Util::Game::Entity {

public:
    /**
     * Default Constructor.
     */
    Dino(const Util::Math::Vector2D &position);

    /**
     * Copy Constructor.
     */
    Dino(const Dino &other) = delete;

    /**
     * Assignment operator.
     */
    Dino &operator=(const Dino &other) = delete;

    /**
     * Destructor.
     */
    ~Dino() override = default;

    void initialize() override;

    void onUpdate(double delta) override;

    void dash();

    void jump();

    void hatch();

    void die();

    void reset();

    [[nodiscard]] bool hasHatched() const;

    [[nodiscard]] bool isDying() const;

    [[nodiscard]] bool isDead() const;

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

    double time = 0;
    Util::Game::SpriteAnimation *currentAnimation = &eggAnimation;
    Util::Game::SpriteAnimation runAnimation;
    Util::Game::SpriteAnimation dashAnimation;
    Util::Game::SpriteAnimation eggAnimation;
    Util::Game::SpriteAnimation crackAnimation;
    Util::Game::SpriteAnimation hatchAnimation;
    Util::Game::SpriteAnimation deathAnimation;

    static const constexpr double JUMP_VELOCITY = 0.75;
};

#endif
