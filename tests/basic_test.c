#include "cdl.h"

typedef int add_t(
    __in int x,
    __in int y
);

add_t* addo = NULL;

int add(
    __in int x,
    __in int y
)
{
	printf("Inside original function\n");
	return x + y;
}

int add_detour(
    __in int x,
    __in int y
)
{
    printf("Inside detour function\n");
    return addo(5,5);
}

int main(
    __in void
)
{
	struct cdl_jmp_patch jmp_patch = {};
	addo = (add_t*)add;

	printf("Before attach: \n");
	printf("add(1,1) = %i\n\n", add(1,1));

	jmp_patch = cdl_jmp_attach((void**)&addo, add_detour);
	if(jmp_patch.active)
	{
		printf("After attach: \n");
		printf("add(1,1) = %i\n\n", add(1,1));
		printf("== DEBUG INFO ==\n");
		cdl_jmp_dbg(&jmp_patch);
	}

	cdl_jmp_detach(&jmp_patch);
	printf("\nAfter detach: \n");

	printf("add(1,1) = %i\n\n", add(1,1));

	//////////////////////////////////////////////////////////////////////


	struct cdl_swbp_patch swbp_patch = {};
	addo = (add_t*)add;

	printf("Before attach: \n");
	printf("add(1,1) = %i\n\n", add(1,1));

	swbp_patch = cdl_swbp_attach((void**)&addo, add_detour);
	if(swbp_patch.active)
	{
		printf("After attach: \n");
		printf("add(1,1) = %i\n\n", add(1,1));
		printf("== DEBUG INFO ==\n");
		cdl_swbp_dbg(&swbp_patch);
	}

	cdl_swbp_detach(&swbp_patch);
	printf("\nAfter detach: \n");

	printf("add(1,1) = %i\n\n", add(1,1));

	return 0;
}
