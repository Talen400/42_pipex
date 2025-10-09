#include <stdio.h>
#include <stdlib.h>

int main()
{
	int	c;

	while ((c = getchar()) != EOF)
	{
		if (putchar(c) == EOF)
		{
			break;
		}
	}
	return (0);
}
