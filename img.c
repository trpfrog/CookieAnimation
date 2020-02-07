#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "img.h"
#include "object.h"

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];

//template_function
void img_clear(void) {
    int i, j;
    for(j = 0; j < HEIGHT; ++j) {
        for(i = 0; i < WIDTH; ++i) {
            buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
        }
    }
}

struct color set_valid_alpha(struct color c){
    if(c.a > 1){
        c.a = 1.0;
    }else if(c.a < 0){
        c.a = 0.0;
    }
    return c;
}

//template_function
void img_write(void) {
    sprintf(fname, "img%04d.ppm", ++filecnt);
    FILE *f = fopen(fname, "wb");
    if(f == NULL) { fprintf(stderr, "can't open %s\n", fname); exit(1); }
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(buf, sizeof(buf), 1, f);
    fclose(f);
}

struct color mix_color(struct color c, struct color base){
    c = set_valid_alpha(c);
    base = set_valid_alpha(base);
    double alpha = c.a + (1-c.a)*base.a;
    unsigned char r = base.r*(1-c.a)+c.r*c.a;
    unsigned char g = base.g*(1-c.a)+c.g*c.a;
    unsigned char b = base.b*(1-c.a)+c.b*c.a;
    struct color new_color =  {r,g,b,alpha};
    return new_color;
}

struct color get_pixel(int x, int y){
    struct color temp = {buf[HEIGHT-y-1][x][0],
                         buf[HEIGHT-y-1][x][1],
                         buf[HEIGHT-y-1][x][2],
                         1.0};
    return temp;
}

void put_pixel(struct color c, int x, int y) {
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    c = set_valid_alpha(c);
    if(c.a != 1.0) c = mix_color(c,get_pixel(x,y));
    buf[HEIGHT-y-1][x][0] = c.r;
    buf[HEIGHT-y-1][x][1] = c.g;
    buf[HEIGHT-y-1][x][2] = c.b;
}

void merge_layer(struct color layer[HEIGHT][WIDTH]){
    for(int x=0; x<WIDTH; x++){
        for(int y=0; y<HEIGHT; y++){
            if(layer[y][x].a<=0) continue;
            put_pixel(layer[y][x],x,y);
        }
    }
}

bool color_equal(struct color c1, struct color c2){
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

void print_color(struct color c){
    printf("r=%d, g=%d, b=%d, a=%f\n",c.r,c.g,c.b,c.a);
}