import urllib, json
from urllib import request,error
from urllib.request import urlopen
from LastFM import LastFM

apikey = "8725d482c1ff93a7147673296a1f4144"
"""url = f"http://ws.audioscrobbler.com/2.0/?method=auth.gettoken&api_key={apikey}&format=json"
response = urllib.request.urlopen(url)
json_results = response.read()
token = eval(json_results)['token']
print(token)
        
url1 = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettopartists&api_key={apikey}&format=json"
response1 = urllib.request.urlopen(url1)
json_results1 = response1.read()
x = json_results1.decode('utf8')
y = eval(x)
print(y['artists']['artist'])"""

"""
z = y['artists']['artist']
for i in range(len(z)):
    print(z[i]['name'])"""
    
"""list of top artuist"""
"""
url1 = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettoptracks&api_key={apikey}&format=json"
response1 = urllib.request.urlopen(url1)
json_results1 = response1.read()
x = json_results1.decode('utf8')
y = eval(x)
print(y)
print(y['tracks']['track'])
z = y['tracks']['track']
for i in range(len(z)):
    print(i)
    print(z[i]['name'])"""
"""top tracks"""

"""url1 = f"http://ws.audioscrobbler.com/2.0/?method=user.gettopalbums&user=rj&api_key={apikey}&format=json"
response1 = urllib.request.urlopen(url1)
json_results1 = response1.read()
x = json_results1.decode('utf8')
y = eval(x)
print(y)
print(y['topalbums']['album'])
z = y['topalbums']['album']
for i in range(len(z)):
    print(i)
    print(z[i]['name'])
    """
"""top albums"""
"""url1 = f"http://ws.audioscrobbler.com/2.0/?method=artist.gettoptags&artist=cher&api_key={apikey}&format=json"
response1 = urllib.request.urlopen(url1)
json_results1 = response1.read()
x = json_results1.decode('utf8')
y = eval(x)
print(y['toptags']['tag'])
z = y['toptags']['tag']
for i in range(len(z)):
    print(i)
    print(z[i]['name'])"""
"""print(0)"""
apikey = "8725d482c1ff93a7147673296a1f41441"
lf = LastFM(apikey)
"""
print(lf.top_5artists)
print(lf.top_5tracks)
print(lf.top_5albums)
print(lf.top_5tags)"""
p = "i love how @lastfm is @lastfm_top_3_artists. is @lastfm_top_3_tracks, is @lastfm_top_3_albums is @lastfm_top_3_tags"
print(p)
if '@' in p:
    p = lf.transclude(p)
print(p)
apikey = "8725d482c1ff93a7147673296a1f4144"
lf.set_apikey(apikey)
p = "i love how @lastfm is @lastfm_top_3_artists. is @lastfm_top_3_tracks, is @lastfm_top_3_albums is @lastfm_top_3_tags"
print(p)
if '@' in p:
    p = lf.transclude(p)
print(p)
p = "i love how @lastfm; is @lastfm_top_3_artists. is @lastfm_top_3_tracks, is @lastfm_top_3_albums] is @lastfm_top_3_tags&"
print(p)
if '@' in p:
    p = lf.transclude(p)
print(p)
