
#include "boatplayer.hpp"

void BoatPlayer::handle_controls()
{
	set_controls(controls(
		sf::Keyboard::isKeyPressed(fwd_key),
		sf::Keyboard::isKeyPressed(bwd_key),
		sf::Keyboard::isKeyPressed(left_key),
		sf::Keyboard::isKeyPressed(right_key),
		sf::Keyboard::isKeyPressed(shoot_left_key),
		sf::Keyboard::isKeyPressed(shoot_right_key)
	));
	Boat::_handle_controls();
}

BoatPlayer BoatPlayer::create(const int& y)
{
	sim::physics::RigidBody* b = engine.createGenericBoat();
	BoatPlayer boat(b, b->getState(), y);

	return boat;
}