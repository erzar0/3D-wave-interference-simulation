#include <omp.h>
#include <cmath>
#include <functional>
#include <execution>
#include "Mesh.h"
#include "Utils.h"

using std::sin;
using std::cos;
double Mesh::m_time{0};

double Mesh::interferenceFun(double x, double y, double dx1, double dy1, double dx2, double dy2,
	double A1, double A2, double f1, double f2, double k1, double k2)
{	
	auto sqrtxy = [&](double dx, double dy) { return std::sqrt((x - dx) * (x - dx) + (y - dy) * (y - dy)); };
	static float max{ -1000000000 };
	double sqrtX2Y2A = sqrtxy(dx1, dy1);
	double sqrtX2Y2B = sqrtxy(dx2, dy2);
	double tw2 = 2 * utils::pi * f2 * m_time;
	double tw1 = 2 * utils::pi * f1 * m_time;
	float val = (float) (A1* std::exp(-sqrtX2Y2A)* cos(-tw1 + sqrtX2Y2A*k1)
				+ A2*std::exp(-sqrtX2Y2B) * cos(-tw2 + sqrtX2Y2B*k2));
	if (val > max) max = val;
	return val/(max);
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
			if (m_imageLoaded)
			{
				m_sfPoints[i * m_density + j].color = sf::Color(
					m_image.getPixel((int)((x + 1.0) / 2.0 * m_image.getSize().x),
					(int)((y+1.0)/2.0 * m_image.getSize().y)).toInteger());
			}
			else
			{
				m_sfPoints[i * m_density + j].color = utils::HSVtoRGB((float)utils::mapInterval(-1, 1, 0, 1, z));
			}
		}
	}
}
Mesh::Mesh(int density) :
	m_density{ density }
{
	if (m_image.loadFromFile("texture.jpg")) m_imageLoaded = true;
	m_sfPoints =  new sf::Vertex[m_density * m_density];
	m_points = new Eigen::Vector4d[m_density * m_density];
	m_sfQuadsSorted.resize(m_density * m_density * 4);
	m_sfQuadsSorted.setPrimitiveType(sf::Quads);
	m_sfQuads.reserve(m_density* m_density);
	for(int i = 0; i<m_density * m_density; i++)
	{
		m_sfQuads.push_back(std::array<sf::Vertex, 5>());
	}
	updatePoints();
}


void Mesh::renderOnWindow(sf::RenderWindow* window)
{
	updatePoints();
	sf::Vector2i windowSize = (sf::Vector2i) window->getSize();
	Eigen::Matrix4d viewModel = m_M.get().inverse();
	Eigen::Vector4d cameraPosition = viewModel.col(3);
	#pragma omp parallel for 
	for (int i{ 0 }; i < m_density; i++)
	{
		for (int j{ 0 }; j < m_density; j++)
		{
			if (i != 0 && j != 0)
			{
				m_sfQuads[i * m_density + j][4].position.x = (float)utils::distanceBetweenPoints(cameraPosition, m_points[i * m_density + j]);
			}

			m_points[i * m_density + j] = m_M.get() * m_points[i * m_density + j];
			float x, y, w;
			w = (float)m_points[i * m_density + j].w();
			x = (float)utils::mapInterval(-1, 1, 0, windowSize.x, m_points[i * m_density + j].x() / w);
			y = (float)utils::mapInterval(-1, 1, 0, windowSize.y, m_points[i * m_density + j].y() / w);
			m_sfPoints[i * m_density + j].position = sf::Vector2f(x, y);

			if (i != 0 && j != 0)
			{
				m_sfQuads[i * m_density + j][0] = m_sfPoints[(i - 1) * m_density + j - 1];
				m_sfQuads[i * m_density + j][1] = m_sfPoints[(i - 1) * m_density + j];
				m_sfQuads[i * m_density + j][2] = m_sfPoints[(i)*m_density + j];
				m_sfQuads[i * m_density + j][3] = m_sfPoints[(i)*m_density + j - 1];
			}
		}
	}

	std::sort(std::execution::par_unseq, m_sfQuads.begin(), m_sfQuads.end(), [&](auto q1, auto q2) {
		return q1[4].position.x < q2[4].position.x; });

	#pragma omp parallel for
	for (int i = 0; i < m_density; i++)
	{
		for (int j{ 0 }; j < m_density; j++)
		{
			m_sfQuadsSorted[(i*m_density + j)*4 + 0] = m_sfQuads[i*m_density + j][0];
			m_sfQuadsSorted[(i*m_density + j)*4 + 1] = m_sfQuads[i*m_density + j][1];
			m_sfQuadsSorted[(i*m_density + j)*4 + 2] = m_sfQuads[i*m_density + j][2];
			m_sfQuadsSorted[(i*m_density + j)*4 + 3] = m_sfQuads[i*m_density + j][3];
		}

	}
	window->draw(m_sfQuadsSorted);
}
