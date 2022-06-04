#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include "TransformMatrix.h"
#include "Utils.h"

class Mesh {
public:
	Mesh(int density = 100);
	void renderOnWindow(sf::RenderWindow* window);
	TransformMatrix& getTransMat(void) { return m_M; }

private:
	int m_density{};
	TransformMatrix m_M{};
	std::vector<std::vector<sf::Vertex>> m_sfPoints;
	std::vector<std::vector<Eigen::Vector4d>> m_points{};
};




