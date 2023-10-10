#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <netdb.h>
//#include <arpa/inet.h>

//#include <error.h>
//#include <sys/types.h>
//#include <ctype.h>

typedef struct arr_int {
	int n;
	int nums[10];
} arr_int;

int main(int argc, char *argv[])
{
	char hostname[100];
	int portno;
	int conn_fd;
	static struct sockaddr_in sock_name, client_info;
	struct hostent hostentstruct, *hostentptr;
	int retval;
	char str[100], ch;

	if (argc < 3)
	{
		printf("Usage client <hostname> <port#>\n");
		exit(-1);
	}

	memset(&sock_name, 0, sizeof(sock_name));
	memset(&client_info, 0, sizeof(client_info));

	strcpy(hostname, argv[1]);
	portno = atoi(argv[2]);

	if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
		exit(-1);
	}

	if ((hostentptr = gethostbyname(hostname)) == NULL)
	{
		perror("gethostbyname error");
		close(conn_fd);
		exit(-1);
	}
	hostentstruct = *hostentptr;
	sock_name.sin_family = AF_INET;
	sock_name.sin_port = htons(portno);
	sock_name.sin_addr = *((struct in_addr *)hostentstruct.h_addr);

	if ((retval = connect(conn_fd, (const struct sockaddr *)&sock_name, sizeof(sock_name))) != 0)
	{
		perror("connect error");
		close(conn_fd);
		exit(-1);
	}

	arr_int number;
	do
	{
		printf("Enter number of arrays : ");
		scanf("%d", &number.n);
		if (number.n >= 1 && number.n <= 10) break;
		printf("number of arrays should be from (1 - 10)\n");
	} while(1);

	for (int i = 0; i < number.n; i++)
	{
		printf("Enter number %d : ", i + 1);
		scanf("%d", &number.nums[i]);
	}

	write(conn_fd, &number, sizeof(number));
	printf("\nFrom Server: ");

	arr_int numberServ;
	read(conn_fd, &numberServ, sizeof(numberServ));

	for (int i = 0; i < numberServ.n; i++)
	{
		printf("%d ", numberServ.nums[i]);
	}
	printf("\n");

	close(conn_fd);
	return 0;
}
