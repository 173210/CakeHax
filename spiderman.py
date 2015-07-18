#!/usr/bin/env python
from __future__ import division

import os
import sys
import struct
import array

with open(sys.argv[1], "rb") as fp:
	code = fp.read()
	fp.close()

enc_code = array.array('b', b'\x00' * len(code))

key = 0
for x in range(len(code) // 4):
	key += 0xD5828281;
	val = struct.unpack_from('<I', code, x * 4)[0] - key;
	struct.pack_into('<I', enc_code, x * 4, val & 0xffffffff);

with open(sys.argv[2], "wb") as fp:
	fp.seek(0)
	fp.write(enc_code)
	fp.close()