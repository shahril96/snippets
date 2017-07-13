#include <stdio.h>

/*
  crackme link : http://crackmes.de/users/lafarge/lafarges_crackme_2/
*/

void xor_data(char *src, int nsrc, char *byte)
{
	for(int i = 0; nsrc-- > 0; i++)
	{
		char tmp = *src;
		*src++ ^= byte[i % 5];
		byte[i % 5] = tmp;
	}
}

void xor_datarev(char *src, int nsrc, char *byte)
{
	for(int i = 0; --nsrc >= 0; i++)
	{
		char tmp = src[nsrc];
		src[nsrc] ^= byte[i % 5];
		byte[i % 5] = tmp;
	}
}

int main()
{
	
	puts(" LaFarge's crackme #2 solution by #shahril");
	
	// list of data
	char first_blk[] = {0xAA, 0x89, 0xC4, 0xFE, 0x46};
	char secnd_blk[] = {0x78, 0xF0, 0xD0, 0x03, 0xE7};
	char third_blk[] = {0xF7, 0xFD, 0xF4, 0xE7, 0xB9};
	char forth_blk[] = {0xB5, 0x1B, 0xC9, 0x50, 0x73};
	
	char username[100] = {0}, key[100] = {0}, *new, *tmp;
	unsigned int div;
	
	int size;
	
	printf("\n Enter username : ");
	scanf("%1000s%n", username, &size);
	
	new = username + 1; // author intended?
	
	xor_data(new, size, first_blk);
	xor_datarev(new, size, secnd_blk);
	xor_data(new, size, third_blk);
	xor_datarev(new, size, forth_blk);

	// convert int pointer to char pointer
	tmp = (char *)&div;

	// takes only 4 bytes chunk 
	for(int i = 0; i < size; i++)
		tmp[i & 3] += new[i];
	
	size_t count; // count length of string
	
	// sixth loop - collect remainder
	for(count = 0; div > 0; count++)
	{
		key[count] = 0x30 + (div % 10); // ascii
		div /= 10; // 0xA
	}
	
	// reverse str
	for(int i = 0, z = count-1; i < z; i++, z--)
		key[i] ^= key[z] ^= key[i] ^= key[z]; // xor-swap ;)
		
	printf(" Key : %s\n", key);
	
	puts("");
}