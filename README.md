# NSCA1_stepper_motor_control

Code written to control a stepper motor in one-dimention from an arcus performax NSCA1 control box. 

I am not affiliated with Arcus Technologies and provide no warranty or guarantees with the following code

# Dependencies
Only requires libusb. MYSYS2 seems to work well to get libusb on windows (not tested)

On arch:
$ sudo pacman -S libusb

Debian
$ sudo apt-get install libusb-dev # I haven't tested this

# Building
Uses cmake. Currently embedding lua to be able to control it by calling a lua script. Can also use all the commands
defined in stage control.


$ mkdir build 
$ cd build 
$ cmake .. 
$ make 

# Usage
The biggest downfall is I have only ever used it with a single device connected so it doesn't directly allow a user to open a device with multiple connected

There is also something to be said that arcus technologies likely changes the api provided for their motor boxes so some of the calls I implement here may be 
depreciated. I likely need to add a method to check if a command was understood. 

For all implemented commands see src/stage_control/commands.c 

To add your own commands, use "send_command_get_response" in src/stage_control/driver.c

I'm thinking its not great, but my Device struct only needs the user to initialize the interface number. So basic usage would look like:

```c
Device device = {0}; // Initializes the interface number to be zero
// device.iface_number = 1; // change interface number
open(&device);

move_stage(device, 1000);

close(device);
```

calibrate and run were written for my usages and I wouldn't image they would be great use to other but may give a good example of how I used the api
