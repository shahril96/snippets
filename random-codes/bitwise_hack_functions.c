// set of useful functions for manipulation integer in low level binary

// this was written when i'm started to learn C
// code look suck, well, this shit is from 2 years ago :) (ahh unforgotten memories)
// hope you can learn somethings from this code

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/*
 * Return C-style string pointer to binary representation of decimal
 * This will just work with unsigned integer.
 * Note that you must clean heap that created using free()
 */
char *num2BinCharStr(uint64_t dNum, uint8_t representNum)
{
	// + 1 for null terminated (0x0)
	char *store = (char *)malloc(representNum + 1);

	// null terminated
	store[representNum] = '\0';

	for (uint8_t i = 0; i < representNum; i++)
	{
		// iterate bit using reverse technique
		store[i] = (dNum & (((uint64_t)1 << (representNum - 1)) >> i)) ? '1' : '0';
	}

	// return dynamic memory pointer
	return store;
}

/*
 * Check if n-bit is set inside binary
 * If set, then result will return non-zero, otherwise zero
 */
uint8_t isBinSet(uint64_t num, uint8_t positionFromRight)
{
	return (num & ((uint64_t)1 << (positionFromRight - 1)));
}

/*
 * Get length of maximum bit size
 * 0x4 = 0100 = will return 3
 */
uint8_t binLength(uint64_t num)
{
	// get type bit size
	uint8_t numSize = sizeof(num) * 8;

	// iterate trough all bit
	for (uint16_t i = 0; numSize > i; i++)
	{
		// if first bit found, then return it size
		if (num & (((uint64_t)1 << (numSize - 1)) >> i))
			return numSize - i;
	}

	// if no bit found (input = 0), then return 0
	return 0;
}

uint64_t binSubStr(uint64_t num, uint8_t fromLeft, uint8_t fromRight)
{
	uint8_t sizeNum = (sizeof(num)* 8), firstBitCount = 0;
	uint64_t tmpUInt = 0, output = 0;

	// get last bit (iterate bit from left to right)
	for (uint8_t i = 0; i < sizeNum; i++)
	{
		if (num & (((uint64_t)1 << (sizeNum - 1)) >> i))
		{
			firstBitCount = i;
			break;
		}
	}

	for (uint8_t i = (fromLeft + firstBitCount); i < sizeNum; i++)
	{
		uint64_t currentBit = (((uint64_t)1 << (sizeNum - 1)) >> i);

		if (num & currentBit)
		{
			tmpUInt |= currentBit;
		}
	}

	uint8_t cTmp = 0;

	for (uint8_t i = fromRight; i < (sizeNum - firstBitCount); i++)
	{
		uint64_t currentBit = (uint64_t)1 << i;
		if (tmpUInt & currentBit)
		{
			output |= 1 << cTmp;
		}
		cTmp++;
	}

	return output;
}

int main()
{
	appendBin(0x100000000000000, 0x4);
}