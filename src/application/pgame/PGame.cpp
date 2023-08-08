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

#include "PGame.h"

#include <cstdint>

#include "application/pgame/Player.h"
#include "lib/util/io/key/Key.h"
#include "lib/util/game/Camera.h"
#include "lib/util/game/entity/component/LinearMovementComponent.h"
#include "lib/util/game/entity/component/GravityComponent.h"
#include "lib/util/game/GameManager.h"
#include "application/pgame/Ground.h"
#include "lib/util/base/String.h"
#include "lib/util/game/Game.h"
#include "lib/util/game/Graphics2D.h"
#include "lib/util/game/Sprite.h"
#include "lib/util/game/Text.h"
#include "lib/util/graphic/Color.h"
#include "lib/util/math/Vector2D.h"
#include "application/pgame/RectangleParticleSystem.h"

PGame::PGame() : player(new Player(Util::Math::Vector2D(-0.8, 0))), pointText(new Util::Game::Text(Util::Math::Vector2D(-1, 0.9), "Points: 0")), ground(4) {
    player->addComponent(new Util::Game::LinearMovementComponent(*player));

    addObject(player);
    addObject(pointText);

    for (uint32_t i = 0; i < 4; i++) {
        auto *newGround = new Ground(Util::Math::Vector2D(getCamera().getPosition().getX() - 1.5 + i, -0.8));
        ground.offer(newGround);
        addObject(newGround);
    }
    RectangleParticleSystem *psystem = new RectangleParticleSystem();
    addParticleSystem(psystem);
/*    psystem = new Util::Game::ParticleSystem(5,Util::Game::Sprite("/initrd/dino/ground.bmp",0.1,0.1));
    emitter = new Util::Game::BoxEmitter();
    addParticleSystem(psystem);*/

    setKeyListener(*this);
}

void PGame::initializeBackground(Util::Game::Graphics2D &graphics) {
    graphics.clear(Util::Graphic::Color(57, 97, 255));

}

void PGame::update(double delta) {
        if (moveLeft) {
            player->moveLeft();
        }
        if (moveRight) {
            player->moveRight();
        }

        if (ground.peek()->getPosition().getX() < getCamera().getPosition().getX() - 2.5) {
            auto positionX = (static_cast<uint32_t>((getCamera().getPosition().getX() + 1.5) * 10) / 5) * 5 / 10.0 ;
            auto *newGround = new Ground(Util::Math::Vector2D(positionX, -0.8));
            removeObject(ground.poll());
            ground.offer(newGround);
            addObject(newGround);
        }



        getCamera().setPosition(Util::Math::Vector2D(player->getPosition().getX() + 0.8, 0));
        pointText->setPositionX(getCamera().getPosition().getX() - 1);
        pointText->setText(Util::String::format("Points: %u", static_cast<uint32_t>(getCamera().getPosition().getX())));

}

void PGame::keyPressed(Util::Io::Key key) {
    switch (key.getScancode()) {
        case Util::Io::Key::ESC :
            Util::Game::GameManager::getGame().stop();
            break;
        case Util::Io::Key::D :
            moveRight = true;
            break;

        case Util::Io::Key::A :
            moveLeft = true;
            break;
    }
}

void PGame::keyReleased(Util::Io::Key key) {
    switch (key.getAscii()) {
        case 'a':
            moveLeft = false;
            break;
        case 'd':
            moveRight = false;
            break;
    }
}