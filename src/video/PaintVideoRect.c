/*
 * PaintVideoRect.c
 *
 *  Created on: 2019年12月13日
 *      Author: xwr
 */
#include "paintRect.h"
int  DrawVideoDisplayRect() {
	int fp = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long screensize = 0;
	char *fbp = NULL;
	int i;
	fp = open("/dev/fb0", O_RDWR);
	if (fp < 0) {
		printf("Error : Can not open framebuffer device/n");
		exit(1);
	}

	if (ioctl(fp, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information/n");
		exit(2);
	}

	if (ioctl(fp, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable information/n");
		exit(3);
	}
	screensize = finfo.smem_len;
	fbp = (char*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp,
			0);
	if ((int) fbp == -1) {
		printf("Error: failed to map framebuffer device to memory./n");
		exit(4);
	}
	printf("Get virt mem = %p\n", fbp);
	const int bytesPerPixel = 4;
	const int stride = finfo.line_length / bytesPerPixel;
	int end_x = 660, end_y = 395;
	int start_x = 140;
	int start_y = 5;
	int *dest = (int*) (fbp) + (start_y + vinfo.yoffset) * stride
			+ (start_x + vinfo.xoffset);
	int j;
	for (j = 0; j < end_y - start_y; j++) {
		for (i = 0; i < end_x - start_x; i++)
			*dest++ = 0;
		dest += 800 - end_x + start_x;
	}
	munmap(fbp, screensize);
	close(fp);
	return 0;
}
