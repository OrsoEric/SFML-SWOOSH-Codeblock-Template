#pragma once

#include <SFML/Graphics.hpp>
#include <Swoosh/Game.h>

#include "utils_graphics.hpp"

class Button
{
public:
    //Construct a button with a solid color
    Button( sf::Vector2f iaf32_size, sf::Vector2f iaf32_position, sf::Color ie_color ) :
        gx_hovering(false), gx_click_allowed(false), gx_clicked(false), gaf32_size(iaf32_size), gaf32_position(iaf32_position), ge_color(ie_color), ge_color_hover(ie_color), ge_color_click(ie_color)
    {
		this->init_vars();

		//Create a rectangle color solid and save it as sprite
		if (Utils::create_sprite_solid_color( this->gcl_sprite, iaf32_size, ie_color ) == true)
		{
			//FAIL
			std::cerr << "Button Constructor: Failed to create background sprite\n";
		}

        this->gpcl_text = nullptr;

        return;
    }

    //Construct an invisible button

	//Hover logic
	//Click logic: the button must unpressed, to allow registering clicks
    void update(sf::RenderWindow& window, float f32_elapsed)
    {

		if (this->gf32_cooldown_timer == 0.0f)
		{
			//Do nothing
		}
		//Apply the cooldown
		else if (this->gf32_cooldown_timer > f32_elapsed)
		{
			this->gf32_cooldown_timer -= f32_elapsed;
		}
		else
		{
			std::cout << this->gs_text  << "Cooldown expired, action ready!\n";
			this->gf32_cooldown_timer = 0.0f;
		}

		//Actions are in cooldown
		if (this->gf32_cooldown_timer > 0.0f)
		{
			this->gx_hovering = false;
			this->gx_click_allowed = false;
			this->gx_clicked = false;
		}
		//Mouse is not within the bounds of the button
		else if (isMouseHovering(*this, window) == false)
		{
			this->gx_hovering = false;
			this->gx_click_allowed = false;
			this->gx_clicked = false;
		}
		//Mouse is within the bounds of the button
		else
		{
			this->gx_hovering = true;
			//Capture the mouse button
			bool x_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			//Must first see the button unclicked
			if ((this->gx_click_allowed == false) && (x_click == false))
			{
				this->gx_click_allowed = true;
				if (this->cx_debug_enabled == true)
					std::cout << this->gs_text  << " | Armed\n";
			}
			//Click already allowed
			else if ((this->gx_click_allowed == true) && (x_click == false))
			{
				//Do nothing
			}
			//Button was already pressed before going inside the button
			else if ((this->gx_click_allowed == false) && (x_click == true))
			{
				//Do nothing
			}
			//Button was already pressed before going inside the button
			else if ((this->gx_click_allowed == true) && (x_click == true))
			{
				//Trigger the cooldown
				this->set_cooldown();
				//Register the click
				this->gx_clicked = true;
				//Disallow next click
				this->gx_click_allowed = false;
				std::cout << this->gs_text << "Click\n";
			}
			//Can never happen
			else
			{
				//Do nothing
			}
		}

        return;
    }

    void draw(sf::RenderTexture& surface )
    {
        if (this->gx_hovering)
        {
            gcl_sprite.setColor(this->ge_color_hover);
        }
        else
        {
            gcl_sprite.setColor(this->ge_color);
        }

        gcl_sprite.setPosition(this->gaf32_position);
        gcl_sprite.setOrigin(gcl_sprite.getGlobalBounds().width / 2.0f, gcl_sprite.getGlobalBounds().height / 2.0f);
        surface.draw(gcl_sprite);
        //If there is text to draw
        if (this->gpcl_text != nullptr)
        {
            this->gpcl_text->setString(this->gs_text);
            this->gpcl_text->setOrigin(this->gpcl_text->getGlobalBounds().width / 2.0f, this->gpcl_text->getGlobalBounds().height / 2.0f);
            this->gpcl_text->setPosition(this->gaf32_position -sf::Vector2f(0.0f, this->gpcl_text->getGlobalBounds().height / 2.0f) );
            surface.draw(*this->gpcl_text);
        }
    }

    void set_text( sf::Text &ircl_text, std::string is_text )
    {
        //reference to SFML text class to use to render the text
        this->gpcl_text = &ircl_text;
        //Text
        this->gs_text = is_text;
    }

    bool set_color_hover( sf::Color ie_color )
    {
        this->ge_color_hover = ie_color;
        return false;
    }

    bool set_color_click( sf::Color ie_color )
    {
        this->ge_color_click = ie_color;
        return false;
    }

    bool set_position( sf::Vector2f iaf32_position )
    {
        this->gaf32_position = iaf32_position;
        return false;
    }

    std::string &get_text()
    {
        return this->gs_text;
    }

    bool is_clicked()
    {
        return this->gx_clicked;
    }

    bool is_hover()
    {
        return this->gx_hovering;
    }

    /*
    //ix_click_enabled true = enable click action
    bool set_click_enabled( bool ix_click_enabled )
    {
		this->gx_click_enabled = ix_click_enabled;
		return false;
    }
    */

    //Trigger the cooldown
    bool set_cooldown()
    {
		if (this->cx_debug_enabled == true)
			std::cout << this->gs_text << " | Action in cooldown...\n";

		this->gf32_cooldown_timer = this->cf32_cooldown_time;
		return false;
    }
private:

    //TODO: create asset class, that loads sprites and textures in a standard vector
    //Sprites
    //std::vector<sf::Sprite> gacl_sprite;

    //Initialize class variables
    bool init_vars()
    {
		this->gf32_cooldown_timer = 0.0f;
		return false;
    }

    const bool isMouseHovering(Button& btn, sf::RenderWindow& window)
    {
        sf::Sprite& gcl_sprite = btn.gcl_sprite;
        sf::Vector2i mousei = sf::Mouse::getPosition(window);
        sf::Vector2f mouse = window.mapPixelToCoords(mousei);
        sf::FloatRect bounds = gcl_sprite.getGlobalBounds();

        return (mouse.x >= bounds.left && mouse.x <= bounds.left + bounds.width && mouse.y >= bounds.top && mouse.y <= bounds.top + bounds.height);
    }

    static const constexpr bool cx_debug_enabled = true;
    //true = mouse is hovering over the button
    bool gx_hovering;
    //true = mouse has clicked the button
    bool gx_click_allowed;
    bool gx_clicked;
    //Cooldown must be expired to allow actions to occour
    float gf32_cooldown_timer;
    //Default cooldown in seconds to allow actions to occour
    static const constexpr float cf32_cooldown_time = 0.2f;
    //Size of the button in pixels
    sf::Vector2f gaf32_size;
    //Position of the button on the screen
    sf::Vector2f gaf32_position;

    sf::Sprite gcl_sprite;
    //Color of the button at rest
    sf::Color ge_color;
    //Color of the button when hovering
    sf::Color ge_color_hover;
    //Color of the button when clicked
    sf::Color ge_color_click;

    //SFML text to use to draw the text with the correct font and colors
    sf::Text *gpcl_text;
    //Text of the button
    std::string gs_text;
};
