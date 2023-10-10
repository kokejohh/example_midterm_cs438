#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <sys/socket.h>
#include <netinet/in.h>
//#include <netdb.h>
//#include <arpa/inet.h>

//#include <errno.h>
//#include <sys/types.h>
//#include <ctype.h>

#define	PORT	5789

typedef struct arr_int {
	int n;
	int nums[10];
} arr_int;

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main(int argc, char *argv[])
{
	int lst_fd, conn_fd;
	static struct sockaddr_in sock_name, client_info;
	int retval, len;

	if ((lst_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
		exit(-1);
	}

	memset(&sock_name, 0, sizeof(sock_name));
	memset(&client_info, 0, sizeof(client_info));

	sock_name.sin_family = AF_INET;
	sock_name.sin_port = htons(PORT);
	sock_name.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((retval = bind(lst_fd, (const struct sockaddr *)&sock_name, sizeof(sock_name))) != 0)
	{
		perror("bind error");
		close(lst_fd);
		exit(-1);
	}

	if ((retval = listen(lst_fd, 5)) != 0)
	{
		perror("listen error");
		close(lst_fd);
		exit(-1);
	}

	len = sizeof(client_info);
	if ((conn_fd = accept(lst_fd, (struct sockaddr *)&client_info, &len)) < 0)
	{
		perror("accept error");
		close(lst_fd);
		exit(-1);
	}

	arr_int number;

	read(conn_fd, &number, sizeof(number));

	qsort(number.nums, number.n, sizeof(int), compare);

	write(conn_fd, &number, sizeof(number));

	close(conn_fd);
	close(lst_fd);
	
	return 0;
}
