#include <stdint.h>
#include <stdarg.h>

#include "aimbot.h"
#include "drawing.h"
#include "esp.h"
#include "functions.h"
#include "global.h"
#include "math.h"
#include "patches.h"
#include "structs.h"

void Draw() {
	if (IsInZombies()) {
		ESP::DrawActors();
	}
	ESP::DrawPlayers();

	DrawAimbotRect(750.0f, 1050.0f);
}

void ReadBaseAddress(uint64_t basePtr) {
	baseAddress = *(uint64_t *)basePtr;
}

void Run(uint64_t basePtr) {
	ReadBaseAddress(basePtr);

	InitFunctions();
	ReadStructs();

	ApplyPatches();
	
	if (!IsInGame()) {
		return;
	}

	Aimbot::Aimbot();
	Draw();
}

// ##########################################################################################
// Do NOT modify any code in here unless you know what you are doing                        #
// The elf loader uses some hardcoded addresses in this function                            #
//                                                                                          #
extern "C" void _main(void) { //                                                            #
	asm("lea rax, [rip + 6]"); // load address of base address pointer into rax             #
	asm("jmp [rip + 8]"); // later replaced in elf loader with realtive jump                #
	asm("nop"); // dummy nops for base address storage                                      #
	asm("nop"); //                                                                          #
	asm("nop"); //                                                                          #
	asm("nop"); //                                                                          #
	asm("nop"); //                                                                          #
	asm("nop"); //                                                                          #
	asm("nop"); //                                                                          #
	asm("nop"); //                                                                          #
	register uint64_t rax asm("rax"); // read register value (pointer to base address)      #
	Run(rax); //                                                                            #
} //                                                                                        #
//                                                                                          #
// ##########################################################################################
