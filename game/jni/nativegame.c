#include <jni.h>
#include "game.h"

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_init(
    JNIEnv *env, jclass cls, int is_host, jstring host_ip) {

    is_host = is_host;
    host_ip = strdup((*env)->GetStringUTFChars(env, host_ip, 0));

    logic_init();
    view_init();
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_resize(
    JNIEnv *env, jobject obj, jint w, jint h) {
    view_resize(w, h);
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_touch(
    JNIEnv *env, jobject obj, jfloat x, jfloat y) {
    view_touch(x, y);
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_render(
    JNIEnv *env, jobject obj, jfloat dt) {
    logic_update(dt);
    view_update(dt);
    view_render(dt);
}

JNIEXPORT float JNICALL Java_com_honorsgame_NativeGame_playerx(
    JNIEnv *env, jobject obj) {
    return real_player_x;
}

JNIEXPORT float JNICALL Java_com_honorsgame_NativeGame_playery(
    JNIEnv *env, jobject obj) {
    return real_player_y;
}
