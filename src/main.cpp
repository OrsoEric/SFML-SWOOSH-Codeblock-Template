#include <iostream>

#include <SFML/window.hpp>
#include <SFML/Graphics.hpp>

#include <Swoosh/ActivityController.h>

#include "constants.hpp"

//TODO:
//I can make a GUI class from the asset manager
//The core is handle text, image, clicks and name of controls


//utils.cpp
std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect);

//page_transition.cpp
//Handles transition to remove include dependencies on pages
extern bool page_push( swoosh::ActivityController& ircl_activity_controller, std::string is_page_name );

bool init_window( sf::RenderWindow &icl_window )
{
    if (icl_window.isOpen())
        return false; // Return false if the window is already initialized

    icl_window.create(sf::VideoMode(Constant::Window::cn_width, Constant::Window::cn_height), "My Window");

    if (!icl_window.isOpen())
        return true; // Return true if the window failed to open

    icl_window.setFramerateLimit(60);
    icl_window.setVerticalSyncEnabled(true);
    icl_window.setMouseCursorVisible(false);

    return false; // Return false if the window was successfully initialized
}

bool init_activity_controller( swoosh::ActivityController &icl_activity_controller )
{
    icl_activity_controller.optimizeForPerformance(swoosh::quality::realtime);

    return false;
}

bool create_texture_triangle( sf::RenderTexture &ircl_render_texture, float if32_size )
{
    sf::CircleShape triangle(if32_size/2.0, 3);
    triangle.setOutlineColor(sf::Color::Red);

    if (!ircl_render_texture.create(if32_size, if32_size))
        return true;  // error
    ircl_render_texture.draw(triangle);
    return false;
}

int main()
{
    //Create window
    sf::RenderWindow cl_window;
    if (init_window(cl_window))
    {
        std::cerr << "ERR: Failed to initialize window\n";
        return -1;
    }
    //Crate a texture for the cursor
    sf::RenderTexture renderTexture;
    create_texture_triangle(renderTexture, 30 );
    //Create cursor
    sf::Sprite cl_cursor;
    cl_cursor.setTexture(renderTexture.getTexture());

    // Create an ActivityController with the current window as our target to draw to
    swoosh::ActivityController cl_activity_controller(cl_window);
    if (init_activity_controller( cl_activity_controller ))
    {
        std::cerr << "ERR: Failed to initialize ActivityController\n";
        return -1;
    }

    if (page_push( cl_activity_controller, Constant::cs_page_main_menu ) == true)
    {
		std::cerr << "ERR: " << __LINE__  << " | Unable to push page...\n";
		return -1;
    }

    //Timekeeping
    sf::Clock cl_clock;
    float f32_elapsed = 0.0f;

    // run the program as long as the cl_window is open
    while (cl_window.isOpen())
    {
        cl_clock.restart();
        // check all the window's cl_events that were triggered since the last iteration of the loop
        sf::Event cl_event;
        while (cl_window.pollEvent(cl_event))
        {
            if (cl_event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect st_visible_area(0, 0, cl_event.size.width, cl_event.size.height);
                cl_window.setView(sf::View(st_visible_area));
                std::cout << "EVENT RESIZE: " << st_visible_area << "\n";
            }
            // "close requested" cl_event: we close the cl_window
            if (cl_event.type == sf::Event::Closed)
            {
                std::cout << "CLOSE: User requested close\n";
                cl_window.close();
            }
        }

        cl_activity_controller.update( f32_elapsed );
        //If there are no activities on the stack
        if (cl_activity_controller.getStackSize() <= 0)
        {
            std::cout << "CLOSE: No activities left...\n";
            cl_window.close();
        }

        cl_window.clear();

        cl_activity_controller.draw();

        sf::Vector2f mousepos = cl_window.mapPixelToCoords(sf::Mouse::getPosition(cl_window));
        cl_cursor.setPosition(mousepos);

        // Draw the mouse cursor over everything else
        cl_window.draw(cl_cursor);

        cl_window.display();

        f32_elapsed = static_cast<float>(cl_clock.getElapsedTime().asSeconds());
    }

    return 0;
}
