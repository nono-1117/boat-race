
#pragma once

#include "boat.hpp"
#include <chrono>
#include <list>

class BoatAI: public Boat {
private:
    int interval;
    std::chrono::_V2::steady_clock::time_point last;
    bool crazy;
    
public:
    BoatAI(sim::physics::RigidBody*& pbody, const sim::physics::State& pstate, const int& y, const int& pinterval);
    void handle_controls() override;

    static BoatAI create(const int& y, const int& interval);
};
