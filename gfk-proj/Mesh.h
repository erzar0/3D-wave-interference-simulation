#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Eigen/Dense>
//#include "Matvec.h"
#include <vector>
#include <iostream>
#include "Utils.h"

class Mesh {
public:
	Mesh(int density = 100);

	void renderOnWindow(sf::RenderWindow* window);

private:
	int m_density{};
	std::vector<std::vector<sf::Vertex>> m_sfPoints;
	std::vector<std::vector<Eigen::Vector4d>> m_points{};
};



