#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "object.h"
#include "layer.h"

int main(void){
    int background[HEIGHT][WIDTH][3];
    int cookie[HEIGHT][WIDTH][3];
    int cookieband[HEIGHT][WIDTH][3];
    draw_background(background);
    draw_cookieband(cookieband);
    bake_cookie(cookie);
    for(int i=0; i<1; i++){
        img_clear();
        merge_layer(background,1.0);
        merge_layer(cookieband,0.5);
        merge_layer(cookie,1.0);
        img_write();
    }
    return 0;
}