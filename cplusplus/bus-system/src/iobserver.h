/**
 * @file iobserver.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/data_structs.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief: IObserver is an abstract class to observe
 *
 * Other classes inherit IObserver, as to allow them to observe
 * objects of the type IObserverable.
 **/
class IObserver {
 public:
    /**
     * @brief: Vitual method to notify observers
     *
     * Virtual method to establish the class
     * Will be used to update observers on new information
     *
     * @param[in]: info, new information to be processed
     **/
    virtual void BNotify(BusData * info) = 0;

    /**
     * @brief: Vitual method to notify observers
     *
     * Virtual method to establish the class
     * Will be used to update observers on new information
     *
     * @param[in]: info, new information to be processed
     **/
    virtual void SNotify(StopData * info) = 0;
};

#endif  // SRC_IOBSERVER_H_
