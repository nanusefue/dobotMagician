# dobotMagician
Python lib for Dobot Magician 

Install
Qt5*
libusb*
libQt* 
Qt5Serial-Dev
qmake DobotDll.pro
make


Python Script
1- Connect Raspberry Pi using serial port
(Pin Outs: https://es.pinout.xyz/pinout/uart )
![Alt text](pinsout.png?raw=true "Pins")

Important!!! USB to TTL (3.3v)
Terminal:
 screen /dev/ttyUSB0 115200

python Script.py --Json data2.json



dobot.service

[Unit]
Description=DobotRobot 
After=network.target

[Service]
ExecStart=/usr/bin/python2 -u init.py
WorkingDirectory=/home/pi/script
StandardOutput=inherit
StandardError=inherit
Restart=always
User=pi

[Install]
WantedBy=multi-user.target


start
sudo systemctl start dobot.service

restart
sudo systemctl restart dobot.service


stopt
sudo systemctl stop dobot.service

Enable boot
sudo cp dobot.service /etc/systemd/system/dobot.service


sudo systemctl enable dobot.service


Logs
 journalctl -u dobot
