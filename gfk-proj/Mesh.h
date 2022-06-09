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
	Mesh(int density = 200);
	~Mesh() { delete[] m_sfPoints; delete[] m_points; }
	void renderOnWindow(sf::RenderWindow* window);
	TransformMatrix& getTransMat(void) { return m_M; }
	void updateTime(sf::Time& deltaTime) { m_time += (deltaTime.asMicroseconds()) / std::pow(10, 6); }
	void updatePoints(void);
	//double interferenceFun(double x, double y, double dx1 = -0.5, double dy1 = -0.5, double dx2 = 0.5, 
	//	double dy2 = 0.5, double A1 = 3, double A2 = 3, double f1 = 0.2, double f2 = 0.1, double k1=60, double k2=60);
	double interferenceFun(double x, double y, double dx1 = m_wavesParameters[0], double dy1 = m_wavesParameters[1], double dx2 = m_wavesParameters[2],
		double dy2 = m_wavesParameters[3], double A1 = m_wavesParameters[4], double A2 = m_wavesParameters[5], double f1 = m_wavesParameters[6], double f2 = m_wavesParameters[7], double k1 = m_wavesParameters[8], double k2 = m_wavesParameters[9]);
	static float m_wavesParameters[10];

private:
	int m_density{};
	TransformMatrix m_M{};
	sf::Vertex* m_sfPoints{};
	std::vector<std::array<sf::Vertex, 5>> m_sfQuads;
	sf::VertexArray m_sfQuadsSorted;
	Eigen::Vector4d* m_points{};
	sf::Image m_image{};
	bool m_imageLoaded{ false };
	static double m_time;
	//std::vector<std::vector<Eigen::Vector4d>> m_points{};

};




