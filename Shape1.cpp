#include "Mesh.hpp"

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
    face[idx].flag = true;
    idx++;
    
    //mat tam giac tren phai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-5;
    face[idx].vert[1].vertIndex = 4 * nSegment;
    face[idx].vert[2].vertIndex = 6 * nSegment;
    face[idx].flag = true;
    idx++;
    
    //mat hinh chu nhat truoc trai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[1].vertIndex = numVerts - 2;
    face[idx].vert[0].vertIndex = numVerts - 4;
    face[idx].vert[3].vertIndex = 1 + 5 * nSegment;
    face[idx].vert[2].vertIndex = 1 + 4 * nSegment;
    face[idx].flag = true;
    idx++;
    
    //mat hinh chu nhat truoc phai
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts - 3;
    face[idx].vert[1].vertIndex = numVerts - 5;
    face[idx].vert[2].vertIndex = 6 * nSegment;
    face[idx].vert[3].vertIndex = 5 * nSegment;
    face[idx].flag = true;
    idx++;
    
    //mat tam giac huong len trai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-2;
    face[idx].vert[2].vertIndex = 1 + 4 * nSegment;
    face[idx].vert[1].vertIndex = 1 + 1 * nSegment;
    face[idx].flag = true;
    idx++;
    
    //mat tam giac huong len phai
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts-3;
    face[idx].vert[1].vertIndex = 5 * nSegment;
    face[idx].vert[2].vertIndex = 2 * nSegment;
    face[idx].flag = true;
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