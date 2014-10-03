//============================================================================
// Name        : Simple video transcoder for spatial resolution reduction
// Author      : Fernando Felix do Nascimento Junior
// Copyright   : MIT
// Description : Simple video transcoder for spacial resolution reduction, using median algorithms
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <math.h>

#include "MedianReduction.h"

void medianReduction(int windowSize, int type, int frames, int layers,
		int width, int height, String inputPath, String outputPath) {

	MedianReduction teste(frames, layers, width, height, inputPath, outputPath);

	teste.run(windowSize, type);

}

int main(int argc, char* argv[]) {

	int frames = 150;
	int layers = 3;
	int width = 352;
	int height = 288;

	String
			inputVideo =
					"/home/jr/Desktop/ifpb/CD/trabalho_filtros remocao_ruido video/videos/news_cif.yuv";

	String outputVideo = "/home/jr/Desktop/video_filtrado.yuv";

	char windowSize = argv[1][0];
	char type = argv[2][0];

	if (windowSize == '2') {
		if (type == '0')
			medianReduction(2, 0, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '1')
			medianReduction(2, 1, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '2')
			medianReduction(2, 2, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '3')
			medianReduction(2, 3, frames, layers, width, height, inputVideo,
					outputVideo);
	}

	if (windowSize == '3') {
		if (type == '0')
			medianReduction(3, 0, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '1')
			medianReduction(3, 1, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '2')
			medianReduction(3, 2, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '3')
			medianReduction(3, 3, frames, layers, width, height, inputVideo,
					outputVideo);
	}

	if (windowSize == '4') {
		if (type == '0')
			medianReduction(4, 0, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '1')
			medianReduction(4, 1, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '2')
			medianReduction(4, 2, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '3')
			medianReduction(4, 3, frames, layers, width, height, inputVideo,
					outputVideo);
	}

	if (windowSize == '5') {
		if (type == '0')
			medianReduction(5, 0, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '1')
			medianReduction(5, 1, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '2')
			medianReduction(5, 2, frames, layers, width, height, inputVideo,
					outputVideo);
		if (type == '3')
			medianReduction(5, 3, frames, layers, width, height, inputVideo,
					outputVideo);
	}

}
