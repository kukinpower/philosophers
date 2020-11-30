#include "philo_one.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	d_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	d_len = dst_len;
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (dst_len < dstsize - 1 && src[i])
	{
		dst[dst_len] = src[i];
		i++;
		dst_len++;
	}
	dst[dst_len] = 0;
	return (d_len + src_len);
}