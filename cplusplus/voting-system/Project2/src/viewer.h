/**
 * @file viewer.h
 *
 * @copyright 2019 5801 Team24, All rights reserved.
 */

#ifndef SRC_VIEWER_H_
#define SRC_VIEWER_H_

#include "src/Voting_System.h"

/**
 * @brief Environment for which the simulation runs
 */
class Viewer {
 public:
  virtual ~Viewer() {}
  virtual bool RunViewer() = 0;
  virtual void SetVotingSystem(Voting_System* vote_sys) = 0;
};

#endif  // SRC_VIEWER_H_
