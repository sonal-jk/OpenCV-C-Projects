#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

 Mat img;
 vector<vector<int>> newpoints;
vector<vector<int>> colors={{90,71,88,123,182,119}//blue
,{38,60,66,80,166,209}//green
,{0,145,171,179,255,255}//orange
//,{16,0,23,179,96,109}//purple
//,{13,180,125,137,255,238}//yellow
};
vector<Scalar> colorvalues={{255,0,0}//blue
,{0,255,0}//green
,{31,104,255}//orange
//,{255,0,255}//purple
//,{0,255,255}//yellow
};


Point getContours( Mat imgDil){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgDil,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	//drawContours(img,contours,-1,Scalar(255,0,255),2);
     vector<vector<Point>> conpoly(contours.size());
        vector<Rect> boundReact(contours.size());
        Point mypoint(0,0);

	for (int i=0;i<contours.size();i++){
		int area=contourArea(contours[i]);
		cout<<area<<endl;
        
       
        string obbjType;
        if (area>1000){
            float peri=arcLength(contours[i],true);
            approxPolyDP(contours[i],conpoly[i],0.02*peri,true);
            cout<<conpoly[i].size()<<endl;
            boundReact[i]=boundingRect(conpoly[i]);
            mypoint.x=boundReact[i].x+boundReact[i].width/2;
            mypoint.y=boundReact[i].y;

            drawContours(img,conpoly,i,Scalar(255,0,255),2);
            rectangle(img,boundReact[i].tl(),boundReact[i].br(),Scalar(0,255,0),5);
            
        }
        
         	}
return mypoint;
}


vector<vector<int>> findColor(Mat img){
    Mat imgHSV;
    cvtColor(img,imgHSV,COLOR_BGR2HSV);
    for (int i=0;i<colors.size();i++){
        Scalar lower(colors[i][0],colors[i][1],colors[i][2]);
        Scalar upper(colors[i][3],colors[i][4],colors[i][5]);
        Mat mask;
        inRange(imgHSV,lower,upper,mask);
       imshow(to_string(i),mask);
       Point mypoints=getContours(mask);
       if (mypoints.x !=0 && mypoints.y!=0) newpoints.push_back({mypoints.x,mypoints.y,i});

    }
    return newpoints;

}

void drawOnCannvas( vector<vector<int>> newpoints,vector<Scalar> colorvalues){
    for (int i=0;i<newpoints.size();i++){
        circle(img,Point((newpoints[i][0]),newpoints[i][1]),10,colorvalues[newpoints[i][2]],FILLED);

    }

}


int main(){
    VideoCapture cap(0);
   
    while (true){
        cap.read(img);
        newpoints=findColor(img);
        drawOnCannvas(newpoints,colorvalues);
        imshow("Virtual Painter",img);
        waitKey(1);
        }
    
    return 0;
}