#include "mem.h"
#include "structs.h"

static struct_layout STRUCT_0_LAYOUT = {
	.payload_size = 24,
	.field_count = 3,
	.fields = {
		{.type=STRUCT, .offset=0, .size=8},
		{.type=STRUCT, .offset=8, .size=8},
		{.type=LITERAL, .offset=16, .size=4},
	}
};
struct_layout STRUCT_DATA[1];

void init_struct_layout(){
	STRUCT_DATA[0] = STRUCT_0_LAYOUT;
}