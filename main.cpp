#include <windows.h>
#include "include/CompileTimeCrypt.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    auto encryptedHello = encrypt("Hello, World!"); // Encrypts at compile time
    MessageBoxA(NULL, encryptedHello.decrypt(), "Decrypted HW Message 1", MB_OK); // Decrypts at runtime
    encryptedHello.clear(); // this will write over / erase the original encrypted and decrypted strings
    MessageBoxA(NULL, encryptedHello.decrypt(), "Decrypted HW Message 2", MB_OK); // because the message was cleared, the window is blank

    auto encryptedTestMessage = encrypt("Second Test!"); // Encrypts at compile time
    MessageBoxA(NULL, encryptedTestMessage.decrypt(), "Test Message 1", MB_OK); // Decrypts at runtime
    MessageBoxA(NULL, encryptedTestMessage.decrypt(), "Test Message 2", MB_OK); // Expected to return decrypted string again, because uncleared
    encryptedTestMessage.clear(); // this will write over / erase the original encrypted and decrypted strings
    MessageBoxA(NULL, encryptedTestMessage.decrypt(), "Test Message 3", MB_OK); // because the message was cleared, the window is blank

    MessageBoxA(NULL, encrypt("Inline String Test").decrypt(), "Inline String Test - One Liner", MB_OK); // Encrypts at compile & decrypts at runtime - oneliner
    // not recommended if you need to clear the data as there will not be a way to do so 
    
    return 0;
    
}
