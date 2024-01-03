#include <iostream>

// Overload the << operator for sf::FloatRect
std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect)
{
    os << "sf::FloatRect(" << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << ")";
    return os;
}
