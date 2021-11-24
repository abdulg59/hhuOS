/*
 * Copyright (C) 2018-2021 Heinrich-Heine-Universitaet Duesseldorf,
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

#include "CursorRunnable.h"
#include "LinearFrameBufferTerminal.h"

namespace Device::Graphic {

CursorRunnable::CursorRunnable(LinearFrameBufferTerminal &terminal) : terminal(terminal) {}

void CursorRunnable::run() {
    if (!terminal.cursorLock.tryAcquire()) {
        return;
    }

    const auto character = terminal.characterBuffer[terminal.currentRow * terminal.getColumns() + terminal.currentColumn];
    const char c = visible ? static_cast<char>(219) : character.value;
    terminal.stringDrawer.drawChar(terminal.font, terminal.currentColumn * terminal.font.getCharWidth(), terminal.currentRow * terminal.font.getCharHeight(), c, character.foregroundColor, character.backgroundColor);

    visible = !visible;

    terminal.cursorLock.release();
}

}