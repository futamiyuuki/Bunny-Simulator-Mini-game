#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Vector3.h"
#include "Group.h"
#include "Node.h"
#include "MatrixTransform.h"
#include <vector>

class Window	  // OpenGL output window related routines
{
private:
    static MatrixTransform* rootb;
    static MatrixTransform* rooty;
    static MatrixTransform* rootd;
  public:
    static int width, height; 	            // window size

    static void setup();
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	
    static void parseFile();
    
	static void processNormalKeys(unsigned char, int, int);
    static void processSpecialKeys(int, int, int);
    static void onButtonDown(int, int, int, int);
    static void onMouseMove(int, int);
    static void calculateTimu();
    
    static Vector3 trackBallMapping(int, int);
    static string getState();
    static void camthing();
};

#endif

