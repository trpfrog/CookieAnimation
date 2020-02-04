#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "object.h"

void draw_background(void){
    //頼んだ つまみより
}

void bake_cookie(void){

}

void bake_background_cookie(void){

}

//template_function
void img_fillcircle(struct color c, int x, int y, double r) {
    int imin = x - r - 1, imax = x + r + 1;
    int jmin = y - r - 1, jmax = y + r + 1;
    int i, j;
    for(j = jmin; j <= jmax; ++j) {
        for(i = imin; i <= imax; ++i) {
            if((x-i)*(x-i) + (y-j)*(y-j) <= r*r) put_pixel(c, i, j, 1.0);
        }
    }
}
