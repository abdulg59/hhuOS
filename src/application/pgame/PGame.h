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

#ifndef HHUOS_PGAME_H
#define HHUOS_PGAME_H

#include "lib/util/game/KeyListener.h"
#include "lib/util/collection/ArrayBlockingQueue.h"
#include "Ground.h"
#include "lib/util/math/Random.h"
#include "lib/util/collection/Array.h"
#include "lib/util/collection/ArrayList.h"
#include "lib/util/collection/Collection.h"
#include "lib/util/collection/Iterator.h"
#include "lib/util/game/Scene.h"
#include "Player.h"


namespace Util {
    namespace Game {
        class Graphics2D;
        class Text;
    }  // namespace Game

    namespace Io {
        class Key;
    }  // namespace Io
}  // namespace Util

class PGame : public Util::Game::Scene, public Util::Game::KeyListener {

public:
    /**
     * Default Constructor.
     */
    PGame();

    /**
     * Copy Constructor.
     */
    PGame(const PGame &other) = delete;

    /**
     * Assignment operator.
     */
    PGame &operator=(const PGame &other) = delete;

    /**
     * Destructor.
     */
    ~PGame() override = default;

    void update(double delta) override;

    void initializeBackground(Util::Game::Graphics2D &graphics) override;

    void keyPressed(Util::Io::Key key) override;

    void keyReleased(Util::Io::Key key) override;

private:

    Player *player;
    Util::Game::ParticleSystem* psystem;
    Util::Game::Text *pointText;

    Util::ArrayBlockingQueue<Ground*> ground;

    Util::Math::Random random;

    double currentVelocity = START_VELOCITY;

    bool moveLeft = false;
    bool moveRight = false;

    static const constexpr double START_VELOCITY = 0.25;
    static const constexpr double DASH_VELOCITY = 1;
    static const constexpr double MAX_VELOCITY = 1.5;
};

#endif