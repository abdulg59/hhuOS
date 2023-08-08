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

#include "Image.h"

#include "lib/util/graphic/Color.h"


namespace Util::Graphic {

Image::Image(uint16_t width, uint16_t height, Color *pixelBuffer) : width(width), height(height), pixelBuffer(pixelBuffer) {

}

Image::~Image() {
    delete[] pixelBuffer;
}

Graphic::Color* Image::getPixelBuffer() const {
    return pixelBuffer;
}

uint16_t Image::getWidth() const {
    return width;
}

uint16_t Image::getHeight() const {
    return height;
}

Image* Image::scale(uint16_t newWidth, uint16_t newHeight){
    auto *newPixelBuffer = new Graphic::Color[newWidth*newHeight];
    double factorX = static_cast<double>(newWidth) / width;
    double factorY = static_cast<double>(newHeight) / height;

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            auto oldX = static_cast<uint16_t>(x / factorX);
            auto oldY = static_cast<uint16_t>(y / factorY);
            newPixelBuffer[newWidth * y + x] = pixelBuffer[width * oldY + oldX];
        }
    }

    return new Image(newWidth, newHeight, newPixelBuffer);
}


 /*   Image* Image::rotate(int angle) {
        auto *newPixelBuffer = new Graphic::Color[width * height];
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                newPixelBuffer[width * y + x] = pixelBuffer[width];
            }
        }
*//*
        double nx_x = rot_x(-angle, 1.0, 0.0);
        double nx_y = rot_x(-angle, 1.0, 0.0);
        double ny_x = rot_x(-angle, 0.0, 1.0);
        double ny_y = rot_x(-angle, 0.0, 1.0);

        double x0 = rot_x(-angle, getWidth() / 2.0, -height / 2.0) + width /2.0;
        double y0 = rot_y(-angle, getWidth() / 2.0, -height / 2.0) + height /2.0;

        for(int y = 0; y<height; y++){
            double x1 = x0;
            double y1 = y0;
            for(int x = 0; x < width; x++){
                int xx = (int) y1;
                int yy = (int) y1;
                newPixelBuffer[x + y * width] = pixelBuffer[xx + yy + width];
                x1 += nx_x;
                y1 += nx_y;
            }

        }*//*
        return nullptr;
    }*/






}