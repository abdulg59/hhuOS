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

#include "Player.h"

#include "lib/util/collection/Array.h"
#include "lib/util/game/Graphics2D.h"
#include "lib/util/game/Sprite.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/entity/event/CollisionEvent.h"
#include "Ground.h"
#include "lib/util/game/entity/collider/Collider.h"
#include "lib/util/game/entity/collider/RectangleCollider.h"
#include "lib/util/game/entity/event/TranslationEvent.h"
#include "lib/util/game/GameManager.h"
#include "lib/util/game/Game.h"



Player::Player(const Util::Math::Vector2D &position) : Util::Game::Entity(TAG, position, Util::Game::RectangleCollider(Util::Math::Vector2D(-0.8, 0), Util::Game::Collider::DYNAMIC, 0.2, 0.2)) {}

void Player::initialize() {
    sprite = Util::Game::Sprite("/initrd/dino/run1.bmp", 0.2, 0.2267);
/*    psystem = new Util::Game::ParticleSystem(100,5,400, Util::Game::Sprite("/initrd/dino/ground.bmp", 0.1, 0.1));
    Util::Game::GameManager::getGame().getCurrentScene().addParticleSystem(psystem);*/
}



void Player::onUpdate(double delta) {
    getCollider().setWidth(sprite.getWidth());
    getCollider().setHeight(sprite.getHeight());
    double x = -(getVelocity().getX()/16.0);
/*
    psystem->updateSystem(getPosition(), Util::Math::Vector2D(x,0), Util::Math::Vector2D(0,0));
*/
}

void Player::draw(Util::Game::Graphics2D &graphics) {
    graphics.drawImage(getPosition(), sprite.getImage(), directionLeft);
}


void Player::moveRight() {
    translateX(speed);
    directionLeft = false;
}

void Player::moveLeft() {
    translateX(-speed);
    directionLeft = true;
}

void Player::reset() {
    if (!hatching) {
        time = 0;
        hatching = false;
        dying = false;
        hatched = false;
        dead = false;
        setVelocity(Util::Math::Vector2D(0, 0));
    }
}

void Player::onTranslationEvent(Util::Game::TranslationEvent &event) {
    if (dying || dead) {
        event.cancel();
    }
}

void Player::onCollisionEvent(Util::Game::CollisionEvent &event) {
    if (event.getSide() == Util::Game::RectangleCollider::BOTTOM && event.getCollidedWidth().getTag() == Ground::TAG) {
        onGround = true;
    }
}