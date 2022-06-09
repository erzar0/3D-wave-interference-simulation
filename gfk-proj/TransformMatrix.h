#pragma once
#define SFML_STATIC
#include <Eigen/Dense>
#include "Matvec.h"
#include "Enums.h"

class TransformMatrix {
public:
	TransformMatrix();
	Eigen::Matrix4d& get(void);
	void update();
	void rotateX(double ax);
	void rotateY(double ay);
	void rotateZ(double az);
	void mrotate(double ax=0, double ay=0, double az=0);
	void scaleX(double sx = 0.25);
	void scaleY(double sy = 0.25);
	void scaleZ(double sz = 0.025);
	void mscale(double sx = 1, double sy = 1, double sz = 1);
	void translateX(double tx);
	void translateY(double ty);
	void translateZ(double tz);
	void mtranslate(double tx=0, double ty=0, double tz=0);
	void changeFOV(double fov = 60);
	void changeFar(double far = 100);
	void changeNear(double near = 1);
	void projection(double fov=60, double far=100, double near=1);

private:
	Eigen::Matrix4d m_M{};
	double m_tx{0}, m_ty{0}, m_tz{0}, m_sx{ 10 }, m_sy{ 1 }, m_sz{ 1 },
		m_ax{ 0 }, m_ay{0}, m_az{0}, m_far{ 100 }, m_near{ 1 }, m_fov{ 60 };
};

