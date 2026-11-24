
#pragma once

#include "boat.hpp"

class BoatPlayer: public Boat {
private:
public:
    BoatPlayer(sim::physics::RigidBody*& _body, const sim::physics::State& _state, const int& _y):
        Boat(_body, _state, _y) {}
    static BoatPlayer create(const int& y);
    void handle_controls() override;
};
