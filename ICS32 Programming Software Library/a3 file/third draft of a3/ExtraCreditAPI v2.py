import urllib, json
from urllib import request,error

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
            print('Failed to download contents of URL')
            print('Status code: {}'.format(e.code))

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
            quote = "\"{}\" by {}".format(info['q'],info['a'])
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
    random_quote = property(random_quote)
    extracredit = property(random_quote)
