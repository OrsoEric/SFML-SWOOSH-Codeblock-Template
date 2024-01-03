#include <iostream>

#include <SFML/Graphics.hpp>

#include "Swoosh/Game.h"

#include "gui_button.hpp"

#include "utils_graphics.hpp"

class Page_mainmenu : public swoosh::Activity
{
public:

    Page_mainmenu(swoosh::ActivityController& icl_controller) : swoosh::Activity(&icl_controller)
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

    ~Page_mainmenu()
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

            /*
            if (b.isClicked && inFocus)
            {
                selectFX.play();

                if (b.text == PLAY_OPTION)
                {
                    getController().push<segue<DreamCustom<50>, sec<3>>::to<GameplayPage_mainmenu>>(savefile);
                    fadeMusic = true;
                }
                else if (b.text == SCORE_OPTION)
                {
                    using segue = segue<BlurFadeIn, sec<2>>;
                    using intent = segue::to<HiScorePage_mainmenu>;

                    getController().push<intent>(savefile);
                }
                else if (b.text == ABOUT_OPTION)
                {
                    getController().push<segue<VerticalSlice, sec<2>>::to<AboutPage_mainmenu>>();
                }
            }
            */
        }

        return;
    }

    void onDraw(sf::RenderTexture& icl_surface) override
    {
        /*
        // Get the current size of the window
        sf::Vector2u an_texture_size = icl_surface.getSize();

        // Get the size of the sprite
        sf::Vector2u spriteSize = gcl_sprite_background.getTexture()->getSize();

        // Calculate the scale factors
        float scaleX = static_cast<float>(an_texture_size.x) / spriteSize.x;
        float scaleY = static_cast<float>(an_texture_size.y) / spriteSize.y;


        // Set the scale of the sprite
        gcl_sprite_background.setScale(scaleX, scaleY);
        std::cout << "onDraw called, window size: " << an_texture_size.x << " | " << an_texture_size.y << std::endl;
        */
        //sf::RenderWindow& window = getController().getWindow();

        icl_surface.draw(gcl_sprite_background);

        /*
        swoosh::game::setOrigin( this->gs_text_default, 0.5, 0.5 );
        this->gs_text_default.setPosition(sf::Vector2f(100, 100));
        icl_surface.draw(this->gs_text_default);
        */

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
		x_ret |= Utils::create_sprite_from_file(this->gcl_sprite_background, "resources/black_rose_800_600.jpg");

        x_ret |= load_text(this->gs_text_default);

        return x_ret;
    }

	bool unload_assets( void )
	{
		return false;
	}

    static const constexpr char *cs_button_text_exit = "Exit";

    sf::Font gcl_font;

    sf::Text gs_text_default;

    //Texture and sprite for the background
    sf::Sprite gcl_sprite_background;

    //Buttons inside the scene
    std::vector<Button> gacl_button;

    bool gx_focus;

};
