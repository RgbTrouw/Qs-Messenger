     QsMessenger v 1.0.2 Instant Messaging Client & Server Application  
     Copyright (C) 2023-2025  Radu G. Balaban G.  
  
     This program is free software: you can redistribute it and/or modify  
     it under the terms of the GNU General Public License as published by  
     the Free Software Foundation, either version 3 of the License, or  
     (at your option) any later version.  
  
     This program is distributed in the hope that it will be useful,  
     but WITHOUT ANY WARRANTY; without even the implied warranty of  
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
     GNU General Public License for more details.  
  
     You should have received a copy of the GNU General Public License  
     along with this program. If not, see <https://www.gnu.org/licenses/>.  
  
    
 Qs Messenger Client and Server for Linux, Windows (and Android*)   
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
     - C++ open source program developed with qt5 / Qt Creator IDE -  
  

<Introduction>  
  
The program is supposed to be similar to/ replace an old, popular instant messaging application that has eventually become unavailable.  
  
     ** Note that windows portable binaries set up a windows startup registery key, making the application start on windows startup. Move the QsMessenger folder to a friendly location before starting.  
       
     ** Make sure to adjust the server address within the enclosed "hostname" file; (address:port)    
     
     ** Stay tuned for the latest updates and developments.   

  
** Notice ** Some files have been revised. Binaries have thus been removed for now.   
  
 
Client configuration:  
--------------------------------------------------
Host address and port has to be assigned within the messenger client folder "host" file.  
  

Server configuration:  
--------------------------------------------------
*require Php Pear (Mail)  
*require Mysql Server  
*require Openssl  
*require Ssl certificate bundle  
  

- configure credentials in 'assets' folder;
  (sql and smtp)  
- import certificates to 'crt' folder  
- import 'messenger.sql' file to mysql database 'messenger'  

About Source:  
--------------------------------------------------  
  
The source is mostly clean. 
Only the server source might be hard to follow at times, especially when it comes to the list handling.


* The client source does contain some unused objects. These are within the "Source/Objects" folder and are just a working, early version of the "FriendsList" object but without the "Widget" component. They are not #included anywhere.    
The used components are within the "Objects/Windows" folder.
  
* SessionId is a parameter that was supposed to be implemented in early stages, is still present in all queries, but doesn't provide any particular purpose, except for being a potential log indicator. (it is indeed more specific to REST APIs)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
* Some features are to be improved in a future version.

Known Issues:
- Secure Socket doesn't seem to be connecting on Windows for now .? We are working on finding suitable solutions to resolve the issue. 

- Window positioning is off on Windows and a simple fix has been designed. 

- Messages relay has a delay of 1 second and has to be addapted for instant forwarding. 

- An eronous comma "," will occur in the friends list sql database table. This does not affect the list data processing and should be fixed at some point. 

- Clear messages function not yet implemented.

- Some file/folder paths inherited a debian package installer format. This is a publishing error. Thus "/usr/local/share/QsMessengerServer/avatars/" would have to become "./avatars".  
  
  
Note:
If you plan on testing the email sending processes with Google Smtp service, the smtp account password differs from the regular account password and has to be generated from Google Account Settings (generate app password).


For suggestions or comments please send a note to:  
  
"rgb.trust@gmail.com"  

    
  ...  
