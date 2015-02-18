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
#include "House.h"


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d1;

float n = 10.0;
bool square[N][N], water[N][N];
House* houses[N][N];
Object3D* roads_m[N][N];
Object3D* roads_t[N][N];
int rotations[N][N];
float x_minus = -25.0, y_minus = -100.0, x_plus = 25.0, y_plus = -40.0;
Background *land;




//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	v2d1 = new Visual2D(-30,-100,20,-50,0,0,600,600);
	v2d1->tipTran(true);
	addVisual2D(v2d1);
	land = new Background(n, v2d1);
	std::cout<<"land "<<land->contur[2][7]->vertices[3]->x<<" "<<land->contur[0][0]->vertices[0]->y <<"\n";

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			water[i][j] = false;
			square[i][j] = false;
			roads_m[i][j] = NULL;
			roads_t[i][j] = NULL;
			houses[i][j] = NULL;
			rotations[i][j] = 0;
		}
	}
	
}

// constructorul din background
Background::Background(float n,Visual2D *v2d1) {
	this->n = n;
	this->v2d1 = v2d1;
	vector <Point3D*> vertices;
	vector <Face*> faces;
	cursor = new Point2D(n-1,n-1);
	
	vertices.push_back(new Point3D(0,0,0));
	vertices.push_back(new Point3D(n,0,0));
	vertices.push_back(new Point3D(n,0,n));
	vertices.push_back(new Point3D(0,0,n));

	vector <int> contour;
	
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	for (int i = 0; i < N; i++) {
		vector <Object3D*> row_contur;
		for (int j = 0; j < N; j++) {
			grid[i][j] = new Object3D(vertices,faces,Color(0.4,0.2,0.0),true);
			DrawingWindow::addObject3D_to_Visual2D(grid[i][j], v2d1);
			row_contur.push_back(new Object3D(vertices,faces,Color(0,0,0),false));
			DrawingWindow::addObject3D_to_Visual2D(row_contur[j],v2d1);
		}
		contur.push_back(row_contur);
	}

	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Transform3D::loadIdentityModelMatrix();
			Transform3D::loadIdentityProjectionMatrix();
			Transform3D::translateMatrix(-100 + i*10,-100,-100+j*10);
			Transform3D::isometricProjectionMatrix();
			Transform3D::applyTransform(grid[i][j]);
			Transform3D::applyTransform(contur[i][j]);

		}
	}
	grid[9][9]->color = Color(1,0,0);
}

// functia de select pt cursor din Background
void Background::select(unsigned char key) {
	if (water[(int)cursor->x][(int)cursor->y])
		grid[(int)cursor->x][(int)cursor->y]->color = Color(0,1,1);
	else if (roads_t[(int)cursor->x][(int)cursor->y])
	{}
	else if (houses[(int)cursor->x][(int)cursor->y])
	{
		grid[(int)cursor->x][(int)cursor->y]->color = Color(0.0,0.8,0.4);
	}
	else if (square[(int)cursor->x][(int)cursor->y])
		grid[(int)cursor->x][(int)cursor->y]->color = Color(0.0,0.8,0.4);
	else
		grid[(int)cursor->x][(int)cursor->y]->color = Color(0.4,0.2,0.0);

	if (key == GLUT_KEY_UP) {
		if (cursor->y > 0)
			cursor->y--;
		if (cursor->x > 0)
			cursor->x--;
		
	}
	if (key == GLUT_KEY_LEFT) {
		if (cursor->y < N - 1)
			cursor->y++;
		 if (cursor->x > 0) 
			cursor->x--;
		
	}
	if (key == GLUT_KEY_DOWN) {
		if (cursor->y < N - 1)
			cursor->y++;
		if (cursor->x < N - 1)
			cursor->x++;
		
	}
	if (key == GLUT_KEY_RIGHT) {
		if (cursor->y > 0 )			
			cursor->y--;
		if (cursor->x < N - 1) 
			cursor->x++;
	}

		grid[(int)cursor->x][(int)cursor->y]->color = Color(1,0,0);
}

void Background::add_water() {
	if (roads_t[(int)cursor->x][(int)cursor->y] || water[(int)cursor->x][(int)cursor->y] || houses[(int)cursor->x][(int)cursor->y])
		return;
	
	grid[(int)cursor->x][(int)cursor->y]->color = Color(0,1,1);
	contur[(int)cursor->x][(int)cursor->y]->color = Color(0,1,1);
	water[(int)cursor->x][(int)cursor->y] = true;

}

void Background::add_square() {
	for (int i = (int)cursor->x - 1; i <= (int)cursor->x + 1; i++)
		for (int j = (int)cursor->y - 1; j <= (int)cursor->y + 1; j++) {
			if ( i >=0 && i <= N-1 && j >= 0 && j <= N - 1)
				if (!water[i][j] && roads_t[i][j] == NULL && houses[i][j] == NULL) {
					grid[i][j]->color = Color(0.0,0.8,0.4);
					square[i][j] = true;
				}
		}

} 

void Background::add_road() {
	if (roads_t[(int)cursor->x][(int)cursor->y] || water[(int)cursor->x][(int)cursor->y] || houses[(int)cursor->x][(int)cursor->y])
		return;

	vector <Point3D*> vertices;
	vector <Face*> faces;
	
	vertices.push_back(new Point3D(0,0,0));
	vertices.push_back(new Point3D(n,0,0));
	vertices.push_back(new Point3D(n,0,n));
	vertices.push_back(new Point3D(0,0,n));

	vector <int> contour;
	
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	Object3D* road_tile = new Object3D(vertices,faces,Color(0,0,0),true);
	roads_t[(int)cursor->x][(int)cursor->y] = road_tile;


	vector <Point3D*> vertices2;
	vector <Face*> faces2;
	
	vertices2.push_back(new Point3D(4, 0, 2));
	vertices2.push_back(new Point3D(6, 0, 2));
	vertices2.push_back(new Point3D(6 ,0, 8));
	vertices2.push_back(new Point3D(4, 0, 8));

	vector <int> contour2;
	
	contour2.clear();
	contour2.push_back(0);
	contour2.push_back(1);
	contour2.push_back(2);
	contour2.push_back(3);
	faces2.push_back(new Face(contour2));

	Object3D* road_mark = new Object3D(vertices2,faces2,Color(1,1,1),true);
	roads_m[(int)cursor->x][(int)cursor->y] = road_mark;
	DrawingWindow::addObject3D_to_Visual2D(road_mark, v2d1);
	DrawingWindow::addObject3D_to_Visual2D(road_tile, v2d1);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*(int)cursor->x,-100+0.001,-100+10*(int)cursor->y);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(road_tile);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*(int)cursor->x,-100+0.002,-100+10*(int)cursor->y);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(road_mark);
}

void Background::add_house() {
	if (!water[(int)cursor->x][(int)cursor->y] && roads_t[(int)cursor->x][(int)cursor->y] == NULL && square[(int)cursor->x][(int)cursor->y]) {
		House *h = new House(n, v2d1, (int)cursor->x, (int)cursor->y);
		houses[(int)cursor->x][(int)cursor->y] = h;
	}
}

void Background::remove() {
	water[(int)cursor->x][(int)cursor->y] = false;
	if (roads_t[(int)cursor->x][(int)cursor->y]) {
		DrawingWindow::removeObject3D_from_Visual2D(roads_t[(int)cursor->x][(int)cursor->y], v2d1);
		DrawingWindow::removeObject3D_from_Visual2D(roads_m[(int)cursor->x][(int)cursor->y], v2d1);
		roads_t[(int)cursor->x][(int)cursor->y] = NULL;
		roads_m[(int)cursor->x][(int)cursor->y] = NULL;
	}
	else if ((houses[(int)cursor->x][(int)cursor->y])) {
		DrawingWindow::removeObject3D_from_Visual2D(houses[(int)cursor->x][(int)cursor->y]->cube1, v2d1);
		DrawingWindow::removeObject3D_from_Visual2D(houses[(int)cursor->x][(int)cursor->y]->cube2, v2d1);
		DrawingWindow::removeObject3D_from_Visual2D(houses[(int)cursor->x][(int)cursor->y]->cube3, v2d1);
		DrawingWindow::removeObject3D_from_Visual2D(houses[(int)cursor->x][(int)cursor->y]->door, v2d1);
		DrawingWindow::removeObject3D_from_Visual2D(houses[(int)cursor->x][(int)cursor->y]->window1, v2d1);
		DrawingWindow::removeObject3D_from_Visual2D(houses[(int)cursor->x][(int)cursor->y]->window2, v2d1);
		houses[(int)cursor->x][(int)cursor->y] = NULL;
	}


	if (square[(int)cursor->x][(int)cursor->y]) {
		grid[(int)cursor->x][(int)cursor->y]->color = Color(1,0,0);
		contur[(int)cursor->x][(int)cursor->y]->color = Color(0,0,0);
	}
	else {
		grid[(int)cursor->x][(int)cursor->y]->color = Color(0.4,0.2,0.0);
		contur[(int)cursor->x][(int)cursor->y]->color = Color(0,0,0);
	}
}

void Background::rotate(unsigned char key) {
	if(roads_t[(int)cursor->x][(int)cursor->y]){
		if (key == KEY_lt)
			rotations[(int)cursor->x][(int)cursor->y]=1;
		else
			rotations[(int)cursor->x][(int)cursor->y]=2;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::loadIdentityProjectionMatrix();
		Transform3D::rotateMatrixOx(rotations[(int)cursor->x][(int)cursor->y]*PI/2);
		Transform3D::rotateMatrixOy(rotations[(int)cursor->x][(int)cursor->y]*PI/2);
		Transform3D::rotateMatrixOz(rotations[(int)cursor->x][(int)cursor->y]*PI/2);
		Transform3D::isometricProjectionMatrix();
		Transform3D::translateMatrix(-100+10*(int)cursor->x,-100+0.001,-100+10*(int)cursor->y);
		Transform3D::applyTransform(roads_t[(int)cursor->x][(int)cursor->y]);

		Transform3D::loadIdentityModelMatrix();
		Transform3D::loadIdentityProjectionMatrix();
		Transform3D::rotateMatrixOx(rotations[(int)cursor->x][(int)cursor->y]*PI/2);
		Transform3D::rotateMatrixOy(rotations[(int)cursor->x][(int)cursor->y]*PI/2);
		Transform3D::rotateMatrixOz(rotations[(int)cursor->x][(int)cursor->y]*PI/2);
		Transform3D::isometricProjectionMatrix();
		Transform3D::translateMatrix(-100+10*(int)cursor->x,-100+0.002,-100+10*(int)cursor->y);
		Transform3D::applyTransform(roads_m[(int)cursor->x][(int)cursor->y]);
	}
	else if(houses[(int)cursor->x][(int)cursor->y] != NULL) {
		Point3D center = Point3D(0.0,0.0,0.0);
		
		for (Point3D* point : houses[(int)cursor->x][(int)cursor->y]->cube->vertices) {
			center.x += (float)point->x;
			center.y += (float)point->y;
			center.z += (float)point->z;
		}
		center.x = center.x / houses[(int)cursor->x][(int)cursor->y]->cube->vertices.size();
		center.y = center.y / houses[(int)cursor->x][(int)cursor->y]->cube->vertices.size();
		center.z = center.z / houses[(int)cursor->x][(int)cursor->y]->cube->vertices.size();
		/*
		center.x = -100+10*(int)cursor->x + 5;
		center.y = -100+5;
		center.x = -100+10*(int)cursor->y + 5;*/

		float angle = PI/2;

		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		Transform3D::translateMatrix(-100+10*(int)cursor->x,-100,-100+10*(int)cursor->y);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->cube1);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->cube2);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->cube3);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->door);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->window1);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->window2);

		 /*
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		//Transform3D::translateMatrix(-100+10*(int)cursor->x,-100,-100+10*(int)cursor->y+5);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->cube1);

		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		//Transform3D::translateMatrix(-100+10*(int)cursor->x,-100,-100+10*(int)cursor->y);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->cube2);

		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		//Transform3D::translateMatrix(-100+10*(int)cursor->x+5,-100,-100+10*(int)cursor->y);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->cube3);

		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		//Transform3D::translateMatrix(-100+10*(int)cursor->x,-100,-100+10*(int)cursor->y+10+0.001);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->door);

		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		//Transform3D::translateMatrix(-100+10*(int)cursor->x+0.001,-100,-100+10*(int)cursor->y+5);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->window1);

		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-center.x,-center.y,-center.z);
		Transform3D::rotateMatrixOy(angle);
		Transform3D::translateMatrix(center.x,center.y,center.z);
		//Transform3D::translateMatrix(-100+10*(int)cursor->x+5+0.001,-100,-100+10*(int)cursor->y);
		Transform3D::applyTransform(houses[(int)cursor->x][(int)cursor->y]->window2);*/
	} 
}
//functia care permite animatia
void DrawingWindow::onIdle()
{
	v2d1->fereastra(x_minus, y_minus, x_plus, y_plus);
		
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,0,600,600);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	
	switch(key)
	{
		case 27 :
			{					
				exit(0);
			}
		case GLUT_KEY_RIGHT :
			{ 
				if (x_plus < 70) {
					x_plus += N * sqrt(2);
					x_minus += N * sqrt(2);
				}
				land->select(key);
				break;
			}
		case GLUT_KEY_LEFT :{ 
				if (x_minus > -80) {
					x_plus -= N * sqrt(2);
					x_minus -= N * sqrt(2);
				}
				land->select(key);
				break;
			}
		case GLUT_KEY_UP :{ 
				if (y_plus < 10) {
					y_plus += N / 2;
					y_minus += N / 2;
				}
				land->select(key);
				break;
			}
		case GLUT_KEY_DOWN :{ 
				if (y_minus > -100) {
					y_plus -= N / 2;
					y_minus -= N / 2;
				}
				land->select(key);
				break;
			}
		case KEY_W :{
				land->add_water();
				break;
			}
		case KEY_BACKSPACE :{
				land->remove();
				break;
			}
		case KEY_S :{
				land->add_square();
				break;
			}
		case KEY_R :{
				land->add_road();
				break;
			}
		case KEY_H :{
				land->add_house();
				break;
			}
		case KEY_lt :{
				land->rotate(key);
				break;
			}
		case KEY_gt :{
				land->rotate(key);
				break;
			}
		default: break;
	}
	
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	//land->select(x,y);
	std::cout<<x <<" "<<y<<std::endl;
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 600, 600, 300, 50, "Tema2");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}