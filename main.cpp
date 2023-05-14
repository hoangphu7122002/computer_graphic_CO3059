#include "Mesh.hpp"
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

float angle = 0;
int rotate_tayQuay = 359;
float rotate_Wheel = 0;
bool drawToggle = 0;
bool viewToggle = 1;
float cameraHeight = 10;
float cameraDistance = 10;
bool drawFlag = false;

float util_ambient[4];
float util_diffuse[4];
float util_specular[4];
float shine = 12.8f;
//Shape1 parameter
// int nSegment, float I1_R, float I2_R, float O_R, float I_fAngle, float O_fAngle, float lHeight, float hHeight, float dTam
// 32,1.5,3,1.5,PI/3,PI/3 + PI/12,0.5,1.2,1

//Shape2 parameter
// int nSegment, float lHeight, float hHeight, float fIRadius, float fORadius, float fAngle
// 32,0.3,1.2,1,1.5,PI/3 + PI/6

vector <Shape1> shape1 = {};
Cuboid GiaDo = Cuboid(4,0.5,4);
Cylinder HinhTru = Cylinder(32,1,0.23);
Cuboid thanhNgang = Cuboid(1,0.295,0.15);
Shape2 shape2 = Shape2(32,0.3,0.6,1,1.5,M_PI/3 + M_PI/6);
// Shape1(32,0.5,0.8,1.5,2,M_PI/4,1)

void drawText(float xPos, float yPos, float zPos,string str) {
    glRasterPos3f(xPos, yPos, zPos);
    void* font = GLUT_BITMAP_9_BY_15;
    for (int i = 0; i < str.length(); ++i)
        glutBitmapCharacter(font,str[i]);
}

void drawAxis() {
    glLineWidth(3);
    glBegin(GL_LINES);
        // glVertex3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(5,0,0);
        
        // glVertex3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,5,0);
        
        // glVertex3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,5);
    glEnd();
    glColor3f(0,0,0);
    drawText(4.9,0,0,"X");
    drawText(0,4.3,0,"Y");
    drawText(0,0,4.9,"Z");
}

void keyNormal(unsigned char key, int x, int y) {
    rotate_tayQuay %= 360;
    if (key == '1') {
        rotate_tayQuay -= 2;
        if (rotate_tayQuay >= 263);
        else if (rotate_tayQuay >= 257) {
            rotate_Wheel -= 0.5;
        }
        else if (rotate_tayQuay >= 251) {
            rotate_Wheel -= 0.6;
        }
        else if (rotate_tayQuay >= 233) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= 221) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay >= 209) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= 199) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay >= 179) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= 161) {
            rotate_Wheel -= 0.85;
        }
        else if (rotate_tayQuay >= 141) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay >= 117) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= 105) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay == 103) {
            rotate_Wheel -= 0.55;
        }
        else if (rotate_tayQuay >= -97);
        else if (rotate_tayQuay >= -103) {
            rotate_Wheel -= 0.5;
        }
        else if (rotate_tayQuay >= -109) {
            rotate_Wheel -= 0.6;
        }
        else if (rotate_tayQuay >= -127) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= -139) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay >= -151) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= -161) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay >= -181) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= -199) {
            rotate_Wheel -= 0.85;
        }
        else if (rotate_tayQuay >= -219) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay >= -243) {
            rotate_Wheel -= 0.8;
        }
        else if (rotate_tayQuay >= -255) {
            rotate_Wheel -= 0.7;
        }
        else if (rotate_tayQuay == -257) {
            rotate_Wheel -= 0.55;
        }
    }
    else if (key == '2') {
        rotate_tayQuay += 2;
        if (rotate_tayQuay >= 263);
        else if (rotate_tayQuay >= 257) {
            rotate_Wheel += 0.5;
            
        }
        else if (rotate_tayQuay >= 251) {
            rotate_Wheel += 0.6;
            
        }
        else if (rotate_tayQuay >= 233) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= 221) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay >= 209) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= 199) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay >= 179) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= 161) {
            rotate_Wheel += 0.85;
            
        }
        else if (rotate_tayQuay >= 141) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay >= 117) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= 105) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay == 103) {
            rotate_Wheel += 0.55;
            
        }
        else if (rotate_tayQuay >= -97);
        else if (rotate_tayQuay >= -103) {
            rotate_Wheel += 0.5;
            
        }
        else if (rotate_tayQuay >= -109) {
            rotate_Wheel += 0.6;
            
        }
        else if (rotate_tayQuay >= -127) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= -139) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay >= -151) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= -161) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay >= -181) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= -199) {
            rotate_Wheel += 0.85;
            
        }
        else if (rotate_tayQuay >= -219) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay >= -243) {
            rotate_Wheel += 0.8;
            
        }
        else if (rotate_tayQuay >= -255) {
            rotate_Wheel += 0.7;
            
        }
        else if (rotate_tayQuay == -257) {
            rotate_Wheel += 0.55;
            
        }
    }
    else if (key == 'W' || key == 'w') drawToggle = !drawToggle;
    else if (key == 'V' || key == 'v') viewToggle = !viewToggle;
    else if (key == '+') cameraDistance += 0.1;
    else if (key == '-') cameraDistance -= 0.1;
    else if (key == '3') drawFlag = !drawFlag;
    // cout << "quay_tay: " << rotate_tayQuay << endl;
    glutPostRedisplay();
}

void setupMauNorm(float ambient[4],float diffuse[4], float specular[4], float shine_util) {
    for (int i = 0; i < 4; ++i) {
        util_ambient[i] = ambient[i];
        util_diffuse[i] = diffuse[i];
        util_specular[i] = specular[i];
    }
    shine = shine_util;
    glMaterialfv(GL_FRONT, GL_AMBIENT, util_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, util_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, util_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

void drawChainShape1() {
    float mat_ambient[] ={ 0.1f, 0.18725f, 0.1745f, 0.8f };
    float mat_diffuse[] ={0.396f, 0.74151f, 0.69102f, 0.8f };
    float mat_specular[] ={0.297254f, 0.30829f, 0.306678f, 0.8f };
    
    setupMauNorm(mat_ambient, mat_diffuse, mat_specular , 12.8);
    for (int i = 0; i < 6; ++i) {
        glPushMatrix();
        glRotatef(60 * i,0,1,0);
        glTranslated(0.4,0.5,0);
        if (drawToggle == false) shape1[i].DrawNorm();
        else shape1[i].DrawWireframe();
        // shape1[i].vien(0.5);
        glPopMatrix();
    }
    
    float mat_ambient1[] ={ 0.2295f, 0.08825f, 0.0275f, 1.0f };
    float mat_diffuse1[] ={0.5508f, 0.2118f, 0.066f, 1.0f };
    float mat_specular1[] ={0.580594f, 0.223257f, 0.0695701f, 1.0f };
    setupMauNorm(mat_ambient1, mat_diffuse1, mat_specular1 , 51.2f);
    
    if (drawToggle == false) GiaDo.DrawNorm();
    else GiaDo.DrawWireframe();
}

void drawTayQuay() {
    float mat_ambient[] ={ 0.135f, 0.2225f, 0.1575f, 0.95f };
    float mat_diffuse[] ={0.54f, 0.89f, 0.63f, 0.95f };
    float mat_specular[] ={0.316228f, 0.316228f, 0.316228f, 0.95f };
    
    setupMauNorm(mat_ambient, mat_diffuse, mat_specular , 12.8f);
    glPushMatrix();
    glTranslated(-0.9,0.5,0);
    
    if (drawToggle == false) HinhTru.DrawNorm();
    else HinhTru.DrawWireframe();
    glPopMatrix(); 
    
    glPushMatrix();
    glTranslated(0,1,0);
    if (drawToggle == false) shape2.DrawNorm();
    else shape2.DrawWireframe();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,1,0);
    if (drawToggle == false) thanhNgang.DrawNorm();
    else thanhNgang.DrawWireframe();
    glPopMatrix();
}



void lightSetup() {
    float ambient[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specular[4] ={ 0.3f, 0.3f, 0.3f, 1.0f };
    float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[4] = { -10.0f, 5.0f, -10.0f, 0.0f };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (viewToggle) gluLookAt(cameraDistance,cameraHeight,cameraDistance,0,0,0,0,1,0);
    else gluLookAt(0,15,0,0,0,0,1,0,0);
    
    glRotatef(angle,0,1,0);
    lightSetup();
    
    // glViewport(0,0,500,500);
    glPushMatrix();
    glRotatef(rotate_Wheel,0,1,0);
    drawChainShape1();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.4,0,0);
    glRotatef(rotate_tayQuay,0,1,0);
    drawTayQuay();
    glPopMatrix();

    
    glFlush();
}

void init() {
    glClearColor(1.0,1.0,1.0,1.0);
    glFrontFace(GL_CCW);
    glColor3f(0.0,0.0,0.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-4,4,-4,4,-10,10);
    gluPerspective(38.7, 1, 1, 1000);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glFrustum(-0.3,0.3,-0.3,0.3,1,1000);
    
    
}

void mySpecialFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) 
        angle += 5;
    else if (key == GLUT_KEY_RIGHT) 
        angle -= 5;
    else if (key == GLUT_KEY_UP) {
        cameraHeight += 0.2;
    }
    else if (key == GLUT_KEY_DOWN) {
        cameraHeight -= 0.2;
    }
    glutPostRedisplay();
} 


int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("tet Mesh");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    glutKeyboardFunc(keyNormal);
    for (int i = 0; i < 6; ++i) shape1.push_back(Shape1(32,1.5,3,1.5,M_PI/3,M_PI/3 + M_PI/12,0.5,1.2,1));
    for (int i = 0; i < 6; ++i) shape1[i].creatShape();
    GiaDo.createShape();
    shape2.creatShape();
    HinhTru.createShape();
    
    thanhNgang.createShape();
    init();
    
    glutMainLoop();
}