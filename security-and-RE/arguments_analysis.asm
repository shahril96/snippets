/*

#include <stdio.h>

int main(int argc, char *argv[])
{
    puts(""); // space

    if(argc == 1)
    {
        printf("failed!");
    }
    else
    {
        for(int i = 1; i < argc; i++)
        {
            printf("[%d] -> %s\n", i, argv[i]);
        }
    }
}


*/

/*
Contents of section .rodata:
 8048558 03000000 01000200 00666169 6c656421  .........failed!
 8048568 005b2564 5d202d3e 2025730a 00        .[%d] -> %s..
*/

0804844b <main>:

    ; save first perimeter stack address inside ecx
 804844b:	8d 4c 24 04          	lea    ecx,[esp+0x4]

    ; align esp (bottom of stack) to 16-bytes boundry
 804844f:	83 e4 f0             	and    esp,0xfffffff0

    ; get currect routine start stack address inside stack
 8048452:	ff 71 fc             	push   DWORD PTR [ecx-0x4]

    ; function epilogue
 8048455:	55                   	push   ebp
 8048456:	89 e5                	mov    ebp,esp

    ; store ebx, ecx value into stack for later uses
 8048458:	53                   	push   ebx
 8048459:	51                   	push   ecx

    ; allocate 0x10 bytes from stack (0x10 = 16)
 804845a:	83 ec 10             	sub    esp,0x10

    ; move first perimeter address from ecx to ebx
    ; ebx is now first address of stack containing perimeter of main routine
 804845d:	89 cb                	mov    ebx,ecx

    ; allocated 0xc more space inside stack (0xc = 12)

    ; 0x8048560 = address containing null byte (0) at rodata segment
    ; clear 0x10 because 0xc + 0x4 (perimeter) is 0x10
 804845f:	83 ec 0c             	sub    esp,0xc
 8048462:	68 60 85 04 08       	push   0x8048560
 8048467:	e8 b4 fe ff ff       	call   8048320 <puts@plt>
 804846c:	83 c4 10             	add    esp,0x10

    ; check first perimeter (number of perimetes) eq to 1
    ; if not eq (which is numb of perimeters greater than 1), then take the jump
 804846f:	83 3b 01             	cmp    DWORD PTR [ebx],0x1
 8048472:	75 12                	jne    8048486 <main+0x3b>

    ; print 0x8048561 address containing "failed!" message inside .rodata segment
    ; clear 0x10 because 0xc + 0x4 (perimeter) is 0x10
 8048474:	83 ec 0c             	sub    esp,0xc
 8048477:	68 61 85 04 08       	push   0x8048561
 804847c:	e8 8f fe ff ff       	call   8048310 <printf@plt>
 8048481:	83 c4 10             	add    esp,0x10

    ; jump to the end of main func.
 8048484:	eb 39                	jmp    80484bf <main+0x74>

    ; if argument number checking is successful, then run code below this

    main+0x3b:

    ; move 1 into local stack value
    ; then jump to set up
 8048486:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [ebp-0xc],0x1
 804848d:	eb 29                	jmp    80484b8 <main+0x6d>

    main+0x44:

    ; move incrementing local stack value into eax
 804848f:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]

    ; edx = multiply by 4 (array of pointer string)
 8048492:	8d 14 85 00 00 00 00 	lea    edx,[eax*4+0x0]

    ; get first address array of pointer strings
    ; add it up with edx to get each argument string address
 8048499:	8b 43 04             	mov    eax,DWORD PTR [ebx+0x4]
 804849c:	01 d0                	add    eax,edx

    ; dereferencing address to real address to string
 804849e:	8b 00                	mov    eax,DWORD PTR [eax]

    ; print each of string arguments
 80484a0:	83 ec 04             	sub    esp,0x4
 80484a3:	50                   	push   eax                      ; address to string
 80484a4:	ff 75 f4             	push   DWORD PTR [ebp-0xc]      ; for %d
 80484a7:	68 69 85 04 08       	push   0x8048569                ; string format -> "[%d] -> %s\n"
 80484ac:	e8 5f fe ff ff       	call   8048310 <printf@plt>
 80484b1:	83 c4 10             	add    esp,0x10

    ; add 1 to local stack variable ebp-0xc (that hold up incrementing value)
 80484b4:	83 45 f4 01          	add    DWORD PTR [ebp-0xc],0x1

    main+0x6d:

    ; give 1 (which containing at local stack variable) to eax
    ; compare first perimeter (num of perimeters) with ecx value
    ; if still lower, then jump to main+0x44
    ; this is increment for loop (or while loop, or whatever)
 80484b8:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
 80484bb:	3b 03                	cmp    eax,DWORD PTR [ebx]
 80484bd:	7c d0                	jl     804848f <main+0x44>

    main+0x74:

    ; eax is default return value for C-calling convention
 80484bf:	b8 00 00 00 00       	mov    eax,0x0

    ; give back esp value (esp at aligned 16-bytes)
 80484c4:	8d 65 f8             	lea    esp,[ebp-0x8]

    ; give back preserved value of ecx, ebx registers
 80484c7:	59                   	pop    ecx
 80484c8:	5b                   	pop    ebx

    ; give original esp (before aligned at 16-bytes boundry)
 80484c9:	5d                   	pop    ebp
 80484ca:	8d 61 fc             	lea    esp,[ecx-0x4]

    ; return to previous routine
 80484cd:	c3                   	ret

    ; dafuq?
 80484ce:	66 90                	xchg   ax,ax