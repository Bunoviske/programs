//
// Created by bruno on 12/10/18.
//

#include "opencv.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_example_bruno_testeopencv3_11_10_MainActivity_opencvTeste(JNIEnv *env, jobject instance) {

// TODO
    cv::Mat OI = cv::Mat(10,10,CV_8UC1);
    opencv Obj;
    Obj.ola = OI.clone();

}