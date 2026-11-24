
#include "boatAI.hpp"
#include <experimental/random>

using namespace std::experimental;

BoatAI BoatAI::create(const int& y, const int& interval)
{
	sim::physics::RigidBody* b = engine.createGenericBoat();
	BoatAI boat(b, b->getState(), y, interval);

	return boat;
}

BoatAI::BoatAI(sim::physics::RigidBody*& pbody, const sim::physics::State& pstate, const int& y, const int& pinterval):
    Boat(pbody, pstate, y), interval(pinterval), last(std::chrono::steady_clock::now()), crazy(false)
{

}

void BoatAI::handle_controls()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);

    // Cooldown sur le chargement des touches appuyées
    if (elapsed.count() >= interval) {

        controls c;
        if(crazy){
            c = controls(
                randint(0, 100) == 0, // 1% de chance d'avancer
                randint(0, 100) == 0, // 1% de chance de freiner 
                randint(0, 100) > 25, // 75% de chacnes de tourner
                randint(0, 100) > 25, // 75% de chacnes de tourner
                randint(0, 100) > 25, // 75% de chacnes de tirer
                randint(0, 100) > 25  // 75% de chacnes de tirer
            );

            crazy = randint(0, 100) > 5; // 95% de chances de rester crazy
        } else {
            c = controls(
                randint(0, 100) > 25, // 75% de chacnes d'avancer
                randint(0, 20) == 0,
                randint(0, 10) == 0,
                randint(0, 10) == 0,
                randint(0, 50) == 0, // 1/50 de tirer
                randint(0, 50) == 0  // 1/50 de tirer
            );

            bool become_crazy = randint(0, 100) > 99;
            crazy = become_crazy; // 1% de chances de devenir crazy
        }

        // Si le bateau 
        set_controls(c);
        last = now; // reset le timer
    }

    Boat::_handle_controls();
}
