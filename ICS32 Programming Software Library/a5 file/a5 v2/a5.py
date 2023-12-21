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
import BioEditor
import ServerEditor
import HelpWindow


class Body(tk.Frame):
    """
    The subclass that is used to make up the body of the GUI.
    This subclass consists of the text entry box that allows for the bio to be edited.
    
    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the body portion of the root frame.

    # a list of the Post objects available in the active DSU file
    # After all initialization is complete, call the _draw method to pack the widgets
    # into the Body instance 
    """
    def __init__(self, root, select_callback=None):
        tk.Frame.__init__(self, root)
        self.root = root
        self._select_callback = select_callback
        self._posts = [Post]
        self._draw()
    

    def node_select(self, event):
        """
        This function will register the mouse clicking or selecting in the post tree on the left and
        display the certain posts in the entry box.

        Update the entry_editor with the full post entry when the corresponding node in the posts_tree
        is selected.

        #selections are not 0-based, so subtract one.
        """
        index = int(self.posts_tree.selection()[0])-1
        try:
            entry = self._posts[index].entry
        except:
            entry = self._posts[index-1].entry
        self.set_text_entry(entry)
    

    def get_text_entry(self) -> str:
        """
        This function is used to get the text that is in the entry box and make it into
        a string format that can be a variable or be used by other functions and modules.

        Returns the text that is currently displayed in the entry_editor widget.
        """
        return self.entry_editor.get('1.0', 'end').rstrip()


    def set_text_entry(self, text:str):
        """
        This function will clear the entry box and then set it with the text that is passed in.
        Basically, it will make sure the passed in text is the only thing in the entry box.

        Sets the text to be displayed in the entry_editor widget.
        NOTE: This method is useful for clearing the widget, just pass an empty string.

        # TODO: Write code to that deletes all current text in the self.entry_editor widget
        # and inserts the value contained within the text parameter.
        """
        self.entry_editor.delete(0.0,'end')
        self.entry_editor.insert(0.0, text)
    

    def set_posts(self, posts:list):
        """
        This function is called and will use the posts in the file to fill out the post tree
        on the left of the text entry box by iteriating through it.

        Populates the self._posts attribute with posts from the active DSU file.

        # TODO: Write code to populate self._posts with the post data passed
        # in the posts parameter and repopulate the UI with the new post entries.
        # HINT: You will have to write the delete code yourself, but you can take 
        # advantage of the self.insert_posttree method for updating the posts_tree
        # widget.
        """
        self._posts = posts
        for i in range(len(self._posts)):
            self._insert_post_tree(i+1, self._posts[i])


    def insert_post(self, post: Post):
        """
        Is called to add the new post to the tree.

        Inserts a single post to the post_tree widget.
        """
        self._posts.append(post)
        self._insert_post_tree(len(self._posts)+1, post)


    def reset_ui(self):
        """
        This function will use the set text entry function, this is reseting it or to clear it
        by passing in empty text so the box is in empty.

        Resets all UI widgets to their default state. Useful for when clearing the UI is neccessary such
        as when a new DSU file is loaded, for example.
        """
        self.set_text_entry("")
        self._posts = []
        for item in self.posts_tree.get_children():
            self.posts_tree.delete(item)


    def _insert_post_tree(self, id, post: Post):
        """
        This function is called to insert the post that is being passed in the post tree.

        Inserts a post entry into the posts_tree widget.

        # Since we don't have a title, we will use the first 24 characters of a
        # post entry as the identifier in the post_tree widget.
        """
        entry = post.entry
        if len(entry) > 25:
            entry = entry[:24] + "..."
        self.posts_tree.insert('', id, id, text=entry)
    

    def _draw(self):
        """
        Is called upon initialization to add the body to the overall frame.
        """
        posts_frame = tk.Frame(master=self, width=250)
        posts_frame.pack(fill=tk.BOTH, side=tk.LEFT)
        self.posts_tree = ttk.Treeview(posts_frame)
        self.posts_tree.bind("<<TreeviewSelect>>", self.node_select)
        self.posts_tree.pack(fill=tk.BOTH, side=tk.TOP, expand=True, padx=5, pady=5)

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
    This subclass consists of the two status bars, the online checker,
    and the save post button.
    
    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the footer portion of the root frame.
    """
    def __init__(self, root, save_callback=None, online_callback=None):
        """
        This function is used to initialize the footer class to be used by setting up the
        frame, root, save callback, online callback, and the draw function to have the outline.

        # IntVar is a variable class that provides access to special variables
        # for Tkinter widgets. is_online is used to hold the state of the chk_button widget.
        # The value assigned to is_online when the chk_button widget is changed by the user
        # can be retrieved using he get() function:
        #chk_value = self.is_online.get()
        # After all initialization is complete, call the _draw method to pack the widgets
        # into the Footer instance 
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._save_callback = save_callback
        self._online_callback = online_callback
        self.is_online = tk.IntVar()
        self._draw()
    

    def online_click(self):
        """
        Calls the callback function specified in the online_callback class attribute, if
        available, when the chk_button widget has been clicked.

        # TODO: Add code that implements a callback to the chk_button click event.
        # The callback should support a single parameter that contains the value
        # of the self.is_online widget variable.
        """
        if self._online_callback is not None:
            self._online_callback(self.is_online)


    def save_click(self):
        """
        Calls the callback function specified in the save_callback class attribute, if
        available, when the save_button has been clicked.
        """
        if self._save_callback is not None:
            self._save_callback()

    def set_status(self, message):
        """
        This function is called to replace the text in the status bar in the footer.

        Updates the text that is displayed in the footer_label widget
        """
        self.footer_label.configure(text=message)

    def set_status_two(self, message):
        """
        This function is called to replace the text in the status bar in the footer.

        Updates the text that is displayed in the footer_label widget
        """
        self.footer_label_two.configure(text=message)
    

    def _draw(self):
        """
        Is called upon initialization to add the footer to the overall frame.
        """
        save_button = tk.Button(master=self, text="Save Post", width=20)
        save_button.configure(command=self.save_click)
        save_button.pack(fill=tk.BOTH, side=tk.RIGHT, padx=5, pady=5)

        self.chk_button = tk.Checkbutton(master=self, text="Online", variable=self.is_online)
        self.chk_button.configure(command=self.online_click) 
        self.chk_button.pack(fill=tk.BOTH, side=tk.RIGHT)

        self.footer_label = tk.Label(master=self, text="Ready.")
        self.footer_label.pack(fill=tk.BOTH, side=tk.LEFT, padx=5)
        self.footer_label_two = tk.Label(master=self, text="")
        self.footer_label_two.pack(fill=tk.BOTH, side=tk.LEFT, padx=5)


class MainApp(tk.Frame):
    """
    The subclass that is used to make up the main frame of the GUI.
    This subclass consists of the menu bar, body frame and all of its contents,
    and the footer frame and all of its buttons and status bars.

    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the main portion of the root frame. Also manages all method calls for
    the NaClProfile class.
    """
    def __init__(self, root):
        """
        This function is used to initialize the main class to be used by setting up the
        frame, root, current profile being used, have the online status, and the draw
        function to have
        the outline.

        # Initialize a new NaClProfile and assign it to a class attribute.

        # After all initialization is complete, call the _draw method to pack the widgets
        # into the root frame
        """
        tk.Frame.__init__(self, root)
        self.root = root
        self._current_profile = NaClProfile()
        self._draw()
        self._is_online = False
        self._profile_filename = None


    def new_profile(self):
        """
        This fucntion is used to create a new dsu file to store the information that will be
        created and inputted.
        
        Creates a new DSU file when the 'New' menu item is clicked.

        # TODO Write code to perform whatever operations are necessary to prepare the UI for
        # a new DSU file.
        # HINT: You will probably need to do things like generate encryption keys and reset the ui.
        """
        try:
            filename = tk.filedialog.asksaveasfile(filetypes=[('Distributed Social Profile', '.dsu')], defaultextension=[('Distributed Social Profile', '.dsu')])
            self._profile_filename = filename.name
            self._current_profile.generate_keypair()
            self.body.reset_ui()
            self._current_profile.dsuserver = '168.235.86.101'
            self._current_profile.username = 'DefaultUserName'
            self._current_profile.password = 'EasyPassword'
            self._current_profile._posts = []
            self._current_profile.save_profile(self._profile_filename)
        except:
            self.footer.set_status_two('No File Was Created')

    
    def open_profile(self):
        """
        Will open the file that is being passed in as the current profile file name and
        load the information needed like the keypair.
        Then will reset the UI to be prepared to have the empty text box displayed.

        Opens an existing DSU file when the 'Open' menu item is clicked and loads the profile
        data into the UI.

        # TODO: Write code to perform whatever operations are necessary to prepare the UI for
        # an existing DSU file.
        # HINT: You will probably need to do things like load a profile, import encryption keys 
        # and update the UI with posts.
        """
        try:
            filename = tk.filedialog.askopenfile(filetypes=[('Distributed Social Profile', '*.dsu')])
            self._profile_filename = filename.name
            self.footer.set_status_two('File Selected: {}'.format(self._profile_filename))
            self._current_profile = NaClProfile()
            self._current_profile.load_profile(self._profile_filename)
            if self._current_profile.dsuserver == None:
                self._current_profile.dsuserver = '168.235.86.101'
            if self._current_profile.username == None:
                self._current_profile.username = 'DefaultUserName'
            if self._current_profile.password == None:
                self._current_profile.password = 'EasyPassword'
            self._current_profile.import_keypair(self._current_profile.keypair)
            self.body.reset_ui()
            self.body.set_posts(self._current_profile.get_posts())
        except:
            self.footer.set_status_two('No File Was Selected')
    

    def close(self):
        """
        This is used to close the widget.

        Closes the program when the 'Close' menu item is clicked.
        """
        self.root.destroy()


    def save_profile(self):
        """
        This function is used to save the posts to the file. If online is checked
        then it will try to send it to the server.

        Saves the text currently in the entry_editor widget to the active DSU file.

        # TODO: Write code to perform whatever operations are necessary to save a 
        # post entry when the user clicks the save_button widget.
        # HINT: You will probably need to do things like create a new Post object,
        # fill it with text, add it to the active profile, save the profile, and
        # clear the editor_entry UI for a new post.
        # This might also be a good place to check if the user has selected the online
        # checkbox and if so send the message to the server.
        """
        if self.body.get_text_entry() != '':
            post = Post(self.body.get_text_entry())
            self.body.insert_post(post)
            self._current_profile.add_post(post)
            self._current_profile.save_profile(self._profile_filename)
            self.body.set_text_entry("")
            self.footer.set_status_two("Post Saved")
            if self._is_online is True:
                self.publish(post)
        else:
            self.footer.set_status_two("Cannot Post Nothing or Whitespace")


    def publish(self, post:Post):
        """
        This function is used to connect to the server using the ds_client module to do so.
        This will then send the post for the specified user.
        If it fails to do so then it will put in the status bar the specfic message.
        """
        text = post.get_entry()
        try:
            self.footer.set_status_two("Connecting to Server to Post")
            connect = ds_client.connect(self._current_profile.dsuserver, 2021)
            if connect != None:
                join_msg = ds_protocol.joinmsg(self._current_profile.username, self._current_profile.password, self._current_profile.public_key)
                response = ds_client.write(connect, join_msg)
                server_response = ds_protocol.extract_response_typ(response)
                server_token = ds_protocol.extract_token(response)
                if server_response == 'ok':
                    typ = ds_client.post(connect, self._current_profile.public_key, self._current_profile.private_key, server_token, text, str(time.time()))
                    self.footer.set_status_two("Post Has Been Posted")
                else:
                    self.footer.set_status_two("Could Not Join Server")
            else:
                self.footer.set_status_two("Could Not Connect to Server")
        except:
            self.footer.set_status_two("Unable to Connect to Server, maybe DSUServer is incorrect")


    def online_changed(self, value:bool):
        """
        This function is used to show if the onine box is checked or not and will update the status bar accordingly.

        A callback function for responding to changes to the online chk_button.

        # TODO: 
        # 1. Remove the existing code. It has been left here to demonstrate
        # how to change the text displayed in the footer_label widget and
        # assist you with testing the callback functionality (if the footer_label
        # text changes when you click the chk_button widget, your callback is working!).
        # 2. Write code to support only sending posts to the DSU server when the online chk_button
        # is checked.
        """
        value = value.get()
        self._is_online = bool(value)
        if value == 1:
            self.footer.set_status("Online")
        else:
            self.footer.set_status("Offline")


    def openweathert(self):
        """
        This is the Open Weather API that is in the menu bar that will scan through the text
        entry box when called and replace the certain keywords wtih the information that is
        requested.
        """
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        open_weather = OpenWeather("92841","US","824eab18432eee3e404cff1e4df28b87")
        texts = open_weather.transclude(text)
        self.body.set_text_entry(texts)
        self.footer.set_status_two('Done Transcluding')    


    def lastfmt(self):
        """
        This is the Last FM API that is in the menu bar that will scan through the text
        entry box when called and replace the certain keywords wtih the information that is
        requested.
        """
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        lf = LastFM("8725d482c1ff93a7147673296a1f4144")
        texts = lf.transclude(text)
        self.body.set_text_entry(texts)
        self.footer.set_status_two('Done Transcluding')       


    def extracreditt(self):
        """
        This is the Extra Credit API that is in the menu bar that will scan through the text
        entry box when called and replace the @extracredit keywords wtih the random quote that is
        requested.
        """
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        texts = ExtraCreditAPI().transclude(text)
        self.body.set_text_entry(texts)
        self.footer.set_status_two('Done Transcluding')


    def all_apis(self):
        """
        This will do the job of all the other 3 to scan through the text entry box when called
        and replace the certain keywords wtih the information that isrequested.
        """
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        open_weather = OpenWeather("92841","US","824eab18432eee3e404cff1e4df28b87")
        text = open_weather.transclude(text)
        lf = LastFM("8725d482c1ff93a7147673296a1f4144")
        text = lf.transclude(text)
        texts = ExtraCreditAPI().transclude(text)
        self.body.set_text_entry(texts)
        self.footer.set_status_two('Done Transcluding')


    def bio_editor(self):
        """
        Will open the bio editor widget to allow the user to edit their bio.
        """
        if self._profile_filename == None:
            self.footer.set_status_two('Can Not Load Settings With No File')
        else:
            new_window = tk.Tk()
            new_window.title("Bio Editor")
            new_window.geometry("600x420")
            new_window.option_add('*tearOff', False)
            BioEditor.MainApp(new_window,self._profile_filename)
            new_window.update()
            new_window.minsize("600", "420")
            new_window.maxsize("600", "420")
            new_window.mainloop()
            self._current_profile.load_profile(self._profile_filename)


    def server_editor(self):
        """
        Will open the server editor widget to allow the user to edit their dsuserver.
        """
        if self._profile_filename == None:
            self.footer.set_status_two('Can Not Load Settings With No File')
        else:
            new_window = tk.Tk()
            new_window.title("DSUServer Editor")
            new_window.geometry("600x420")
            new_window.option_add('*tearOff', False)
            ServerEditor.MainApp(new_window,self._profile_filename)
            new_window.update()
            new_window.minsize("600", "420")
            new_window.maxsize("600", "420")
            new_window.mainloop()
            self._current_profile.load_profile(self._profile_filename)
        
    def help_window(self):
        """
        Will open the help information widget to allow the user to see the help information.
        """
        new_window = tk.Tk()
        new_window.title("Help")
        new_window.geometry("600x420")
        new_window.option_add('*tearOff', False)
        HelpWindow.MainApp(new_window)
        new_window.update()
        new_window.minsize("600", "420")
        new_window.maxsize("600", "420")
        new_window.mainloop()


    def _draw(self):
        """
        Is called upon initialization to add the main part to the overall frame.

        # Build a menu and add it to the root frame.

        # NOTE: Additional menu items can be added by following the conventions here.
        # The only top level menu item is a 'cascading menu', that presents a small menu of
        # command items when clicked. But there are others. A single button or checkbox, for example,
        # could also be added to the menu bar.

        # The Body and Footer classes must be initialized and packed into the root window.

        # TODO: Add a callback for detecting changes to the online checkbox widget in the Footer class. Follow
        # the conventions established by the existing save_callback parameter.
        # HINT: There may already be a class method that serves as a good callback function!
        """
        menu_bar = tk.Menu(self.root)
        self.root['menu'] = menu_bar
        menu_file = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_file, label='File')
        menu_file.add_command(label='New', command=self.new_profile)
        menu_file.add_command(label='Open...', command=self.open_profile)
        menu_file.add_command(label='Close', command=self.close)

        self.body = Body(self.root, self._current_profile)
        self.body.pack(fill=tk.BOTH, side=tk.TOP, expand=True)

        menu_apis = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_apis, label='APIS')
        menu_apis.add_command(label='ALL 3 APIS', command=self.all_apis)
        menu_apis.add_command(label='Weather', command=self.openweathert)
        menu_apis.add_command(label='LastFM', command=self.lastfmt)
        menu_apis.add_command(label='ExtraCredit(Random Quote)', command=self.extracreditt)

        menu_setting = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_setting, label='Settings')
        menu_setting.add_command(label='Bio Editor', command=self.bio_editor)
        menu_setting.add_command(label='DSUServer Editor', command=self.server_editor)

        menu_help = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_help, label='Help')
        menu_help.add_command(label='Help', command=self.help_window)

        self.footer = Footer(self.root, save_callback=self.save_profile, online_callback=self.online_changed)
        self.footer.pack(fill=tk.BOTH, side=tk.BOTTOM)

if __name__ == "__main__":
    """
    # All Tkinter programs start with a root window. We will name ours 'main'.
    
    # 'title' assigns a text value to the Title Bar area of a window.
    
    # This is just an arbitrary starting point. You can change the value around to see how
    # the starting size of the window changes. I just thought this looked good for our UI.
    
    # adding this option removes some legacy behavior with menus that modern OSes don't support. 
    # If you're curious, feel free to comment out and see how the menu changes.
    
    # Initialize the MainApp class, which is the starting point for the widgets used in the program.
    # All of the classes that we use, subclass Tk.Frame, since our root frame is main, we initialize 
    # the class with it.
    
    # When update is called, we finalize the states of all widgets that have been configured within the root frame.
    # Here, Update ensures that we get an accurate width and height reading based on the types of widgets
    # we have used.
    # minsize prevents the root window from resizing too small. Feel free to comment it out and see how
    # the resizing behavior of the window changes.

    # And finally, start up the event loop for the program (more on this in lecture).
    """
    main = tk.Tk()
    main.title("ICS 32 Distributed Social")
    main.geometry("720x480")
    main.option_add('*tearOff', False)
    MainApp(main)
    main.update()
    main.minsize(main.winfo_width(), main.winfo_height())
    main.mainloop()
