#include "game.h"

void logic_init() {
    if (is_host) {
	LOGI("honorsgame", "Am the host!\n");
    } else {
	LOGI("honorsgame", "Client: Got the ip address! %s\n", host_ip);
    }
}

int ball_dir = -1;

void logic_update(float dt) {
    // mirror the player
    enemy_x = -player_x;
    enemy_y = -player_y;

    // some of that ball logic
    ball_x = 0;
    ball_y = 0;
    ball_z += ball_dir * dt * 3;
    if (ball_z < -5) {
	ball_dir = 1;
    }
    if (ball_z > 0) {
	ball_dir = -1;
    }
}
