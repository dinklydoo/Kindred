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
static struct_layout STRUCT_DATA[] {
	STRUCT_0_LAYOUT,
};
