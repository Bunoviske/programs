set(OpenCV_STATIC ON)
set(OpenCV_DIR ${OPENCV_HOME}/sdk/native/jni)
find_package (OpenCV REQUIRED)

target_link_libraries(native-lib ${OpenCV_LIBS})