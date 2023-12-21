from OpenWeather import OpenWeather

zipcode = "92841"
ccode = "US"
apikey = "824eab18432eee3e404cff1e4df28b871"

open_weather = OpenWeather(zipcode,ccode,apikey)
print(f"The temperature for {zipcode} is {open_weather.temperature} degrees")
print(f"The high for today in {zipcode} will be {open_weather.high_temperature} degrees")
print(f"The low for today in {zipcode} will be {open_weather.low_temperature} degrees")
print(f"The coordinates for {zipcode} are {open_weather.longitude} longitude and {open_weather.latitude} latitude")
print(f"The current weather for {zipcode} is {open_weather.description}")
print(f"The current humidity for {zipcode} is {open_weather.humidity}")
print(f"The sun will set in {open_weather.city} at {open_weather.sunset}")
print(f"The sun will rise in {open_weather.city} at {open_weather.sunrise}")
print(f"The current windspeed for {zipcode} is {open_weather.windspeed}")
print(f"The current cloudiness for {zipcode} is {open_weather.cloudiness}")

p = "i love how @weather is @weather_sunrise, >?: @weather_sunset @weather @weather_description @weather_temperature @weather_high_temperature @weather_low_temperature @weather_longitude @weather_latitude @weather_humidity @weather_windspeed @weather_cloudiness @weather_city"
print(p)
if '@' in p:
    p = open_weather.transclude(p)
print(p)
