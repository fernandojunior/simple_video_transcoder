/*
 * MedianReduction.cpp
 *
 *  Created on: Aug 15, 2011
 *      Author: fernando felix do Nascimento Junior
 */

#include "MedianReduction.h"

Frame MedianReduction::mallocFrame(int layers, int width, int height) {
	// limpando Memoria
	fflush(stderr);

	// alocando as camadas (3) de um frame na memoria
	Frame frame = (Frame) malloc(layers * sizeof(SimpleFrame));

	// alocando pixeis em todas as camas do frame, de acordo com o tamanho do frame (width * height) do video
	for (register int i = 0; i < layers; i++)
		if (!(frame[i] = (SimpleFrame) malloc(width * height * sizeof(Pixel)))) {
			fprintf(stderr, "ALOCACAO FALHOU\n");
			exit(1);
		}

	return frame;
}

void MedianReduction::readFrame(int index) {
	fflush(stderr);

	char errortext[256];
	FILE *fd;

	// abrindo arquivo (video) de entrada
	if (!(fd = fopen(inputVideo, "rb"))) {
		sprintf(errortext, "NAO PODE ABRIR %s\n", inputVideo);
		exit(1);
	}

	// posicao do frame do video de entrada na memoria (serial), de acordo com o indice 'index' passado como parametro
	long pos = frameSizeLWH * index;

	// seek correct position. Add buffer to file, if necessary
	fseek(fd, pos, SEEK_SET);

	/* Y */
	for (register int i = 0; i < height; i++)
		fread(inFrame[0] + i * width, 1, width, fd);

	/* U */
	for (register int i = 0; i < height; i++)
		fread(inFrame[1] + i * width, 1, width, fd);

	/* V */
	for (register int i = 0; i < height; i++)
		fread(inFrame[2] + i * width, 1, width, fd);

	fclose(fd);
}

void MedianReduction::writeFrame(int layers, int width, int height, int index) {

	FILE *fd;

	// tamanho total de um frame que possui mais de uma camada = layers * width * height
	long size = layers * width * height;

	// abrindo arquivo (video) de saida
	if (index == 0)
		fd = fopen(outputVideo, "wb");
	else
		fd = fopen(outputVideo, "r+b");
	if (!fd) {
		fprintf(stderr, "Video de saida nao pode ser criado.\n");
		exit(-1);
	}

	// posicao do frame do video de entrada na memoria (serial), de acordo com o indice 'index' passado como parametro
	long pos = size * index;

	// seek correct position.  Add buffer to file, if necessary
	fseek(fd, pos, SEEK_SET);

	/* Y */
	for (int i = 0; i < height; i++)
		fwrite(outFrame[0] + i * width, 1, width, fd);
	/* Cb */
	for (int i = 0; i < height; i++)
		fwrite(outFrame[1] + i * width, 1, width, fd);

	/* Cr */
	for (int i = 0; i < height; i++)
		fwrite(outFrame[2] + i * width, 1, width, fd);

	fclose(fd);

}

void MedianReduction::run(int windowSize, int type) {

	// alocacao de memoria temporaria que sera utilizada para cada frame do video de entrada (original)
	inFrame = mallocFrame(3, width, height);

	// alocacao de memoria temporaria que sera utilizada para cada frame do video de saida (final)
	outFrame = mallocFrame(3, width / 2, height / 2);

	// frame loop
	for (register int iF = 0; iF < frames; iF++) {
		readFrame(iF);

		// layer loop
		for (register int iL = 0; iL < layers; iL++)

			// height loop
			for (register int iH = 0; iH < height; iH++)

				// width loop
				for (register int iW = 0; iW < width; iW++)
					if (iW % 2 == 0 && iH % 2 == 0) {

						// acessando o endereco da memoria do pixel do frame do video de saida
						Pixel *iP = getPixel(outFrame, width / 2, iL, iW / 2,
								iH / 2);

						// gravando o valor do pixel com base no pixel mediano da janela do frame do video de entrada
						*iP = getMedian(windowSize, type, iL, iW, iH);
					}

		writeFrame(layers, width / 2, height / 2, iF);
	}

}

int MedianReduction::getMedian(int windowSize, int type, int iL, int iW, int iH) {

	switch (windowSize) {
	case 2:
		return median2x2(type, iL, iW, iH);
	case 3:
		return median3x3(type, iL, iW, iH);
	case 4:
		return median4x4(type, iL, iW, iH);
	case 5:
		return median5x5(type, iL, iW, iH);
	default:
		throw new _IO_FILE;
	}

}

int MedianReduction::getMedian(int type, int window[], int windowSize) {

	switch (type) {
	case 0:
		return Math::normalMedian(window, windowSize);
	case 1:
		return Math::quickSelectMedian(window, windowSize);
	case 2:
		return Math::wirthMedian(window, windowSize);
	case 3:
		return Math::torbenMedian(window, windowSize);
	default:
		throw new _IO_FILE;
	}

}

int MedianReduction::median2x2(int type, int iL, int iW, int iH) {

	if (iW != (width - 1) || iH != (height - 1)) {

		int size = 4;

		int window[size];

		window[0] = *getPixel(inFrame, iL, iW, iH);
		window[1] = *getPixel(inFrame, iL, iW, iH + 1);
		window[2] = *getPixel(inFrame, iL, iW + 1, iH);
		window[3] = *getPixel(inFrame, iL, iW + 1, iH + 1);

		return getMedian(type, window, size);

	}

	if (iW == (width - 1) || iH == (height - 1))
		return *getPixel(inFrame, iL, iW, iH);

	throw new _IO_FILE;

}

int MedianReduction::median3x3(int type, int iL, int iW, int iH) {

	if (iW != 0 && iH != 0 && iW != (width - 2) && iH != (height - 2)) {

		int size = 9;

		int window[size];

		window[0] = *getPixel(inFrame, iL, iW - 1, iH - 1);
		window[1] = *getPixel(inFrame, iL, iW, iH - 1);
		window[2] = *getPixel(inFrame, iL, iW + 1, iH - 1);

		window[3] = *getPixel(inFrame, iL, iW - 1, iH);
		window[4] = *getPixel(inFrame, iL, iW, iH); //pixel corrente
		window[5] = *getPixel(inFrame, iL, iW + 1, iH);

		window[6] = *getPixel(inFrame, iL, iW - 1, iH + 1);
		window[7] = *getPixel(inFrame, iL, iW, iH + 1);
		window[8] = *getPixel(inFrame, iL, iW + 1, iH + 1);

		return getMedian(type, window, size);
	}

	if (iW == 0 || iH == 0 || iW == (width - 2) || iH == (height - 2))
		return *getPixel(inFrame, iL, iW, iH);

	throw new _IO_FILE;

}

int MedianReduction::median4x4(int type, int iL, int iW, int iH) {

	if (iW != 0 && iH != 0 && iW != (width - 3) && iH != (height - 3)) {

		int size = 16;

		int window[size];

		window[0] = *getPixel(inFrame, iL, iW - 1, iH - 1);
		window[1] = *getPixel(inFrame, iL, iW - 1, iH);
		window[2] = *getPixel(inFrame, iL, iW - 1, iH + 1);
		window[3] = *getPixel(inFrame, iL, iW - 1, iH + 2);

		window[4] = *getPixel(inFrame, iL, iW, iH - 1);
		window[5] = *getPixel(inFrame, iL, iW, iH); //pixel corrente
		window[6] = *getPixel(inFrame, iL, iW, iH + 1);
		window[7] = *getPixel(inFrame, iL, iW, iH + 2);

		window[8] = *getPixel(inFrame, iL, iW + 1, iH - 1);
		window[9] = *getPixel(inFrame, iL, iW + 1, iH);
		window[10] = *getPixel(inFrame, iL, iW + 1, iH + 1);
		window[11] = *getPixel(inFrame, iL, iW + 1, iH + 2);

		window[12] = *getPixel(inFrame, iL, iW + 2, iH - 1);
		window[13] = *getPixel(inFrame, iL, iW + 2, iH);
		window[14] = *getPixel(inFrame, iL, iW + 2, iH + 1);
		window[15] = *getPixel(inFrame, iL, iW + 2, iH + 2);

		return getMedian(type, window, size);
	}

	if (iW == 0 || iH == 0 || iW == (width - 3) || iH == (height - 3))
		return *getPixel(inFrame, iL, iW, iH);

	throw new _IO_FILE;

}

int MedianReduction::median5x5(int type, int iL, int iW, int iH) {

	if (iW != 0 && iH != 0 && iW != (width - 4) && iH != (height - 4)) {

		int size = 25;

		int window[size];

		window[0] = *getPixel(inFrame, iL, iW - 2, iH - 2);
		window[1] = *getPixel(inFrame, iL, iW - 2, iH - 1);
		window[2] = *getPixel(inFrame, iL, iW - 2, iH);
		window[3] = *getPixel(inFrame, iL, iW - 2, iH + 1);
		window[4] = *getPixel(inFrame, iL, iW - 2, iH + 2);

		window[5] = *getPixel(inFrame, iL, iW - 1, iH - 2);
		window[6] = *getPixel(inFrame, iL, iW - 1, iH - 1);
		window[7] = *getPixel(inFrame, iL, iW - 1, iH);
		window[8] = *getPixel(inFrame, iL, iW - 1, iH + 1);
		window[9] = *getPixel(inFrame, iL, iW - 1, iH + 2);

		window[10] = *getPixel(inFrame, iL, iW, iH - 2);
		window[11] = *getPixel(inFrame, iL, iW, iH - 1);
		window[12] = *getPixel(inFrame, iL, iW, iH); //pixel corrente
		window[13] = *getPixel(inFrame, iL, iW, iH + 1);
		window[14] = *getPixel(inFrame, iL, iW, iH + 2);

		window[15] = *getPixel(inFrame, iL, iW + 1, iH - 2);
		window[16] = *getPixel(inFrame, iL, iW + 1, iH - 1);
		window[17] = *getPixel(inFrame, iL, iW + 1, iH);
		window[18] = *getPixel(inFrame, iL, iW + 1, iH + 1);
		window[19] = *getPixel(inFrame, iL, iW + 1, iH + 2);

		window[20] = *getPixel(inFrame, iL, iW + 2, iH - 2);
		window[21] = *getPixel(inFrame, iL, iW + 2, iH - 1);
		window[22] = *getPixel(inFrame, iL, iW + 2, iH);
		window[23] = *getPixel(inFrame, iL, iW + 2, iH + 1);
		window[24] = *getPixel(inFrame, iL, iW + 2, iH + 2);

		return getMedian(type, window, size);

	}

	if (iW == 0 || iH == 0 || iW == (width - 4) || iH == (height - 4))
		return *getPixel(inFrame, iL, iW, iH);

	throw new _IO_FILE;

}
