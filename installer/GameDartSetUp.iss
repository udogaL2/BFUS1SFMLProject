; Имя приложения
#define   Name       "Darts Game"
; Версия приложения
#define   Version    "D0.2"
; Фирма-разработчик
#define   Publisher  "ShEvgy"
; Имя исполняемого модуля
#define   ExeName    "Darts.exe"

[Setup]
AppId={{3113320E-C7BE-409C-847E-25E83BD63B8D}
AppName={#Name}
AppVersion={#Version}
AppPublisher={#Publisher}
DefaultDirName={pf}\{#Name}
DefaultGroupName={#Name}

OutputDir="F:\CLionProjects\sfml_Project\installer\output"
OutputBaseFileName=Darts Game setup

SetupIconFile="F:\CLionProjects\sfml_Project\installer\dart.ico"

Compression=lzma
SolidCompression=yes

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"; LicenseFile: "License_RUS.txt"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[files]
Source: "F:\CLionProjects\sfml_Project\installer\DartsGame.exe"; DestDir: "{app}"; Flags: ignoreversion; DestName: Darts.exe
Source: "F:\CLionProjects\sfml_Project\installer\data\*"; DestDir: "{app}\data"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "F:\CLionProjects\sfml_Project\installer\VC_redist.x64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall


[Icons]
Name: "{group}\{#Name}"; Filename: "{app}\{#ExeName}"; IconFilename: "{app}\data\ico\dart.ico"; Tasks: desktopicon
Name: "{commondesktop}\{#Name}"; Filename: "{app}\{#ExeName}"; Tasks: desktopicon
[Run]
Filename: {tmp}\VC_redist.x64.exe; Parameters: "/q:a /c:""install /l /q"""; StatusMsg: VS redistributable package is installed. Please wait...