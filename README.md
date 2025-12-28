     QsMessenger v 1.0.2a Instant Messaging Client & Server Application  
     Copyright (C) 2026 Radu G. Balaban G.  
  
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
  
     
*New* QsMessenger Client and Server 1.0.2a Released    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


      
     - C++ open source program developed with qt5 / Qt Creator IDE -  
  
  
             Windows binaries might be available soon        
   

<Introduction>  

    
The program is supposed to be similar to/ replace an old, popular instant messaging application that has become unavailable.  
  
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
 Thank you for your insterest in the application.    
  
'The QsMessenger Team' wishes you a Merry Christmas and a Happy New Year!  

     -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
       
     ** Note that windows portable binaries set up a windows startup registery key, making the application start on windows startup. Move the QsMessenger folder to a friendly location before starting.  
       
     
     ** Stay tuned for the latest updates and developments.   


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  

  
  QsMessenger Client & Server 1.0.2a Release Main Changes:  
    

- Host address setting added to client, along with other minor changes.  
  
- Relay functions have all been adapted for instant forwarding;  
  
- Almost all database queries use "email" as primary key;  
  
- ( The database also has some changes; )  
  
- Some unused variables and functions have been removed (including sessionId from all requests);  
  
- Logging is only started with the "-log" program argument;  
  (Two distinct client classes are used to spare processing time)  

  - In essence the server is a bit cleaner and it runs more smoothly;   
  
  
It is still a new release, other errors are not excluded, but it does seem to be ok for now.  
  
Other changes may be included in the future...
    
  * Qt Windows is somehow missing openSSL support for me, soo it could be the reason for no connectivity on Windows.  
Suggestions are welcome.
  
** Update ** OpenSSL 3 should apparently be supported starting with qt 6.5;   
  
** Update  ** It is indeed connecting with qt 6 on Windows. However, the QMYSQL database driver is missing for now.  
This might get fixed and there might be a Windows binary available soon.  
  

 
Client configuration:  
--------------------------------------------------
Host address and port has to be assigned within the messenger settings menu.  
  

Server configuration:  
--------------------------------------------------
*require Php Pear (Mail)  
*require Mysql Server  
*require OpenSSL  
*require Ssl certificate bundle  
  

- configure credentials in 'assets' folder;
  (sql and smtp)  
- import certificates to 'crt' folder
- import 'messenger.sql' file to mysql database 'messenger'  

Note:
If you plan on testing the server with Google Smtp service, the password used here differs from the regular account password and has to be generated from Google Account Settings (generate app password).  
(Please use this method only for limited testing and do not use it to send out spam or any unsolicited advertising.)

  
       
//  
//  
//  
//  
  
For suggestions or comments please send a note to:  
  
"rgb.trust@gmail.com"  
  
    
  ...  
