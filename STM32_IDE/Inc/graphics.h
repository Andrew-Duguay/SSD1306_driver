void drawPixel(int x, int y);

void erasePixel(int x, int y);

void drawSquare(int x, int y, int w, int h);

void eraseSquare(int x, int y, char w, char h);

void circleUtil(int xc, int yc, int x, int y, char erase);

// Algorithm source:   https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
void drawCircle(int xc, int yc, int r);

// Algorithm source:   https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
void eraseCircle(int xc, int yc, int r);

void drawLine(int x0, int y0, int x1, int y1);

void eraseLine(int x0, int y0, int x1, int y1);

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2);

void eraseTriangle(int x0, int y0, int x1, int y1, int x2, int y2);

int abs_int(int x);

int min(int a, int b);

int max(int a, int b);
