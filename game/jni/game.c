#include <jni.h>
#include "game.h"

int game_state = 0;
char *death_message = NULL;

int is_host;
char *ip;

float player_x;
float player_y;
float enemy_x;
float enemy_y;

float real_player_x;
float real_player_y;
float real_enemy_x;
float real_enemy_y;

float ball_x;
float ball_y;
float ball_z;

void die(char *message) {
    if (game_state == 0) {
	game_state = -1;
	death_message = strdup(message);
    }
}

JNIEXPORT void JNICALL Java_com_honorsgame_NativeGame_init(
    JNIEnv *env, jclass cls, jstring j_ip) {

    const char *ip2 = (*env)->GetStringUTFChars(env, j_ip, 0);
    if (ip2 != NULL) {
	is_host = 0;
	ip = strdup(ip2);
    } else {
	is_host = 1;
	ip = NULL;
    }

    logic_init();
    view_init();

    (*env)->ReleaseStringUTFChars(env, j_ip, ip2);
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
    if (game_state == 0) {
	logic_update(dt);
	view_update(dt);
	view_render(dt);
    }
    if (game_state == -1) {
	logic_cleanup();
	view_cleanup();
	game_state = -2;
    }
}

JNIEXPORT jstring JNICALL Java_com_honorsgame_NativeGame_death(
    JNIEnv *env, jobject obj) {
    jstring result = (*env)->NewStringUTF(env, death_message);
    return result;
}

JNIEXPORT float JNICALL Java_com_honorsgame_NativeGame_playerx(
    JNIEnv *env, jobject obj) {
    return real_player_x;
}

JNIEXPORT float JNICALL Java_com_honorsgame_NativeGame_playery(
    JNIEnv *env, jobject obj) {
    return real_player_y;
}
