import hashlib

with open("bin2.txt", "r+") as f:
	a = f.read()

a = hashlib.sha256(str(a).encode('utf-8')).hexdigest()

with open("bin2.txt", "w") as f:
	f.write(a)