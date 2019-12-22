import sys

mod = 119315717514047

class pol:
	def __init__(self, a = 1, b = 0):
		self.a = a
		self.b = b
	
	def __str__(self):
		return str(self.a) + "x " + ("- " if self.b < 0 else "+ ") + str(abs(self.b))

	def cut(self, x):
		self.b -= x

	def increment(self, x):
		self.a *= x
		self.b *= x

	def newStack(self):
		self.a *= -1
		self.b *= -1
		self.b += mod - 1

	def __call__(self, x):
		if type(self) == type(x):
			return pol(self.a * x.a, self.a * x.b + self.b)
		else:
			x *= self.a
			x += self.b
			x %= mod
			return x if x > 0 else x + mod

	def normalize(self):
		self.a %= mod
		self.b %= mod

def expfunc(p, e):
	if e == 0:
		return pol()
	if e == 1:
		return p
	f = expfunc(p, e // 2)
	f = f(f)
	if e % 2:
		f = f(p)
	return f

def eucl(a, b):
	if b == 0:
		return 1, 0, a
	x, y, d = eucl(b, a % b)
	return y, x - (a // b) * y, d

def inv(x, mod):
	n, _, _ = eucl(x, mod)
	if n < 0:
		n += mod
	return n

def solve(p, y):
	y -= p.b
	y *= inv(p.a, mod)
	y %= mod
	if y < 0:
		y += mod
	return y
	
def main():
	p = pol()
	for s in sys.stdin:
		if (s[0] == 'c'):
			x = int(s[4:])
			p.cut(x)
		elif (s[5] == 'w'):
			x = int(s[20:])
			p.increment(x)
		else:
			p.newStack()
	p.normalize()

	qtd = 101741582076661
	ans = pol()
	while qtd:
		x = qtd % 2
		if x:
			ans = p(ans)
			ans.normalize()
		qtd //= 2
		p = p(p)
		p.normalize()

	print(solve(ans, 2020))

main()
