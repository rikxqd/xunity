adb push launch /data/local/tmp/
adb push libxmono.so /data/local/tmp/
adb push liblua.so /data/local/tmp/
adb push libsubstrate.so /data/local/tmp/
adb push Lua.dll /data/local/tmp/
adb push behaviac.dll /data/local/tmp/
adb push cfac.dll /data/local/tmp/
call pushscript.bat
adb shell<launch.txt