#include "supportClass.hpp"

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
	Face()
	{
		nVerts = 0;
		vert = NULL;
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
	void DrawNorm();
	// void createShape();
};

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