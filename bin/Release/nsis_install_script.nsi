# define installer name
OutFile "installer.exe"

# set desktop as install directory
InstallDir $DESKTOP\Snake360

# default section start
Section

# define output path
SetOutPath $INSTDIR

# specify files to go in output path
File Snake360.exe

File libsndfile-1.dll
File openal32.dll

File grassbackground2.jpg
File highscorebg.jpg
File snake_head.gif
File snake_skin.gif
File titlescreen.jpg

File eat.wav
File gameover.wav
File wetlands.wav

File arial.ttf

File highscores.txt



# define uninstaller name
WriteUninstaller $INSTDIR\uninstaller.exe


#-------
# default section end
SectionEnd

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"

# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe

# now delete installed files
Delete $INSTDIR\Snake360.exe

Delete $INSTDIR\libsndfile-1.dll
Delete $INSTDIR\openal32.dll

Delete $INSTDIR\grassbackground2.jpg
Delete $INSTDIR\highscorebg.jpg
Delete $INSTDIR\snake_head.gif
Delete $INSTDIR\snake_skin.gif
Delete $INSTDIR\titlescreen.jpg

Delete $INSTDIR\eat.wav
Delete $INSTDIR\gameover.wav
Delete $INSTDIR\wetlands.wav

Delete $INSTDIR\arial.ttf

Delete $INSTDIR\highscores.txt

RMDir $INSTDIR\

SectionEnd
