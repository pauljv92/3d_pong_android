#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

int wd;

void draw_player(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    #define PSIZE 0.2
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(PSIZE, PSIZE, 0);
    glVertex3f(-PSIZE, PSIZE, 0);
    glVertex3f(-PSIZE, -PSIZE, 0);
    glVertex3f(PSIZE, -PSIZE, 0);
    glEnd();

    glPopMatrix();
}

void draw_boxes(float a1, float a2, float a3, float b1, float b2, float b3) {
    int i, j;
    float near = 1.f, far = -5.0f, hw = 1.0f;
    float hh = (float)HEIGHT / WIDTH * hw;

    const GLfloat unit[] = {
	-1, 1, 0,
	1, 1, 0,
	1, -1, 0,
	-1, -1, 0
    };
    
    float alpha = 0.5;
    GLfloat colors[] = {
	0, 0, 0, alpha,
	0, 0, 0, alpha,
	0, 0, 0, alpha,
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

	colors[0] = colors[4] = colors[8] = d1;
	colors[1] = colors[5] = colors[9] = d2;
	colors[2] = colors[6] = colors[10] = d3;
	
	glPushMatrix();
	glTranslatef(0, 0, near + (far - near) * z);
	glScalef(hw, hh, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, unit);
	glDrawArrays(GL_LINE_LOOP, 0, 4);	
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	
//	glEnableClientState(GL_COLOR_ARRAY);

//	glColorPointer(3, GL_FLOAT, 0, colors);
//	glDisableClientState(GL_COLOR_ARRAY);

/*	glColor3f(d1, d2, d3);
	glBegin(GL_LINE_LOOP);
	for (j=0; j<4; j++) {
	    glVertex3fv(ends[j]);
	}
	glEnd();*/
    }
}

int center_button = 0;
int centerx = -1;
int centery = -1;
float targetx = 0;
float targety = 0;

int sensitivity = 200;

void mouse(int x, int y) {
    if (centerx < 0 || centery < 0) {
	centerx = x;
	centery = y;
    }

    // set target x and y!!
    float tx = (float)(x - centerx) / sensitivity;
    float ty = -(float)(y - centery) / sensitivity;
    if (tx > 1) {
	tx = 1;
    }
    if (tx < -1) {
	tx = -1;
    }
    if (ty > 1) {
	ty = 1;
    }
    if (ty < -1) {
	ty = -1;
    }
    targetx = tx;
    targety = ty;
}

void key(unsigned char key, int x, int y) {
    if (key == 32) {
	centerx = x;
	centery = y;
    }
}

void init() {
    // todo
    printf("Starting!\n");
}

int last = -1;
float playerx = 0;
float playery = 0;

int xdir = 1;
int ydir = 1;
float compx = 0;
float compy = 0;

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

void update(float dt) {
    float speed = 8;

    follow(targetx, targety, &playerx, &playery, speed * dt, 0.6);

    float compspeed = 3;
    float comptargetx = -playerx;
    float comptargety = -playery;
    follow(-playerx, -playery, &compx, &compy, compspeed * dt, 0.6);
}

void display() {
    int i;

    int now = glutGet(GLUT_ELAPSED_TIME);
    if (last > 0) {
	if (now > last) {
	    update((float)(now - last) / 1000);
	    last = now;
	}
    } else {
	last = now;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // clear the color buffer
    glClearColor(0, 0, 0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)WIDTH / HEIGHT, 0.1, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(playerx/2, playery/2, 2.0, playerx/4, playery/4, 0.0, 0.0, 1.0, 0.0);

    glColor3f(0.0, 1.0, 1.0);
    glLineWidth(1.1);
    draw_boxes(0.0, 0.0, 0.0, 0.5, 0.5, 0.0);

    glColor4f(0.0, 0.7, 0.0, 1);
    draw_player(compx, compy, -5.0);

    glColor4f(0.7, 0.0, 0.0, 0.8);
    draw_player(playerx, playery, 0.0);

    glFlush();
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    wd = glutCreateWindow("Game");
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}
