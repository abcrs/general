/**
 * @file iobservable.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#include "src/iobservable.h"

// Add new observer to list maintaind in IObservable object
void IObservable::RegisterObserver(IObserver * observer) {
    observers_.push_back(observer);
}

// Clear observers from list maintained in IObservable object
void IObservable::ClearObservers() {
    observers_.clear();
}

// Notify all observers of relevant information change5
void IObservable::NotifyBusObservers(BusData * data) {
    for (std::vector<IObserver *>::iterator iter = observers_.begin();
        iter != observers_.end(); ++iter) {
          if (*iter != 0) {
              (*iter)->BNotify(data);
        }
    }
}

void IObservable::NotifyStopObservers(StopData * data) {
    for (std::vector<IObserver *>::iterator iter = observers_.begin();
        iter != observers_.end(); ++iter) {
          if (*iter != 0) {
              (*iter)->SNotify(data);
        }
    }
}
