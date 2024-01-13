#pragma once

#include <stdint.h>

bool Is4K();
float _4K(float in); // scale float "in" to screen resolution

void DrawShader(float x, float y, float width, float height, const float *color);

void DrawLine(float x1, float y1, float x2, float y2, float width, const float *color);

void DrawText(const char *text, float x, float y, const float *color, float fontSize);

void DrawCenterTextWithBackground(const char *text, float x, float y, const float *color, float fontSize, const float *backgroundColor);

void DrawCenterTextWithBackgroundWithBorder(const char *text, float x, float y, const float *color, float fontSize, const float *backgroundColor, int borderSize, const float *borderColor);

void DrawAimbotRect(float width, float height);
