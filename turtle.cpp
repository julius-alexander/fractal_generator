#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#include "turtle.h"

//Initializes a turtle width a blank canvas of a given size
//The turtle starts at (0, 0), facing right, with its pen down
Turtle::Turtle(int width, int height) {
    img = new color_t[width * height];
    for (int i = 0; i < width * height; i++)
        img[i] = WHITE;
    x = y = 0.0;
    heading = RIGHT;
    pendown = true;
    this->width = width;
    this->height = height;
}

//Copy constructor
Turtle::Turtle(const Turtle& copy) {
    width = copy.width;
    height = copy.height;
    x = copy.x;
    y = copy.y;
    heading = copy.heading;
    pendown = copy.pendown;
    img = new color_t[width * height];
    memcpy(img, copy.img, width * height * sizeof(color_t));
}

//Copy assignment operator
const Turtle& Turtle::operator=(const Turtle& copy) {
    if (copy.width * copy.height > width * height) {
        delete[] img;
        img = new color_t[copy.width * copy.height];
    }
    width = copy.width;
    height = copy.height;
    x = copy.x;
    y = copy.y;
    pendown = copy.pendown;
    memcpy(img, copy.img, width * height * sizeof(color_t));
    return *this;
}

// Destructor
Turtle::~Turtle() { delete[] img; }

// Function to move the turtle forwards a given distance
// Will draw on the canvas if the pen is down
// Will not go past edge of canvas
void Turtle::forward(double dist) {
    int sx, sy, dx, dy;
    sx = x;
    sy = y;
    dx = DX[heading];
    dy = DY[heading];
  
    x = x + dx * dist;
    y = y + dy * dist;

  if (pendown)
    while ((x - sx) * dx >= 0 && (y - sy) * dy >= 0)
    {
      if (sx >= 0 && sx < width && sy >= 0 && sy < height)
        img[sy * width + sx] = BLACK;
      sx += dx;
      sy += dy;
    }
}

// Turtle turns left 90 degrees
// UP -> LEFT -> DOWN -> RIGHT -> UP
void Turtle::turnLeft() {
    heading = (dir_t) (((int) heading + 3) % 4);
}

// Turtle turns right 90 degrees
// UP -> RIGHT -> DOWN -> LEFT -> UP
void Turtle::turnRight() {
    heading = (dir_t) (((int) heading + 1) % 4);
}

//Follows the given instructions
//Ignores all "odd" and "even" nodes
void Turtle::follow(const InstructionList& instr) {
    for (hilbert_t move : instr)
        switch (move) {
            case FORWARD:
                forward(instr.getDistance());
                break;
            case TURN_LEFT:
                turnLeft();
                break;
            case TURN_RIGHT:
                turnRight();
                break;
            default:
                break;
    }
}

// BMP output code is based on:
// http://cpansearch.perl.org/src/DHUNT/PDL-Planet-0.12/libimage/bmp.c
struct BMPHeader {
    char bfType[2];       // "BM"
    int bfSize;           // size of file in bytes
    int bfReserved;       // set to 0
    int bfOffBits;        // byte offset to actual bitmap data (= 54)
    int biSize;           // size of BITMAPINFOHEADER, in bytes (= 40)
    int biWidth;          // width of image, in pixels
    int biHeight;         // height of images, in pixels
    short biPlanes;       // number of planes in target device (set to 1)
    short biBitCount;     // bits per pixel (24 in this case)
    int biCompression;    // type of compression (0 if no compression)
    int biSizeImage;      // image size, in bytes (0 if no compression)
    int biXPelsPerMeter;  // resolution in pixels/meter of display device
    int biYPelsPerMeter;  // resolution in pixels/meter of display device
    int biClrUsed;        // number of colors in the color table (if 0, use maximum allowed by biBitCount)
    int biClrImportant;   // number of important colors.  If 0, all colors are important
};

void Turtle::outputImage(string file) const {
    int i;
    int bytesPerLine;
    char* line;
    ofstream out;
    struct BMPHeader bmph;

    // the length of each line must be a multiple of 4 bytes
    bytesPerLine = (3 * (width + 1) / 4) * 4;

    // write header
    strncpy(bmph.bfType, "BM", 2);
    bmph.bfOffBits = 54;
    bmph.bfSize = bmph.bfOffBits + bytesPerLine * height;
    bmph.bfReserved = 0;
    bmph.biSize = 40;
    bmph.biWidth = width;
    bmph.biHeight = height;
    bmph.biPlanes = 1;
    bmph.biBitCount = 24;
    bmph.biCompression = 0;
    bmph.biSizeImage = bytesPerLine * height;
    bmph.biXPelsPerMeter = 0;
    bmph.biYPelsPerMeter = 0;
    bmph.biClrUsed = 0;
    bmph.biClrImportant = 0;

    out.open(file, ios::binary);

    if (!out.is_open()) {
        cout << "Could not open " << file << " for writing!\n";
        return;
    }

    out.write(reinterpret_cast<char*>(&bmph.bfType), 2);
    out.write(reinterpret_cast<char*>(&bmph.bfSize), 4);
    out.write(reinterpret_cast<char*>(&bmph.bfReserved), 4);
    out.write(reinterpret_cast<char*>(&bmph.bfOffBits), 4);
    out.write(reinterpret_cast<char*>(&bmph.biSize), 4);
    out.write(reinterpret_cast<char*>(&bmph.biWidth), 4);
    out.write(reinterpret_cast<char*>(&bmph.biHeight), 4);
    out.write(reinterpret_cast<char*>(&bmph.biPlanes), 2);
    out.write(reinterpret_cast<char*>(&bmph.biBitCount), 2);
    out.write(reinterpret_cast<char*>(&bmph.biCompression), 4);
    out.write(reinterpret_cast<char*>(&bmph.biSizeImage), 4);
    out.write(reinterpret_cast<char*>(&bmph.biXPelsPerMeter), 4);
    out.write(reinterpret_cast<char*>(&bmph.biYPelsPerMeter), 4);
    out.write(reinterpret_cast<char*>(&bmph.biClrUsed), 4);
    out.write(reinterpret_cast<char*>(&bmph.biClrImportant), 4);

    line = new char[bytesPerLine];
    memset(line, 0, bytesPerLine);

    for (i = 0; i < height; i++) {
        memcpy(line, &img[i*width], width*sizeof(color_t));
        out.write(line, bytesPerLine);
    }

    delete line;
    out.close();
}
