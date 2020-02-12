#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "object.h"
#include "layer.h"
#include "drawtool.h"
#include "fonts.h"

void show_progress(int now, int all){
    int percent = (int)round(100*now/(double)all);
    printf("\rNow printing...[");
    for(int i=1; i<=10; i++){
        printf(i*10<percent ? "#" : " ");
    }
    printf("] %2d%% done (%3d/%d)",(int)(100*now/(double)all),now,all);
    fflush(stdout);
}

struct color temp_cursor[HEIGHT][WIDTH];
void build_circle_cursor(struct color cursor[HEIGHT][WIDTH]){
    for(int i=0; i<3; i++){
        clear_layer(temp_cursor);
        draw_cursor(100,70-i*12,temp_cursor);
        if(i%2==1){
            rotate_layer(temp_cursor,5,100,140);
        }
        unite_layer(cursor,temp_cursor);
    }
}

int main(void){
    struct color background[HEIGHT][WIDTH];
    struct color background_cookie[HEIGHT][WIDTH];
    struct color cookie[HEIGHT][WIDTH];
    struct color pop_up[HEIGHT][WIDTH];

    struct color cursor[HEIGHT][WIDTH];
    build_circle_cursor(cursor);

    draw_background(background);

    bake_cookie(cookie);
    initialize_funcarray();
    struct color figure[HEIGHT][WIDTH];
    int output_files = 250;
    printf("Now printing... 00%%done");
    for(int t=0; t<output_files; t++){
        show_progress(t,output_files);

        img_clear();

        bake_background_cookie(background_cookie, t);
        draw_pop_up(pop_up,t);
        merge_layer(background);
        merge_layer(background_cookie);
        draw_glow_circle();
        draw_shine(3*t,4);
        draw_shine(3*t+30,4);

        copy_layer(temp_cursor,cursor);
        rotate_layer(temp_cursor,-0.5*(t%20),100,140);
        struct color invisible = {0,0,0,0.0};
        for(int i=250; i<=300; i++){
            for(int j=0; j<WIDTH; j++){
                temp_cursor[i][j] = invisible;
            }
        }
        merge_layer(temp_cursor);

        int h = 0;
        if(50<t) h = t<150 ? t-50 : 100;
        pour_milk(t,0.7*h);
        merge_layer(cookie);
        pour_milk(t+15,0.7*h);

        merge_layer(pop_up);
        draw_cookieband();
        print_number(623456789000+98765321l*t,figure);
        print_cookies(figure);
        merge_layer(figure);
        img_write();
    }
    printf("\rNow printing...[##########]100%% done! (%d/%d)\n",output_files,output_files);
    printf("Output successfully completed!\n");
    return 0;
}