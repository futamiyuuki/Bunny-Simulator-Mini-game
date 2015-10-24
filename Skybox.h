#ifndef __PA6__Skybox__
#define __PA6__Skybox__

#include <stdio.h>
#include "Geode.h"
#include "Shader.h"

class Skybox : public Geode {
private:
    double len;
    double lent = 16;
    int c = 0;
    GLuint texture[6];
    GLuint cm;
    GLuint SkyBoxVBO;
    Shader *shader;
    unsigned char* loadPPM(const char* filename, int& width, int& height);
public:
    Skybox(double);
    void update();
    void render();
    bool load_cube_map_side(GLuint tex, GLenum side_target, const char* fn);
    GLuint pass();
    
};

#endif /* defined(__PA6__Skybox__) */
