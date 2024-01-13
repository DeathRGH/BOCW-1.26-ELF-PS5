#pragma once

// we store all of our update sepcific addresses in one place for easy porting

// patches
#define ADDR_Patch_BG_WeaponFireRecoil 0x00000000009EB140

#define ADDR_Patch_GunShake1 0x0000000000A7A2B1
#define ADDR_Patch_GunShake2 0x0000000000A7A2BE

#define ADDR_Patch_AllClient_Godmode 0x0000000000D93560
#define ADDR_Patch_AllClient_InfAmmo 0x0000000000AA436C

#define ADDR_Patch_UnlockAll 0x00000000011C0270

// structures and data
#define ADDR_MaterialWhite 0x0000000004556620
#define ADDR_FontDefault 0x0000000004556648

#define ADDR_ScrPlace 0x00000000031FED80
#define ADDR_UiContext 0x000000000BE196D0
#define ADDR_cg 0x000000000A156780
#define ADDR_cgs 0x000000000A156788
#define ADDR_centity 0x000000000A0CB860
#define ADDR_clientActive 0x000000000BE14CE8

// functions
#define ADDR_atanf 0x0000000001F27BA0
#define ADDR_atan2 0x0000000001F2E4C0
#define ADDR_cos 0x0000000001F2C010
#define ADDR_frexp 0x0000000001F2E8B0
#define ADDR_ldexp 0x0000000001F2E910
#define ADDR_memcpy 0x0000000001F27AD0

#define ADDR_powf 0x0000000001F27F60

#define ADDR_snprintf 0x0000000001F2BE20

#define ADDR_strcmp 0x0000000001F27A80

#define ADDR_AimTarget_GetTagPos 0x00000000000AF9E0
#define ADDR_AimTarget_IsTargetVisible 0x00000000000AFC80
#define ADDR_CG_DrawRotatedPicPhysicalW 0x0000000000BF0300
#define ADDR_R_AddCmdDrawText 0x00000000011D3570
#define ADDR_R_TextHeight 0x0000000000356CB0
#define ADDR_R_TextWidth 0x0000000000356950
