#include <mainboard.h>

void main()
{

	while(TRUE)
	{
		while(!IN1){}
		M1_H();
		while(!IN1){}		
	}

}
