#include <stdio.h>
#include "duktape.h"
#include "duk_console.h"

int main(int argc, char *argv[]) {
	duk_context *ctx;
	int i;

	ctx = duk_create_heap_default();
	if (!ctx) {
		return 1;
	}

	duk_console_init(ctx, DUK_CONSOLE_PROXY_WRAPPER /*flags*/);

	for (i = 1; i < argc; i++) {
		printf("Evaling: %s\n", argv[i]);
		(void) duk_peval_string(ctx, argv[i]);
		printf("--> %s\n", duk_safe_to_string(ctx, -1));
		duk_pop(ctx);
	}

	printf("Done\n");
	duk_destroy_heap(ctx);
	return 0;
}
