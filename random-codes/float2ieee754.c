// Floating Point to IEEE 754 32-bit Converter

// this was written when i'm started to learn C
// code look suck, well, this shit is from 2 years ago :) (ahh unforgotten memories)
// hope you can learn somethings from this code

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> // to use bool (c99 standard)

struct mantissa_s
{
	double actual;
	bool sign;
	char exponent;
	bool denormalized;
	int mantissa_bit;
};

struct standardNum
{
	double num;
	int exponent;
};

// function prototype
void getNormalizeValue(double num, struct standardNum *sN);
void getBitfrom32BitFloating(double num, struct mantissa_s *mantissa);
char *num2BinCharStr(int dNum, int representNum);

int main()
{
	double set_ur_number_here = -99.99;

	struct mantissa_s mantissa_struct;
	getBitfrom32BitFloating(set_ur_number_here, &mantissa_struct);

	char *exponentBit = num2BinCharStr(mantissa_struct.exponent, 8);
	char *mantissaBit = num2BinCharStr(mantissa_struct.mantissa_bit, 23);

	printf("\nActual Number \t: %.32f\n", mantissa_struct.actual);
	printf("Sign \t\t: %d (%s value)\n", mantissa_struct.sign, mantissa_struct.sign ? "Negative" : "Positive");
	printf("Exponent \t: %s\n", exponentBit);
	printf("Type \t\t: %d (%s value)\n", mantissa_struct.denormalized, mantissa_struct.denormalized ? "Normalize" : "Denormalize");
	printf("Mantissa \t: %s\n", mantissaBit);
	printf("\n\nBit : %d %s %s\n", mantissa_struct.sign, exponentBit, mantissaBit);

	// clean heap
	free(exponentBit);
	free(mantissaBit);
}

void getBitfrom32BitFloating(double num, struct mantissa_s *mantissa)
{
	// store actual double value into struct
	mantissa->actual = num;

	// this is easy
	// if positive, then 0, if negative, then 1
	mantissa->sign = !(num > -1);

	// convert num into positive number
	if (num < 0)
		num = -num;

	struct standardNum sN;
	getNormalizeValue(num, &sN);

	// bias is the maximum value for signed bit representation
	// for signed 32 bit, maximum number is 127
	unsigned char bias = ~0;
	bias /= 2;

	// exponent is bias + loop_mormalize
	mantissa->exponent = bias + sN.exponent;

	// to store if there any denormalized number
	// 1 for normalize, 0 for denormalized
	mantissa->denormalized = mantissa->exponent != 0 ? 1 : 0;
		
	// temp for mantissa
	double t_mantissa = sN.num - (int)sN.num;
	char shift_value = 22;

	// initialized
	mantissa->mantissa_bit = 0;

	int i;

	// get mantissa
	for (i = 0; i < 23; i++)
	{
		t_mantissa *= 2;

		if((int)t_mantissa)
			mantissa->mantissa_bit = mantissa->mantissa_bit | 1 << shift_value;

		t_mantissa -= (int)t_mantissa;

		shift_value--;
	}
}

void getNormalizeValue(double num, struct standardNum *sNa)
{
	sNa->num = num;
	sNa->exponent = 0;

	while(1)
	{
		if ((int)sNa->num == 1)
			break;
		else
		{
			if (sNa->num < 1)
			{
				sNa->num *= 2;
				sNa->exponent--;
			}
			else if (sNa->num > 1)
			{
				sNa->num /= 2;
				sNa->exponent++;
			}
		}
	}
}

char *num2BinCharStr(int dNum, int representNum)
{
	// + 1 for null terminator (0x0)
	char *store = (char *)malloc(representNum + 1);

	// null terminated
	store[representNum] = '\0';

	int i;

	for (i = 0; i < representNum; i++)
	{
		// iterate bit using reverse technique
		store[i] = (dNum & ((uint32_t)(1 << (representNum - 1)) >> i)) ? '1' : '0';
	}

	// return dynamic memory pointer
	return store;
}