#include "Mesh.hpp"

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