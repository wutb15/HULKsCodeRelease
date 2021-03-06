#include "Tools/Chronometer.hpp"

#include "ActionCommand.hpp"
#include "BehaviorModule.hpp"
#include "Units.hpp"


BehaviorModule::BehaviorModule(const ModuleManagerInterface& manager)
  : Module(manager, "BehaviorModule")
  , remoteMotionRequest_(*this, "remoteMotionRequest", [this] { std::lock_guard<std::mutex> lg(actualRemoteMotionRequestLock_); actualRemoteMotionRequest_ = remoteMotionRequest_(); })
  , useRemoteMotionRequest_(*this, "useRemoteMotionRequest", []{})
  , gameControllerState_(*this)
  , ballState_(*this)
  , robotPosition_(*this)
  , bodyPose_(*this)
  , playerConfiguration_(*this)
  , playingRoles_(*this)
  , motionState_(*this)
  , headMotionOutput_(*this)
  , teamBallModel_(*this)
  , teamPlayers_(*this)
  , ballSearchPosition_(*this)
  , fieldDimensions_(*this)
  , strikerAction_(*this)
  , keeperAction_(*this)
  , cycleInfo_(*this)
  , setPosition_(*this)
  , defendingPosition_(*this)
  , bishopPosition_(*this)
  , supportingPosition_(*this)
  , buttonData_(*this)
  , worldState_(*this)
  , motionRequest_(*this)
  , eyeLEDRequest_(*this)
  , actionCommand_(ActionCommand::dead())
  , dataSet_(*this, *gameControllerState_, *ballState_, *robotPosition_, *bodyPose_, *playerConfiguration_, *playingRoles_, *motionState_, *headMotionOutput_,
             *teamBallModel_, *teamPlayers_, *fieldDimensions_, *strikerAction_, *keeperAction_, *cycleInfo_, *setPosition_, *defendingPosition_,
             *bishopPosition_, *supportingPosition_, *buttonData_, *worldState_, *ballSearchPosition_, actionCommand_)
{

  {
    // This is needed because callbacks are called asynchronously and a MotionRequest is large enough that it is too dangerous.
    std::lock_guard<std::mutex> lg(actualRemoteMotionRequestLock_);
    actualRemoteMotionRequest_ = remoteMotionRequest_();
  }
  useRemoteMotionRequest_() = false;
}

void BehaviorModule::cycle()
{
  Chronometer time(debug(), mount_ + ".cycle_time");
  if (gameControllerState_->state == GameState::PLAYING
      && gameControllerState_->penalty == Penalty::NONE
      && !bodyPose_->fallen
      && useRemoteMotionRequest_())
  {
    std::lock_guard<std::mutex> lg(actualRemoteMotionRequestLock_);
    *motionRequest_ = actualRemoteMotionRequest_;
  }
  else
  {
    actionCommand_ = rootBehavior(dataSet_);
    actionCommand_.toMotionRequest(*motionRequest_);
    actionCommand_.toEyeLEDRequest(*eyeLEDRequest_);
  }
}
