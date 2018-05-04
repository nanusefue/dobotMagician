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

