//---------------------------------------
// Program: line.cpp
// Purpose: To generate random line sequence
// Author:  John Gauch
// Date:    September 2008
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;


// Define global variables
#define SIZE 32
float X[SIZE + 1];
float Y[SIZE + 1];

//---------------------------------------
// Calculate random value between [-R..R]
//---------------------------------------
float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

//---------------------------------------
// Recursive function to split lines
//---------------------------------------
void split(int low, int high, float radius)
{
   // Check terminating condition
   if ((high - low) > 1)
   {
      // Calculate length of line segment
      float dx = X[high] - X[low];
      float dy = Y[high] - Y[low];
      float length = sqrt(dx * dx + dy * dy) / radius;

      // Generate midpoint with random displacement
      int mid = (high + low) / 2;
      X[mid] = (X[high] + X[low]) / 2 + myrand(length);
      Y[mid] = (Y[high] + Y[low]) / 2 + myrand(length);

      // Perform recursive calls
      split(low, mid, radius);
      split(mid, high, radius);
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//---------------------------------------
// Display callback for OpenGL

//---------------------------------------
void makefirework(){
	   int i;
	   //float randomNum = rand() % 19 + (-9);
	   float randomNum = myrand(15);
	   int randomNum2 = rand() % 19 + (-9);
	   glColor3f(randomNum,randomNum2, randomNum);
	   glBegin(GL_LINE_STRIP);
	   X[0] = randomNum;
	   Y[0] = randomNum2;
	   X[SIZE] = randomNum;
	   Y[SIZE] = randomNum;
	   split(0, SIZE, 5);
	   glEnd();
	   float startpoint = randomNum/10;
	   cout<<startpoint<<endl;

	   for (i = 0; i <= SIZE; i++){
	   	//cout<<randomNum<<endl;
	   	glBegin(GL_LINE_STRIP);
	   	glVertex2f(startpoint,startpoint);
	   	
	   	randomNum = rand() % 19 + (-9);
	    randomNum2 = rand() % 19 + (-9);
	   	X[0] = randomNum;
	    Y[0] = randomNum2;
	    X[SIZE] = .1;
	    Y[SIZE] = .1;
	    split(0, SIZE, 5);

	    glVertex2f(X[i], Y[i]);
	    glEnd();
	}

}

void display()
{
	for(int q= 0 ; q<5; q++){
		makefirework();
	}
		
		

	
	
  
   

   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Line");
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}
