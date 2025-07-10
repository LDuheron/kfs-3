#include <stdio.h>

int main(void)
{
	static const char	code[200] = "#include <stdio.h>%c%cint%cmain(void)%c{%c%cstatic const char%ccode[200] = %c%s%c;%c%c%cprintf(code, 10, 10, 9, 10, 10, 9, 9, 34, code, 34, 10, 10, 9, 10, 9, 10,10);%c%creturn(0);%c}%c";

	printf(code, 10, 10, 9, 10, 10, 9, 9, 34, code, 34, 10,10, 9, 10, 9, 10, 10);
	return(0);
}
