/*
 * Copyright (C) 2012 Martin Storsjo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   // <-- AÑADIDO para la función open()
#include <unistd.h>  // <-- AÑADIDO para la función close()
#include "log.h"
#include "libusb.h"
#include "rtl-sdr.h"

// JNI OnLoad
static JavaVM* java_vm;
static jclass libusb_class;

// UsbDeviceConnection
static jfieldID field_context;

// usb_device
static jfieldID field_descriptor;

struct usb_device* android_java_to_usb_device(JNIEnv* env, jobject connection) {
    if (connection == NULL)
        return NULL;
    return (struct usb_device*)(intptr_t)(*env)->GetIntField(env, connection, field_context);
}

int android_java_usbdevice_open(const char* pathname, int mode) {
    JNIEnv* env;
    int ret;
    int needs_detach = 0;
    if ((*java_vm)->GetEnv(java_vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        if ((*java_vm)->AttachCurrentThread(java_vm, &env, NULL) != JNI_OK)
            return -1;
        needs_detach = 1;
    }

    jstring path_str = (*env)->NewStringUTF(env, pathname);
    jmethodID method_open = (*env)->GetStaticMethodID(env, libusb_class, "open", "(Ljava/lang/String;)I");
    int retval = (*env)->CallStaticIntMethod(env, libusb_class, method_open, path_str);
    (*env)->DeleteLocalRef(env, path_str);

    if (needs_detach)
        (*java_vm)->DetachCurrentThread(java_vm);

    return retval; // <-- CORREGIDO: Devolvemos el valor obtenido
}

void android_java_usbdevice_close(int fd, struct usb_device* device) {
    JNIEnv* env;
    int needs_detach = 0;
    if ((*java_vm)->GetEnv(java_vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        if ((*java_vm)->AttachCurrentThread(java_vm, &env, NULL) != JNI_OK)
            return;
        needs_detach = 1;
    }
    jmethodID method_close = (*env)->GetStaticMethodID(env, libusb_class, "close", "(I)V");
    (*env)->CallStaticVoidMethod(env, libusb_class, method_close, fd);

    if (needs_detach)
        (*java_vm)->DetachCurrentThread(java_vm);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    java_vm = vm;
    if ((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_6) != JNI_OK)
        return -1;

    jclass temp_class = (*env)->FindClass(env, "com/sdr/librtlsdr/Libusb");
    if (!temp_class)
        return -1;
    libusb_class = (*env)->NewGlobalRef(env, temp_class);
    field_context = (*env)->GetFieldID(env, libusb_class, "mNativeContext", "I");

    temp_class = (*env)->FindClass(env, "android/hardware/usb/UsbDevice");
    jclass local_class = (*env)->NewGlobalRef(env, temp_class);
    field_descriptor = (*env)->GetFieldID(env, local_class, "mLegacyDeviceAddress", "I");

    usb_device_set_open_close_func(android_java_usbdevice_open, android_java_usbdevice_close);
    return JNI_VERSION_1_6;
}
