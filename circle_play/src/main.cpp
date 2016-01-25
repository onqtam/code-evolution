#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glut.h"

#include "config.h"
#include "util.h"
#include "types.h"
#include "list.h"

enum InsertMode
{
	INS_A = 0,
	INS_B,
	INS_CIRCLE
};

//mode of the program insertion (Points A/B or Circles)
InsertMode g_Mode = INS_CIRCLE;

//positions of cursor and current radius for click-inserted circles
double g_InsertX = 0.0;
double g_InsertY = 0.0;
double g_InsertRadius = 0.1;

//for tweaking parameters: Circle Radius, Number of reflections, number of rays
bool g_IsUpKeyHeld = false;
bool g_IsDownKeyHeld = false;
bool g_IsLeftKeyHeld = false;
bool g_IsRightKeyHeld = false;
bool g_IsPageUpKeyHeld = false;
bool g_IsPageDownKeyHeld = false;

double g_AngleStep = 0.00005;
Vector2D g_A, g_B;
unsigned int g_N, g_K;
List<Circle> g_Circles;

List<IntersectionList> g_Intersections;
List<IntersectionList> g_Results;

static int win;
void DrawOverlay();
void Draw();
void Run();
void MouseMotion(int x, int y);
void MouseButton(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void KeyboardSpecial(int key, int x, int y);
void KeyboardUpSpecial(int key, int x, int y);
void PrintBitmapString(void* font, char* s);

void Cleanup();
bool ReadInput(const char* file);
void RaytraceAll();

int main(int argc, char **argv)
{
	if(!ReadInput("data/input.txt")) return 1;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutInitWindowPosition(120,80);
	win = glutCreateWindow("ray play");
	glutDisplayFunc(Draw); 
	glutIdleFunc(Run);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(KeyboardSpecial);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialUpFunc(KeyboardUpSpecial);
	glutMouseFunc(MouseButton);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	atexit(Cleanup);
	glutMainLoop();
	return 0;
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//draw all circles
	glColor3f(1.0, 0.0, 0.0);
	for(List<Circle>::iterator it = g_Circles.begin(); it != g_Circles.end(); ++it)
	{
		glPushMatrix();
		glTranslatef(it->o.x, it->o.y, 0);
		glutSolidSphere(it->r, 32, 2);
		glPopMatrix();
	}
	
	glPushMatrix();
	glBegin(GL_LINES);
	for(List<IntersectionList>::iterator it = g_Intersections.begin(); it != g_Intersections.end(); ++it)
	{
		glColor3f(it->color.r, it->color.g, it->color.b);
		
		if(it->numReflections > 0)
		{
			glVertex2d(g_A.x, g_A.y);
			glVertex2d(it->infos[0].ip.x, it->infos[0].ip.y);
			
			for(size_t i = 0; i < it->numReflections - 1; ++i)
			{
				glVertex2d(it->infos[i].ip.x, it->infos[i].ip.y);
				glVertex2d(it->infos[i + 1].ip.x, it->infos[i + 1].ip.y);
			}
			
			//ray after last reflection goes through scene without reflecting
			glVertex2d(
				it->infos[it->numReflections - 1].ip.x, 
				it->infos[it->numReflections - 1].ip.y);
			glVertex2d(
				it->infos[it->numReflections - 1].ip.x + it->lastDir.x * 10, 
				it->infos[it->numReflections - 1].ip.y + it->lastDir.y * 10);
#if DISPLAY_PROJECTIONS
			glColor3f(1,1,1);
			Ray ray(it->infos[it->numReflections - 1].ip, it->lastDir);
			Vector2D point;
			if(GetPointProjectionOntoRay(ray, g_B, point))
			{
				glVertex2d(g_B.x, g_B.y);
				glVertex2d(point.x, point.y);
			}
#endif // DISPLAY_PROJECTIONS
		}
	}
	
	for(List<IntersectionList>::iterator it = g_Results.begin(); it != g_Results.end(); ++it)
	{
		glColor3f(it->color.r, it->color.g, it->color.b);

		glVertex2d(g_A.x, g_A.y);
		glVertex2d(it->infos[0].ip.x, it->infos[0].ip.y);
		
		for(size_t i = 0; i < it->numReflections - 1; ++i)
		{
			glVertex2d(it->infos[i].ip.x, it->infos[i].ip.y);
			glVertex2d(it->infos[i + 1].ip.x, it->infos[i + 1].ip.y);
		}
		
		//ray after last reflection goes through scene without reflecting
		glVertex2d(
			it->infos[it->numReflections - 1].ip.x, 
			it->infos[it->numReflections - 1].ip.y);
		glVertex2d(
			it->infos[it->numReflections - 1].ip.x + it->lastDir.x * 10, 
			it->infos[it->numReflections - 1].ip.y + it->lastDir.y * 10);
	}
	glEnd();
	glPopMatrix();
	
	//draw A
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(g_A.x, g_A.y, 0);
	glutSolidSphere(DISTANCE_EPSILON + 0.005, 32, 2);
	glPopMatrix();
	
	//draw B
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(g_B.x, g_B.y, 0);
	glutSolidSphere(DISTANCE_EPSILON + 0.005, 32, 2);
	glPopMatrix();
	
	//drawing the circle from the mouse cursor
	if(g_Mode == INS_CIRCLE)
	{
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(g_InsertX, g_InsertY, 0);
		glutWireSphere(g_InsertRadius, 32, 2);
		glPopMatrix();
	}
	
	DrawOverlay();
	
	glFlush();
	glutSwapBuffers();
}

void DrawOverlay()
{
	#define NUM_TEXTS 6
	char texts [NUM_TEXTS][128];
	
	sprintf(texts[0], "MODE: %14s (A/B for points A/B, C for Circles)", 
		(g_Mode == INS_A) ? ("PLACE POINT A") : 
		(g_Mode == INS_B) ? ("PLACE POINT B") : ("INSERT CIRCLE"));
	sprintf(texts[1], "ANGLE STEP: %5lf (Page Up / Page Down)", g_AngleStep);
	sprintf(texts[2], "K:    %8d       (Left / Right)", g_K);
	sprintf(texts[3], "RADIUS: %5lf     (Up / Down)", g_InsertRadius);
	sprintf(texts[4], "Press BACKSPACE to clear the scene.");
	sprintf(texts[5], "Press SPACE to start the simulation.");
	
	glColor3f(1.0, 1.0, 1.0);
	for(size_t i = 0; i < NUM_TEXTS; ++i)
	{
		glRasterPos2f(-0.99, 0.97 - i * 0.03);
		PrintBitmapString(GLUT_BITMAP_9_BY_15, texts[i]);
	}
}

void Run()
{
	static int timeOld = 0;
	int time = glutGet(GLUT_ELAPSED_TIME);
	int frameTime = time - timeOld;
	timeOld = time;
	
	if(g_IsUpKeyHeld)
	{
		g_InsertRadius += static_cast<float>(frameTime) / 10000;
		if(g_InsertRadius > 0.5)
			g_InsertRadius = 0.5;
	}
	if(g_IsDownKeyHeld)
	{
		g_InsertRadius -= static_cast<float>(frameTime) / 10000;
		if(g_InsertRadius < 0.01)
			g_InsertRadius = 0.01;
	}
	
	if(g_IsPageUpKeyHeld)
	{
		g_AngleStep += g_AngleStep / 100;
		if(g_AngleStep > 0.5)
			g_AngleStep = 0.5;
	}
	if(g_IsPageDownKeyHeld)
	{
		g_AngleStep -= g_AngleStep / 100;
		if(g_AngleStep < 0.000001)
			g_AngleStep = 0.000001;
	}
	if(g_IsLeftKeyHeld)
	{
		g_K -= 1;
		if(g_K < 1)
			g_K = 1;
	}
	if(g_IsRightKeyHeld)
	{
		g_K += 1;
		if(g_K > 50)
			g_K = 50;
	}
	
	glutPostRedisplay();
}

void MouseMotion(int x, int y)
{
	g_InsertX = (static_cast<float>(x) / SCR_WIDTH) * 2 - 1;
	g_InsertY = (static_cast<float>(SCR_HEIGHT - y) / SCR_HEIGHT) * 2 - 1;
}

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			switch(g_Mode)
			{
			case INS_A:
				{
					g_A.x = (static_cast<float>(x) / SCR_WIDTH) * 2 - 1;
					g_A.y = (static_cast<float>(SCR_HEIGHT - y) / SCR_HEIGHT) * 2 - 1;
				}
				break;
			case INS_B:
				{
					g_B.x = (static_cast<float>(x) / SCR_WIDTH) * 2 - 1;
					g_B.y = (static_cast<float>(SCR_HEIGHT - y) / SCR_HEIGHT) * 2 - 1;
				}
				break;
			case INS_CIRCLE:
				{
					++g_N;
					g_Circles.push_back(Circle(Vector2D(
						(static_cast<float>(x) / SCR_WIDTH) * 2 - 1,
						(static_cast<float>(SCR_HEIGHT - y) / SCR_HEIGHT) * 2 - 1),
						g_InsertRadius));
				}
				break;
			}
			
		}
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	//escape
	if(key == 27)
	{
		glutDestroyWindow(win); 
		exit(0); 
	}
	//backspace
	if(key == 8)
	{
		Cleanup();
	}
	//space
	if(key == 32)
	{
		RaytraceAll();
	}
	
	//insert modes
	if(key == 'a' || key == 'A')
	{
		g_Mode = INS_A;
	}
	if(key == 'b' || key == 'B')
	{
		g_Mode = INS_B;
	}
	if(key == 'c' || key == 'C')
	{
		g_Mode = INS_CIRCLE;
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	
}

void KeyboardSpecial(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
	{
		g_IsUpKeyHeld = true;
	}
	if(key == GLUT_KEY_DOWN)
	{
		g_IsDownKeyHeld = true;
	}
	if(key == GLUT_KEY_LEFT)
	{
		g_IsLeftKeyHeld = true;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		g_IsRightKeyHeld = true;
	}
	if(key == GLUT_KEY_PAGE_UP)
	{
		g_IsPageUpKeyHeld = true;
	}
	if(key == GLUT_KEY_PAGE_DOWN)
	{
		g_IsPageDownKeyHeld = true;
	}
}

void KeyboardUpSpecial(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
	{
		g_IsUpKeyHeld = false;
	}
	if(key == GLUT_KEY_DOWN)
	{
		g_IsDownKeyHeld = false;
	}
	if(key == GLUT_KEY_LEFT)
	{
		g_IsLeftKeyHeld = false;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		g_IsRightKeyHeld = false;
	}
	if(key == GLUT_KEY_PAGE_UP)
	{
		g_IsPageUpKeyHeld = false;
	}
	if(key == GLUT_KEY_PAGE_DOWN)
	{
		g_IsPageDownKeyHeld = false;
	}
}

void PrintBitmapString(void* font, char* s)
{
	if(s && strlen(s))
	{
		while(*s)
		{
			glutBitmapCharacter(font, *s);
			++s;
		}
	}
}
