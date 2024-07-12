import hashlib
import sys


'''
beka    =   47a9bacc5051c49be189d7d051f2c755
hanin   =   3e241cb997b341abd86502442b0a8f60
mmpi    =   e2f39eb45ac7ab873f751bde423fb5bb
scl     =   f32305c695d7dc05e9dccfadf8e5e01d
tobol   =   98a61ef88202ffe2d5b0feccd273353c
zung    =   1761aba4dcb26fcfe1c80b3513a26ef6
'''


if len(sys.argv) < 2:
    print("Error: no methodics name are given")
    exit(1)

for m in sys.argv[1::]:
    h = hashlib.blake2b(m.encode('ascii'), digest_size=16)
    print("{} = {}".format(m, h.hexdigest()))
