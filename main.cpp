
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
/*
  Animation animation;
  PNG png;
  png.readFromFile("pacman-solid-bfs-2.png");

  FloodFilledImage image(png);
  DFS dfs(png, Point(40, 40), 0.05);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill( dfs, rainbow );

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
*/

   PNG png;
   png.readFromFile("flower.png");
   png.resize(500, 500);
   FloodFilledImage image(png);
   DFS dfs(png, Point(250, 250), 0.8);
   BFS bfs(png, Point(250, 250), 0.8);
   MyColorPicker c;
   image.addFloodFill( dfs, c );
   image.addFloodFill( bfs, c );
   Animation animation = image.animate(5000);
   PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
   lastFrame.writeToFile("myFloodFill.png");
 animation.write("myFloodFill.gif");

  return 0;
}
