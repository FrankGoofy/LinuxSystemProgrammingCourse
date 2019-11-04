#include <stdlib.h>
#include <stdio.h>

static void __attribute__ ((constructor)) before_main(void)
{
printf("Running brfore main!\n");
}

int mian()
{
printf("main!\n");
return 0;
}
