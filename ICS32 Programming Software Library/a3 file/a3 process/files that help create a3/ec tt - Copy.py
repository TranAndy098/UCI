import urllib, json
from urllib import request,error
from urllib.request import urlopen
from ExtraCreditAPIS import ExtraCreditAPI

ec = ExtraCreditAPI()
print(ec.random_quote)
p = "i love how @extracredit"
print(p)
if '@' in p:
    p = ec.transclude(p)
print(p)
