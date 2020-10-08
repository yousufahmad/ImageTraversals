#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(){
  /** @todo [Part 1] */
  traversal_ = NULL;
  //start_ = Point(-1, -1);
}

//ImageTraversal::~ImageTraversal() {
	// Nothing
//}

//
// ImageTraversal::Iterator::~Iterator() {
//   std::cout << "Destroy\n";
//   for(int i = 0; i < (int)png_.width(); i++) {
//     delete[] visited[i];
//   }
//
//   delete[] visited;
// }

//parametrized iterator constructor for derived classes to use
ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, PNG png, Point &start, double tolerance){
  traversal_ = traversal; //store all passed in info into \private variables
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;

  current = start; //iterator Point set to the beginning
//  traversal_->add(start); //add the start Point to the stack/queue
  startpixel = png_.getPixel(start.x, start.y); //get pixel of starting Point

  //TRYING TO MAKE A 2D VECTOR of bools
  //vector<vector<bool> > visited(png.width(),vector<bool>(png.height(), false));



  visited = new bool*[png_.width()]; //2D array of bools all initialized to false
  for(unsigned int i = 0; i < png_.width(); i++){
    visited[i] = new bool[png_.height()];
  }
  for(unsigned i=0; i<png_.width(); i++){//the pixel values
    for(unsigned j=0; j<png_.height(); j++){
      visited[i][j] = false;
    }
  }

  visited[start.x][start.y] = true; //marks the starting point as visited

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  traversal_->pop();
  visited[current.x][current.y] = true; //very first point is visited

  //moving mark visisted line to the bottom

  Point right = Point(current.x+1, current.y);
  Point down = Point(current.x, current.y+1);
  Point left = Point(current.x-1, current.y);
  Point up = Point(current.x, current.y-1);


//check right
if(right.x < png_.width()){
  if(calculateDelta(startpixel, png_.getPixel(right.x, right.y)) < tolerance_ &&
    visited[right.x][right.y] == false ){
    traversal_->add(right);
  }
}

//check down
if(down.y < png_.height()){
  if(calculateDelta(startpixel, png_.getPixel(down.x, down.y)) < tolerance_ &&
    visited[down.x][down.y] == false){
    traversal_->add(down);
  }
}

//check left
if(left.x < png_.width()){
  if(calculateDelta(startpixel, png_.getPixel(left.x, left.y)) < tolerance_ &&
    visited[left.x][left.y] == false) {
      traversal_->add(left);
}
  }

//check up
if(up.y < png_.height()){
  if(calculateDelta(startpixel, png_.getPixel(up.x, up.y)) < tolerance_ &&
    visited[up.x][up.y] == false){
    traversal_->add(up);
  }
}

  while(!traversal_->empty() && visited[traversal_->peek().x][traversal_->peek().y] == true){
    traversal_->pop();
  }
  if(!traversal_->empty()){
    current = traversal_->peek();
  }

  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal_ == NULL) { thisEmpty = true; }
  if (other.traversal_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal_->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal_->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal_ != other.traversal_); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}
