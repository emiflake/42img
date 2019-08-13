/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap_parse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 23:07:11 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 00:32:17 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
# include <stdio.h>

#include "bitmap.h"

/*
** Skip at most n 1024 bytes
*/

static void	fdskip(int fd, size_t bytes)
{
	char buf[1024];
	
	if (bytes > 1024)
		perror("Can't skip more than 1024 bytes");
	read(fd, buf, bytes);
}

static int	read_bytes(t_bitmap *out, int fd)
{
	uint32_t	color;
	int			x;
	int			y;
	int			i;

	out->raw_pixels = (char*)malloc(out->bpp / 8 * out->width * out->height);
	if (!out->raw_pixels)
		return (3);
	y = out->height - 1;
	i = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < out->width)
		{
			color = 0;
			read(fd, &color, out->bpp / 8);
			*img_get_pixel(out, x, y) = color;
			i++;
			x++;
		}
		y--;
		fdskip(fd, out->width * out->bpp / 8 % 4);
	}
	return (0);
}

/*
** Return types:
** - 1 => Unexpected / Malformed input
** - 2 => Issue with bitmap
** - 0 => Success 
*/
int			img_bmp_parse(t_bitmap *out, int fd)
{
	char		header_buf[2];
	uint32_t	reading_offset;
	
	if (read(fd, header_buf, 2) != 2 
		|| header_buf[0] != 'B' || header_buf[1] != 'M')
		return (1);
	read(fd, &out->size, 4);
	fdskip(fd, 4);
	read(fd, &reading_offset, 4);
	fdskip(fd, 4);
	read(fd, &out->width, 4);
	read(fd, &out->height, 4);
	// printf("%d x %d\n", out->width, out->height);
	fdskip(fd, 2);
	read(fd, &out->bpp, 2);
	// printf("BPP: %d\n", out->bpp);
	// Our current position in file: 30bytes
	fdskip(fd, reading_offset - 30);
	if (read_bytes(out, fd) != 0)
		return (2);
	return (0);
}