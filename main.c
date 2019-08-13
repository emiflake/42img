#include "inc/image.h"
#include <stdio.h>

int main(void)
{
	t_image		*img;
	u_int32_t	*pix;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	printf("Opening 'image.bmp'\n");
	img = img_read("image.bmp");
	if (!img)
		perror("Failed to load 'image.bmp'");
	printf("Loaded image: [%hd BPP] %d x %d.\n", img->bpp, img->width, img->height);

	img_gen(img, "copy.bmp");

	img_free(&img);
	printf("Freeing\n");
	return (0);
}
