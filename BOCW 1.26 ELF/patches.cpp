#include "patches.h"

#include "functions.h"

void ApplyPatches() {
	// no recoil (most guns)
	memcpy((void *)ResolveAddress(ADDR_Patch_BG_WeaponFireRecoil), "\xC3", 1);

	// reduce visual gun shake
	memcpy((void *)ResolveAddress(ADDR_Patch_GunShake1), "\x90\x90\x90\x90\x90\x90\x90", 7);
	memcpy((void *)ResolveAddress(ADDR_Patch_GunShake2), "\x90\x90\x90\x90\x90\x90\x90", 7);

	// all client godmode
	memcpy((void *)ResolveAddress(ADDR_Patch_AllClient_Godmode), IsInZombies() ? "\xC3" : "\x55", 1);

	// all client inf ammo
	//
	// add r14d, dword ptr [rbx + rdx*4 + 0x13DC]
	// ->
	// mov r14, 999
	memcpy((void *)ResolveAddress(ADDR_Patch_AllClient_InfAmmo), "\x49\xC7\xC6\xE7\x03\x00\x00\x90", 8);

	// return 1 for loot item quantity
	// 
	// xor eax, eax
	// inc eax
	// ret
	memcpy((void *)ResolveAddress(ADDR_Patch_UnlockAll), "\x31\xC0\xFF\xC0\xC3", 5);

	// return 12 for the class count (12 is max)
	// 
	// mov eax, 12
	// ret
	memcpy((void *)ResolveAddress(ADDR_Patch_MaxClasses), "\xB8\x0C\x00\x00\x00\xC3", 6);
}
