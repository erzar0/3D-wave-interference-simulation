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
    static float m_renderOptions[10];

private:
    Project();
    virtual ~Project();
    Project(Project& p) = delete;
    void operator=(Project& p) = delete;

    sf::RenderWindow* m_window{};
    sf::Event m_sfEvent{};
    sf::Clock m_deltaClock{};
    sf::Time m_dt{};

    int m_meshDensity{ 250 };
    Mesh* m_meshPtr { new Mesh(m_meshDensity) };
    Mesh& m_mesh { *m_meshPtr };
    unsigned m_isNewMesh{ 2 };

    void run();

    void initWindow();
    void initMesh();

    void render();
    void renderMenu();

    void update();
    void updateEvents();
    void updateDt();

    bool stopped{ false };
};
