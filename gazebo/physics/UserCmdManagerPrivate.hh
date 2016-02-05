/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef _GAZEBO_PHYSICS_USERCMDMANAGER_PRIVATE_HH_
#define _GAZEBO_PHYSICS_USERCMDMANAGER_PRIVATE_HH_

#include <string>
#include <vector>
#include <sdf/sdf.hh>

#include "gazebo/common/CommonTypes.hh"

#include "gazebo/msgs/msgs.hh"

#include "gazebo/physics/PhysicsTypes.hh"
#include "gazebo/physics/UserCmdManager.hh"
#include "gazebo/physics/WorldState.hh"

#include "gazebo/transport/TransportTypes.hh"

namespace gazebo
{
  namespace physics
  {
    /// \internal
    /// \brief Private data for the UserCmdManager class
    class UserCmdPrivate
    {
      /// \brief Pointer to the world.
      public: WorldPtr world;

      /// \brief Whole world state the moment the user command was executed.
      public: WorldState startState;

      /// \brief Whole world state for the most recent time the user has
      /// triggered undo for this command.
      public: WorldState endState;

      /// \brief Unique ID identifying this command in the server.
      public: unsigned int id;

      /// \brief Description for the command.
      public: std::string description;

      /// \brief Type of command, such as MOVING or DELETING.
      public: msgs::UserCmd::Type type;

      /// \brief Type of command, such as MOVING or DELETING.
      public: std::string entityName;

      /// \brief SDF for the entity being inserted or deleted.
      public: sdf::SDFPtr sdf;

      /// \brief Pointer to the user command manager.
      public: UserCmdManagerPtr manager;

      /// \brief Pointer to the user command manager.
      public: UserCmd::CmdStatus status;
    };

    class UserCmd;

    /// \internal
    /// \brief Private data for the UserCmdManager class
    class UserCmdManagerPrivate
    {
      /// \brief Pointer to the world.
      public: WorldPtr world;

      /// \brief Counter to generate unique ids for commands in a sequence.
      public: unsigned int idCounter;

      /// \brief Transportation node.
      public: transport::NodePtr node;

      /// \brief Subscriber to user command messages.
      public: transport::SubscriberPtr userCmdSub;

      /// \brief Subscriber to undo redo messages.
      public: transport::SubscriberPtr undoRedoSub;

      /// \brief Publisher of undo redo statistics messages.
      public: transport::PublisherPtr userCmdStatsPub;

      /// \brief Publisher of model modify messages.
      public: transport::PublisherPtr modelModifyPub;

      /// \brief Publisher of light modify messages.
      public: transport::PublisherPtr lightModifyPub;

      /// \brief Publisher of model factory messages.
      public: transport::PublisherPtr modelFactoryPub;

      /// \brief Publisher of light factory messages.
      public: transport::PublisherPtr lightFactoryPub;

      /// \brief Publisher of world control messages.
      public: transport::PublisherPtr worldControlPub;

      /// \brief List of commands which can be undone.
      public: std::vector<UserCmdPtr> undoCmds;

      /// \brief List of commands which can be redone.
      public: std::vector<UserCmdPtr> redoCmds;

      /// \brief Vector of entities whose insertions are pending.
      public: std::list<UserCmdPtr> cmdQueue;

      /// \brief All the event connections.
      public: event::Connection_V connections;

      /// \brief Vector of entities whose insertions are pending.
      public: std::vector<std::string> insertionsPending;

      /// \brief Vector of states waiting to be applied.
      public: std::list<WorldState> pendingStates;
    };
  }
}
#endif

