#include <SFML/Graphics.hpp>
#include <Swoosh/Game.h>

#include "utils_graphics.hpp"

class Button
{
public:
    //Construct a button with a solid color
    Button( sf::Vector2f iaf32_size, sf::Vector2f iaf32_position, sf::Color ie_color ) :
        gx_clicked(false), gx_hovering(false), gaf32_size(iaf32_size), gaf32_position(iaf32_position), ge_color(ie_color), ge_color_hover(ie_color), ge_color_click(ie_color)
    {
		//Create a rectangle color solid and save it as sprite
		if (Utils::create_sprite_solid_color( this->gcl_sprite, iaf32_size, ie_color ) == true)
		{
			//FAIL
			std::cerr << "Button Constructor: Failed to create background sprite\n";
		}

        this->gpcl_text = nullptr;

        return;
    }

    void update(sf::RenderWindow& window)
    {
        if (isMouseHovering(*this, window))
        {
            gx_hovering = true;
            gx_clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        }
        else
        {
            gx_clicked = gx_hovering = false;
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
private:
    //true = mouse has clicked the button
    bool gx_clicked;
    //true = mouse is hovering over the button
    bool gx_hovering;
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

    //TODO: create asset class, that loads sprites and textures in a standard vector
    //Sprites
    //std::vector<sf::Sprite> gacl_sprite;

    const bool isMouseHovering(Button& btn, sf::RenderWindow& window)
    {
        sf::Sprite& gcl_sprite = btn.gcl_sprite;
        sf::Vector2i mousei = sf::Mouse::getPosition(window);
        sf::Vector2f mouse = window.mapPixelToCoords(mousei);
        sf::FloatRect bounds = gcl_sprite.getGlobalBounds();

        return (mouse.x >= bounds.left && mouse.x <= bounds.left + bounds.width && mouse.y >= bounds.top && mouse.y <= bounds.top + bounds.height);
    }
};


