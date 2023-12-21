import urllib, json
from urllib import request,error
import re

class LastFM:
    """
    The LastFM class is responsible for taking in the the user's api key.
    It will take that information and connect to the LastFM website to get information.
    It allows the user to get specfic infromation and also translude post that have the certain @[keyword].
    """
    def __init__(self, apikey):
        """
        Initalize the classes' object's state.
        """
        self.set_apikey(apikey)

    def _download_url(self,url_to_download: str) -> dict:
        """
        This function is resposnible for connecting to the api website to get the total set of information.
        """
        response = None
        r_obj = None

        try:
            response = urllib.request.urlopen(url_to_download)
            json_results = response.read()
            r_obj = json.loads(json_results)

        except urllib.error.HTTPError as e:
            if self.errors < 1:
                self.errors += 1
                print('Failed to download contents of URL')
                print('Status code: {}'.format(e.code))
                if e.code == 400:
                    print('request to server cannot be understood due to invalid syntax')
                elif e.code == 401:
                    print('invalid apikey, please try again with a new apikey')
                elif e.code == 403:
                    print('possible invalid apikey or access is forbidden')
                elif e.code == 404:
                    print('cannot find the url, so unable to connect')
                elif e.code == 408:
                    print('client unable to produce a request within server timeout limit')
                elif e.code == 410:
                    print('server no longer exists')
                elif e.code == 414:
                    print('the request url is longer than what the server is willing to interpret')
                elif e.code == 422:
                    print('correct request entity and syntax, but unable to process the contained instructions')
                elif e.code == 502:
                    print('bad gatway from server so unable to fulfill request')
                elif e.code == 503:
                    print('server unable to connect due to possible maintenance or is overloaded with requests')
                elif e.code == 504:
                    print('reuqest to server took too long, so gateway timed out')
                elif e.code == 505:
                    print('server does not support or refuses to support the request message')
                elif 399 < e.code < 452:
                    print('a client error')
                elif 499 < e.code < 512:
                    print('a server error')

        finally:
            if response != None:
                response.close()
        
        return r_obj

    def connect(self, url):
        """
        This function takes in the api key and uses it to connect to the website and then be able to use the information.
        """
        lastfm_obj = self._download_url(url)
        if lastfm_obj is not None:
            return lastfm_obj
    
    def set_apikey(self, apikey:str) -> None:
        '''
        Sets the apikey required to make requests to a web API.
        :param apikey: The apikey supplied by the API service
        Will assign the api kepy parameter to the self.apikey to be used by the functions in the class.
            
        '''
        self.apikey = apikey
        pass

    def lastfm(self):
        """
        Will connect to the server and sort through the information and return the top 3 artists.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettopartists&api_key={apikey}&format=json"
        try:
            data = self.connect(url)
            all_artists = data['artists']['artist']
            top_3_artists = ''
            for i in range(3):
                if top_3_artists == '':
                    top_3_artists = top_3_artists + all_artists[i]['name']
                elif i + 1 == 3:
                    top_3_artists = top_3_artists + ', and ' + all_artists[i]['name']
                else:
                    top_3_artists = top_3_artists + ', ' + all_artists[i]['name']
            return top_3_artists
        except:
            return '@lastfm'

    def top_3_artists(self):
        """
        Will connect to the server and sort through the information and return the top 3 artists.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettopartists&api_key={apikey}&format=json"
        try:
            data = self.connect(url)
            all_artists = data['artists']['artist']
            top_3_artists = ''
            for i in range(3):
                if top_3_artists == '':
                    top_3_artists = top_3_artists + all_artists[i]['name']
                elif i + 1 == 3:
                    top_3_artists = top_3_artists + ', and ' + all_artists[i]['name']
                else:
                    top_3_artists = top_3_artists + ', ' + all_artists[i]['name']
            return top_3_artists
        except:
            return '@lastfm_top_3_artists'

    def top_3_tracks(self):
        """
        Will connect to the server and sort through the information and return the top 3 tracks.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettoptracks&api_key={apikey}&format=json"
        try:
            data = self.connect(url)
            all_tracks = data['tracks']['track']
            top_3_tracks = ''
            for i in range(3):
                if top_3_tracks == '':
                    top_3_tracks = top_3_tracks + all_tracks[i]['name']
                elif i + 1 == 3:
                    top_3_tracks = top_3_tracks + ', and ' + all_tracks[i]['name']
                else:
                    top_3_tracks = top_3_tracks + ', ' + all_tracks[i]['name']
            return top_3_tracks
        except:
            return '@lastfm_top_3_tracks'

    def top_3_albums(self):
        """
        Will connect to the server and sort through the information and return the top 3 albums.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=user.gettopalbums&user=rj&api_key={apikey}&format=json"
        try:
            data = self.connect(url)
            all_albums = data['topalbums']['album']
            top_3_albums = ''
            for i in range(3):
                if top_3_albums == '':
                    top_3_albums = top_3_albums + all_albums[i]['name']
                elif i + 1 == 3:
                    top_3_albums = top_3_albums + ', and ' + all_albums[i]['name']
                else:
                    top_3_albums = top_3_albums + ', ' + all_albums[i]['name']
            return top_3_albums
        except:
            return '@lastfm_top_3_albums'

    def top_3_tags(self):
        """
        Will connect to the server and sort through the information and return the top 3 tags.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=artist.gettoptags&artist=cher&api_key={apikey}&format=json"
        try:
            data = self.connect(url)
            all_tags = data['toptags']['tag']
            top_3_tags = ''
            for i in range(3):
                if top_3_tags == '':
                    top_3_tags = top_3_tags + all_tags[i]['name']
                elif i + 1 == 3:
                    top_3_tags = top_3_tags + ', and ' + all_tags[i]['name']
                else:
                    top_3_tags = top_3_tags + ', ' + all_tags[i]['name']
            return top_3_tags
        except:
            return '@lastfm_top_3_tags'

    def transclude(self, message:str) -> str:
        '''
        Replaces keywords in a message with associated API data.
        :param message: The message to transclude
        
        :returns: The transcluded message
        '''
        replacements = {'@lastfm':self.lastfm,'@lastfm_top_3_artists':self.top_3_artists,'@lastfm_top_3_tracks':self.top_3_tracks,'@lastfm_top_3_albums':self.top_3_albums,'@lastfm_top_3_tags':self.top_3_tags}
        components = re.split('(\W+(?<!@))', message)
        for i in range(len(components)):
            for keys in replacements:
                if components[i] == keys:
                    components[i] = replacements[keys]
        new_message = ''.join(components)
        return new_message

    """
    The property method is used to support each variable to use the function to get the specfic information each are requesting.
    """
    errors = 0
    top_3_artists = property(top_3_artists)
    top_3_tracks = property(top_3_tracks)
    top_3_albums = property(top_3_albums)
    top_3_tags = property(top_3_tags)
    lastfm = property(lastfm)
