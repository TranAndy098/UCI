The Extra Credits, I implemented into the GUI.

1. API Implementations
- I added the API data into the toolbar under “APIS”
- The supported apis are OpenWeather, LastFM, and My Extra Credit Api, which generates a random quote.
- To find all the supported keywords, the user can check under “Help.”
- The user will type in the desired keyword into the text entry box then click on the API desired to overwrite the keywords.
- If the user uses all the types, there is an easy way to have the keywords replaced with one click instead of each individual click.
- The APIs have hardcoded api keys, zip code, and country code to avoid any errors.

2. Bio Editor/Adder
- The Bio Editor is in the toolbar under “Settings.”
- This will open a new window that will set the text entry box to the bio in the file, if it is empty then it will be blank.
- The user can type whatever they desire.
- The user can enter in whitespace or nothing to clear there bio.
- The APIs are also supported for the Bio Editor.
- The Bio Editor has 4 features in the footer.
- The Close Button will close the window without saving.
- There is a status bar that will display a message if a problem occurs like the DSUServer cannot be connected to.
- The Save to File Button will save the bio to the file in the dsu file that is passed in when the editor is opened, regardless if the server works or not.
- The Save to Server Button will save the bio to the server and if it successfully saves then it will save to the file, if not then it will inform the user of the problem in the status bar and prompt the user to try again.

3. DSUServer Editor/Adder
- The Server Editor is in the toolbar under “Settings.”
- This will open a new window that will set the text entry box to the dsuserver in the file.
- The user can change whatever they desire.
- The user can not make the server blank because there is no such thing is connecting to a empty ip address.
- The Server Editor has 4 features in the footer.
- The Close Button will close the window without saving.
- There is a status bar that will display a message if a problem occurs like the DSUServer cannot be connected to.
- The Save to File Button will save the server to the file in the dsu file that is passed in when the editor is opened, regardless if the server can be connected to or not.
- The Save to Server Button will try to connect to the server and if it successfully connects then it will save to the file, if not then it will inform the user of the problem in the status bar and prompt the user to try again.

