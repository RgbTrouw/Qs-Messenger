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
  


        
Security Features
--------------------------------------------------------------------------

- Secure Socket Layer  
- Server doesn't process same request twice*  
- Passwords are always sent and stored in sha-256 format (hash -> rehash)**  
- Service port should run above 1023 to avoid root access*
- ( consider firewall geolocation filter )*  

  

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
If you would like to be a part of the project, or have any other suggestions or comments please send a note to:  
  
"rgb.trust@gmail.com"  

    
  ...  
