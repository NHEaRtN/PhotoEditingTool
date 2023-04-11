#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
   if(data.size() == 0) {
    return 0;
  }
  return data[0].size();
}



int Block::width() const {
  /* your code here */
    return data.size();
 
}



void Block::render(PNG &im, int x) const {
// int w = width();
// int h = height();

// // for(int i = 0; i  < w; i++) {
// //     for(int j = 0; j < h ; j++) {

// //      *im.getPixel(i+x,j) = data[i][j];

for(int i = x; i < x + width() ; i++) {
    for(int j = 0; j < height(); j++) {
      HSLAPixel* pixel = im.getPixel(i,j);
      *pixel = data[i-x][j];
    //  *(im.getPixel(width,height))= data[width-x][height];

    }
}
}


void Block::build(PNG &im, int x, int width) {
  // int h = im.height();
  // int w = im.width();

  for(int num = x; num < x+width; num++) {
    vector<HSLAPixel> vec;
    for(unsigned int i = 0; i < im.height() ; i++) {

      vec.push_back(*(im.getPixel(num,i)));
    
    }    
    data.push_back(vec);
  }

}



