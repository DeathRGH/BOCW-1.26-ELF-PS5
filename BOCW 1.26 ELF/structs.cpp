#include <stdint.h>

#include "structs.h"
#include "functions.h"

UiContext_t UiContext;
cg_t cg;
cgs_t cgs;
centity_t centity;
clientActive_t clientActive;

void ReadStructs() {
	UiContext = (UiContext_t)ResolveAddress(ADDR_UiContext);
	cg = (cg_t)(*(uint64_t *)ResolveAddress(ADDR_cg));
	cgs = (cgs_t)(*(uint64_t *)ResolveAddress(ADDR_cgs));
	centity = (centity_t)(*(uint64_t *)ResolveAddress(ADDR_centity));
	clientActive = (clientActive_t)(*(uint64_t *)ResolveAddress(ADDR_clientActive));
}

bool IsAlive(centity_t cent) {
	if (IsInZombies) {
		return cent->alive != 0 && !(cent->state & 0x8000);
	}
	else {
		return cent->alive != 0;
	}
}

bool IsZombieSpawning(centity_t cent) {
	return cent->state & 0x80;
}

bool IsZombieTurned(centity_t cent) {
	return cent->alive & 0x20;
}

bool IsTeammate(int i) {
	if (i == cg->clientNum)
		return true;

	if (cg->clientInfo[i].team == cg->clientInfo[cg->clientNum].team)
		return true;

	return false;
}

bool IsInZombies() {
	if (!cgs) {
		return false;
	}

	return !strcmp(cgs->gametype, "zclassic") || !strcmp(cgs->gametype, "zsurvival") || !strcmp(cgs->gametype, "zonslaught") || !strcmp(cgs->gametype, "zonslaught_containment");
}
