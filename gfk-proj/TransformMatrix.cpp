#include "TransformMatrix.h"
#include "Utils.h"
using std::sin;
using std::cos;

TransformMatrix::TransformMatrix()
{
	m_M = s_projectionMatrix(m_fov, m_near, m_far)
		* s_translateMatrix(m_tx, m_ty, m_tz)
		* s_scaleMatrix(m_sx, m_sy, m_sz)
		* s_rotateMatrix(m_ax, m_ay, m_az);
}

void TransformMatrix::update()
{
	m_M = s_projectionMatrix(m_fov, m_near, m_far)
		* s_translateMatrix(m_tx, m_ty, m_tz)
		* s_rotateMatrix(m_ax, m_ay, m_az)
		* s_scaleMatrix(m_sx, m_sy, m_sz);
}

Eigen::Matrix4d& TransformMatrix::get(void){
	return m_M;
}

void TransformMatrix::rotateX(double ax) { m_ax = ax; update(); }
void TransformMatrix::rotateY(double ay) { m_ay = ay; update(); }
void TransformMatrix::rotateZ(double az) { m_az = az; update(); }
void TransformMatrix::scaleX(double sx) { m_sx = sx; update(); }
void TransformMatrix::scaleY(double sy) { m_sy = sy; update(); }
void TransformMatrix::scaleZ(double sz) { m_sz = sz; update(); }
void TransformMatrix::translateX(double tx) { m_tx = tx; update(); }
void TransformMatrix::translateY(double ty){ m_ty = ty; update();}
void TransformMatrix::translateZ(double tz){ m_tz = tz; update();}
void TransformMatrix::changeFOV(double fov) { m_fov = fov; update(); }

Eigen::Matrix4d TransformMatrix::s_translateMatrix(double tx, double ty, double tz) {
	Eigen::Matrix4d res;
	res << 1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1;
	return res;
}
Eigen::Matrix4d TransformMatrix:: s_rotateMatrixX(double ax) {
	Eigen::Matrix4d res;
	double cosA = cos(ax);
	double sinA = sin(ax);
	res << 1, 0, 0, 0,
			0, cosA, sinA, 0,
			0, -sinA, cosA, 0,
			0, 0, 0, 1;
	return res;
}
Eigen::Matrix4d TransformMatrix:: s_rotateMatrixY(double ay) {
	Eigen::Matrix4d res;
	double cosA = cos(ay);
	double sinA = sin(ay);
	res << cosA, 0, -sinA, 0,
			0, 1, 0, 0,
			-sinA, 0, cosA, 0,
			0, 0, 0, 1;
	return res;
}
Eigen::Matrix4d TransformMatrix:: s_rotateMatrixZ(double az) {
	Eigen::Matrix4d res;
	double cosA = cos(az);
	double sinA = sin(az);
	res << cosA, sinA, 0, 0,
			-sinA, cosA, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;
	return res;
}
Eigen::Matrix4d TransformMatrix::s_rotateMatrix(double ax, double ay, double az) {
	return  s_rotateMatrixX(ax) *  s_rotateMatrixY(ay) *  s_rotateMatrixZ(az);
}
Eigen::Matrix4d TransformMatrix::s_scaleMatrix(double sx, double sy, double sz) {
	Eigen::Matrix4d res;
	res << sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1;
	return res;
}
Eigen::Matrix4d TransformMatrix::s_projectionMatrix(double angleOfView, double near, double far)
{
	double scale = 1 / std::tan(angleOfView * 0.5 * std::atan(DBL_MAX) * 2 / 180.0f);
	Eigen::Matrix4d res;
	res << scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, -far / (far - near), -1,
			0, 0, -far * near / (far - near), 1;
	return res;
}
