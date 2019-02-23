#include <jni.h>
#include <string>
#include <stdio.h>


using namespace std;

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_bruno_mvpdiabetesnew_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());

}
