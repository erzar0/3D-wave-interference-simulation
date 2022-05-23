#define SFML_STATIC
#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Project{
public:
    static Project& init();
    Project();
    virtual ~Project();

    Project(Project& p) = delete;
    void operator=(Project& p) = delete;


private:

    sf::RenderWindow* m_window{};
    sf::Event m_sfEvent{};
    sf::Clock m_deltaClock{};
    void run();
    void initWindow();
    void update();
    void updateEvents();
    void render();
};
 /*{
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

   
}*/
