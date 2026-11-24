
#pragma once

#include <SFML/Graphics.hpp>
#include "physics/common.h"

// T doit hériter de sf::Shape
template <typename T>
class Entity: public sf::Drawable {
public:
    Entity() = default;
    virtual ~Entity() noexcept = default;
    Entity(const T& pshape): shape(pshape) {}
    Entity& operator=(const Entity& e)
    {
        shape = e.shape;
    }

    template <typename U>
    inline bool hasCrossed(const Entity<U>& e) const
    {
        return shape.getGlobalBounds().intersects(e.get_shape().getGlobalBounds());
    }

    T get_shape() const { return shape; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(shape, states);
    }

    virtual inline void setPosition(const sim::common::Vector2& v)
    {
        const double& x = v.x;
        const double& y = v.y;

        shape.setPosition(x, y);
    }

    virtual inline void setPosition(const sf::Vector2f& v)
    {
        const double& x = v.x;
        const double& y = v.y;

        shape.setPosition(x, y);
    }

    virtual inline void setRotation(const float& f)
    { shape.setRotation(f); }

    inline void setFillColor(const sf::Color& color) { shape.setFillColor(color); }
    inline void setScale(const sf::Vector2f& scale) { shape.setScale(scale); }

protected:
    T shape;
};
