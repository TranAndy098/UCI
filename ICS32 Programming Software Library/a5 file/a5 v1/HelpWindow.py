import tkinter as tk
from tkinter import ttk, filedialog
from Profile import Profile, Post
from NaClProfile import NaClProfile
import ds_client
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
    def __init__(self, root):
        """
        This function is used to initialize the body class to be used by setting up the
        frame, root, , and the draw function to have the outline.
        And sets all the information in place.
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._draw()
        self.set_text_entry()
        self.entry_editor.config(state='disabled')
        


    def set_text_entry(self):
        """
        This function will put the information in the box.
        """
        text = "Supported shorcut keywords for posts and bios: \n (to use just type out keyword then click the API that goes with it) \n OpenWeather: \n @weather - description of weather \n @weather_description - description of weather \n @weather_temperature - temperature today \n @weather_high_temperature - highest temperature today \n @weather_low_temperature - lowest temperature today \n @weather_longitude - longitude of the weather location \n @weather_latitude - latitude of the weather location \n @weather_humidity - percetnage of humanity \n @weather_sunset - time of sunset \n @weather_sunrise - time of sunrise \n @weather_windspeed - speed of wind today \n @weather_cloudiness - percentage of cloudiness \n @weather_city - city name for weather \n LastFM: \n @lastfm - top 3 artists of today \n @lastfm_top_3_artists - top 3 artists of today \n @lastfm_top_3_tracks - top 3 tracks of today \n @lastfm_top_3_albums - top 3 albums of today \n @lastfm_top_3_tags - top 3 tags of today \n ExtraCreditAPI: \n @extracredit - a random quote"
        self.entry_editor.delete(0.0,'end')
        self.entry_editor.insert(0.0, text)



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
    This subclass consists of the close button.
    
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

   

    def close_click(self):
        """
        Calls the callback function specified in the close callback class attribute, if
        available, when the close button has been clicked. Will close the widget window
        and return to the main window.
        """
        self.root.destroy()

    def _draw(self):
        """
        Is called upon initialization to add the footer to the overall frame.
        """

        cancel_button = tk.Button(master=self, text="Close", width=5)
        cancel_button.configure(command=self.close_click)
        cancel_button.pack(fill=tk.BOTH, side=tk.LEFT, padx=5, pady=5)
        
        self.footer_label = tk.Label(master=self, text="")
        self.footer_label.pack(fill=tk.BOTH, side=tk.LEFT, padx=5)

class MainApp(tk.Frame):
    """
    The subclass that is used to make up the main frame of the GUI.
    This subclass consists of the body frame and the footer frame
    and all of its buttons.
    """
    def __init__(self, root):
        """
        This function is used to initialize the main class to be used by setting up the
        frame, root, and the draw function to have the outline.
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._draw()


    def _draw(self):
        """
        Is called upon initialization to add the main part to the overall frame.
        """
        self.body = Body(self.root)
        self.body.pack(fill=tk.BOTH, side=tk.TOP, expand=True)
        self.footer = Footer(self.root)
        self.footer.pack(fill=tk.BOTH, side=tk.BOTTOM)
