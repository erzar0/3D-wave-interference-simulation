#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <array>
#include "TransformMatrix.h"
#include "Utils.h"
#include <Eigen/Core>

class Mesh {
public:
	Mesh(int density = 100);
	~Mesh() { delete[] m_sfPoints; delete[] m_points; }
	void renderOnWindow(sf::RenderWindow* window);
	TransformMatrix& getTransMat(void) { return m_M; }
	void updateTime(sf::Time& deltaTime) { m_time += (deltaTime.asMicroseconds())/ std::pow(10, 6); }
	void updatePoints(void);
	double interferenceFun(double x, double y, double dx1 = -0.5, double dy1 = -0.5, double dx2 = 0.5, 
		double dy2 = 0.5, double A1 = 2, double A2 = 3, double f1 = 0.2, double f2 = 0.1, double k1=30, double k2=30);

private:
	int m_density{};
	TransformMatrix m_M{};
	sf::Vertex* m_sfPoints{};
	std::vector<std::array<sf::Vertex, 4>> m_sfQuads;
	sf::Vertex* m_sfQuadsSorted{};
	Eigen::Vector4d* m_points{};

	static double m_time;
	//std::vector<std::vector<Eigen::Vector4d>> m_points{};
};




