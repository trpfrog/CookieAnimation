#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "object.h"
#include "layer.h"
#include "drawtool.h"
#include "fonts.h"

int main(void){
    struct color background[HEIGHT][WIDTH];
    struct color background_cookie[HEIGHT][WIDTH];
    struct color cookie[HEIGHT][WIDTH];
    struct color pop_up[HEIGHT][WIDTH];
    draw_background(background);
    bake_cookie(cookie);
    initialize_funcarray();

    for(int t=0; t<150; t++){
        img_clear();
        bake_background_cookie(background_cookie, t);
        draw_pop_up(pop_up,t);
        merge_layer(background);
        merge_layer(background_cookie);
        draw_glow_circle();
        draw_shine(3*t,4);
        draw_shine(3*t+30,4);
        draw_cookieband();
        merge_layer(cookie);
        pour_milk(t);
        pour_milk(t+4);
        draw_cursor(100, 70);
        merge_layer(pop_up);
        print_number(623456789000+98765321l*t,figure);
        print_cookies(figure);
        merge_layer(figure);
        img_write();
    }
    return 0;
}