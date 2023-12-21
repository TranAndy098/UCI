import urllib, json
from urllib import request,error
from urllib.request import urlopen
from LastFM import LastFM

"""
apikey = "8725d482c1ff93a7147673296a1f41441"
url = f"https://quotes.rest/yaml/theysaidso.quotes.openapi.yaml?v1.1"
response = urllib.request.urlopen(url)
json_results = response.read()
print(response)
print(json_results)
print(json_results.decode(encoding = 'utf-8'))"""
"""
url = f"http://quotes.rest/qod.json?category=inspire"
response = urllib.request.urlopen(url)
json_results = response.read()
print(response)
print(json_results.decode(encoding = 'utf-8'))"""

url = f"https://zenquotes.io/api/random"
response = urllib.request.urlopen(url)
json_results = response.read()
print(response)
print(json_results)
print(json_results.decode(encoding = 'utf-8'))
x = json_results.decode(encoding = 'utf-8')
y = eval(x)
print(y[0]['q'])
print(y[0]['a'])
