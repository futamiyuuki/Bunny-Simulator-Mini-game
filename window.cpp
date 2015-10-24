#include <iostream>

#include <GLUT/glut.h>

#include <vector>
#include <math.h>
#include <ctime>
#include "Window.h"
#include "Matrix4.h"
#include "Camera.h"
#include "parser.h"
#include "Cube.h"
#include "Sphere.h"
#include "Object.h"
#include "Material.h"
#include "Light.h"
#include "Cone.h"
#include "Shader.h"
#include "PBC.h"
#include "Skybox.h"
#include "BS.h"


using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
static Camera cam(Vector3(0,0,20),Vector3(0,0,0),Vector3(0,1,0));
bool swing = true;
double wholer = 0;
double scaler = 1;
bool start = false;
bool jump = false;
bool jumped = false;
bool reset = false;
bool death = false;
bool updatecam = false;
int jumpc = 0;
Vector3 lastPoint;
double clk = 0.0;
int diff = 20;
int lap = 0;
int highscore = 0;

//MatrixTransform
MatrixTransform* root = new MatrixTransform(Matrix4());
MatrixTransform* rotw;
MatrixTransform* sclw;
MatrixTransform* smove;
MatrixTransform* bunny;
MatrixTransform* sclb = new MatrixTransform(Matrix4());
MatrixTransform* rotb = new MatrixTransform(Matrix4());
MatrixTransform* movb = new MatrixTransform(Matrix4());


//light
Vector4 lightamb = Vector4(0.0,0.0,0.0,1.0);
Vector4 lightamb1 = Vector4(0.2,0.2,0.2,1.0);
Vector4 lightdif = Vector4(1.0,1.0,1.0,1.0);
Vector4 lightspec = Vector4(1.0,1.0,1.0,1.0);
Vector4 lightpos = Vector4(-10.0,10.0,-15,0.0);
Vector4 lightpos2 = Vector4(10.0,10.0,-30,0.0);
Vector4 lightpos3 = Vector4(-10.0,10.0,-45,0.0);
Vector4 lightpos4 = Vector4(10.0,10.0,-60,0.0);
Vector3 spotdir = Vector3(-10.0,5.0,0.0);
//Light sl(lightamb1,lightdif,lightspec,lightpos2,spotdir,1.1,10,1.0,0.1,0.0);//cutoff is 3 degrees, with 10 as exponent,linear att is set to 0.1
Light pl(lightamb,lightdif,lightspec,lightpos);
Light pl2(lightamb,lightdif,lightspec,lightpos2);
Light pl3(lightamb,lightdif,lightspec,lightpos3);
Light pl4(lightamb,lightdif,lightspec,lightpos4);

//material
Vector4 nomat = Vector4(0.0,0.0,0.0,1.0);
Vector4 matamb = Vector4(0.7,0.7,0.2,1.0);
Vector4 matdif = Vector4(0.1,0.5,0.8,1.0);
Vector4 matspec = Vector4(0.9,0.8,0.9,1.0);
float noshine = 0.0;
float lowshine = 10;
float shine = 50;
Vector4 matemis = Vector4(0.3,0.2,0.2,0.0);
Material bmat;
Material ymat;
Material dmat;
Material wmat;

//Bezier curve
PBC* pc;
Vector3 cp[16];

//bunny
vector <Vector3> bver, bnor, bvi, bni, bc;
Vector3 bmax, bmin;
Matrix4 bmove, bscale;
Vector3 bunpos;
Vector3 bunprev;
Vector3 bunpost;
double buncount = 0;
Vector3 la;
Vector3 face = Vector3(0,0,1);
BS bunbs;

//hazards
vector<Vector3> haz;
//Vector3 h1pos;
//Vector3 h2pos;
double hr = 1.3;
Vector3 h1pos;
Vector3 h2pos;
Vector3 h3pos;
Vector3 h4pos;
Vector3 h5pos;
Vector3 h6pos;
MatrixTransform * h1sph;
MatrixTransform * h2sph;
MatrixTransform * h3sph;
MatrixTransform * h4sph;
MatrixTransform * h5sph;
MatrixTransform * h6sph;

//shader
Shader *shader;

enum FKEY{F1, F2, F3, F4, F5};
FKEY f = F1;
enum ACTION{REST, ROTATE, ZOOM};
ACTION act = REST;

//initialize
void Window::setup() {
    //shader = new Shader("/Users/Yuuki/Desktop/HW/CSE167/L\&S/diffuse_shading.vert","/Users/Yuuki/Desktop/HW/CSE167/L\&S/diffuse_shading.frag",true);
    
    cp[0] = Vector3(0,0,0);
    cp[1] = Vector3(44,0,-10);
    cp[2] = Vector3(3,0,-20);
    cp[3] = Vector3(30,0,-30);
    cp[4] = Vector3(30,0,-30);
    cp[5] = Vector3(19,0,-80);
    cp[6] = Vector3(16,0,-30);
    cp[7] = Vector3(1,0,-60);
    cp[8] = Vector3(1,0,-60);
    cp[9] = Vector3(-7,0,-50);
    cp[10] = Vector3(-13,0,-40);
    cp[11] = Vector3(-19,0,-30);
    cp[12] = Vector3(-19,0,-30);
    cp[13] = Vector3(-11,0,-20);
    cp[14] = Vector3(-5,0,-10);
    cp[15] = Vector3(0,0,0);
    
    Matrix4 tempm;
    sclw = new MatrixTransform(Matrix4());
    rotw = new MatrixTransform(Matrix4());
    pc = new PBC(cp, 4 ,1000);
    sclw->addChild(pc);
    rotw->addChild(sclw);
    root->addChild(rotw);
    
    Skybox* sb = new Skybox(100);
    //tempm.makeTranslate(0,8,-5);
    smove = new MatrixTransform(tempm);
    sclw->addChild(smove);
    smove->addChild(sb);
    
    /*bp->setCM(sb->pass());
    
    wmat = Material(nomat, matdif, matspec, nomat, shine);
    wmat.create();*/
    pl.create();
    pl2.create();
    pl3.create();
    pl4.create();
    
    
    //bmat = Material(matamb, matdif, matspec, nomat, lowshine);
    //ymat = Material(nomat, matdif, nomat, nomat, noshine);
    //dmat = Material(nomat, matdif, matspec, nomat, shine);
    
    bunprev = pc->getPoint(buncount);
    buncount++;
    bunpos = pc->getPoint(buncount);
    buncount++;
    bunpost = bunpos;
    
    h1pos = pc->getPoint(100);
    h1pos.setY(h1pos.getY()+1);
    tempm.makeTranslate(h1pos.getX(),h1pos.getY(),h1pos.getZ());
    h1sph = new MatrixTransform(tempm);
    haz.push_back(h1pos);
    
    h2pos = pc->getPoint(50);
    h2pos.setY(h2pos.getY()+1);
    tempm.makeTranslate(h2pos.getX(),h2pos.getY(),h2pos.getZ());
    h2sph = new MatrixTransform(tempm);
    haz.push_back(h2pos);
    
    h3pos = pc->getPoint(800);
    h3pos.setY(h3pos.getY()+1);
    tempm.makeTranslate(h3pos.getX(),h3pos.getY(),h3pos.getZ());
    h3sph = new MatrixTransform(tempm);
    haz.push_back(h3pos);
    
    Vector3 h4pos = pc->getPoint(1400);
    h4pos.setY(h4pos.getY()+1);
    tempm.makeTranslate(h4pos.getX(),h4pos.getY(),h4pos.getZ());
    h4sph = new MatrixTransform(tempm);
    haz.push_back(h4pos);
    
    h5pos = pc->getPoint(2300);
    h5pos.setY(h5pos.getY()+1);
    tempm.makeTranslate(h5pos.getX(),h5pos.getY(),h5pos.getZ());
    h5sph = new MatrixTransform(tempm);
    haz.push_back(h5pos);
    
    Vector3 h6pos = pc->getPoint(3300);
    h6pos.setY(h6pos.getY()+1);
    tempm.makeTranslate(h6pos.getX(),h6pos.getY(),h6pos.getZ());
    h6sph = new MatrixTransform(tempm);
    haz.push_back(h6pos);
    
    bmove.makeTranslate( -(bmax.getX() + bmin.getX()) / 2, -(bmax.getY() + bmin.getY() * 2), -(bmax.getZ() + bmin.getZ()) / 2);
    double xdif = bmax.getX() - bmin.getX();
    double ydif = bmax.getY() - bmin.getY();
    double temp = xdif > ydif ? xdif : ydif;
    double wmax = 36 * tan(M_PI / 6);
    double scalef = wmax / (4 * temp);
    bscale.makeScale(scalef,scalef,scalef);
    bunny = new MatrixTransform(bscale * bmove);
    //tempm.makeRotateY(180);
    //rotb->change(tempm * rotb->getM());
    sclw->addChild(movb);
    movb->addChild(rotb);
    rotb->addChild(sclb);
    sclb->addChild(bunny);
    bunny->addChild(new Object(&bver, &bnor, &bvi, &bni, &bc, bmax, bmin));
    
    sclw->addChild(h1sph);
    h1sph->addChild(new Sphere(hr,10,10,"solid",1.0,1.0,1.0));
    sclw->addChild(h2sph);
    h2sph->addChild(new Sphere(hr,10,10,"solid",1.0,1.0,1.0));
    sclw->addChild(h3sph);
    h3sph->addChild(new Sphere(hr,10,10,"solid",1.0,1.0,1.0));
    sclw->addChild(h4sph);
    h4sph->addChild(new Sphere(hr,10,10,"solid",1.0,1.0,1.0));
    sclw->addChild(h5sph);
    h5sph->addChild(new Sphere(hr,10,10,"solid",1.0,1.0,1.0));
    sclw->addChild(h6sph);
    h6sph->addChild(new Sphere(hr,10,10,"solid",1.0,1.0,1.0));
    
    bunbs.setCenter(bunpos);
    bunbs.setRadius((bmax.getX() - bmin.getX())/2);
}

void Window::camthing() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
    gluLookAt(bunprev.getX(),bunprev.getY()+3,bunprev.getZ(),bunpos.getX(),bunpos.getY(),bunpos.getZ(),0,1,0);
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
    /*bp->wave(2.0,clk);
    clk += 0.01;
    if (clk > numeric_limits<double>::max())
        clk = 0;*/
  displayCallback();         // call display routine to show the cube
    //calculateTimu();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
    //camthing();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  gluLookAt(5,15,40,0,0,-30,0,1,0);
  //glTranslatef(-5, -15, -40);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
    //camthing();
  glMatrixMode(GL_MODELVIEW);
  //glLoadMatrixd(cam.getMatrix().getPointer());
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //shader->bind();
    Matrix4 id = Matrix4();
    Matrix4 tempm;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(start&&!death) {
        bunpost = pc->getPoint(buncount);
        
        bunbs.setCenter(bunpos);

        Matrix4 bunmove;
        if(jump) {
            if(!jumped) {
                bunmove.makeTranslate(bunpos.getX() - bunprev.getX(),10,bunpos.getZ() - bunprev.getZ());
                movb->change(bunmove * movb->getM());
                jumped = true;
            } else if(jumpc == 10-diff/10) {
                bunmove.makeTranslate(bunpos.getX() - bunprev.getX(),-10,bunpos.getZ() - bunprev.getZ());
                movb->change(bunmove * movb->getM());
            } else {
                bunmove.makeTranslate(bunpos.getX() - bunprev.getX(),(bunpos.getY() - bunprev.getY()),bunpos.getZ() - bunprev.getZ());
                movb->change(bunmove * movb->getM());
            }
            bunbs.setCenter(Vector3(bunpos.getX(),bunpos.getY()+10,bunpos.getZ()));
            jumpc++;
            if(jumpc > 15-diff/10) {
                jump = false;
                jumped = false;
                jumpc = 0;
            }
        } else {
            bunmove.makeTranslate(bunpos.getX() - bunprev.getX(),(bunpos.getY() - bunprev.getY()),bunpos.getZ() - bunprev.getZ());
            movb->change(bunmove * movb->getM());
        }
        
        //bunbs.setCenter(bunpos);
        //cout<< (bunbs.getCenter()-h1pos).length() << " " << bunbs.getRadius()+hr << endl;
        for(int i = 0; i < haz.size(); i++) {
            if((bunbs.getCenter()-haz[i]).length() < (bunbs.getRadius()+hr)) {
                tempm.makeRotateX(180);
                rotb->change(tempm * rotb->getM());
                death = true;
                if(lap > highscore)
                    highscore = lap;
                cout<< "SCORE: " << lap << "   HIGHSCORE: " << highscore << "!!!!!" << endl;
                lap = 0;
            }
        }
    
        bunprev = bunpos;
        bunpos = bunpost;
    
    
        if(buncount < 3999-diff)
            buncount+=diff;
        else {
            buncount = 0;
            lap++;
        }
        
        updatecam = true;
        
    }
    
    if(reset) {
        Matrix4 bunmove;
        bunmove.makeTranslate(-bunprev.getX(),0,-bunprev.getZ());
        movb->change(bunmove * movb->getM());
        buncount = 0;
        bunprev = pc->getPoint(buncount);
        buncount++;
        bunpos = pc->getPoint(buncount);
        buncount++;
        reset = false;
        if(death) {
            death = false;
            tempm.makeRotateX(180);
            rotb->change(tempm * rotb->getM());
            start = false;
        }
        updatecam = true;
        lap = 0;
        while(!haz.empty()) {
            haz.pop_back();
        }
        sclw->removeChild(h1sph);
        sclw->removeChild(h2sph);
        sclw->removeChild(h3sph);
        sclw->removeChild(h4sph);
        sclw->removeChild(h5sph);
        sclw->removeChild(h6sph);
        double x = rand()% 800 + 300;
        h1pos = pc->getPoint(x);
        h1pos.setY(h1pos.getY()+1);
        haz.push_back(h1pos);
        tempm.makeTranslate(h1pos.getX(),h1pos.getY(),h1pos.getZ());
        h1sph = new MatrixTransform(tempm);
        x = rand()% 800 + 1300;
        h2pos = pc->getPoint(x);
        h2pos.setY(h2pos.getY()+1);
        haz.push_back(h2pos);
        tempm.makeTranslate(h2pos.getX(),h2pos.getY(),h2pos.getZ());
        h2sph = new MatrixTransform(tempm);
        x = rand()% 500 + 2300;
        h3pos = pc->getPoint(x);
        h3pos.setY(h3pos.getY()+1);
        haz.push_back(h3pos);
        tempm.makeTranslate(h3pos.getX(),h3pos.getY(),h3pos.getZ());
        h3sph = new MatrixTransform(tempm);
        x = rand()% 1000 + 2900;
        h4pos = pc->getPoint(x);
        h4pos.setY(h4pos.getY()+1);
        haz.push_back(h4pos);
        tempm.makeTranslate(h4pos.getX(),h4pos.getY(),h4pos.getZ());
        h4sph = new MatrixTransform(tempm);
        x = rand()% 50 + 50;
        h5pos = pc->getPoint(x);
        h5pos.setY(h5pos.getY()+1);
        haz.push_back(h5pos);
        tempm.makeTranslate(h5pos.getX(),h5pos.getY(),h5pos.getZ());
        h5sph = new MatrixTransform(tempm);
        x = rand()% 50 + 1200;
        h6pos = pc->getPoint(x);
        h6pos.setY(h6pos.getY()+1);
        haz.push_back(h6pos);
        tempm.makeTranslate(h6pos.getX(),h6pos.getY(),h6pos.getZ());
        h6sph = new MatrixTransform(tempm);
        sclw->addChild(h1sph);
        sclw->addChild(h2sph);
        sclw->addChild(h3sph);
        sclw->addChild(h4sph);
        sclw->addChild(h5sph);
        sclw->addChild(h6sph);
        
    }
    if(updatecam) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
        if(reset) {
            gluLookAt(5,15,40,0,0,0,0,1,0);
        } else {
            gluLookAt(5,15,40,bunpos.getX(),bunpos.getY(),bunpos.getZ(),0,1,0);
        }
        updatecam = false;
    }

    glMatrixMode(GL_MODELVIEW);
    
    root->draw(id);
    
  glFlush();  
  glutSwapBuffers();
}

void Window::parseFile() {
    Parser::parseObj("/Users/Yuuki/Desktop/HW/CSE167/FPA/bunny.obj",bver,bnor,bvi,bni,bc,bmax,bmin,true);
}

void Window::processNormalKeys(unsigned char k, int x, int y) {
    Matrix4 temp = Matrix4();
	switch (k) {
        case 'p':
            if(!death)
                start = !start;
            break;
        case 'j':
            if(!jump&&!death)
                jump = true;
            break;
        case '1':
            diff = 1;
            break;
        case '2':
            diff = 10;
            break;
        case '3':
            diff = 20;
            break;
        case '4':
            diff = 40;
            break;
        case '5':
            diff = 60;
            break;
        case '6':
            diff = 90;
            break;
        case 'r':
            reset = true;
            break;
	}
}

void Window::processSpecialKeys(int k, int x, int y) {

}

void Window::onMouseMove(int x, int y) {
    Vector3 currPoint;
    Vector3 dir;
    double pixel_diff;
    double rot_angle, zoom_factor;
    currPoint = trackBallMapping(x,y);
    switch(act) {
        case ROTATE: {
            //currPoint = trackBallMapping(x,y);
            dir = currPoint - lastPoint;
            double velocity = dir.length();
            if(velocity > 0.0001) {
                Vector3 rotAxis = lastPoint.cross(currPoint);
                //Vector3 rotAxis = currPoint.cross(lastPoint);
                rotAxis.normalize();
                rot_angle = velocity * 90; //m_ROTATE found on piazza
                Matrix4 rot;
                rot.makeRotate(rot_angle,rotAxis);
                rotw->change(rot * rotw->getM());
            }
            displayCallback(); }
            break;
        case ZOOM: {
            //Vector3 curr(x,y,0);
            pixel_diff = currPoint.getY() - lastPoint.getY();
            zoom_factor = 1.0 + pixel_diff * 1; //m_ZOOMSCALE found on piazza
            Matrix4 scale;
            scale.makeScale(zoom_factor,zoom_factor,zoom_factor);
            sclw->change(scale * sclw->getM());
            displayCallback(); } 
            break;
        case REST:
            break;
    }
    lastPoint = currPoint;
}

void Window::onButtonDown(int lr, int stt, int x, int y) {
    if(lr == GLUT_LEFT_BUTTON && stt == GLUT_DOWN) {
        act = ROTATE;
        lastPoint = trackBallMapping(x,y);
    } else if(lr == GLUT_RIGHT_BUTTON && stt == GLUT_DOWN) {
        act = ZOOM;
        lastPoint = trackBallMapping(x,y);
    } else
        act = REST;
}

Vector3 Window::trackBallMapping(int x, int y) {
    Vector3 v = Vector3();
    double d;
    v.setX(double(2*x - width) / double(width));
    v.setY(double(height - 2*y) / double(height));
    v.setZ(0);
    d = v.length();
    d = d < 1.0 ? d : 1.0;
    v.setZ(sqrt(1.001 - d*d));
    v.normalize();
    return v;
}

void Window::calculateTimu() {
    clock_t start = clock();
    
    displayCallback();
    
    clock_t end = clock();
    double sec = double(end-start) / CLOCKS_PER_SEC;
    cout << "fps: " << (1.0)/sec << endl;
    
}