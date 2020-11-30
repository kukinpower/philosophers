#include "philo_one.h"

void		ft_alloc_check(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("error: out of memory\n", 2);
		exit(1);
	}
}
