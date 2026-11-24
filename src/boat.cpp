
#include "boat.hpp"
#include <cmath>

inline constexpr float maxSpeed = 1.0f;  // Vitesse maximale normale du bateau
inline constexpr float maxBoostSpeed = 8.0f;  // Vitesse maximale boostée
inline constexpr float acceleration = 0.0005f;  // Accélération normale quand seul Z est enfoncé
inline constexpr float boostIncrement = 0.01f;  // Incrémentation du boost quand S et Z sont enfoncés
inline constexpr float deceleration = 0.0002f;  // Décélération quand on relâche Z
inline constexpr float reverseDeceleration = deceleration * 10;  // Réduction rapide avec S

sim::physics::PhysicsEngine engine;

sf::Vector2f fromAngle(float angleDeg) {
    float rad = angleDeg * sim::common::DEG_TO_RAD;
    return { std::cos(rad) / 10, std::sin(rad) / 10 };
}

sf::Vector2f perpendicular(const sf::Vector2f& v, bool right = true) {
    return right ? sf::Vector2f{-v.y, v.x}
                 : sf::Vector2f{ v.y, -v.x};
}

float moveTowards(float x, float y, float step) {
    if (std::abs(y - x) <= step) return y;  // Évite les dépassements
    return x + std::copysign(step, y - x);  // Avance dans la bonne direction
}

Boat::Boat(sim::physics::RigidBody*& pbody, const sim::physics::State& pstate, const float& y):
    body(pbody), state(pstate), Velocity(0.0f), Acceleration(0.0f), angularVelocity(0.0f), default_y(y)
{
    shape.setOrigin(75, 25);
    shape.setPosition(sf::Vector2f(0, y));
    body->setPosition(0, y);

    setShape();

    shape.setFillColor(sf::Color(80, 80, 120));       // bleu-gris
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
}

void Boat::setShape(const BOATYPE& boattype)
{
    // Coque du bateau (forme arrondie)
    shape.setPointCount(6); // On passe à 6 points pour un contour plus smooth

    shape.setPoint(0, {0,    0});   // Pointe avant (centrée)
    shape.setPoint(1, {100,  0});   // Flanc droit avant
    shape.setPoint(2, {150, 25});   // Flanc droit arrière
    shape.setPoint(3, {100, 50});   // Arrière centré (poupe)
    shape.setPoint(4, {0,   50});   // Flanc gauche arrière
    switch (boattype) {
        case BOATYPE::RIDICULOUS:
            shape.setScale({0.2, 0.2});
            break;
        case BOATYPE::NORMAL:
            shape.setScale({0.6, 0.6});
            break;
        case BOATYPE::OUTRAGEOUSLYHARD:
            shape.setScale({1, 1});
            break;
    }
}

void Boat::_handle_controls(){
    // 1. Gestion de la décélération forcée avec S (avant le turbo pour éviter l'écrasement)
	if (_controls.bwd_key) {
	    Backward();
	}
	
	// 2. Gestion du boost et de l'accélération normale
	if (_controls.fwd_key) {
	    if (_controls.bwd_key) {
	        ChargingBoost();
	    } else {
	        Forward();
	    }
	} else {
	    Idle();
	}
	
	// 3. Gestion de la rotation
    bool turning = false;
	if (_controls.right_key){
        turning = true;
	    TurningRight();
    }
    if (_controls.left_key){
        turning = true;
	    TurningLeft();
	}
    if(!turning) {
	    NotTurning();
	}

    if(_controls.shoot_left_key) shoot(false);
    if(_controls.shoot_right_key) shoot();
}

void Boat::Forward()
{

    if(Acceleration > 0.0f) {
        /*
        std::cout << "Acceleration : " << boat.Acceleration << std::endl;
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("car-drifting.wav")) {  // Remplace "sound.wav" par ton fichier
            std::cerr << "Erreur : Impossible de charger le son !" << std::endl;
            return -1;
        }
    
        // Associer le buffer au son et jouer
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        */
    }

    // Accélération normale avec Z seul
    Velocity = moveTowards(Velocity + acceleration + Acceleration, maxSpeed, 0.005f);
    Acceleration = 0.0f;
}

void Boat::Backward()
{
    Velocity = std::max(0.0f, Velocity - reverseDeceleration);
}

void Boat::ChargingBoost()
{
	// Boost tant que S et Z sont maintenus
	Acceleration = std::min(maxBoostSpeed, Acceleration + boostIncrement);
}

void Boat::Idle()
{
    Acceleration = 0.0f;
	// Décélération progressive quand Z est relâché
	Velocity = moveTowards(Velocity, 0, 0.005f);
	Velocity = std::max(0.0f, Velocity - deceleration);
}

void Boat::TurningLeft()
{
    angularVelocity = std::max(-0.05f, angularVelocity - 0.0001f);
    body->setAngularVelocity(angularVelocity);
}

void Boat::TurningRight()
{
    angularVelocity = std::min(0.05f, angularVelocity + 0.0001f);
    body->setAngularVelocity(angularVelocity);
}

void Boat::NotTurning()
{
    angularVelocity = moveTowards(angularVelocity, 0, 0.0001f);;
    body->setAngularVelocity(angularVelocity);
}

void Boat::update()
{
    body->setVelocity_body(Velocity, 0);
    Entity::setPosition(state.position);
    Entity::setRotation(state.yaw * sim::common::RAD_TO_DEG);
}

void Boat::shoot(const bool& right)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shoot);

    // Cooldown sur le tir
    if (elapsed.count() >= INTERVAL_MS) {
        sf::Vector2f dir = fromAngle(shape.getRotation());
        sf::Vector2f fire_dir = perpendicular(dir, right); // direction du tir
        sf::Vector2f pos = shape.getPosition() + fire_dir * 800.f; // décale dans la bonne direction

        Cannonball::create(pos, fire_dir);
        last_shoot = now;
    }
}
