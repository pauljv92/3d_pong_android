#include "game.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int GAME_PORT = 6969;

int sockfd;
struct sockaddr_in serv_addr;

void logic_init() {
    if (is_host) {
	host_init();
    } else {
	client_init();
    }
}

void logic_cleanup() {
}

void host_init() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(GAME_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    // start a server thread
}

void client_init() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(GAME_PORT);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr) != 0) {
	die("inet_pton");
	return;
    }

    // start a client thread
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
