#include <SFML/Graphics.hpp>

//Utils.cpp
template <typename T>
extern std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& iraf32);

//5,5
//4,5
//4,4
//5,4

namespace Utils
{

class Coordinate_generator
{
public:
	Coordinate_generator()
	{
		return;
	}
	Coordinate_generator( sf::Vector2i ian_map_size ) : gan_size( ian_map_size )
	{
		gaf32_map_center.x = 0.5f *(0.0f +float(ian_map_size.x));
		gaf32_map_center.y = 0.5f *(0.0f +float(ian_map_size.y));
		std::cout << gaf32_map_center;
	}



private:
	sf::Vector2i gan_size;
	sf::Vector2i gan_coordinate;
	sf::Vector2f gaf32_map_center;
};

}; //namespace Utils
