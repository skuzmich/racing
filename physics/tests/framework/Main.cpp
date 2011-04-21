/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Render.h"
#include "Test.h"
#include "glui/GL/glui.h"

#include <cstdio>
#include <stdio.h>

namespace
{
	int32 testIndex = 0;
	int32 testSelection = 0;
	int32 testCount = 0;
	TestEntry* entry;
	Test* test;
	Settings settings;
	int32 width = 640;
	int32 height = 480;
	int32 framePeriod = 16;
	int32 mainWindow;
	float settingsHz = 60.0;
        //GLUI *glui;
	float32 viewZoom = 3.0f;
	b2Vec2 viewCenter(0.0f, 20.0f);
	int tx, ty, tw, th;
	bool rMouseDown;
	b2Vec2 lastp;
}

void Resize(int32 w, int32 h)
{
        width = w;
        height = h;

        GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
        glViewport(tx, ty, tw, th);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float32 ratio = float32(tw) / float32(th);

        b2Vec2 extents(ratio * 25.0f, 25.0f);
        extents *= viewZoom;

        b2Vec2 lower = viewCenter - extents;
        b2Vec2 upper = viewCenter + extents;

        // L/R/B/T
        gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}
// This is used to control the frame rate (60Hz).
void Timer(int)
{
	glutSetWindow(mainWindow);
	glutPostRedisplay();
	glutTimerFunc(framePeriod, Timer, 0);
}

void SimulationLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

    test->MainLoop();
	test->Step(&settings);

    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	B2_NOT_USED(x);
	B2_NOT_USED(y);

	switch (key)
	{
	case 27:
		exit(0);
		break;

                // Press 'z' to zoom out.
        case 'z':
                viewZoom = b2Min(1.1f * viewZoom, 20.0f);
                Resize(width, height);
                break;

                // Press 'x' to zoom in.
        case 'x':
                viewZoom = b2Max(0.9f * viewZoom, 0.02f);
                Resize(width, height);
                break;

                // Press 'r' to reset.
        case 'r':
                delete test;
                test = entry->createFcn();
                break;

                // Press space to launch a bomb.

	case 'p':
		settings.pause = !settings.pause;
		break;
		
	default:
		if (test)
		{
			test->Keyboard(key);
		}
	}
}

void KeyboardSpecial(int key, int x, int y)
{
        B2_NOT_USED(x);
        B2_NOT_USED(y);

        switch (key)
        {
        case GLUT_KEY_LEFT:
                viewCenter.x -= 5.5f;
                Resize(width, height);
                break;

                // Press right to pan right.
        case GLUT_KEY_RIGHT:
                viewCenter.x += 5.5f;
                Resize(width, height);
                break;

                // Press down to pan down.
        case GLUT_KEY_DOWN:
                viewCenter.y -= 5.5f;
                Resize(width, height);
                break;

                // Press up to pan up.
        case GLUT_KEY_UP:
                viewCenter.y += 5.5f;
                Resize(width, height);
                break;

                // Press home to reset the view.
        case GLUT_KEY_HOME:
                viewZoom = 1.0f;
                viewCenter.Set(0.0f, 20.0f);
                Resize(width, height);
                break;
        }
}

void Restart(int)
{
        delete test;
        entry = g_testEntries + testIndex;
        test = entry->createFcn();
    Resize(width, height);
}

void Pause(int)
{
	settings.pause = !settings.pause;
}


int main(int argc, char** argv)
{
	testCount = 0;
	while (g_testEntries[testCount].createFcn != NULL)
	{
		++testCount;
	}

	testIndex = b2Clamp(testIndex, 0, testCount-1);
	testSelection = testIndex;

	entry = g_testEntries + testIndex;
	test = entry->createFcn();

        glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	char title[32];
	sprintf(title, "Racing 2D Debug");
	mainWindow = glutCreateWindow(title);

	glutDisplayFunc(SimulationLoop);
  GLUI_Master.set_glutReshapeFunc(Resize);
	GLUI_Master.set_glutKeyboardFunc(Keyboard);
  GLUI_Master.set_glutSpecialFunc(KeyboardSpecial);
	glutTimerFunc(framePeriod, Timer, 0);

	glutMainLoop();

	return 0;
}
