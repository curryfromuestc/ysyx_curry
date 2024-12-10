#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->F, 2, LD0, LD1);
	nvboard_bind_pin( &top->Y, 2, SW0, SW1);
	nvboard_bind_pin( &top->X0, 2, SW2, SW3);
	nvboard_bind_pin( &top->X1, 2, SW4, SW5);
	nvboard_bind_pin( &top->X2, 2, SW6, SW7);
	nvboard_bind_pin( &top->X3, 2, SW8, SW9);
}
