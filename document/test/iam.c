#include <nametest.h>

int main(int argc, char *argv[])
{
    if(argc>1) 
	{
		if(iam(argv[1])<0) 
		{
			return -1;
		}
		return 0;	
	}
	return -1;
}
