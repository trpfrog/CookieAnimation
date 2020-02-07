void draw_background(struct color layer[HEIGHT][WIDTH]);
void draw_cookieband(struct color layer[HEIGHT][WIDTH]);
void bake_cookie(struct color layer[HEIGHT][WIDTH]);
void bake_background_cookie(void);
void img_fillcircle(struct color c, int x, int y, double r, struct color layer[HEIGHT][WIDTH]);
void img_fillrect(struct color c, double x, double y, double w, double h, struct color layer[HEIGHT][WIDTH]);
void fill_polygon(int x[], int y[], int dots, struct color c, struct color layer[HEIGHT][WIDTH]);