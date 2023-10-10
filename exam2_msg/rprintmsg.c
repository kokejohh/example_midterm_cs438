#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <rpc/rpc.h>

#define _RPCGEN_CLNT
#include "msg.h"

int main(int argc, char *argv[])
{
	CLIENT *cl;

	char **result;
	char *server;
	char *message;
	char buffer[100];

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s host \n", argv[0]);
		exit(1);
	}

	server = argv[1];
	message = buffer;

	printf("Enter message: ");
	fgets(buffer, 99, stdin);

	cl = clnt_create(server, MESSAGEPROG, MESSAGEVERS, "tcp");

	if (cl == NULL)
	{
		clnt_pcreateerror(server);
		exit(1);
	}

	cl->cl_auth = authunix_create_default();

	result = convmessage_1(&message, cl);
	if (result == NULL)
	{
		clnt_perror(cl, server);
		exit(1);
	}

	printf("Converted message from %s => %s \n", server, *result);
	
	exit(0);
}
