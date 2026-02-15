#include "mem.h"
#include "closure.h"

static env_layout ENV_2_LAYOUT = {
	.payload_size = 8,
	.var_count = 2,
	.vars = {
		{.type=LITERAL, .offset=0, .size=4},
		{.type=LITERAL, .offset=4, .size=1},
	}
};
static env_layout ENV_DATA[] {
	ENV_0_LAYOUT,
	ENV_1_LAYOUT,
	ENV_2_LAYOUT,
	ENV_3_LAYOUT,
	ENV_4_LAYOUT,
	ENV_5_LAYOUT,
	ENV_6_LAYOUT,
};
