#include <stdbool.h>
bool is_valid_alpha(struct color c);
void copy_layer(struct color new_layer[HEIGHT][WIDTH], struct color layer[HEIGHT][WIDTH]);
void clear_layer(struct color layer[HEIGHT][WIDTH]);
void unite_layer(struct color lower_layer[HEIGHT][WIDTH], struct color upper_layer[HEIGHT][WIDTH], struct color new_layer[HEIGHT][WIDTH]);
void subtract_layer(struct color lower_layer[HEIGHT][WIDTH], struct color upper_layer[HEIGHT][WIDTH], struct color new_layer[HEIGHT][WIDTH]);
void linear_transform(struct color layer[HEIGHT][WIDTH], double matrix[2][2],int origin_x, int origin_y);
void fill_painted_pixel(struct color layer[HEIGHT][WIDTH], struct color c);
void rotate_layer(struct color layer[HEIGHT][WIDTH], double degree, int center_x, int center_y);