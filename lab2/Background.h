#pragma once
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#define N 10
#define KEY_W 119 // add water
#define KEY_R 114 // roads
#define KEY_H 104 // houses
#define KEY_S 115 // add square
#define KEY_BACKSPACE 8 // delete
#define KEY_lt 110 // rotate left
#define KEY_gt 109 // rotate right


class Background {
public:
	float n;
	Visual2D *v2d1;
	//vector <vector <Object3D*>> grid;
	Object3D* grid[N][N];
	vector <vector <Object3D*>> contur;
	Point2D *cursor;

	Background(float n,Visual2D *v2d1);
	void select(unsigned char key);
	void add_water();
	void add_road();
	void add_square();
	void add_house();
	void rotate(unsigned char key);
	void remove();
	~Background();
};