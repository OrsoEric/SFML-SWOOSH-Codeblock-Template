#include <iostream>

#include <SFML/window.hpp>

#include <Swoosh/ActivityController.h>

//#include <Segues/ZoomOut.h>

#include "scene.hpp"

bool init_window( sf::RenderWindow &icl_window )
{
    if (icl_window.isOpen())
        return false; // Return false if the window is already initialized

    icl_window.create(sf::VideoMode(800, 600), "My Window");

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

int main()
{
    //Create window
    sf::RenderWindow cl_window;
    if (init_window(cl_window))
    {
        std::cerr << "ERR: Failed to initialize window\n";
        return -1;
    }

    // Create an ActivityController with the current window as our target to draw to
    swoosh::ActivityController cl_activity_controller(cl_window);
    if (init_activity_controller( cl_activity_controller ))
    {
        std::cerr << "ERR: Failed to initialize ActivityController\n";
        return -1;
    }

    cl_activity_controller.push<Scene>();

    //cl_activity_controller.push<segue<ZoomOut>::to<Scene>>();
    /*
    sf::Text s_time_elapsed;
    s_time_elapsed.setString("0.0");
    text.setCharacterSize(24); // in pixels, not points!
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    */

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
            // "close requested" cl_event: we close the cl_window
            if (cl_event.type == sf::Event::Closed)
                cl_window.close();
        }

        cl_activity_controller.update( f32_elapsed );

        cl_window.clear();

        cl_activity_controller.draw();

        //cl_window.draw(text);

        cl_window.display();

        f32_elapsed = static_cast<float>(cl_clock.getElapsedTime().asSeconds());
    }

    return 0;
}
