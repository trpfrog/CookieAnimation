#include <stdbool.h>
bool is_within_colorrange(int color[3]);
void copy_layer(int new_layer[HEIGHT][WIDTH][3], int layer[HEIGHT][WIDTH][3]);
void paint_layerpixel(int pixel[3], int color[3]);
void clear_layer(int layer[HEIGHT][WIDTH][3]);
void unite_layer(int lower_layer[HEIGHT][WIDTH][3], int upper_layer[HEIGHT][WIDTH][3], int new_layer[HEIGHT][WIDTH][3]);
void subtract_layer(int lower_layer[HEIGHT][WIDTH][3], int upper_layer[HEIGHT][WIDTH][3], int new_layer[HEIGHT][WIDTH][3]);
void linear_transform(int layer[HEIGHT][WIDTH][3], double matrix[2][2],int origin_x, int origin_y, int new_layer[HEIGHT][WIDTH][3]);
void fill_painted_pixel(int layer[HEIGHT][WIDTH][3], struct color c);