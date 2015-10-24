#include "PBC.h"
#include "math.h"


PBC::PBC(Vector3 *arr, int numo, int len) {
    num = numo;
    set = new BC*[num];
    for(int i = 0; i < 4; i++)
        for(int h = 0; h < 4; h++) {
            ctrl[i][h] = arr[4*i+h];
        }
    
    
    for(int j = 0; j < num; j++) {
        set[j] = new BC(ctrl[j],len);
    }
}

void PBC::update() { }

void PBC::render() {
    for(int i = 0; i < num; i++)
        set[i]->render();
}

Vector3 PBC::getPoint(double i) {
    return set[int(floor(i/1000))]->getPoint(int(i)%1000);
}
