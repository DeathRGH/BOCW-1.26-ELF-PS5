#pragma once

#define MATH_PI 3.14159265358979323846

double sqrt(double x);

float Distance(float * one, float * two);

void VectorToAngles(const float * forward, float * angles);

float DotProduct(float * view, float * axis);
