#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>


using namespace std;
using namespace cv;
int main(){

VideoCapture cap(0);
Mat img;
while (true){
 cap.read(img);
 CascadeClassifier facecascade;
 facecascade.load("haarcascade_frontalface_default.xml");
if (facecascade.empty()) cout<<"Empty";

vector<Rect> faces;
facecascade.detectMultiScale(img,faces,1.1,10);
for (int i=0;i<faces.size();i++){
    rectangle(img,faces[i].tl(),faces[i].br(),Scalar(0,250,0),2);
}

imshow("Face Detection",img);
waitKey(1);
}



return 0;
}