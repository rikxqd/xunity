call ndk-build

if %errorlevel% == 0 goto PUSHANDINJECT
goto END

:PUSHANDINJECT
copy ".\libs\armeabi-v7a\launch" "..\work\launch"

:END
echo>nul