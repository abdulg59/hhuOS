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
 *
 * The network stack is based on a bachelor's thesis, written by Hannes Feil.
 * The original source code can be found here: https://github.com/hhuOS/hhuOS/tree/legacy/network
 */

#ifndef HHUOS_LIB_SOCKET_H
#define HHUOS_LIB_SOCKET_H

#include <cstdint>

namespace Util {
namespace Network {
class NetworkAddress;
class Datagram;
}  // namespace Network
}  // namespace Util

namespace Util::Network {

class Socket {

public:

    enum Type {
        ETHERNET, IP4, IP6, ICMP, UDP, TCP
    };

    enum Request {
        BIND, GET_LOCAL_ADDRESS
    };

    /**
     * Copy Constructor.
     */
    Socket(const Socket &other) = delete;

    /**
     * Assignment operator.
     */
    Socket &operator=(const Socket &other) = delete;

    /**
     * Destructor.
     */
    ~Socket() = default;

    static Socket createSocket(Type socketType);

    [[nodiscard]] bool bind(const NetworkAddress &address) const;

    [[nodiscard]] NetworkAddress* getLocalAddress() const;

    bool send(const Util::Network::Datagram &datagram) const;

    bool receive(Util::Network::Datagram &datagram) const;

private:
    /**
     * Default Constructor.
     */
    explicit Socket(int32_t fileDescriptor, Type socketType);

    int32_t fileDescriptor;
    Type socketType;
};

}

#endif