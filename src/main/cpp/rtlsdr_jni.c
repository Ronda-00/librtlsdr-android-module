#include <jni.h>
#include <android/log.h>
#include "include/rtl-sdr.h"

#define LOG_TAG "RTLSDR_JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

JNIEXPORT jint JNICALL
Java_com_sdr_librtlsdr_SdrDriver_getDeviceCount(JNIEnv *env, jobject thiz) {
    int count = rtlsdr_get_device_count();
    LOGI("Device count: %d", count);
    return count;
}

JNIEXPORT jstring JNICALL
Java_com_sdr_librtlsdr_SdrDriver_getDeviceName(JNIEnv *env, jobject thiz, jint index) {
    const char* name = rtlsdr_get_device_name(index);
    if (name) {
        LOGI("Device name: %s", name);
        return (*env)->NewStringUTF(env, name);
    }
    return (*env)->NewStringUTF(env, "Unknown");
}

JNIEXPORT jint JNICALL
Java_com_sdr_librtlsdr_SdrDriver_openDevice(JNIEnv *env, jobject thiz, jint index) {
    rtlsdr_dev_t *dev = NULL;
    int result = rtlsdr_open(&dev, index);
    LOGI("Open device result: %d", result);
    return result;
}

JNIEXPORT jint JNICALL
Java_com_sdr_librtlsdr_SdrDriver_closeDevice(JNIEnv *env, jobject thiz) {
    // Simplificado para el test
    LOGI("Close device called");
    return 0;
}
