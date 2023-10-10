const MAXSIZE = 64;

typedef int newInt;

struct objNumber {
	newInt nums<MAXSIZE>;
};

typedef struct objNumber returntype;
typedef struct objNumber parameter;

program ASS2PROG {
	version ASS2VERS {
		returntype SORT(parameter) = 1;
	} = 1;
} = 2091;
