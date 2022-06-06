#include "Matvec.h" 
#include <cmath>
#include <cfloat>
using std::sin;
using std::cos;



Eigen::Matrix4d translate(double tx, double ty, double tz){
	Eigen::Matrix4d res;
	res << 1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1;
	return res;
}

Eigen::Matrix4d rotateX(double ax){
	Eigen::Matrix4d res;
	double cosA = cos(ax);
	double sinA = sin(ax);
	res << 1, 0, 0, 0,
		0, cosA, sinA, 0,
		0, -sinA, cosA, 0,
		0, 0, 0, 1;
	return res;
}

Eigen::Matrix4d rotateY(double ay){
	Eigen::Matrix4d res;
	double cosA = cos(ay);
	double sinA = sin(ay);
	res << cosA, 0, -sinA, 0,
			0, 1, 0, 0,
			-sinA, 0, cosA, 0,
			0, 0, 0, 1;
	return res;
}


Eigen::Matrix4d rotateZ(double az){
	Eigen::Matrix4d res;
	double cosA = cos(az);
	double sinA = sin(az);
	res << cosA, sinA, 0, 0,
		-sinA, cosA, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
	return res;
}

Eigen::Matrix4d rotate(double ax, double ay, double az){
	return rotateX(ax) * rotateY(ay) * rotateZ(az);
}


Eigen::Matrix4d scale(double sx, double sy, double sz){
	Eigen::Matrix4d res;
	res << sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1;
	return res;
}


Eigen::Matrix4d projectionMatrix(double angleOfView, double near, double far)
{	
	double scale = 1 / std::tan(angleOfView * 0.5 * std::atan(DBL_MAX)*2/180.0f);
	Eigen::Matrix4d res;
	res << scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, -far / (far - near), -1,
		0, 0, -far * near / (far - near),1 ;
	return res;
}

