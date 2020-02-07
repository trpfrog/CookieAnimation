#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "object.h"
#include "layer.h"

void draw_background(struct color layer[HEIGHT][WIDTH]){
    //仮
    struct color base_color = {15,100,160,1.0};
    for (int i = 0; i < HEIGHT; i++){
        for(int j = 0; j<WIDTH; j++){
            layer[i][j] = base_color;
        }
    }
    /*
    struct color base_color = {15,100,160,1.0};
    struct color base_color2 = {30,144,255,1.0};
    for (double i = 0; i < 20; i++){
        if((int)i%2 == 0){
            img_fillrect(base_color2,(double)i*10, 150, 10, 300,layer);
        }else if((int)i%2 == 1){
            img_fillrect(base_color,(double)i*10, 150, 10, 300,layer);
        }
    }
    */
}

void draw_cookieband(struct color layer[HEIGHT][WIDTH]){
    clear_layer(layer);
    struct color c = {0,0,0,0.5};
    for(int i=230; i<=270; i++){
        for(int j=0; j<WIDTH; j++){
            layer[i][j] = c;
        }
    }
}

void bake_cookie(struct color layer[HEIGHT][WIDTH]){
    clear_layer(layer);
    int center_x = 100;
    int center_y = 140;
    struct color shadow = {0x60, 0x38, 0x23, 1.0};
    struct color light = {0xad, 0x8b, 0x60, 0.0};
    struct color c;
    //img_fillcircle(shadow,center_x,center_y,60,layer);

    for(int r = 60; r > 0; r--){
        light.a = sqrt(3600-r*r)/60.0;
        c = mix_color(light,shadow);
        c.a = 1.0;
        img_fillcircle(c,center_x,center_y,r,layer);
    }

    int x1[] = {80, 95, 105,102,90, 85, 75 };
    int y1[] = {160,165,150,145,135,135,145};
    struct color chocochip[HEIGHT][WIDTH];
    struct color choco_color = {0x5c,0x34,0x21,1.0};
    clear_layer(chocochip);
    fill_polygon(x1,y1,7,choco_color,chocochip);
    struct color temp[HEIGHT][WIDTH];
    merge_layer(chocochip);
    img_write();
    unite_layer(layer,chocochip,temp);
    merge_layer(temp);
    img_write();
    clear_layer(layer);
    copy_layer(layer,temp);
}

void bake_background_cookie(void);

//template_function
void img_fillcircle(struct color c, int x, int y, double r, struct color layer[HEIGHT][WIDTH]) {
    int imin = x - r - 1, imax = x + r + 1;
    int jmin = y - r - 1, jmax = y + r + 1;
    int i, j;
    for(j = jmin; j <= jmax; ++j) {
        for(i = imin; i <= imax; ++i) {
            if((x-i)*(x-i) + (y-j)*(y-j) <= r*r){
                layer[j][i] = mix_color(c,layer[j][i]);
            }
        }
    }
}

//template_function
void img_fillrect(struct color c, double x, double y, double w, double h, struct color layer[HEIGHT][WIDTH]){
    int imin = (int)(x - w / 2), imax = (int)(x + w / 2);
    int jmin = (int)(y - h / 2), jmax = (int)(y + h / 2);
    int i, j;
    for (j = jmin; j <= jmax; ++j){
        for (i = imin; i <= imax; ++i){
            layer[j][i] = mix_color(c,layer[j][i]);
        }
    }
}

void fill_polygon(int x[], int y[], int dots, struct color c, struct color layer[HEIGHT][WIDTH]){
    int x_max = 0; int x_min = WIDTH-1;
    int y_max = 0; int y_min = HEIGHT-1;
    for(int i=0; i<dots; i++){
        if (x_max < x[i]) x_max = x[i];
        if (x_min > x[i]) x_min = x[i];
        if (y_max < x[i]) y_max = y[i];
        if (y_min > y[i]) y_min = y[i];
    }

    double invisible = -1.0;
    double marker    = -2.0;
    double ignore    = -3.0;

    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            layer[i][j].a = invisible;
        }
    }

    //枠を描く
    int x0, x1, x2, y0, y1, y2;
    for(int i=0; i<dots; i++){
        x1 = x[i%dots]; x2 = x[(i+1)%dots];
        y1 = y[i%dots]; y2 = y[(i+1)%dots];
        if(x1 > x2){
            int temp_x,  temp_y;
            temp_x = x1; temp_y = y1;
            x1 = x2;     y1 = y2;
            x2 = temp_x; y2 = temp_y;
        }
        if(WIDTH <= x1 || x1 == x2) continue;
        double m = (y1-y2)/(double)(x1-x2);

        int draw_y;
        for(int j = x1; j<=x2; j++){
            draw_y = (int)(m*(j-x1)+y1);
            if(draw_y<0 || HEIGHT<=draw_y || j<0) continue;
            layer[draw_y][j].a = marker;
        }
    }

    //無視する頂点に印をつける
    for(int i=0; i<dots; i++){
        x0 = x[(i-1)%dots];
        x1 = x[i%dots];
        x2 = x[(i+1)%dots];
        if((x0 < x1 && x1 < x2)||(x2 < x1 && x1 < x0)) continue;
        if(x0==x1||x1==x2){
            for(int j=0; j<2; j++){
                if(x[(i+j-1)%dots]==x[(i+j)%dots]){
                    y0 = y[(i+j-1)%dots];
                    y1 = y[(i+j)%dots];
                    if(y0 > y1){
                        int temp_y;
                        temp_y = y1;
                        y1 = y2;
                        y2 = temp_y;
                    }
                    for(int draw_y = y0; draw_y <= y1; draw_y++){
                        layer[draw_y][x1].a = ignore;
                    }
                }
            }
        }
        layer[y[i]][x[i]].a = ignore;
    }

    //縦のスキャンラインで塗る
    for(int draw_x = x_min; draw_x <= x_max; draw_x++){
        struct color brush;
        struct color invisible_brush = {c.r,c.g,c.b,-1.0};
        brush = invisible_brush;
        for(int draw_y = y_min; draw_y <= y_max; draw_y++){
            if(layer[draw_y][draw_x].a==ignore){
                continue;
            }else if(layer[draw_y][draw_x].a==marker){
                brush = (color_equal(brush,c) ? invisible_brush : c);
                continue;
            }
            layer[draw_y][draw_x] = mix_color(layer[draw_y][draw_x],brush); //バグが起きるならmix_colorはやめて直接代入にした方が良さそう
        }
    }

    //枠線と頂点を塗る
    for(int draw_x = x_min; draw_x <= x_max; draw_x++){
        for(int draw_y = y_min; draw_y <= y_max; draw_y++) {
            if (layer[draw_y][draw_x].a != ignore || layer[draw_y][draw_x].a != marker) continue;
            layer[draw_y][draw_x] = mix_color(layer[draw_y][draw_x],c);
        }
    }
}