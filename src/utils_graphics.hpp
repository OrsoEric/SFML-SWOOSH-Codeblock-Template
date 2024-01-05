#pragma once

#ifndef _UTILS_GRAPHICS_HPP
	#define _UTILS_GRAPHICS_HPP

#include <SFML/Graphics.hpp>

namespace Utils
{
	//Create a sprite that is a single square of solid colour
	bool create_sprite_solid_color( sf::Sprite &orcl_sprite, sf::Vector2f iaf32_size, sf::Color ie_color_background )
	{
		// Create an image of the desired size filled with the desired color
        sf::Image cl_image;
        cl_image.create(iaf32_size.x, iaf32_size.y, ie_color_background);

        // Create a gs_texture and load the image into it
        sf::Texture cl_texture;
        cl_texture.loadFromImage(cl_image);

		// Create a gcl_sprite and set its gs_texture
        orcl_sprite.setTexture(cl_texture);

		return false; //SUCCESS
	}

	//Create a sprite by loading an image from file
	bool create_sprite_from_file( sf::Texture &orcl_texture, sf::Sprite &orcl_sprite, const std::string& path )
	{
        if (orcl_texture.loadFromFile(path) == false)
        {
            std::cerr << "ERR: loading texture: " << path << "\n";
            return true; //FAIL
        }

		orcl_sprite.setTexture(orcl_texture);

		return false; //SUCCESS
	}

}; //Utils

#else
	#error "Multiple Inclusions of _UTILS_GRAPHICS_HPP"
#endif
