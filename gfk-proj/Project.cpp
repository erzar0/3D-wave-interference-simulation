#include "Project.h"
#include "Utils.h"
#include "Matvec.h"
#include <iostream>
#include <cmath>
#include <string>

float Project::m_options[14]{};

void Project::initWindow()
{
	m_window = new sf::RenderWindow(sf::VideoMode(1440, 1080), "3DWaveInterference");
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
    m_mesh.updateTime(m_dt);
}

void Project::render()
{
    renderDebugInfo();

    m_window->clear();
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
    //enum 
    if(ImGui::SliderFloat("Amplitude", m_options, -1.0, 1.0)){
    }
    if(ImGui::SliderFloat("Frequency", m_options+1, -1.0, 1.0)){
    }
    if(ImGui::SliderFloat("Rotate X", m_options+2, -3.14f, 3.14f)){
        m_mesh.getTransMat().rotateX(m_options[OPT::ROTX]);
    }
    if(ImGui::SliderFloat("Rotate Y", m_options+3, -3.14f, 3.14f)){
        m_mesh.getTransMat().rotateY(m_options[OPT::ROTY]);
    }
    if(ImGui::SliderFloat("Rotate Z", m_options+4, -3.14f, 3.14f)){
        m_mesh.getTransMat().rotateZ(m_options[OPT::ROTZ]);
    }
    if(ImGui::SliderFloat("Scale X", m_options+5, -2.0f, 2.0f)){
        m_mesh.getTransMat().scaleX(m_options[OPT::SCALEX]);
    }    
    if(ImGui::SliderFloat("Scale Y", m_options+6, -2.0f, 2.0f)){
        m_mesh.getTransMat().scaleY(m_options[OPT::SCALEY]);
    }
    if(ImGui::SliderFloat("Scale Z", m_options+7, -2.0f, 2.0f)){
        m_mesh.getTransMat().scaleZ(m_options[OPT::SCALEZ]);
    }    
    if(ImGui::SliderFloat("Translate X", m_options+8, -1.0f, 1.0f)){
        m_mesh.getTransMat().translateX(m_options[OPT::TRANSX]);
    }    
    if(ImGui::SliderFloat("Translate Y", m_options+9, -1.0f, 1.0f)){
        m_mesh.getTransMat().translateY(m_options[OPT::TRANSY]);
    }    
    if(ImGui::SliderFloat("Translate Z", m_options+10, -3.0f, 3.0f)){
        m_mesh.getTransMat().translateZ(m_options[OPT::TRANSZ]);
    }    
    if(ImGui::SliderFloat("FOV", m_options+11, 0.0f, 170.0f)){
    }    
    if(ImGui::SliderFloat("Far", m_options+12, -1.0f, 1.0f)){
    }    
    if(ImGui::SliderFloat("Near", m_options+13, -1.0f, 1.0f)){
    }    

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

