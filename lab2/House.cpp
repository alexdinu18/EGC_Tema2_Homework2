#pragma once
#include "House.h"

House::House(float n, Visual2D *v2d1, int grid_x, int grid_y) {
	this->n = n;
	this->v2d1 = v2d1;
	
	vector <Point3D*> vertices;
	vector <Face*> faces;
	
	//varfurile de jos
	vertices.push_back(new Point3D(0,0,0));
	vertices.push_back(new Point3D(n/2,0,0));
	vertices.push_back(new Point3D(n/2,0,n/2));
	vertices.push_back(new Point3D(0,0,n/2));
	//varfurile de sus
	vertices.push_back(new Point3D(0,n/2,0));
	vertices.push_back(new Point3D(n/2,n/2,0));
	vertices.push_back(new Point3D(n/2,n/2,n/2));
	vertices.push_back(new Point3D(0,n/2,n/2));
	
	//cele 6 fete
	vector <int> contour;
	//fata jos
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));
	//fata sus
	contour.clear();
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	//fata fata
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(5);
	contour.push_back(4);
	faces.push_back(new Face(contour));
	//fata dreapta
	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(6);
	contour.push_back(5);
	faces.push_back(new Face(contour));
	//fata spate
	contour.clear();
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	//fata stanga
	contour.clear();
	contour.push_back(3);
	contour.push_back(0);
	contour.push_back(4);
	contour.push_back(7);
	faces.push_back(new Face(contour));

	cube1 = new Object3D(vertices,faces,Color(0.65,0.44,0.39), true);
	cube2 = new Object3D(vertices,faces,Color(0.65,0.44,0.39), true);
	cube3 = new Object3D(vertices,faces,Color(0.65,0.44,0.39), true);
	
	DrawingWindow::addObject3D_to_Visual2D(cube1, v2d1);
	DrawingWindow::addObject3D_to_Visual2D(cube3, v2d1);
	DrawingWindow::addObject3D_to_Visual2D(cube2, v2d1);
	
	// pt cube1
	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x,-100,-100+10*grid_y+5);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(cube1);

	//pt cube2
	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x,-100,-100+10*grid_y);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(cube2);

	//pt cube3
	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x+5,-100,-100+10*grid_y);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(cube3);
	


	//pt usa
	vector <Point3D*> vertices2;
	vector <Face*> faces2;
	vector <int> contour2;

	vertices2.push_back(new Point3D(n/2-3,0,0));
	vertices2.push_back(new Point3D(n/2-2,0,0));
	vertices2.push_back(new Point3D(n/2-2,0,n/2-6));
	vertices2.push_back(new Point3D(n/2-3,0,n/2-6));
	//varfurile de sus
	vertices2.push_back(new Point3D(n/2-3,n/2-2,0));
	vertices2.push_back(new Point3D(n/2-2,n/2-2,0));
	vertices2.push_back(new Point3D(n/2-2,n/2-2,n/2-6));
	vertices2.push_back(new Point3D(n/2-3,n/2-2,n/2-6));
	//cele 6 fete
	//fata jos
	contour2.clear();
	contour2.push_back(0);
	contour2.push_back(1);
	contour2.push_back(2);
	contour2.push_back(3);
	faces2.push_back(new Face(contour2));
	//fata sus
	contour2.clear();
	contour2.push_back(4);
	contour2.push_back(5);
	contour2.push_back(6);
	contour2.push_back(7);
	faces2.push_back(new Face(contour2));
	//fata fata
	contour2.clear();
	contour2.push_back(0);
	contour2.push_back(1);
	contour2.push_back(5);
	contour2.push_back(4);
	faces2.push_back(new Face(contour2));
	//fata dreapta
	contour2.clear();
	contour2.push_back(1);
	contour2.push_back(2);
	contour2.push_back(6);
	contour2.push_back(5);
	faces2.push_back(new Face(contour2));
	//fata spate
	contour2.clear();
	contour2.push_back(2);
	contour2.push_back(3);
	contour2.push_back(7);
	contour2.push_back(6);
	faces2.push_back(new Face(contour2));
	//fata stanga
	contour2.clear();
	contour2.push_back(3);
	contour2.push_back(0);
	contour2.push_back(4);
	contour2.push_back(7);
	faces2.push_back(new Face(contour2));

	door = new Object3D(vertices2,faces2,Color(0.79,0.44,0.09),true);
	DrawingWindow::addObject3D_to_Visual2D(door, v2d1);
	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x,-100,-100+10*grid_y+10+0.001);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(door);

	// pt geamuri
	vector <Point3D*> vertices3;
	vector <Face*> faces3;
	
	
	vertices3.push_back(new Point3D(n/2-1,n/2-3,n/2-4));
	vertices3.push_back(new Point3D(n/2,n/2-3,n/2-4));
	vertices3.push_back(new Point3D(n/2,n/2-3,n/2-1));
	vertices3.push_back(new Point3D(n/2-1,n/2-3,n/2-1));
	//varfurile de sus
	vertices3.push_back(new Point3D(n/2-1,n/2-1,n/2-4));
	vertices3.push_back(new Point3D(n/2,n/2-1,n/2-4));
	vertices3.push_back(new Point3D(n/2,n/2-1,n/2-1));
	vertices3.push_back(new Point3D(n/2-1,n/2-1,n/2-1));
	
	//cele 6 fete
	//fata jos
	contour2.clear();
	contour2.push_back(0);
	contour2.push_back(1);
	contour2.push_back(2);
	contour2.push_back(3);
	faces3.push_back(new Face(contour2));
	//fata sus
	contour2.clear();
	contour2.push_back(4);
	contour2.push_back(5);
	contour2.push_back(6);
	contour2.push_back(7);
	faces3.push_back(new Face(contour2));
	//fata fata
	contour2.clear();
	contour2.push_back(0);
	contour2.push_back(1);
	contour2.push_back(5);
	contour2.push_back(4);
	faces3.push_back(new Face(contour2));
	//fata dreapta
	contour2.clear();
	contour2.push_back(1);
	contour2.push_back(2);
	contour2.push_back(6);
	contour2.push_back(5);
	faces3.push_back(new Face(contour2));
	//fata spate
	contour2.clear();
	contour2.push_back(2);
	contour2.push_back(3);
	contour2.push_back(7);
	contour2.push_back(6);
	faces3.push_back(new Face(contour2));
	//fata stanga
	contour2.clear();
	contour2.push_back(3);
	contour2.push_back(0);
	contour2.push_back(4);
	contour2.push_back(7);
	faces3.push_back(new Face(contour2));

	window1 = new Object3D(vertices3,faces3,Color(0.79,1.00,0.90),true);
	window2 = new Object3D(vertices3,faces3,Color(0.79,1.00,0.90),true);
	DrawingWindow::addObject3D_to_Visual2D(window1, v2d1);
	DrawingWindow::addObject3D_to_Visual2D(window2, v2d1);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x+0.001,-100,-100+10*grid_y+5);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(window1);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x+5+0.001,-100,-100+10*grid_y);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(window2);

	//////////

	vector <Point3D*> vertices4;
	vector <Face*> faces4;
	
	//varfurile de jos
	vertices4.push_back(new Point3D(0,0,0));
	vertices4.push_back(new Point3D(n,0,0));
	vertices4.push_back(new Point3D(n,0,n));
	vertices4.push_back(new Point3D(0,0,n));
	//varfurile de sus
	vertices4.push_back(new Point3D(0,n,0));
	vertices4.push_back(new Point3D(n,n,0));
	vertices4.push_back(new Point3D(n,n,n));
	vertices4.push_back(new Point3D(0,n,n));
	
	//cele 6 fete
	vector <int> contour4;
	//fata jos
	contour4.clear();
	contour4.push_back(0);
	contour4.push_back(1);
	contour4.push_back(2);
	contour4.push_back(3);
	faces4.push_back(new Face(contour4));
	//fata sus
	contour4.clear();
	contour4.push_back(4);
	contour4.push_back(5);
	contour4.push_back(6);
	contour4.push_back(7);
	faces4.push_back(new Face(contour4));
	//fata fata
	contour4.clear();
	contour4.push_back(0);
	contour4.push_back(1);
	contour4.push_back(5);
	contour4.push_back(4);
	faces4.push_back(new Face(contour4));
	//fata dreapta
	contour4.clear();
	contour4.push_back(1);
	contour4.push_back(2);
	contour4.push_back(6);
	contour4.push_back(5);
	faces4.push_back(new Face(contour4));
	//fata spate
	contour4.clear();
	contour4.push_back(2);
	contour4.push_back(3);
	contour4.push_back(7);
	contour4.push_back(6);
	faces4.push_back(new Face(contour4));
	//fata stanga
	contour4.clear();
	contour4.push_back(3);
	contour4.push_back(0);
	contour4.push_back(4);
	contour4.push_back(7);
	faces4.push_back(new Face(contour4));

	cube = new Object3D(vertices4,faces4,Color(0,0,1), false);
	//DrawingWindow::addObject3D_to_Visual2D(cube, v2d1);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-100+10*grid_x,-100,-100+10*grid_y);
	Transform3D::isometricProjectionMatrix();
	Transform3D::applyTransform(cube);

}
House::~House(){}