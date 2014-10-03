/*
 * Video.h
 *
 *  Created on: Jun 5, 2011
 *      Author: Fernando Felix do Nascimento Junior
 *
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Math.h"

/**
 * Definindo tipo para string
 */
typedef char * String;

/**
 * Definindo o tipo para os pixeis de um Video
 */
typedef unsigned char Pixel;

/**
 * Frame = Conjunto de Pixeis
 */
typedef Pixel * DefaultFrame;

/**
 * LayeredFrame = Frame que possui mais de uma camada de cores
 */
typedef DefaultFrame * LayeredFrame;

/**
 * Uma classe de video que fornece apoio para processamento de videos digitais,
 * como filtros. Basicamente um reader e writer de frames que possuem mais de
 * uma camada de cores.
 *
 * @author: Fernando Felix do Nascimento Junior
 */

class Video {
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
	Video(int frames, int layers, int width, int height, String videoIN,
			String videoOUT) :
		frames(frames), layers(layers), width(width), height(height),
				videoIN(videoIN), videoOUT(videoOUT) {

		frameIN = mallocLFrame();
		frameOUT = mallocLFrame();

	}
	;

	/**
	 * Deconstrutor
	 */
	virtual ~Video() {
		delete[] frameIN;
		delete[] frameOUT;
	}
	;

	/**
	 * Alocação de memória para um Layered Frame, ou seja, para um frame que
	 * possui mais de uma camada
	 *
	 * @return O objeto enderecado na memoria
	 */
	LayeredFrame mallocLFrame();

	/**
	 * Ler um frame, com base no indice especificado, do arquivo de entrada
	 *
	 * @param index
	 *            O indice do frame a ser lido
	 */
	void readLFrame(int index);

	/**
	 * Escrever um layered frame em um arquivo de video de saida, com base no
	 * indice especificado. Baseado no codigo de DANILO REGIS at al., 2011
	 *
	 * @param index
	 *            O indice do video de saida, na qual o frame ira ser escrito
	 */
	void writeLFrame(int index);

	/**
	 * Metodo que retorna o tamanho de um frame padrao. Baseado no codigo de DANILO REGIS at al., 2011
	 *
	 * @return Tamanho de um frame padrao
	 */
	long getDFrameSize() {
		return (long) ((width * height));
	}
	;

	/**
	 * Metodo que retorna o tamanho de um frame com camadas
	 *
	 * @return Tamanho de um layered frame
	 */
	long getLFrameSize() {
		return (long) ((width * height) * layers);
	}
	;

	/**
	 * Retorna o indice do pixel no frame. Inicia de (0,0) ate
	 * (width-1,height-1)
	 *
	 * @param w
	 *            O indice na dimensao width
	 * @param h
	 *            O indice na dimensao height
	 *
	 */
	int getPixIndex(int w, int h) {
		return h * width + w;
	}
	;

	/**
	 * Acessa o pixel do frame. Inicia de (0,0,0) ate
	 * (layers-1,width-1,height-1).
	 *
	 * @param l
	 *            A posicao nos layers onde o pixel desejado esta
	 * @param x
	 *            A posicao no width onde o pixel desejado esta
	 * @param y
	 *            A posicao no height onde o pixel desejado esta
	 * @param frame
	 *            O frame, na qual, deseja-se acessar o pixel
	 */
	Pixel * Pix(int l, int x, int y, LayeredFrame frame) {
		return (frame[l] + getPixIndex(x, y));
	}
	;

	/**
	 * Acessa o pixel do frame IN. Inicia de (0,0,0) ate
	 * (layers-1,width-1,height-1).
	 *
	 * @param l
	 *            A posicao nos layers onde o pixel desejado esta
	 * @param x
	 *            A posicao no width onde o pixel desejado esta
	 * @param y
	 *            A posicao no height onde o pixel desejado esta
	 */
	Pixel * PixIN(int l, int x, int y) {
		return Pix(l, x, y, frameIN);
	}
	;

	/**
	 * Acessa o pixel do frame OUT. Inicia de (0,0,0) ate
	 * (layers-1,width-1,height-1).
	 *
	 * @param l
	 *            A posicao nos layers onde o pixel desejado esta
	 * @param x
	 *            A posicao no width onde o pixel desejado esta
	 * @param y
	 *            A posicao no height onde o pixel desejado esta
	 */
	Pixel * PixOUT(int l, int x, int y) {
		return Pix(l, x, y, frameOUT);
	}
	;

	/**
	 * Numero de frames que o video de entrada possui
	 */
	int frames;

	/**
	 * layers Numero de camadas de cores que o video de entrada possui
	 * width O tamanho da largura que o video de entrada possui
	 * height O tamanho da altura que o video de entrada possui
	 */
	int layers, width, height;

	/**
	 * videoIN O arquivo de video de entrada a ser processado
	 * videoOUT O arquivo de video de saida processado
	 */
	String videoIN, videoOUT;

	/**
	 * Objetos que ira conter as alocacoes de memoria, necessarias para fazer o processamento do video de entrada
	 */
	LayeredFrame frameIN, frameOUT;

};

#endif /* VIDEO_H_ */
