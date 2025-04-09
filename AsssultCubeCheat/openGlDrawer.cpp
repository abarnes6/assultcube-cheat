#include <Windows.h>
#include <iostream>
#include <gl/GL.h>=
#include "sdk.hpp"

GLint viewport[4];


#pragma comment(lib, "Opengl32.lib")
void initDrawer() {

    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(0, 0, viewport[2], viewport[3]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

void restoreDrawer() {
    glEnable(GL_DEPTH_TEST);
}

void drawBox(float x, float y, float height, float width, GLubyte color[3]) {

    glColor3ub(color[0], color[1], color[2]);
    glBegin(GL_LINE_STRIP);

    glVertex2f(x, y);
    glVertex2f(x+width, y);
    glVertex2f(x+width, y-height);
    glVertex2f(x, y-height);
    glVertex2f(x, y);

    glEnd();
}

void drawPlayer(float x, float y, float height, float width) {
    GLubyte color[3] = {255, 0, 0};
    drawBox(x-(width/2), y + height, height, width, color);
}

bool WorldToScreen(Vector3 pos, Vector2 &screen, float matrix[16])
{
    //Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
    Vector4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clipCoords.w < 0.1f)
        return false;

    //perspective division, dividing by clip.W = Normalized Device Coordinates
    Vector3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    //Transform to window/screen coordinates
    screen.x = (viewport[2] / 2 * NDC.x) + (NDC.x + viewport[2] / 2);
    screen.y = -(viewport[3] / 2 * NDC.y) + (NDC.y + viewport[3] / 2);

    return true;
}

void drawLine(Vector2 v1, Vector2 v2) {

    glColor3ub(255, 0, 0);
    glBegin(GL_LINE_STRIP);

    glVertex2f(v1.x, v1.y);
    glVertex2f(v2.x, v2.y);

    glEnd();

}