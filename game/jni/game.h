#ifndef GAME_H
#define GAME_H

#ifndef NOT_ANDROID
#include <android/log.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOGV(TAG,...) __android_log_print(ANDROID_LOG_VERBOSE, TAG,__VA_ARGS__)
#define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG  , TAG,__VA_ARGS__)
#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO   , TAG,__VA_ARGS__)
#define LOGW(TAG,...) __android_log_print(ANDROID_LOG_WARN   , TAG,__VA_ARGS__)
#define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR  , TAG,__VA_ARGS__)

void die(char *message);
#define die2(TAG, ...) { char die_buf[256];	\
	sprintf(die_buf, TAG, __VA_ARGS__);	\
	die(die_buf); }

extern int game_state;
extern char *death_message;

extern int is_host;
extern char *ip;

extern float player_x; // read only
extern float player_y; // read only
extern float enemy_x; // write me
extern float enemy_y; // write me

extern float ball_x; // write me
extern float ball_y; // write me
extern float ball_z; // write me

extern float real_player_x;
extern float real_player_y;
extern float real_enemy_x;
extern float real_enemy_y;

void view_init();
void view_cleanup();
void view_resize(int width, int height);
void view_update(float dt);
void view_render(float dt);
void view_touch(float x, float y);

void logic_init();
void logic_cleanup();
void logic_update(float dt);

#endif
