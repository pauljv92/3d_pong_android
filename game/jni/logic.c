#include "game.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

const int GAME_PORT = 6967;
int sockfd, connfd;
struct sockaddr_in serv_addr, client;
pthread_t worker;
pthread_mutex_t enemy_mutex,ball_mutex;

void host_init();
void client_init();

void logic_init() 
{
    if (is_host) 
    {
	host_init();
    } 
    else 
    {
	client_init();
    }
}

void logic_cleanup(){
}

void update_enemy_coord(float x, float y)
{
    pthread_mutex_lock(&enemy_mutex);
    enemy_x = x;
    enemy_y = y;
    pthread_mutex_unlock(&enemy_mutex);
    
}
void update_ball_coord(float x, float y, float z)
{
    pthread_mutex_lock(&ball_mutex);
    ball_x = x;
    ball_y = y;
    ball_z = z;
    pthread_mutex_unlock(&ball_mutex);
}

void* server_thread(void* in)
{   
    char client_message[1000], reply[1000];
    int read_size;
    //   int c;

    listen(sockfd,3);
    //Accept and incoming connection
    puts("Waiting for incoming connections...\n");
    
    while (1) 
    {
	puts("THIS IS FUCKING AMAZING!!!!!");
	connfd = accept(sockfd, (struct sockaddr*)NULL, NULL);
	
	if(connfd < 0)
	{
	    puts("FAILEDDDDDDDDDDDDDDDDDD");
	    die("Problem accepting connection. \n");
	    continue;
	} 
	else
	{       
	    puts("Connection accepted. \n");
	    //Receive a message from client
	    while( (read_size = recv(connfd , client_message , 2000 , 0)) > 0 )
	    {
		printf("This is the client's message: %s\n",client_message);
		int n = sprintf(reply, "%f,%f,%f,%f,%f \n", player_x, player_y, ball_x, ball_y, ball_z);
		write(connfd , reply , n);
	    }
	    if(read_size == 0)
	    {
		puts("Client disconnected \n");
		fflush(stdout);
	    }
	    else if(read_size == -1)
	    {
		puts("FAILEDDDDDDDDDDDDDDDDDD");
		perror("recv failed \n");
	    }
	}
    }
}

void host_init()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(GAME_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)))
    {
	perror("bind failed. Error");
    }
    puts("Bind done");

    // start a server thread
    pthread_create(&worker, (void*) NULL, server_thread, NULL);
    //pthread_join(worker,NULL);
}

void* client_thread(void* in)
{   
    char message[1000] , server_reply[1000];
     
    //server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server.sin_family = AF_INET;
    //server.sin_port = htons( 8888 );

    sleep(1);
    //Connect to remote server
    if (connect(sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0)
    {
	puts("FAILEDDDDDDDDDDDDDDDDDD");
        perror("connect failed. Error \n");
        return NULL;
    }
    printf("Connected. \n");

    //keep communicating with server
    while(1)
    {        
	int n = sprintf(message, "%f,%f, \n", player_x, player_y);
	//Send some data
        if(send(sockfd, message,strlen(message),0) < 0)
        {
	    puts("FAILEDDDDDDDDDDDDDDDDDD");
            die("Send failed \n");
            return NULL;
        }
        //Receive a reply from the server
        if( recv(sockfd, server_reply , 2000 , 0) < 0)
        {
	    puts("FAILEDDDDDDDDDDDDDDDDDD");
            die("recv failed \n");
            break;
        }
	else
	{
	    float new_enemyx, new_enemyy, new_ballx, new_bally, new_ballz;
	    sscanf(server_reply,"(%f,%f,%f,%f,%f) \n", &new_enemyx, &new_enemyy, &new_ballx, &new_bally, &new_ballz);
	    //xprintf(server_reply);
	    update_enemy_coord(new_enemyx, new_enemyy);
	    update_ball_coord(new_ballx, new_bally, new_ballz);
	}
    }
     
    close(sockfd);
    return NULL;
}

void client_init() 
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //Create socket
    if (sockfd == -1)
    {
	puts("FAILEDDDDDDDDDDDDDDDDDD");
        printf("Could not create socket \n");
    }
    puts("Socket created \n");
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(GAME_PORT);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr) != 1) 
    {
	puts("FAILEDDDDDDDDDDDDDDDDDD");
	die2("inet_pton: %s \n", ip);
	return;
    }
    else
    {
	printf("Connected to Server @ %s\n", ip);
    }

    // start a client thread
    pthread_create(&worker,(void*) NULL, client_thread, NULL);
//    pthread_join(worker,NULL);
}



void logic_update(float dt) 
{
    int ball_dir = -1;
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
