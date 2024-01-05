//Meant to manage loading and unloading of sprites
//Sprite can be built before drawing
//Asset Manager should be given to the GUI class to handle asset loading

//Widely supported preprocessor directive to prevent multiple loadings of this file
#pragma once

//Prompt:
//This class should load an image file from file as asset structure inside a gacl_asset, and save the index in a map. The asset name is the path and image name.
//An hash table quickly decode the index of an asset name to return the sprite

#include <map>

#include <SFML/Graphics.hpp>

//BUG: cause a linker error due to redefinition of "<< Rect"
//#include "utils.hpp"

class Asset_manager
{
public:
	//Graphics Asset
	struct Asset
	{
		std::string s_asset_name;
		sf::Texture cl_texture;

		sf::Vector2u get_sprite_size()
		{
			return this->cl_texture.getSize();
		}
		//Stringfy an asset
		std::string to_str()
		{
			sf::Vector2u an_size = get_sprite_size();
			return std::string("Asset name: ") +s_asset_name +std::string(" | Width: ") +std::to_string( an_size.x ) +std::string(" | Height: ") +std::to_string( an_size.y );
		}
	};

	Asset_manager()
	{
		return;
	}

	~Asset_manager()
	{
		return;
	}

	bool draw_asset( sf::RenderTexture& ircl_surface, std::string is_asset_name )
	{
		return this->draw_asset( ircl_surface, is_asset_name, sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 0.0f, 0.0f ), 1.0f );
	}

	bool draw_asset( sf::RenderTexture& ircl_surface, std::string is_asset_name, sf::Vector2f iaf32_position, sf::Vector2f iaf32_size, float if32_transparency )
	{
		int n_index;
		if (this->find_asset_index(is_asset_name, n_index) == true)
		{
			std::cerr << "ERR: Failed to find asset\n";
			return true; //FAIL
		}
		Asset &st_asset = this->gacl_asset[n_index];
		sf::Sprite cl_sprite;
		cl_sprite.setTexture(st_asset.cl_texture);
		if (this->cx_debug_enabled)
			std::cout << "Found Asset: " << st_asset.to_str() << "\n";

		cl_sprite.setPosition(iaf32_position);

		// Only resize if the desired size is not (0,0)
		if (iaf32_size.x != 0 && iaf32_size.y != 0)
		{
			// Calculate the scale factors
			float scaleX = iaf32_size.x / cl_sprite.getGlobalBounds().width;
			float scaleY = iaf32_size.y / cl_sprite.getGlobalBounds().height;

			// Set the scale
			cl_sprite.setScale(scaleX, scaleY);
		}

		// Set the transparency
		sf::Color color = cl_sprite.getColor();
		color.a = if32_transparency * 255; // convert from [0,1] to [0,255]
		cl_sprite.setColor(color);

		ircl_surface.draw( cl_sprite );

		return false; //OK
	}

	bool load_from_file( std::string is_path )
	{
		Asset asset;
        asset.s_asset_name = is_path;
        if (!asset.cl_texture.loadFromFile(is_path))
            return true;
        gacl_asset.push_back(asset);
        ghst_name_to_index[is_path] = gacl_asset.size() - 1;
        if (this->cx_debug_enabled)
			std::cout << "loaded: " << asset.s_asset_name << " | as index: " << ghst_name_to_index[is_path] << "\n";
		return false; //OK
	}

private:

	bool find_asset_index( std::string is_asset_name, int &orn_index )
	{
		// Search for the asset name in the Map
		auto it = this->ghst_name_to_index.find(is_asset_name);
		if (it == this->ghst_name_to_index.end())
		{
			std::cerr << "ERR: Key doesn't exist in Map: " << is_asset_name << "\n";
			orn_index = 0;
			return true; //FAIL
		}

		int n_index = it->second;
		if ((n_index < 0) || (n_index >= this->gacl_asset.size()))
		{
			std::cerr << "ERR: Index is OOB " << n_index << " of " << gacl_asset.size() << "\n";
			orn_index = 0;
			return true; //FAIL
		}

		if (this->cx_debug_enabled)
			std::cout << "Retrieve: " << is_asset_name << " | Index: " << n_index << "\n";
		orn_index = n_index;
		return false; //OK
	}

	//Asset storage class
	std::vector<Asset> gacl_asset;
	//Hash table associating resource to index inside vector
	std::map<std::string, int> ghst_name_to_index;

	static const constexpr bool cx_debug_enabled = false;

}; //class Asset_manager

