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
#include "Background.h"
#include "Framework/Object3D.h"
#include "Framework/Object2D.h"

#define PI 3.14159265358979323846

class House { 
public:
	float n;
	Visual2D *v2d1;
	Object3D *cube1,*cube2,*cube3, *door, *window1, *window2,*cube;

	House(float n,Visual2D *v2d1, int grid_x, int grid_y);
	~House();
};