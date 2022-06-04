#include "TransformMatrix.h"

TransformMatrix::TransformMatrix()
{
	m_M = projectionMatrix(m_fov, m_near, m_far) * translate(m_tx, m_ty, m_tz) * scale(m_sx, m_sy, m_sz) * rotate(m_ax, m_ay, m_az);
}

Eigen::Matrix4d& TransformMatrix::get(void){
	return m_M;
}

void TransformMatrix::update()
{
	m_M = projectionMatrix(m_fov, m_near, m_far) * translate(m_tx, m_ty, m_tz) * rotate(m_ax, m_ay, m_az) * scale(m_sx, m_sy, m_sz);
}
void TransformMatrix::rotateX(double ax) { m_ax = ax; update(); }
void TransformMatrix::rotateY(double ay) { m_ay = ay; update(); }
void TransformMatrix::rotateZ(double az) { m_az = az; update(); }
void TransformMatrix::mrotate(double ax, double ay, double az) { m_ax=ax; m_ay=ay; m_az=az;update();}
void TransformMatrix::scaleX(double sx) { m_sx = sx; update(); }
void TransformMatrix::scaleY(double sy) { m_sy = sy; update(); }
void TransformMatrix::scaleZ(double sz) { m_sz = sz; update(); }
void TransformMatrix::mscale(double sx, double sy, double sz) { m_sx = sx; m_sy = sy; m_sz = sz; update(); }
void TransformMatrix::translateX(double tx) { m_tx = tx; update(); }
void TransformMatrix::translateY(double ty){ m_ty = ty; update();}
void TransformMatrix::translateZ(double tz){ m_tz = tz; update();}
void TransformMatrix::mtranslate(double tx, double ty, double tz) { m_tx = tx; m_ty = ty; m_tz = tz; update(); }
void TransformMatrix::projection(double fov, double far, double near){m_fov = fov; m_far = far; m_near = near; update();}