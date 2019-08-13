/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 22:49:31 by nmartins       #+#    #+#                */
/*   Updated: 2019/08/13 16:30:04 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>

/*
** The basic representation of a bitmap that has been read
*/
typedef struct	s_image
{
	int			size;

	int			width;
	int			height;

	char		*raw_pixels;

	uint16_t	bpp;
}				t_image;


/*
** Read a bitmap from a file
** ----
** Uses the BMP format
** ref. https://en.wikipedia.org/wiki/BMP_file_format
*/
t_image	*img_read_bmp_fd(int fd);

/*
** Helper function, opens file
*/
t_image	*img_read_bmp(const char *filename);

/*
** Even more automatic helper function
*/
t_image	*img_read(const char *filename);


int			img_bmp_parse(t_image *out, int fd);

uint32_t	*img_get_pixel(t_image *bmp, int x, int y);

void		img_free(t_image **bmp);

void		img_set_pixel(t_image *bmp, int x, int y, uint32_t pixel);

void		img_bmp_gen_fd(t_image *img, int fd);
void		img_bmp_gen(t_image *img, const char *filename);
void		img_gen(t_image *img, const char *filename);

#endif