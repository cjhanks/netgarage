
all_of_them = [
    '0x2b-NULL-0',
    '0x2b-NULL-1',
    '0x2d-NULL-0',
    '0x2d-NULL-1',
    '0x2e-NULL-0',
    '0x2e-NULL-1',
    '0x3e-0x2d-0',
    '0x3e-0x2d-1',
    '0x3e-NULL-0',
    '0x3e-NULL-1',
    '0x5b-NULL-0',
    '0x5b-NULL-1',
    '0x5d-NULL-0',
    '0x5d-NULL-1',
    'NULL-0x2b-0',
    'NULL-0x2b-1',
    'NULL-0x2d-0',
    'NULL-0x2d-1',
    'NULL-0x2e-0',
    'NULL-0x2e-1',
    'NULL-0x3c-0',
    'NULL-0x3c-1',
    'NULL-0x5b-0',
    'NULL-0x5b-1',
]


all_set = set()
for them in all_of_them:
    (a, b, _) = them.split('-')

    if a == 'NULL':
        all_set.add(chr(int(b, 16)))

    if b == 'NULL':
        all_set.add(chr(int(a, 16)))

print(all_set)
