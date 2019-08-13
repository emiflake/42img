/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img_read.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 22:49:51 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 16:32:28 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "image.h"

uint32_t	*img_get_pixel(t_image *bmp, int x, int y)
{
	return ((uint32_t*)&bmp->raw_pixels[(bmp->bpp / 8) * (bmp->width * y + x)]);
}

t_image	*img_read_bmp_fd(int fd)
{
	t_image	*bmp;

	bmp = (t_image*)malloc(sizeof(t_image));
	if (!bmp)
		return (NULL);
	if (img_bmp_parse(bmp, fd) != 0)
		return (NULL);
	return (bmp);
}

t_image	*img_read_bmp(const char *str)
{
	int			fd;
	t_image	*bmp;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bmp = img_read_bmp_fd(fd);
	close(fd);
	return (bmp);
}

t_image	*img_read(const char *str)
{
	return (img_read_bmp(str));
}

void		img_free(t_image **bmp)
{
	free((*bmp)->raw_pixels);
	free(*bmp);
	*bmp = 0;
}