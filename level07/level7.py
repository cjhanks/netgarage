import base64
import pwn

addr = pwn.p32(0x574f4c46)

print(60 * 'w' + 'FLOW')
#print(addr)
#print(base64.b64encode(addr))
