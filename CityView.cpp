/*327119871
Paulina Huta 
*/
#include "glut.h"
#include <math.h>
#include <time.h>

const int WIN_SIZE = 40;


bool winLights[WIN_SIZE][WIN_SIZE];


double red = 0;
double offset = 0;

void init()
{

	srand(time(0)); // seed or init random numbers generator
	// init the windows light randomly
	for (int i = 0; i < WIN_SIZE; i++)
	{
		for (int j = 0; j < WIN_SIZE; j++)
		{
			winLights[i][j] = !(rand() % 3 == 0);
		}
	}

	//    (red, green , blue, alpha)
	glClearColor(0.0, 0.6, 0.8, 0);// color of window background

	// define main axes (left,right,bottom,top,near far)
	glOrtho(-1, 1, -1, 1, -1, 1);
}

void DrawAxes() 
{
	glColor3d(1, 1, 1); // set color
	// x- axis
	glBegin(GL_LINE_STRIP);
		glVertex2d(-1, 0); // (x,y)
		glVertex2d(1, 0);
		glVertex2d(0.9, 0.1);
		glVertex2d(0.9, -0.1);
		glVertex2d(1, 0);
	glEnd();
	// y-axis
	glBegin(GL_LINES);
		glVertex2d(0,-1);
		glVertex2d(0, 1);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2d(0, 1);
		glVertex2d(-0.05, 0.9);
		glVertex2d(0.05, 0.9);
	glEnd();

}

void DrawFunctionGraph() 
{
	double x, y;
	double step = 0.01;
	// red, green,blue
	glColor3d(0, 0, 0.3);

	// top 
	// 1-st function 
	glBegin(GL_LINE_STRIP);//GL_POINTS);
	for(x=-1;x<=1;x+=step) 
	{
		y = fabs(0.8 * sin(5 * x - offset));
		
		glColor3d(fabs(x), fabs(y), 0.3);
		glVertex2d(x, y);
	}
	glEnd();

	// bottom (reflection)
	glBegin(GL_LINE_STRIP);//GL_POINTS);
	for (x = -1; x <= 1; x += step)
	{
		y = -fabs(0.8 * sin(5 * x - offset));

		glColor3d(fabs(x), -y, 0.3);
		glVertex2d(x, y);
	}
	glEnd();


	// 2-nd function 
	glBegin(GL_LINE_STRIP);//GL_POINTS);
	for (x = -1; x <= 1; x += step)
	{
		y = 0.1 * sin(6 * x - offset)+0.2;

		glColor3d(1-fabs(x), y, 0.3);
		glVertex2d(x, y);
	}
	glEnd();
	// reflection
	// 2-nd function 
	glBegin(GL_LINE_STRIP);//GL_POINTS);
	for (x = -1; x <= 1; x += step)
	{
		y = 0.1 * sin(6 * x - offset) + 0.2;

		glColor3d(1 - fabs(x), y, 0.3);
		glVertex2d(x, -y);
	}
	glEnd();

}

void DrawOneBuilding(double left, double height, double width, bool reflection )
{
	if (reflection)
		height = -height; 
	// building
	glBegin(GL_POLYGON);
		if(reflection) 	glColor3d(fabs(left) * 0, fabs(height) * 0, 0);
		else glColor3d(fabs(left)*0, fabs(height)*0, 0);

		glVertex2d(left, height); // 1-st point   this is our sin value
		glVertex2d(left+width, height); // 1-st point   this is our sin value
		if (reflection) glColor3d(0, 0, 0);
		else glColor3d(0, 0, 0);
		glVertex2d(left + width, 0); // 1-st point   this is our sin value
		glVertex2d(left, 0); // 1-st point   this is our sin value
	glEnd();

	// windows
	double floor = 0.01;
	double h,x;
	int i, j;
	height = fabs(height);
	glColor3d(1, 1, 0); // yellow
		glBegin(GL_POINTS);
	for (h = height - 2 * floor,i=0; h >= 2 * floor; h -= 2 * floor,i++)
	{
		for (x = left + floor,j=0; x <= left + width - floor; x += floor,j++)
		{
			if (winLights[i][j]) // only for lit windows
			{
				if (!reflection)
					glVertex2d(x, h);
				else
					glVertex2d(x, -h);
			}
		}
	}
		glEnd();

}

void DrawBuildings()
{
	double x, y;
	double step = 0.14;
	// tall buildings
	for (x = -1; x <= 1; x += step)
	{
		y = fabs(0.6 * sin(6 * x-offset));
		DrawOneBuilding(x, y, step - 0.01, false);
	// water reflections
		DrawOneBuilding(x, y, step - 0.04, true);
	}
	step = 0.10;
	//cos buildings
	for (x = -1; x <= 1; x += step)
	{
		y = fabs(0.4 * cos(6 * x - offset));
		DrawOneBuilding(x, y, step - 0.01, false);
		// water reflections
		DrawOneBuilding(x, y, step - 0.01, true);
	}

	step = 0.12;
	// small buildings
	for (x = -1; x <= 1; x += step)
	{
		y = 0.1 * sin(6 * x - offset) + 0.2;
		DrawOneBuilding(x, y, step - 0.01, false);
		// water reflections
		DrawOneBuilding(x , y , step - 0.01, true);
	}
}


void DrawMoon()
{
	double theta, x, i;
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(0.5 + 0.1 * cos(theta), 0.8 + 0.1 * sin(theta));
	
	}
	glEnd();


	//moon reflection
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(0.5 + 0.1 * cos(theta), -0.8 + 0.1 * sin(theta));

	}
	glEnd();
	//moon reflection
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(0.5 + 0.1 * cos(theta), -0.8 + 0.1 * sin(theta));

	}
	glEnd();

	//polaris
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(0.3 + 0.006 * cos(theta), 0.75 + 0.006 * sin(theta));

	}
	glEnd();


	//polaris reflection
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(0.3 + 0.006 * cos(theta), -0.75 + 0.006 * sin(theta));
		glVertex2d(0.3 + 0.006 * cos(theta), -0.75 + 0.006 * sin(theta));

	}
	glEnd();


	//star
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(-0.35 + 0.004 * cos(theta), 0.55 + 0.004 * sin(theta));

	}
	glEnd();


	//star reflection
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
		theta = x * 3.142 / 180;
		glColor3d(1.1, 1, 0.7);
		glVertex2d(-0.35 + 0.004 * cos(theta), -0.55 + 0.004 * sin(theta));

	}
	glEnd();

	//star
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
			theta = x * 3.142 / 180;
			glColor3d(1.1, 1, 0.7);
			glVertex2d(-0.55 + 0.004 * cos(theta), 0.9 + 0.004 * sin(theta));
	}
	glEnd();


	//star reflection
	glBegin(GL_POLYGON);
	for (x = 0; x < 360; x++)
	{
			theta = x * 3.142 / 180;
			glColor3d(1.1, 1, 0.7);
			glVertex2d(-0.55 + 0.004 * cos(theta), -0.9 + 0.004 * sin(theta));

	}
	glEnd();

}



void DrawBackground()
{
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.2);
	glVertex2d(-1, 1);  // top sky points
	glVertex2d(1, 1);
	glColor3d(0.4, 0.6, 0.7);
	glVertex2d(1, 0); // ground points
	glVertex2d(-1, 0);
	glEnd();

	// water reflection
	glBegin(GL_POLYGON);
	glColor3d(0.4, 0.4, 0.5);
	glVertex2d(1, 0); // ground points
	glVertex2d(-1, 0);
	glColor3d(0, 0, 0.2);
	glVertex2d(-1, -1);  // top sky points
	glVertex2d(1, -1);
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	// main axes (with arrows)
	DrawBackground();
	DrawBuildings();
	DrawMoon();
	glutSwapBuffers(); // show all
}


void idle()
{

	int row, col;
	row = rand() % WIN_SIZE;
	col = rand() % WIN_SIZE;

	// randomly changes lights
	winLights[row][col] = !winLights[row][col];

	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // defines BUFFERS: Color buffer (frame buffer)
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(150, 50);
	glutCreateWindow("City At Night By Paulina Huta");

	glutDisplayFunc(display); // refresh window function
	glutIdleFunc(idle); // kind of timer function

	init();
	glutMainLoop();
	return 0;
}
