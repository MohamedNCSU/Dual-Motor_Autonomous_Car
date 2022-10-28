Executable files built outside of IAR Embedded Workbench

Follow these steps to load and debug an executable file that was built outside
IAR Embedded Workbench, for example projects built on the command line. 

1. Choose Project>Add Files to add the executable file (filename extension d43)
that you want to debug to the project. 

2. Set up the debugger options according to you needs. The only project options
that are meaningful to set for this kind of project are options in the General
Options and Debugger categories. Make sure to set up the general project 
options in the same way as when the executable file was built.

3. To start the debugger, select the project in the workspace window and
click the Debug button. The project can be reused whenever you rebuild your
executable file. The debugger will notice if the executable file has been 
rebuilt and ask you if you want to reload it.

4. This file (readme.txt) must be removed from the project before the debugger
can be started.

Constructed and soldered a small dual-motor autonomous car that can detect and drive along a black line and maneuver in different shapes specified by the user using embedded systems. The car also has an LCD display that can communicate with the user, as well as two switches on either side so the user can provide inputs on what they want the car to do. Car was programmed in C on the MSP 430 processor; Implemented timers, interrupt service routines, state machines, pulse width modulation to control wheel speed, etc in order to innovate vehicle functionality.
