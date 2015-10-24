#include "Skybox.h"
#include "stdlib.h"
#include "stdio.h"
#include "stb_image.h"
#include <GLUT/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

Skybox::Skybox(double length) {
    len = length;
    
    float SkyBoxVertices[] =
    {	// x, y, z, x, y, z, x, y, z, x, y, z
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f
    };
    glGenBuffers(1, &SkyBoxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, SkyBoxVBO);
    glBufferData(GL_ARRAY_BUFFER, 288, SkyBoxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &cm);
    glGenTextures(6,&texture[0]);
    
    // load each image and copy into a side of the cube-map texture
    if (!load_cube_map_side(cm, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "/Users/Yuuki/Desktop/HW/CSE167/FPA/star.jpg"))
        cerr << "fail to load" << endl;
    if (!load_cube_map_side(cm, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "/Users/Yuuki/Desktop/HW/CSE167/FPA/star.jpg"))
        cerr << "fail to load" << endl;
    if(!load_cube_map_side(cm, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "/Users/Yuuki/Desktop/HW/CSE167/FPA/star.jpg"))
       cerr << "fail to load" << endl;
    if(!load_cube_map_side(cm, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "/Users/Yuuki/Desktop/HW/CSE167/FPA/star.jpg"))
        cerr << "fail to load" << endl;
    if(!load_cube_map_side(cm, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "/Users/Yuuki/Desktop/HW/CSE167/FPA/star.jpg"))
       cerr << "fail to load" << endl;
    if(!load_cube_map_side(cm, GL_TEXTURE_CUBE_MAP_POSITIVE_X, "/Users/Yuuki/Desktop/HW/CSE167/FPA/star.jpg"))
        cerr << "fail to load" << endl;
    // format cube map texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    
    shader = new Shader("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/cm.vert","/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/cm.frag");
}

bool Skybox::load_cube_map_side(GLuint tex, GLenum side_target, const char* fn) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
    
    int x, y, n;
    int force_channels = 4;
    unsigned char*  image_data = stbi_load(fn, &x, &y, &n, force_channels);
    if (!image_data) {
        fprintf(stderr, "ERROR: could not load %s\n", fn);
        return false;
    }
    // non-power-of-2 dimensions check
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
        fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n", fn);
    }
    
    // copy image data into 'target' side of cube map
    glTexImage2D(side_target,
                 0,
                 GL_RGBA,
                 x,
                 y,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image_data
                 );
    free(image_data);
    return true;
}



void Skybox::update() { }

unsigned char* Skybox::loadPPM(const char* filename, int& width, int& height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    if ( (fp=fopen(filename, "rb")) == NULL)
    {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }
    
    // Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
    // Read width and height:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    // Read maxval:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    
    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    if (read != 1)
    {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    
    return rawData;
}

GLuint Skybox::pass() {
    return cm;
}

void Skybox::render() {
    /*glEnable(GL_TEXTURE_2D);
    
    int twidth0, twidth1, twidth2, twidth3, twidth4;
    int theight0, theight1, theight2, theight3, theight4;
    unsigned char *tdata0, *tdata1, *tdata2, *tdata3, *tdata4;
    
    tdata0 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/front.ppm",twidth0,theight0);
    tdata1 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/back.ppm",twidth1,theight1);
    tdata2 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/left.ppm",twidth2,theight2);
    tdata3 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/right.ppm",twidth3,theight3);
    tdata4 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/top.ppm",twidth4,theight4);
    
    glGenTextures(6,&texture[0]);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth0, theight0, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata0);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth1, theight1, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata1);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth2, theight2, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata2);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth3, theight3, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata3);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth4, theight4, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata4);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glDisable(GL_LIGHTING);
    glColor3f(1,1,1);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth0, theight0, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(len,-len,-len);
    glTexCoord2f(1,1);
    glVertex3f(-len,-len,-len);
    glTexCoord2f(1,0);
    glVertex3f(-len,len,-len);
    glTexCoord2f(0,0);
    glVertex3f(len,len,-len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth1, theight1, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(-len,-len,len);
    glTexCoord2f(1,1);
    glVertex3f(len,-len,len);
    glTexCoord2f(1,0);
    glVertex3f(len,len,len);
    glTexCoord2f(0,0);
    glVertex3f(-len,len,len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth3, theight3, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata3);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(-len,-len,-len);
    glTexCoord2f(1,1);
    glVertex3f(-len,-len,len);
    glTexCoord2f(1,0);
    glVertex3f(-len,len,len);
    glTexCoord2f(0,0);
    glVertex3f(-len,len,-len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth2, theight2, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata2);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(len,-len,len);
    glTexCoord2f(1,1);
    glVertex3f(len,-len,-len);
    glTexCoord2f(1,0);
    glVertex3f(len,len,-len);
    glTexCoord2f(0,0);
    glVertex3f(len,len,len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth4, theight4, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata4);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(len,len,-len);
    glTexCoord2f(1,1);
    glVertex3f(-len,len,-len);
    glTexCoord2f(1,0);
    glVertex3f(-len,len,len);
    glTexCoord2f(0,0);
    glVertex3f(len,len,len);
    glEnd();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    
    delete tdata0;
    delete tdata1;
    delete tdata2;
    delete tdata3;
    delete tdata4; */
    
    
    
    glEnable(GL_TEXTURE_CUBE_MAP);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cm);
    shader->bind();
    glBegin(GL_QUADS);
    /*glVertex3f(len, -len, len);
    glVertex3f(-len, -len, len);
    glVertex3f(-len, len, len);
    glVertex3f(len, len, len);
    
    glVertex3f(len, -len, -len);
    glVertex3f(len, -len, len);
    glVertex3f(len, len, len);
    glVertex3f(len, len, -len);
    
    glVertex3f(-len, -len, len);
    glVertex3f(-len, -len, -len);
    glVertex3f(-len, lent, -len);
    glVertex3f(-len, lent, len);
    
    glVertex3f(len, -len, len);
    glVertex3f(-len, -len, len);
    glVertex3f(-len, len, len);
    glVertex3f(len, len, len);
    
    glVertex3f(-len, -len, -len);
    glVertex3f(len, -len, -len);
    glVertex3f(len, len, -len);
    glVertex3f(-len, len, -len);
    
    glVertex3f(-len, len, -len);
    glVertex3f(len, len, -len);
    glVertex3f(len, len, len);
    glVertex3f(-len, len, len);*/
    
    glVertex3f(len,-len,-len);
    glVertex3f(-len,-len,-len);
    glVertex3f(-len,len,-len);
    glVertex3f(len,len,-len);

    glVertex3f(-len,-len,len);
    glVertex3f(len,-len,len);
    glVertex3f(len,len,len);
    glVertex3f(-len,len,len);
    
    glVertex3f(-len,-len,-len);
    glVertex3f(-len,-len,len);
    glVertex3f(-len,len,len);
    glVertex3f(-len,len,-len);

    glVertex3f(len,-len,-len);
    glVertex3f(len,-len,len);
    glVertex3f(len,len,len);
    glVertex3f(len,len,-len);
    
    //glTexCoord2f(0,1);
    glVertex3f(len,len,-len);
    //glTexCoord2f(1,1);
    glVertex3f(-len,len,-len);
    //glTexCoord2f(1,0);
    glVertex3f(-len,len,len);
    //glTexCoord2f(0,0);
    glVertex3f(len,len,len);
    
    glVertex3f(len,-len,len);
    glVertex3f(len,-len,-len);
    glVertex3f(-len,-len,-len);
    glVertex3f(-len,-len,len);

    glEnd();
    shader->unbind();
    glDisable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
}

/*void Skybox::render() {
    glEnable(GL_TEXTURE_2D);
    
    //GLuint texture[6];
    int twidth0, twidth1, twidth2, twidth3, twidth4;
    int theight0, theight1, theight2, theight3, theight4;
    unsigned char *tdata0, *tdata1, *tdata2, *tdata3, *tdata4;
    
    tdata0 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/front.ppm",twidth0,theight0);
    tdata1 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/back.ppm",twidth1,theight1);
    tdata2 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/left.ppm",twidth2,theight2);
    tdata3 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/right.ppm",twidth3,theight3);
    tdata4 = loadPPM("/Users/Yuuki/Desktop/HW/CSE167/Simple\ Water/top.ppm",twidth4,theight4);
    
    glGenTextures(6,&texture[0]);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth0, theight0, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata0);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth1, theight1, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata1);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth2, theight2, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata2);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth3, theight3, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata3);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth4, theight4, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata4);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glDisable(GL_LIGHTING);
    glColor3f(1,1,1);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth0, theight0, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(len,-len,-len);
    glTexCoord2f(1,1);
    glVertex3f(-len,-len,-len);
    glTexCoord2f(1,0);
    glVertex3f(-len,len,-len);
    glTexCoord2f(0,0);
    glVertex3f(len,len,-len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth1, theight1, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(-len,-len,len);
    glTexCoord2f(1,1);
    glVertex3f(len,-len,len);
    glTexCoord2f(1,0);
    glVertex3f(len,len,len);
    glTexCoord2f(0,0);
    glVertex3f(-len,len,len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth3, theight3, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata3);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(-len,-len,-len);
    glTexCoord2f(1,1);
    glVertex3f(-len,-len,len);
    glTexCoord2f(1,0);
    glVertex3f(-len,len,len);
    glTexCoord2f(0,0);
    glVertex3f(-len,len,-len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth2, theight2, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata2);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(len,-len,len);
    glTexCoord2f(1,1);
    glVertex3f(len,-len,-len);
    glTexCoord2f(1,0);
    glVertex3f(len,len,-len);
    glTexCoord2f(0,0);
    glVertex3f(len,len,len);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth4, theight4, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata4);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(len,len,-len);
    glTexCoord2f(1,1);
    glVertex3f(-len,len,-len);
    glTexCoord2f(1,0);
    glVertex3f(-len,len,len);
    glTexCoord2f(0,0);
    glVertex3f(len,len,len);
    glEnd();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    
    delete tdata0;
    delete tdata1;
    delete tdata2;
    delete tdata3;
    delete tdata4;
}*/