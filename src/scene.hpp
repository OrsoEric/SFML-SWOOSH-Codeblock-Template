#include <iostream>

#include <SFML/Graphics.hpp>

#include "Swoosh/Game.h"

class Scene : public swoosh::Activity
{
public:

    Scene(swoosh::ActivityController& icl_controller) : swoosh::Activity(&icl_controller)
    {
        gx_focus = true;

        //this->setView(icl_controller.getVirtualWindowSize());

        if (load_assets())
        {
            std::cerr << "ERR: failed to load assets...";
        }
        return;
    }

    ~Scene()
    {
        if(unload_assets())
        {
            std::cerr << "ERR: failed to unload assets\n";
        }
        return;
    }

    void onStart() override
    {
        std::cout << "OnStart called" << std::endl;
        return;
    }

    void onUpdate(double f64_elapsed) override
    {
        std::cout << "onUpdate called: " << f64_elapsed << std::endl;
        return;
    }

    void onLeave() override
    {
        std::cout << "OnLeave called" << std::endl;
        gx_focus = false;
    }

    void onExit() override
    {
        std::cout << "OnExit called" << std::endl;
    }

    void onEnter() override
    {
        std::cout << "OnEnter called" << std::endl;

    }

    void onResume() override
    {
        std::cout << "OnLeave called" << std::endl;
        gx_focus = true;
    }

    void onDraw(sf::RenderTexture& icl_surface) override
    {
        std::cout << "onDraw called" << std::endl;
        //sf::RenderWindow& window = getController().getWindow();

        icl_surface.draw(gcl_sprite_background);

        swoosh::game::setOrigin( this->gs_timer, 0.5, 0.5 );
        this->gs_timer.setPosition(sf::Vector2f(100, 100));
        icl_surface.draw(this->gs_timer);

        return;
    }

    void onEnd() override
    {
        std::cout << "OnEnd called" << std::endl;
        return;
    }

protected:

private:

    sf::Texture* load_texture(const std::string& path)
    {
        sf::Texture* cl_texture = new sf::Texture();
        if (!cl_texture->loadFromFile(path))
        {
            delete cl_texture;
            cl_texture = nullptr;
            std::cerr << "ERR: loading texture: " << path << "\n";
        }

        return cl_texture;
    }

    bool load_text( sf::Text &irs_text )
    {
        if (!this->gcl_font.loadFromFile("resources/manual.ttf")) // Check if the font is loaded correctly
        {
            std::cerr << "ERR: Failed to load font\n";
            return true; // Return true if the font failed to load
        }

        irs_text.setFont(this->gcl_font);
        irs_text.setFillColor(sf::Color::Red);
        irs_text.setString("Shaka");

        if (irs_text.getString().isEmpty()) // Check if the text is initialized correctly
        {
            std::cerr << "ERR: Failed to initialize text\n";
            return true; // Return true if the text failed to initialize
        }

        return false; // Return false if the font and text were successfully loaded and initialized
    }

    bool load_assets( void )
    {
        bool x_ret = false;
        this->gcl_texture = load_texture("resources/black_rose_800_600.jpg");
        this->gcl_sprite_background = sf::Sprite(*this->gcl_texture);

        x_ret |= load_text(this->gs_timer);

        return x_ret;
    }

    bool unload_assets( void )
    {
        delete gcl_texture;
        return false;
    }

    sf::Font gcl_font;

    sf::Text gs_timer;

    //Texture and sprite for the background
    sf::Texture* gcl_texture;
    sf::Sprite gcl_sprite_background;

    bool gx_focus;

};
