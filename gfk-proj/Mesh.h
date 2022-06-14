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
	void updateTime(sf::Time& deltaTime) { m_time += (deltaTime.asMicroseconds()) / std::pow(10, 6); }
	void updatePoints(void);
	static float s_wavesParameters[10];
	double interferenceFun(double x, double y, 
		double dx1 = s_wavesParameters[0], 
		double dy1 = s_wavesParameters[1], 
		double dx2 = s_wavesParameters[2],
		double dy2 = s_wavesParameters[3], 
		double A1 = s_wavesParameters[4], 
		double A2 = s_wavesParameters[5], 
		double f1 = s_wavesParameters[6], 
		double f2 = s_wavesParameters[7], 
		double k1 = s_wavesParameters[8], 
		double k2 = s_wavesParameters[9]);

private:
	int m_density{};
	TransformMatrix m_M{};
	static double m_time;

	sf::Vertex* m_sfPoints{};
	std::vector<std::array<sf::Vertex, 5>> m_sfQuads;
	sf::VertexArray m_sfQuadsSorted;
	Eigen::Vector4d* m_points{};

	sf::Image m_image{};
	bool m_imageLoaded{ false };

};




