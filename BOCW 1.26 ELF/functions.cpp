#include "functions.h"

#include "addresses.h"
#include "math.h"

// function defines

atanf_t atanf;
atan2_t atan2;
cos_t cos;
frexp_t frexp;
ldexp_t ldexp;
memcpy_t memcpy;
powf_t powf;
snprintf_t snprintf;
strcmp_t strcmp;

// game function defines

AimTarget_GetTagPos_t AimTarget_GetTagPos;
AimTarget_IsTargetVisible_t AimTarget_IsTargetVisible;
CG_DrawRotatedPicPhysicalW_t CG_DrawRotatedPicPhysicalW;
R_AddCmdDrawText_t R_AddCmdDrawText;
R_TextHeight_t R_TextHeight;
R_TextWidth_t R_TextWidth;

uint64_t baseAddress;
uint64_t ResolveAddress(uint64_t offset) {
	return baseAddress + offset;
}

void InitFunctions() {
	atanf = (atanf_t)ResolveAddress(ADDR_atanf);
	atan2 = (atan2_t)ResolveAddress(ADDR_atan2);
	cos = (cos_t)ResolveAddress(ADDR_cos);
	frexp = (frexp_t)ResolveAddress(ADDR_frexp);
	ldexp = (ldexp_t)ResolveAddress(ADDR_ldexp);
	memcpy = (memcpy_t)ResolveAddress(ADDR_memcpy);

	powf = (powf_t)ResolveAddress(ADDR_powf);

	snprintf = (snprintf_t)ResolveAddress(ADDR_snprintf);

	strcmp = (strcmp_t)ResolveAddress(ADDR_strcmp);

	AimTarget_GetTagPos = (AimTarget_GetTagPos_t)ResolveAddress(ADDR_AimTarget_GetTagPos);
	AimTarget_IsTargetVisible = (AimTarget_IsTargetVisible_t)ResolveAddress(ADDR_AimTarget_IsTargetVisible);
	CG_DrawRotatedPicPhysicalW = (CG_DrawRotatedPicPhysicalW_t)ResolveAddress(ADDR_CG_DrawRotatedPicPhysicalW);
	R_AddCmdDrawText = (R_AddCmdDrawText_t)ResolveAddress(ADDR_R_AddCmdDrawText);
	R_TextHeight = (R_TextHeight_t)ResolveAddress(ADDR_R_TextHeight);
	R_TextWidth = (R_TextWidth_t)ResolveAddress(ADDR_R_TextWidth);
}

// custom functions

bool WorldToScreen(float *worldLocation, float *screen) {
	float local[3];
	float transform[3];

	local[0] = worldLocation[0] - cg->refdef.vieworg[0];
	local[1] = worldLocation[1] - cg->refdef.vieworg[1];
	local[2] = worldLocation[2] - cg->refdef.vieworg[2];

	transform[0] = DotProduct(local, cg->refdef.viewaxis[1]);
	transform[1] = DotProduct(local, cg->refdef.viewaxis[2]);
	transform[2] = DotProduct(local, cg->refdef.viewaxis[0]);

	if (transform[2] < 0.01f)
		return false;

	screen[0] = (cg->refdef.width / 2) * (1.0f - (transform[0] / cg->refdef.tanHalfFovX / transform[2]));
	screen[1] = (cg->refdef.height / 2) * (1.0f - (transform[1] / cg->refdef.tanHalfFovY / transform[2]));

	return (transform[2] > 0);
}

bool IsInGame() {
	return cg != 0 && cgs != 0 && centity != 0 && clientActive != 0;
}
