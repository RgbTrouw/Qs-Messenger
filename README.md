     QsMessenger v 0.1 Instant Messaging Client & Server Application  
     Copyright (C) 2025  Radu G. Balaban G.  
  
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
  
    
** Qs Messenger v.0.1  Client and Server for Linux, Windows, Android **  

  
     - C++ open source program developed with Qt Creator IDE -  

<Introduction>

Linux   -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------     

a) Client
   
   Install:
    
    - install .deb package (dpkg -i <package name>);   
    - set server hostaddress and port in the "/etc/QsMessenger/hostname" file;  
    - run;  
      
  Features: 
  
b) Server  

  Requirements:   
    - php Pear (Mail);  
    - MySql server;  
    
  Install:  
      
    - install .deb package (dpkg -i <package name>);  
      
    - import ssl certificate and key in "/etc/QsMessengerServer/crt/" folder;  
    - import sql database template from "/usr/local/share/QsMessengerServer/sql" folder to MySql server;  
      
    - set MySQL Credentials in "/etc/QsMessengerServer/mysql" file;  
    - set Mail Credentials in "/etc/QsMessengerServer/mail" file;  
      
    - run;  
    
   Features:    
    - log    
  
Windows -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------      
  
