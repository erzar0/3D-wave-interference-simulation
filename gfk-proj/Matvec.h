#pragma once
#define SFML_STATIC
#include <iostream>
#include <string>
#include <Eigen/Dense>

Eigen::Matrix4d translate(double tx = 0, double ty = 0, double tz = 0);
Eigen::Matrix4d rotateX(double ax = 0);
Eigen::Matrix4d rotateY(double ay = 0);
Eigen::Matrix4d rotateZ(double az = 0);
Eigen::Matrix4d rotate(double ax = 0, double ay = 0, double az = 0);
Eigen::Matrix4d scale(double sx = 1, double sy = 1, double sz = 1);
Eigen::Matrix4d ProjectionMatrix(const double& angleOfView = 60, const double& near = 1, const double& far = 100);

