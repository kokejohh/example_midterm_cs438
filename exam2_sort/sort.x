const MAXSORTSIZE = 64;

typedef int mytype;

struct sortobject {
	mytype ss<MAXSORTSIZE>;
};

typedef struct sortobject returntype;
typedef struct sortobject parameter;

program SORTPROG {
	version SORTVERS {
		returntype SORT(parameter) = 1;
	} = 1;
} = 22855;
