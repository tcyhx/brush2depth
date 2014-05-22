#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#pragma comment(lib, "opencv_video246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")
#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_contrib246d.lib")
#pragma comment(lib, "opencv_calib3d246d.lib")
#else
#pragma comment(lib, "opencv_video246.lib")
#pragma comment(lib, "opencv_imgproc246.lib")
#pragma comment(lib, "opencv_highgui246.lib")
#pragma comment(lib, "opencv_core246.lib")
#pragma comment(lib, "opencv_contrib246.lib")
#pragma comment(lib, "opencv_calib3d246.lib")
#endif

static void help()
{
    cout << "\nThis program demonstrates interactive user brush on image to assign initial depth\n"
            "Usage:\n"
            "./brush2depth [image_name -- default is fruits.jpg]\n" << endl;


    cout << "Hot keys: \n"
        "\tESC - quit the program\n"
        "\tr - restore the original image\n"
        "\tw or SPACE - save mask image and user defined depth image\n"
        "\t\t(before running it, *roughly* mark the areas to segment on the image)\n"
        "\t  (before that, roughly outline several markers on the image)\n";
}
Mat markerMask, markerDpt, img;
Point prevPt(-1, -1);
int markDpt = 255;
int markWidth = 3;

static void setIntensity( int, void* )
{
    //cout << "mark depth=" << markDpt << endl;
}

static void setBrushWidth( int, void* )
{
    //cout << "mark width=" << markWidth << endl;
}

static void onMouse( int event, int x, int y, int flags, void* )
{
    if( x < 0 || x >= img.cols || y < 0 || y >= img.rows )
        return;
    if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
        prevPt = Point(-1,-1);
    else if( event == CV_EVENT_LBUTTONDOWN )
        prevPt = Point(x,y);
    else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
    {
        Point pt(x, y);
        if( prevPt.x < 0 )
            prevPt = pt;
        line(markerMask, prevPt, pt, Scalar(255), markWidth, 8, 0 );
		line(markerDpt, prevPt, pt, Scalar(markDpt), markWidth, 8, 0 );
        line(img, prevPt, pt, Scalar(0,0,markDpt), markWidth, 8, 0 );
        prevPt = pt;
        imshow("image", img);
    }
}

int main( int argc, char** argv )
{
    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
    Mat img0 = imread(filename, 1);

    if( img0.empty() )
    {
        cout << "Couldn'g open image " << filename << ". Usage: watershed <image_name>\n";
        return 0;
    }
    help();
    namedWindow( "image", 1 );

    img0.copyTo(img);
    cvtColor(img, markerMask, CV_BGR2GRAY);
    markerMask = Scalar::all(0);
	markerMask.copyTo(markerDpt);
    imshow( "image", img );
    setMouseCallback( "image", onMouse, 0 );
	createTrackbar( "markDpt", "image", &markDpt, 255, setIntensity );
	createTrackbar( "markWidth", "image", &markWidth, 5, setBrushWidth );

    for(;;)
    {
        int c = waitKey(0);

        if( (char)c == 27 )
            break;

        if( (char)c == 'r' )
        {
            markerMask = Scalar::all(0);
			markerMask.copyTo(markerDpt);
            img0.copyTo(img);
            imshow( "image", img );
        }

		if( (char)c == 'b' )
        {
            markerMask = imread("mask.png", 0);
			markerDpt = imread("strokes.png",0);
			img = imread("imglbls.png",1);
            imshow( "image", img );
        }

        if( (char)c == 'w' || (char)c == ' ' )
        {
            imshow("marker mask", markerMask);
			imshow("marker depth", markerDpt);
			imwrite("mask.png", markerMask);
			imwrite("strokes.png", markerDpt);
			imwrite("imglbls.png", img);
        }
    }

    return 0;
}
