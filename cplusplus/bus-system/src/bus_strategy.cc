/**
 * @file bus_strategy.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#include "src/bus_strategy.h"

static int morn_strat = 0;
static int after_strat = 0;
static int even_strat = 0;

int Strategy::GetTime() {
    time_t t = time(0);
    struct tm now;
    localtime_r(&t, &now);

    return now.tm_hour;
}

int MorningStrategy::PickBus() {
    time_t t = time(0);
    struct tm now;
    localtime_r(&t, &now);
    char buffer[8];
    strftime(buffer, 8, "%R", &now);
    std::cout << buffer;
    std::cout << " - Strategy: " << morn_strat % 2;

    if (morn_strat % 2 == 0) {
        std::cout << " created a Small Bus" << std::endl;
        morn_strat++;
        return 1;
    } else {
        std::cout << " created a Regular Bus" << std::endl;
        morn_strat++;
        return 2;
    }
}

int AfternoonStrategy::PickBus() {
    time_t t = time(0);
    struct tm now;
    localtime_r(&t, &now);
    char buffer[8];
    strftime(buffer, 8, "%R", &now);
    std::cout << buffer;
    std::cout << " - Strategy: " << after_strat % 2;

    if (after_strat % 2 == 0) {
        std::cout << " created a Regular Bus" << std::endl;
        after_strat++;
        return 2;
    } else {
        std::cout << " created a Large Bus" << std::endl;
        after_strat++;
        return 3;
    }
}

int EveningStrategy::PickBus() {
    time_t t = time(0);
    struct tm now;
    localtime_r(&t, &now);
    char buffer[8];
    strftime(buffer, 8, "%R", &now);
    std::cout << buffer;
    std::cout << " - Strategy: " << even_strat % 3;

    if (even_strat % 3 == 0) {
        std::cout << " created a Small Bus." << std::endl;
        even_strat++;
        return 1;
    } else if (even_strat % 3 == 1) {
        std::cout << " created a Regular Bus." << std::endl;
        even_strat++;
        return 2;
    } else {
        std::cout << " created a Large Bus." << std::endl;
        even_strat++;
        return 3;
    }
}

int OvernightStrategy::PickBus() {
    time_t t = time(0);
    struct tm now;
    localtime_r(&t, &now);
    char buffer[8];
    strftime(buffer, 8, "%R", &now);
    std::cout << buffer;
    std::cout << " - Overnight Small Bus created." << std::endl;

    return 1;
}
