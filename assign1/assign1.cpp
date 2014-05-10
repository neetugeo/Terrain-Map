// assign1.cpp : Defines the entry point for the console application.
//

/*
  CSCI 480 Computer Graphics
  Assignment 1: Height Fields
  C++ starter code
*/

#include "stdafx.h"
#include <pic.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>

using namespace std;

int g_iMenuId;
float rotation = 0.0;

int g_vMousePos[2] = {0, 0};
int g_iLeftMouseButton = 0;    /* 1 if pressed, 0 if not */
int g_iMiddleMouseButton = 0;
int g_iRightMouseButton = 0;
int i = 0;
bool start = true;
bool translation = true;
int number = 0; //Incrementation for pictures
ostringstream ss; //for Char* conversion for image names.
typedef enum { ROTATE, TRANSLATE, SCALE } CONTROLSTATE;

CONTROLSTATE g_ControlState = ROTATE;

/* state of the world */
float g_vLandRotate[3] = {0.0, 0.0, 0.0};
float g_vLandTranslate[3] = {0.0, 0.0, 0.0};
float g_vLandScale[3] = {1.0, 1.0, 1.0};

/* see <your pic directory>/pic.h for type Pic */
Pic * g_pHeightData;

/* Write a screenshot to the specified filename */
void saveScreenshot (char *filename)
{
  int i, j;
  Pic *in = NULL;

  if (filename == NULL)
    return;

  /* Allocate a picture buffer */
  in = pic_alloc(640, 480, 3, NULL);

  printf("File to save to: %s\n", filename);

  for (i=479; i>=0; i--) {
    glReadPixels(0, 479-i, 640, 1, GL_RGB, GL_UNSIGNED_BYTE,
                 &in->pix[i*in->nx*in->bpp]);

	
  }

  if (jpeg_write(filename, in))
    printf("File saved Successfully\n");
  else
    printf("Error in Saving\n");

  pic_free(in);
}

void myinit()
{
  /* setup gl view here */
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);

}

float getZValue(int zx, int zy)  //made a function to call Z. Easier than rewriting vvv that every time
{
	float Alpha;
	Alpha = PIC_PIXEL(g_pHeightData,zx,zy,0);
	return (Alpha);
}


void display()
{
  /* draw 1x1 cube about origin */
  /* replace this code with your height field implementation */
  /* you may also want to precede it with your 
rotation/translation/scaling */
	

	for (int y = 0; y < (g_pHeightData->ny) - 1; y++)
	{
		for(int x = 0; x < (g_pHeightData->nx) - 1; x++)
		{
			
			glBegin(GL_POINTS);
			float z = getZValue(x,y);
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x,y,z);

			z = getZValue((x+1.0),y);
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0),y,z);

			z = getZValue(x,(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x, (y+1.0), z);

			z = getZValue((x+1.0),y); 
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0),y,z);

			z = getZValue(x,(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x,(y+1.0),z);

			z = getZValue((x+1.0),(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0), (y+1.0), z);

			glEnd();

		}
	}

  glFlush();
  glutSwapBuffers();
}

void clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
}

void displayTris()
{
	for (int y = 0; y < (g_pHeightData->ny) - 1; y++)
	{
		for(int x = 0; x < (g_pHeightData->nx) - 1; x++)
		{
			
			glBegin(GL_TRIANGLES);
			float z = getZValue(x,y);
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x,y,z);

			z = getZValue((x+1.0),y);
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0),y,z);

			z = getZValue(x,(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x, (y+1.0), z);

			z = getZValue((x+1.0),y);
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0),y,z);

			z = getZValue(x,(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x,(y+1.0),z);

			z = getZValue((x+1.0),(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0), (y+1.0), z);

			glEnd();

		}
	}


  glFlush();
  glutSwapBuffers();

}

void displayEdges()
{
	for (int y = 0; y < (g_pHeightData->ny) - 1; y++)
	{
		for(int x = 0; x < (g_pHeightData->nx) -1; x++)
		{
			
			glBegin(GL_LINES);
			float z = getZValue(x,y); 
			glColor3f(1.0,0.0,(z/255.0)); //allows for colors to vary according to height.
										  //I like purple to red.
			glVertex3f(x,y,z);

			z = getZValue((x+1.0),y);
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0),y,z);

			z = getZValue(x,(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x, (y+1.0), z);

			z = getZValue((x+1.0),y); 
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0),y,z);

			z = getZValue(x,(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f(x,(y+1.0),z);

			z = getZValue((x+1.0),(y+1.0));
			glColor3f(1.0,0.0,(z/255.0));
			glVertex3f((x+1.0), (y+1.0), z);

			glEnd();

		}
	}


  glFlush();
  glutSwapBuffers();

}





void menufunc(int value)
{
  switch (value)
  {
    case 0:
      exit(0);
     break;
	case 1:
		glutDisplayFunc(displayTris);		//manually display tris
	break;
	case 2: 
		glutDisplayFunc(displayEdges);		//manually display mesh
	break;
	case 3:
		glutDisplayFunc(display);			//manually display points
	break;
  }
}

void doIdle()
{
  /* do some stuff... */
	
	if (start == true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glRotatef(1.0,0,0,1);
   	    glutPostRedisplay();
	}
		/* make the screen update */
		
		glReadBuffer(GL_FRONT);
		if (number != 300)				//Global integer number to help with animation
		{
			string* str = new string();
			str->erase(0, (str->length() - 1));
			ss << number;
			*str = ss.str();
			*str = *str + ".jpeg";
			cout << *str << endl;
			ss.str(string());
			
			char* charStar = new char[str->length()+1];
			strcpy(charStar,str->c_str());

			delete str;
			number++;

			saveScreenshot(charStar);

			delete charStar;
		}

		if (number == 100)
		{
			glutDisplayFunc(displayTris); //Automatically change to triangles
		}
		if (number == 200)
		{
			glutDisplayFunc(displayEdges); //Automatically change to mesh
		}
}

/* converts mouse drags into information about 
rotation/translation/scaling */
void mousedrag(int x, int y)
{
  int vMouseDelta[2] = {x-g_vMousePos[0], y-g_vMousePos[1]};
  
  switch (g_ControlState)
  {
	 //All the functions Translate,Rotate,Scale had some modifier before the '='.
	  //I removed them all because the incrementation caused problems for functionality.
	  //as in they didn't do what they were intended to do.

    case TRANSLATE:  
      if (g_iLeftMouseButton)
      {
		glClear(GL_COLOR_BUFFER_BIT);

		start = false; //Going into any of the mouse functions should override rotation animation.

        g_vLandTranslate[0] = vMouseDelta[0]*0.1;
        g_vLandTranslate[1] = vMouseDelta[1]*0.5; 
		glTranslatef(g_vLandTranslate[0], g_vLandTranslate[1], 0.0);

		glutPostRedisplay();
      }
      if (g_iMiddleMouseButton)
      {
		
		start = false;

		glClear(GL_COLOR_BUFFER_BIT);

        g_vLandTranslate[2] = vMouseDelta[1]*0.1;
		glTranslatef(0.0,0.0,g_vLandTranslate[2]);

		glutPostRedisplay();
      }
      break;
    case ROTATE:
      if (g_iLeftMouseButton)
      {
        glClear(GL_COLOR_BUFFER_BIT);

		start = false;

		g_vLandRotate[0] = vMouseDelta[1];
        g_vLandRotate[1] = vMouseDelta[0];
		glRotatef(g_vLandRotate[0],1,0,0);
		glRotatef(g_vLandRotate[1],0,1,0);

		glutPostRedisplay();
      }
      if (g_iMiddleMouseButton)
      {
		glClear(GL_COLOR_BUFFER_BIT);

		start = false;

        g_vLandRotate[2] = vMouseDelta[1];
		glRotatef(g_vLandRotate[2],0,0,1); 

		glutPostRedisplay();
      }
      break;
    case SCALE:
      if (g_iLeftMouseButton)
      {
		start = false;

		glClear(GL_COLOR_BUFFER_BIT);

		cout << start << endl;

        g_vLandScale[0] = 1.0+vMouseDelta[0]*0.01;
        g_vLandScale[1] = 1.0-vMouseDelta[1]*0.01;
		g_vLandScale[2] = 1.0-vMouseDelta[1]*0.01;
		

		glScalef(g_vLandScale[0],g_vLandScale[0],g_vLandScale[0]); //want this to scale together. 

		glutPostRedisplay();
      }
      if (g_iMiddleMouseButton)
      {
        g_vLandScale[2] *= 1.0-vMouseDelta[1]*0.01;
      }
      break;
  }
  g_vMousePos[0] = x;
  g_vMousePos[1] = y;
}


void mouseidle(int x, int y)
{
		g_vMousePos[0] = x;
		g_vMousePos[1] = y;
	
}

void mousebutton(int button, int state, int x, int y)
{

  switch (button)
  {
    case GLUT_LEFT_BUTTON:
      g_iLeftMouseButton = (state==GLUT_DOWN);
      break;
    case GLUT_MIDDLE_BUTTON:
      g_iMiddleMouseButton = (state==GLUT_DOWN);
      break;
    case GLUT_RIGHT_BUTTON:
      g_iRightMouseButton = (state==GLUT_DOWN);
      break;
  }
 
  switch(glutGetModifiers())
  {
    case GLUT_ACTIVE_CTRL:
      g_ControlState = TRANSLATE;
      break;
    case GLUT_ACTIVE_SHIFT:
      g_ControlState = SCALE;
      break;
    default:
      g_ControlState = ROTATE;
      break;
  }

  g_vMousePos[0] = x;
  g_vMousePos[1] = y;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// I've set the argv[1] to spiral.jpg.
	// To change it, on the "Solution Explorer",
	// right click "assign1", choose "Properties",
	// go to "Configuration Properties", click "Debugging",
	// then type your texture name for the "Command Arguments"
	if (argc<2)
	{  
		printf ("usage: %s heightfield.jpg\n", argv[0]);
		exit(1);
	}

	char* temp[] = {"GrandTeton-256.jpg"};
	g_pHeightData = jpeg_read(*temp, NULL);
	if (!g_pHeightData)
	{
	    printf ("error reading %s.\n", argv[1]);
	    exit(1);
	}

	glutInit(&argc,(char**)argv);
  
	/*
		create a window here..should be double buffered and use depth testing
  
	    the code past here will segfault if you don't have a window set up....
	    replace the exit once you add those calls.
	*/
	
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);

	gluPerspective(60,1.33,.01,100); //setting up the camera

	/* tells glut to use a particular display function to redraw */
	glTranslatef(0.0,-.25,-1.5);
	glScalef(.00392,.00392,.00392); //So now you can see the entirety of the terrain map. 
	glRotatef(-90,1,0,0);			//A size small enough for the window.
	


	glutDisplayFunc(display);
	/* allow the user to quit using the right mouse button menu */

	g_iMenuId = glutCreateMenu(menufunc);
	glutSetMenu(g_iMenuId);
	glutAddMenuEntry("Quit",0);
	glutAddMenuEntry("Triangles",1);
	glutAddMenuEntry("Mesh",2);
	glutAddMenuEntry("Points",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* replace with any animate code */	
	glutIdleFunc(doIdle);

	/* callback for mouse drags */
	glutMotionFunc(mousedrag);
	/* callback for idle mouse movement */
	
	//glutPassiveMotionFunc(mouseidle);

	/* callback for mouse button changes */
	glutMouseFunc(mousebutton);


	/* do initialization */
	myinit();

	glutMainLoop();
	return 0;
}