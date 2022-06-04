#include "Project.h"
#include "Utils.h"
#include "Matvec.h"
#include <iostream>
#include <cmath>
#include <string>

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

void Project::update()
{
    updateDt();
    updateEvents();
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
    ImGui::SFML::Update(*m_window, m_dt);
}

void Project::updateDt()
{
    m_dt = m_deltaClock.restart();
}

void Project::render()
{
    sf::CircleShape shape(100.f, 10);
    shape.setFillColor(sf::Color::Green);
    renderDebugInfo();
    m_window->clear();
    //sf::Sprite sprite(m_mesh.getTexture(m_window->getSize().x, m_window->getSize().y), );
    m_window->draw(shape);
    m_mesh.renderOnWindow(m_window);
    ImGui::SFML::Render(*m_window);
    m_window->display();
}

void Project::renderDebugInfo()
{
    double updatesPerSec = 5;
    double dtAsSeconds = m_dt.asMicroseconds() / std::pow(10, 6);

    static std::string fps{ 0 };
    static std::string frameTime{ 0 };
    static double timeElapsed{ 0 };
    float amp = 0.5, freq = 0.5;
    timeElapsed += dtAsSeconds;

    if(timeElapsed >= 1/updatesPerSec)
    { 
        timeElapsed = 0;
		fps = std::string("FPS: ") + std::to_string(static_cast<int>(1.0/dtAsSeconds));
		frameTime = std::string("Frametime: ") + utils::to_string_with_precision<double>(dtAsSeconds*1000.0, 2) + "ms";
    }
	ImGui::Begin("Menu");
	ImGui::Text(fps.c_str());
	ImGui::Text(frameTime.c_str());
    ImGui::SliderFloat("Amplitude", &amp, 0.0f, 1.0f);
    ImGui::SliderFloat("Frequency", &freq, 0.0f, 1.0f);    
    for(int i = 0; i < 3; i++)
        ImGui::Spacing();
    ImGui::Button("Save",ImVec2(80.0f,0.0f));
    ImGui::SameLine();
    ImGui::Button("Copy", ImVec2(80.0f, 0.0f));
    ImGui::SameLine();
    ImGui::Button("Stop",ImVec2(80.0f,0.0f));

	ImGui::End();
}
void Project::run()
{
    while (m_window->isOpen())
    {
        update();
        render();
    }

}

