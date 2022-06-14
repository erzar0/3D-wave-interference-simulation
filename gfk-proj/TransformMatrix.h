#pragma once
#define SFML_STATIC
#include <Eigen/Dense>

class TransformMatrix {
public:
	TransformMatrix();
	Eigen::Matrix4d& get(void);
	void update();
	void rotateX(double ax);
	void rotateY(double ay);
	void rotateZ(double az);
	void scaleX(double sx);
	void scaleY(double sy);
	void scaleZ(double sz);
	void translateX(double tx);
	void translateY(double ty);
	void translateZ(double tz);
	void changeFOV(double fov);

private:
	Eigen::Matrix4d m_M{};
	double m_tx{0}, m_ty{0}, m_tz{0}, m_sx{ 10 }, m_sy{ 1 }, m_sz{ 1 },
		m_ax{ 0 }, m_ay{0}, m_az{0}, m_far{ 100 }, m_near{ 1 }, m_fov{ 60 };

	static Eigen::Matrix4d s_translateMatrix(double tx = 0, double ty = 0, double tz = 0);
	static Eigen::Matrix4d  s_rotateMatrixX(double ax = 0);
	static Eigen::Matrix4d  s_rotateMatrixY(double ay = 0);
	static Eigen::Matrix4d  s_rotateMatrixZ(double az = 0);
	static Eigen::Matrix4d s_rotateMatrix(double ax = 0, double ay = 0, double az = 0);
	static Eigen::Matrix4d s_scaleMatrix(double sx = 1, double sy = 1, double sz = 1);
	static Eigen::Matrix4d s_projectionMatrix(double angleOfView = 60, double near = 1, double far = 100);
};

