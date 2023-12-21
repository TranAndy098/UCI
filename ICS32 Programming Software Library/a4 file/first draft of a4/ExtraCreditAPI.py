import urllib, json
from urllib import request,error
import re

class ExtraCreditAPI:
    """
    The ExtraCreditAPI class is responsible for generating a random quote.
    It will get that information from the ZenQuotes website.
    It allows the user to get a random quote and also translude post that have the certain @[keyword].
    """
    def __init__(self):
        """
        Initalize the classes' object's state.
        """

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

    def connect(self):
        """
        This function connects to the website and obtains the data to be able to use the information.
        """
        url = f"https://zenquotes.io/api/random"
        quote_obj = self._download_url(url)
        if quote_obj is not None:
            return quote_obj

    def random_quote(self):
        """
        This function will take in the data and convert it into a quote by author format
        """
        try:
            data = self.connect()
            info = data[0]
            quote = '\"{}\" by {}'.format(info['q'],info['a'])
            return quote
        except:
            return '@extracredit'

    def transclude(self, message:str) -> str:
        '''
        Replaces keywords in a message with associated API data.
        :param message: The message to transclude
        
        :returns: The transcluded message
        '''
        replacements = {'@extracredit':self.random_quote}
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
    random_quote = property(random_quote)
    extracredit = property(random_quote)
