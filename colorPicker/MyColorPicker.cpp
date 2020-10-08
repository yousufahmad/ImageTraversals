#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  //double hue =11;
  unsigned rand = x+y;
  double hue = 50 - (rand % 100);
  HSLAPixel pixel(hue, 1, 0.5);
  return pixel;

  //return HSLAPixel();
}
