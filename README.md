     QsMessenger v 0.1 Instant Messaging Application  
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
  
** Qs Messenger v.0.1 - Client & Server - Linux, Windows, Android **  

<Introduction>

Linux -

a) Qs Messenger Client

  Features:  
  Notes:  
    - install .deb package (dpkg -i <package name>);   
    - set server hostaddress and port in the "/etc/QsMessenger/hostname" file;  
    - run;  

b) Qs Messenger Server  

  Requirements:   
    - Php Pear (Mail)  
  Setup:  
    - install .deb package (dpkg -i <package name>);   
    - import sql database template from "src/sql" folder;  
    - import ssl certificate and key in "/etc/QsMessengerServer/crt/" folder;  
    - set MySQL user and password in "/etc/QsMessengerServer/mysql" file;  
    - set Mail Credentials in "/etc/QsMessengerServer/mail" file;  
    - run;  
    
  Notes:  
    - log    
