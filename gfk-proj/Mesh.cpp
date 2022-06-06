#include "Mesh.h"
#include <omp.h>

Mesh::Mesh(int density) :
	m_density{ density }
{
	double d = 2.0f / m_density;
	m_sfPoints =  new sf::Vertex[m_density * m_density];
	for (int i{ 0 }; i < m_density; i++)
	{
		m_points.push_back(std::vector<Eigen::Vector4d>());
		for (int j{ 0 }; j < m_density; j++)
		{
			m_points[i].push_back(Eigen::Vector4d(-1.0 + d * i, -1.0 + d * j, std::sin(1+d*j), 1.0));
		}
	}
}

void Mesh::renderOnWindow(sf::RenderWindow* window)
{
	sf::Vector2i size = (sf::Vector2i) window->getSize();

	#pragma omp parallel for 
	for (int i{ 0 }; i < m_density; i++)
	{
		#pragma omp parallel for 
		for (int j{ 0 }; j < m_density; j++)
		{

			float x, y, w;
			Eigen::Vector4d temp;
			temp = m_M.get() * m_points[i][j];
			w = temp.w();
			x = temp.x() / w;
			y = temp.y() / w;
			x = utils::mapInterval(-1, 1, 0, size.x, x);
			y = utils::mapInterval(-1, 1, 0, size.y, y);
			m_sfPoints[i * m_density + j].position=(sf::Vector2f(x, y));

		}
	}
	window->draw(m_sfPoints, m_density*m_density, sf::Points);

}
