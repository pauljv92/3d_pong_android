#ifndef GAME_H
#define GAME_H

#include <android/log.h>
#include <stdlib.h>
#include <string.h>

#define LOGV(TAG,...) __android_log_print(ANDROID_LOG_VERBOSE, TAG,__VA_ARGS__)
#define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG  , TAG,__VA_ARGS__)
#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO   , TAG,__VA_ARGS__)
#define LOGW(TAG,...) __android_log_print(ANDROID_LOG_WARN   , TAG,__VA_ARGS__)
#define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR  , TAG,__VA_ARGS__)

int is_host;
char *host_ip;

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

void view_init();
void view_resize(int width, int height);
void view_update(float dt);
void view_render(float dt);
void view_touch(float x, float y);

void logic_init();
void logic_update(float dt);

#endif
