#include "Mesh.h"

Mesh::Mesh(int density) :
	m_density{ density }
{
	double d = 2.0f / m_density;
	for (int i{ 0 }; i < m_density; i++)
	{
		m_points.push_back(std::vector<Eigen::Vector4d>());
		m_sfPoints.push_back(std::vector<sf::Vertex>());
		for (int j{ 0 }; j < m_density; j++)
		{
			m_points[i].push_back(Eigen::Vector4d(-1.0 + d * i, -1.0 + d * j, 0, 1.0));
			m_sfPoints[i].push_back(sf::Vertex());
		}
	}
}

void Mesh::renderOnWindow(sf::RenderWindow* window)
{
	Eigen::Vector4d temp;
	sf::Vector2i size = (sf::Vector2i) window->getSize();
	m_M.update();
	double x, y;
	for (int i{ 0 }; i < m_density; i++)
	{
		for (int j{ 0 }; j < m_density; j++)
		{

			temp = m_M.get() * m_points[i][j];
			temp.x() = temp.x() / temp.w();
			temp.y() = temp.y() / temp.w();
			temp.z() = temp.z() / temp.w();
			x = utils::mapInterval(-1, 1, 0, size.x, (float)temp.x());
			y = utils::mapInterval(-1, 1, 0, size.y, (float)temp.y());
			m_sfPoints[i][j] = sf::Vertex((sf::Vector2f((float)x, (float)y)),
				sf::Color((char)255, (char)100, (char)0));
			window->draw(&m_sfPoints[i][j], 1, sf::Points);

		}
	}
}
