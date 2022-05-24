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

private:

    Project();
    virtual ~Project();
    Project(Project& p) = delete;
    void operator=(Project& p) = delete;

    sf::RenderWindow* m_window{};
    sf::Event m_sfEvent{};
    sf::Clock m_deltaClock{};
    void run();
    void initWindow();
    void update();
    void updateEvents();
    void render();
};
