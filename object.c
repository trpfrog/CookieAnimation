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
    int x[][14] = {{80, 95, 105,102,90, 85, 75, 75, 75, 75, 75, 75, 75, 75},
                   {86, 94, 102,105,97, 87, 83, 82, 82, 82, 82, 82, 82, 82},
                   {135,140,142,138,133,124,123,125,125,125,125,125,125,125},
                   {137,140,139,140,138,133,124,121,123,127,132,132,132,132},
                   {94, 99, 95, 91, 88, 84, 79, 76, 73, 71, 74, 79, 81, 91},
                   {108,117,121,119,114,111,108,103,102,105,105,105,105,105},
                   {79, 85, 77, 73, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76}
                 };
    int y[][14] = {{160,165,150,145,135,135,145,145,145,145,145,145,145,145},
                   {186,184,181,175,172,175,181,184,184,184,184,184,184,184},
                   {164,160,147,146,148,145,156,158,158,158,158,158,158,158},
                   {133,131,127,121,122,119,118,119,122,126,127,127,127,127},
                   {117,113,105,102,105,105,103,103,105,108,112,112,114,117},
                   {117,112,103,100,98, 99, 98, 101,110,116,116,116,116,116},
                   {127,122,115,120,126,126,126,126,126,126,126,126,126,126}
                 };
    int dots[] = {7,8,8,11,14,10,5};
    struct color chocochip[HEIGHT][WIDTH];
    struct color temp[HEIGHT][WIDTH];
    struct color choco_color = {0x5c,0x34,0x21,1.0};

    for(int i=0; i<7; i++){
        clear_layer(chocochip);
        fill_polygon(x[i],y[i],dots[i],choco_color,chocochip);
        merge_layer(chocochip);
        unite_layer(layer,chocochip,temp);
        merge_layer(temp);
        clear_layer(layer);
        copy_layer(layer,temp);
    }

}

void bake_background_cookie(struct color layer[HEIGHT][WIDTH], int t){
    struct color light = {0xad, 0x8b, 0x60, 0.0};
    struct color choco_color = {0x5c, 0x34, 0x21, 1.0};
    for (int i; i < 41;i++){
        img_fillcircle(light,5*i,300-(5*t)%220,8,layer);
        img_fillcircle(choco_color, 5 * i - 1, (300 - (5 * t) % 220) + 2, 3, layer);
        img_fillcircle(choco_color, 5 * i + 4, (300 - (5 * t) % 220) + 2, 1, layer);
        img_fillcircle(choco_color, 5 * i + 1, (300 - (5 * t) % 220) - 4, 1, layer);
        img_fillrect(choco_color, 5 * i - 1, (300 - (5 * t) % 220) + 5, 3, 1, layer);
        img_fillrect(choco_color, 5 * i - 2, (300 - (5 * t) % 220) - 4, 3, 1, layer);
        img_fillrect(choco_color, 5 * i + 4, (300 - (5 * t) % 220) - 2, 3, 1, layer);
    }
}

void pour_milk(int t){
    double omega = 1;
    struct color milk_color = {225,225,224,0.8};
    for(int x=0; x<WIDTH; x++){
        int endpoint = (int)(7*sin(omega*t+x/50.0)+50);
        for(int y = 0; y<=endpoint; y++){
            int diff = 10;
            struct color c = {(milk_color.r-diff)+(diff/endpoint*y),
                              (milk_color.g-diff)+(diff/endpoint*y),
                              (milk_color.b-diff)+(diff/endpoint*y),
                              (milk_color.a-0.3)+(0.3/endpoint*y)};
            put_pixel(c,x,y);
        }
    }
}

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