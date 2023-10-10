#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <rpc/rpc.h>
#include <ctype.h>

#define _RPCGEN_SVC
#include "msg.h"

char **convmessage_1_svc(msg, UNUSED)
char **msg; struct svc_req *UNUSED;
{
	char *s;
	s = *msg;
	while (*s != '\0')
	{
		*s = toupper(*s);
		s++;
	}
	return (msg);
}
