#include "header.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main()
{
    long    x;
    x = ft_get_time();
    printf("%ld", x);
}
