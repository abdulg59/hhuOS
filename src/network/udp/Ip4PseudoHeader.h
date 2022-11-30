/*
 * Copyright (C) 2018-2022 Heinrich-Heine-Universitaet Duesseldorf,
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

#ifndef HHUOS_IP4PSEUDOHEADER_H
#define HHUOS_IP4PSEUDOHEADER_H

#include "network/ip4/Ip4Address.h"
#include "network/NetworkModule.h"

namespace Network::Udp {

class Ip4PseudoHeader {

public:
    /**
     * Constructor.
     */
    Ip4PseudoHeader(const NetworkModule::LayerInformation &information);

    /**
     * Copy Constructor.
     */
    Ip4PseudoHeader(const Ip4PseudoHeader &other) = delete;

    /**
     * Assignment operator.
     */
    Ip4PseudoHeader &operator=(const Ip4PseudoHeader &other) = delete;

    /**
     * Destructor.
     */
    ~Ip4PseudoHeader() = default;

    void write(Util::Stream::OutputStream &stream) const;

    static const constexpr uint32_t HEADER_SIZE = 12;

private:

    const Ip4::Ip4Address sourceAddress;
    const Ip4::Ip4Address destinationAddress;
    const uint16_t datagramLength;
};

}

#endif