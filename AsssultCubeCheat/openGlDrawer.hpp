#include <gl/GL.h>
#include "vecs.hpp"

void initDrawer();

void restoreDrawer();

void drawBox(float x, float y, float height, float width, GLubyte color[3]);


void drawPlayer(float x, float y, float height, float width);

bool WorldToScreen(Vector3 pos, Vector2& screen, float matrix[16]);

void drawLine(Vector2 v1, Vector2 v2);