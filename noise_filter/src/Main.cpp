//============================================================================
// Name        : Simple video transcoder for noise filter.
// Author      : Fernando Felix do Nascimento Junior
// Copyright   : MIT
//============================================================================

#include <iostream>
#include "Video.h"
#include "MedianFilter.h"

using namespace std;

int main() {

	MedianFilter
			test(
					150,
					3,
					352 / 2,
					288 / 2,
					"/home/jr/Desktop/ifpb/CD/filtros_remocao_ruido_video/ok/Fernando/foreman/16qam/foreman-Rayleigh-16QAM-10.0.yuv",
					"/home/jr/Desktop/video_filtrado.yuv");

	test.medianFilter();

	return 0;
}
