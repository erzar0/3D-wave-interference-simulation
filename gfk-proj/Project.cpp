#include "Project.h"

void Project::initWindow()
{
	m_window = new sf::RenderWindow(sf::VideoMode(640, 480), "3DWaveInterference");
    ImGui::SFML::Init(*m_window);
}

Project::Project()
{
    initWindow();
    run();
}

Project::~Project()
{
	delete m_window;
    ImGui::SFML::Shutdown();
}


Project& Project::init()
{
    static Project instance;
    return instance;
}


void Project::updateEvents()
{
    while (m_window->pollEvent(m_sfEvent)) 
    {
        ImGui::SFML::ProcessEvent(*m_window, m_sfEvent);

        if (m_sfEvent.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

void Project::render()
{
    sf::CircleShape shape(100.f, 10);
    shape.setFillColor(sf::Color::Green);
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();


    m_window->clear();
    m_window->draw(shape);
    ImGui::SFML::Render(*m_window);
    m_window->display();
}
void Project::run()
{
    while (m_window->isOpen())
    {
        update();
        ImGui::SFML::Update(*m_window, m_deltaClock.restart());
        render();
    }

}

void Project::update()
{
    updateEvents();
}
