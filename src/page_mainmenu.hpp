#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Swoosh/Game.h"

#include "gui_button.hpp"

#include "utils_graphics.hpp"

#include "asset_manager.hpp"

#include "constants.hpp"

//page_transition.cpp
//Handles transition to remove include dependencies on pages
extern bool page_push( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name );

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

        //Create the START Button
        Button cl_gui_button_start( sf::Vector2f(100, 50), sf::Vector2f(400, 200), sf::Color::White );
        cl_gui_button_start.set_text( this->gs_text_default, this->cs_button_text_village );
        cl_gui_button_start.set_color_hover(sf::Color::Green);
        cl_gui_button_start.set_color_click(sf::Color::Blue);
		this->gacl_button.push_back(cl_gui_button_start);

        // Create the EXIT button
        Button cl_gui_button_exit( sf::Vector2f(100, 50), sf::Vector2f(400, 300), sf::Color::White );
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

	//Triggered when:
    //- Activity is pushed inside the Activity_controller
	void onStart() override
    {
        if (this->cx_debug_enabled == true)
			std::cout << "Page: Main Menu | onStart called" << std::endl;

		this->trigger_gui_cooldowns();
        return;
    }

	//Triggered when:
	//- Activity is popped from Activity_controller
	void onEnd() override
    {
		if (this->cx_debug_enabled == true)
			std::cout << "page Main Menu | OnEnd called" << std::endl;
        return;
    }

    //Triggered when:
    //- another Activity is pushed inside the activity controller, pushing this activity down the priority
    void onLeave() override
    {
        if (this->cx_debug_enabled == true)
			std::cout << "Page: Main Menu | onLeave called" << std::endl;
        gx_focus = false;
        return;
    }

	//Triggered when:
    //- Activity resumes after onLeave, e.g. when the activity that pushed this activity down was popped, making this the highest priority activity again
    void onResume() override
    {
		if (this->cx_debug_enabled == true)
			std::cout << "Page: Main Menu | onResume called" << std::endl;
		this->trigger_gui_cooldowns();
        gx_focus = true;
        return;
    }

    void onEnter() override
    {
        if (this->cx_debug_enabled == true)
			std::cout << "Page: Main Menu | onEnter called" << std::endl;
		this->trigger_gui_cooldowns();
		return;
    }

    void onExit() override
    {
        if (this->cx_debug_enabled == true)
			std::cout << "Page: Main Menu | onExit called" << std::endl;
		return;
    }

    //Triggered when:
    //- Activity controller update method is called in the main loop
    void onUpdate(double if64_elapsed) override
    {
		if (this->cx_debug_tick_enabled == true)
			std::cout << "Page: Main Menu | onUpdate called: " << if64_elapsed << std::endl;

		//For buttons
        for (auto& cl_gui_button : gacl_button)
        {
            cl_gui_button.update(getController().getWindow(), if64_elapsed);
            //If this button has been clicked
            if (cl_gui_button.is_clicked())
            {
                //If this button is the exit button
                if (this->cs_button_text_exit == cl_gui_button.get_text())
                {
                    //Pop this scene
                    this->getController().pop();
                }
                else if (this->cs_button_text_village == cl_gui_button.get_text())
                {
                    if (page_push( this->getController(), Constant::cs_page_village ) == true)
					{
						std::cerr << "ERR: " << __LINE__ << "ERR: Unable to push page...\n";
					}
                }
            }
        }	//For buttons

        return;
    }

    //Triggered when:
    //- Activity controller draw method is called in the main loop
    void onDraw(sf::RenderTexture& icl_surface) override
    {
		if (this->cx_debug_tick_enabled == true)
			std::cout << "Page: Main Menu | onUpdate called" << std::endl;

        this->gcl_asset_manager.draw_asset( icl_surface, Constant::Page_main_menu::cs_resource_background );

        for (auto& cl_gui_button : gacl_button)
        {
            cl_gui_button.draw( icl_surface );
        }

        return;
    }

protected:

private:

	bool trigger_gui_cooldowns()
	{
		for (auto& cl_gui_button : gacl_button)
        {
            cl_gui_button.set_cooldown();
        }
		return false;
	}

    bool load_text( sf::Text &irs_text )
    {
        if (!this->gcl_font.loadFromFile(Constant::cs_font)) // Check if the font is loaded correctly
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
		x_ret |= this->gcl_asset_manager.load_from_file( Constant::Page_main_menu::cs_resource_background );

        x_ret |= load_text(this->gs_text_default);

        return x_ret;
    }

	bool unload_assets( void )
	{
		return false;
	}

	static const constexpr bool cx_debug_enabled = true;
	static const constexpr bool cx_debug_tick_enabled = false;

    static const constexpr char *cs_button_text_village = "Village";
    static const constexpr char *cs_button_text_exit = "Exit";

    sf::Font gcl_font;

    sf::Text gs_text_default;

    //Texture and sprite for the background
    //sf::Texture gcl_texture_background;
    //sf::Sprite gcl_sprite_background;

    //Buttons inside the scene
    std::vector<Button> gacl_button;

    bool gx_focus;
	//Handle loading of image files
    Asset_manager gcl_asset_manager;
};
