#include "Mesh.hpp"

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
    
    //mat tu giac ngoai
    // for (i = 0; i < nSegment; ++i) {
    //     face[idx].nVerts = 4;
    //     face[idx].vert = new VertexID[face[idx].nVerts];
    //     face[idx].vert[0].vertIndex = 0;
    //     face[idx].vert[1].vertIndex = numVerts - 1;
    //     face[idx].vert[2].vertIndex = i + 1 + 2*nSegment;
    //     face[idx].vert[3].vertIndex = i + 1;
        
    //     idx++;
    // }
    
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
        idx++;
    }
    
    //mat ben chu nhat nho
    // for (i = 2*nSegment; i < 3*nSegment - 1; ++i) {
    //     face[idx].nVerts = 4;
    //     face[idx].vert = new VertexID[face[idx].nVerts];
    //     face[idx].vert[0].vertIndex = i + 1;
    //     face[idx].vert[1].vertIndex = i + nSegment + 1;
    //     face[idx].vert[2].vertIndex = i - nSegment + 1;
    //     face[idx].vert[3].vertIndex = i - 2 * nSegment + 1;
    //     idx++;
    // }
    
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

float vien(float line) {
    
}