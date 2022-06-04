#pragma once
#define SFML_STATIC
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Mesh.h"
#include "Enums.h"



class Project{
public:
    static Project& init();
    friend class GUI;
    static float m_options[14];

private:
    Project();
    virtual ~Project();
    Project(Project& p) = delete;
    void operator=(Project& p) = delete;

    sf::RenderWindow* m_window{};
    sf::Event m_sfEvent{};
    sf::Clock m_deltaClock{};
    sf::Time m_dt{};
    Mesh m_mesh{};
    void run();
    void initWindow();

    void render();
    void renderDebugInfo();

    void update();
    void updateEvents();
    void updateDt();
};
