import tkinter as tk
from tkinter import ttk, filedialog
from Profile import Profile, Post
from NaClProfile import NaClProfile
import ds_client
import ds_protocol
import asyncio, time, json
from ExtraCreditAPI import ExtraCreditAPI
from OpenWeather import OpenWeather
from LastFM import LastFM


class Body(tk.Frame):
    """
    The subclass that is used to make up the body of the GUI.
    This subclass consists of the text entry box that allows for the bio to be edited.
    
    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the body portion of the root frame.
    """
    def __init__(self, root, select_callback=None):
        """
        This function is used to initialize the body class to be used by setting up the
        frame, root, select callback, and the draw function to have the outline.
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._select_callback = select_callback
        self._draw()

    def get_text_entry(self) -> str:
        """
        This function is used to get the text that is in the entry box and make it into
        a string format that can be a variable or be used by other functions and modules.
        """
        return self.entry_editor.get('1.0', 'end').rstrip()


    def set_text_entry(self, text:str):
        """
        This function will clear the entry box and then set it with the text that is passed in.
        Basically, it will make sure the passed in text is the only thing in the entry box.
        """
        self.entry_editor.delete(0.0,'end')
        self.entry_editor.insert(0.0, text)
    

    def reset_ui(self):
        """
        This function will use the set text entry function, this is reseting it or to clear it
        by passing in empty text so the box is in empty.
        """
        self.set_text_entry("")


    def _draw(self):
        """
        Is called upon initialization to add the body to the overall frame.
        """
        posts_frame = tk.Frame(master=self, width=0)
        posts_frame.pack(fill=tk.BOTH, side=tk.LEFT)

        entry_frame = tk.Frame(master=self, bg="")
        entry_frame.pack(fill=tk.BOTH, side=tk.TOP, expand=True)
        
        editor_frame = tk.Frame(master=entry_frame, bg="red")
        editor_frame.pack(fill=tk.BOTH, side=tk.LEFT, expand=True)
        
        scroll_frame = tk.Frame(master=entry_frame, bg="blue", width=10)
        scroll_frame.pack(fill=tk.BOTH, side=tk.LEFT, expand=False)
        
        self.entry_editor = tk.Text(editor_frame, width=0)
        self.entry_editor.pack(fill=tk.BOTH, side=tk.LEFT, expand=True, padx=0, pady=0)

        entry_editor_scrollbar = tk.Scrollbar(master=scroll_frame, command=self.entry_editor.yview)
        self.entry_editor['yscrollcommand'] = entry_editor_scrollbar.set
        entry_editor_scrollbar.pack(fill=tk.Y, side=tk.LEFT, expand=False, padx=0, pady=0)


class Footer(tk.Frame):
    """
    The subclass that is used to make up the footer of the GUI.
    This subclass consists of the close button, save to server, save to file, and also
    a status bar to replace printing in idle by showing messages that would have been
    printed instead.
    
    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the footer portion of the root frame.
    """
    def __init__(self, root, save_file_callback=None, save_server_callback=None):
        """
        This function is used to initialize the footer class to be used by setting up the
        frame, root, save file callback, save to server callback, and the draw function to have the outline.
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._save_file_callback = save_file_callback
        self._save_server_callback = save_server_callback
        self._draw()
        
            
    def save_file_click(self):
        """
        Calls the callback function specified in the save file callback class attribute, if
        available, when the save to file button has been clicked. This will call the save to
        file fucntion which will simply overwrite the current bio in there or replace it and
        save.
        """
        if self._save_file_callback is not None:
            self._save_file_callback()

    def save_server_click(self):
        """
        Calls the callback function specified in the save server callback class attribute, if
        available, when the save to server button has been clicked. This will call the save to
        server function which will connect to the DSUServer to send the bio to it along with
        the required information to do so.
        """
        if self._save_server_callback is not None:
            self._save_server_callback()

    def close_click(self):
        """
        Calls the callback function specified in the close callback class attribute, if
        available, when the close button has been clicked. Will close the widget window
        and return to the main window.
        """
        self.root.destroy()

    def set_status(self, message):
        """
        This function is called to replace the text in the status bar in the footer.
        """
        self.footer_label.configure(text=message)

    def _draw(self):
        """
        Is called upon initialization to add the footer to the overall frame.
        """
        saves_button = tk.Button(master=self, text="Save Bio to Server and File", width=20)
        saves_button.configure(command=self.save_server_click)
        saves_button.pack(fill=tk.BOTH, side=tk.RIGHT, padx=5, pady=5)

        savef_button = tk.Button(master=self, text="Save Bio to File Only", width=15)
        savef_button.configure(command=self.save_file_click)
        savef_button.pack(fill=tk.BOTH, side=tk.RIGHT, padx=5, pady=5)

        cancel_button = tk.Button(master=self, text="Close", width=5)
        cancel_button.configure(command=self.close_click)
        cancel_button.pack(fill=tk.BOTH, side=tk.LEFT, padx=5, pady=5)
        
        self.footer_label = tk.Label(master=self, text="")
        self.footer_label.pack(fill=tk.BOTH, side=tk.LEFT, padx=5)


class MainApp(tk.Frame):
    """
    The subclass that is used to make up the main frame of the GUI.
    This subclass consists of the menu bar, body frame and all of its contents,
    and the footer frame and all of its buttons and status bars.

    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the main portion of the root frame. Also manages all method calls for
    the NaClProfile class.
    """
    def __init__(self, root, file):
        """
        This function is used to initialize the main class to be used by setting up the
        frame, root, current profile being used, profile filename which is passed in when
        intialized so this widget has the file that is used, opens the porfile to have the
        inforamtion, display the bio in the text entry box, and the draw function to have
        the outline.
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._current_profile = NaClProfile()
        self._draw()
        self._profile_filename = file
        self.open_profile()
        self.bio_display()

    def open_profile(self):
        """
        Will open the file that is being passed in as the current profile file name and
        load the information needed like the keypair.
        Then will reset the UI to be prepared to have the bio displayed.
        """
        self._profile_filename
        self._current_profile = NaClProfile()
        self._current_profile.load_profile(self._profile_filename)
        self._current_profile.import_keypair(self._current_profile.keypair)
        self.body.reset_ui()


    def close(self):
        """
        This is used to close the widget.
        """
        self.root.destroy()

    def save_profile_server(self):
        """
        This function is used to connect to the server using the ds_client module to do so.
        This will then update the bio for the specified user.
        If it fails to do so then it will put in the status bar the specfic message.
        """
        text = self.body.get_text_entry()
        try:
            self.footer.set_status("Connecting to Server to Send Bio")
            connect = ds_client.connect(self._current_profile.dsuserver, 2021)
            if connect != None:
                join_msg = ds_protocol.joinmsg(self._current_profile.username, self._current_profile.password, self._current_profile.public_key)
                response = ds_client.write(connect, join_msg)
                server_response = ds_protocol.extract_response_typ(response)
                server_token = ds_protocol.extract_token(response)
                if server_response == 'ok':
                    typ = ds_client.bios(connect, self._current_profile.public_key, self._current_profile.private_key, server_token, text, str(time.time()))
                    self.footer.set_status("Bio Updated, closing now")
                    self._current_profile.bio = text
                    self._current_profile.save_profile(self._profile_filename)
                    self.close()
                else:
                    self.footer.set_status("Could Not Join Server")
                    self.body.set_text_entry(text)
            else:
                self.footer.set_status("Could Not Connect to Server")
                self.body.set_text_entry(text)
        except:
            self.footer.set_status("Unable to Connect to Server, maybe DSUServer is incorrect")
            self.body.set_text_entry(text)


    def save_profile_file(self):
        """
        This function is used to save the bio to the file.
        """
        text = self.body.get_text_entry()
        self._current_profile.bio = text
        self._current_profile.save_profile(self._profile_filename)
        self.close()


    def openweathert(self):
        """
        This is the Open Weather API that is in the menu bar that will scan through the text
        entry box when called and replace the certain keywords wtih the information that is
        requested.
        """
        text = self.body.get_text_entry()
        open_weather = OpenWeather("92841","US","824eab18432eee3e404cff1e4df28b87")
        texts = open_weather.transclude(text)
        self.body.set_text_entry(texts)        

    def lastfmt(self):
        """
        This is the Last FM API that is in the menu bar that will scan through the text
        entry box when called and replace the certain keywords wtih the information that is
        requested.
        """
        text = self.body.get_text_entry()
        lf = LastFM("8725d482c1ff93a7147673296a1f4144")
        texts = lf.transclude(text)
        self.body.set_text_entry(texts)        

    def extracreditt(self):
        """
        This is the Extra Credit API that is in the menu bar that will scan through the text
        entry box when called and replace the @extracredit keywords wtih the random quote that is
        requested.
        """
        text = self.body.get_text_entry()
        texts = ExtraCreditAPI().transclude(text)
        self.body.set_text_entry(texts)

    def all_apis(self):
        """
        This will do the job of all the other 3 to scan through the text entry box when called
        and replace the certain keywords wtih the information that isrequested.
        """
        text = self.body.get_text_entry()
        open_weather = OpenWeather("92841","US","824eab18432eee3e404cff1e4df28b87")
        text = open_weather.transclude(text)
        lf = LastFM("8725d482c1ff93a7147673296a1f4144")
        text = lf.transclude(text)
        texts = ExtraCreditAPI().transclude(text)
        self.body.set_text_entry(texts)
    
    def bio_display(self):
        """
        This will place the current bio in the entry text box, if it is empty then nothing is displayed.
        """
        self.open_profile()
        self.body.set_text_entry(self._current_profile.bio)
        

    def _draw(self):
        """
        Is called upon initialization to add the main part to the overall frame.
        """
        menu_bar = tk.Menu(self.root)
        self.root['menu'] = menu_bar

        self.body = Body(self.root, self._current_profile)
        self.body.pack(fill=tk.BOTH, side=tk.TOP, expand=True)

        menu_apis = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_apis, label='APIS')
        menu_apis.add_command(label='ALL 3 APIS', command=self.all_apis)
        menu_apis.add_command(label='Weather', command=self.openweathert)
        menu_apis.add_command(label='LastFM', command=self.lastfmt)
        menu_apis.add_command(label='ExtraCredit(Random Quote)', command=self.extracreditt)

        self.footer = Footer(self.root, save_file_callback=self.save_profile_file, save_server_callback=self.save_profile_server)
        self.footer.pack(fill=tk.BOTH, side=tk.BOTTOM)

