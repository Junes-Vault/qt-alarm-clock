; Installer custom created for alarm clock - v1.0.1.1

; Should have no spaces in name
#define FileProgramName "AlarmClock"

; Should have spaces (Appear natural to users)
#define DisplayProgramName "Alarm Clock"

; Should be numbers only and up to 3 periods max
#define NumberVersion "1.1.3.0"

; Shgould be more detailed
#define TextVersion "v1.1.3.0-beta"

; Should have the written word "Copyright" not the symbol
; Followed by the full 4 digit year and the Authors Full Name
#define Copyright "Copyright 2013 June Hanabi"

; Short and to the point
#define Description "A simple and elegant alarm clock"

; Really shouldnt change, lol
#define Author "June Hanabi and other contributors"

[Setup]
WizardImageFile=source\resources\logo\MyLogo.bmp
WizardSmallImageFile=source\resources\logo\MyLogo.bmp
AppName={#DisplayProgramName}
AppVersion={#TextVersion}
ShowTasksTreeLines=True
AlwaysShowGroupOnReadyPage=True
AlwaysShowDirOnReadyPage=True
AppCopyright={#Copyright}
AppId={{9A14F464-023A-4724-B9EF-412E8BC5BC90}
LicenseFile=gpl.txt
TimeStampsInUTC=Yes
SetupIconFile=source\resources\logo\MyLogo.ico
DefaultDirName={sd}\{#FileProgramName}
AllowRootDirectory=True
ShowLanguageDialog=no
AllowNoIcons=True
DefaultGroupName={#FileProgramName}
AppPublisher={#Author}
AppPublisherURL=https://github.com/junebug12851/AlarmClock
AppSupportURL=https://github.com/junebug12851/AlarmClock/issues
AppUpdatesURL=https://github.com/junebug12851/AlarmClock/releases
AppComments={#Description}
UninstallDisplayName={#DisplayProgramName}
UninstallDisplayIcon=source\resources\logo\MyLogo.ico
UninstallFilesDir={app}\program\deployed\windows\uninstall
VersionInfoVersion={#NumberVersion}
VersionInfoCompany={#Author}
VersionInfoDescription={#Description}
VersionInfoTextVersion={#TextVersion}
VersionInfoCopyright={#Copyright}
VersionInfoProductName={#DisplayProgramName}
VersionInfoProductVersion={#NumberVersion}
VersionInfoProductTextVersion={#TextVersion}
OutputDir=./
OutputBaseFilename=installer/setup-{#FileProgramName}-{#TextVersion}
SourceDir=../
Compression=lzma2/ultra
InternalCompressLevel=ultra
LZMAAlgorithm=1
LZMADictionarySize=65535
LZMAMatchFinder=BT
LZMANumFastBytes=273

[Types]
Name: "ProgramSource"; Description: "Program and Source Code"
Name: "Program"; Description: "Program Only"
Name: "Source"; Description: "Source Code Only"
Name: "Custom"; Description: "Custom"; Flags: iscustom

[Components]
Name: "Program"; Description: "The Alarm Clock itself"; Types: Program ProgramSource
Name: "Source"; Description: "Source code used for this version"; Types: ProgramSource Source

[Tasks]
Name: "DesktopIcon"; Description: "Create a desktop icon"; GroupDescription: "Icons"
Name: "QuickLaunchIcon"; Description: "Create a quick launch icon"; GroupDescription: "Icons"; OnlyBelowVersion: 0,6.1
Name: "LaunchProjectDesktopIcon"; Description: "Create a desktop icon to the project"; Components: Source

[Files]
Source: "source/*"; DestDir: "{app}\source"; Flags: createallsubdirs overwritereadonly recursesubdirs uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Source; Excludes: "AlarmClock.pro.user"
Source: "program/deployed/windows/*"; DestDir: "{app}\program\deployed\windows"; Flags: createallsubdirs overwritereadonly recursesubdirs uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Program
Source: "gpl.txt"; DestDir: "{app}"; Flags: overwritereadonly uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Source
Source: "README.md"; DestDir: "{app}"; Flags: overwritereadonly uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Source
Source: "program/deployed/windows/.keep"; DestDir: "{app}/program/deployed/windows"; Flags: overwritereadonly uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Source
Source: "program/deployed/windows/RequiredDLLs.txt"; DestDir: "{app}/program/deployed/windows"; Flags: overwritereadonly uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Source
Source: "program/deployed/windows/uninstall/.keep"; DestDir: "{app}/program/deployed/windows/uninstall"; Flags: overwritereadonly uninsremovereadonly sortfilesbyextension sortfilesbyname; Components: Source

[Dirs]
Name: "{app}\installer"; Components: Source
Name: "{app}\program\compiled\debug"; Components: Source
Name: "{app}\program\compiled\release"; Components: Source

[Icons]
Name: "{group}\Launch Project"; Filename: "{app}/source/AlarmClock.pro"; Flags: excludefromshowinnewinstall; Components: Source
Name: "{commondesktop}\Launch Project"; Filename: "{app}/source/AlarmClock.pro"; Flags: excludefromshowinnewinstall; Components: Source; Tasks: LaunchProjectDesktopIcon
Name: "{group}\{#DisplayProgramName}"; Filename: "{app}/program/deployed/windows/AlarmClock.exe"; Components: Program
Name: "{commondesktop}\{#DisplayProgramName}"; Filename: "{app}/program/deployed/windows/AlarmClock.exe"; Flags: excludefromshowinnewinstall; Components: Program; Tasks: DesktopIcon
Name: "{group}\Project Page"; Filename: "https://github.com/junebug12851/AlarmClock"; Flags: excludefromshowinnewinstall; Components: Source
Name: "{group}\Uninstall {#DisplayProgramName}"; Filename: "{uninstallexe}"; Flags: excludefromshowinnewinstall; Components: Program
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#DisplayProgramName}"; Filename: "{app}/program/deployed/windows/AlarmClock.exe"; Flags: excludefromshowinnewinstall; Components: Program; Tasks: QuickLaunchIcon

[Run]
Filename: "{app}/program/deployed/windows/AlarmClock.exe"; Flags: nowait postinstall skipifsilent; Description: "Launch Alarm Clock"; Components: Program
