#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "ass2.h"

int main(argc, argv)
	int argc;
	char *argv[];
{
	CLIENT *cl;
	char *machinename;
	parameter args;
	returntype *res;
	returntype result;

	newInt arrObj[MAXSIZE];

	if (argc < 3)
	{
		fprintf(stderr, "usage: %s machinename [s1 ...]\n", argv[0]);
		exit(1);
	}
	machinename = argv[1];
	res = &result;
	args.nums.nums_len = argc - 2;

	for (int i = 2, j = 0; i < argc; i++, j++)
		arrObj[j] = atoi(argv[i]);
	args.nums.nums_val = &arrObj[0];
	res->nums.nums_val = (newInt *)NULL;

	cl = clnt_create(machinename, ASS2PROG, ASS2VERS, "tcp");

	if (cl == NULL)
	{
		clnt_pcreateerror(machinename);
		exit(1);
	}
	res = sort_1(&args, cl);
	if (res == NULL)
	{
		clnt_perror(cl, machinename);
		exit(1);
	}
	printf("From server : ");
	if (res->nums.nums_len == 0) printf("No even number!");
	for (int i = 0; i < res->nums.nums_len; i++)
		printf("%d ", res->nums.nums_val[i]);
	printf("\n");
	
	exit(0);
}
