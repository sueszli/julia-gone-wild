#include "stacktrace.h"
#include <stdlib.h>

void test(int entier) {
	char* truc = 0;
	*truc = 'a'; //should raise segmentation fault
}

void bar() {
	test(9);
}

void foo() {
	bar();
}

int main(int argc, char* argv[]) {
	init_exceptions(argv[0]);
	foo();
	return EXIT_SUCCESS;
}
