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
