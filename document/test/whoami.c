#include <nametest.h>

int main(void)
{
    char str[128];  
    if(whoami(str, 23)<0) 
	return -1;
    else 
	printf("%s\n", str);
    return 0;
}
