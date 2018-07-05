#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat img, gray;
    if( argc != 2 || !(img=imread(argv[1], 1)).data)
        return -1;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    Mat MorphElement = getStructuringElement(cv::MORPH_CROSS, Size(3,3));
    //GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
    Canny(gray, gray, 0, 255);
    vector<Vec3f> circles;
    dilate(gray, gray, MorphElement);
    HoughCircles(gray, circles, HOUGH_GRADIENT, 2, gray.rows/4);
    for( size_t i = 0; i < circles.size(); i++ ){

        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // draw the circle outline
        circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    imshow( "PreDetect", gray);
    imshow( "circles", img );
    waitKey(0);

    return 0;
}