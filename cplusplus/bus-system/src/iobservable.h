/**
 * @file iobservable.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#ifndef SRC_IOBSERVABLE_H_
#define SRC_IOBSERVABLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <list>
#include <iostream>
#include <string>

#include "src/iobserver.h"
#include "src/data_structs.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief: IObservable is a class to be observed
 *
 * Other classes inherit IObservable, as to allow them to interact with
 * the IObserver class, so that they can be observed.
 **/
class IObservable {
 public:
     /**
      * @brief: Adds observes to the mainted list of observers
      *
      * Update the mainted observer_ vector
      *
      * @param[in] observer, a new observer object that will observe
      **/
     void RegisterObserver(IObserver * observer);

    /**
     * @brief: Clears all observers
     *
     * Empties observer_ vector of any observers
     **/
    void ClearObservers();

    /**
     * @brief: Update bus observers
     *
     * Updates all observers with relevant information
     *
     * @param[in]: busdata, the data needed to update observers
     **/
    void NotifyBusObservers(BusData * data);

    /**
     * @brief: Update stop observers
     *
     * Updates all observers with relevant information
     *
     * @param[in]: stopdata, the data needed to update observers
     **/
    void NotifyStopObservers(StopData * data);


 private:
     std::vector<IObserver *> observers_;
};

#endif  // SRC_IOBSERVABLE_H_
