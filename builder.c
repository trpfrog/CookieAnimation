#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "object.h"
#include "layer.h"
#include "drawtool.h"

int main(void){
    struct color background[HEIGHT][WIDTH];
    struct color background_cookie[HEIGHT][WIDTH];
    struct color cookie[HEIGHT][WIDTH];
    struct color cookieband[HEIGHT][WIDTH];

    draw_background(background);
    draw_cookieband(cookieband);
    bake_cookie(cookie);

    for(int t=0; t<1; t++){
        img_clear();
        bake_background_cookie(background_cookie, t);
        merge_layer(background);
        //merge_layer(background_cookie);
        draw_glow_circle();
        draw_shine(3*t,4);
        draw_shine(3*t+30,4);
        merge_layer(cookieband);
        merge_layer(cookie);
        pour_milk(t);
        pour_milk(t+4);
        img_write();
    }
    return 0;
}