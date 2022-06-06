#include "Mesh.h"
#include <omp.h>
#include <cmath>
#include <functional>

using std::sin;
using std::cos;
double Mesh::m_time{0};

double Mesh::interferenceFun(double x, double y, double dx1, double dy1, double dx2, double dy2,
	double A1, double A2, double f1, double f2, double k1, double k2)
{	
	auto sqrtxy = [&](double dx, double dy) { return std::sqrt((x - dx) * (x - dx) + (y - dy) * (y - dy)); };
	double sqrtX2Y2A = sqrtxy(dx1, dy1);
	double sqrtX2Y2B = sqrtxy(dx2, dy2);
	double tw2 = 2 * pi * f2 * m_time;
	double tw1 = 2 * pi * f1 * m_time;
	double val = A1* std::exp(-sqrtX2Y2A)* cos(tw1 + sqrtX2Y2A*k1) + A2*std::exp(-sqrtX2Y2B) * cos(tw2 + sqrtX2Y2B*k2);
	return val/(2*A1*A2);
}
void Mesh::updatePoints(void)
{
	double d = 2.0f / m_density;
	#pragma omp parallel for
	for (int i{ 0 }; i < m_density; i++)
	{
		for (int j{ 0 }; j < m_density; j++)
		{
			double x = -1.0 + d * i;
			double y = -1.0 + d * j;
			double z = interferenceFun(x, y);
			m_points[i * m_density + j] = Eigen::Vector4d(x, y, z, 1.0);
			m_sfPoints[i * m_density + j].color = utils::HSVtoRGB((float)utils::mapInterval(-1.0f, 1.0f, 0.0f, 1.0f, z));
		}
	}
}
Mesh::Mesh(int density) :
	m_density{ density }
{
	m_sfPoints =  new sf::Vertex[m_density * m_density];
	m_points = new Eigen::Vector4d[m_density * m_density];
	updatePoints();
}

void Mesh::renderOnWindow(sf::RenderWindow* window)
{
	updatePoints();
	sf::Vector2i size = (sf::Vector2i) window->getSize();

	#pragma omp parallel for 
	for (int i{ 0 }; i < m_density; i++)
	{
		for (int j{ 0 }; j < m_density; j++)
		{

			float x, y, w;
			Eigen::Vector4d temp;
			temp = m_M.get() * m_points[i*m_density + j];
			w = (float)temp.w();
			x = (float)utils::mapInterval(-1, 1, 0, size.x, temp.x()/w);
			y = (float)utils::mapInterval(-1, 1, 0, size.y, temp.y()/w);
			m_sfPoints[i * m_density + j].position = sf::Vector2f(x, y);

		}
	}
	window->draw(m_sfPoints, m_density*m_density, sf::Points);

}
