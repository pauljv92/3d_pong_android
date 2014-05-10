#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

int screen_width;
int screen_height;

float player_target_x;
float player_target_y;

float real_enemy_x;
float real_enemy_y;

void view_init() {
}

void view_resize(int w, int h) {
    screen_width = w;
    screen_height = h;
    glViewport(0, 0, screen_width, screen_height);
}

void view_touch(float x, float y) {
    float normx = (float)(x - screen_width/2) / (screen_width/2);
    float normy = -(float)(y - screen_height/2) / (screen_height/2);

    normx *= 1.8;
    if (normx > 1) {
	normx = 1;
    }
    if (normx < -1) {
	normx = -1;
    }
    normy *= 1.8;
    if (normy > 1) {
	normy = 1;
    }
    if (normy < -1) {
	normy = -1;
    }
    
    player_x = normx;
    player_y = normy;
}

void draw_ball(float x, float y, float z) {
    const GLfloat ball[] = {
	1, 1, 0,
	-1, 1, 0,
	-1, -1, 0,
	1, -1, 0
    };

    float size = 0.05;

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, ball);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void draw_player(float x, float y, float z) {
    const GLfloat paddle[] = {
	1, 1, 0,
	-1, 1, 0,
	-1, -1, 0,
	1, -1, 0
    };

    float size = 0.2;

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, paddle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void draw_boxes(float a1, float a2, float a3, float b1, float b2, float b3) {
    int i, j;
    float near = 1.f, far = -5.0f, hw = 1.0f;
    float hh = (float)screen_height / screen_width * hw;

    const GLfloat square[] = {
	-1, 1, 0,
	1, 1, 0,
	1, -1, 0,
	-1, -1, 0
    };

    float a = 1.05;
    float k = log(2) / log(a);

    float z = 0;
    i = 0;
    while (z < 1) {
	z = (z+1)*a - 1;
	++i;
	
	float d1 = a1 + i/k*(b1 - a1);
	float d2 = a2 + i/k*(b2 - a2);
	float d3 = a3 + i/k*(b3 - a3);

	glColor4f(d1, d2, d3, 1.0f);

	glPushMatrix();
	glTranslatef(0, 0, near + (far - near) * z);
	glScalef(hw, hh, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, square);
	glDrawArrays(GL_LINE_LOOP, 0, 4);	
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
    }
}

void follow(float tx, float ty, float *x, float *y, float max, float a) {
    float ox = (tx - *x) * a;
    float oy = (ty - *y) * a;

    float b = 1;
    float l = sqrt(ox * ox + oy * oy);
    if (l > max) {
	b = max / l;
    }
    *x += ox * b;
    *y += oy * b;
}

void view_update(float dt) {
    float speed = 8;
    follow(player_x, player_y,
	   &real_player_x, &real_player_y, speed * dt, 0.6);

    follow(enemy_x, enemy_y, &real_enemy_x, &real_enemy_y, 
	   speed * dt, 0.6);
}

void view_render(float dt) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(1.1);
    draw_boxes(0.0, 0.0, 0.0, 0.5, 0.5, 0.0);

    float ratio = (float)screen_height / screen_width;

    glColor4f(14.0/256, 50.0/256, 102.0/256, 1.0);
    draw_player(real_enemy_x, real_enemy_y * ratio, -5.0);

    glColor4f(1.0, 1.0, 1.0, 1.0);
    draw_ball(ball_x, ball_y, ball_z);
    
    glColor4f(0.984, 0.414, 0.00, 0.75);
    draw_player(real_player_x, real_player_y * ratio, 0);

    glFlush();
}
