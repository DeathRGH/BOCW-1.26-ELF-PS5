#pragma once

#include <stdint.h>

#include "structs.h"

// function defines

typedef float(*atanf_t)(float x);
extern atanf_t atanf;

typedef double(*atan2_t)(double y, double x);
extern atan2_t atan2;

typedef double(*cos_t)(double x);
extern cos_t cos;

typedef double(*frexp_t)(double x, int* exp);
extern frexp_t frexp;

typedef double(*ldexp_t)(double x, int exp);
extern ldexp_t ldexp;

typedef void *(*memcpy_t)(void *destination, const void *source, uint64_t num);
extern memcpy_t memcpy;

typedef float(*powf_t)(float base, float exponent);
extern powf_t powf;

typedef int(*snprintf_t)(char *s, uint64_t n, const char *format, ...);
extern snprintf_t snprintf;

typedef int(*strcmp_t)(const char *str1, const char *str2);
extern strcmp_t strcmp;

// game function defines

typedef void(*AimTarget_GetTagPos_t)(const centity_t ent, float *pos);
extern AimTarget_GetTagPos_t AimTarget_GetTagPos;

typedef bool(*AimTarget_IsTargetVisible_t)(LocalClientNum_t localClientNum, centity_t targetEnt);
extern AimTarget_IsTargetVisible_t AimTarget_IsTargetVisible;

typedef void(*CG_DrawRotatedPicPhysicalW_t)(const ScreenPlacement *screenPlacement, float x, float y, float w, float width, float height, float angle, const float *color, uint64_t material, uint64_t image);
extern CG_DrawRotatedPicPhysicalW_t CG_DrawRotatedPicPhysicalW;

typedef void(*R_AddCmdDrawText_t)(const char *text, int maxChars, uint64_t font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style, float padding);
extern R_AddCmdDrawText_t R_AddCmdDrawText;

typedef int(*R_TextHeight_t)(uint64_t font);
extern R_TextHeight_t R_TextHeight;

typedef float(*R_TextWidth_t)(LocalClientNum_t localClientNum, const char *text, int maxChars, uint64_t font);
extern R_TextWidth_t R_TextWidth;

extern uint64_t baseAddress;
uint64_t ResolveAddress(uint64_t offset);

void InitFunctions();

// custom functions

bool WorldToScreen(float *worldLocation, float *screen);

bool IsInGame();
