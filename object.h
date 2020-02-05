void draw_background(int layer[HEIGHT][WIDTH][3]);
void draw_cookieband(int layer[HEIGHT][WIDTH][3]);
void bake_cookie(int layer[HEIGHT][WIDTH][3]);
void bake_background_cookie(void);
void img_fillcircle(struct color c, int x, int y, double r, int layer[HEIGHT][WIDTH][3]);
void img_fillrect(struct color c, double x, double y, double w, double h, int layer[HEIGHT][WIDTH][3]);
void fill_polygon(int x[], int y[], int dots, struct color c, int layer[HEIGHT][WIDTH][3]);