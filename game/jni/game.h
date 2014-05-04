#ifndef GAME_H
#define GAME_H

#include <android/log.h>

#define LOGV(TAG,...) __android_log_print(ANDROID_LOG_VERBOSE, TAG,__VA_ARGS__)
#define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG  , TAG,__VA_ARGS__)
#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO   , TAG,__VA_ARGS__)
#define LOGW(TAG,...) __android_log_print(ANDROID_LOG_WARN   , TAG,__VA_ARGS__)
#define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR  , TAG,__VA_ARGS__)

float player_x;
float player_y;

float player_target_x;
float player_target_y;

float comp_x;
float comp_y;

void init();
void resize(int width, int height);
void touch(float x, float y);
void accelerometer(float x, float y, float z);
void render(float dt);

#endif
