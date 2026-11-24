
#pragma once

#include "entity.hpp"
#include "finishline.hpp"
#include "cannonball.hpp"
#include <chrono>
#include <iostream>

inline constexpr int INTERVAL_MS = 1000;
enum class BOATYPE {RIDICULOUS, NORMAL, OUTRAGEOUSLYHARD};

struct controls {
	bool fwd_key;
	bool bwd_key;
	bool left_key;
	bool right_key;
    bool shoot_left_key;
    bool shoot_right_key;

	controls():
	fwd_key(false), bwd_key(false), left_key(false), right_key(false), shoot_left_key(false), shoot_right_key(false)
	{}

	controls(const bool& pZ, const bool& pS, const bool& pQ, const bool& pD, const bool& pA, const bool& pE):
	fwd_key(pZ), bwd_key(pS), left_key(pQ), right_key(pD), shoot_left_key(pA), shoot_right_key(pE)
	{}
};

class Boat: public Entity<sf::ConvexShape> {
protected:
    void shoot(const bool& right = true);
    void _handle_controls();

    sim::physics::RigidBody* body;
    const sim::physics::State& state;
    float Velocity; // Vitesse du bateau
    float Acceleration; // Accélération du bateau
    float angularVelocity;
    float default_y;
    controls _controls;
    std::chrono::_V2::steady_clock::time_point last_shoot;

    sf::Keyboard::Key fwd_key;
    sf::Keyboard::Key bwd_key;
    sf::Keyboard::Key left_key;
    sf::Keyboard::Key right_key;
    sf::Keyboard::Key shoot_left_key;
    sf::Keyboard::Key shoot_right_key;

    inline void set_controls(const controls& c) { _controls = c; }

public:
    Boat(sim::physics::RigidBody*& pbody, const sim::physics::State& pstate, const float& y);
    virtual ~Boat() {};
    
    ///////////////////////////////////
    ///////////// SETTER //////////////
    ///////////////////////////////////

    /// @brief set the position of the boat
    /// @param v new position
    inline void setPosition(const sim::common::Vector2& v) override
    {
        body->setPosition(v.x, v.y);
        Entity::setPosition(v);
    }

    /// @brief set the position of the boat
    /// @param v new position
    inline void setPosition(const sf::Vector2f& v) override
    {
        body->setPosition(v.x, v.y);
        Entity::setPosition(v);
    }

    /// @brief set the angular velocity of the boat
    /// @param n new angular velocity
    inline void setAngularVelocity(const float& n)
    {
        body->setAngularVelocity(angularVelocity);
    }

    /// @brief set the new rotation of the boat
    /// @param f new rotation's angle
    inline void setRotation(const float& f) override
    {
        body->setRotation(f);
        Entity::setRotation(f);
    }

    inline void resetVelocity()
    {
        Velocity = 0.f;
    }

    /// @brief reset all parameter of the boat (Velocity, Acceleration, angularVelocity)
    inline void reset()
    {
        setPosition(sf::Vector2f{0, default_y});
        resetVelocity();
        Acceleration = 0.0f;

        body->setAngularVelocity(0.0f);
        body->setVelocity_body(0, 0);
    }

    inline void set_keys_controls(
        const sf::Keyboard::Key& _fwd_key,
        const sf::Keyboard::Key& _bwd_key,
        const sf::Keyboard::Key& _left_key,
        const sf::Keyboard::Key& _right_key,
        const sf::Keyboard::Key& _shoot_left_key,
        const sf::Keyboard::Key& _shoot_right_key
    )
    {
        fwd_key = _fwd_key;
        bwd_key = _bwd_key;
        left_key = _left_key;
        right_key = _right_key;
        shoot_left_key = _shoot_left_key;
        shoot_right_key = _shoot_right_key;
    }
    

    /// @brief set the shape of the boat, default is BOATYPE::NORMAL
    /// @param boattype the type of the boat
    void setShape(const BOATYPE& boattype=BOATYPE::NORMAL);

    /////////////////////////////////////////////
    ///////////// CONTROL HANDLING //////////////
    /////////////////////////////////////////////

    void Forward();
    void Backward();
    void ChargingBoost();
    void Idle();

    void update();

    void TurningLeft();
    void TurningRight();
    void NotTurning();
    virtual void handle_controls() = 0;

    inline void shoot_right() { shoot(); }
    inline void shoot_left() { shoot(false); }
};

extern sim::physics::PhysicsEngine engine;
