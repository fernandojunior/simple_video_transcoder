/*
 * Math.cpp
 *
 *  Created on: May 31, 2011
 *      Author: Fernando Felix do Nascimento Junior
 */

#include "Math.h"

float Math::selectMax(float arr[], int n) {
	float temp = 0;

	for (register int i = 0; i < n; i++)
		if (arr[i] > temp)
			temp = arr[i];

	return temp;
}

float Math::selectMin(float arr[], int n) {
	float temp = arr[0];

	for (register int i = 1; i < n; i++)
		if (arr[i] < temp)
			temp = arr[i];

	return temp;
}

float Math::sumElements(float arr[], int n) {
	float sum = 0;

	for (register int i = 0; i < n; i++)
		sum += arr[i];

	return sum;
}

float Math::countElements(float arr[], int n, float min, float max) {
	float count = 0;

	for (register int i = 0; i < n; i++)
		if (arr[i] > min && arr[i] < max)
			count++;

	return count;
}

Binary Math::parseToBin(unsigned char c) {
	return std::bitset<CHAR_BIT>(c);
}

unsigned char Math::parseToChar(Binary bin) {
	return bin.to_ulong();
}

/**
 * Normal
 */
int Math::normalMedian(int arr[], int n) {
	int temp;

	//ordenando os numeros em ordem crescente
	for (int register a = 0; a < (n - 1); a++)
		for (int register b = a + 1; b < n; b++)
			if (arr[a] > arr[b]) {
				temp = arr[a];
				arr[a] = arr[b];
				arr[b] = temp;
			}

	if (n % 2 != 0)
		return arr[((n + 1) / 2) - 1];

	int mid1 = arr[(n / 2) - 1];
	int mid2 = arr[(n / 2)];

	return (mid1 + mid2) / 2;
}
//end:normal

/**
 * Quick Select
 */
#define ELEM_SWAP(a,b) { register int t=(a);(a)=(b);(b)=t; }
int Math::quickSelectMedian(int arr[], int n) {
	int low, high;
	int median;
	int middle, ll, hh;
	low = 0;
	high = n - 1;
	median = (low + high) / 2;
	for (;;) {
		if (high <= low) // One element only
			return arr[median];
		if (high == low + 1) { // Two elements only
			if (arr[low] > arr[high])
				ELEM_SWAP(arr[low], arr[high]);
			return arr[median];
		}
		// Find median of low, middle and high items; swap into position low
		middle = (low + high) / 2;
		if (arr[middle] > arr[high])
			ELEM_SWAP(arr[middle], arr[high]);
		if (arr[low] > arr[high])
			ELEM_SWAP(arr[low], arr[high]);
		if (arr[middle] > arr[low])
			ELEM_SWAP(arr[middle], arr[low]);
		// Swap low item (now in position middle) into position (low+1)
		ELEM_SWAP(arr[middle], arr[low+1]);
		// Nibble from each end towards middle, swapping items when stuck
		ll = low + 1;
		hh = high;
		for (;;) {
			do
				ll++;
			while (arr[low] > arr[ll]);
			do
				hh--;
			while (arr[hh] > arr[low]);
			if (hh < ll)
				break;
			ELEM_SWAP(arr[ll], arr[hh]);
		}
		// Swap middle item (in position low) back into correct position
		ELEM_SWAP(arr[low], arr[hh]);
		// Re-set active partition
		if (hh <= median)
			low = ll;
		if (hh >= median)
			high = hh - 1;
	}
}
#undef ELEM_SWAP
// end:quickselect

/**
 * Wirth
 */
#define ELEM_SWAP(a,b) { register int t=(a);(a)=(b);(b)=t; }

int Math::kth_smallest(int a[], int n, int k) {
	register int i, j, l, m;
	register int x;
	l = 0;
	m = n - 1;
	while (l < m) {
		x = a[k];
		i = l;
		j = m;
		do {
			while (a[i] < x)
				i++;
			while (x < a[j])
				j--;
			if (i <= j) {
				ELEM_SWAP(a[i],a[j]);
				i++;
				j--;
			}
		} while (i <= j);
		if (j < k)
			l = i;
		if (k < i)
			m = j;
	}
	return a[k];
}
#undef ELEM_SWAP

int Math::wirthMedian(int a[], int n) {
	return kth_smallest(a, n, (((n) & 1) ? ((n) / 2) : (((n) / 2) - 1)));
}
// end:wirth

/*
 * Torben
 */
int Math::torbenMedian(int m[], int n) {
	int i, less, greater, equal;
	int min, max, guess, maxltguess, mingtguess;
	min = max = m[0];
	for (i = 1; i < n; i++) {
		if (m[i] < min)
			min = m[i];
		if (m[i] > max)
			max = m[i];
	}
	while (1) {
		guess = (min + max) / 2;
		less = 0;
		greater = 0;
		equal = 0;
		maxltguess = min;
		mingtguess = max;
		for (i = 0; i < n; i++) {
			if (m[i] < guess) {
				less++;
				if (m[i] > maxltguess)
					maxltguess = m[i];
			} else if (m[i] > guess) {
				greater++;
				if (m[i] < mingtguess)
					mingtguess = m[i];
			} else
				equal++;
		}
		if (less <= (n + 1) / 2 && greater <= (n + 1) / 2)
			break;
		else if (less > greater)
			max = maxltguess;
		else
			min = mingtguess;
	}
	if (less >= (n + 1) / 2)
		return maxltguess;
	else if (less + equal >= (n + 1) / 2)
		return guess;
	else
		return mingtguess;
}
// end:torben
