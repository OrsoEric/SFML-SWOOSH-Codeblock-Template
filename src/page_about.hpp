#include <iostream>

#include <SFML/Graphics.hpp>

#include "Swoosh/Game.h"

#include "gui_button.hpp"

class Page_about : public swoosh::Activity
{
public:

    Page_about(swoosh::ActivityController& icl_controller) : swoosh::Activity(&icl_controller)
    {
        gx_focus = true;

        this->setView(icl_controller.getVirtualWindowSize());

        if (this->load_assets())
        {
            std::cerr << "ERR: failed to load assets...";
        }

        // Create the EXIT button
        Button cl_gui_button_exit( sf::Vector2f(100, 100), sf::Vector2f(400, 300), sf::Color::White );
        cl_gui_button_exit.set_text( this->gs_text_default, this->cs_button_text_exit );
        cl_gui_button_exit.set_color_hover(sf::Color::Green);
        cl_gui_button_exit.set_color_click(sf::Color::Blue);

        this->gacl_button.push_back(cl_gui_button_exit);
        return;
    }

    ~Page_about()
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

    void onUpdate(double f64_elapsed) override
    {
        std::cout << "onUpdate called: " << f64_elapsed << std::endl;
        for (auto& cl_gui_button : gacl_button)
        {
            cl_gui_button.update(getController().getWindow());
            //If this button has been clicked
            if (cl_gui_button.is_clicked())
            {
                //If this button is the exit button
                if (this->cs_button_text_exit == cl_gui_button.get_text())
                {
                    //Pop this scene
                    this->getController().pop();
                }
            }
        }

        return;
    }

    void onDraw(sf::RenderTexture& icl_surface) override
    {

        for (auto& cl_gui_button : gacl_button)
        {
            cl_gui_button.draw( icl_surface );
        }

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

        x_ret |= load_text(this->gs_text_default);

        return x_ret;
    }

	bool unload_assets( void )
	{
		delete gcl_texture;
		return false;
	}

    static const constexpr char *cs_button_text_exit = "Exit";

    sf::Font gcl_font;

    sf::Text gs_text_default;

    //Buttons inside the scene
    std::vector<Button> gacl_button;

    bool gx_focus;

};

