#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <cmath>
#include <assert.h>
#include <fstream>

using namespace std;

/*
variable goes here
*/
float _cameraAngle = 0.0;
float sun_trans_x = -3.2;
float sun_trans_y = 2.45;
float test = 0.0;
float color_c1_r[3] = {200,200,200};
float color_c1_g[3]= { 200,200,200 };
float color_c1_b[3]= { 200,200,200 };


double base = 0.75;
double height = 1.40;
double slices = 50.0;
double stacks = 50.0;

float x1, y_1, x2, y2, x3, y3;
double radius = 0.5;
float angle;

float boat_1_move = 2.5;
float boat_1_scale_x = 0.25, boat_1_scale_y = 0.25;
float boat_1_position_x = 0.5;
bool sunset = false;
int sky_R = 59, sky_G = 153, sky_B = 250;

int l_house_color_R[9] = { 127, 154, 200, 237, 105, 239, 200, 154, 195 };
int l_house_color_G[9] = { 127, 154, 191, 28, 81, 191, 228, 154, 195 };
int l_house_color_B[9] = { 127, 78, 231, 36, 111, 231, 176, 78, 195 };


int r_house_color_R[6] = { 78, 236,21, 121,210,85 };
int r_house_color_G[6] = { 102, 200, 130, 113, 130, 30 };
int r_house_color_B[6] = { 103, 73, 120, 120, 218, 18 };

int water_color_R = 65, water_color_G = 180, water_color_B = 167;

// ENDS HEre

void makeNight() {
	for (int i = 0; i < 9; i++) {
		l_house_color_R[i] = 51;
		l_house_color_G[i] = 51;
		l_house_color_B[i] = 51;
	}

	for (int i = 0; i < 6; i++) {
		r_house_color_R[i] = 51;
		r_house_color_G[i] = 51;
		r_house_color_B[i] = 51;
	}
	for (int i = 0; i < 3; i++) {
		color_c1_r[i] = 51;
		color_c1_g[i] = 51;
		color_c1_b[i] = 51;
	}

	sky_R = sky_G = sky_B = 100;
	water_color_R = 0;
	water_color_G = 125;
	water_color_B = 255;
}

void makeSunrise() {
	int l_house_color_R_copy[9] = { 127, 154, 200, 237, 105, 239, 200, 154, 195 };
	int l_house_color_G_copy[9] = { 127, 154, 191, 28, 81, 191, 228, 154, 195 };
	int l_house_color_B_copy[9] = { 127, 78, 231, 36, 111, 231, 176, 78, 195 };

	int r_house_color_R_copy[6] = { 78, 236,21, 121,210,85 };
	int r_house_color_G_copy[6] = { 102, 200, 130, 113, 130, 30 };
	int r_house_color_B_copy[6] = { 103, 73, 120, 120, 218, 18 };

	water_color_R = 65, water_color_G = 180, water_color_B = 167;
	sky_R = 59, sky_G = 153, sky_B = 250;

	for (int i = 0; i < 9; i++) {
		l_house_color_R[i] = l_house_color_R_copy[i];
		l_house_color_G[i] = l_house_color_G_copy[i];
		l_house_color_B[i] = l_house_color_B_copy[i];
	}

	for (int i = 0; i < 6; i++) {
		r_house_color_R[i] = r_house_color_R_copy[i];
		r_house_color_G[i] = r_house_color_G_copy[i];
		r_house_color_B[i] = r_house_color_B_copy[i];
	}
	for (int i = 0; i < 3; i++) {
		color_c1_r[i] = 200;
		color_c1_g[i] = 200;
		color_c1_b[i] = 200;
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


//Draw circle function
void drawCircle(float rad, float r, float g, float b) {

	glBegin(GL_POLYGON);
	//chooseColor(r,g,b);
	glColor3ub(r, g, b);
	for (int i = 0; i<100; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 100;
		float r = rad;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}

	glEnd();
}


//draws and joints multiple shapes and creates a boat untransformed...AUTHOR:RAFAT
void getBoat()
{
	float insideBoat_R = 15, insideBoat_G = 16, insideBoat_B = 11;
	float outsideBoat_R = 69, outsideBoat_G = 69, outsideBoat_B = 69;

	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B);
	glBegin(GL_POLYGON);
	glVertex3f(-1, .5, 1);
	glVertex3f(0, .5, 1.5);
	glVertex3f(0, 1.5, 1.75);
	glEnd();

	glColor3ub(insideBoat_R, insideBoat_G, insideBoat_B); // inside
	glBegin(GL_POLYGON);
	glVertex3f(-.90, .5, 1);
	glVertex3f(0, .5, 1.5);
	glVertex3f(0, 1.40, 1.75);
	glEnd();

	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B);
	glBegin(GL_POLYGON);
	glVertex3f(0, .5, 1.5);
	glVertex3f(1, .5, 1);
	glVertex3f(0, 1.5, 1.75);
	glEnd();
	glColor3ub(insideBoat_R, insideBoat_G, insideBoat_B); // inside
	glBegin(GL_POLYGON);
	glVertex3f(0, .5, 1.5);
	glVertex3f(.90, .5, 1);
	glVertex3f(0, 1.40, 1.75);
	glEnd();

	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.25);
	glVertex3f(.5, 0, 0.25);
	glVertex3f(1, .5, 1);
	glVertex3f(0, .5, 1.5);
	glEnd();
	glColor3ub(insideBoat_R, insideBoat_G, insideBoat_B); // inside
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.10, 0.25);
	glVertex3f(.45, 0.10, 0.25);
	glVertex3f(.9, .5, 1);
	glVertex3f(0, .5, 1.5);
	glEnd();

	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B);
	glBegin(GL_POLYGON);
	glVertex3f(-.5, 0, 0.25);
	glVertex3f(0, 0, 0.25);
	glVertex3f(0, .5, 1.5);
	glVertex3f(-1, .5, 1);
	glEnd();
	glColor3ub(insideBoat_R, insideBoat_G, insideBoat_B); // inside
	glBegin(GL_POLYGON);
	glVertex3f(-.40, 0.10, 0.25);
	glVertex3f(0, 0.1, 0.25);
	glVertex3f(0, 0.5, 1.5);
	glVertex3f(-.9, .5, 1);
	glEnd();

	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B);
	glBegin(GL_POLYGON);
	glVertex3f(-1, .5, 1);
	glVertex3f(-.5, .3, -1);
	glVertex3f(-.5, 0, -1);
	glVertex3f(-.5, 0, .25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, .5, 1);
	glVertex3f(.5, .3, -1);
	glVertex3f(.5, 0, -1);
	glVertex3f(.5, 0, .25);
	glEnd();

	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B);
	glBegin(GL_POLYGON);
	glVertex3f(.5, 0, -1);
	glVertex3f(-.5, 0, -1);
	glVertex3f(-.75, .3, -1);
	glVertex3f(0, .45, -1);
	glVertex3f(.75, .3, -1);
	glEnd();
	glColor3ub(outsideBoat_R, outsideBoat_G, outsideBoat_B); // inside
	glBegin(GL_POLYGON);
	glVertex3f(.45, 0.05, -1);
	glVertex3f(-.45, 0.05, -1);
	glVertex3f(-.65, .25, -1);
	glVertex3f(0, .4, -1);
	glVertex3f(.65, .25, -1);
	glEnd();


}

// takes the boat and applies some transformations and has animation and rotation transformations...AUTHOR:RAFAT
void drawBoats()
{
	glPushMatrix();
	glTranslatef(0, -1, 1);
	glScalef(0.4, 0.4, 0);
	getBoat();
	glPopMatrix();
}


void drawPrivateCar() {
	//drawing car starts here
	//_-_-_-_-_-_-_-_-_-_-_-_-
	glPushMatrix();
	glRotatef(2, 0, 0, 1);
	glTranslatef(-0.2, 0.5, 0);
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);//(R,G,B)
	glVertex3f(0.57, -0.2, 0.0);
	glVertex3f(0.23, -0.2, 0.0);
	glVertex3f(0.2, -0.4, 0.0);
	glVertex3f(0.6, -0.4, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);//(R,G,B)
	glVertex3f(0.6, -0.4, 0.0);
	glVertex3f(0.2, -0.4, 0.0);
	glVertex3f(0.15, -0.55, 0.0);
	glVertex3f(0.65, -0.55, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);//(R,G,B)
	glVertex3f(0.55, -0.43, 0.0);
	glVertex3f(0.24, -0.43, 0.0);
	glVertex3f(0.19, -0.51, 0.0);
	glVertex3f(0.61, -0.51, 0.0);
	glEnd();



	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);//(R,G,B)
	glVertex3f(0.15, -0.55, 0.0);
	glVertex3f(0.65, -0.55, 0.0);
	glVertex3f(0.65, -0.65, 0.0);
	glVertex3f(0.15, -0.65, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);//(R,G,B)
	glVertex3f(0.3, -0.58, 0.0);
	glVertex3f(0.5, -0.58, 0.0);
	glVertex3f(0.5, -0.62, 0.0);
	glVertex3f(0.3, -0.62, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);//(R,G,B)
	glVertex3f(0.19, -0.57, 0.0);
	glVertex3f(0.24, -0.57, 0.0);
	glVertex3f(0.24, -0.63, 0.0);
	glVertex3f(0.19, -0.63, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);//(R,G,B)
	glVertex3f(0.58, -0.57, 0.0);
	glVertex3f(0.62, -0.57, 0.0);
	glVertex3f(0.62, -0.63, 0.0);
	glVertex3f(0.58, -0.63, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.6, 0.3);//(R,G,B)
	glVertex3f(0.65, -0.55, 0.0);
	glVertex3f(0.6, -0.4, 0.0);
	glVertex3f(0.57, -0.2, 0.0);
	glVertex3f(0.583, -0.2, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);//(R,G,B)
	glVertex3f(0.65, -0.55, 0.0);
	glVertex3f(0.6, -0.4, 0.0);
	glVertex3f(0.57, -0.2, 0.0);
	glVertex3f(0.583, -0.2, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);//(R,G,B)
	glVertex3f(0.15, -0.55, 0.0);
	glVertex3f(0.2, -0.4, 0.0);
	glVertex3f(0.23, -0.2, 0.0);
	glVertex3f(0.22, -0.2, 0.0);
	glEnd();

	glPopMatrix();

	//_________________----------- car ends here
}

void drawBus() {

	//-----------------------bus start here
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);//(R,G,B)
	glVertex3f(-0.9, -0.9, 0.0);
	glVertex3f(-0.4, -0.9, 0.0);
	glVertex3f(-0.3, -1.5, 0.0);
	glVertex3f(-1.0, -1.5, 0.0);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);//(R,G,B)
	glVertex3f(-0.3, -1.5, 0.0);
	glVertex3f(-1.0, -1.5, 0.0);
	glVertex3f(-1.0, -2.1, 0.0);
	glVertex3f(-0.3, -2.1, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-0.33, -1.55, 0.0);
	glVertex3f(-0.96, -1.55, 0.0);
	glVertex3f(-0.96, -1.95, 0.0);
	glVertex3f(-0.33, -1.95, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-0.33, -2.0, 0.0);
	glVertex3f(-0.96, -2.0, 0.0);
	glVertex3f(-0.96, -2.05, 0.0);
	glVertex3f(-0.33, -2.05, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.43, -2.0, 0.0);
	glVertex3f(-0.86, -2.0, 0.0);
	glVertex3f(-0.86, -2.05, 0.0);
	glVertex3f(-0.43, -2.05, 0.0);
	glEnd();

	glPopMatrix();

	//________________
	//bus ends here

}

/*

void drawTree_1() {
	//---------------------------------------
	//Drawing Tree starts here
	//---------------------------------------

	glPushMatrix(); //cone 1
	glColor3f(0.0, 0.3, 0.0);
	glTranslated(0.0, 0.5, -10);
	glRotated(65, -1.0, 0.0, 0.0);
	glutSolidCone(base, height, slices, stacks);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.0, 1.0); //cone 2
	glColor3f(0.0, 0.3, 0.0);
	glTranslated(0.0, 0.5, -10);
	glRotated(65, -1.0, 0.0, 0.0);
	glutSolidCone(base, height, slices, stacks);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.01, 2.0, 1.0); //cone 3
	glColor3f(0.0, 0.3, 0.0);
	glTranslated(0.0, 0.5, -10);
	glRotated(65, -1.0, 0.0, 0.0);
	glutSolidCone(base, height, slices, stacks);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS); //lower part
	glColor3ub(102, 51, 0);
	glVertex2f(-0.03, 0.1);
	glVertex2f(-0.03, -0.5);
	glVertex2f(0.1, -0.5);
	glVertex2f(0.1, 0.1);
	glEnd();
	glPopMatrix();

	//---------------------------------------
	//Drawing tree ends here
	//---------------------------------------
}
*/
void drawTree_2() {

	//---------------------------------------
	//Drawing tree starts here
	//---------------------------------------
	glPushMatrix();
	glTranslated(-0.5, 0.0, 0.0);
	glColor3ub(102, 51, 0);
	glBegin(GL_TRIANGLES);

	//Triangle

	glVertex3f(2.3, -1.0, 0.0);
	glVertex3f(2.0, -0.2, 0.0);
	glVertex3f(1.8, -1.0, 0.0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, -0.5, 0.0);
	x1 = 0.5, y_1 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y_1);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle) * radius;
		y2 = y_1 + cos(angle) * radius;
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	//---------------------------------------
	//Drawing tree ends here
	//---------------------------------------
}


void drawTree_3() {

	//---------------------------------------
	//Drawing tree starts here
	//---------------------------------------

	glPushMatrix();
	glTranslatef(-0.15, -0.6, 0.0);
	glBegin(GL_QUADS); //lower part
	glColor3ub(102, 51, 0);
	glVertex2f(-0.7, 0.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(-0.7, -1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix(); //circle 1
	glTranslated(-1.5, -0.5, 0.0);
	x2 = 0.5, y2 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x3 = x2 + sin(angle) * radius;
		y3 = y2 + cos(angle) * radius;
		glVertex2f(x3, y3);
	}
	glEnd();
	glPopMatrix();

	////////////////////////////
	glPushMatrix(); //circle 2
	glTranslated(-1.9, -0.9, 0.0);
	x2 = 0.5, y2 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x3 = x2 + sin(angle) * radius;
		y3 = y2 + cos(angle) * radius;
		glVertex2f(x3, y3);
	}
	glEnd();
	glPopMatrix();
	////////////////////////////

	glPushMatrix(); //circle 3
	glTranslated(-1.1, -0.9, 0.0);
	x2 = 0.5, y2 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x3 = x2 + sin(angle) * radius;
		y3 = y2 + cos(angle) * radius;
		glVertex2f(x3, y3);
	}
	glEnd();
	glPopMatrix();

	//---------------------------------------
	//Drawing tree ends here
	//---------------------------------------
}

void drawTree_4() {


	//---------------------------------------
	//Drawing tree starts here
	//---------------------------------------
	glTranslatef(3.3, -1.5, 0.0);
	glPushMatrix();
	glTranslatef(-0.15, -0.6, 0.0);
	glBegin(GL_QUADS); //lower part
	glColor3ub(102, 51, 0);
	glVertex2f(-0.7, 0.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(-0.7, -1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix(); //circle 1
	glTranslated(-1.5, -0.5, 0.0);
	x2 = 0.5, y2 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x3 = x2 + sin(angle) * radius;
		y3 = y2 + cos(angle) * radius;
		glVertex2f(x3, y3);
	}
	glEnd();
	glPopMatrix();

	////////////////////////////
	glPushMatrix(); //circle 2
	glTranslated(-1.9, -0.9, 0.0);
	x2 = 0.5, y2 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x3 = x2 + sin(angle) * radius;
		y3 = y2 + cos(angle) * radius;
		glVertex2f(x3, y3);
	}
	glEnd();
	glPopMatrix();
	////////////////////////////

	glPushMatrix(); //circle 3
	glTranslated(-1.1, -0.9, 0.0);
	x2 = 0.5, y2 = 0.6;
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x3 = x2 + sin(angle) * radius;
		y3 = y2 + cos(angle) * radius;
		glVertex2f(x3, y3);
	}
	glEnd();
	glPopMatrix();

	//---------------------------------------
	//Drawing tree ends here
	//---------------------------------------


}

//makes tiny cloud parts using circle and polygons... AUTHOR: RAFAT
void getCloudlet(float r, float g, float b)
{
	glPushMatrix();
	drawCircle(.2, r, g, b);
	glPopMatrix();
}
//combines the cloudlets and makes a signle cloud...AUTHOR:RAFAT
void getCloud(float r, float g, float b)
{
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-.70, 0, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.50, .15, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.25, .25, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, .30, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.25, .25, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.50, .15, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.70, 0, 0);
	getCloudlet(r, g, b);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glPushMatrix();
	glTranslatef(-.70, 0, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.50, .15, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.25, .25, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, .30, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.25, .25, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.50, .15, 0);
	getCloudlet(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.70, 0, 0);
	getCloudlet(r, g, b);
	glPopMatrix();
	glPopMatrix();

	glColor3f(r / 255.0, g / 255.0, b / 255.0);
	glBegin(GL_POLYGON);
	glVertex3f(-.5, -.15, 0);
	glVertex3f(.5, -.15, 0);
	glVertex3f(.5, .15, 0);
	glVertex3f(-.5, .15, 0);
	glEnd();
	glPopMatrix();
}
//draws 3 clouds with differend transformations...AUTHOR:RAFAT
void drawClouds(float r, float g, float b)
{
	glPushMatrix();
	glScalef(1, .5, 1);

	glPushMatrix();
	glTranslatef(-2, 4, 0);
	getCloud(color_c1_r[0], color_c1_g[0], color_c1_b[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 3.75, 0);
	getCloud(color_c1_r[1], color_c1_g[1], color_c1_b[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4.4, 0);
	getCloud(color_c1_r[2], color_c1_g[2], color_c1_b[2]);
	glPopMatrix();
	glPopMatrix();
}

//draws banner...
void drawBanner(char *text, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

}


//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units


								  //Use this color function
								  // max (R,G,B) 0- 255


								  //---------------------------------------
								  //Water drawing starts here
								  //---------------------------------------
	glColor3ub(water_color_R, water_color_G, water_color_B);

	glBegin(GL_POLYGON);
	glVertex3f(-4.0, -3.0, 0.0);
	glVertex3f(4.0, -3.0, 0.0);
	glVertex3f(4.0, -1.5, 0.0);
	glVertex3f(0.4, 0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(-4.0, -1.8, 0.0);
	glEnd();



	//---------------------------------------
	//Water drawing ends here
	//---------------------------------------


	//---------------------------------------
	//Drawing sky starts Here
	//---------------------------------------
	glPushMatrix();
	glColor3ub(sky_R, sky_G, sky_B);
	glBegin(GL_POLYGON);
	glVertex3f(-4.0, 3.0, 0.0);
	glVertex3f(-4.0, -1.8, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(4.0, 3.0, 0.0);
	glVertex3f(4.0, -1.5, 0.0);
	glVertex3f(0.4, 0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glEnd();

	glPopMatrix();

	//water part
	glColor3ub(water_color_R, water_color_G, water_color_B);
	glBegin(GL_POLYGON);
	glVertex3f(-4.0, -1.8, 0);
	glVertex3f(-3.35, -1.45, 0);
	glVertex3f(-4.0, -1.45, 0);
	glEnd();
	//---------------------------------------
	//Drawing sky ends here
	//---------------------------------------

	//---------------------------------------
	//Drawing Sun starts here
	//---------------------------------------

	glPushMatrix();
	glTranslatef(sun_trans_x, sun_trans_y, 0.0);
	drawCircle(0.4, 255, 200, 66);
	drawCircle(0.3, 255, 207, 90);
	drawCircle(0.2, 255, 213, 110);
	glPopMatrix();
	//---------------------------------------
	//Drawing Sun ends here
	//---------------------------------------

	//---------------------------------------
	//Drawing Cloud starts here
	//--------------------------------------

	//---------------------------------------
	//Drawing Cloud ends here
	//--------------------------------------

	//---------------------------------------
	//Drawing House starts here
	//---------------------------------------
	//LEFT SIDE
	//1st house
	glColor3ub(l_house_color_R[0], l_house_color_G[0], l_house_color_B[0]);
	glBegin(GL_POLYGON);
	glVertex3f(-4.0, 1.8, 0.0);
	glVertex3f(-4.0, -1.5, 0.0);
	glVertex3f(-3.4, -1.458, 0.0);
	glVertex3f(-3.4, 1.8, 0.0);
	glEnd();



	glColor3ub(l_house_color_R[1], l_house_color_G[1], l_house_color_B[1]);
	glBegin(GL_POLYGON);
	glVertex3f(-3.4, -1.458, 0.0);
	glVertex3f(-2.3, -0.83, 0.0);
	glVertex3f(-2.3, 1.6, 0.0);
	glVertex3f(-3.4, 1.8, 0.0);
	glEnd();

	//Separator starts here
	glColor3ub(50, 50, 50);
	glBegin(GL_POLYGON);
	glVertex3f(-4.0, 0.62, 0.0);
	glVertex3f(-3.4, 0.62, 0.0);
	glVertex3f(-3.4, 0.50, 0.0);
	glVertex3f(-4.0, 0.50, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-3.4, 0.50, 0.0);
	glVertex3f(-2.3, 0.6, 0.0);
	glVertex3f(-2.3, 0.7, 0.0);
	glVertex3f(-3.4, 0.62, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-4.0, -0.70, 0.0);
	glVertex3f(-3.4, -0.70, 0.0);
	glVertex3f(-3.4, -0.62, 0.0);
	glVertex3f(-4.0, -0.62, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-3.4, -0.70, 0.0);
	glVertex3f(-2.3, -0.3, 0.0);
	glVertex3f(-2.3, -0.24, 0.0);
	glVertex3f(-3.4, -0.62, 0.0);
	glEnd();

	//Separator ends here


	//Windows starts here
	glColor3ub(37, 28, 36);
	float leftSideWin[6] = { 0.0,-0.4,-0.8,
		-1.4,-2.0,-2.6 };


	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslatef(0.1, leftSideWin[i], 0.0);
		glBegin(GL_POLYGON);
		glVertex3f(-3.9, 1.5, 0.0);
		glVertex3f(-3.7, 1.5, 0.0);
		glVertex3f(-3.7, 1.7, 0.0);
		glVertex3f(-3.9, 1.7, 0.0);
		glEnd();
		glPopMatrix();
	}

	//////////Middle top window//////////////
	glColor3ub(195, 195, 195);
	glBegin(GL_POLYGON);
	glVertex3f(-3.1, 0.9, 0.0);
	glVertex3f(-2.5, 0.88, 0.0);
	glVertex3f(-2.5, 1.22, 0.0);
	glVertex3f(-3.1, 1.3, 0.0);
	glEnd();

	glColor3ub(0.0, 0.0, 0.0);
	for (float i = 0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-3.1, 0.9 + i, 0.0);
		glVertex3f(-2.5, 0.88 + i, 0.0);
		glVertex3f(-2.5, 1.22 + i, 0.0);
		glVertex3f(-3.1, 1.3 + i, 0.0);
		glEnd();
	}
	///////////////////////////////////


	//////////Middle Middle window//////////////
	glColor3ub(195, 195, 195);
	glBegin(GL_POLYGON);
	glVertex3f(-3.1, -0.2, 0.0);
	glVertex3f(-2.5, -0.05, 0.0);
	glVertex3f(-2.5, 0.30, 0.0);
	glVertex3f(-3.1, 0.2, 0.0);
	glEnd();

	glColor3ub(0.0, 0.0, 10.0);
	for (float i = 0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-3.1, -0.2 + i, 0.0);
		glVertex3f(-2.5, -0.05 + i, 0.0);
		glVertex3f(-2.5, 0.30 + i, 0.0);
		glVertex3f(-3.1, 0.2 + i, 0.0);
		glEnd();
	}
	//////////Middle Middle window ends here//////////////

	//windows ends here
	//1st house end here

	//2nd house start here
	glColor3ub(l_house_color_R[2], l_house_color_G[2], l_house_color_B[2]);
	glBegin(GL_POLYGON);
	glVertex3f(-2.3, -0.83, 0.0);
	glVertex3f(-1.85, -0.57, 0.0);
	glVertex3f(-1.85, 1.3, 0.0);
	glVertex3f(-2.3, 1.4, 0.0);
	glEnd();

	//Windows starts here
	glColor3ub(209, 195, 41);

	glBegin(GL_POLYGON);
	glVertex3f(-2.21, 1.24, 0);
	glVertex3f(-2.21, 0.90, 0);
	glVertex3f(-1.95, 0.92, 0);
	glVertex3f(-1.95, 1.18, 0);
	glEnd();

	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-2.21, 0.90 + i, 0);
		glVertex3f(-1.95, 0.92 + i, 0);
		glVertex3f(-1.95, 1.18 + i, 0);
		glVertex3f(-2.21, 1.24 + i, 0);
		glEnd();
	}

	glColor3ub(209, 195, 41);
	glPushMatrix();
	glTranslatef(0.0, -0.9, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-2.21, 1.26, 0);
	glVertex3f(-2.21, 0.90, 0);
	glVertex3f(-1.95, 0.96, 0);
	glVertex3f(-1.95, 1.3, 0);
	glEnd();
	glPopMatrix();

	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.01; i += 0.001) {
		glPushMatrix();
		glTranslatef(0.0, -0.9, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-2.21, 1.26 + i, 0);
		glVertex3f(-2.21, 0.90 + i, 0);
		glVertex3f(-1.95, 0.96 + i, 0);
		glVertex3f(-1.95, 1.3 + i, 0);
		glEnd();
		glPopMatrix();
	}

	//Windows ends here

	//separator starts here
	glColor3ub(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-2.3, 0.7, 0.0);
	glVertex3f(-1.82, 0.75, 0.0);
	glVertex3f(-1.82, 0.78, 0.0);
	glVertex3f(-2.3, 0.74, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0, -1.3, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-2.3, 0.78, 0.0);
	glVertex3f(-1.82, 0.9, 0.0);
	glVertex3f(-1.82, 0.98, 0.0);
	glVertex3f(-2.3, 0.70, 0.0);
	glEnd();
	glPopMatrix();
	//separator ends here


	//2nd house ens here

	//3rd house starts here
	glColor3ub(l_house_color_R[3], l_house_color_G[3], l_house_color_B[3]);
	glBegin(GL_POLYGON);
	glVertex3f(-1.85, -0.57, 0.0);
	glVertex3f(-1.7, -0.5, 0.0);
	glVertex3f(-1.7, 1.4, 0.0);
	glVertex3f(-1.85, 1.3, 0.0);
	glEnd();

	glColor3ub(l_house_color_R[4], l_house_color_G[4], l_house_color_B[4]);
	glBegin(GL_POLYGON);
	glVertex3f(-1.7, -0.5, 0.0);
	glVertex3f(-1.3, -0.26, 0.0);
	glVertex3f(-1.3, 1.3, 0.0);
	glVertex3f(-1.7, 1.4, 0.0);
	glEnd();

	//separator starts here
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-1.7, 0.7, 0);
	glVertex3f(-1.3, 0.7, 0);

	glVertex3f(-1.7, 0.08, 0);
	glVertex3f(-1.3, 0.2, 0);
	glEnd();

	//separator starts ends

	//windows starts here
	glColor3ub(236, 236, 236);
	glBegin(GL_POLYGON);
	glVertex3f(-1.63, 1.14, 0);
	glVertex3f(-1.63, 0.8, 0);
	glVertex3f(-1.37, 0.80, 0);
	glVertex3f(-1.37, 1.06, 0);
	glEnd();

	glColor3ub(20, 20, 20);
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.63 + i, 1.14 + i, 0);
		glVertex3f(-1.63 + i, 0.8 + i, 0);
		glVertex3f(-1.37 + i, 0.80 + i, 0);
		glVertex3f(-1.37 + i, 1.06 + i, 0);
		glEnd();
	}

	glPushMatrix();
	glColor3ub(236, 236, 236);
	glTranslatef(0.0, -0.6, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.63, 1.14, 0);
	glVertex3f(-1.63, 0.8, 0);
	glVertex3f(-1.37, 0.9, 0);
	glVertex3f(-1.37, 1.16, 0);
	glEnd();

	glColor3ub(20, 20, 20);
	//glTranslatef(0.0,-0.6,0);
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.63 + i, 1.14 + i, 0);
		glVertex3f(-1.63 + i, 0.8 + i, 0);
		glVertex3f(-1.37 + i, 0.9 + i, 0);
		glVertex3f(-1.37 + i, 1.16 + i, 0);
		glEnd();
	}

	glPopMatrix();
	//windows end here


	//3rd house ends here

	//4th house starts here
	glColor3ub(l_house_color_R[5], l_house_color_G[5], l_house_color_B[5]);
	glBegin(GL_POLYGON);
	glVertex3f(-1.3, -0.26, 0.0);
	glVertex3f(-1.12, -0.16, 0.0);
	glVertex3f(-1.12, 1.18, 0.0);
	glVertex3f(-1.3, 1.2, 0.0);
	glEnd();


	// separator ends here

	//4th house ends here


	//5th house starts here

	glColor3ub(l_house_color_R[6], l_house_color_G[6], l_house_color_B[6]);
	glBegin(GL_POLYGON);
	glVertex3f(-1.12, -0.16, 0.0);
	glVertex3f(-1.0, -0.1, 0.0);
	glVertex3f(-1.0, 1.22, 0.0);
	glVertex3f(-1.12, 1.18, 0.0);
	glEnd();

	glColor3ub(l_house_color_R[7], l_house_color_G[7], l_house_color_B[7]);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, -0.1, 0.0);
	glVertex3f(-0.78, 0.02, 0.0);
	glVertex3f(-0.78, 1.2, 0.0);
	glVertex3f(-1.0, 1.22, 0.0);
	glEnd();

	//separator starts here
	glColor3ub(12, 20, 10);
	glBegin(GL_LINES);
	for (float i = 0; i < 0.005; i += 0.001) {
		glVertex3f(-1.12, 0.88 + i, 0.0);
		glVertex3f(-1.0, 0.9 + i, 0.0);
		glVertex3f(-1.0, 0.9 + i, 0.0);
		glVertex3f(-0.78, 0.9 + i, 0.0);
	}
	for (float i = 0; i < 0.005; i += 0.001) {
		glVertex3f(-1.12, 0.2 + i, 0.0);
		glVertex3f(-1.0, 0.2 + i, 0.0);
		glVertex3f(-1.0, 0.20 + i, 0.0);
		glVertex3f(-0.78, 0.30 + i, 0.0);
	}

	glEnd();
	//separator ends here

	//Windows starts here
	glPushMatrix();
	glColor3ub(243, 156, 156);
	glTranslatef(-0.15, 0.55, 0);
	glScalef(0.5, 0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.63, 1.14, 0);
	glVertex3f(-1.63, 0.8, 0);
	glVertex3f(-1.37, 0.80, 0);
	glVertex3f(-1.37, 1.06, 0);
	glEnd();
	glColor3ub(10, 10, 10);
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.63 + i, 1.14 + i, 0);
		glVertex3f(-1.63 + i, 0.8 + i, 0);
		glVertex3f(-1.37 + i, 0.80 + i, 0);
		glVertex3f(-1.37 + i, 1.06 + i, 0);
		glEnd();
	}

	glPopMatrix();

	glPushMatrix();
	glColor3ub(243, 156, 156);
	glTranslatef(-0.15, 0.2, 0);
	glScalef(0.5, 0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.63, 1.05, 0);
	glVertex3f(-1.63, 0.8, 0);
	glVertex3f(-1.37, 0.80, 0);
	glVertex3f(-1.37, 1.06, 0);
	glEnd();
	glColor3ub(10, 10, 10);
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.63 + i, 1.05 + i, 0);
		glVertex3f(-1.63 + i, 0.8 + i, 0);
		glVertex3f(-1.37 + i, 0.80 + i, 0);
		glVertex3f(-1.37 + i, 1.06 + i, 0);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	glColor3ub(243, 156, 156);
	glTranslatef(-0.15, 0.0, 0);
	glScalef(0.5, 0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.63, 1.05, 0);
	glVertex3f(-1.63, 0.8, 0);
	glVertex3f(-1.37, 0.80, 0);
	glVertex3f(-1.37, 1.06, 0);
	glEnd();
	glColor3ub(10, 10, 10);
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.63 + i, 1.05 + i, 0);
		glVertex3f(-1.63 + i, 0.8 + i, 0);
		glVertex3f(-1.37 + i, 0.80 + i, 0);
		glVertex3f(-1.37 + i, 1.06 + i, 0);
		glEnd();
	}
	glPopMatrix();
	//windows ends here


	//5th house ends here


	//6th house starts here
	glColor3ub(l_house_color_R[8], l_house_color_G[8], l_house_color_B[8]);
	glBegin(GL_POLYGON);
	glVertex3f(-0.78, 0.02, 0.0);
	glVertex3f(0.0, 0.45, 0.0);
	glVertex3f(0.0, 0.95, 0.0);
	glVertex3f(-0.78, 1.1, 0.0);
	glEnd();

	//separator starts here
	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.005; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(-0.78, 0.9 + i, 0.0);
		glVertex3f(0.0, 0.8 + i, 0.0);

		glVertex3f(-0.78, 0.2 + i, 0.0);
		glVertex3f(0.0, 0.6 + i, 0.0);
		glEnd();
	}
	//separator ends here

	//shades starts her

	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	//vertical line
	glVertex3f(-0.6, 0.87, 0);
	glVertex3f(-0.6, 0.28, 0);

	glVertex3f(-0.3, 0.83, 0);
	glVertex3f(-0.3, 0.46, 0);

	glVertex3f(-0.1, 0.83, 0);
	glVertex3f(-0.1, 0.54, 0);
	//Horizontal lines
	glVertex3f(-0.78, 0.72, 0);
	glVertex3f(0.0, 0.7, 0);

	glVertex3f(-0.78, 0.4, 0);
	glVertex3f(0.0, 0.65, 0);
	glEnd();
	//shades ends here

	//6th house ends here



	//Right sides house
	//1st house starts here
	glColor3ub(r_house_color_R[0], r_house_color_G[0], r_house_color_B[0]);
	glBegin(GL_POLYGON);
	glVertex3f(2.7, -0.8, 0.0);
	glVertex3f(4.0, -1.5, 0.0);
	glVertex3f(4.0, 1.8, 0.0);
	glVertex3f(2.7, 1.52, 0.0);
	glEnd();

	//separator starts here
	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(4.0, 1.3 + i, 0.0);
		glVertex3f(2.7, 1.15 + i, 0.0);

		glVertex3f(4.0, -0.9 + i, 0.0);
		glVertex3f(2.7, -0.35 + i, 0.0);
		glEnd();
	}
	//separator ends here

	//Windows starts here
	glColor3ub(100, 100, 100);
	glBegin(GL_POLYGON);
	glVertex3f(3.2, 0.085, 0);
	glVertex3f(3.7, -0.11, 0);
	glVertex3f(3.7, 0.81, 0);
	glVertex3f(3.2, 0.75, 0);
	glEnd();

	for (float i = 0; i < 0.05; i += 0.001) {
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(3.2 - i, 0.09 - i, 0);
		glVertex3f(3.7 + i, -0.11 - i, 0);
		glVertex3f(3.7 + i, 0.81 + i, 0);
		glVertex3f(3.2 - i, 0.75 + i, 0);
		glEnd();
	}

	//Windows ends here

	//1st house ends here

	//2nd house starts here
	glColor3ub(r_house_color_R[1], r_house_color_G[1], r_house_color_B[1]);
	glBegin(GL_POLYGON);
	glVertex3f(1.8, -0.29, 0.0);
	glVertex3f(2.7, -0.8, 0.0);
	glVertex3f(2.7, 1.4, 0.0);
	glVertex3f(1.8, 1.2, 0.0);

	glEnd();

	//separator starts here
	glColor3ub(20, 20, 20);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(2.7, 0.95 + i, 0.0);
		glVertex3f(1.8, 0.85 + i, 0.0);

		glVertex3f(2.7, -0.25 + i, 0.0);
		glVertex3f(1.8, 0.0 + i, 0.0);
		glEnd();
	}
	//separator ends here

	//Windows starts here
	glPushMatrix();
	glTranslatef(-0.04, 0.08, 0);
	glPushMatrix();
	glColor3ub(255, 255, 250);
	glBegin(GL_POLYGON);
	glVertex3f(2.41, 0.43, 0.0);
	glVertex3f(2.63, 0.43, 0.0);
	glVertex3f(2.63, 0.7, 0.0);
	glVertex3f(2.41, 0.65, 0.0);
	glEnd();

	glColor3ub(5, 5, 5);
	for (float i = 0; i < 0.02; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(2.41 - i, 0.43 - i, 0.0);
		glVertex3f(2.63 + i, 0.43 - i, 0.0);
		glVertex3f(2.63 + i, 0.7 + i, 0.0);
		glVertex3f(2.41 - i, 0.65 + i, 0.0);
		glEnd();
	}
	glPopMatrix();

	//------------------------------
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0);
	glColor3ub(255, 255, 250);
	glBegin(GL_POLYGON);
	glVertex3f(2.41, 0.45, 0.0);
	glVertex3f(2.63, 0.45, 0.0);
	glVertex3f(2.63, 0.65, 0.0);
	glVertex3f(2.41, 0.61, 0.0);
	glEnd();

	glColor3ub(5, 5, 5);
	for (float i = 0; i < 0.02; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(2.41 - i, 0.45 - i, 0.0);
		glVertex3f(2.63 + i, 0.45 - i, 0.0);
		glVertex3f(2.63 + i, 0.65 + i, 0.0);
		glVertex3f(2.41 - i, 0.61 + i, 0.0);
		glEnd();
	}
	glPopMatrix();

	////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.0, -0.45, 0.0);
	glColor3ub(255, 255, 250);
	glBegin(GL_POLYGON);
	glVertex3f(2.41, 0.47, 0.0);
	glVertex3f(2.63, 0.43, 0.0);
	glVertex3f(2.63, 0.7, 0.0);
	glVertex3f(2.41, 0.7, 0.0);
	glEnd();

	glColor3ub(5, 5, 5);
	for (float i = 0; i < 0.02; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(2.41 - i, 0.47 - i, 0.0);
		glVertex3f(2.63 + i, 0.43 - i, 0.0);
		glVertex3f(2.63 + i, 0.7 + i, 0.0);
		glVertex3f(2.41 - i, 0.7 + i, 0.0);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.4, 0.0);
	glColor3ub(255, 255, 250);
	glBegin(GL_POLYGON);
	glVertex3f(2.41, 0.49, 0.0);
	glVertex3f(2.63, 0.45, 0.0);
	glVertex3f(2.63, 0.65, 0.0);
	glVertex3f(2.41, 0.65, 0.0);
	glEnd();

	glColor3ub(5, 5, 5);
	for (float i = 0; i < 0.02; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(2.41 - i, 0.49 - i, 0.0);
		glVertex3f(2.63 + i, 0.45 - i, 0.0);
		glVertex3f(2.63 + i, 0.65 + i, 0.0);
		glVertex3f(2.41 - i, 0.65 + i, 0.0);
		glEnd();
	}
	glPopMatrix();

	glPopMatrix();

	//Windows ends here

	//2nd house ends here


	//2nd and 3rd house space
	glColor3ub(r_house_color_R[2], r_house_color_G[2], r_house_color_B[2]);
	glBegin(GL_POLYGON);
	glVertex3f(1.62, -0.2, 0.0);
	glVertex3f(1.8, -0.3, 0.0);
	glVertex3f(1.8, 1.1, 0.0);
	glVertex3f(1.62, 1.1, 0.0);
	glEnd();
	/////////////////////////

	//3rd house starts here
	glColor3ub(r_house_color_R[3], r_house_color_G[3], r_house_color_B[3]);
	glBegin(GL_POLYGON);
	glVertex3f(1.3, 0.0, 0.0);
	glVertex3f(1.62, -0.18, 0.0);
	glVertex3f(1.62, 1.1, 0.0);
	glVertex3f(1.3, 1.18, 0.0);
	glEnd();

	//Windows starts here
	glColor3ub(200, 208, 200);
	glPushMatrix();
	glTranslatef(-0.07, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.93, 0.0);
	glVertex3f(1.62, 0.9, 0.0);
	glVertex3f(1.62, 1.05, 0.0);
	glVertex3f(1.5, 1.08, 0.0);
	glEnd();

	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(1.5 + i, 0.93 + i, 0.0);
		glVertex3f(1.62 + i, 0.9 + i, 0.0);
		glVertex3f(1.62 + i, 1.05 + i, 0.0);
		glVertex3f(1.5 + i, 1.08 + i, 0.0);
		glEnd();
	}
	glPopMatrix();

	glColor3ub(200, 208, 200);
	glPushMatrix();
	glTranslatef(-0.07, -0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.93, 0.0);
	glVertex3f(1.62, 0.9, 0.0);
	glVertex3f(1.62, 1.05, 0.0);
	glVertex3f(1.5, 1.08, 0.0);
	glEnd();

	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(1.5 + i, 0.93 + i, 0.0);
		glVertex3f(1.62 + i, 0.9 + i, 0.0);
		glVertex3f(1.62 + i, 1.05 + i, 0.0);
		glVertex3f(1.5 + i, 1.08 + i, 0.0);
		glEnd();
	}

	glPopMatrix();


	//Windows ends here

	glColor3ub(r_house_color_R[4], r_house_color_G[4], r_house_color_B[4]);
	glBegin(GL_POLYGON);
	glVertex3f(0.9, 0.2, 0.0);
	glVertex3f(1.3, 0.0, 0.0);
	glVertex3f(1.3, 1.18, 0.0);
	glVertex3f(0.9, 1.1, 0.0);

	glEnd();

	//windows start here
	glColor3ub(200, 208, 200);
	glPushMatrix();
	glTranslatef(-0.43, -0.35, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1.4, 0.87, 0.0);
	glVertex3f(1.62, 0.8, 0.0);
	glVertex3f(1.62, 1.05, 0.0);
	glVertex3f(1.4, 1.03, 0.0);
	glEnd();
	glColor3ub(10, 10, 10);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(1.4 + i, 0.87 + i, 0.0);
		glVertex3f(1.62 + i, 0.8 + i, 0.0);
		glVertex3f(1.62 + i, 1.05 + i, 0.0);
		glVertex3f(1.4 + i, 1.03 + i, 0.0);
		glEnd();
	}
	glPopMatrix();
	//windows ends here

	//separator starts here
	glColor3ub(20, 20, 20);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(1.62, 0.8 + i, 0.0);
		glVertex3f(1.30, 0.85 + i, 0.0);
		glVertex3f(1.30, 0.85 + i, 0.0);
		glVertex3f(0.90, 0.80 + i, 0.0);


		glVertex3f(1.62, 0.1 + i, 0.0);
		glVertex3f(1.30, 0.2 + i, 0.0);
		glVertex3f(1.30, 0.2 + i, 0.0);
		glVertex3f(0.90, 0.35 + i, 0.0);
		glEnd();
	}
	//separator ends here

	//3rd house ends here

	//4th house starts here
	glColor3ub(r_house_color_R[5], r_house_color_G[5], r_house_color_B[5]);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.42, 0.0);
	glVertex3f(0.9, 0.2, 0.0);
	glVertex3f(0.9, 0.98, 0.0);
	glVertex3f(0.5, 0.90, 0.0);
	glEnd();

	//separator starts here
	glColor3ub(20, 20, 20);
	for (float i = 0; i < 0.03; i += 0.001) {
		glBegin(GL_LINES);
		glVertex3f(0.90, 0.80 + i, 0.0);
		glVertex3f(0.50, 0.75 + i, 0.0);

		glVertex3f(0.90, 0.35 + i, 0.0);
		glVertex3f(0.50, 0.55 + i, 0.0);
		glEnd();
	}
	//separator ends here

	//Shades starts here
	glColor3ub(10, 10, 10);
	glBegin(GL_LINES);
	//Vertical shades
	glVertex3f(0.82, 0.82, 0);
	glVertex3f(0.82, 0.42, 0);

	glVertex3f(0.66, 0.80, 0);
	glVertex3f(0.66, 0.45, 0);

	glVertex3f(0.55, 0.80, 0);
	glVertex3f(0.55, 0.5, 0);
	//Horizontal shades
	glVertex3f(0.90, 0.74, 0);
	glVertex3f(0.52, 0.68, 0);

	glVertex3f(0.90, 0.48, 0);
	glVertex3f(0.52, 0.62, 0);
	glEnd();
	//Shades ends here

	//4th house ends here


	//---------------------------------------
	//Drawing House ends here
	//---------------------------------------

	// additional house work
	//Making pillar
	//Left house one start
	glColor3ub(0, 0, 0);
	for (float i = 0.0; i < 0.02; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-4.0 + i, -1.5 + i, 0.0);
		glVertex3f(-3.4 + i, -1.458 + i, 0.0);
		glVertex3f(-3.4 + i, 1.8 + i, 0.0);
		glVertex3f(-4.0 + i, 1.8 + i, 0.0);
		glEnd();
	}
	for (float i = 0.0; i < 0.02; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-3.4 + i, -1.458 + i, 0.0);
		glVertex3f(-2.3 + i, -0.83 + i, 0.0);
		glVertex3f(-2.3 + i, 1.6 + i, 0.0);
		glVertex3f(-3.4 + i, 1.8 + i, 0.0);
		glEnd();
	}

	//second house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-2.3 + i, -0.83 + i, 0.0);
		glVertex3f(-1.85 + i, -0.57 + i, 0.0);
		glVertex3f(-1.85 + i, 1.3 + i, 0.0);
		glVertex3f(-2.3 + i, 1.4 + i, 0.0);
		glEnd();
	}

	//third house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.85 + i, -0.57 + i, 0.0);
		glVertex3f(-1.7 + i, -0.5 + i, 0.0);
		glVertex3f(-1.7 + i, 1.4 + i, 0.0);
		glVertex3f(-1.85 + i, 1.3 + i, 0.0);
		glEnd();
	}


	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.7 + i, -0.5 + i, 0.0);
		glVertex3f(-1.3 + i, -0.26 + i, 0.0);
		glVertex3f(-1.3 + i, 1.3 + i, 0.0);
		glVertex3f(-1.7 + i, 1.4 + i, 0.0);
		glEnd();
	}

	//forth house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glBegin(GL_POLYGON);
		glVertex3f(-1.3 + i, -0.26 + i, 0.0);
		glVertex3f(-1.12 + i, -0.16 + i, 0.0);
		glVertex3f(-1.12 + i, 1.18 + i, 0.0);
		glVertex3f(-1.3 + i, 1.2 + i, 0.0);
		glEnd();
	}

	//fifth house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.12 + i, -0.16 + i, 0.0);
		glVertex3f(-1.0 + i, -0.1 + i, 0.0);
		glVertex3f(-1.0 + i, 1.22 + i, 0.0);
		glVertex3f(-1.12 + i, 1.18 + i, 0.0);
		glEnd();

	}
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1.0 + i, -0.1 + i, 0.0);
		glVertex3f(-0.78 + i, 0.02 + i, 0.0);
		glVertex3f(-0.78 + i, 1.2 + i, 0.0);
		glVertex3f(-1.0 + i, 1.22 + i, 0.0);
		glEnd();
	}

	//sixth house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.78 + i, 0.02 + i, 0.0);
		glVertex3f(0.0 + i, 0.45 + i, 0.0);
		glVertex3f(0.0 + i, 0.95 + i, 0.0);
		glVertex3f(-0.78 + i, 1.1 + i, 0.0);
		glEnd();
	}

	//Left sides additional works starts here
	//first house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(2.7 + i, -0.8 + i, 0.0);
		glVertex3f(4.0 + i, -1.5 + i, 0.0);
		glVertex3f(4.0 + i, 1.8 + i, 0.0);
		glVertex3f(2.7 + i, 1.52 + i, 0.0);
		glEnd();
	}
	//second house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(1.8 + i, -0.29 + i, 0.0);
		glVertex3f(2.7 + i, -0.8 + i, 0.0);
		glVertex3f(2.7 + i, 1.4 + i, 0.0);
		glVertex3f(1.8 + i, 1.2 + i, 0.0);
		glEnd();
	}
	//third house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.9 + i, 0.2 + i, 0.0);
		glVertex3f(1.3 + i, 0.0 + i, 0.0);
		glVertex3f(1.3 + i, 1.18 + i, 0.0);
		glVertex3f(0.9 + i, 1.1 + i, 0.0);

		glEnd();
	}

	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);

		glVertex3f(1.3 + i, 0.0 + i, 0.0);
		glVertex3f(1.62 + i, -0.18 + i, 0.0);
		glVertex3f(1.62 + i, 1.1 + i, 0.0);
		glVertex3f(1.3 + i, 1.18 + i, 0.0);
		glEnd();
	}

	//Third and forth house space
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(1.62 + i, -0.2 + i, 0.0);
		glVertex3f(1.8 + i, -0.3 + i, 0.0);
		glVertex3f(1.8 + i, 1.1 + i, 0.0);
		glVertex3f(1.62 + i, 1.1 + i, 0.0);
		glEnd();
	}

	//forth house
	for (float i = 0.0; i < 0.01; i += 0.001) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.5 + i, 0.42 + i, 0.0);
		glVertex3f(0.9 + i, 0.2 + i, 0.0);
		glVertex3f(0.9 + i, 0.98 + i, 0.0);
		glVertex3f(0.5 + i, 0.90 + i, 0.0);
		glEnd();
	}

	/////////////////////////////////////////
	glPushMatrix();
	glScalef(boat_1_scale_x, boat_1_scale_y, 0);
	glTranslatef(boat_1_position_x, boat_1_move, 0);
	drawBoats();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(-0.8, -0.2, 0);
	drawPrivateCar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, -1.0, 0);
	glScalef(0.7, 0.7, 0);
	drawPrivateCar();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(-1.5, -0.5, 0);
	drawBus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.7, -2.2, 0);
	glScalef(0.4, 0.2, 0);
//	drawTree_1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.85, 0.1, 0);
	glScalef(0.2, 0.12, 0);
//	drawTree_1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, -1.0, 0);
	glScalef(0.5, 0.5, 0);
	drawTree_2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.72, 0.5, 0);
	glScalef(0.3, 0.25, 0);
	drawTree_2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.2, -1.4, 0);
	glScalef(0.4, 0.3, 0);
	drawTree_3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.9, 0.0, 0);
	glScalef(0.4, 0.3, 0);
	drawTree_4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 0.5, 0);
	glScalef(0.4, 0.3, 0);
	drawTree_4();
	glPopMatrix();

	drawClouds(255, 255, 255);

	// banner draw call...
	glPushMatrix();
	glColor3ub(175, 184, 122);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 1.8, 0);
	glVertex3f(1.5, 1.8, 0);
	glVertex3f(1.5, 1.4, 0);
	glVertex3f(-1.5, 1.4, 0);
	glEnd();
	glColor3ub(0,0,0);
	glBegin(GL_LINES);
	glVertex3f(-1.5, 1.8, 0);
	glVertex3f(-1.7, 1.3, 0);
	glVertex3f(1.5, 1.8, 0);
	glVertex3f(1.8, 1.1, 0);
	glEnd();
	glColor3ub(100, 0,0);
	drawBanner("Panir Niche Rasta Valo",-1, 1.5, 0);
	glPopMatrix();

	glutSwapBuffers();
}

void update(int value) {

	if (sunset) {
		if (sun_trans_y > 1.36) {
			sun_trans_y -= 0.002;
			if (sun_trans_y < 1.55) {
				makeNight();
			}
		}
	}
	else {
		if (sun_trans_y < 2.45) {
			sun_trans_y += 0.002;
			if (sun_trans_y > 1.6) {
				makeSunrise();
			}
		}
	}

	boat_1_move -= 0.004;
	boat_1_scale_x += 0.0005;
	boat_1_scale_y += 0.0005;
	//cout << "x: " << boat_1_scale_x << endl;
	//cout << "y: " << boat_1_scale_y << endl;
	cout << "sun y: " << sun_trans_y << endl;


	if (boat_1_move < -2.8) {
		boat_1_move = 2.5;
		boat_1_scale_x = 0.25;
		boat_1_scale_y = 0.25;
	}

	cout << boat_1_move << endl;

	glutPostRedisplay(); //Tell GLUT that the display has changed
						 //Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 's':
		sunset = true;
		glutPostRedisplay();
		break;

	case 'r':
		sunset = false;
		glutPostRedisplay();
		break;

	case 'a':
		boat_1_position_x -= 0.02;
		glutPostRedisplay();
		break;

	case 'd':
		boat_1_position_x += 0.02;
		glutPostRedisplay();
		break;
	}


}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(250, 80);

	//Create the window
	glutCreateWindow("Future Rainy Dhaka");
	//initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}


