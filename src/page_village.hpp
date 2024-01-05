
#pragma once

#include <iostream>
//#include <math>

#include <SFML/Graphics.hpp>

#include "Swoosh/Game.h"

#include "gui_button.hpp"

#include "utils_graphics.hpp"

#include "asset_manager.hpp"

#include "village_simulator.hpp"

#include "coordinate_generator.hpp"

//page_transition.cpp
//Handles transition to remove include dependencies on pages
extern bool page_push( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name );

class Page_village : public swoosh::Activity
{
public:

    Page_village(swoosh::ActivityController& icl_controller) : swoosh::Activity(&icl_controller)
    {
        gx_focus = true;

        this->setView(icl_controller.getVirtualWindowSize());

        this->init_simulation();

        //this->init_gui();


        if (this->load_assets())
        {
            std::cerr << "ERR: failed to load assets...";
        }

        // Create the TIME button
        Button cl_gui_button_about( sf::Vector2f(100, 50), sf::Vector2f(700, 100), sf::Color::White );
        cl_gui_button_about.set_text( this->gs_text_default, this->cs_button_text_about );
        cl_gui_button_about.set_color_hover(sf::Color::Green);
        cl_gui_button_about.set_color_click(sf::Color::Blue);
		this->gacl_button.push_back(cl_gui_button_about);

		// Create the WOOD button
        Button cl_gui_button_wood( sf::Vector2f(100, 50), sf::Vector2f(700, 150), sf::Color::White );
        cl_gui_button_wood.set_text( this->gs_text_default, this->cs_button_text_about );
        cl_gui_button_wood.set_color_hover(sf::Color::Green);
        cl_gui_button_wood.set_color_click(sf::Color::Blue);
		this->gacl_button.push_back(cl_gui_button_wood);

        // Create the EXIT button
        Button cl_gui_button_exit( sf::Vector2f(100, 50), sf::Vector2f(700, 500), sf::Color::White );
        cl_gui_button_exit.set_text( this->gs_text_default, this->cs_button_text_exit );
        cl_gui_button_exit.set_color_hover(sf::Color::Green);
        cl_gui_button_exit.set_color_click(sf::Color::Blue);
        this->gacl_button.push_back(cl_gui_button_exit);
        return;
    }

    ~Page_village()
    {
        if(unload_assets())
        {
            std::cerr << "ERR: " << __LINE__ << "failed to unload assets\n";
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
		float f32_simulated_years_elapsed = if64_elapsed* Constant::Simulation::cf32_years_per_second;
		//Absolute time of the simulation
		this->gf32_year += f32_simulated_years_elapsed;

		this->gcl_village_simulator.simulate( f32_simulated_years_elapsed, 1.0f );

		if (this->cx_debug_tick_enabled == true)
			std::cout << "Page: Main Menu | onUpdate called: " << if64_elapsed << std::endl;

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
            }
        }

        return;
    }

    //Triggered when:
    //- Activity controller draw method is called in the main loop
    void onDraw(sf::RenderTexture& icl_surface) override
    {
		if (this->cx_debug_tick_enabled == true)
			std::cout << "Page: Main Menu | onUpdate called" << std::endl;

		this->gcl_asset_manager.draw_asset( icl_surface, Constant::Page_village::cs_resource_background );

		Village_simulator::Land st_land = this->gcl_village_simulator.get_land();
		//Draw the integer woods
		for (int n = 0; n < st_land.n_wood;n++)
		{
			this->gcl_asset_manager.draw_asset( icl_surface, Constant::Page_village::cs_resource_tree, sf::Vector2f(0.0f+n*20.0f,100.0f), sf::Vector2f(30.0f,30.0f), 0.4f  );
		}

		//Time on first button
		this->gacl_button[0].set_text(this->gs_text_default, std::to_string(this->gf32_year) );
		//Woods on the second button
		this->gacl_button[1].set_text(this->gs_text_default, std::to_string(st_land.n_wood) );

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
		x_ret |= this->gcl_asset_manager.load_from_file( Constant::Page_village::cs_resource_background );
		x_ret |= this->gcl_asset_manager.load_from_file( Constant::Page_village::cs_resource_tree );

        x_ret |= load_text(this->gs_text_default);

        return x_ret;
    }

	bool unload_assets( void )
	{
		return false;
	}

	bool init_simulation( void )
	{
		this->gf32_year = 0.0f;

		this->gcl_village_simulator.set_land( Constant::Simulation::cn_land_total, 10, 0, 0 );



		return false; //OK
	}

	//Takes care of drawing the village
	bool draw_village()
	{
		//I divide plots in a grid 10x10
		//I want plots to be drawn consistently
		//BUilding are drawn spirally from center going out

		//Spiral coordinates
		//Start from 5.5, 5.5
		//Fill clockwise

		//First buildings
		//Then fields
		//Then undeveloped
		//Then woods

		//Get village plots
		Village_simulator::Land st_land = this->gcl_village_simulator.get_land();
		//Compute integer and fraction of fields
		int n_builts = st_land.n_built;
		float n_builts_fraction = st_land.n_built -n_built;
		int n_fields = st_land.n_built;
		float n_fields_fraction = st_land.n_field -n_field;

		//Scan the fields
		for (int n_row = 0;n_row < Constant::Simulation::cn_land_rows;n_row++)
		{
			for (int n_col = 0;n_col < Constant::Simulation::cn_land_rows;n_col++)
			{
				if (n_builds

			}
		}



		return false;
	}


	static const constexpr bool cx_debug_enabled = true;
	static const constexpr bool cx_debug_tick_enabled = false;

    static const constexpr char *cs_button_text_about = "About";
    static const constexpr char *cs_button_text_exit = "Exit";

    sf::Font gcl_font;

    sf::Text gs_text_default;

    //Buttons inside the scene
    std::vector<Button> gacl_button;

    bool gx_focus;
	//Handle loading of image files
    Asset_manager gcl_asset_manager;
	//Handles the number simulation
    Village_simulator gcl_village_simulator;
	//Generate spiral coordinates for the drawing of the engine
	Utils::Coordinate_generator gcl_coordinate_generator;

    float gf32_year;
};
