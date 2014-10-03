/*
 * Video.cpp
 *
 *  Created on: Jun 5, 2011
 *      Author: Fernando Felix do Nascimento Junior
 */

#include "Video.h"

LayeredFrame Video::mallocLFrame() {
	/* Memory clean */
	fflush(stderr);

	/* Layered Frame Memory Alloc	 */
	LayeredFrame frame = (LayeredFrame) malloc(layers * sizeof(DefaultFrame));

	int frameSize = getDFrameSize();

	for (register int i = 0; i < layers; i++)
		if (!(frame[i] = (DefaultFrame) malloc(frameSize * sizeof(Pixel)))) {
			fprintf(stderr, "ALOCACAO FALHOU\n");
			exit(1);
		}

	return frame;
}

void Video::readLFrame(int index) {
	fflush(stderr);

	char errortext[256];
	FILE *fd;

	/* Layered Frame Size */
	long size = (long) (getLFrameSize());

	/* Open file */
	if (!(fd = fopen(videoIN, "rb"))) {
		sprintf(errortext, "NAO PODE ABRIR %s\n", videoIN);
		exit(1);
	}

	/* Video Frame Init */
	long pos = size * index;

	/* Seek correct position.  Add buffer to file, if necessary */
	fseek(fd, pos, SEEK_SET);

	/* Y */
	for (register int i = 0; i < height; i++)
		fread(frameIN[0] + i * width, 1, width, fd);

	/* U */
	for (register int i = 0; i < height; i++)
		fread(frameIN[1] + i * width, 1, width, fd);

	/* V */
	for (register int i = 0; i < height; i++)
		fread(frameIN[2] + i * width, 1, width, fd);

	fclose(fd);
}

void Video::writeLFrame(int index) {

	FILE *fd;

	/* Layered Frame Size */
	long size = (long) (getLFrameSize());

	/* Open file */
	if (index == 0)
		fd = fopen(videoOUT, "wb");
	else
		fd = fopen(videoOUT, "r+b");
	if (!fd) {
		fprintf(stderr, "Video de entrada nao pode ser aberto.\n");
		exit(-1);
	}

	/* Video Frame Init */
	long pos = size * index;

	/* Seek correct position.  Add buffer to file, if necessary */
	fseek(fd, pos, SEEK_SET);

	/* Y */
	for (int i = 0; i < height; i++)
		fwrite(frameOUT[0] + i * width, 1, width, fd);
	/* Cb */
	for (int i = 0; i < height; i++)
		fwrite(frameOUT[1] + i * width, 1, width, fd);

	/* Cr */
	for (int i = 0; i < height; i++)
		fwrite(frameOUT[2] + i * width, 1, width, fd);

	fclose(fd);
}
