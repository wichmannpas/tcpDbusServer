TCP DBus Server
===============

**Attention!** *You are currently viewing the unstable development branch. Using this source code can cause compatibility issues when used with the tcpDbusClient Android application. See stable branch for stable releases.*

This is a dbus tcp server script receiving tcp connections and sending the appropriate system signal to give remote media key (i.e. for Android) functionality.

Features currently supported:

* play/pause
* previous/next
* volume control

See [tcpDbusClient](http://github.com/wichmannpas/tcpDbusClient) for a basic Android app communicating with this server script.

Compatibility
-------------

The signals can be sent to each application handling the MPRIS DBus specifications (http://www.freedesktop.org/wiki/Specifications/mpris-spec/). These are for example *Rhytmbox* or the *Spotify Linux Preview*.

The script should compile fine on each linux distribution with GNU Make compiler and Qt>=4 installed. To be able to work with the dbus signals, you need to have DBus up and running on your system.

Tested on:

* Arch Linux with GNOME3 shell

Prerequisites and Compilation
-----------------------------

To use this script you will need:

* dbus installed and working on your system
* GNU Compiler
* Qt
* alsa-utils (for using volume control features)

To compile, switch to the directory where you have downloaded the source code and type in the following:

	qmake
	make

Make sure that the compiled script is started with the user session (i.e. put it in the startup applications of your desktop manager - **not** on system level, because the dbus signals will not be received correctly then).

Customizing
--------------------------------------

You can change the port where the tcp server is listening. Default is *12341*.

All other data can be dynamically sent in the tcp data, i.e. the target dbus application.

License
-------

Copyright 2014 Pascal Wichmann

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
