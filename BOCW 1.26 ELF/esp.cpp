#include "esp.h"

#include "aimbot.h"
#include "drawing.h"
#include "functions.h"
#include "math.h"
#include "structs.h"

NAMESPACE(ESP)

void DrawHealthBar(int i, float *screenPos, float *screenHeadPos) {
	const float *healthColor = (cg->clientInfo[i].health < (cg->clientInfo[i].maxHealth * 0.25f)) ? red10 : (cg->clientInfo[i].health < (cg->clientInfo[i].maxHealth * 0.8f)) ? yellow10 : green10;

	float entWidth = (screenPos[1] - screenHeadPos[1]) / 2 / 2;
	float barWidth = (entWidth / 5);

	if (barWidth > 6) {
		barWidth = 6;
	}

	DrawShader(screenPos[0] - entWidth - barWidth - 10, screenHeadPos[1], barWidth + 4, screenPos[1] - screenHeadPos[1], black08);
	DrawShader(screenPos[0] - entWidth - barWidth - 8, screenHeadPos[1] + ((screenPos[1] - screenHeadPos[1]) - (((screenPos[1] - screenHeadPos[1]) / cg->clientInfo[i].maxHealth) * cg->clientInfo[i].health)) + 2,
		barWidth, (((screenPos[1] - screenHeadPos[1]) / cg->clientInfo[i].maxHealth) * cg->clientInfo[i].health) - 4, healthColor);
}

void DrawBox(float *screenPos, float *screenHeadPos, const float *color) {
	float entWidth = (screenPos[1] - screenHeadPos[1]) / 2 / 2;

	DrawLine(screenPos[0] - entWidth, screenPos[1], screenPos[0] + entWidth, screenPos[1], 2.0f, color);
	DrawLine(screenPos[0] - entWidth, screenHeadPos[1], screenPos[0] + entWidth, screenHeadPos[1], 2.0f, color);
	DrawLine(screenPos[0] - entWidth, screenPos[1] + 1.0f, screenPos[0] - entWidth, screenHeadPos[1] - 1.0f, 2.0f, color);
	DrawLine(screenPos[0] + entWidth, screenPos[1] + 1.0f, screenPos[0] + entWidth, screenHeadPos[1] - 1.0f, 2.0f, color);
}

void DrawActors() {
	for (int i = 0; i < 2048; i++) {
		centity_t cent = &centity[i];
		if (!IsAlive(cent) || cent->nextState.eType != entityType_t::ET_ACTOR)
			continue;

		float dist = Distance(cg->refdef.vieworg, cent->origin);
		if (dist > DISTANCE_LIMIT_ESP) { // dont draw super far away
			continue;
		}

		float headPos[3];
		headPos[0] = cent->origin[0];
		headPos[1] = cent->origin[1];
		headPos[2] = cent->origin[2] + 74.0f;

		float screen[2];
		float screenHead[2];
		if (WorldToScreen(cent->origin, screen) && WorldToScreen(headPos, screenHead)) {
			const float *espColor = (IsZombieTurned(cent) ? green10 : (i == Aimbot::closestClientNumber ? white10 : red10));

			DrawBox(screen, screenHead, espColor);

			float fontSize = 0.8f - (0.8f / DISTANCE_LIMIT_ESP * dist);
			if (fontSize < 0.4f)
				fontSize = 0.4f;

			// draw name
			char temp[100];
			snprintf(temp, sizeof(temp), "Zombie [%.1f m]", dist * 0.0254f);
			DrawCenterTextWithBackgroundWithBorder(temp, screenHead[0], screenHead[1] - 2 - (R_TextHeight(FontDefault) * fontSize) / 2, white10, fontSize, black08, 2.0f, espColor);
		}
	}
}

void DrawPlayers() {
	for (int i = 0; i < cgs->maxClients; i++) {
		if (i == cg->clientNum)
			continue;

		centity_t cent = &centity[i];
		if (!IsAlive(cent) || cent->nextState.eType != entityType_t::ET_PLAYER) {
			continue;
		}

		float dist = Distance(cg->refdef.vieworg, cent->origin);
		if (dist > DISTANCE_LIMIT_ESP) { // dont draw super far away
			continue;
		}

		float headPos[3];
		headPos[0] = cent->origin[0];
		headPos[1] = cent->origin[1];
		headPos[2] = cent->origin[2] + 74.0f;

		float screen[2];
		float screenHead[2];
		if (WorldToScreen(cent->origin, screen) && WorldToScreen(headPos, screenHead)) {
			const float *espColor = (IsTeammate(i) ? green10 : (i == Aimbot::closestClientNumber ? white10 : red10));

			DrawBox(screen, screenHead, espColor);
			DrawHealthBar(i, screen, screenHead);

			float fontSize = 0.8f - (0.8f / DISTANCE_LIMIT_ESP * dist);
			if (fontSize < 0.4f)
				fontSize = 0.4f;

			// draw name
			char temp[100];
			snprintf(temp, sizeof(temp), "%s [%.1f m]", cg->clientInfo[i].name, dist * 0.0254f);
			DrawCenterTextWithBackgroundWithBorder(temp, screenHead[0], screenHead[1] - 2 - (R_TextHeight(FontDefault) * fontSize) / 2, white10, fontSize, black08, 2.0f, espColor);
		}
	}
}

END
