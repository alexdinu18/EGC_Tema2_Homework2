#pragma once
#include "Background.h"

Background::~Background() {
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++) {
			delete grid[i][j];
			delete contur[i][j];
		}
}