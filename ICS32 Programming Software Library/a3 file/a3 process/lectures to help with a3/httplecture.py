from urllib.request import urlopen
uri = "http://168.235.86.101:9996"
res = urlopen(uri)
data = res.read()
res.close()

print(data)
print(type(data))

text = data.decode(encoding = 'utf-8')
print(type(text))
print(text)
header = res.getheader("Content-Type")
print(header)
