/*
 * MedianFilter.cpp
 *
 *  Created on: Jun 6, 2011
 *      Author: Fernando Felix do Nascimento Junior
 */

#include "MedianFilter.h"

void MedianFilter::medianFilter() {

	for (register int frameIndex = 0; frameIndex < frames; frameIndex++) { // frames loop
		readLFrame(frameIndex);
		for (register int layerIndex = 0; layerIndex < layers; layerIndex++) // layers loop
			for (register int heightIndex = 0; heightIndex < height; heightIndex++) // height loop
				for (register int widthIndex = 0; widthIndex < width; widthIndex++) // width loop
				{

					/* Acessando os pixeis correntes dos frames de entrada e de saida, respectivamente */
					Pixel * pixIN = PixIN(layerIndex, widthIndex, heightIndex);
					Pixel * pixOUT =
							PixOUT(layerIndex, widthIndex, heightIndex);

					/* Condicao do frame para se fazer a mediana da janela corrente: ooooo oxxxo oxxxo oxxxo ooooo */
					if (widthIndex > 0 && heightIndex > 0 && widthIndex
							< (width - 1) && heightIndex < (height - 1))
						*pixOUT = getMedian3x3(layerIndex, widthIndex,
								heightIndex);

					/* Caso contrario */
					if (widthIndex == 0 || heightIndex == 0 || widthIndex
							== (width - 1) || heightIndex == (height - 1))
						*pixOUT = *pixIN;

				}

		writeLFrame(frameIndex);

	}

}

float MedianFilter::getMedian3x3(int layerIndex, int widthIndex,
		int heightIndex) {

	/**
	 * Ver arquivo ref1
	 */

	/* Window/Kernel Size */
	int size = 3 * 3;

	/* Serializable Window */
	float window[size];

	//linha 1
	window[0] = *PixIN(layerIndex, widthIndex - 1, heightIndex - 1);
	window[1] = *PixIN(layerIndex, widthIndex, heightIndex - 1);
	window[2] = *PixIN(layerIndex, widthIndex + 1, heightIndex - 1);

	//linha 2
	window[3] = *PixIN(layerIndex, widthIndex - 1, heightIndex);
	window[4] = *PixIN(layerIndex, widthIndex, heightIndex); //pixel corrente
	window[5] = *PixIN(layerIndex, widthIndex + 1, heightIndex);

	//linha 3
	window[6] = *PixIN(layerIndex, widthIndex - 1, heightIndex + 1);
	window[7] = *PixIN(layerIndex, widthIndex, heightIndex + 1);
	window[8] = *PixIN(layerIndex, widthIndex + 1, heightIndex + 1);

	return Math::quickSelectMedian(window, size);

}
