import tkinter as tk
from tkinter import ttk, filedialog
from ds_messenger import DirectMessenger, ConnectionException
import HelpWindow
from ExtraCreditAPI import ExtraCreditAPI
from OpenWeather import OpenWeather
from LastFM import LastFM

class API:
    def __init__(self):
        self.zipcode = '92617'
        self.country = 'US'
        self.owa = "824eab18432eee3e404cff1e4df28b87"
        self.lfma = "8725d482c1ff93a7147673296a1f4144"


class Body(tk.Frame):
    """
    A subclass of tk.Frame that is responsible for drawing all of the widgets in the body portion of the root frame.
    """
    def __init__(self, root):
        tk.Frame.__init__(self, root)
        self.root = root
        self.recipient = None
        self._users = {}
        self._draw()
        self.msg_view.config(state='disabled')


    def node_select(self, event):
        """
        This function will register the mouse clicking or selecting in the user tree on the left and
        display the messages recieved in the msg_view box.

        Update the msg_view with the user when the corresponding node in the user_tree
        is selected.
        """
        index = int(self.user_tree.selection()[0])-2
        l = list(self._users)
        try:
            user = l[index]
        except:
            index = int(self.user_tree.selection()[0])-3
            user = l[index]
        entry = ''
        self.recipient = user
        for users in self._users:
            if users == user:
                for i in range(len(self._users[user])):
                    entry = entry + '{} @ {}'.format(self._users[user][i]['message'], self._users[user][i]['timestamp']) + '\n'
        self.msg_view.config(state='normal')
        self.msg_view.delete(0.0, 'end')
        self.msg_view.insert(0.0, entry)
        self.msg_view.config(state='disabled')


    def get_text_entry(self) -> str:
        """
        This function is used to get the text that is in the entry box and make it into
        a string format that can be a variable or be used by other functions and modules.

        Returns the text that is currently displayed in the msg_editor widget.
        """
        return self.msg_editor.get('1.0', 'end').rstrip()


    def set_text_entry(self, text:str):
        """
        This function will clear the entry box and then set it with the text that is passed in.
        Basically, it will make sure the passed in text is the only thing in the entry box.

        Sets the text to be displayed in the msg_editor widget.
        NOTE: This method is useful for clearing the widget, just pass an empty string.
        """
        self.msg_editor.delete(0.0, 'end')
        self.msg_editor.insert(0.0, text)
    

    def set_users(self, dic:dict):
        """
        This function is called and will use the users in the self._users to fill out the user tree
        on the left of the text entry box by iteriating through it.
        """
        self._users = dic
        o = 1
        for users in dic:
            o += 1
            entry = ''
            for i in range(len(dic[users])):
                entry = entry + '{} @ {}'.format(dic[users][i]['message'], dic[users][i]['timestamp']) + '\n'
            self._insert_user_tree(o, users)


    def insert_user(self, user):
        """
        Is called to add the new user to the tree.

        Inserts a single user to the user_tree widget.
        """
        self._users[user] = []
        d = self._users.copy()
        self.reset_ui()
        self._users = d
        self.set_users(d)
        self._insert_user_tree(len(self._users)+2, '')


    def reset_ui(self):
        """
        This function will use the set text entry function, this is reseting it or to clear it
        by passing in empty text so the box is in empty.

        Resets all UI widgets to their default state
        """
        self.set_text_entry("")
        self._users = {}
        for item in self.user_tree.get_children():
            self.user_tree.delete(item)


    def _insert_user_tree(self, num, message):
        """
        This function is called to insert the user that is being passed in the users tree.

        Inserts a user into the users_tree widget.
        """
        self.user_tree.insert('', num, num, text=message)


    def _draw(self):
        """
        Is called upon initialization to add the body to the overall frame.
        """
        user_frame = tk.Frame(master=self, width=250, bg="gray")
        user_frame.pack(fill=tk.BOTH, side=tk.LEFT)
        self.user_tree = ttk.Treeview(user_frame)
        self.user_tree.bind("<<TreeviewSelect>>", self.node_select)
        self.user_tree.pack(fill=tk.BOTH, side=tk.TOP, expand=True, padx=5, pady=5)
        
        view_frame = tk.Frame(master=self, bg="gray")
        view_frame.pack(fill=tk.BOTH, side=tk.TOP, expand=True)

        entry_frame = tk.Frame(master=self, bg="gray")
        entry_frame.pack(fill=tk.BOTH, side=tk.BOTTOM, expand=True)

        self.msg_view = tk.Text(master=view_frame, height=20)
        self.msg_view.pack(fill=tk.BOTH, side=tk.TOP, expand=True, padx=5, pady=5)
        
        self.msg_editor = tk.Text(master=entry_frame, height=0)
        self.msg_editor.pack(fill=tk.BOTH, side=tk.BOTTOM, expand=True, padx=5, pady=5)


class Footer(tk.Frame):
    """
    The subclass that is used to make up the footer of the GUI.
    This subclass consists of the send message, add user, and refresh.
    
    A subclass of tk.Frame that is responsible for drawing all of the widgets
    in the footer portion of the root frame.
    """
    def __init__(self, root, send_callback=None, add_callback=None, refresh_callback=None):
        tk.Frame.__init__(self, root)
        self.root = root
        self._send_callback = send_callback
        self._add_callback = add_callback
        self._refresh_callback = refresh_callback
        self._draw()


    def send_click(self):
        """
        Calls the callback function specified in the save_callback class attribute, if available, when the save_button has been clicked.
        """
        if self._send_callback is not None:
            self._send_callback()


    def add_click(self):
        """
        Calls the callback function specified in the add_callback class attribute, if available, when the add_button has been clicked.
        """
        if self._add_callback is not None:
            self._add_callback()

    
    def refresh(self):
        """
        Calls the callback function specified in the refresh_callback class attribute, if available, when the refresh_button has been clicked.
        """ 
        if self._refresh_callback is not None:
            self._refresh_callback()


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
        footer_frame = tk.Frame(master=self, bg="gray")
        footer_frame.pack(fill=tk.BOTH, side=tk.BOTTOM)
        
        send_button = tk.Button(master=footer_frame, text="Send", width=20)
        send_button.configure(command=self.send_click)
        send_button.pack(fill=tk.BOTH, side=tk.RIGHT, padx=5, pady=5)
        
        refresh_button = tk.Button(master=footer_frame, text="Refresh", width=20)
        refresh_button.configure(command=self.refresh)
        refresh_button.pack(fill=tk.BOTH, side=tk.RIGHT, padx=5, pady=5)

        add_button = tk.Button(master=footer_frame, text="Add User")
        add_button.configure(command=self.add_click)
        add_button.pack(fill=tk.BOTH, side=tk.LEFT, padx=5, pady=5)

        self.footer_label_two = tk.Label(master=self, text="")
        self.footer_label_two.pack(fill=tk.BOTH, side=tk.LEFT, padx=5)


class MainApp(tk.Frame):
    """
    A subclass of tk.Frame that is responsible for drawing all of the widgets in the main portion of the root frame.
    """
    def __init__(self, root):
        tk.Frame.__init__(self, root)
        self.root = root
        self.user = None
        self.dsuserver = '168.235.86.101'
        self.port = 3021
        self.username = "AT"
        self.password = 'PASSWORD'
        self.token = 'user_token'
        self._draw()
        self.refresh_msg()


    def send_message(self):
        """
        Sends the written message to the server when the 'Send' button is clicked.
        """
        dm = DirectMessenger(self.dsuserver,self.username, self.password)
        resp = dm.send(self.body.get_text_entry(), self.body.recipient)
        if resp == 'ok':
            print('Message Sent Successful')
            self.body.set_text_entry('')
            self.refresh_msg()
            self.footer.set_status_two('Message Sent Successful')   
        else:
            print('Message Unable To Send')
            self.footer.set_status_two('Message Unable To Send')   


    def add_user(self):
        """
        Creates a new Toplevel window so that a user can add a new user.
        """
        self.user_window = tk.Toplevel()
        self.user_window.geometry("300x100")
        
        title = tk.Label(master=self.user_window, text='LOGIN')
        title.pack(fill='x', padx=5, pady=5)

        self.msg_editor = tk.Text(master=self.user_window, height=0)
        self.msg_editor.pack(fill=tk.BOTH, side=tk.BOTTOM, expand=True, padx=5, pady=5)

        save_button = tk.Button(master=self.user_window, text="Add User", width=20)
        save_button.configure(command=self.get_user_info)
        save_button.pack(fill=tk.BOTH, side=tk.TOP, padx=5, pady=5)


    def get_user_info(self):
        """
        Gets the username inputted from add_user and adds it onto the user_tree.
        """
        self.body.insert_user(self.msg_editor.get('1.0', 'end').rstrip())
        self.body.recipient = self.msg_editor.get('1.0', 'end').rstrip()
        self.user_window.destroy()


    def refresh_msg(self):
        """
        Take in retrieve_new information and replace what was in it before.
        """
        try:
            if self.username != None:
                dm = DirectMessenger(self.dsuserver,self.username,self.password)
                all_messages = dm.retrieve_all()
                before = self.body._users.copy()
                self.body.reset_ui()
                after = {}
                if all_messages != None:
                    if len(all_messages) != 0:
                        for i in range(len(all_messages)):
                            after[all_messages[i]['from']] = []
                        for i in range(len(all_messages)):
                            if all_messages[i]['from'] in after:
                                after[all_messages[i]['from']].append({'message':all_messages[i]['message'], 'timestamp':all_messages[i]['timestamp']})
                    for keys in after:
                        if keys not in before:
                            before[keys] = after[keys]
                        elif keys in before:
                            before[keys] = after[keys]
                else:
                    print('Nothing was retrieved')
                    self.footer.set_status_two('Nothing was retrieved, So no refresh')
                self._users = before
                self.body.set_users(self._users)
        except ConnectionException:
            print("Connection Error")
            self.footer.set_status_two("Connection Error")
            


    def openweathert(self):
        """
        This is the Open Weather API that is in the menu bar that will scan through the text
        entry box when called and replace the certain keywords wtih the information that is
        requested.
        """
        api = API()
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        open_weather = OpenWeather(api.zipcode, api.country, api.owa)
        texts = open_weather.transclude(text)
        self.body.set_text_entry(texts)
        self.footer.set_status_two('Done Transcluding')    


    def lastfmt(self):
        """
        This is the Last FM API that is in the menu bar that will scan through the text
        entry box when called and replace the certain keywords wtih the information that is
        requested.
        """
        api = API()
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        lf = LastFM(api.lfma)
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
        api = API()
        self.footer.set_status_two('Please Wait Transcluding')
        text = self.body.get_text_entry()
        open_weather = OpenWeather(api.zipcode, api.country, api.owa)
        text = open_weather.transclude(text)
        lf = LastFM(api.lfma)
        text = lf.transclude(text)
        texts = ExtraCreditAPI().transclude(text)
        self.body.set_text_entry(texts)
        self.footer.set_status_two('Done Transcluding')


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
        """
        menu_bar = tk.Menu(self.root)
        self.root['menu'] = menu_bar

        self.body = Body(self.root)
        self.body.pack(fill=tk.BOTH, side=tk.TOP, expand=True)

        menu_apis = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_apis, label='APIS')
        menu_apis.add_command(label='ALL 3 APIS', command=self.all_apis)
        menu_apis.add_command(label='Weather', command=self.openweathert)
        menu_apis.add_command(label='LastFM', command=self.lastfmt)
        menu_apis.add_command(label='ExtraCredit(Random Quote)', command=self.extracreditt)

        menu_help = tk.Menu(menu_bar)
        menu_bar.add_cascade(menu=menu_help, label='Help')
        menu_help.add_command(label='Help', command=self.help_window)
        
        self.footer = Footer(self.root, send_callback=self.send_message, add_callback=self.add_user, refresh_callback=self.refresh_msg)
        self.footer.pack(fill=tk.BOTH, side=tk.BOTTOM)


if __name__ == "__main__":
    main = tk.Tk()
    main.title("ICS 32 Mesenger Demo")
    main.geometry("720x480")
    main.option_add('*tearOff', False)
    MainApp(main)
    main.update()
    main.minsize(main.winfo_width(), main.winfo_height())
    main.mainloop()
