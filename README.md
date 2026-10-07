Qs-Messenger 1.0.2d Source Released  
-----------------------------------------------------------------------------------------
       
      
     - C++ open source program developed with qt5 & qt6 / Qt Creator IDE -  

 *" the cute and small messenger "*  
  
Host Address: **qsmessenger.net 7080**   
(*offline)
  

<Introduction>  

  
" This program is supposed to be similar to/ replace an old, popular instant messaging application that has become unavailable "  
  
----------------------------------------------------------------------------------------------------

 Thank you for your insterest in the application.  

Release Notes:  

- Both server and client have overall improvements, but most changes come with the server.
  
  * "is writing a message... " notification has been added.
   
- The client contains some minor changes, new Icons, some Smileys, send IM to Group Option and Audio Notifications.
     
- The server provides a more thorough syntax with better logging, display of service messages and performance,  plus an added option of filtering out IP clients
by country code.
  
 (OpenSSL binary dependency removed)
      


 Qs-Messenger Server Synopsis  

     
   
```
Qs-MessengerServer v1.0.2d - Copyright 2026 Rgb-Trust
Usage: ./QsMessengerServer [-h] [-v] [-l] [-f <CountryCode>] [ipLookupApiKey]
 
Options: 
  -h                 display usage information
  -v                 display server-client messages
  -l                 log server-client messages (recommended)
  -f <NN> <apiKey>   allow only IPs from <NN> region - use https://ip2location.io <apiKey>
 
Service Port SSL: 7080
 
Configuration:
 
MYSQL Database Template               - assets/messenger.sql
MYSQL Service Username and Password   - assets/mysql_credentials
 
SMTP Username and Password            - assets/mailToRegister.php
SMTP Username and Password            - assets/mailToRecover.php
 
SSL CA Root Certificate               - crt/ca_certificate.crt
SSL Certificate                       - crt/certificate.crt
SSL Private Key                       - crt/private.key
```
    
Suggested mysql configuration (extend allowed active session time):

  `[mysqld]`  
  `wait_timeout = 604800`  
  `interactive_timeout = 604800`  
      
       
------------------------------------------------------------------------------------------------------------------------------
  
For suggestions or comments please send a note to:  
  
"rgb.trust@gmail.com"  
  
    
  ...  
