
from ExtraCreditAPI import ExtraCreditAPI
from OpenWeather import OpenWeather
from LastFM import LastFM


def change_message(message):
    if '@e' in message:
        ec = ExtraCreditAPI()
        message = ec.transclude(message)
    print('Message before possible changes:{}'.format(message))
    if '@w' in message:
        location_choice = input('Do you want to use Irvine, CA as the location for the weather? (Y/N)')
        while location_choice != 'Y':
            if location_choice == 'N':
                zipcode = str(input('What is your 5 digit zip code?'))
                ccode = str(input('What is your country code?'))
                if (len(zipcode) == 5) and ((ccode.isspace() == False) and (ccode != '')):
                    break
                else:
                    print('invalid zipcode and/or country code format')
            else:
                print('Please input correct format')
                location_choice = input('Do you want to use Irvine, CA as the location for the weather? (Y/N)')
        if location_choice == 'Y':
            zipcode = "92697"
            ccode = "US"
        apikey_choice = input('Do you want to use your own apikey? (Y/N)')
        while apikey_choice != 'N':
            if apikey_choice == 'Y':
                apikey = str(input('What is your apikey?'))
                if (apikey.isspace() == False) and (apikey != ''):
                    break
                else:
                    print('invalid apikey format')
            else:
                print('Please input correct format')
                apikey_choice = input('Do you want to use your own apikey? (Y/N)')
        if apikey_choice == 'N':
            apikey = "824eab18432eee3e404cff1e4df28b87"
        open_weather = OpenWeather(zipcode,ccode,apikey)
        message = open_weather.transclude(message)
    print(message)
    if '@l' in message:
        apikey_choice = input('Do you want to use your own apikey? (Y/N)')
        while apikey_choice != 'N':
            if apikey_choice == 'Y':
                apikey = str(input('What is your apikey?'))
                if (apikey.isspace() == False) and (apikey != ''):
                    break
                else:
                    print('invalid apikey format')
            else:
                print('Please input correct format')
                apikey_choice = input('Do you want to use your own apikey? (Y/N)')
        if apikey_choice == 'N':
            apikey = "8725d482c1ff93a7147673296a1f4144"
        lf = LastFM(apikey)
        message = lf.transclude(message)
    print('Message after possible changes:{}'.format(message))
    return message


"""
def trans(message):
    if '@e' in message:
        ec = ExtraCreditAPI()
        message = ec.transclude(message)
    print(message)
    if '@w' in message:
        zipcode = "92841"
        ccode = "US"
        apikey = "824eab18432eee3e404cff1e4df28b871"
        open_weather = OpenWeather(zipcode,ccode,apikey)
        message = open_weather.transclude(message)
    print(message)
    if '@l' in message:
        apikey = "8725d482c1ff93a7147673296a1f4144"
        lf = LastFM(apikey)
        message = lf.transclude(message)
    print(message)
    return message
    """



p = "i love how @lastfm is @lastfm_top_5artists. is @lastfm_top_5tracks, is @lastfm_top_5albums is @lastfm_top_5tags"
x = change_message(p)
print(x)
