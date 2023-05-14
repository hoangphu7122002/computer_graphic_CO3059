#include "Mesh.hpp"
#include <iostream>

using namespace std;

#define PI 3.1415926

void Cylinder::createShape()
{
	numVerts = nSegments*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegments;
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