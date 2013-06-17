/*
Face Detection code Using OPENCV

Xikui Wang 

Date: 2013.06.18
*/
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace std;

void faceDetection(CascadeClassifier cascade,Mat faceIMG,int faceId)
{
	Mat grayIMG;
	ostringstream convert;
	string faceIdS;
	convert<<faceId;
	faceIdS = convert.str();
	convert.clear();

	cvtColor(faceIMG,grayIMG,CV_BGR2GRAY);
	equalizeHist(grayIMG,grayIMG);

	vector<Rect> faces;
	cascade.detectMultiScale(grayIMG,faces,1.2,3);

	for (int iter1 = 0; iter1<faces.size();iter1++){
		Rect r = faces[iter1];
		Mat face0 = Mat(faceIMG,faces[iter1]);
		//rectangle(faceIMG,Point(r.x,r.y),Point(r.x+r.width,r.y+r.height),CV_RGB(0,255,0));
		convert<<iter1;
		string iFaceId = faceIdS+convert.str();
		convert.clear();
		imshow(iFaceId,face0);
		puts("get!!");
	}
}

int main()
{

	CascadeClassifier cascade;
	char FILENAME[30];
	if (!cascade.load("haarcascade_frontalface_alt.xml")){
		cout<<"cascade Load Error!"<<endl;
		return -1;
	}
	for (int iter1=0;iter1<5;iter1++){
		sprintf(FILENAME,"resource/face%d.jpg",iter1+1);
		printf("%s\n",FILENAME);
		Mat faceIMG = imread(FILENAME);
		///printf("%d\n",faceIMG.size());
		if (faceIMG.empty()){
			cout<<"Face reading error!"<<endl;
			return -1;
		}
		faceDetection(cascade,faceIMG,iter1);
	}
	waitKey(0);

	return 0;
}