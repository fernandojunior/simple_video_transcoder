/*
 * Math.h
 *
 *  Created on: May 31, 2011
 *      Author: Fernando Felix do Nascimento Junior
 */

#ifndef MATH_H_
#define MATH_H_

#include <bitset>
#include <iostream>
#include <limits.h>

typedef std::bitset<8u> Binary;

/**
 * Classe que contem funcoes matematicas necessarias para o processamento de um video
 * @author Fernando Felix do Nascimento Junior
 *
 */
class Math {
public:

	/**
	 * Seleciona o elemento maximo de um array
	 *
	 * @param arr
	 *            O array
	 * @param n
	 *            O tamanho do array
	 * @return O elemento Maximo
	 */
	static float selectMax(float arr[], int n);

	/**
	 * Seleciona o elemento minimo de um array
	 *
	 * @param arr
	 *            O array
	 *
	 * @param n
	 *            O tamanho do array
	 * @return O elemento Maximo
	 */
	static float selectMin(float arr[], int n);

	/**
	 * Soma os elementos de um array
	 *
	 * @param arr
	 *            O array
	 * @param n
	 *            Tamanho do array
	 * @return A soma dos elementos
	 */
	static float sumElements(float arr[], int n);

	/**
	 * Conta o numero de elementos entre um determinado valor minimo (min) e
	 * maximo (max)
	 *
	 * @param arr
	 *            O array
	 *
	 * @param n
	 *            Tamanho do array
	 *
	 * @param min
	 *            O valor minimo
	 * @param max
	 *            O valor maximo
	 * @return O numero de elementos entre min && max
	 */
	static float countElements(float arr[], int n, float min, float max);

	/**
	 * Converte um pixel em binario
	 * @param pixel
	 *             O pixel a ser convertido
	 * @return O pixel em binario
	 */
	static Binary parseToBin(unsigned char c);

	/**
	 * Converte um pixel de binario para decimal
	 * @param pixel
	 *             O pixel a ser convertido
	 * @return O pixel em binario
	 */
	static unsigned char parseToChar(Binary bin);

	static int normalMedian(int arr[], int n);

	/**
	 * QuickSelect
	 *
	 * This Quickselect routine is based on the algorithm described in
	 * "Numerical recipes in C", Second Edition, Cambridge University Press,
	 * 1992, Section 8.5, ISBN 0-521-43108-5 This code by Nicolas Devillard -
	 * 1998. Public domain.
	 *
	 * @param arr
	 *            O array
	 * @param n
	 *            O tamanho do array
	 */
	static int quickSelectMedian(int arr[], int n);

	/*
	 * Wirth
	 * Algorithm from N. Wirth’s book, implementation by N. Devillard.
	 * This code in public domain.
	 */
	static int wirthMedian(int a[], int n);

	/**
	 * Torben
	 *
	 * The following code is public domain.
	 * Algorithm by Torben Mogensen, implementation by N. Devillard.
	 * This code in public domain.
	 *
	 */
	static int torbenMedian(int m[], int n);

private:
	static int kth_smallest(int a[], int n, int k);

};

#endif /* MATH_H_ */
