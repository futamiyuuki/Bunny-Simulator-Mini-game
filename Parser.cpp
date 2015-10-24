#include "Parser.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include "Matrix4.h"
#include "window.h"

using namespace std;

void Parser::parseObj(char* name, vector<Vector3> &vertex, vector<Vector3> &normal, vector<Vector3> &vi, vector<Vector3> &ni, vector<Vector3> &color, Vector3 &max, Vector3 &min, bool bunny) {
    FILE *fp;
    float r, g, b;
    r = g = b = 1.0;
    int c1,c2;
    
    fp = fopen(name,"rb");
    if(fp == NULL) { cerr << "error loading file" << endl; exit(-1); }
    max.setX(numeric_limits<double>::min());
    max.setY(numeric_limits<double>::min());
    max.setZ(numeric_limits<double>::min());
    min.setX(numeric_limits<double>::max());
    min.setY(numeric_limits<double>::max());
    min.setZ(numeric_limits<double>::max());
    
    int lineLen = 128; //number of characters in a line
    char line[lineLen];
    while(fgets(line, lineLen, fp)) {
        char c1 = line[0];
        char c2 = line[1];
        
        if(c1 == 'v' && c2 == ' ') {
            float x, y, z;
            Vector3 temp;
            Vector3 rgb((double)r,(double)g,(double)b);
            //fscanf(file, "%f %f %f", &x, &y, &z);
            //sscanf(line, "v %f %f %f", &x, &y, &z);
            if(bunny) {
                sscanf(line, "v %f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);
                temp.create((double)x, (double)y, (double)z);
                rgb.create((double)r,(double)g,(double)b);
                //cout<<"hiiiiiiiiii"<<endl;
            } else {
                sscanf(line, "v %f %f %f\n", &x, &y, &z);
                temp.create((double)x, (double)y, (double)z);
            }
            /*if(n > xmax)
                xmax = n;
            if(n < xmin)
                xmin = n;
            vertex.push_back(n);
            s >> n;
            if(n > ymax)
                ymax = n;
            if(n < ymin)
                ymin = n;
            vertex.push_back(n);
            s >> n;
            if(n > zmax)
                zmax = n;
            if(n < zmin)
                zmin = n;
            vertex.push_back(n); */
            
            if(temp.getX() > max.getX())
                max.setX(temp.getX());
            if(temp.getX() < min.getX())
                min.setX(temp.getX());
            if(temp.getY() > max.getY())
                max.setY(temp.getY());
            if(temp.getY() < min.getY())
                min.setY(temp.getY());
            if(temp.getZ() > max.getZ())
                max.setZ(temp.getZ());
            if(temp.getZ() < min.getZ())
                min.setZ(temp.getZ());
            
            vertex.push_back(temp);
            color.push_back(rgb);
            
        } else if(c1 == 'v' && c2 == 'n') {
            float x, y, z;
            sscanf(line, "vn %f %f %f\n", &x, &y, &z);
            Vector3 temp((double)x, (double)y, (double)z);
            temp.normalize();
            normal.push_back(temp);
            
        } else if(c1 == 'f' && c2 == ' ') {
            int vx, vy, vz, nx, ny, nz;
            sscanf(line, "f %d//%d %d//%d %d//%d\n", &vx, &nx, &vy, &ny, &vz, &nz);
            Vector3 tempV((double)vx,(double)vy,(double)vz);
            Vector3 tempN((double)nx,(double)ny,(double)nz);
            vi.push_back(tempV);
            ni.push_back(tempN);
        } else
            continue; //case for #
    }
    fclose(fp);
}