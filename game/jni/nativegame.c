#include <jni.h>
#include "game.h"

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_init(
    JNIEnv *env, jclass cls) {
    init();
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_resize(
    JNIEnv *env, jobject obj, jint w, jint h) {
    resize(w, h);
}


JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_touch(
    JNIEnv *env, jobject obj, jfloat x, jfloat y) {
    touch(x, y);
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_accelerometer(
    JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z) {
    accelerometer(x, y, z);
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_render(
    JNIEnv *env, jobject obj, jfloat dt) {
    render(dt);
}

JNIEXPORT float JNICALL Java_com_honorsgame_NativeGame_playerx(
    JNIEnv *env, jobject obj) {
    return player_x;
}

JNIEXPORT float JNICALL Java_com_honorsgame_NativeGame_playery(
    JNIEnv *env, jobject obj) {
    return player_y;
}
