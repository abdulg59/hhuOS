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
 *
 * The game engine is based on a bachelor's thesis, written by Malte Sehmer.
 * The original source code can be found here: https://github.com/Malte2036/hhuOS
 */
#ifndef HHUOS_LINEARMOVEMENTCOMPONENT_H
#define HHUOS_LINEARMOVEMENTCOMPONENT_H

#include "Component.h"

namespace Util {
namespace Game {
class Entity;
}  // namespace Game
}  // namespace Util

namespace Util::Game {

class LinearMovementComponent : public Component {


public:
    /**
    * Constructor.
    */
    explicit LinearMovementComponent(Entity &entity);

    /**
     * Copy Constructor.
     */
    LinearMovementComponent(const LinearMovementComponent &other) = delete;

    /**
     * Assignment operator.
     */
    LinearMovementComponent &operator=(const LinearMovementComponent &other) = delete;

    /**
     * Destructor.
     */
    ~LinearMovementComponent() = default;

protected:

    void update(double delta) override;
};

}

#endif
