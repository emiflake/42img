/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img_bmp_gen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 16:24:16 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 18:12:10 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "image.h"

static const char g_bitmap_header[2] = "BM";

void		write_null(int fd, size_t len)
{
	const static char null_buff[1024] = {};

	if (len > 1024)
		perror("Cannot write more than 1024 null bytes");
	write(fd, null_buff, len);
}

static void	write_bytes(t_image *img, int fd)
{
	uint32_t	color;
	int			x;
	int			y;
	int			i;

	y = img->height;
	i = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < img->width)
		{
			color = *img_get_pixel(img, x, y);
			write(fd, &color, img->bpp / 8);
			i++;
			x++;
		}
		y--;
		write_null(fd, img->width * img->bpp / 8 % 4);
	}
}

void		write_size_bitmap(t_image *img, int fd)
{
	const int size_row = img->width * img->bpp / 8 + img->width * img->bpp / 8 % 4;
	const int size_bitmap = size_row * img->height;

	write(fd, &size_bitmap, 4);
}

int			calculate_size(t_image *img)
{
	const int size_row = img->width * img->bpp / 8 + img->width * img->bpp / 8 % 4;
	int	size;

	size = 54;
	size += size_row * img->height;
	return (size);
}

void		img_bmp_gen_fd(t_image *img, int fd)
{
	const int		reading_offset = 54;
	const int		num_bytes = 40;
	const short		plane = 1;
	const int		size = calculate_size(img);

	write(fd, g_bitmap_header, 2);
	write(fd, &size, 4);
	write_null(fd, 4);
	write(fd, &reading_offset, 4);
	write(fd, &num_bytes, 4);
	write(fd, &img->width, 4);
	write(fd, &img->height, 4);
	write(fd, &plane, 2);
	write(fd, &img->bpp, 2);
	write_null(fd, 4);
	write_size_bitmap(img, fd);
	write_null(fd, 16);
	write_bytes(img, fd);
}