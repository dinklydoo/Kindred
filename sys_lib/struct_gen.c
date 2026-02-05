#include "mem.h"
#include "structs.h"

static struct_layout STRUCT_1_LAYOUT = {
	.payload_size = 24,
	.field_count = 3,
	.fields = {
		{.type=STRUCT, .offset=0},
		{.type=STRUCT, .offset=8},
		{.type=LITERAL, .offset=16},
	}
};
static struct_layout STRUCT_DATA[] {
	STRUCT_1_LAYOUT,
};
