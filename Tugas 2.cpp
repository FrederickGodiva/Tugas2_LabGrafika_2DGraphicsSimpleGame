// Tugas 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glut.h>
#include <iostream>

float firstObjectX = 0;
float firstObjectY = 0;
float secondObjectX = 0;
float secondObjectY = 0;

float xp1 = 30, yp1 = 450, xp2 =  450, yp2 = 30, r = 30, n = 1000, a, posX1, posY1, posX2, posY2;

bool firstObject = false;
bool secondObject = false;
bool start = false;
bool replay = false;

void write(float x, float y, float z, void* font, const char* string)
{
    const char* c;

    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void redBox()
{
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(135, 190);
        glVertex2f(235, 190);
        glVertex2f(235, 290);
        glVertex2f(135, 290);
    glEnd();
}

void greenBox()
{
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(245, 190);
        glVertex2f(345, 190);
        glVertex2f(345, 290);
        glVertex2f(245, 290);
    glEnd();
}

void redCircle()
{
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        a = 6.28 / n;
        for (int i = 0; i < n; i++) 
        {
            posX1 = xp1 + r * cos(i * a);
            posY1 = yp1 + r * sin(i * a);
            glVertex2f(posX1 + firstObjectX, posY1 + firstObjectY);
        }
    glEnd();
}

void greenCircle()
{
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        a = 6.28 / n;
        for (int i = 0; i < n; i++)
        {
            posX2 = xp2 + r * cos(i * a);
            posY2 = yp2 + r * sin(i * a);
            glVertex2f(posX2 + secondObjectX, posY2 + secondObjectY);
        }
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 13:
            if (firstObject && secondObject)
            {
                replay = true;
                std::cout << "===================================" << std::endl;
                std::cout << "\t     REPLAY GAME" << std::endl;
                std::cout << "===================================" << std::endl;
            }
            break;
        case 27:
            std::cout << "===================================" << std::endl;
            std::cout << "\t     EXIT GAME" << std::endl;
            std::cout << "===================================" << std::endl;
            exit(1);
            break;
        case 32:
            if (!start)
            {
                start = true;
                std::cout << "===================================" << std::endl;
                std::cout << "\t     START GAME" << std::endl;
                std::cout << "===================================" << std::endl;
            }
            break;
        case 'a':
        case 'A':
            if (firstObjectX > 0)
            {
                firstObjectX -= 5;
            }
            std::cout << "Red Circle = (" << firstObjectX << ", " << firstObjectY << ")" << std::endl;
            break;
        case 'd':
        case 'D':
            if (firstObjectX < 480)
            {
                firstObjectX += 5;
            }
            std::cout << "Red Circle = (" << firstObjectX << ", " << firstObjectY << ")" << std::endl;
            break;
        case 'w':
        case 'W':
            if (firstObjectY < 0)
            {
                firstObjectY += 5;
            }
            std::cout << "Red Circle = (" << firstObjectX << ", " << firstObjectY << ")" << std::endl;
            break;
        case 's':
        case 'S':
            if (firstObjectY > -480)
            {
                firstObjectY -= 5;
            }
            std::cout << "Red Circle = (" << firstObjectX << ", " << firstObjectY << ")" << std::endl;
            break;
    }

    if (firstObjectX >= 130 && firstObjectX <= 180 && firstObjectY >= -235 && firstObjectY <= -185)
    {
        firstObject = true;
        std::cout << "The red circle is inside the red box" << std::endl;
    }
    else
    {
        firstObject = false;
    }
}

void specialKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            if (secondObjectX > -420)
            {
                secondObjectX -= 5;
            }
            std::cout << "Green Circle = (" << secondObjectX << ", " << secondObjectY << ")" << std::endl;
            break;
        case GLUT_KEY_RIGHT:
            if (secondObjectX < 0)
            {
                secondObjectX += 5;
            }
            std::cout << "Green Circle = (" << secondObjectX << ", " << secondObjectY << ")" << std::endl;
            break;
        case GLUT_KEY_UP:
            if (secondObjectY < 480)
            {
                secondObjectY += 5;
            }
            std::cout << "Green Circle = (" << secondObjectX << ", " << secondObjectY << ")" << std::endl;
            break;
        case GLUT_KEY_DOWN:
            if (secondObjectY > 0)
            {
                secondObjectY -= 5;
            }
            std::cout << "Green Circle = (" << secondObjectX << ", " << secondObjectY << ")" << std::endl;
            break;
    }

    if (secondObjectX >= -175 && secondObjectX <= -135 && secondObjectY >= 190 && secondObjectY <= 230)
    {
        secondObject = true;
        std::cout << "The green circle inside the green box" << std::endl;
    }
    else
    {
        secondObject = false;
    }
}

void restartGame()
{
    start = false;
    replay = false;
    firstObjectX = 0;
    firstObjectY = 0;
    secondObjectX = 0;
    secondObjectY = 0;
    firstObject = false;
    secondObject = false;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    redBox();
    greenBox();

    if (!start)
    {
        write(140, 300, 0, GLUT_BITMAP_HELVETICA_18, "Press SPACE to start the game");
    }

    if (start)
    {
        redCircle();
        greenCircle();
    }

    if (firstObject && secondObject)
    {
        write(150, 170, 0, GLUT_BITMAP_HELVETICA_18, "Both circles are inside the box");
        write(175, 150, 0, GLUT_BITMAP_HELVETICA_18, "Press ENTER to replay");

        if (replay)
        {
            restartGame();
        }
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(128, 128);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Tugas 2 Lab Grafika Komputer");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 480, 0, 480);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutMainLoop();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
