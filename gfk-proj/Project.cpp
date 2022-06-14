#include "Project.h"
#include "Utils.h"
#include <iostream>
#include <cmath>
#include <string>

float Project::m_renderOptions[10] = { 2.4f, 0.0f, 0.0f, 0.4f, 0.4f, 0.05f, 0.0f, 0.0f, 0.0f, 60.0f };
float Mesh::s_wavesParameters[10] = {-0.5f, -0.5f, 0.5f, 0.5f, 3.0f, 3.0f, 0.2f, 0.1f, 60.0f, 60.0f};

void Project::initWindow()
{
	m_window = new sf::RenderWindow(sf::VideoMode(1600, 900), "3DWaveInterference");
    ImGui::SFML::Init(*m_window);
    m_mesh.getTransMat().scaleX(m_renderOptions[RENDER::SCALEX]);
    m_mesh.getTransMat().rotateX(m_renderOptions[RENDER::ROTX]);
    m_mesh.getTransMat().scaleY(m_renderOptions[RENDER::SCALEY]);
    m_mesh.getTransMat().scaleZ(m_renderOptions[RENDER::SCALEZ]);
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
    if(!stopped)
        m_mesh.updateTime(m_dt);
}

void Project::render()
{
    renderMenu();

    m_window->clear();
    m_mesh.renderOnWindow(m_window);
    ImGui::SFML::Render(*m_window);
    m_window->display();
}

void Project::run()
{
    while (m_window->isOpen())
    {
        update();
        render();
    }

}

void Project::renderMenu()
{
    static std::string fps{ 0 };
    static std::string frameTime{ 0 };
    static double timeElapsed{ 0 };
    double updatesPerSec = 5;
    double dtAsSeconds = m_dt.asMicroseconds() / std::pow(10, 6);
    timeElapsed += dtAsSeconds;
    if (timeElapsed >= 1 / updatesPerSec)
    {
        timeElapsed = 0;
        fps = std::string("FPS: ") + std::to_string(static_cast<int>(1.0 / dtAsSeconds));
        frameTime = std::string("Frametime: ") + utils::to_string_with_precision<double>(dtAsSeconds * 1000.0, 2) + "ms";
    }

    ImGui::Begin("Menu");
    ImGui::SetWindowPos(ImVec2(float(m_window->getSize().x-330), float(m_window->getSize().y-800)));
    ImGui::SetWindowSize(ImVec2(300, 650));
    ImGui::Text(fps.c_str());
    ImGui::Text(frameTime.c_str());
    
    ImGui::Spacing();
    ImGui::Text("Wave parameters:");
    ImGui::SliderFloat("x1", Mesh::s_wavesParameters, -1.0, 1.0);
    ImGui::SliderFloat("y1", Mesh::s_wavesParameters+1, -1.0, 1.0);
    ImGui::SliderFloat("x2", Mesh::s_wavesParameters+2, -1.0, 1.0);
    ImGui::SliderFloat("y2", Mesh::s_wavesParameters+3, -1.0, 1.0);
    ImGui::SliderFloat("Amplitude 1", Mesh::s_wavesParameters+4, 0.0, 10.0);
    ImGui::SliderFloat("Amplitude 2", Mesh::s_wavesParameters+5, 0.0, 10.0);
    ImGui::SliderFloat("Frequency 1",Mesh::s_wavesParameters+6, 0.0, 2.0);
    ImGui::SliderFloat("Frequency 2",Mesh::s_wavesParameters+7, 0.0, 2.0);
    ImGui::SliderFloat("Wavenumber 1", Mesh::s_wavesParameters + 8, 50.0, 100.0);
    ImGui::SliderFloat("Wavenumber 2", Mesh::s_wavesParameters + 9, 50.0, 100.0);
    
    ImGui::Spacing();
    ImGui::Text("Manipulating wave:");
    if (ImGui::SliderFloat("Rotate X", &m_renderOptions[RENDER::ROTX], -3.14f, 3.14f)) {
        m_mesh.getTransMat().rotateX(m_renderOptions[RENDER::ROTX]);
    }
    if (ImGui::SliderFloat("Rotate Y", &m_renderOptions[RENDER::ROTY], -3.14f, 3.14f)) {
        m_mesh.getTransMat().rotateY(m_renderOptions[RENDER::ROTY]);
    }
    if (ImGui::SliderFloat("Rotate Z", &m_renderOptions[RENDER::ROTZ], -3.14f, 3.14f)) {
        m_mesh.getTransMat().rotateZ(m_renderOptions[RENDER::ROTZ]);
    }
    if (ImGui::SliderFloat("Scale X", &m_renderOptions[RENDER::SCALEX], -1.0f, 1.0f)) {
        m_mesh.getTransMat().scaleX(m_renderOptions[RENDER::SCALEX]);
    }
    if (ImGui::SliderFloat("Scale Y", &m_renderOptions[RENDER::SCALEY], -1.0f, 1.0f)) {
        m_mesh.getTransMat().scaleY(m_renderOptions[RENDER::SCALEY]);
    }
    if (ImGui::SliderFloat("Scale Z", &m_renderOptions[RENDER::SCALEZ], -0.25f, 0.25f)) {
        m_mesh.getTransMat().scaleZ(m_renderOptions[RENDER::SCALEZ]);
    }
    if (ImGui::SliderFloat("Translate X", &m_renderOptions[RENDER::TRANSX], -1.0f, 1.0f)) {
        m_mesh.getTransMat().translateX(m_renderOptions[RENDER::TRANSX]);
    }
    if (ImGui::SliderFloat("Translate Y", &m_renderOptions[RENDER::TRANSY], -1.0f, 1.0f)) {
        m_mesh.getTransMat().translateY(m_renderOptions[RENDER::TRANSY]);
    }
    if (ImGui::SliderFloat("Translate Z", &m_renderOptions[RENDER::TRANSZ], -3.0f, 3.0f)) {
        m_mesh.getTransMat().translateZ(m_renderOptions[RENDER::TRANSZ]);
    }
    if (ImGui::SliderFloat("FOV", &m_renderOptions[RENDER::FOV], 1.0f, 170.0f)) {
        m_mesh.getTransMat().changeFOV(m_renderOptions[RENDER::FOV]);
    }

    for (int i = 0; i < 3; i++)
        ImGui::Spacing();

    if(ImGui::Button("Save", ImVec2(80.0f, 0.0f))){
        sf::Vector2u windowSize = m_window->getSize();
        sf::Texture texture;
        texture.create(windowSize.x, windowSize.y);
        texture.update(*m_window);
        sf::Image screenshot = texture.copyToImage();
        screenshot.saveToFile("output.png");
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop", ImVec2(80.0f, 0.0f))) {
        stopped == false ? stopped = true : stopped = false;
    }

	ImGui::End();
}
