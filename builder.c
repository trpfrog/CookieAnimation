#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "object.h"

int main(void){
    int background[HEIGHT][WIDTH][3];
    int cookie[HEIGHT][WIDTH][3];
    draw_background(&background);
    bake_cookie(&cookie);
    for(int i=0; i<1; i++){
        img_clear();
        merge_layer(background);
        //do something
        merge_layer(cookie);
        img_write();
    }
    return 0;
}