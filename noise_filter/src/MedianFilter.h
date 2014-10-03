/*
 * MedianFilter.h
 *
 *  Created on: Jun 6, 2011
 *      Author: Fernando Felix do Nascimento Junior
 */

#ifndef MEDIANFILTER_H_
#define MEDIANFILTER_H_

#include "Video.h"

/**
 * Classe que faz o processamento de um video com um filtro mediano.
 * @author Fernando Felix do Nascimento Junior
 *
 */
class MedianFilter: public Video {
public:

	/**
	 * Contrutor que inicializa os parametros necessarios para o processamento
	 * de um video de entrada em um video de saida
	 *
	 * @param frames
	 *            Numero de frames que o video de entrada possui
	 * @param layers
	 *            Numero de camadas de cores que o video de entrada possui
	 *
	 * @param width
	 *            width O tamanho da largura que o video de entrada possui
	 * @param height
	 *            O tamanho da altura que o video de entrada possui
	 * @param videoIN
	 *            O arquivo de video de entrada a ser processado
	 *
	 * @param videoOUT
	 *            O arquivo de video de saida processado
	 *
	 *
	 */
	MedianFilter(int frames, int layers, int width, int height, String videoIN,
			String videoOUT) :
		Video(frames, layers, width, height, videoIN, videoOUT) {
	}
	;

	/**
	 * Deconstrutor
	 */
	virtual ~MedianFilter() {
		delete[] frameIN;
		delete[] frameOUT;
	}
	;

	/**
	 * Filtro Mediano para remocao de ruido em Videos
	 */
	void medianFilter();

	/**
	 * Retorna o pixel mediando de uma janela 3x3, com base no endereco (layerIndex, widthIndex, heightIndex) do pixel corrente passado como parametro.
	 * @param layerIndex O indice da camada de cor do pixel corrente
	 * @param widthIndex O indice do width do pixel corrente
	 * @param heightIndex O indice do height do pixel corrente
	 * @return O valor do pixel mediano, com base no pixel corrente, com uma janela de filtro de tamanho 3x3
	 */
	inline float getMedian3x3(int layerIndex, int widthIndex, int heightIndex);

};

#endif /* MEDIANFILTER_H_ */
