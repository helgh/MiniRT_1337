#include <stdio.h>

char	to_upper(char c)
{
	return (c -= 32);
}


int main()
{
	char	ptr[] = "hello";
	int 	i = -1;

	while (ptr[++i])
		ptr[i] = to_upper(ptr[i]);
	printf("%s\n", ptr);
}