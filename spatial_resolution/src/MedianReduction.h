/*
 * MedianReduction.h
 *
 *  Created on: Aug 15, 2011
 *      Author: Fernando Felix do Nascimento Junior
 */

#ifndef MEDIANREDUCTION_H_
#define MEDIANREDUCTION_H_

#include <stdlib.h>
#include <stdio.h>
#include "util/Math.h"

/**
 * Definindo novo tipo para String
 */
typedef char * String;

/**
 * Definindo novo tipo Pixel
 */
typedef unsigned char Pixel;

/**
 * Default frame = Conjunto de Pixeis, com apenas uma camada de cor
 */
typedef Pixel * SimpleFrame;

/**
 * Frame = Conjunto de Pixeis, com mais de uma camada de cores
 */
typedef SimpleFrame * Frame;

class MedianReduction {
public:

	MedianReduction(int frames, int layers, int width, int height,
			String inputPath, String outputPath) :
		frames(frames), layers(layers), width(width), height(height),
				inputVideo(inputPath), outputVideo(outputPath),
				frameSizeWH(width * height),
				frameSizeLWH(layers * width * height) {

	}
	;

	/**
	 * Deconstrutor
	 */
	virtual ~MedianReduction() {
		delete[] inFrame;
		delete[] outFrame;
	}
	;

	Frame mallocFrame(int layers, int width, int height);

	void readFrame(int index);

	void writeFrame(int layers, int width, int height, int index);

	void run(int type, int windowSize);

	int getMedian(int type, int windowSize, int layerIndex, int widthIndex,
			int heightIndex);
	int getMedian(int type, int window[], int size);

	int median5x5(int type, int iL, int iW, int iH);

	int median4x4(int type, int iL, int iW, int iH);

	int median3x3(int type, int layerIndex, int widthIndex, int heightIndex);

	int median2x2(int type, int layerIndex, int widthIndex, int heightIndex);

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
	inline int getPixIndex(int w, int h, int width) {
		return h * width + w;
	}
	;

	/**
	 * Acessa o pixel do frame da memoria. Inicia de (0,0,0) ate
	 * (layers-1,width-1,height-1).
	 *
	 * @param l
	 *            A posicao na dimensao layers onde o pixel desejado esta
	 * @param x
	 *            A posicao na dimensao width onde o pixel desejado esta
	 * @param y
	 *            A posicao na dimensao height onde o pixel desejado esta
	 * @param frame
	 *            O frame, na qual, deseja-se acessar o pixel
	 */
	Pixel * getPixel(Frame frame, int width, int l, int x, int y) {
		return (frame[l] + getPixIndex(x, y, width));
	}
	;

	/**
	 * Acessa o pixel do frame da memoria. Inicia de (0,0,0) ate
	 * (layers-1,width-1,height-1).
	 *
	 * @param l
	 *            A posicao na dimensao layers onde o pixel desejado esta
	 * @param x
	 *            A posicao na dimensao width onde o pixel desejado esta
	 * @param y
	 *            A posicao na dimensao height onde o pixel desejado esta
	 * @param frame
	 *            O frame, na qual, deseja-se acessar o pixel
	 */
	Pixel * getPixel(Frame frame, int l, int x, int y) {
		return (frame[l] + getPixIndex(x, y, width));
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
	Pixel * PixIN(int l, int x, int y, int width) {
		return getPixel(inFrame, l, x, y, width);
	}
	;

	/**
	 * //definindo posicao na memoria do pixel de saida corrente
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
	Pixel * PixOUT(int l, int x, int y, int width) {
		return getPixel(outFrame, l, x, y, width);
	}
	;

private:
	int frames, layers, width, height;
	String inputVideo, outputVideo;
	Frame inFrame, outFrame;
	int frameSizeWH;
	int frameSizeLWH;

};

#endif /* MEDIANREDUCTION_H_ */
