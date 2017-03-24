# eds_project
This project is primarily intended to support gaining experience with Linux/ARM platform development using C++. However, the end result should provide tangible working functionality to regulate temperature for an existing hydronic heating system.

The hardware target platform for this project is an inexpensive Odroid-C2 board (rather like a Raspberry Pi-3) with an LCD daughter board and added-on sensor electronics that will expand as the project progresses. Currenty, the only added-on sensor hardware is a low cost and easy to design in (yet quite sophisticated) hall effect sensor using an I2C interface. This is to monitor a mixing valve open/close position to regulate heating loop supply temperature.

This effort will ultimately replace an existing off-the-shelf control unit that is defective and obsolete. At first glance, this solution would seem totally absured compared to just purchasing another off-the-shelf controller and installing it. Way overkill in terms of software and hardware complexity and crazy amount of time ultimately invested. But in light of the primary goal of learning a skill set, it really makes good sense. Actually, hardware and install cost of a quality off-the-shelf hydronic controller IS very expensive and the hardware cost for this project costs just a small fraction of that. Very economical actually - - Ok... as long as one accepts the premise that time invested has no monitary value.

The initial commit to this project repository is leveraged from an existing reference design (C code) that I massively modified (much of it to strip pit unneeded code) to yield the first milestone of functionality that can be demonstrated. Not very complex but demonstrates display, LED, and pushbutton functionality of the daughterboard as well as demonstrating the ability to read magnet orientation from the hall effect sensor. Lots of effort remains - ability to read two temperature sensors; ability to issue open/close orders to the mixing valve motor; and then the control algorithm itself needed to yield proper thermal regulation in heating loop zones.

More to follow as effort continues...

Next chore is to modify the existing C code to be more in line with C++ (11) best practices. Am now looking for some useful guidelines on porting from C to C++.


