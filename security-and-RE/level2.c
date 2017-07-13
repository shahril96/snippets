#include <stdio.h>
#include <string.h>

int main()
{
	char key[40] = {0};
	memset(key, 'O', 32);
	int i = 0;
	
	unsigned id;
	printf("enter id : ");
	scanf("%u", &id);
	
	if(id & 1) // check least significant bit for set
		key[i] = '*';
	
	i++;
	
	if(id <= 0xb16b00b5)
		key[i] = '*';

	key[++i] = '*';
	key[++i] = '*';
	
	for(int z = 28; z > 0; z--)
	{
		id >>= 1;
		int rem = id % 26;

		// z & 1 to check either number is odd
		key[i++] = rem + ((z & 1) ? 'A' : 'a');			
	}
	
	printf("key : %s\n", key);

}