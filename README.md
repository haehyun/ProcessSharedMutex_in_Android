# Process Shared Mutex in Android
This is an example of using the process shared mutex in Android. 

After building the source code, 

adb push Server /Server,
adb push Client /Client

adb shell chmod 755 /Server,
adb shell chmod 755 /Client

adb shell ./Server,
adb shell ./Client
