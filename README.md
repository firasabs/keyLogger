# KeyLogger

This project is a keylogger application designed for both **macOS** and **Windows**, utilizing **C** and **Python**. The keylogger records keystrokes and periodically sends them to a Python server, where they are stored in an SQLite database. This project is created purely for **educational purposes** to demonstrate how low-level programming interacts with system APIs and network communication.

## Features
- **Cross-Platform Keylogger (Client):**
  - **macOS**:
    - Developed using Core Graphics and Carbon frameworks.
    - Captures keystrokes using macOS-specific APIs.
  - **Windows**:
    - Uses Windows API for low-level keylogging functionality.
  - Sends collected data to the Python server every 10 seconds.
- **Python Server**:
  - Receives keystrokes from clients on both macOS and Windows.
  - Stores the received data in an SQLite database.
- **SQLite Database**:
  - Saves timestamped keystroke data for each connected client.

## Technology Stack
- **C**:
  - Cross-platform implementation for capturing keystrokes.
  - Core Graphics and Carbon frameworks for macOS.
  - Windows API for keylogging on Windows systems.
- **Python**:
  - Socket programming for client-server communication.
  - SQLite for persistent data storage.
- **macOS System Frameworks**:
  - Core Graphics
  - Carbon
- **Windows System Frameworks**:
  - User32.dll
  - Kernel32.dll

## Disclaimer
This project is intended strictly for **educational purposes only**. Unauthorized use of keylogging software is illegal and may lead to severe consequences. Always ensure you have proper authorization before using this software.

## How to Run
### Prerequisites
- For macOS:
  - A macOS system to run the keylogger client.
  - GCC compiler installed.
- For Windows:
  - A Windows system with MinGW or any suitable compiler.
- Python 3 installed on the server system.

### Steps
1. **Compile the KeyLogger (Client):**
   - For macOS:
     ```bash
     gcc -o keylogger keylogger.c -framework ApplicationServices -framework Carbon -framework CoreServices
     ```
   - For Windows:
     ```bash
     gcc -o keylogger.exe keylogger.c -luser32 -lkernel32
     ```

2. **Run the Python Server:**
   - Navigate to the server directory and execute:
     ```bash
     python3 Server.py
     ```

3. **Run the KeyLogger (Client):**
   - On macOS:
     ```bash
     ./keylogger
     ```
   - On Windows:
     ```bash
     keylogger.exe
     ```

4. **Monitor Keystrokes:**
   - The server logs received keystrokes to the console and saves them in the SQLite database.

### SQLite Database
- The database (`keystrokes.db`) is automatically created and managed by the server.
- Use any SQLite viewer or the `sqlite3` CLI to inspect the database:
  ```bash
  sqlite3 keystrokes.db
  SELECT * FROM Keystrokes;
  ```

## Files
- **keylogger.c**: Cross-platform C code for capturing keystrokes and sending them to the server.
- **Server.py**: Python server to receive and store keystroke data.
- **Database.py**: Python module for handling SQLite database operations.

## Acknowledgments
This project is inspired by low-level programming concepts and socket programming tutorials. Special thanks to macOS and Windows documentation for providing essential APIs for Core Graphics, Carbon, and Windows API usage.

