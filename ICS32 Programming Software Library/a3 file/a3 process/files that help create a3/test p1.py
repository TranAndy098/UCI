import urllib, json
from urllib import request,error
from OpenWeather import OpenWeather
from LastFM import LastFM

zipcode = "92841"
ccode = "US"
apikeys = "824eab18432eee3e404cff1e4df28b87"
open_weather = OpenWeather(zipcode,ccode,apikeys)
apikey = "8725d482c1ff93a7147673296a1f4144"
lf = LastFM(apikey)

p = "i love how @lastfm is @lastfm.top_5artists is @lastfm.top_5tracks is @lastfm.top_5albums is @lastfm.top_5tags, i love how @weather is @weather.sunrise @weather.sunset @weather @weather.description @weather.temperature @weather.high_temperature @weather.low_temperature @weather.longitude @weather.latitude @weather.humidity @weather.windspeed @weather.cloudiness @weather.city"
print(p)
if '@' in p:
    p = open_weather.transclude(p)
    p = lf.transclude(p)
print(p)
