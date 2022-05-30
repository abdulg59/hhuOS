/*
 * Copyright (C) 2018-2022 Heinrich-Heine-Universitaet Duesseldorf,
 * Institute of Computer Science, Department Operating Systems
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

#include "FloppyDevice.h"
#include "FloppyMotorControlJob.h"
#include "kernel/system/System.h"
#include "kernel/service/JobService.h"

namespace Device::Storage {

FloppyDevice::FloppyDevice(FloppyController &controller, uint8_t driveNumber, FloppyController::DriveType driveType) :
        controller(controller), driveNumber(driveNumber), driveType(driveType), motorControlJob(new FloppyMotorControlJob(*this)) {
    switch (driveType) {
        case FloppyController::DRIVE_360KB_5_25 :
            cylinders = 40;
            sectorsPerCylinder = 9;
            gapLength = 32;
            break;
        case FloppyController::DRIVE_1200KB_5_25 :
            cylinders = 80;
            sectorsPerCylinder = 15;
            gapLength = 32;
            break;
        case FloppyController::DRIVE_720KB_3_5 :
            cylinders = 80;
            sectorsPerCylinder = 9;
            gapLength = 27;
            break;
        default :
        case FloppyController::DRIVE_1440KB_3_5 :
            cylinders = 80;
            sectorsPerCylinder = 18;
            gapLength = 27;
            break;
        case FloppyController::DRIVE_2880KB_3_5 :
            cylinders = 80;
            sectorsPerCylinder = 36;
            gapLength = 27;
    }

    Kernel::System::getService<Kernel::JobService>().registerJob(motorControlJob, Kernel::Job::Priority::LOW, Util::Time::Timestamp(0, FloppyMotorControlJob::INTERVAL * 1000000));
}

FloppyDevice::CylinderHeadSector FloppyDevice::lbaToChs(uint32_t lbaSector) const {
    return {
        static_cast<uint8_t>(lbaSector / (2 * sectorsPerCylinder)),
        static_cast<uint8_t>((lbaSector % (2 * sectorsPerCylinder)) / sectorsPerCylinder),
        static_cast<uint8_t>((lbaSector % (2 * sectorsPerCylinder)) % sectorsPerCylinder + 1)
    };
}

uint32_t FloppyDevice::getSectorSize() {
    return FloppyController::SECTOR_SIZE;
}

uint64_t FloppyDevice::getSectorCount() {
    return sectorsPerCylinder * cylinders * 2;
}

uint32_t FloppyDevice::read(uint8_t *buffer, uint32_t startSector, uint32_t sectorCount) {
    return performIO(FloppyController::READ, buffer, startSector, sectorCount);
}

uint32_t FloppyDevice::write(const uint8_t *buffer, uint32_t startSector, uint32_t sectorCount) {
    return performIO(FloppyController::WRITE, const_cast<uint8_t*>(buffer), startSector, sectorCount);
}

uint32_t FloppyDevice::performIO(FloppyController::IO operation, uint8_t *buffer, uint32_t startSector, uint32_t sectorCount) {
    uint32_t sectors = 0;
    auto startChs = lbaToChs(startSector);
    auto endChs = lbaToChs(startSector + sectorCount - 1);

    for (uint32_t cylinder = startChs.cylinder; cylinder <= endChs.cylinder; cylinder++) {
        uint8_t head, firstSector, count;
        if (cylinder == startChs.cylinder && cylinder == endChs.cylinder) {
            head = startChs.head;
            firstSector = startChs.sector;
            count = sectorCount;
        } else if (cylinder == startChs.cylinder) {
            head = startChs.head;
            firstSector = startChs.sector;
            count = ((sectorsPerCylinder * 2) - firstSector + 1) - (head * sectorsPerCylinder);
        } else if (cylinder == endChs.cylinder) {
            head = 0;
            firstSector = 1;
            count = endChs.head * sectorsPerCylinder + endChs.sector;
        } else {
            head = 0;
            firstSector = 1;
            count = sectorsPerCylinder * 2;
        }

        auto result = controller.performIO(*this, operation, buffer + sectors * getSectorSize(), cylinder, head, firstSector, count);
        if (result) {
            sectors += count;
        } else {
            return sectors;
        }
    }

    return sectors;
}

uint8_t FloppyDevice::getDriveNumber() const {
    return driveNumber;
}

FloppyController::MotorState FloppyDevice::getMotorState() const {
    return motorState;
}

FloppyController::DriveType FloppyDevice::getDriveType() const {
    return driveType;
}

uint8_t FloppyDevice::getGapLength() const {
    return gapLength;
}

uint8_t FloppyDevice::getSectorsPerCylinder() const {
    return sectorsPerCylinder;
}

uint8_t FloppyDevice::getCylinders() const {
    return cylinders;
}

FloppyController& FloppyDevice::getController() const {
    return controller;
}

void FloppyDevice::setMotorState(FloppyController::MotorState state) {
    if (state == FloppyController::ON) {
        motorControlJob->resetTime();
    }

    FloppyDevice::motorState = state;
}

}