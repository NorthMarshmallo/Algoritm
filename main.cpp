#include "tgaimage.h"
#include <math.h>
#include <iostream>
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void DrawLine(int x1, int y1, int x2, int y2, TGAImage& Image) {
	double dx, dy,e,x,y;
	e = 1/fmax(abs(x2 - x1), abs(y2 - y1));
	x = x1; y = y1;
	dx = e * (x2-x1);
	dy = e * (y2-y1);
	if (abs(dx) < abs(dy)) {
		while (y != y2) {
			Image.set(round(x), round(y),red);
			y += dy;
			x += dx;
			cout << x << " " << y << endl;
		}
		Image.set(x2,y2, red);
	}
	else {
		while (x != x2) {
			Image.set(round(x), round(y),red);
			y += dy;
			x += dx;
			cout << x << " " << y << endl;
		}
		Image.set(x2,y2,red);
	}
}

void DrawLineBrez(int x1, int y1, int x2, int y2, TGAImage& Image) {
	double dy, dx, x, y;
	bool flag = false;
	x = x1; y = y1;
	dx = x2 - x1; dy = y2 - y1;
	if (abs(dx) < abs(dy)) {
		swap(x, y);
		swap(x1, y1);
		swap(x2, y2);
		swap(dx, dy);
		flag = true;
	}
	double d = 2 * dy - dx;
	while (x != x2) {
		if (flag == true)
			Image.set(round(y), round(x), red);
		else
		    Image.set(round(x), round(y), red);
		if (d < 0) {
			d += 2 * abs(dy);
		}
		else{
			d += 2 * (abs(dy) - abs(dx));
			if ((y2 - y1) != 0)
				y += (y2 - y1) / (abs(y2 - y1));
			else
				y += 0;
	    }
		if ((x2 - x1) != 0)
			x += (x2 - x1) / abs(x2 - x1);
		else
			x += 0;
		cout << x << " " << y << endl;
	}
	if (flag == true) {
		swap(x2,y2);
	}
	Image.set(x2, y2, red);
}

void DrawCircle(int x0, int y0, int r, TGAImage& Image) {
	for (int x = 0; x <= r / sqrt(2); x++) {
		int y = (int)(sqrt(r*r-x*x));
		Image.set(x0+x, y0+y, red);
		Image.set(x0+y, y0+x, red);
		Image.set(x0-x, y0-y, red);
		Image.set(x0-y, y0-x, red);
		Image.set(x0-x, y0+y, red);
		Image.set(x0-y, y0+x, red);
		Image.set(x0+x, y0-y, red);
		Image.set(x0+y, y0-x, red);
		cout << x << " " << y << endl;
	}
}

void DrawCirclecda(int x0, int y0, int r, TGAImage& Image) {
	double x, y, x1, y1, e;
	e = pow(2, -ceil(log(r) / log(2)));
	x = r; y = 0;
	cout << "CDA" << endl;
	for (int i = 0; i <= 360; i++) {
		x1 = x + e * y;
		y1 = y - e * x1;
		DrawLine(x+x0, y+y0, x1+x0, y1+y0, Image);
		x = x1; y = y1;
	}
}

void DrawCirclecbrez(int x0, int y0, int r, TGAImage& Image) {
	double d, x, y;
	d = 3 - 2 * r; x = 0; y = r;
	while (x < r / sqrt(2)) {
		Image.set(x0 + x, y0 + y, red);
		Image.set(x0 + y, y0 + x, red);
		Image.set(x0 - x, y0 - y, red);
		Image.set(x0 - y, y0 - x, red);
		Image.set(x0 - x, y0 + y, red);
		Image.set(x0 - y, y0 + x, red);
		Image.set(x0 + x, y0 - y, red);
		Image.set(x0 + y, y0 - x, red);
		if (d < 0) {
			d += 4 * x + 6;
		}
		else {
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	TGAImage image1(100, 100, TGAImage::RGB);
	TGAImage image2(100, 100, TGAImage::RGB);
	DrawLine(56, 2, 56, 89,image);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	DrawLineBrez(3,3,11,25, image1);
	image1.flip_vertically();
	image1.write_tga_file("outputbrez.tga");
	DrawCircle(25,38,15, image2);
	image2.flip_vertically();
	image2.write_tga_file("outputcircle.tga");
	TGAImage image3(100, 100, TGAImage::RGB);
	DrawCirclecda(25,38,15, image3);
	image3.flip_vertically();
	image3.write_tga_file("outputcirclecda.tga"); 
	TGAImage image4(100, 100, TGAImage::RGB);
	DrawCirclecbrez(25, 38, 15, image4);
	image4.flip_vertically();
	image4.write_tga_file("outputcirclebrez.tga");
	return 0;
}

