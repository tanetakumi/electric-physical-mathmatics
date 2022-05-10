#include <sys/types.h>  // socket(), listen(), accept(), read(), write()
#include <sys/socket.h> // socket(), listen(), accept(), read(), write()
#include <sys/uio.h>    // read(), write()

#include <netinet/in.h> // struct sockaddr_in

#include <string.h> // memset()
#include <stdio.h>  // printf()
#include <unistd.h> // read(), write()


void revStr(char* str){
    int size = strlen(str);
    int i,j;
    char tmp = {0};
    
    for(i = 0, j = size - 1; i < size / 2; i++, j--){
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    
    return;    
}


int main()
{
	int sockfd, acceptfd;
	int len;
	char buf[1024];
	struct sockaddr_in server, client;

	/* create socket */
	sockfd = socket(PF_INET, SOCK_STREAM,0);

	/* initialize socket */
	memset(&server, 0, sizeof(server));//clear
	server.sin_family = PF_INET;
	server.sin_port   = htons(7000);

	server.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));

	/* wait here until client tries to connect */
	listen(sockfd, 5);

	/* establish connection between a client host */
	memset(&client, 0, sizeof(client));
	len = sizeof(client);
    acceptfd = accept(sockfd, (struct sockaddr*)&client, &len);

	/* read data */
	read(acceptfd, buf, sizeof(buf));
	/*printf("accept data: %s\n", buf);*/

	/* write data */
    revStr(buf);
	write(acceptfd, buf, strlen(buf));
    write(acceptfd, "\n", strlen(buf));
	/* close procedure */
	close(acceptfd);
	close(sockfd);

	return 0;
}
