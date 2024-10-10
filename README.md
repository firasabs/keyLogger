# keyLogger
1. start python Server:
    python3 Server.py
2. Run the C Client (Keylogger): Compile and run the C keylogger on your mac:
    gcc -o keyloggermac keyloggermac.c -framework ApplicationServices -framework Carbon -framework CoreServices
    ./keyloggermac