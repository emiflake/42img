/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 22:49:51 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 00:13:44 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "bitmap.h"

uint32_t	*img_get_pixel(t_bitmap *bmp, int x, int y)
{
	return ((uint32_t*)&bmp->raw_pixels[(bmp->bpp / 8) * (bmp->width * y + x)]);
}

t_bitmap	*img_read_bmp_fd(int fd)
{
	t_bitmap	*bmp;

	bmp = (t_bitmap*)malloc(sizeof(t_bitmap));
	if (!bmp)
		return (NULL);
	if (img_bmp_parse(bmp, fd) != 0)
		return (NULL);
	return (bmp);
}

t_bitmap	*img_read_bmp(const char *str)
{
	int			fd;
	t_bitmap	*bmp;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bmp = img_read_bmp_fd(fd);
	close(fd);

	return (bmp);
}

t_bitmap	*img_read(const char *str)
{
	return (img_read_bmp(str));
}