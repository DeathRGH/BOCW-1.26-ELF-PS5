#include "aimbot.h"

#include "drawing.h"
#include "functions.h"
#include "math.h"
#include "structs.h"

NAMESPACE(Aimbot)

int closestClientNumber = -1;

bool PointIsInAimbotRect(float width, float height, float *point) {
	if ((point[0] < _4K((cg->refdef.width / 2) + (width / 2))) && (point[0] > _4K((cg->refdef.width / 2) - (width / 2)))) {
		if ((point[1] < _4K((cg->refdef.height / 2) + (height / 2))) && (point[1] > _4K((cg->refdef.height / 2) - (height / 2)))) {
			return true;
		}
	}

	return false;
}

int ClosestZombie() {
	int closestZombieNum = -1;
	float dist = 0.0f;

	for (int i = 0; i < 2048; i++) {
		centity_t cent = &centity[i];

		if (cent->nextState.eType != ET_ACTOR || !IsAlive(cent) || IsZombieTurned(cent) || IsZombieSpawning(cent))
			continue;

		float curDist = Distance(cg->refdef.vieworg, cent->origin);
		if (curDist > DISTANCE_LIMIT_AIMBOT) { // ignore far away
			continue;
		}

		if (!AimTarget_IsTargetVisible(LocalClientNum_t::LOCAL_CLIENT_0, cent)) {
			continue;
		}

		float aimBonePos[3];
		AimTarget_GetTagPos(cent, aimBonePos);

		float screenPoint[2];
		if (WorldToScreen(aimBonePos, screenPoint)) {
			if (PointIsInAimbotRect(750.0f, 1050.0f, screenPoint)) {
				if (dist == 0.0f) {
					dist = curDist;
					closestZombieNum = i;
				}
				else {
					if (dist > curDist) {
						dist = curDist;
						closestZombieNum = i;
					}
				}
			}
		}
	}

	return closestZombieNum;
}

int ClosestClient() {
	int closestClientNum = -1;
	float dist = 0.0f;

	for (int i = 0; i < cgs->maxClients; i++) {
		if (i == cg->clientNum || IsTeammate(i))
			continue;

		centity_t cent = &centity[i];
		if (!IsAlive(cent) || cent->nextState.eType != entityType_t::ET_PLAYER)
			continue;

		float curDist = Distance(cg->refdef.vieworg, cent->origin);
		if (curDist > DISTANCE_LIMIT_AIMBOT) { // ignore far away
			continue;
		}

		if (!AimTarget_IsTargetVisible(LocalClientNum_t::LOCAL_CLIENT_0, cent)) {
			continue;
		}

		float aimBonePos[3];
		AimTarget_GetTagPos(cent, aimBonePos);

		float screenPoint[2];
		if (WorldToScreen(aimBonePos, screenPoint)) {
			if (PointIsInAimbotRect(750.0f, 1050.0f, screenPoint)) {
				if (dist == 0.0f) {
					dist = curDist;
					closestClientNum = i;
				}
				else {
					if (dist > curDist) {
						dist = curDist;
						closestClientNum = i;
					}
				}
			}
		}
	}

	return closestClientNum;
}

void Aimbot() {
	closestClientNumber = -1;
	closestClientNumber = IsInZombies() ? ClosestZombie() : ClosestClient();

	centity_t self = &centity[cg->clientNum];
	centity_t cent = &centity[closestClientNumber];

	if (!(self->nextState.lerp.eFlags & eFlag_t::ENTITY_FLAG_ADS) || closestClientNumber == -1) {
		return;
	}

	float aimBonePos[3];
	AimTarget_GetTagPos(cent, aimBonePos);

	aimBonePos[0] -= cg->refdef.vieworg[0];
	aimBonePos[1] -= cg->refdef.vieworg[1];
	aimBonePos[2] -= cg->refdef.vieworg[2];

	float newAngles[3];
	VectorToAngles(aimBonePos, newAngles);

	newAngles[0] -= clientActive->deltaAngles[0];
	newAngles[1] -= clientActive->deltaAngles[1];

	clientActive->viewangles[0] = newAngles[0];
	clientActive->viewangles[1] = newAngles[1];
}

END
