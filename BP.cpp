#include "BP.h"
#include "math.h"


BP::BP(Vector3 *arr, int xlen, int ylen) {
    for(int i = 0; i < 16; i++)
        ctrl[i] = arr[i];
    x = xlen;
    y = ylen;

    /*
    q0 = Matrix4(ctrl[0].getX(),ctrl[1].getX(),ctrl[2].getX(),ctrl[3].getX(),
                 ctrl[0].getY(),ctrl[1].getY(),ctrl[2].getY(),ctrl[3].getY(),
                 ctrl[0].getZ(),ctrl[1].getZ(),ctrl[2].getZ(),ctrl[3].getZ());
    q1 = Matrix4(ctrl[4].getX(),ctrl[5].getX(),ctrl[6].getX(),ctrl[7].getX(),
                 ctrl[4].getY(),ctrl[5].getY(),ctrl[6].getY(),ctrl[7].getY(),
                 ctrl[4].getZ(),ctrl[5].getZ(),ctrl[6].getZ(),ctrl[7].getZ());
    q2 = Matrix4(ctrl[8].getX(),ctrl[9].getX(),ctrl[10].getX(),ctrl[11].getX(),
                 ctrl[8].getY(),ctrl[9].getY(),ctrl[10].getY(),ctrl[11].getY(),
                 ctrl[8].getZ(),ctrl[9].getZ(),ctrl[10].getZ(),ctrl[11].getZ());
    q4 = Matrix4(ctrl[12].getX(),ctrl[13].getX(),ctrl[14].getX(),ctrl[15].getX(),
                 ctrl[12].getY(),ctrl[13].getY(),ctrl[14].getY(),ctrl[15].getY(),
                 ctrl[12].getZ(),ctrl[13].getZ(),ctrl[14].getZ(),ctrl[15].getZ());
    */
    
    
    //Formula copied from Lecture Slide "GLSL" slide 12
    gx = Matrix4(ctrl[0].getX(),ctrl[1].getX(),ctrl[2].getX(),ctrl[3].getX(),
                 ctrl[4].getX(),ctrl[5].getX(),ctrl[6].getX(),ctrl[7].getX(),
                 ctrl[8].getX(),ctrl[9].getX(),ctrl[10].getX(),ctrl[11].getX(),
                 ctrl[12].getX(),ctrl[13].getX(),ctrl[14].getX(),ctrl[15].getX());
    gy = Matrix4(ctrl[0].getY(),ctrl[1].getY(),ctrl[2].getY(),ctrl[3].getY(),
                 ctrl[4].getY(),ctrl[5].getY(),ctrl[6].getY(),ctrl[7].getY(),
                 ctrl[8].getY(),ctrl[9].getY(),ctrl[10].getY(),ctrl[11].getY(),
                 ctrl[12].getY(),ctrl[13].getY(),ctrl[14].getY(),ctrl[15].getY());
    gz = Matrix4(ctrl[0].getZ(),ctrl[1].getZ(),ctrl[2].getZ(),ctrl[3].getZ(),
                 ctrl[4].getZ(),ctrl[5].getZ(),ctrl[6].getZ(),ctrl[7].getZ(),
                 ctrl[8].getZ(),ctrl[9].getZ(),ctrl[10].getZ(),ctrl[11].getZ(),
                 ctrl[12].getZ(),ctrl[13].getZ(),ctrl[14].getZ(),ctrl[15].getZ());
    cx = bbez * gx * bbez; //transpose of bbez is the same as bbez
    cy = bbez * gy * bbez;
    cz = bbez * gz * bbez;
    shader = new Shader("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/reflection.vert","/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/reflection.frag");
}

void BP::update() { }

double BP::coeff(double n, double i, double t) {
    return combo(n, i) * pow(1.0-t, n-i) * pow(t, i);
}

double BP::combo(double n, double i) {
    return factorial(n) / (factorial(n-i) * factorial(i));
}

double BP::factorial(double n) {
    double result = 1;
    if( n <=0 )
        return result;
    
    for(double i = n; i > 0; --i) {
        result *= i;
    }
    
    return result;
}

Vector3 BP::getPoint(double u, double v) {
    Vector4 uvector(u * u * u, u * u, u, 1);
    Vector4 vvectort(v * v * v, v* v, v, 1);
    Vector4 vcx = cx.reversemul(vvectort);
    Vector4 vcy = cy.reversemul(vvectort);
    Vector4 vcz = cz.reversemul(vvectort);
    return Vector3(vcx * uvector,
                   vcy * uvector,
                   vcz * uvector);
}

void BP::render() {
    if(shade) {
        shader->bind();
        glEnable(GL_TEXTURE_CUBE_MAP);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cm);
    }
    glBegin(GL_QUADS);
    for(int yy = 0; yy < y; yy++) {
        Vector3 tl = getPoint(0,(yy+1)/double(y)); //top left
        Vector3 bl = getPoint(0,yy/double(y)); //bottom left
        for(int xx = 1; xx <= x; xx++) {
            Vector3 br = getPoint(xx/double(x),yy/double(y)); //bottom right
            Vector3 tr = getPoint(xx/double(x),(yy+1)/double(y)); //top right
            Vector3 tanu = bl - tl; //tangent approximation
            Vector3 tanv = tr - tl;
            Vector3 normal = tanu.cross(tanv);
            normal.normalize();
            glNormal3d(normal.getX(),normal.getY(),normal.getZ());
            glVertex3d(tl.getX(),tl.getY(),tl.getZ());
            glVertex3d(bl.getX(),bl.getY(),bl.getZ());
            glVertex3d(br.getX(),br.getY(),br.getZ());
            glVertex3d(tr.getX(),tr.getY(),tr.getZ());
            tl = tr;
            bl = br;
        }
    }
    glEnd();
    if(shade) {
        glDisable(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP,0);
        shader->unbind();
    }
}

void BP::setCM(GLuint s) {
    cm = s;
}

void BP::wave(double height, double time) {
    for(int i = 0; i < 16; i++) {
        double dist = sqrt(ctrl[i].getX() * ctrl[i].getX() + ctrl[i].getZ() * ctrl[i].getZ());
        double ydif = height * sin(M_PI * dist * time / 2); //using a sine wave
        ctrl[i].setY(ydif);
    }

    gy = Matrix4(ctrl[0].getY(),ctrl[1].getY(),ctrl[2].getY(),ctrl[3].getY(),
                 ctrl[4].getY(),ctrl[5].getY(),ctrl[6].getY(),ctrl[7].getY(),
                 ctrl[8].getY(),ctrl[9].getY(),ctrl[10].getY(),ctrl[11].getY(),
                 ctrl[12].getY(),ctrl[13].getY(),ctrl[14].getY(),ctrl[15].getY());
    cy = bbez * gy * bbez;
}

void BP::shadeSwitch() {
    shade = !shade;
}