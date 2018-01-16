// opencv3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdio.h>
#pragma warning(disable : 4996)
using namespace cv;
using namespace std;

//hide the local functions in an anon namespace
namespace {
	void help(char** av) {
		cout << "The program captures frames from a video file, image sequence (01.jpg, 02.jpg ... 10.jpg) or camera connected to your computer." << endl
			<< "Usage:\n" << av[0] << " <video file, image sequence or device number>" << endl
			<< "q,Q,esc -- quit" << endl
			<< "space   -- save frame" << endl << endl
			<< "\tTo capture from a camera pass the device number. To find the device number, try ls /dev/video*" << endl
			<< "\texample: " << av[0] << " 0" << endl
			<< "\tYou may also pass a video file instead of a device number" << endl
			<< "\texample: " << av[0] << " video.avi" << endl
			<< "\tYou can also pass the path to an image sequence and OpenCV will treat the sequence just like a video." << endl
			<< "\texample: " << av[0] << " right%%02d.jpg" << endl;
	}

	int process(VideoCapture& capture) {
		int n = 0;
		char filename[200];
		string window_name = "video | q or esc to quit";
		cout << "press space to save a picture. q or esc to quit" << endl;
		namedWindow(window_name, WINDOW_KEEPRATIO); //resizable window;
		Mat frame;

		for (;;) {
			capture >> frame;
			if (frame.empty())
				break;

			imshow(window_name, frame);
			char key = (char)waitKey(30); //delay N millis, usually long enough to display and capture input

			switch (key) {
			case 'q':
			case 'Q':
			case 27: //escape key
				return 0;
			case ' ': //Save an image
				sprintf(filename, "filename%.3d.jpg", n++);
				imwrite(filename, frame);
				cout << "Saved " << filename << endl;
				break;
			default:
				break;
			}
		}
		return 0;
	}
}

int main(int ac, char** av) {

	if (ac != 2) {
		help(av);
		return 1;
	}
	std::string arg = av[1];
	VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file or image sequence
	if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
		capture.open(atoi(arg.c_str()));
	if (!capture.isOpened()) {
		cerr << "Failed to open the video device, video file or image sequence!\n" << endl;
		help(av);
		return 1;
	}
	return process(capture);
}
/*
#include "opencv2/objdetect.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui/highgui_c.h"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>

using namespace std;
using namespace cv;

static void help()
{
	cout << "\nThis program demonstrates the cascade recognizer. Now you can use Haar or LBP features.\n"
		"This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.\n"
		"It's most known use is for faces.\n"
		"Usage:\n"
		"./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]\n"
		"   [--nested-cascade[=nested_cascade_path this an optional secondary classifier such as eyes]]\n"
		"   [--scale=<image scale greater or equal to 1, try 1.3 for example>]\n"
		"   [--try-flip]\n"
		"   [filename|camera_index]\n\n"
		"see facedetect.cmd for one call:\n"
		"./facedetect --cascade=\"../../data/haarcascades/haarcascade_frontalface_alt.xml\" --nested-cascade=\"../../data/haarcascades/haarcascade_eye.xml\" --scale=1.3\n\n"
		"During execution:\n\tHit any key to quit.\n"
		"\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale, bool tryflip);

string cascadeName = "../../data/haarcascades/haarcascade_frontalface_alt.xml";
string nestedCascadeName = "../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

int main(int argc, const char** argv)
{
	CvCapture* capture = 0;
	Mat frame, frameCopy, image;
	const string scaleOpt = "--scale=";
	size_t scaleOptLen = scaleOpt.length();
	const string cascadeOpt = "--cascade=";
	size_t cascadeOptLen = cascadeOpt.length();
	const string nestedCascadeOpt = "--nested-cascade";
	size_t nestedCascadeOptLen = nestedCascadeOpt.length();
	const string tryFlipOpt = "--try-flip";
	size_t tryFlipOptLen = tryFlipOpt.length();
	string inputName;
	bool tryflip = false;

	help();

	CascadeClassifier cascade, nestedCascade;
	double scale = 1;

	for (int i = 1; i < argc; i++)
	{
		cout << "Processing " << i << " " << argv[i] << endl;
		if (cascadeOpt.compare(0, cascadeOptLen, argv[i], cascadeOptLen) == 0)
		{
			cascadeName.assign(argv[i] + cascadeOptLen);
			cout << "  from which we have cascadeName= " << cascadeName << endl;
		}
		else if (nestedCascadeOpt.compare(0, nestedCascadeOptLen, argv[i], nestedCascadeOptLen) == 0)
		{
			if (argv[i][nestedCascadeOpt.length()] == '=')
				nestedCascadeName.assign(argv[i] + nestedCascadeOpt.length() + 1);
			if (!nestedCascade.load(nestedCascadeName))
				cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		}
		else if (scaleOpt.compare(0, scaleOptLen, argv[i], scaleOptLen) == 0)
		{
			if (!sscanf(argv[i] + scaleOpt.length(), "%lf", &scale) || scale < 1)
				scale = 1;
			cout << " from which we read scale = " << scale << endl;
		}
		else if (tryFlipOpt.compare(0, tryFlipOptLen, argv[i], tryFlipOptLen) == 0)
		{
			tryflip = true;
			cout << " will try to flip image horizontally to detect assymetric objects\n";
		}
		else if (argv[i][0] == '-')
		{
			cerr << "WARNING: Unknown option %s" << argv[i] << endl;
		}
		else
			inputName.assign(argv[i]);
	}

	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		help();
		return -1;
	}

	if (inputName.empty() || (isdigit(inputName.c_str()[0]) && inputName.c_str()[1] == '\0'))
	{
		capture = cvCaptureFromCAM(inputName.empty() ? 0 : inputName.c_str()[0] - '0');
		int c = inputName.empty() ? 0 : inputName.c_str()[0] - '0';
		if (!capture) cout << "Capture from CAM " << c << " didn't work" << endl;
	}
	else if (inputName.size())
	{
		image = imread(inputName, 1);
		if (image.empty())
		{
			capture = cvCaptureFromAVI(inputName.c_str());
			if (!capture) cout << "Capture from AVI didn't work" << endl;
		}
	}
	else
	{
		image = imread("../data/lena.jpg", 1);
		if (image.empty()) cout << "Couldn't read ../data/lena.jpg" << endl;
	}

	cvNamedWindow("result", 1);

	if (capture)
	{
		cout << "In capture ..." << endl;
		for (;;)
		{
			IplImage* iplImg = cvQueryFrame(capture);
			frame = cv::cvarrToMat(iplImg);
			if (frame.empty())
				break;
			if (iplImg->origin == IPL_ORIGIN_TL)
				frame.copyTo(frameCopy);
			else
				flip(frame, frameCopy, 0);

			detectAndDraw(frameCopy, cascade, nestedCascade, scale, tryflip);

			if (waitKey(10) >= 0)
				goto _cleanup_;
		}

		waitKey(0);

	_cleanup_:
		cvReleaseCapture(&capture);
	}
	else
	{
		cout << "In image read" << endl;
		if (!image.empty())
		{
			detectAndDraw(image, cascade, nestedCascade, scale, tryflip);
			waitKey(0);
		}
		else if (!inputName.empty())
		{
			/* assume it is a text file containing the
			list of the image filenames to be processed - one per line * /
			FILE* f = fopen(inputName.c_str(), "rt");
			if (f)
			{
				char buf[1000 + 1];
				while (fgets(buf, 1000, f))
				{
					int len = (int)strlen(buf), c;
					while (len > 0 && isspace(buf[len - 1]))
						len--;
					buf[len] = '\0';
					cout << "file " << buf << endl;
					image = imread(buf, 1);
					if (!image.empty())
					{
						detectAndDraw(image, cascade, nestedCascade, scale, tryflip);
						c = waitKey(0);
						if (c == 27 || c == 'q' || c == 'Q')
							break;
					}
					else
					{
						cerr << "Aw snap, couldn't read image " << buf << endl;
					}
				}
				fclose(f);
			}
		}
	}

	cvDestroyWindow("result");

	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale, bool tryflip)
{
	int i = 0;
	double t = 0;
	vector<Rect> faces, faces2;
	const static Scalar colors[] = { CV_RGB(0, 0, 255),
		CV_RGB(0, 128, 255),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 255, 0),
		CV_RGB(255, 128, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(255, 0, 0),
		CV_RGB(255, 0, 255) };
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	cvtColor(img, gray, COLOR_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double)cvGetTickCount();
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
		| CASCADE_SCALE_IMAGE
		,
		Size(30, 30));
	if (tryflip)
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT
			//|CASCADE_DO_ROUGH_SEARCH
			| CASCADE_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)cvGetTickCount() - t;
	printf("detection time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r->width / r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
			cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1)*scale)),
			color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT
			//|CASCADE_DO_ROUGH_SEARCH
			//|CASCADE_DO_CANNY_PRUNING
			| CASCADE_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++)
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}
	cv::imshow("result", img);
}














/*
#include<stdio.h>
#include<stdlib.h>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<math.h>


/*lesson 34.2* /

IplImage *image = 0;
IplImage *templ = 0;
int main(int argc, char *argv[])
{
	char *filename = argc >= 2 ? argv[1] : "image0.jpg";
	image = cvLoadImage(filename, 1);
	printf("[i] image: %s\n", filename);
	assert(image != 0);
	char *filename1 = argc >= 3 ? argv[2] : "image1.jpg";
	templ = cvLoadImage(filename1, 1);
	printf("[i] templ: %s\n", filename1);
	assert(templ != 0);
	cvNamedWindow("original");
	cvNamedWindow("templ");
	cvNamedWindow("match");
	cvNamedWindow("res");

	int width = templ->width;
	int height = templ->height;
	cvShowImage("original", image);
	cvShowImage("templ", templ);

	IplImage *res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);
	cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);

	cvShowImage("res", res);
	double minval, maxval;


	CvPoint minloc, maxloc;
	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);
	cvNormalize(res, res, 1, 0, CV_MINMAX);
	cvNamedWindow("res_norm");
	cvShowImage("res_norm", res);
	cvRectangle(image,cvPoint(minloc.x,minloc.y), cvPoint(minloc.x+templ->width-1,minloc.y+templ->height-1),CV_RGB(255,0,0),1,8);
	cvShowImage("match",image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();
	return 0;


}

/*lesson 34.1* /
int main(int argc, char *argv[])
{
	IplImage *src, *templ, *ftmp[6];
	int i;
	char *filename = argc >= 2 ? argv[1] : "image0.jpg";
	char* filename1 = argc >= 3 ? argv[2] : "image1.jpg";
	if ((src = cvLoadImage(filename, 1)) == 0)
	{
		printf("error on reading src image %s\n", filename);
		return(-1);
	}
	if ((templ = cvLoadImage(filename1, 1)) == 0)
	{
		printf("error on reading templ image %s\n", filename1);
		return (-1);
	}
	int patchx = templ->width;
	int patchy = templ->height;
	int iwidth = src->width - patchx + 1;
	int iheight = src->height - patchy + 1;
	for (i = 0; i < 6; i++)
	{
		ftmp[i] = cvCreateImage(cvSize(iwidth, iheight), 32, 1);
	}
	for (i = 0; i < 6; i++)
	{
		cvMatchTemplate(src, templ, ftmp[i], i);
		cvNormalize(ftmp[i], ftmp[i], 1, 0, CV_MINMAX);
	}

	cvNamedWindow("template");
	cvShowImage("template", templ);
	cvNamedWindow("image");
	cvShowImage("image", src);
	cvNamedWindow("sqdiff");
	cvShowImage("sqdiff", ftmp[0]);
	cvNamedWindow("normed");
	cvShowImage("normed", ftmp[1]);
	cvNamedWindow("ccorr");
	cvShowImage("ccorr", ftmp[2]);
	cvNamedWindow("ccorr_normed");
	cvShowImage("ccorr_normed", ftmp[3]);
	cvNamedWindow("ccoeff");
	cvShowImage("ccoeff", ftmp[4]);
	cvNamedWindow("ccoeff_normed");
	cvShowImage("ccoeff_normed", ftmp[5]);

	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&templ);
	for (i = 0; i < 6; i++)
	{
		cvReleaseImage(&ftmp[i]);
	}

	cvDestroyAllWindows();
	return 0;
}

/*lesson 33 site* /
void testMatch(IplImage* original, IplImage* templ)
{
	assert(original != 0);
	assert(templ != 0);

	printf("[i] test cvMatchShapes()\n");

	IplImage *src = 0, *dst = 0;

	src = cvCloneImage(original);
printf("cvCreateImae binI\n");
	IplImage* binI = cvCreateImage(cvGetSize(src), 8, 1);
printf("cvCreateImae binT\n");
	IplImage* binT = cvCreateImage(cvGetSize(templ), 8, 1);

printf("cvCreateImae rgb\n");
	// заведём цветные картинки
	IplImage* rgb = cvCreateImage(cvGetSize(original), 8, 3);
	cvConvertImage(src, rgb, CV_GRAY2BGR);
printf("cvCreateImae rgbT\n");
	IplImage* rgbT = cvCreateImage(cvGetSize(templ), 8, 3);
	cvConvertImage(templ, rgbT, CV_GRAY2BGR);



	// получаем границы изображения и шаблона
	cvCanny(src, binI, 50, 200);
	cvCanny(templ, binT, 50, 200);

	// показываем
	cvNamedWindow("cannyI", 1);
	cvShowImage("cannyI", binI);

	cvNamedWindow("cannyT", 1);
	cvShowImage("cannyT", binT);

	// для хранения контуров
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contoursI = 0, *contoursT = 0;

	// находим контуры изображения
	int contoursCont = cvFindContours(binI, storage, &contoursI, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	// для отметки контуров
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0);
	char buf[128];
	int counter = 0;

	// нарисуем контуры изображения
	if (contoursI != 0){
		for (CvSeq* seq0 = contoursI; seq0 != 0; seq0 = seq0->h_next){
			// рисуем контур
			cvDrawContours(rgb, seq0, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
			// выводим его номер
			//CvPoint2D32f point; float rad;
			//cvMinEnclosingCircle(seq0,&point,&rad); // получим окружность содержащую контур
			//cvPutText(rgb, itoa(++counter, buf, 10), cvPointFrom32f(point), &font, CV_RGB(0,255,0));
		}
	}
	// показываем
	cvNamedWindow("cont", 1);
	cvShowImage("cont", rgb);

	cvConvertImage(src, rgb, CV_GRAY2BGR);

	// находим контуры шаблона
	cvFindContours(binT, storage, &contoursT, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	CvSeq* seqT = 0;
	double perimT = 0;

	if (contoursT != 0){
		// находим самый длинный контур 
		for (CvSeq* seq0 = contoursT; seq0 != 0; seq0 = seq0->h_next){
			double perim = cvContourPerimeter(seq0);
			if (perim>perimT){
				perimT = perim;
				seqT = seq0;
			}
			// рисуем
			cvDrawContours(rgbT, seq0, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8); // рисуем контур
		}
	}
	// покажем контур шаблона
	cvDrawContours(rgbT, seqT, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8); // рисуем контур
	cvNamedWindow("contT", 1);
	cvShowImage("contT", rgbT);


	CvSeq* seqM = 0;
	double matchM = 1000;
	// обходим контуры изображения 
	counter = 0;
	if (contoursI != 0){
		// поиск лучшего совпадения контуров по их моментам 
		for (CvSeq* seq0 = contoursI; seq0 != 0; seq0 = seq0->h_next){
			double match0 = cvMatchShapes(seq0, seqT, CV_CONTOURS_MATCH_I3);
			if (match0<matchM){
				matchM = match0;
				seqM = seq0;
			}
			printf("[i] %d match: %.2f\n", ++counter, match0);
		}
	}
	// рисуем найденный контур
	cvDrawContours(rgb, seqM, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8); // рисуем контур

	cvNamedWindow("find", 1);
	cvShowImage("find", rgb);

	// ждём нажатия клавиши
	cvWaitKey(0);

	// освобождаем ресурсы
	cvReleaseMemStorage(&storage);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&rgb);
	cvReleaseImage(&rgbT);
	cvReleaseImage(&binI);
	cvReleaseImage(&binT);

	// удаляем окна
	cvDestroyAllWindows();
}

int main(int argc, char* argv[])
{
	IplImage *original = 0, *templ = 0;

	// имя картинки задаётся первым параметром
	char* filename = argc >= 2 ? argv[1] : "image0.jpg";
	// получаем картинку
	original = cvLoadImage(filename, 0);

	printf("[i] image: %s\n", filename);
	assert(original != 0);

	// имя шаблона задаётся вторым параметром
	char* filename2 = argc >= 3 ? argv[2] : "imagel.jpg";
	// получаем картинку
	templ = cvLoadImage(filename2, 0);

	printf("[i] template: %s\n", filename2);
	assert(templ != 0);

	// покажем изображения
	cvNamedWindow("original", 1);
	cvShowImage("original", original);
	cvNamedWindow("template", 1);
	cvShowImage("template", templ);

	// сравнение
	testMatch(original, templ);

	// освобождаем ресурсы
	cvReleaseImage(&original);
	cvReleaseImage(&templ);
	// удаляем окна
	cvDestroyAllWindows();
	return 0;
}



/*lesson 33* /

void testMatch(IplImage *original,IplImage *temp1)
{
	assert(original != 0);
	assert(temp1 != 0);
	printf("[i] test cvMatchShapes() \n");
	IplImage *src = 0, *dst = 0;
	src = cvCloneImage(original);
	IplImage *binI = cvCreateImage(cvGetSize(src),8,1);
	IplImage *binT = cvCreateImage(cvGetSize(temp1), 8, 1);
	IplImage *rgb = cvCreateImage(cvGetSize(original),8,3);
	cvConvertImage(src, rgb, CV_GRAY2BGR);
	IplImage *rgbT = cvCreateImage(cvGetSize(temp1),8,3);
	cvConvertImage(temp1, rgbT, CV_GRAY2BGR);

	cvCanny(src, binI, 50, 200);
	cvCanny(temp1, binT, 50, 200);

	cvNamedWindow("cannyT", 1);
	cvShowImage("cannyT", binT);
	cvNamedWindow("cannyI", 1);
	cvShowImage("cannyI", binI);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contoursI = 0, *contoursT = 0;
	int contoursCont = cvFindContours(binI, storage, &contoursI, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0);
	char biuf[128];
	int counter = 0;
	if (contoursT = 0)
	{
		for (CvSeq* seq0 = contoursI; seq0 != 0; seq0 = seq0->h_next)
		{
			cvDrawContours(rgb, seq0, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
		}
	}
	cvNamedWindow("cont", 1);
	cvShowImage("cont",rgb);
	cvConvertImage(src, rgb, CV_GRAY2BGR);
	cvFindContours(binT, storage, &contoursT, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	CvSeq *seqT = 0;
	double perimT = 0;
	if (contoursT != 0)
	{
		for (CvSeq *seq0 = contoursT; seq0 != 0; seq0 = seq0->h_next)
		{
			double perim = cvContourPerimeter(seq0);
			if (perim > perimT)
			{
				perimT = perim;
				seqT = seq0;
			}
			cvDrawContours(rgbT, seq0, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
		}
	}
	cvDrawContours(rgbT, seqT, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8);
	cvNamedWindow("contT",1);
	cvShowImage("contT", rgbT);
	CvSeq* seqM = 0;
	double matchM = 1000;
	counter = 0;
	if (contoursI != 0)
	{
		for (CvSeq*seq0 = 0; seq0 != 0; seq0 = seq0->h_next)
		{
			double match0 = cvMatchShapes(seq0, seqT, CV_CONTOURS_MATCH_I3);
			if (match0 < matchM)
			{
				matchM = match0;
				seqM = seq0;
			}
			printf("[i] %d Mathch %.2f\n", ++counter, match0);
		}
	}
	cvDrawContours(rgb, seqM, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8);
	cvNamedWindow("find",1);
	cvShowImage("find",rgb);
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&rgb);
	cvReleaseImage(&rgbT);
	cvReleaseImage(&binI);
	cvReleaseImage(&binT);
	cvReleaseMemStorage(&storage);
	cvDestroyAllWindows();
}
int main(int argc, char* argv[])
{
	IplImage *src = 0, *dst = 0, *dst2 = 0, *dst3 = 0;

	char *filename = argc == 2 ? argv[1] : "image0.jpg";
	src = cvLoadImage(filename);
	printf("[i] image: %s\n", filename);
	assert(src != 0);
	
	char *filename2 = argc >= 3 ? argv[2] : "image1.jpg";
	dst = cvLoadImage(filename2);
	printf("[i] image2: %s\n", filename2);
	assert(dst!= 0);	


	cvNamedWindow("src", 1);
	cvShowImage("src", src);
	cvNamedWindow("dst", 1);
	cvShowImage("dst", dst);

	testMatch(src, dst);

	cvReleaseImage(&dst2);
	cvReleaseImage(&src);
	cvReleaseImage(&dst3);
	cvReleaseImage(&dst);
	cvDestroyAllWindows();
	return 0;


}

/*lesson32.2* /

void findcircle(IplImage*_image)
{
	assert(_image != 0);
	IplImage* bin = cvCreateImage(cvGetSize(_image),IPL_DEPTH_8U,1);
	cvConvertImage(_image, bin, CV_BGR2GRAY);
	cvCanny(bin, bin, 50, 200);
	cvNamedWindow("bin", 1);
	cvShowImage("bin", bin);
	CvMemStorage*storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	int contoursCont = cvFindContours(bin, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	assert(contours != 0);
	for (CvSeq* current = contours; current != NULL; current = current->h_next)
	{
		double area = fabs(cvContourArea(current));
		double perim = cvContourPerimeter(current);
		if (area / (perim*perim) > 0.07 && area / (perim*perim) < 0.087)
		{
			cvDrawContours(_image, current, cvScalar(0, 0, 255), cvScalar(0, 255, 0),-1, 1, 8);

		}
	}
	cvReleaseImage(&bin);
	cvReleaseMemStorage(&storage);
}

void findpoly(IplImage*_image)
{
	assert(_image != 0);
	IplImage* bin = cvCreateImage(cvGetSize(_image),IPL_DEPTH_8U,1);
	cvConvertImage(_image, bin, CV_BGR2GRAY);
	cvCanny(bin, bin, 50, 200);
	cvNamedWindow("bin", 1);
	cvShowImage("bin", bin);
	CvMemStorage*storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	int contoursCont = cvFindContours(bin, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	assert(contours != 0);
	for (CvSeq* current = contours; current != NULL; current = current->h_next)
	{
		
		CvSeq *result = cvApproxPoly(current, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 0.1, 0);
		cvDrawContours(_image, result, cvScalar(0, 0, 255), cvScalar(0, 255, 0),-1, 1, 8);
	}
	cvReleaseImage(&bin);
	cvReleaseMemStorage(&storage);
}


void enclosingCircle(IplImage*_image)
{
	assert(_image != 0);
	IplImage* bin = cvCreateImage(cvGetSize(_image),IPL_DEPTH_8U,1);
	cvConvertImage(_image, bin, CV_BGR2GRAY);
	cvCanny(bin, bin, 50, 200);
	cvNamedWindow("bin", 1);
	cvShowImage("bin", bin);
	CvMemStorage*storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	int contoursCont = cvFindContours(bin, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	assert(contours != 0);
	for (CvSeq* current = contours; current != NULL; current = current->h_next)
	{

		CvPoint2D32f center;
		float radius = 0;
		cvMinEnclosingCircle(current, &center, &radius);
		cvCircle(_image, cvPointFrom32f(center), radius, CV_RGB(255, 0, 0), 1, 8);
	}
	cvReleaseImage(&bin);
	cvReleaseMemStorage(&storage);
}
int main(int argc, char* argv[])
{
	IplImage *src = 0, *dst = 0,*dst2=0,*dst3=0;
	char *filename = argc == 2 ? argv[1] : "image0.jpg";

	src = cvLoadImage(filename);
	printf("[i] image: %s\n", filename);
	assert(src != 0);
	cvNamedWindow("src", 1);
	cvShowImage("src", src);
	dst = cvCloneImage(src);
	dst2 = cvCloneImage(src);
	dst3 = cvCloneImage(src);
	findcircle(dst);
	enclosingCircle(dst2);
	findpoly(dst3);
	cvNamedWindow("circle", 1);
	cvShowImage("circle", dst);
	cvNamedWindow("dst2",1);
	cvShowImage("dst2", dst2);
	cvNamedWindow("dst3", 1);
	cvShowImage("dst3", dst3);
	cvWaitKey(0);
	cvReleaseImage(&dst2);
	cvReleaseImage(&src);
	cvReleaseImage(&dst3);
	cvReleaseImage(&dst);
	cvDestroyAllWindows();
	return 0;


}


/*lesson 32.1*
/

IplImage *image = 0;
IplImage *gray = 0;
IplImage *bin = 0;
IplImage *dst = 0;
int main(int argc, char*argv[])
{
	char*filename = argc > 2 ? argv[1] : "image0.jpg";
	image = cvLoadImage(filename);
	printf("[i] image: %s\n", filename);
	assert(image != 0);
	gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	bin = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	dst = cvCloneImage(image);
	cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("bin", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("gray", CV_WINDOW_AUTOSIZE); 
	cvNamedWindow("dst", 1);
	cvCvtColor(image, gray, CV_RGB2GRAY);
	cvInRangeS(gray, cvScalar(40), cvScalar(150), bin);
	CvMemStorage*storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	int contoursCont = cvFindContours(bin, storage, &contours, sizeof(CvContour), 3,1, cvPoint(0, 0));
	for (CvSeq* seq0 = contours; seq0 != 0; seq0 = seq0->h_next)
	{
		cvDrawContours(dst, seq0, CV_RGB(255, 216, 0), CV_RGB(0, 0, 255), 0, 1, 8);
	}

	cvShowImage("image", image);
	cvShowImage("bin", bin);
	cvShowImage("dst", dst);
	cvShowImage("gray", gray);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&gray);
	cvReleaseImage(&bin);
	cvReleaseImage(&dst);
	cvDestroyAllWindows();
	return 0;
}

/*lesson 30.2* /
int main(int argc, char *argv[])
{
	IplImage *src=0, *dst=0,*dst1=0,*dst2=0,*dst3=0;
	char *filename = argc == 2 ? argv[1] : "image0.jpg";
	src=cvLoadImage(filename,1);
	printf("[i] image: %s", filename);
	assert(src != 0);
	cvNamedWindow("src", 1);
	cvShowImage("src", src);
	CvPoint2D32f srcQuad[4], dstQuad[4];
	CvMat* warp_matrix = cvCreateMat(3,3,CV_32FC1);
	dst = cvCloneImage(src);
	dst1 = cvCloneImage(src);
	dst2 = cvCloneImage(src);
	dst3 = cvCloneImage(src);

	srcQuad[0].x = 0;
	srcQuad[0].y = 0;
	srcQuad[1].x = src->width-1;
	srcQuad[1].y = 0;
	srcQuad[2].x = 0;
	srcQuad[2].y = src->height-1;
	srcQuad[3].x = src->width-1;
	srcQuad[3].y = src->height-1;

	dstQuad[0].x = src->width*0.05;
	dstQuad[0].y = src->height*0.33;
	dstQuad[1].x = src->width*0.9;
	dstQuad[1].y = src->height*0.25;
	dstQuad[2].x = src->width*0.2;
	dstQuad[2].y = src->height*0.7;
	dstQuad[3].x = src->width*0.8;
	dstQuad[3].y = src->height*0.9;


	cvGetPerspectiveTransform(srcQuad, dstQuad, warp_matrix);
	cvWarpPerspective(src,dst,warp_matrix);
	
	//cvRemap(src,dst1,);
	//cvTransform(src,dst2,warp_matrix,dstQuad2);
	cvGetQuadrangleSubPix(src,dst3,warp_matrix);

	cvNamedWindow("dst", 1);
	cvShowImage("dst", dst);
	cvNamedWindow("dst3", 1);
	cvShowImage("dst3", dst3);
	cvWaitKey(0);
	cvReleaseImage(&dst3);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseMat(&warp_matrix);
	cvDestroyAllWindows();
	return 0;

}

/*lesson 30 * /

void rotate(IplImage*_image, double _angle=90)
{
	CvMat *rot_mat = cvCreateMat(2,3,CV_32FC1);
	CvPoint2D32f center = cvPoint2D32f(_image->width / 2, _image->height / 2);
	double angle =_angle;
	double scale = 1;
	cv2DRotationMatrix(center, angle, scale, rot_mat);
	IplImage *Temp = 0;
	Temp = cvCreateImage(cvSize(_image->width,_image->height),_image->depth,_image->nChannels);
	cvWarpAffine(_image, Temp, rot_mat);
	cvCopy(Temp, _image);
	cvReleaseImage(&Temp);
	cvReleaseMat(&rot_mat);
}

int main(int argc, char*argv[])
{
	IplImage *src = 0, *dst = 0;
	char*filename = argc == 2 ? argv[1] : "image0.jpg";
	src = cvLoadImage(filename, 1);
	printf("[i] image: %s", filename);
	assert(src != 0);
	cvNamedWindow("src", 1);
	cvShowImage("src", src);
	CvPoint2D32f srcTri[3], dstTri[3];
	CvMat* rot_mat = cvCreateMat(2,3, CV_32FC1);
	CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);
	dst = cvCloneImage(src);
#if 1
	srcTri[0].x = 0;
	srcTri[0].y = 0;
	srcTri[1].x = src->width-1;
	srcTri[1].y = 0;
	srcTri[2].x = 0;
	srcTri[2].y = src->height-1;


	dstTri[0].x = src->width*0.0;
	dstTri[0].y = src->height*0.33;
	dstTri[1].x = src->width*0.85;
	dstTri[1].y = src->height*0.25;
	dstTri[2].x = src->width*0.15;
	dstTri[2].y = src->height*0.7;
	cvGetAffineTransform(srcTri, dstTri, warp_mat);

	cvWarpAffine(src, dst, warp_mat);

#endif
	cvCopy(dst, src);

#if 1
	CvPoint2D32f center = cvPoint2D32f(src->width / 2, src->height / 2);
	double angle = -60.0;
	double scale = 0.7;
	cv2DRotationMatrix(center,angle, scale,rot_mat);

	cvWarpAffine(src, dst, rot_mat);
#endif
	cvNamedWindow("affine", 1);
	cvShowImage("affine",dst);
	
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseMat(&rot_mat);
	cvReleaseMat(&warp_mat);

	cvDestroyAllWindows();
	return 0;
}
   




/*Lesson 29* /
int main(int argc, char* argv[])
{
	IplImage *src = 0, *dst = 0, *dst2 = 0, *dst3 = 0;
	char* filename = argc >= 2 ? argv[1] : "image0.jpg";
	src = cvLoadImage(filename,0);
	printf("[i] image: %s\n",filename);
	assert(src != 0);
	cvNamedWindow("src",1);
	cvShowImage("src", src);
	dst = cvCreateImage(cvSize(src->width+1, src->height+1),IPL_DEPTH_64F,1);
	dst2 = cvCreateImage(cvSize(src->width+1, src->height+1),IPL_DEPTH_64F,1);
	dst3 = cvCreateImage(cvSize(src->width+1, src->height+1),IPL_DEPTH_64F,1);
	cvIntegral(src, dst, dst2, dst3);
	cvNamedWindow("dst", 1);
	cvShowImage("dst", dst);
	cvNamedWindow("dst2", 1);
	cvShowImage("dst2", dst2);
	cvNamedWindow("dst3", 1);
	cvShowImage("dst3", dst3);
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	cvReleaseImage(&dst3);
	cvDestroyAllWindows();
	return 0;


}

/*lesson28.3* /
int main(int argc, char* argv[])
{
	IplImage* image = 0;
	char* filename = argc >=2 ? argv[1] : "image0.jpg";
	image = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	assert(image != 0);
	printf("[i] image: %s\n", filename);
	IplImage *src = cvLoadImage(filename);
	CvMemStorage* storage = cvCreateMemStorage(0);
	cvSmooth(image, image, CV_GAUSSIAN, 5, 5);
	CvSeq* results = cvHoughCircles(image, storage, CV_HOUGH_GRADIENT, 3, image->width / 5);
	for (int i = 0; i < results->total; i++)
	{
		float *p = (float*)cvGetSeqElem(results, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		cvCircle(src, pt, cvRound(p[2]), CV_RGB(0xff, 0, 0));
	}
	cvNamedWindow("circle", 1);
	cvShowImage("circle", src);
	cvWaitKey(0);

	cvReleaseMemStorage(&storage);
	cvReleaseImage(&src);
	cvReleaseImage(&image);
	cvDestroyAllWindows();
	return 0;	
	


}


/* lesson 28.2 original* /
int main(int argc, char* argv[])
{
	IplImage* src = 0;
	IplImage* dst = 0;
	IplImage* color_dst = 0;

	// имя картинки задаётся первым параметром
	char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
	// получаем картинку (в градациях серого)
	src = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

	if (!src){
		printf("[!] Error: cant load image: %s \n", filename);
		return -1;
	}

	printf("[i] image: %s\n", filename);


	// хранилище памяти для хранения найденных линий
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i = 0;


	dst = cvCreateImage(cvGetSize(src), 8, 1);
	color_dst = cvCreateImage(cvGetSize(src), 8, 3);

	// детектирование границ
	cvCanny(src, dst, 50, 200, 3);

	// конвертируем в цветное изображение
	cvCvtColor(dst, color_dst, CV_GRAY2BGR);

	// нахождение линий
	lines = cvHoughLines2(dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 50, 50, 10);

	// нарисуем найденные линии
	for (i = 0; i < lines->total; i++){
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
		cvLine(color_dst, line[0], line[1], CV_RGB(255, 0, 0), 3, CV_AA, 0);
	}

	// показываем
	cvNamedWindow("Source", 1);
	cvShowImage("Source", src);

	cvNamedWindow("Hough", 1);
	cvShowImage("Hough", color_dst);

	// ждём нажатия клавиши
	cvWaitKey(0);

	// освобождаем ресурсы
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&color_dst);
	cvDestroyAllWindows();
	return 0;
}

/*lesson 28.1original
void houghLine(IplImage* original, float accuracy = 0.1)
{
	assert(original != 0);

	IplImage *src = 0, *rgb = 0;
	IplImage *bin = 0;
	IplImage *phase = 0;

	src = cvCloneImage(original);

	// заведём цветную картинку
	rgb = cvCreateImage(cvGetSize(src), 8, 3);
	cvConvertImage(src, rgb, CV_GRAY2BGR);

	// бинарная картинка - для контуров
	bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCanny(src, bin, 50, 200);

	cvNamedWindow("bin", 1);
	cvShowImage("bin", bin);

	// максимальное расстояние от начала координат - это длина диагонали
	int RMax = cvRound(sqrt((double)(src->width*src->width + src->height*src->height)));

	// картинка для хранения фазового пространства Хафа (r, f)
	// 0 < r < RMax
	// 0 < f < 2*PI
	phase = cvCreateImage(cvSize(RMax, 180), IPL_DEPTH_16U, 1);
	cvZero(phase);

	int x = 0, y = 0, r = 0, f = 0;
	float theta = 0;

	// пробегаемся по пикселям изображения контуров
	for (y = 0; y<bin->height; y++){
		uchar* ptr = (uchar*)(bin->imageData + y * bin->widthStep);
		for (x = 0; x<bin->width; x++){
			if (ptr[x]>0){ // это пиксель контура?
				// рассмотрим все возможные прямые, которые могут 
				// проходить через эту точку
				for (f = 0; f<180; f++){ //перебираем все возможные углы наклона
					short* ptrP = (short*)(phase->imageData + f * phase->widthStep);
					for (r = 0; r<RMax; r++){ // перебираем все возможные расстояния от начала координат
						theta = f*CV_PI / 180.0; // переводим градусы в радианы

						// Если решение уравнения достаточно хорошее (точность больше заданой)
						if (abs(((y)*sin(theta) + (x)*cos(theta)) - r) < accuracy){
							ptrP[r]++; // увеличиваем счетчик для этой точки фазового пространства.
						}
					}
				}
			}
		}
	}

	cvNamedWindow("phase", 1);
	cvShowImage("phase", phase);

	// увеличим фазовую картинку
	IplImage* phaseImage = cvCreateImage(cvSize(phase->width * 3, phase->height * 3), IPL_DEPTH_16U, 1);
	cvResize(phase, phaseImage);

	cvNamedWindow("phaseImage", 1);
	cvShowImage("phaseImage", phaseImage);

	// Выбираем точку фазового пространства которая набрала наибольшее число попаданий
	unsigned int MaxPhaseValue = 0;
	float Theta = 0;
	int R = 0;
	for (f = 0; f<180; f++){ //перебираем все возможные углы наклона
		short* ptrP = (short*)(phase->imageData + f * phase->widthStep);
		for (r = 0; r<RMax; r++){ // перебираем все возможные расстояния от начала координат
			if (ptrP[r]>MaxPhaseValue){
				MaxPhaseValue = ptrP[r];
				Theta = f;
				R = r;
			}
		}
	}

#if 1
	printf("[M] %d\n", MaxPhaseValue);

	// нормировка
	float scaler = 0xFFFFFFFF / (float)MaxPhaseValue;
	for (y = 0; y<phaseImage->height; y++){
		short* ptr = (short*)(phaseImage->imageData + y * phaseImage->widthStep);
		for (x = 0; x<phaseImage->width; x++){
			ptr[x] *= scaler;
		}
	}
	cvNamedWindow("phaseImage2", 1);
	cvShowImage("phaseImage2", phaseImage);
#endif

	// Рисуем линию по точкам для  R, Teta которые получили в результате преобразования
	Theta = Theta*CV_PI / 180.0;
	for (y = 0; y<rgb->height; y++){
		uchar* ptr = (uchar*)(rgb->imageData + y * rgb->widthStep);
		for (x = 0; x<rgb->width; x++){
			if (cvRound(((y)* sin(Theta) + (x)* cos(Theta))) == R){
				ptr[3 * x] = 0;
				ptr[3 * x + 1] = 0;
				ptr[3 * x + 2] = 255;
			}
		}
	}

	cvNamedWindow("line", 1);
	cvShowImage("line", rgb);

	// освобождаем ресурсы
	cvReleaseImage(&src);
	cvReleaseImage(&rgb);

	cvReleaseImage(&bin);
	cvReleaseImage(&phase);
	cvReleaseImage(&phaseImage);
}

int main(int argc, char* argv[])
{
	IplImage *original = 0;

	// имя картинки задаётся первым параметром
	char* filename = argc >= 2 ? argv[1] : "image0.jpg";
	// получаем картинку
	original = cvLoadImage(filename, 0);

	printf("[i] image: %s\n", filename);
	assert(original != 0);

	// покажем изображения
	cvNamedWindow("original", 1);
	cvShowImage("original", original);

	houghLine(original);

	cvWaitKey(0);

	cvReleaseImage(&original);

	// удаляем окна
	cvDestroyAllWindows();
	return 0;
}

/*lesson 28.2* /
int main(int argc, char*argv[])
{
	IplImage *src;
	IplImage* dst;
	IplImage *color;

	char*filename = argc == 2 ? argv[1] : "image0.jpg";
	src = cvLoadImage(filename,CV_LOAD_IMAGE_GRAYSCALE);
	assert(src != 0);
	printf("[i] image:%s\n", filename);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i = 0;
	dst = cvCreateImage(cvGetSize(src), 8,1);
	color = cvCreateImage(cvGetSize(src), 8, 1);
	cvCanny(src, dst, 50, 200, 3);
	cvCvtColor(dst, color, CV_GRAY2BGR);
	lines = cvHoughLines2(dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 50, 50, 10);
	for (i = 0; i < lines->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, 1);
		cvLine(color,line[0],line[1],CV_RGB(255,0,0),3,CV_AA,0);
	}
	cvNamedWindow("source", 1);
	cvShowImage("source", src);
	cvNamedWindow("hough", 1);
	cvShowImage("hough", color);
	cvWaitKey(0);
	cvReleaseMemStorage(&storage);

	cvReleaseImage(&src);
	cvReleaseImage(&color);
	cvReleaseImage(&dst);
	cvDestroyAllWindows();
	return 0;




}

/*lesson 28.1 * /

void houghLine(IplImage* original, float accuracy = 0.1)
{
	assert(original != 0);
	IplImage *src = 0, *rgb = 0;
	IplImage *bin = 0;
	IplImage *phase = 0;
	src = cvCloneImage(original);
	rgb = cvCreateImage(cvGetSize(src),8,3);
	cvConvertImage(src, rgb, CV_BayerGR2BGR);
	bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCanny(src, bin, 50, 200);
	cvNamedWindow("bin",1);
	cvShowImage("bin", bin);
	int Rmax = cvRound(sqrt((double)(src->width*src->width + src->height*src->height)));
	phase = cvCreateImage(cvSize(Rmax, 180), IPL_DEPTH_16U, 1);
	cvZero(phase);
	int x = 0, y = 0, r = 0, f=0;
	float theta = 0;
	for (y = 0; y < bin->height; y++)
	{
		uchar* ptr = (uchar*)(bin->imageData + y*bin->widthStep);
		for (x = 0; x < bin->width; x++)
		{
			if (ptr[x]>0)
			{
				for (f = 0; f < 180; f++)
				{
					short*ptrP = (short*)(phase->imageData + f*phase->widthStep);
					for (r = 0; r < Rmax; r++)
					{
						theta = f*CV_PI / 180.0;
						if (abs(((y)*sin(theta) + (x)*cos(theta)) - r) < accuracy)
						{
							ptrP[r]++;
						}
					}
				}
			}
		}

	}
	cvNamedWindow("phase", 1);
	cvShowImage("phase", phase);
	IplImage*phaseImage = cvCreateImage(cvSize(phase->width * 3, phase->height * 3), IPL_DEPTH_16U, 1);
	cvResize(phase, phaseImage);
	cvNamedWindow("phaseImage", 1);
	cvShowImage("phaseImage", phaseImage);
	unsigned int MaxPhaseValue = 0;
	float Theta = 0;
	int R = 0;
	for (f = 0; f < 180; f++)
	{
		short *ptrP = (short*)(phase->imageData + f*phase->widthStep);
		for (r = 0; r < Rmax; r++)
		{
			if (ptrP[r]>MaxPhaseValue)
			{
				MaxPhaseValue = ptrP[r];
				Theta = r;
				R = r;
			}
		}
	}
#if 1
	printf("[M] %d\n", MaxPhaseValue);
	float scaler = 0xFFFFFFFF / (float)MaxPhaseValue;
	for (y = 0; y < phaseImage->height; y++)
	{
		short *ptr = (short*)(phaseImage->imageData + y*phaseImage->widthStep);
		for (x = 0; x < phaseImage->width; x++)
		{
			ptr[x] *= scaler;
		}
	}
	cvNamedWindow("phaseImage2", 1);
	cvShowImage("phaseImage2", phaseImage);
#endif
	Theta = Theta*CV_PI / 180.0;
	for (y = 0; y < rgb->height; y++)
	{
		uchar*ptr = (uchar*)(rgb->imageData + y*rgb->widthStep);
		for (x = 0; x < rgb->width; x++)
		{
			if (cvRound(((y)*sin(Theta) + (x)*cos(Theta))) == R)
			{
				ptr[3 * x] = 0;
				ptr[3 * x + 1] = 0;
				ptr[3 * x + 2] = 255;
			}
		}
	}
	cvNamedWindow("line", 1);
	cvShowImage("line",rgb);
	cvReleaseImage(&src);
	cvReleaseImage(&rgb);
	cvReleaseImage(&bin);
	cvReleaseImage(&phase);
	cvReleaseImage(&phaseImage);
}

int main(int argc, char *argv[])
{
	IplImage* original=0;
	char* filename = argc == 2 ? argv[1] : "image9.jpg";
	original = cvLoadImage(filename, 0);
	printf("[i] image : %s\n", filename);
	assert(original != 0);
	cvNamedWindow("original", 1);
	cvShowImage("original", original);
	houghLine(original);
	cvWaitKey(0);
	cvReleaseImage(&original);
	cvDestroyAllWindows();
	return 0;
}





/*lesson 27.2 border kenny* /
int main(int argc, char* argv[])
{
	IplImage *src = 0, *dst = 0, *dst2 = 0;
	char *filename = argc >= 2 ? argv[1] : "image0.jpg";
	src = cvLoadImage(filename,1);
	printf("[i] image: %s\n", filename);
	assert(src != 0);
	cvNamedWindow("original",1);
	cvShowImage("original", src);
	dst2 = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	/*cvCvtColor(src, dst2, CV_RGB2GRAY);* /
	cvCanny(src, dst2, 50, 200);
	cvNamedWindow("bin", 1);
	cvShowImage("bin",dst2);
	cvSub(src, dst2, dst2);
	cvNamedWindow("sub", 1);
	cvShowImage("sub", dst2);
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst2);
	cvReleaseImage(&dst);

	cvDestroyAllWindows();
	return 0;
}


/*lesson 27.1 border kenny* /

IplImage* image = 0; 
IplImage* gray = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{	
	char* filename = argc == 2 ? argv[1] : "Image0.jpg";
	image = cvLoadImage(filename, 1);
	printf("[i] image: %s\n :", filename);
	assert(image != 0);
	gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	dst = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("gray", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("canny", CV_WINDOW_AUTOSIZE);
	cvCvtColor(image, gray, CV_RGB2GRAY);
	cvCanny(gray, dst, 10, 100,3);
	cvShowImage("original", image);
	cvShowImage("gray", gray);
	cvShowImage("canny", dst);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&gray);
	cvReleaseImage(&dst);
	cvDestroyAllWindows();

	return 0;


}
 
/*lesson 26.2 laplace* /
IplImage* image = 0; 
IplImage* dst = 0;
IplImage* dst2 = 0;
int main(int argc, char* argv[])
{
	char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
	image = cvLoadImage(filename, 1);
	dst = cvCreateImage(cvGetSize(image), IPL_DEPTH_16S, image->nChannels);
	dst2 = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);
	printf("[i] image: %s\n ", filename);
	assert(image != 0);
	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("laplas", CV_WINDOW_AUTOSIZE);
	int aperture = argc == 3 ? atoi(argv[2]) : 3;
	cvLaplace(image, dst, aperture);
	cvConvertScale(dst, dst2);
	cvShowImage("original", image);
	cvShowImage("laplas", dst2);
	cvWaitKey(0);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	cvReleaseImage(&image);
	cvDestroyAllWindows();
	return 0;

}*/

