import urllib, json
from urllib import request,error

class OpenWeather:
    """
    The OpenWeather class is responsible for taking in the zip code, country code, and the user's api key.
    It will take that information and connect to the Open Weather website to get information.
    It allows the user to get specfic infromation and also translude post that have the certain @[keyword].
    """
    def __init__(self, zipcode, countrycode, apikey):
        """
        Initalize the classes' object's state.
        """
        self.zip = zipcode
        self.ccode = countrycode
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

    def connect(self):
        """
        This function takes in the zip, country code and api key and uses it to connect to the website and then be able to use the information.
        """
        zip = self.zip
        ccode = self.ccode
        apikey = self.apikey
        url = f"https://api.openweathermap.org/data/2.5/weather?zip={zip},{ccode}&appid={apikey}"

        weather_obj = self._download_url(url)
        if weather_obj is not None:
            return weather_obj
    
    def set_apikey(self, apikey:str) -> None:
        '''
        Sets the apikey required to make requests to a web API.
        :param apikey: The apikey supplied by the API service
        Will assign the api kepy parameter to the self.apikey to be used by the functions in the class.
            
        '''
        self.apikey = apikey
        pass


    def temperature(self):
        """
        Will connect to the server and sort through the information and return the regular temperature in Kelvins.
        """
        return str(self.connect()['main']['temp'])

    def high_temperature(self):
        """
        Will connect to the server and sort through the information and return the maximum temperature in Kelvins.
        """
        return str(self.connect()['main']['temp_max'])

    def low_temperature(self):
        """
        Will connect to the server and sort through the information and return the lowest temperature in Kelvins.
        """
        return str(self.connect()['main']['temp_min'])

    def longitude(self):
        """
        Will connect to the server and sort through the information and return the longitude.
        """
        return str(self.connect()['coord']['lon'])

    def latitude(self):
        """
        Will connect to the server and sort through the information and return the latitude.
        """
        return str(self.connect()['coord']['lat'])

    def description(self):
        """
        Will connect to the server and sort through the information and return the description of the current weather.
        """
        return str(self.connect()['weather'][0]['description'])

    def humidity(self):
        """
        Will connect to the server and sort through the information and return the humidity of the current weather.
        """
        return str(self.connect()['main']['humidity'])

    def sunset(self):
        """
        Will connect to the server and sort through the information and return the time the sun sets.
        """
        return str(self.connect()['sys']['sunset'])

    def sunrise(self):
        """
        Will connect to the server and sort through the information and return the time the sun rise.
        """
        return str(self.connect()['sys']['sunrise'])

    def windspeed(self):
        """
        Will connect to the server and sort through the information and return the wind speed.
        """
        return str(self.connect()['wind']['speed'])

    def cloudiness(self):
        """
        Will connect to the server and sort through the information and return the percentage of cloudiness.
        """
        return str(self.connect()['clouds']['all'])

    def city(self):
        """
        Will connect to the server and sort through the information and return the city with the given zipcode.
        """
        return str(self.connect()['name'])

    def transclude(self, message:str) -> str:
        '''
        Replaces keywords in a message with associated API data.
        :param message: The message to transclude
        
        :returns: The transcluded message
        '''
        replacements = {'@weather':self.description,'@weather.temperature':self.temperature,'@weather.high_temperature':self.high_temperature,'@weather.low_temperature':self.low_temperature,'@weather.longitude':self.longitude,'@weather.latitude':self.latitude,'@weather.description':self.description,'@weather.humidity':self.humidity,'@weather.sunset':self.sunset,'@weather.sunrise':self.sunrise,'@weather.windspeed':self.windspeed,'@weather.cloudiness':self.cloudiness,'@weather.city':self.city}
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
    
    temperature = property(temperature)
    high_temperature = property(high_temperature)
    low_temperature = property(low_temperature)
    longitude = property(longitude)
    latitude = property(latitude)
    description = property(description)
    humidity = property(humidity)
    sunset = property(sunset)
    sunrise = property(sunrise)
    windspeed = property(windspeed)
    cloudiness = property(cloudiness)
    city = property(city)
    weather = property(description)
    
