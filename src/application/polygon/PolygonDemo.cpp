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

#include "PolygonDemo.h"

#include "DemoPolygonFactory.h"
#include "application/polygon/DemoPolygon.h"
#include "lib/util/io/key/Key.h"
#include "lib/util/game/GameManager.h"
#include "lib/util/game/Game.h"

namespace Util {
namespace Game {
class Graphics2D;
}  // namespace Game
}  // namespace Util

PolygonDemo::PolygonDemo(uint32_t count) {
    for (uint32_t i = 0; i < count; i++) {
        auto *polygon = factory.createPolygon();
        polygons.offer(polygon);
        addObject(polygon);
    }

    setKeyListener(*this);
}

void PolygonDemo::update(double delta) {
    for (auto &polygon : polygons) {
        polygon->update(delta);
    }
}

void PolygonDemo::keyPressed(Util::Io::Key key) {
    if (key.getScancode() == Util::Io::Key::ESC) {
        Util::Game::GameManager::getGame().stop();
    }

    switch (key.getAscii()) {
        case '+': {
            auto *polygon = factory.createPolygon();
            polygons.offer(polygon);
            addObject(polygon);
            break;
        }
        case '-': {
            if (polygons.size() > 0) {
                removeObject(polygons.poll());
            }
            break;
        }
    }
}

void PolygonDemo::keyReleased(Util::Io::Key key) {}

void PolygonDemo::initializeBackground(Util::Game::Graphics2D &graphics) {}
