# This project is no longer maintained!

## Alarm Clock
A simple and elegant alarm clock

**License**: GPLv3

* * *

### Project Information

####How to help-out

1. Fork this git repository
2. Make wanted changes
3. Send a pull request.

Repeat for every change-set you make. Read the project guidelines below for a
quicker pull-request approval and a smooth transition into the main repository.

####Needed Programs

The programs you need are:

**Qt Creator**:

To configure

1. Open the AlarmClock.pro file
2. Tell Qt to use the **program/compiled/debug** folder for debug compilations
3. Tell Qt to use the **program/compiled/release** folder for release 
compilations

**Inno Setup**

No configurations are needed, the entire process is automated based on given
folder structure.

1. Open Installer script located inside **source** folder
2. Change text and number versions to match program
3. Click compile

**Git**

If you downloaded the source code instead of cloning then you'll need git to
work with it. A fresh clone of the repository is highly-suggested if you
downloaded via zip or tar file.

####Development

To develop, and after the programs are correctly configured:

1. Make changes in Qt
2. Update the version number located in main.cpp
2. Compile for release
3. Copy **program/compiled/release/release/AlarmClock.exe** to 
**program/deployed/windows**.
4. If you haven't already then copy the needed DLL's described in the 
RequiredDLLs.txt file in same folder, it also tells you where to get them.
5. Ensure it runs correctly alone by double clicking executable, also
a good place to do some final testing.
6. Open the installer script located at **source/InstallScript.iss**
7. Type in the new number and text version number, the same one used on the
about screen
8. Click compile
9. Make a git commit
10. Make a git tag if its for a release
11. Push to github
12. If its for a release then go to Releases on github, find new tag at top,
enter information for the end-user to see including a friendly but to the
point title. Drag and drop needed screenshots and upload the compiled installer.

####Project Guidelines

_**User-Interface**_

The user-interface is most important aspect, it's the front-end to what the
users see and use. It's therefore vital to ensure that the user interface
be the most pristine and highest-thought aspect of the program.

**Break out of the shell**: Your typical average user interface consists of
a window with a menu bar, a status bar, a right-click menu, and multiple
other windows such as an about window, a help window, etc...

Break out of this, this program consists of a single window, it doesn't contain
a status bar, a menu, a right-click menu, or multiple windows. Even the 
controls are specially designed.

**Self-Explanatory**: The user interface features some pretty unique design
patterns, despite this, it shouldn't be foreign or hard to figure out.
Everything should be simple and highly intuitive so that how to use each
part of the user interface comes naturally.

**To the point**: The user interface is divided into several "screens" where
each screen takes up about the entire window. All the screens are loaded
all at the same time during runtime and each screen features exactly what needs
to be featured. The clock screen shows just that, 2 clocks, that's it. The
set-up screen shows just that, 2 controls for adjusting the hours and minutes
and 2 buttons for enabling and altering the am/pm.

Each screen is intuitive, simple, and right to the point. No pop-ups or
questions or any of that.

**Central theme**: All the controls are specially designed for a custom look
using the new and modern "flat-style look" that most companies are switching
to. All the controls follow a central-style theme so everything naturally
blends in.

Not only that but the theme is simple and light-weight on the eyes. No heavy
gradients or dark colors or neon stuff, just simple elegance.

**Responsiveness**: The entire user interface is loaded and remains loaded
during runtime divided into screens as mentioned in "to the point" above.
Because of this each screen is switched out immediately with no processing
time or memory allocations and deallocations.

Not only that but the state of all controls remains intact throughout each
screen change so if something is typed into a text-box and highlighted
for example then it will still be that way upon any number of screen
switching.

_**Folder structure**_

The folder structure is heavily centralized, upon cloning or downloading the
repository you have your entire development environment and the correct folder
structure set-up for you, all that's left is the correct software.

The folder structure you see will always be used, even when installing into
the client computer the necessary folders are copied as-is directly onto
the file system.

    ├───installer
    ├───program
    │   ├───compiled
    │   │   ├───debug
    │   │   └───release
    │   └───deployed
    │       └───windows
    │           └───uninstall
    └───source
        └───resources
            ├───logo
            ├───screenshot
            └───sounds

The above is the folder project structure, all folder names are lowercase

**installer**: The installer folder is where the installer
is automatically compiled and correctly outputted to given the installer
script located in the source folder.

**program**: All program compilations and deployments go for all operating
systems.

**program/compiled**: Where all compilations of the program go

**program/compiled/debug**: Where debug compilations go, Qt automatically
compiles here for debug mode

**program/compiled/release**: Where release compilations go, Qt automatically
compiles here for release mode

**program/deployed**: Where different deployments go depending on the system,
Must be hand placed, the needed library files are listed in a text file
along with where to find it to make it easier.

**program/deployed/windows**: Where window deployments go, upon installation
on the client computer, if the client only requests the program be installed,
then it's this specific folder chain that is copied.

**program/deployed/windows/uninstall**: Where uninstall information and 
executables go after installation to the client computer.

**source**: Where the program source goes including installation scripts

**source/resources**: Where all program images and other media and assets go.

**source/resources/logo**: Any form of logo, even if not directly used by the 
application go here. This includes icons.

**source/screenshot**: All screen shots go here, mainly only used with GitHub

**source/sounds**: All sound files go here that are to be built-in to the
program
