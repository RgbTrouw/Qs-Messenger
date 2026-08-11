     QsMessenger v 1.0.2b Rev 4 Instant Messaging Client & Server Application  
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
  
     
QsMessenger 1.0.2b Released - Windows & Linux Client Binaries Included      
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

      
     - C++ open source program developed with qt5 & qt6 / Qt Creator IDE -  

 *" the cute and small messenger "*  
  
Host Address: **qsmessenger.net 7080**  
  
<img src="https://github.com/RgbTrouw/QsMessenger/blob/root/Online.png" width="92" height="34">  
  
*If you are having connectivity problems you can always write an email at 'rgb.trust@gmail.com' or try again later.*     

  
  ![alt text](https://github.com/RgbTrouw/QsMessenger/blob/root/QsMessenger%201.0.2a%20Windows.png)
    
  ![alt text](https://github.com/RgbTrouw/QsMessenger/blob/root/QsMessenger%20v1.0.2a%202026.png)  
  
 
* see "QsMessenger - Login Screen.png"
    
<Introduction>  

  
" This program is supposed to be similar to/ replace an old, popular instant messaging application that has become unavailable. "  
  
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  

 Thank you for your insterest in the application.    
   

* Note that only basic functions are implemented for now.  
  
This includes:  
    
- configure host address  
- user registration  
- password reset
- login / logout  
- set status  
- set avatar  
- all friends list management features
  (accessible by right click context menu)  
- send text message   
- send buzz  
- load archived messages  
- clear archived messages   
  
Not yet implemented:  
  
- peer login / logout notification   
- send smiley, files, pictures 
- webcam session  
- configure start on OS Startup  
  (option is always active)  
- block/ ignore list  
  
     
What is new:  
    
  - completed some of the list functions  
  - only one login allowed, with option of logging out the other session
  - server verbose option "-v" added
  - (removed server logging "-log" for now)
      
  
  
Client configuration:  
--------------------------------------------------
Host address and port have to be assigned within the messenger settings menu.  
Once the setting is configured the client will connect to the server address.
  
 * Note that Windows portable binaries set up a Startup Registery Key, making the application start on Windows startup. Move the QsMessenger folder to a friendly location before starting.  
        

Server configuration:  
--------------------------------------------------
*require Php Pear (Mail)  
*require MySql Server  
*require OpenSSL  
*require SSL certificate bundle  
  

- configure credentials in 'assets' folder;
  (sql and smtp)  
- import certificates to 'crt' folder
- import 'messengerDataBase.sql' file to mysql database 'messenger'  
  
  
The code can be adapted to serve on multiple computers, hosting a larger number of clients.   
  
This involves splitting the sql data by a certain function on multiple back-end sql servers (ie. letters abc s1, def s2, ghi s3, jkl s4, mno s1, pqr s2, etc. or something similar) and multiple front-end servers communicating to each other and any of the sql servers, whilst balancing the nr. of clients between them.  

A single computer might also be a starting point, serving for a base of clients.  
  
  

      
       
------------------------------------------------------------------------------------------------------------------------------
  
For suggestions or comments please send a note to:  
  
"rgb.trust@gmail.com"  
  
    
  ...  
