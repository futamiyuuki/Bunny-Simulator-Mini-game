#include "Object.h"

Object::Object(vector<Vector3> *vertex, vector<Vector3> *normal, vector<Vector3> *vindex, vector<Vector3> *nindex, vector<Vector3> *color, Vector3 maxi, Vector3 mini) {
    ver = vertex;
    nor = normal;
    vi = vindex;
    ni = nindex;
    c = color;
    max = maxi;
    min = mini;
}

void Object::update() {}

void Object::render() {
    glBegin(GL_TRIANGLES);
    
    for(int i = 0; i < (vi->size()); i++) {
        Vector3 cx = (*c)[(*vi)[i].getX() - 1];
        Vector3 vx = (*ver)[(*vi)[i].getX() - 1];
        Vector3 nx = (*nor)[(*ni)[i].getX() - 1];
        glColor3d(cx.getX(),cx.getY(),cx.getZ());
        glNormal3d(nx.getX(),nx.getY(),nx.getZ());
        glVertex3d(vx.getX(),vx.getY(),vx.getZ());
        
        Vector3 cy = (*c)[(*vi)[i].getY() - 1];
        Vector3 vy = (*ver)[(*vi)[i].getY() - 1];
        Vector3 ny = (*nor)[(*ni)[i].getY() - 1];
        glColor3d(cy.getX(),cy.getY(),cy.getZ());
        glNormal3d(ny.getX(),ny.getY(),ny.getZ());
        glVertex3d(vy.getX(),vy.getY(),vy.getZ());
        
        Vector3 cz = (*c)[(*vi)[i].getZ() - 1];
        Vector3 vz = (*ver)[(*vi)[i].getZ() - 1];
        Vector3 nz = (*nor)[(*ni)[i].getZ() - 1];
        glColor3d(cz.getX(),cz.getY(),cz.getZ());
        glNormal3d(nz.getX(),nz.getY(),nz.getZ());
        glVertex3d(vz.getX(),vz.getY(),vz.getZ());
        //std::cout<<vx.getX()<<endl;
        //std::cout<<nx.getX()<<" "<<ny.getX()<<" "<<nz.getX()<<endl;
    }
    
    glEnd();
}