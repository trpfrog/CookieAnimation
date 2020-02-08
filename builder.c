#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "object.h"
#include "layer.h"

int main(void){
    struct color background[HEIGHT][WIDTH];
    struct color background_cookie[HEIGHT][WIDTH];
    struct color cookie[HEIGHT][WIDTH];
    struct color cookieband[HEIGHT][WIDTH];
    draw_background(background);
    draw_cookieband(cookieband);
    bake_cookie(cookie);
    for(int i=0; i<1; i++){
        img_clear();
        bake_background_cookie(background_cookie, i);
        merge_layer(background);
        merge_layer(background_cookie);
        merge_layer(cookieband);
        merge_layer(cookie);
        pour_milk(i);
        pour_milk(i+4);
        img_write();
    }
    return 0;
}