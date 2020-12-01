#include "philo_one.h"

void			error_fatal()
{
	ft_putstr_fd("error: fatal", 2);
	exit(1);
}

void		ft_alloc_check(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("error: out of memory\n", 2);
		exit(1);
	}
}
