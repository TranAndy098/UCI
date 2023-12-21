# direct_message.py

Run with the following command:

[YOUR PYTHON] GUI.py

NOTE: The framework of the graphical interface was provided by Professor Baldwin of ICS 32.

The GUI.py file is the graphical interface of our project. The GUI takes use of the DirectMessenger class in the ds_messenger.py file and allows for the user to send and receive messages. It is the main program for the user to use when sending messages, and seeing what messages they recieved.

The GUI contains 3 classes: Body, Footer, and MainApp. The MainApp class is the hub for all functions for the buttons in the Footer class. These include the main functionality for the Add User, Refresh, and the Send button. The Footer class connects the functionality of the functions in the MainApp to the GUI. Finally, the Body class manages the text and the inputs from user in response to interactions with the buttons and the text editor.

When refreshing the messages, the GUI user must reclick on the user desired to have the updated messages.

**Additional functions now include use of APIs. Writing @weather, @lastfm, and @extracredit and selecting APIS menu with the corresponsing command allows for the keyword to be updated with the following conditions: @weather - weather, @lastfm - music, @extracredit - a random quote. There is also an option for selecting all three apis at the same time.
**Added a API class that now utilizes API information about the weather, music, and random quotes.

Supported shorcut keywords: 
 (to use just type out keyword then click the API that goes with it) 
 OpenWeather: 
 @weather - description of weather 
 @weather_description - description of weather 
 @weather_temperature - temperature today 
 @weather_high_temperature - highest temperature today 
 @weather_low_temperature - lowest temperature today 
 @weather_longitude - longitude of the weather location 
 @weather_latitude - latitude of the weather location 
 @weather_humidity - percetnage of humanity 
 @weather_sunset - time of sunset 
 @weather_sunrise - time of sunrise 
 @weather_windspeed - speed of wind today 
 @weather_cloudiness - percentage of cloudiness 
 @weather_city - city name for weather 
 LastFM: 
 @lastfm - top 3 artists of today 
 @lastfm_top_3_artists - top 3 artists of today 
 @lastfm_top_3_tracks - top 3 tracks of today 
 @lastfm_top_3_albums - top 3 albums of today 
 @lastfm_top_3_tags - top 3 tags of today 
 ExtraCreditAPI: 
 @extracredit - a random quote


ds_messenger.py:

The file contains the shell for sending and storing user data.

NOTE: The framework of this code was provided by Professor Baldwin of ICS 32.

The ds_messenger.py is the main relayer of information. It contains the funcitonality to send data to the server, store and manage data of the user, and receive messages from the server.

Essentially, the file contains the DirectMessenger Class which sends and receives information from the server utilizing a username, a password, a server id, and a token (which is received from the server via the join function). The DirectMessenger Class is weaved throughout the GUI, mainly the MainApp class.

This file will use the ds_protocol to assembly the messages to be sent.

HelpWindow.py:

A seperate window that contains all the supported functions related to the API keywords.

LastFM.py, ExtraCreditAPI.py, OpenWeather.py:

Additional files that contain API information and collecting API data.

ds_protocol.py:

This file translates information stored in the DirectMessenger Class into JSON format to be readable to the server. The same file contains protocols to translate received messages from the server.


**The username, password, and server ID were all hardcoded into the interface. 
