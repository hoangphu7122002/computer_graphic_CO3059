#include <iostream>
#include "Mesh.hpp"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14

using namespace std;

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

void Mesh::DrawNorm() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].norm.x,face[f].norm.y,face[f].norm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}


