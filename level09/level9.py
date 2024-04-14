import re

with open('result', 'r') as fp:
    data = fp.read()

#match = re.compile('(\(nil\)|0x[a-z0-9]+)')
#m = match.split(data)
#print(m)



indices = []
start = 0
while True:
    index_0x = data.find('0x', start)
    index_nl = data.find('(nil)', start)

    if index_0x < 0:
        index = index_nl
    elif index_nl < 0:
        index = index_0x
    else:
        index = min(index_0x, index_nl)

    if index < 0:
        indices.append(len(data))
        break
    else:
        indices.append(index)

    start = index + 1

for (i, (head, tail)) in enumerate(zip(indices, indices[1:])):
    print('%04d : %s' % (i + 1, data[head:tail]))


#print(ret.index('0xbabe'))
#print(ret.index('0xbabe') // 10)
