/*
  here is solution for reverseme #4 php challenge
  written using C, cuz wut? cuz im boringgg at dat time
  here is the link for mentioned challenge : http://w3.tbd.my/thread-15160-post-175788.html#pid175788
  byehhh...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_replace(char *search, char *replace, char *str)
{
	int len_str = strlen(str), len_replace = strlen(replace), i;
	char *p, *d, *z, *backward = str + len_str; 

	while((p = strstr(str, search)) != NULL)
	{
		z = backward += backward != str+len_str && len_replace + 1;
		d = z + len_replace - 1, str = p + len_replace;
		
		while(z != p) *d-- = *z--;
		memcpy(p, replace, len_replace);
	}
}

int ifExistBig(char *str)
{
	for( ; *str; str++)
		if(*str > 'A' && *str < 'Z')
			return 1;
	
	return 0;
}

int main()
{
	char gei[][2][4] =
	{
		{"A", " g"}, {"B", "ve"}, {"C", "ne"}, {"D", "CB"}, {"E", "Dr"},
		{"F", "EA"}, {"G", "Fo"}, {"H", "Gn"}, {"I", "Hn"}, {"J", "Ia"},
		{"K", " y"}, {"L", "Ko"}, {"M", "Lu"}, {"N", "M "}, {"O", "\nJ"},
		{"P", "O "}, {"Q", "un"}, {"R", " a"}, {"S", "Rn"}, {"T", "Sd"},
		{"U", "T "}, {"V", "rt"}, {"W", "VM"}
	}, decoded[500] = "JAiBNupPletNdownPrQRroQdUdeseWPmakeNcryPsayAoodbyePtellR lieUhuW";

	int size_r = sizeof(gei) / (2 * 4), i;

	while(ifExistBig(decoded))
		for(i = 0; i < size_r; i++)
			str_replace(gei[i][0], gei[i][1], decoded);

	printf("\n%s\n\n", decoded);
}