import urllib, json
from urllib import request,error
import re

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

    def weather(self):
        """
        Will connect to the server and sort through the information and return the description of the current weather.
        """
        try:
            return str(self.connect()['weather'][0]['description'])
        except:
            return '@weather'

    def temperature(self):
        """
        Will connect to the server and sort through the information and return the regular temperature in Kelvins.
        """
        try:
            return str(self.connect()['main']['temp'])
        except:
            return '@weather_temperature'

    def high_temperature(self):
        """
        Will connect to the server and sort through the information and return the maximum temperature in Kelvins.
        """
        try:
            return str(self.connect()['main']['temp_max'])
        except:
            return '@weather_high_temperature'

    def low_temperature(self):
        """
        Will connect to the server and sort through the information and return the lowest temperature in Kelvins.
        """
        try:
            return str(self.connect()['main']['temp_min'])
        except:
            return '@weather_low_temperature'

    def longitude(self):
        """
        Will connect to the server and sort through the information and return the longitude.
        """
        try:
            return str(self.connect()['coord']['lon'])
        except:
            return '@weather_longitude'

    def latitude(self):
        """
        Will connect to the server and sort through the information and return the latitude.
        """
        try:
            return str(self.connect()['coord']['lat'])
        except:
            return '@weather_latitude'

    def description(self):
        """
        Will connect to the server and sort through the information and return the description of the current weather.
        """
        try:
            return str(self.connect()['weather'][0]['description'])
        except:
            return '@weather_description'

    def humidity(self):
        """
        Will connect to the server and sort through the information and return the humidity of the current weather.
        """
        try:
            return str(self.connect()['main']['humidity'])
        except:
            return '@weather_humidity'

    def sunset(self):
        """
        Will connect to the server and sort through the information and return the time the sun sets.
        """
        try:
            return str(self.connect()['sys']['sunset'])
        except:
            return '@weather_sunset'

    def sunrise(self):
        """
        Will connect to the server and sort through the information and return the time the sun rise.
        """
        try:
            return str(self.connect()['sys']['sunrise'])
        except:
            return '@weather_sunrise'

    def windspeed(self):
        """
        Will connect to the server and sort through the information and return the wind speed.
        """
        try:
            return str(self.connect()['wind']['speed'])
        except:
            return '@weather_windspeed'

    def cloudiness(self):
        """
        Will connect to the server and sort through the information and return the percentage of cloudiness.
        """
        try:
            return str(self.connect()['clouds']['all'])
        except:
            return '@weather_cloudiness'

    def city(self):
        """
        Will connect to the server and sort through the information and return the city with the given zipcode.
        """
        try:
            return str(self.connect()['name'])
        except:
            return '@weather_city'

    def transclude(self, message:str) -> str:
        '''
        Replaces keywords in a message with associated API data.
        :param message: The message to transclude
        
        :returns: The transcluded message
        '''
        replacements = {'@weather':self.weather,'@weather_temperature':self.temperature,'@weather_high_temperature':self.high_temperature,'@weather_low_temperature':self.low_temperature,'@weather_longitude':self.longitude,'@weather_latitude':self.latitude,'@weather_description':self.description,'@weather_humidity':self.humidity,'@weather_sunset':self.sunset,'@weather_sunrise':self.sunrise,'@weather_windspeed':self.windspeed,'@weather_cloudiness':self.cloudiness,'@weather_city':self.city}
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

    weather = property(weather)
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
    
