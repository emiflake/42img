/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img_gen.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 16:28:06 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 16:49:09 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "image.h"

void	img_set_pixel(t_image *bmp, int x, int y, uint32_t pixel)
{
	*img_get_pixel(bmp, x, y) = pixel;
}

void		img_bmp_gen(t_image *img, const char *filename)
{
	int			fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return ;
	img_bmp_gen_fd(img, fd);
	close(fd);
}

void		img_gen(t_image *img, const char *filename)
{
	img_bmp_gen(img, filename);
}