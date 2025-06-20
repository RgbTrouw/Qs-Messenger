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
  
    
 Qs Messenger Client and Server for Linux, Windows and Android   
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
     - C++ open source program developed with Qt Creator IDE -  

<Introduction>
    
** NOTICE ** Some files have to be re-uploaded / pending **  SRC ONLY 

Windows   
----------------------------------------------------------------------------------------------------------------------     

a) Portable Client:

    ** Notice ** Windows Startup Registery Key to Portable Folder -> place folder to desired location;  
      
    - set server address and port in "hostname" file;    
    - run;  
    
Linux   
----------------------------------------------------------------------------------------------------------------------     

a) Client Install:
    
    - install .deb package (dpkg -i <package name>);   
    - set server hostaddress and port in the "/etc/QsMessenger/hostname" file;  
    - run;  
      
  
b) Server Install:  
      
    - require ssl certificate and key
    - require MySql server  
    - require openssl  
    - require php Pear (Mail) 
      
    - install .deb package (dpkg -i <package name>);  
      
    - import ssl certificate and key in "/etc/QsMessengerServer/crt/" folder;  
    - import sql database template from "/usr/local/share/QsMessengerServer/sql" folder to MySql server;  
      
    - set MySQL Credentials in "/etc/QsMessengerServer/mysql" file;  
    - set Mail Credentials in "/etc/QsMessengerServer/mail" file;  
      
    - run;    
  
Windows 
-------------------------------------------------------------------------------------------------------------------------      

Client Install:  
  
   
  About Source Code
--------------------------------------------------------------------------  

     > some bits of code (not quite very many) are not executed as they might be part of a removed or not fully yet implemented procedure;  
     Ie. "session_id" had been implemented and doesn't actually do any work for now, except it might be a good log indicator; <

     * sql template database included ( with minimal, fictional batch clients data )
    
     * server <-> client syntax format is -> "procedure:parameter:parameter:session_id";  
       
     * files (binary data) respect the same pattern as binary suffix data;  
       
     * messages and status messages are hendled as hex data within the requests;  
  
     * more strengthened parameters validation to be added in the future releases;  
       
     * FriendsListData Format: |Group:user/userdata/userdata:user/userdata/userdata|Group:user/userdata/userdata:user/userdata/userdata (or something simmilar)  
       -> split by "|", ":", "/";  
       -> might be converted to xml or something else in the future;  
       (-> this plain data is loaded into FriendsList->groups->peers Object' - on the client side;)  
       (-> 'groups' Object contains a 'header' Object that displays the actual group name and online count;)  
 
    
     (* database information is handled by its unique integer id;)  
       
     * currently used mailing service is smtp with gmail account -> which is for testing purposes only;  
       -> note that the smtp gmail service requires setting up an "app password" and is different from your regular gmail account password;  
       -> this has to be updated for further releases but could work (does work) for a small testing batch;
    
    
     a) Client  
    
     * 'Source/Objects' folder ie. includes a non graphical version of the FriendsListWidgetObject and is not actually used;  
    
     * IM window does include some unimplemented function buttons.  
    
     * IM "has read at time" function 'almost' implemented, with window focus feedback + server/ database support
       -> which is different from implemented function "last message received at time";
      // (-> *note some context menu action procedures - ie. remove group, add group, move to group - refresh the list tree view, expanding the tree. Status updates only update user data,
       keeping current list tree preference - show all/ show only online/ show none - unchanged;)  

  
     b) Server  
  
     * some sections could use some simplification - especially in the handling of the lists - but the code does accomplish some work for now;  
     -> something for the future releases; 
       
    
     c) Database  
  
     * I would keep an eye out on the sql errors if some functions don't seem to be working after importing the sql database template. Ie. if the database is not imported properly.
  
     * Know issue: extraneous "," in db 'list' csv data, that doesn't seem to affect the handeling of the lists. Should be fixed eventually.
    
        
Security Features
--------------------------------------------------------------------------

- Secure Socket Layer  
    
- Passwords are always sent and stored in sha-256 format (hash -> rehash)**
    
- Service port should run above 1023 to avoid root access*

  *notice - server doesn't process same request twice*  
    
  *consider - firewall geolocation filter*  

  

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
* No need to mention the resemblance with some other old messaging application.  
  
If you would like to be a part of the project, or have any other suggestions or comments please send a note to:  
  
"rgb.trust@gmail.com"  

    
  ...  
