#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

//=====================Helper Class====================
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Point3& p)
						{ x = p.x; y = p.y; z = p.z;}
	Point3() { x = y = z = 0;}
	Point3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
						{ r = red; g = green; b = blue;}
	void set(Color3& c)
						{ r = c.r; g = c.g; b = c.b;}
	Color3() { r = g = b = 0;}
	Color3(float red, float green, float blue)
						{ r = red; g = green; b = blue;}

};
class Point2
{
	public:
		Point2() { x = y = 0.0f; } // constructor 1
		Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
		void set(float xx, float yy) { x = xx; y = yy; }
		float getX() { return x;}
		float getY() { return y;}
		void draw()		{	glBegin(GL_POINTS);
								glVertex2f((GLfloat)x, (GLfloat)y);
							glEnd();
						}
	private:
		float 	x, y;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	void flip()
						{ x = -x; y = -y; z = -z;}
	void normalize();
	Vector3() { x = y = z = 0;}
	Vector3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	Vector3(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};
//=====================Helper Class====================

//====================Implement Helper Class======================
Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}

void Vector3::normalize()
{
	float temp = sqrt(x*x + y*y + z*z);
	x = x/temp;
	y = y/temp;
	z = z/temp;
}
//====================Implement Helper Class======================

//====================Util Class==========================
class VertexID
{
public:
	int	vertIndex;
	int	colorIndex;
};

class Face
{
public:
	int	nVerts;
	VertexID* vert;
	Vector3 norm;
	bool flag = false;
	Face()
	{
		nVerts = 0;
		vert = NULL;
		flag = false;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int	numVerts;
	Point3*	pt;
	
	int	numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void reset() {
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor(int color);
	void calculateNorm();
	void DrawNorm(bool flag, float ambient_default[4],float diffuse_default[4], float specular_default[4], float shine_default, float ambient[4],float diffuse[4], float specular[4], float shine);
	// void createShape();
};
//====================Util Class==========================

//====================Concrete Class=====================
class Cylinder : public Mesh {
private:
	int nSegments;
	float height, radius;
public:     
	Cylinder(int nSegments, float height, float radius){
		this->nSegments = nSegments;
		this->height = height;
		this->radius = radius;
	}
	int getNSegments() {return this->nSegments;}
	float getHeight() {return this->height;}
	float getRadius() {return this->radius;}
	void createShape();
	void vien(float line);
	
};

class Cuboid : public Mesh {
private:
	float fsizeX;
	float fsizeY;
	float fsizeZ;
public:
	Cuboid(float x, float y, float z) {
		this->fsizeX = x;
		this->fsizeY = y;
		this->fsizeZ = z;
	}
	
	float getX() {return this->fsizeX;}
	float getY() {return this->fsizeY;}
	float getZ() {return this->fsizeZ;}
	void createShape();
	void vien(float line);
};

class Shape1 : public Mesh {
private:
	int nSegment;
	float I1_R;
	float I2_R;
	float O_R; 
	float I_fAngle; 
	float O_fAngle; 
	float lHeight;
	float hHeight;
	float dTam;
public:
	Shape1(int nSegment, float I1_R, float I2_R, float O_R, float I_fAngle, float O_fAngle, float lHeight, float hHeight, float dTam){
		this->nSegment = nSegment;
		this->I1_R = I1_R;
		this->I2_R = I2_R;
		this->O_R = O_R;  
		this->I_fAngle = I_fAngle; 
		this->O_fAngle = O_fAngle; 
		this->lHeight = lHeight;
		this->hHeight = hHeight;
		this->dTam = dTam;
	}
	void creatShape();
	void vien(float line);
};

class Shape2 : public Mesh {
private:
	int nSegment;
	float lHeight;
	float hHeight;
	float fIRadius;
	float fORadius;
	float fAngle;
public:
	Shape2(int nSegment, float lHeight, float hHeight, float fIRadius, float fORadius, float fAngle){
		this->nSegment = nSegment;
		this->lHeight = lHeight;
		this->hHeight = hHeight;
		this->fIRadius = fIRadius;
		this->fORadius = fORadius;
		this->fAngle = fAngle;	
	}
	void creatShape();
	void vien(float line);
};

//====================Concrete Class=====================

//===================Implement drawMethod========================
#define	COLORNUM 14

float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

void Mesh::DrawWireframe()
{  
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::calculateNorm(){
	float dx, dy, dz;
	int idx, next;
	for (int f = 0; f < numFaces; f++) {
		dx = 0;
		dy = 0;
		dz = 0;
		for (int v = 0; v < face[f].nVerts; v++) {
			idx = v;
			next = (idx + 1) % face[f].nVerts;

			int p1 = face[f].vert[idx].vertIndex;
			int p2 = face[f].vert[next].vertIndex;

			dx = dx + (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
			dy = dy + (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
			dz = dz + (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);
		}
		face[f].norm.set(dx, dy, dz);
		face[f].norm.normalize();
	}
}

void Mesh::DrawColor(int color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawNorm(bool flag, float ambient_default[4],float diffuse_default[4], float specular_default[4], float shine_default, float ambient[4],float diffuse[4], float specular[4], float shine) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		if (flag == false) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_default);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_default);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular_default);
			glMaterialf(GL_FRONT, GL_SHININESS, shine_default);
		}
		else {
			if (face[f].flag == true) {
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				glMaterialf(GL_FRONT, GL_SHININESS, shine);	
			}
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_default);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_default);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_default);
				glMaterialf(GL_FRONT, GL_SHININESS, shine_default);			
			}
		}
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].norm.x,face[f].norm.y,face[f].norm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
//===================Implement drawMethod========================

//====================Implement Cuboid===================
void Cuboid::createShape() {
    numVerts = 8;
    float x = fsizeX;
    float y = fsizeY;
    float z = fsizeZ;
    pt = new Point3[numVerts];
    pt[0] = Point3(x,0,z);
    pt[1] = Point3(x,0,-z);
    pt[2] = Point3(x,y,-z);
    pt[3] = Point3(x,y,z);
    pt[4] = Point3(-x, y,-z);
    pt[5] = Point3(-x,y,z);
    pt[6] = Point3(-x,0,z);
    pt[7] = Point3(-x,0,-z);
    
    numFaces = 6;
    face = new Face[numFaces];
    
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 0;
    face[0].vert[1].vertIndex = 1;
    face[0].vert[2].vertIndex = 2;
    face[0].vert[3].vertIndex = 3;
    
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 2;
    face[1].vert[1].vertIndex = 4;
    face[1].vert[2].vertIndex = 5;
    face[1].vert[3].vertIndex = 3;
    
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 5;
    face[2].vert[1].vertIndex = 4;
    face[2].vert[2].vertIndex = 7;
    face[2].vert[3].vertIndex = 6;
    
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 1;
    face[3].vert[1].vertIndex = 0;
    face[3].vert[2].vertIndex = 6;
    face[3].vert[3].vertIndex = 7;
    
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 5;
    face[4].vert[1].vertIndex = 6;
    face[4].vert[2].vertIndex = 0;
    face[4].vert[3].vertIndex = 3;
    
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 7;
    face[5].vert[1].vertIndex = 4;
    face[5].vert[2].vertIndex = 2;
    face[5].vert[3].vertIndex = 1;
    
    calculateNorm();
}
//====================Implement Cuboid===================

//====================Implement Cylinder=======================
void Cylinder::createShape()
{
	numVerts = nSegments*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*M_PI/nSegments;
	float	x, y, z;

	pt[0].set(0, 0, 0);
	for(i = 0; i<nSegments; i++)
	{
		x = radius* cos(fAngle*i);
		z = radius* sin(fAngle*i);
		y = 0;
		pt[i+1].set(x, y, z);

		y = height;
		pt[i +1 + nSegments].set(x, y, z);
	}
	pt[numVerts-1].set(0, height, 0);

	numFaces= nSegments*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegments; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegments -1)
			face[idx].vert[2].vertIndex = i + 2;
		else
			face[idx].vert[2].vertIndex = 1;
		face[idx].vert[1].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegments; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[1].vertIndex = i+1;
		if(i <nSegments - 1)
			face[idx].vert[0].vertIndex = i+2;
		else
			face[idx].vert[0].vertIndex = 1;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegments;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegments;

		idx++;
	}

	for(i = 0; i<nSegments; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegments -1)
			face[idx].vert[1].vertIndex = i + 2 + nSegments;
		else
			face[idx].vert[1].vertIndex = 1 + nSegments;
		face[idx].vert[2].vertIndex = i + 1 + nSegments;
		idx++;
	}
}
//====================Implement Cylinder=======================

//====================Implement Shape1=========================
void Shape1::creatShape() {
    numVerts = nSegment * 6 + 6;
    pt = new Point3[numVerts];
    
    int i;
    int idx;
    float Beta_I = -I_fAngle/2;
    float Beta_O = -O_fAngle/2;
    I_fAngle = (I_fAngle/nSegment);
    O_fAngle = (O_fAngle/nSegment);
    float x,y,z;
    
    //duong tron nho dong tam
    
    for (i = 0; i < nSegment; ++i) {
        x =  I1_R * cos(Beta_I + I_fAngle * i);
        z =  I1_R * sin(Beta_I + I_fAngle * i);
        pt[i + 1].set(x,0,z);
        pt[i + nSegment + 1].set(x,lHeight,z); //duong tron nho dong tam mat tren
    }   
    
    //duong tron lon dong tam
    for (i = 0; i < nSegment; ++i) {
        x =  I2_R * cos(Beta_I + I_fAngle * i);
        z =  I2_R * sin(Beta_I + I_fAngle * i);
        pt[i + 2 * nSegment + 1].set(x,0,z);
        pt[i + 3 * nSegment + 1].set(x,hHeight,z); //duong tron lon dong tam mat tren
    }
    
    //duong tron khong dong tam
    for (i = 0; i < nSegment; ++i) {
        x = O_R * cos(Beta_O + O_fAngle * i) + dTam;
        z = O_R * sin(Beta_O + O_fAngle * i) ;
        pt[i + 4 * nSegment + 1].set(x,lHeight,z);
        pt[i + 5 * nSegment + 1].set(x,hHeight,z);
    }
    
    //ban kinh dinh moi
    float R_moi = (I2_R - (I2_R - I1_R)/3);
    float goc_trai = Beta_I;
    float goc_phai = Beta_I + I_fAngle * (nSegment - 1);
    pt[0].set(R_moi * cos(goc_trai),0,R_moi * sin(goc_trai));
    pt[numVerts-1].set(R_moi * cos(goc_phai),0,R_moi * sin(goc_phai));
    pt[numVerts-2].set(R_moi * cos(goc_trai),lHeight,R_moi * sin(goc_trai));
    pt[numVerts-3].set(R_moi * cos(goc_phai),lHeight,R_moi * sin(goc_phai));
    pt[numVerts-4].set(R_moi * cos(goc_trai),hHeight,R_moi * sin(goc_trai));
    pt[numVerts-5].set(R_moi * cos(goc_phai),hHeight,R_moi * sin(goc_phai));
    
    numFaces = nSegment * 6 + 10; 
    face = new Face[numFaces];
    idx = 0;
    //mat chu nhat ngoai cung trai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[1].vertIndex = 0;
    face[idx].vert[0].vertIndex = 1 + 2 * nSegment;
    face[idx].vert[3].vertIndex = 1 + 3 * nSegment;
    face[idx].vert[2].vertIndex = numVerts - 4;
    face[idx].flag = true;
    idx++;
    
    //mat chu nhat ngoai cung phai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts - 1;
    face[idx].vert[1].vertIndex = 3 * nSegment;
    face[idx].vert[2].vertIndex = 4 * nSegment;
    face[idx].vert[3].vertIndex = numVerts - 5;
    face[idx].flag = true;
    idx++;
    
    //mat tam giac tren trai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-4;
    face[idx].vert[2].vertIndex = 1 + 3 * nSegment;
    face[idx].vert[1].vertIndex = 1 + 5 * nSegment;
    // face[idx].flag = true;
    idx++;
    
    //mat tam giac tren phai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-5;
    face[idx].vert[1].vertIndex = 4 * nSegment;
    face[idx].vert[2].vertIndex = 6 * nSegment;
    // face[idx].flag = true;
    idx++;
    
    //mat hinh chu nhat truoc trai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[1].vertIndex = numVerts - 2;
    face[idx].vert[0].vertIndex = numVerts - 4;
    face[idx].vert[3].vertIndex = 1 + 5 * nSegment;
    face[idx].vert[2].vertIndex = 1 + 4 * nSegment;
    // face[idx].flag = true;
    idx++;
    
    //mat hinh chu nhat truoc phai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts - 3;
    face[idx].vert[1].vertIndex = numVerts - 5;
    face[idx].vert[2].vertIndex = 6 * nSegment;
    face[idx].vert[3].vertIndex = 5 * nSegment;
    // face[idx].flag = true;
    idx++;
    
    //mat tam giac huong len trai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-2;
    face[idx].vert[2].vertIndex = 1 + 4 * nSegment;
    face[idx].vert[1].vertIndex = 1 + 1 * nSegment;
    // face[idx].flag = true;
    idx++;
    
    //mat tam giac huong len phai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-3;
    face[idx].vert[1].vertIndex = 5 * nSegment;
    face[idx].vert[2].vertIndex = 2 * nSegment;
    // face[idx].flag = true;
    idx++;
    
    //mat chu nhat ngang ria ngoai trai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[1].vertIndex = 1 + 0 * nSegment;
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[3].vertIndex = numVerts - 2;
    face[idx].vert[2].vertIndex = 1 + 1 * nSegment;
    face[idx].flag = true;
    idx++;
    
    //mat chu nhat ngang ria ngoai phai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 1 * nSegment;
    face[idx].vert[1].vertIndex = numVerts - 1;
    face[idx].vert[2].vertIndex = numVerts - 3;
    face[idx].vert[3].vertIndex = 2 * nSegment;
    face[idx].flag = true;
    idx++;
    
    //mat day I1_R(0) va I2_R(0)
    for (i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[1].vertIndex = i + 1;
        face[idx].vert[0].vertIndex = i + 2;
        face[idx].vert[3].vertIndex = i + 2 + 2 * nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 2 * nSegment;
        idx++;
    }

    //mat not cum tu giac I2_R(0) va I2_R(H)
    for (int i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[1].vertIndex = i + 1 + 2 * nSegment;
        face[idx].vert[0].vertIndex = i + 2 + 2 * nSegment;
        face[idx].vert[3].vertIndex = i + 2 + 3 * nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        idx++;
    }

    //mat hinh lom nho giua I1_R(0) va I1_R(1)
    for (i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1;
        face[idx].vert[1].vertIndex = i + 2;
        face[idx].vert[2].vertIndex = i + 2 + 1 * nSegment;
        face[idx].vert[3].vertIndex = i + 1 + 1 * nSegment;
        idx++;
    }
    
    //mat noi cac cum tu giac I1_R(l) va O_R(l)
    for (i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1 + 1 * nSegment;
        face[idx].vert[1].vertIndex = i + 2 + 1 * nSegment;
        face[idx].vert[2].vertIndex = i + 2 + 4 * nSegment;
        face[idx].vert[3].vertIndex = i + 1 + 4 * nSegment;
        idx++;
    }
    
    //mat noi cac cum tu giac O_R(l) va O_R(H)
    for (int i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1 + 4 * nSegment;
        face[idx].vert[1].vertIndex = i + 2 + 4 * nSegment;
        face[idx].vert[2].vertIndex = i + 2 + 5 * nSegment;
        face[idx].vert[3].vertIndex = i + 1 + 5 * nSegment;
        face[idx].flag = true;
        idx++;
    }
    
    //mat noi cac cum tu giac I2_R(H) va O_R(H)
    for (int i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[1].vertIndex = i + 1 + 3 * nSegment;
        face[idx].vert[0].vertIndex = i + 2 + 3 * nSegment;
        face[idx].vert[3].vertIndex = i + 2 + 5 * nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 5 * nSegment;
        idx++;
    }
    
    calculateNorm();
}
//====================Implement Shape1=========================

//====================Implement Shape2=========================
void Shape2::creatShape() {
    numVerts = nSegment * 4 + 2;
    pt = new Point3[numVerts];
    
    int i;
    int idx;
    float Beta_f = -fAngle/2;
    fAngle = fAngle/nSegment;
    float x,y,z;
    //far
    pt[0].set(0,0,0);
    for (i = 0; i < nSegment; ++i) {
        x =  fORadius * cos(Beta_f + fAngle * i);
        z =  fORadius * sin(Beta_f + fAngle * i);
        pt[i + 1].set(x,0,z);
        pt[i + nSegment + 1].set(x,hHeight,z);
    }
    
    //near
    pt[numVerts-1].set(0,lHeight,0);
    for (i = 0; i < nSegment; ++i) {
        x =  fIRadius * cos(Beta_f + fAngle * i);
        z =  fIRadius * sin(Beta_f + fAngle * i);
        pt[i + 2*nSegment + 1].set(x,lHeight,z);
        pt[i + 3*nSegment + 1].set(x,hHeight,z);
    }
    
    numFaces = nSegment * 7 + 4; 
    face = new Face[numFaces];
    
    idx = 0;
    
    //tam giac tren
    for (i = 2*nSegment; i < 3*nSegment - 1; ++i) {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = numVerts - 1;
        if (i < 3*nSegment - 1) {
			face[idx].vert[1].vertIndex = i + 2;
        }
        else face[idx].vert[1].vertIndex = 2*nSegment + 1;
        face[idx].vert[2].vertIndex = i + 1;   
        idx++;
    }
    
    //tam giac duoi
    for (i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        if (i < nSegment - 1) {
			face[idx].vert[1].vertIndex = i + 2;
        }
        else face[idx].vert[1].vertIndex = 1;
        face[idx].vert[2].vertIndex = i + 1;   
        idx++;
    }
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[1].vertIndex = numVerts - 1;
    face[idx].vert[2].vertIndex = 1 + 2*nSegment;
    face[idx].vert[3].vertIndex = 1;
    idx++;
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[1].vertIndex = 0;
    face[idx].vert[0].vertIndex = numVerts - 1;
    face[idx].vert[3].vertIndex = 3*nSegment;
    face[idx].vert[2].vertIndex = nSegment;
    idx++;
    
    //mat chu nhat nho phia truoc
    for (i = 2*nSegment; i < 3*nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1;
        face[idx].vert[1].vertIndex = i + 2;
        face[idx].vert[2].vertIndex = i + 2 + nSegment;
        face[idx].vert[3].vertIndex = i + 1 + nSegment;
        face[idx].flag = true;
        idx++;
    }
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 2*nSegment + 1;
    face[idx].vert[1].vertIndex = 2*nSegment + nSegment + 1;
    face[idx].vert[2].vertIndex = 2*nSegment - nSegment + 1;
    face[idx].vert[3].vertIndex = 2*nSegment - 2 * nSegment + 1;
    idx++;
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[1].vertIndex = 3*nSegment - 2 + 1 + 1;
    face[idx].vert[0].vertIndex = 3*nSegment - 2 + nSegment + 1 + 1;
    face[idx].vert[3].vertIndex = 3*nSegment - 2 - nSegment + 1 + 1;
    face[idx].vert[2].vertIndex = 3*nSegment - 2 - 2 * nSegment + 1 + 1;
    idx++;
    
    //mat hinh chu nhat ngoai nho
    for (i = 0; i < nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1;
        face[idx].vert[1].vertIndex = i + 1 + nSegment;
        face[idx].vert[2].vertIndex = i + 2  + nSegment;
        face[idx].vert[3].vertIndex = i + 2;
        face[idx].flag = true;
        idx++;
    }
    
    //mat hinh chu nhat tren
    for (i = 3*nSegment; i < 4*nSegment - 1; ++i) {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1;
        face[idx].vert[1].vertIndex = i + 2;
        face[idx].vert[2].vertIndex = i + 2  - 2 * nSegment;
        face[idx].vert[3].vertIndex = i + 1 - 2 * nSegment;
        idx++;
    }   
    calculateNorm();
}
//====================Implement Shape2=========================

//====================Main implement==========================
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

float ambient_default[4] ={0.25f, 0.25f, 0.25f, 1.0f  };
float diffuse_default[4] ={0.4f, 0.4f, 0.4f, 1.0f };
float specular_default[4] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
float shine_default = 76.8f;
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
    
    for (int i = 0; i < 6; ++i) {
        glPushMatrix();
        glRotatef(60 * i,0,1,0);
        glTranslated(0.4,0.5,0);
        if (drawToggle == false) shape1[i].DrawNorm(drawFlag,mat_ambient, mat_diffuse, mat_specular , 12.8, ambient_default, diffuse_default, specular_default, shine_default);
        else shape1[i].DrawWireframe();
        // shape1[i].vien(0.5);
        glPopMatrix();
    }
    
    float mat_ambient1[] ={ 0.2295f, 0.08825f, 0.0275f, 1.0f };
    float mat_diffuse1[] ={0.5508f, 0.2118f, 0.066f, 1.0f };
    float mat_specular1[] ={0.580594f, 0.223257f, 0.0695701f, 1.0f };
    
    if (drawToggle == false) GiaDo.DrawNorm(drawFlag,mat_ambient1, mat_diffuse1, mat_specular1 , 12.8, ambient_default, diffuse_default, specular_default, shine_default);
    else GiaDo.DrawWireframe();
}

void drawTayQuay() {
    float mat_ambient[] ={ 0.135f, 0.2225f, 0.1575f, 0.95f };
    float mat_diffuse[] ={0.54f, 0.89f, 0.63f, 0.95f };
    float mat_specular[] ={0.316228f, 0.316228f, 0.316228f, 0.95f };
    
    setupMauNorm(mat_ambient, mat_diffuse, mat_specular , 12.8f);
    glPushMatrix();
    glTranslated(-0.9,0.5,0);
    
    if (drawToggle == false) HinhTru.DrawNorm(drawFlag,mat_ambient, mat_diffuse, mat_specular , 12.8, ambient_default, diffuse_default, specular_default, shine_default);
    else HinhTru.DrawWireframe();
    glPopMatrix(); 
    
    glPushMatrix();
    glTranslated(0,1,0);
    if (drawToggle == false) shape2.DrawNorm(drawFlag,mat_ambient, mat_diffuse, mat_specular , 12.8, ambient_default, diffuse_default, specular_default, shine_default);
    else shape2.DrawWireframe();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,1,0);
    if (drawToggle == false) thanhNgang.DrawNorm(drawFlag,mat_ambient, mat_diffuse, mat_specular , 12.8, ambient_default, diffuse_default, specular_default, shine_default);
    else thanhNgang.DrawWireframe();
    glPopMatrix();
}

void myReshape(int w, int h) {
    float factor = 2;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // if (w <= h) glOrtho(-factor,factor,-factor*h/w,factor*h/w,-10,10);
    // else glOrtho(-factor*w/h,factor*w/h,-factor,factor,-10,10);
    if (w <= h) gluPerspective(38.7, (double)h / w, 1, 1000);
    else gluPerspective(38.7, (double)w / h, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
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
    cout << "1     :  Quay nguoc chieu kim dong ho" << endl;
    cout << "2     :  Quay cung chieu kim dong ho" << endl;
    cout << "3     :  Bat/tat che do to mau nang cao" << endl;
    cout << "V, v  :  Chuyen doi giua 2 che do nhin" << endl;
    cout << "W, w  :  Chuyen doi qua lai giua che do khung day va to mau" << endl;
    cout << "+     : Tang khoang cach camera" << endl;
    cout << "-     : Giam khoang cach camera" << endl;
    cout << "up arrow  : Tang chieu cao camera" << endl;
    cout << "down arrow: Giam chieu cao camera" << endl;
    cout << "<-        : Quay camera theo chieu kim dong ho" << endl;
    cout << "->        : Quay camera nguoc chieu kim dong ho" << endl;
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Nguyen Dac Hoang Phu - 2010514");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    glutKeyboardFunc(keyNormal);
    glutReshapeFunc(myReshape);
    for (int i = 0; i < 6; ++i) shape1.push_back(Shape1(32,1.5,3,1.5,M_PI/3,M_PI/3 + M_PI/12,0.5,1.2,1));
    for (int i = 0; i < 6; ++i) shape1[i].creatShape();
    GiaDo.createShape();
    shape2.creatShape();
    HinhTru.createShape();
    
    thanhNgang.createShape();
    init();
    
    glutMainLoop();
}
//====================Main implement==========================