import urllib, json
from urllib import request,error

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
            print('Failed to download contents of URL')
            print('Status code: {}'.format(e.code))

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

    def top_5artists(self):
        """
        Will connect to the server and sort through the information and return the top 5 artists.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettopartists&api_key={apikey}&format=json"
        data = self.connect(url)
        all_artists = data['artists']['artist']
        top_5_artists = ''
        for i in range(5):
            if top_5_artists == '':
                top_5_artists = top_5_artists + all_artists[i]['name']
            elif i + 1 == 5:
                top_5_artists = top_5_artists + ', and ' + all_artists[i]['name']
            else:
                top_5_artists = top_5_artists + ', ' + all_artists[i]['name']
        return top_5_artists

    def top_5tracks(self):
        """
        Will connect to the server and sort through the information and return the top 5 tracks.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=chart.gettoptracks&api_key={apikey}&format=json"
        data = self.connect(url)
        all_tracks = data['tracks']['track']
        top_5_tracks = ''
        for i in range(5):
            if top_5_tracks == '':
                top_5_tracks = top_5_tracks + all_tracks[i]['name']
            elif i + 1 == 5:
                top_5_tracks = top_5_tracks + ', and ' + all_tracks[i]['name']
            else:
                top_5_trackss = top_5_tracks + ', ' + all_tracks[i]['name']
        return top_5_tracks

    def top_5albums(self):
        """
        Will connect to the server and sort through the information and return the top 5 albums.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=user.gettopalbums&user=rj&api_key={apikey}&format=json"
        data = self.connect(url)
        all_albums = data['topalbums']['album']
        top_5_albums = ''
        for i in range(5):
            if top_5_albums == '':
                top_5_albums = top_5_albums + all_albums[i]['name']
            elif i + 1 == 5:
                top_5_albums = top_5_albums + ', and ' + all_albums[i]['name']
            else:
                top_5_albums = top_5_albums + ', ' + all_albums[i]['name']
        return top_5_albums

    def top_5tags(self):
        """
        Will connect to the server and sort through the information and return the top 5 tags.
        """
        apikey = self.apikey
        url = f"http://ws.audioscrobbler.com/2.0/?method=artist.gettoptags&artist=cher&api_key={apikey}&format=json"
        data = self.connect(url)
        all_tags = data['toptags']['tag']
        top_5_tags = ''
        for i in range(5):
            if top_5_tags == '':
                top_5_tags = top_5_tags + all_tags[i]['name']
            elif i + 1 == 5:
                top_5_tags = top_5_tags + ', and ' + all_tags[i]['name']
            else:
                top_5_tags = top_5_tags + ', ' + all_tags[i]['name']
        return top_5_tags

    def transclude(self, message:str) -> str:
        '''
        Replaces keywords in a message with associated API data.
        :param message: The message to transclude
        
        :returns: The transcluded message
        '''
        replacements = {'@lastfm':self.top_5artists,'@lastfm.top_5artists':self.top_5artists,'@lastfm.top_5tracks':self.top_5tracks,'@lastfm.top_5albums':self.top_5albums,'@lastfm.top_5tags':self.top_5tags}
        components = message.split(' ')
        for i in range(len(components)):
            for keys in replacements:
                if components[i] == keys:
                    components[i] = replacements[keys]
        new_message = ' '.join(components)
        return new_message

    """
    The property method is used to support each variable to use the function to get the specfic information each are requesting.
    """
    top_5artists = property(top_5artists)
    top_5tracks = property(top_5tracks)
    top_5albums = property(top_5albums)
    top_5tags = property(top_5tags)
