# Testing the RC receiver readout

For testing, wire up the receiver as described in the HoverBot readme. 
Connect the three channels you want to use to control the robot to the Arduino pins 2, 3 and 18 (as defined in the config file). 
Upload the receiver_test.ino sketch to the Arduino.
Once the sketch is uploaded and running, open the Serial Plotter in the Arduino IDE (Tools > Serial Plotter). 
As you move the sticks on the RC transmitter, you should see three curves react accordingly. 
They show the three signals’ pulse widths in microseconds and should be centered roughly around 1500, ranging from 1000 to 2000.
![pasted image 0](https://user-images.githubusercontent.com/8363989/58373131-649e6680-7f29-11e9-90ea-4ef4302ebc89.png)
