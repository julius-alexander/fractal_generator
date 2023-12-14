#ifndef __TURTLE_H
#define __TURTLE_H

#include <cstdint>
#include <string>
using namespace std;

#include "instruction_list.h"

enum dir_t { UP, RIGHT, DOWN, LEFT};
const double DX[] { 0.0, 1.0, 0.0, -1.0 };
const double DY[] { 1.0, 0.0, -1.0, 0.0 };

typedef struct RGB
{
  uint8_t r;
  uint8_t g;
  uint8_t b; 
} color_t;

const color_t WHITE { 255, 255, 255 };
const color_t BLACK { 0, 0, 0 };

class Turtle
{
private:
  color_t* img;
  double x;
  double y;
  int width;
  int height;
  dir_t heading;
  bool pendown;
public:
  Turtle(int width, int height);
  Turtle(const Turtle&);
  const Turtle& operator=(const Turtle&);
  ~Turtle();
  void forward(double dist);
  void turnLeft();
  void turnRight();
  void outputImage(string file) const;
  void penDown() { pendown = true; }
  void penUp() { pendown = false; }
  void follow(const InstructionList&);
};

#endif