#include "drawing.h"

#include "addresses.h"
#include "functions.h"
#include "math.h"

bool Is4K() {
	return UiContext->screenWidth > 1920;
}

float _4K(float in) {
	return in / (Is4K() ? 1.0f : 2.0f);
}

void DrawShader(float x, float y, float width, float height, const float *color) {
	CG_DrawRotatedPicPhysicalW(ScrPlace, _4K(x), _4K(y), 1.0f, _4K(width), _4K(height), 0.0f, color, MaterialWhite, 0);
}

void DrawLine(float x1, float y1, float x2, float y2, float width, const float *color) {
	float x, y, angle, L1, L2, H1;
	H1 = y2 - y1;
	L1 = x2 - x1;
	L2 = sqrt(L1 * L1 + H1 * H1);
	x = x1 + ((L1 - L2) / 2);
	y = y1 + (H1 / 2);
	angle = atanf(H1 / L1) * (180.0f / MATH_PI);
	CG_DrawRotatedPicPhysicalW(ScrPlace, x, y, 1.0f, L2, _4K(width), angle, color, MaterialWhite, 0);
}

void DrawText(const char *text, float x, float y, const float *color, float fontSize) {
	R_AddCmdDrawText(text, 0x7FFFFFFF, FontDefault, _4K(x), _4K(y), _4K(fontSize), _4K(fontSize), 0.0f, color, 0, 0.0f);
}

void DrawCenterTextWithBackground(const char *text, float x, float y, const float *color, float fontSize, const float *backgroundColor) {
	float textWidth = R_TextWidth(LocalClientNum_t::LOCAL_CLIENT_0, text, 0x7FFFFFFF, FontDefault) * fontSize;
	float textHeight = R_TextHeight(FontDefault) * fontSize;

	DrawShader(_4K(x - 4 - textWidth / 2), _4K(y - (textHeight * 0.2f) - textHeight / 2), _4K(textWidth + 8), _4K(textHeight + (textHeight * 0.2f)), backgroundColor);
	DrawText(text, _4K(x - textWidth / 2), _4K(y + textHeight / 2), color, _4K(fontSize));
}

void DrawCenterTextWithBackgroundWithBorder(const char *text, float x, float y, const float *color, float fontSize, const float *backgroundColor, int borderSize, const float *borderColor) {
	float textWidth = R_TextWidth(LocalClientNum_t::LOCAL_CLIENT_0, text, 0x7FFFFFFF, FontDefault) * fontSize;
	float textHeight = R_TextHeight(FontDefault) * fontSize;

	DrawShader(_4K(x - 4 - textWidth / 2), _4K(y - (textHeight * 0.2f) - borderSize - textHeight / 2), _4K(textWidth + 8), _4K(textHeight + (textHeight * 0.2f)), backgroundColor); // background
	DrawShader(_4K(x - 4 - borderSize - textWidth / 2), _4K(y - (textHeight * 0.2f) - borderSize * 2 - textHeight / 2), _4K(borderSize), _4K(textHeight + (textHeight * 0.2f) + 2 * borderSize), borderColor); //left
	DrawShader(_4K(x + 4 + textWidth / 2), _4K(y - (textHeight * 0.2f) - borderSize * 2 - textHeight / 2), _4K(borderSize), _4K(textHeight + (textHeight * 0.2f) + 2 * borderSize), borderColor); //right
	DrawShader(_4K(x - 4 - textWidth / 2), _4K(y - (textHeight * 0.2f) - borderSize * 2 - textHeight / 2), _4K(textWidth + 8), _4K(borderSize), borderColor); //top
	DrawShader(_4K(x - 4 - textWidth / 2), _4K(y - borderSize + textHeight / 2), _4K(textWidth + 8), _4K(borderSize), borderColor); //bottom

	DrawText(text, _4K(x - textWidth / 2), _4K(y - borderSize + textHeight / 2), color, _4K(fontSize));
}

void DrawAimbotRect(float width, float height) {
	DrawLine(_4K((cg->refdef.width / 2) - (width / 2)), _4K((cg->refdef.height / 2) - (height / 2)), _4K((cg->refdef.width / 2) - (width / 2)), _4K((cg->refdef.height / 2) + (height / 2)), _4K(2.0f), yellow10); // left
	DrawLine(_4K((cg->refdef.width / 2) + (width / 2)), _4K((cg->refdef.height / 2) - (height / 2)), _4K((cg->refdef.width / 2) + (width / 2)), _4K((cg->refdef.height / 2) + (height / 2)), _4K(2.0f), yellow10); // right
	DrawLine(_4K((cg->refdef.width / 2) - (width / 2)), _4K((cg->refdef.height / 2) - (height / 2)), _4K((cg->refdef.width / 2) + (width / 2)), _4K((cg->refdef.height / 2) - (height / 2)), _4K(2.0f), yellow10); // top
	DrawLine(_4K((cg->refdef.width / 2) - (width / 2)), _4K((cg->refdef.height / 2) + (height / 2)), _4K((cg->refdef.width / 2) + (width / 2)), _4K((cg->refdef.height / 2) + (height / 2)), _4K(2.0f), yellow10); // bottom
}
