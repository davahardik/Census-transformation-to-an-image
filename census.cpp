#include <iostream>
#include <sstream>
 
#include "opencv2/core/core.hpp"
#include "opencv2/core/opengl_interop.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
 
using namespace std;
using namespace cv;
 
int main(int argc, char** argv)
 {
 const char* imgName = "imL_re.png";
 Mat imgIn = imread(imgName, 0);
 imshow("input", imgIn);
 Size imgSize = imgIn.size();
 Mat imgTemp = Mat::zeros(imgSize, CV_8U);
 

 
 unsigned int census = 0;
 unsigned int bit = 0;
 int m = 3;
 int n = 3;//window size
 int i,j,x,y;
 int shiftCount = 0;
 for (x = m/2; x < imgSize.height - m/2; x++)
 {
   for(y = n/2; y < imgSize.width - n/2; y++)
   {
     census = 0;
     shiftCount = 0;
     for (i = x - m/2; i <= x + m/2; i++)
     {
       for (j = y - n/2; j <= y + n/2; j++)
       {
 
         if( shiftCount != m*n/2 )//skip the center pixel
         {
         census <<= 1;
         if( imgIn.at<uchar>(i,j) < imgIn.at<uchar>(x,y) )//compare pixel values in the neighborhood
         bit = 1;
         else
         bit = 0;
         census = census + bit;
       
 
         }
         shiftCount ++;
       }
     }
 
    imgTemp.ptr<uchar>[x][y] = census;
   }
 }
 
 imshow("output", imgTemp);
 waitKey();
 return 0;
 
}
