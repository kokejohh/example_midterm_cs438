#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "ass2.h"

static int compare(a, b)
	newInt *a, *b;
{
	if (abs(*a) % 2 == 1) return 1;
	else if (*a % 2 == 0 && abs(*b) % 2 == 1) return -1;
	return *(newInt *)a - *(newInt *)b;
}

static int countEven(parameter *numsp)
{
	int count = 0;
	for (int i = 0; i < numsp->nums.nums_len; i++)
		if (numsp->nums.nums_val[i] % 2 == 0)
			count++;
	return count;
}

returntype *sort_1_svc(numsp, c)
	parameter *numsp;
	struct svc_req *c;
{
	static returntype res;

	if (res.nums.nums_val != (newInt *)NULL)
		free(res.nums.nums_val);
	
	qsort(numsp->nums.nums_val, numsp->nums.nums_len, sizeof(newInt), compare);
	
	int numberOfEven = countEven(numsp);
	res.nums.nums_len = numberOfEven;
	res.nums.nums_val = (newInt *)malloc(numberOfEven * sizeof(newInt));
	memmove(res.nums.nums_val, numsp->nums.nums_val, numsp->nums.nums_len * sizeof(newInt));
	return (&res);
}
