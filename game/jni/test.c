#define NOT_ANDROID

#include "game.h"
#include "game.c"
#include "logic.c"

int main(int argc, char **argv) {
    int ppid = getpid();
    int pid;

    if ((pid = fork()) == 0) {
	// server
	is_host = 1;
	ip = NULL;

	logic_init();
	while (1) {
	    usleep(100 * 1000); // 100 milliseconds
	    logic_update(0.1f);
	    printf("server: player_xy(%f, %f)\t"
		   "        enemy_xy(%f, %f)\t"
		   "        ball_xyz(%f, %f, %f)\n",
		   player_x, player_y,
		   enemy_x, enemy_y,
		   ball_x, ball_y, ball_z);
	    if (death_message != NULL) {
		printf("Server Died: %s\n", death_message);
		kill(ppid, 9);
		exit(1);
	    }
	}
    } else {
	// client
	is_host = 0;
	ip = "127.0.0.1";

	logic_init();
	while (1) {
	    usleep(100 * 1000); // 100 milliseconds
	    logic_update(0.1f);
	    printf("client: player_xy(%f, %f)\t"
		   "        enemy_xy(%f, %f)\t"
		   "        ball_xyz(%f, %f, %f)\n",
		   player_x, player_y,
		   enemy_x, enemy_y,
		   ball_x, ball_y, ball_z);
	    if (death_message != NULL) {
		printf("Client Died: %s\n", death_message);
		kill(pid, 9);
		exit(1);
	    }
	}
    }
}
