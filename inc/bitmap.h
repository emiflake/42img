/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 22:49:31 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 00:06:22 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <stdint.h>

/*
** The basic representation of a bitmap that has been read
*/
typedef struct	s_bitmap
{
	int			size;

	int			width;
	int			height;

	char		*raw_pixels;

	uint16_t	bpp;
}				t_bitmap;


/*
** Read a bitmap from a file
** ----
** Uses the BMP format
** ref. https://en.wikipedia.org/wiki/BMP_file_format
*/
t_bitmap	*img_read_bmp_fd(int fd);

/*
** Helper function, opens file
*/
t_bitmap	*img_read_bmp(const char *filename);

/*
** Even more automatic helper function
*/
t_bitmap	*img_read(const char *filename);


int			img_bmp_parse(t_bitmap *out, int fd);

uint32_t	*img_get_pixel(t_bitmap *bmp, int x, int y);

#endif