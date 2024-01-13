#pragma once

#include "addresses.h"
#include "global.h"
#include "sparse.h"

enum LocalClientNum_t : int {
	INVALID_LOCAL_CLIENT = -1,
	LOCAL_CLIENT_0 = 0,
	LOCAL_CLIENT_FIRST = 0,
	LOCAL_CLIENT_KEYBOARD_AND_MOUSE = 0,
	LOCAL_CLIENT_1 = 1,
	LOCAL_CLIENT_2 = 2,
	LOCAL_CLIENT_3 = 3,
	LOCAL_CLIENT_COUNT = 5,
};

enum eFlag_t {
	ENTITY_FLAG_ADS = 0x4000
};

enum entityType_t : short {
	ET_GENERAL = 0x00,
	ET_PLAYER = 0x01,
	ET_MISSILE = 0x04,
	ET_SCRIPTMOVER = 0x06,
	ET_VEHICLE = 0x0C,
	ET_ACTOR = 0x0F,
	ET_ACTOR_SPAWNER = 0x10,
	ET_ACTOR_CORPSE = 0x11,
	ET_ZBARRIER = 0x13,
};

struct ScreenPlacement { //size = 0x74
	float scaleVirtualToReal[2];	//0x00
	float scaleVirtualToFull[2];	//0x08
	float scaleRealToVirtual[2];	//0x10
	float virtualViewableMin[2];	//0x18
	float virtualViewableMax[2];	//0x20
	float virtualTweakableMin[2];	//0x28
	float virtualTweakableMax[2];	//0x30
	float realViewportBase[2];		//0x38
	float realViewportSize[2];		//0x40
	float realViewportMid[2];		//0x48
	float realViewableMin[2];		//0x50
	float realViewableMax[2];		//0x58
	float realTweakableMin[2];		//0x60
	float realTweakableMax[2];		//0x68
	float hudSplitscreenScale;		//0x70
};

#define ScrPlace (ScreenPlacement *)ResolveAddress(ADDR_ScrPlace)
#define MaterialWhite *(uint64_t *)ResolveAddress(ADDR_MaterialWhite)
#define FontDefault *(uint64_t *)ResolveAddress(ADDR_FontDefault)

TYPE_BEGIN(struct UiContext_s, 0x2C); // size unknown
TYPE_FIELD(int screenX, 0x00);
TYPE_FIELD(int screenY, 0x04);
TYPE_FIELD(int screenWidth, 0x0C);
TYPE_FIELD(int screenHeight, 0x10);
TYPE_FIELD(int screenWidth2, 0x14);
TYPE_FIELD(int screenHeight2, 0x18);
TYPE_FIELD(bool isWideScreen, 0x1C);
TYPE_FIELD(bool isFullscreen, 0x1D);
TYPE_FIELD(float aspectRatio, 0x20);
TYPE_END();

typedef struct UiContext_s *UiContext_t;
extern UiContext_t UiContext;

TYPE_BEGIN(struct GfxCameraData_t, 0x40); // size unknown
TYPE_FIELD(int cFlags, 0x00);
TYPE_FIELD(float focalLength, 0x04);
TYPE_FIELD(float focalDistance, 0x08);
TYPE_FIELD(float fstop, 0x0C);
TYPE_FIELD(float shutter, 0x10);
TYPE_FIELD(float iso, 0x14);
TYPE_FIELD(float EV, 0x18);
TYPE_FIELD(float EVcomp, 0x1C);
TYPE_FIELD(float filmCropFactor, 0x20);
TYPE_FIELD(float filmISO_min, 0x24);
TYPE_FIELD(float filmISO_max, 0x28);
TYPE_FIELD(float filmISO_noise, 0x2C);
TYPE_FIELD(float fAdsBlur, 0x30);
TYPE_FIELD(float fAdsScopeBlurStart, 0x34);
TYPE_FIELD(float fAdsScopeBlurAmount, 0x38);
TYPE_FIELD(float mbStrength, 0x3C);
TYPE_END();

TYPE_BEGIN(struct refdef_t, 0x1ED9F8); // size unknown
TYPE_FIELD(int width, 0x0C);
TYPE_FIELD(int height, 0x10);
TYPE_FIELD(int sceneResolutionIndex, 0x24);
TYPE_FIELD(float tanHalfFovX, 0x28);
TYPE_FIELD(float tanHalfFovY, 0x2C);
TYPE_FIELD(float maincamTanHalfFovY, 0x30);
TYPE_FIELD(float fov_x, 0x34);
TYPE_FIELD(float vieworg[3], 0x38);
TYPE_FIELD(float viewaxis[3][3], 0x44);
TYPE_FIELD(int sceneResolutionIndexHistory[4], 0x74);
TYPE_FIELD(GfxCameraData_t gfxCameraData, 0x84);
TYPE_FIELD(int frametime, 0xE8);
TYPE_FIELD(int time, 0xEC);
TYPE_END();

TYPE_BEGIN(struct clientInfo_t, 0x4A8);
TYPE_FIELD(int clientNum, 0x00);
TYPE_FIELD(int team, 0x04);
TYPE_FIELD(short health, 0x3BC);
TYPE_FIELD(short maxHealth, 0x3BE);
TYPE_FIELD(char name[32], 0x3C8);
TYPE_END();

TYPE_BEGIN(struct cg_s, 0x8C85F0);
TYPE_FIELD(int clientNum, 0x08);
TYPE_FIELD(int localClientNum, 0x0C);
TYPE_FIELD(float origin[3], 0xE48);
TYPE_FIELD(float viewAngles[3], 0xE6C);
TYPE_FIELD(clientInfo_t clientInfo[40], 0xA8DE0);
TYPE_FIELD(refdef_t refdef, 0x1C31DC);
TYPE_END();

typedef struct cg_s *cg_t;
extern cg_t cg;

TYPE_BEGIN(struct cgs_s, 0xFFFF); // size unknown
TYPE_FIELD(int screenWidth, 0x08);
TYPE_FIELD(int screenHeight, 0x0C);
TYPE_FIELD(float aspectRatio, 0x10);
TYPE_FIELD(char gametype[0x20], 0x2D);
TYPE_FIELD(char hostname[0x20], 0x51);
TYPE_FIELD(int maxClients, 0x154);
TYPE_FIELD(char mapname_d3dbsp[0x40], 0x15C);
TYPE_FIELD(char mapname[0x20], 0x19C);
TYPE_END();

typedef struct cgs_s *cgs_t;
extern cgs_t cgs;

TYPE_BEGIN(struct LerpEntityState_t, 0xF0); // size unknown
TYPE_FIELD(int eFlags, 0x00);
TYPE_FIELD(int eFlags2, 0x04);
TYPE_FIELD(float origin[3], 0x08);
TYPE_FIELD(float viewAngles[3], 0x2C);
TYPE_END();

TYPE_BEGIN(struct entityState_t, 0x208); // size unknown
TYPE_FIELD(int number, 0x00);
TYPE_FIELD(LerpEntityState_t lerp, 0x08);
TYPE_FIELD(int weapon, 0x70);
TYPE_FIELD(short eType, 0x282);
TYPE_FIELD(short groundEntityNum, 0x286);
TYPE_END();

TYPE_BEGIN(struct centity_s, 0x1020);
TYPE_FIELD(float origin[3], 0x38);
TYPE_FIELD(float viewAngles[3], 0x44);
TYPE_FIELD(int state, 0x488);
TYPE_FIELD(int stateFlag, 0x560);
TYPE_FIELD(int weapon, 0x4F0); // ?
TYPE_FIELD(entityState_t nextState, 0x580);
TYPE_FIELD(int model, 0x810);
TYPE_FIELD(int alive, 0x1014);
TYPE_END();

typedef struct centity_s *centity_t;
extern centity_t centity;

TYPE_BEGIN(struct game_button_bits_t, 0x0C);
TYPE_FIELD(int _array[3], 0x00);
TYPE_END();

TYPE_BEGIN(struct usercmd_t, 0x88);
TYPE_FIELD(int serverTime, 0x00);
TYPE_FIELD(game_button_bits_t button_bits, 0x08);
TYPE_FIELD(int angles[3], 0x20); // not sure, could be 0x2C
TYPE_FIELD(char forwardmove, 0x4D);
TYPE_FIELD(char rightmove, 0x4E);
TYPE_FIELD(int weapon, 0x68);
TYPE_END();

TYPE_BEGIN(struct clientActive_s, 0xBE5D0);
TYPE_FIELD(float deltaAngles[3], 0xE40);
TYPE_FIELD(float mapname[0x40], 0x2EFC);
TYPE_FIELD(float viewangles[3], 0x315C);
TYPE_FIELD(usercmd_t cmds[128], 0x31A0);
TYPE_FIELD(int cmdNumber, 0x7584);
TYPE_END();

typedef struct clientActive_s *clientActive_t;
extern clientActive_t clientActive;

void ReadStructs();

bool IsAlive(centity_t cent);
bool IsZombieSpawning(centity_t cent);
bool IsZombieTurned(centity_t cent);
bool IsTeammate(int i);

bool IsInZombies();
