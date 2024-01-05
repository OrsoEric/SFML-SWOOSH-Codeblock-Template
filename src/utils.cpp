#include <iostream>

#include <SFML/Graphics.hpp>

extern std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect);


template <typename T>
extern std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& iraf32);

// Overload the << operator for sf::FloatRect
std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect)
{
    os << "sf::FloatRect(" << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& iraf32)
{
    os << "sf::Vector2f(" << iraf32.x << ", " << iraf32.y << ")";
    return os;
}

