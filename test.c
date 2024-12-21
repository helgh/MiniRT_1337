#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (fabs(-4.00002 - 4.00002) < 0.00001)
		printf("ok\n");
	else
		printf("ko\n");
}
