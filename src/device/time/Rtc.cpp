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

#include <device/cpu/Cpu.h>
#include <kernel/interrupt/InterruptDispatcher.h>
#include <device/interrupt/Pic.h>
#include <device/sound/PcSpeaker.h>
#include "Rtc.h"
#include "Cmos.h"

namespace Device {

Rtc::Rtc(uint8_t interruptRateDivisor) {
    useBcd = (Cmos::read(STATUS_REGISTER_B) & 0x04) == 0;
    useTwelveHours = (Cmos::read(STATUS_REGISTER_B) & 0x02) == 0;
    currentDate = readDate();
    setInterruptRate(interruptRateDivisor);
}

Rtc &Rtc::getInstance() {
    static Rtc instance;
    return instance;
}

void Rtc::plugin() {
    Cpu::disableInterrupts();
    Cmos::disableNmi();

    // Enable 'update ended interrupts': An Interrupt will be triggered after every RTC-update.
    // Enable 'periodic interrupts': Periodic interrupts will be triggered at the set rate.
    uint8_t oldValue = Cmos::read(STATUS_REGISTER_B);
    Cmos::write(STATUS_REGISTER_B, oldValue | INTERRUPT_UPDATE_ENDED | INTERRUPT_PERIODIC);

    // Read status register C. This will clear the data-flag.
    // As long as this flag is set, the RTC won't trigger any interrupts.
    Cmos::read(STATUS_REGISTER_C);

    Kernel::InterruptDispatcher::getInstance().assign(40, *this);
    Pic::getInstance().allow(Pic::Interrupt::RTC);

    Cmos::enableNmi();
    Cpu::enableInterrupts();
}

void Rtc::trigger(Kernel::InterruptFrame &frame) {
    uint8_t interruptStatus = Cmos::read(STATUS_REGISTER_C);

    if ((interruptStatus & INTERRUPT_UPDATE_ENDED) != 0) {
        currentDate = readDate();
    }

    if ((interruptStatus & INTERRUPT_ALARM) != 0) {
        alarm();
    }

    if ((interruptStatus & INTERRUPT_PERIODIC) != 0) {
        time.addNanoseconds(timerInterval);
        advanceTime(Util::Time::Timestamp(0, timerInterval));
        executePendingJobs();
    }
}

bool Rtc::isValid() {
    // The high bit in status register D indicates validity
    uint8_t value = Cmos::read(STATUS_REGISTER_D);
    return (value & 0x80) != 0;
}

Util::Time::Date Rtc::getCurrentDate() {
    return currentDate;
}

void Rtc::setHardwareDate(const Util::Time::Date &date) {
    Util::Time::Date outDate = date;
    uint8_t century;

    if (outDate.getYear() < 100) {
        century = CURRENT_CENTURY;
    } else {
        century = outDate.getYear() / 100;
        uint8_t year = outDate.getYear() % 100;
        outDate.setYear(year);
    }

    if (useTwelveHours) {
        uint8_t hours = outDate.getHours() % 12;
        outDate.setHours(hours);
    }

    if (useBcd) {
        outDate.setSeconds(binaryToBcd(outDate.getSeconds()));
        outDate.setMinutes(binaryToBcd(outDate.getMinutes()));
        outDate.setHours(binaryToBcd(outDate.getHours()));
        outDate.setDayOfMonth(binaryToBcd(outDate.getDayOfMonth()));
        outDate.setMonth(binaryToBcd(outDate.getMonth()));
        outDate.setYear(binaryToBcd(outDate.getYear()));
        century = binaryToBcd(century);
    }

    while (isUpdating());

    Cpu::disableInterrupts();
    Cmos::disableNmi();

    Cmos::write(SECONDS_REGISTER, outDate.getSeconds());
    Cmos::write(MINUTES_REGISTER, outDate.getMinutes());
    Cmos::write(HOURS_REGISTER, outDate.getHours());
    Cmos::write(DAY_OF_MONTH_REGISTER, outDate.getDayOfMonth());
    Cmos::write(MONTH_REGISTER, outDate.getMonth());
    Cmos::write(YEAR_REGISTER, outDate.getYear());
    Cmos::write(CENTURY_REGISTER, century);

    currentDate = date;

    Cmos::enableNmi();
    Cpu::enableInterrupts();
}

void Rtc::setAlarm(const Util::Time::Date &date) const {
    Util::Time::Date alarmDate = date;

    if (useTwelveHours) {
        uint8_t hours = alarmDate.getHours() % 12;
        alarmDate.setHours(hours);
    }

    if (useBcd) {
        alarmDate.setSeconds(binaryToBcd(alarmDate.getSeconds()));
        alarmDate.setMinutes(binaryToBcd(alarmDate.getMinutes()));
        alarmDate.setHours(binaryToBcd(alarmDate.getHours()));
    }

    Cmos::write(ALARM_SECONDS_REGISTER, alarmDate.getSeconds());
    Cmos::write(ALARM_MINUTES_REGISTER, alarmDate.getMinutes());
    Cmos::write(ALARM_HOURS_REGISTER, alarmDate.getHours());

    // Enable 'alarm interrupts': An Interrupt will be triggered every 24 hours at the set alarm time.
    uint8_t oldValue = Cmos::read(STATUS_REGISTER_B);
    Cmos::write(STATUS_REGISTER_B, oldValue | 0x20);
}

uint8_t Rtc::bcdToBinary(uint8_t bcd) {
    return (bcd & 0x0F) + ((bcd / 16) * 10);
}

uint8_t Rtc::binaryToBcd(uint8_t binary) {
    return (binary % 10) + ((binary / 10) << 4);
}

bool Rtc::isUpdating() {
    return (Cmos::read(STATUS_REGISTER_A) & 0x80) == 0x80;
}

Util::Time::Date Rtc::readDate() const {
    while (isUpdating());

    Util::Time::Date date;
    date.setSeconds(Cmos::read(SECONDS_REGISTER));
    date.setMinutes(Cmos::read(MINUTES_REGISTER));
    date.setHours(Cmos::read(HOURS_REGISTER));
    date.setDayOfMonth(Cmos::read(DAY_OF_MONTH_REGISTER));
    date.setMonth(Cmos::read(MONTH_REGISTER));
    date.setYear(Cmos::read(YEAR_REGISTER));

    uint8_t century = Cmos::read(CENTURY_REGISTER);
    if (century == 0) {
        century = CURRENT_CENTURY;
    }

    if (useBcd) {
        century = bcdToBinary(century);
        date.setSeconds(bcdToBinary(date.getSeconds()));
        date.setMinutes(bcdToBinary(date.getMinutes()));
        date.setHours(bcdToBinary(date.getHours()) | (date.getHours() & 0x80));
        date.setDayOfMonth(bcdToBinary(date.getDayOfMonth()));
        date.setMonth(bcdToBinary(date.getMonth()));
        date.setYear(bcdToBinary(date.getYear()) + (century * 100));
    }

    if (useTwelveHours && (date.getHours() & 0x80)) {
        uint8_t hours = ((date.getHours() & 0x7F) + 12) % 24;
        date.setHours(hours);
    }

    return date;
}

void Rtc::alarm() {
    static AlarmRunnable alarmRunnable;
    registerJob(alarmRunnable, Util::Time::Timestamp(0, 500000000), 6);
}

void Rtc::setInterruptRate(uint8_t divisor) {
    if (divisor < 3 || divisor > 15) {
        Util::Exception::throwException(Util::Exception::INVALID_ARGUMENT, "RTC: Interrupt rate divisor must be between 3 and 15");
    }

    uint8_t oldValue = Cmos::read(STATUS_REGISTER_A);
    Cmos::write(STATUS_REGISTER_A, (oldValue & 0xf0) | divisor);

    // Frequency is divided by 2^divisor
    timerInterval = static_cast<uint32_t>(1000000000 / (BASE_FREQUENCY / (1 << (divisor - 1))));
}

Util::Time::Timestamp Rtc::getTime() {
    return time;
}

bool Rtc::isAvailable() {
    Cpu::disableInterrupts();
    Cmos::disableNmi();

    uint8_t oldValue = Cmos::read(STATUS_REGISTER_A);

    for (uint8_t i = 3; i <= 15; i++) {
        Cmos::write(STATUS_REGISTER_A, (oldValue & 0xf0) | i);
        uint8_t currentValue = Cmos::read(STATUS_REGISTER_A) & 0x0f;

        if (currentValue != i) {
            Cmos::enableNmi();
            Cpu::enableInterrupts();
            return false;
        }
    }

    Cmos::write(STATUS_REGISTER_A, oldValue);

    Cmos::enableNmi();
    Cpu::enableInterrupts();
    return true;
}

}