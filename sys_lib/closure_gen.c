#include "mem.h"
#include "closure.h"

static env_layout ENV_0_LAYOUT = {
	.payload_size = 8,
	.var_count = 2,
	.vars = {
		{.type=LITERAL, .offset=0, .size=4},
		{.type=LITERAL, .offset=4, .size=4},
	}
};
env_layout ENV_DATA[1];

void init_env_layout(){
	ENV_DATA[0] = ENV_0_LAYOUT;
}