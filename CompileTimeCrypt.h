#pragma once
#pragma once

#include <cstddef> // For size_t

template <size_t N>
class EncryptedString {
public:
    constexpr EncryptedString(const char (&str)[N])
        : encrypted_{}, isEncrypted_(true), isCleared_(false) {
        for (size_t i = 0; i < N; ++i) {
            encrypted_[i] = str[i] ^ generateKey(i);
        }
    }

    const char* decrypt() const {

        if (isCleared_) {
            return ""; // Return an empty string if already cleared or decrypted.
        }

        if(!isEncrypted_){
            return decrypted_;
        }

        for (size_t i = 0; i < N; ++i) {
            decrypted_[i] = encrypted_[i] ^ generateKey(i);
        }
        isEncrypted_ = false; // Mark as decrypted
        return decrypted_;
    }

    void clear() {
        if (!isCleared_) {
            // Overwrite both encrypted and decrypted data to ensure it's irrecoverable.
            for (size_t i = 0; i < N; ++i) {
                encrypted_[i] = '\0';
                decrypted_[i] = '\0';
            }
            isEncrypted_ = false;
            isCleared_ = true; // Mark as cleared to block decryption.
        }
    }

    bool isEncrypted() const {
        return isEncrypted_;
    }

    bool isCleared() const {
        return isCleared_;
    }

private:
    mutable char encrypted_[N]; // Mutable to allow clearing
    mutable char decrypted_[N]{}; // Mutable for decryption
    mutable bool isEncrypted_;  // Tracks encryption status
    mutable bool isCleared_;    // Tracks whether data has been cleared

    static constexpr char generateKey(size_t position) {
        return '\xAA' ^ static_cast<char>((position * 33) % 256);
    }
};

// Helper function to deduce the size of the string at compile time and create an EncryptedString instance
template <size_t N>
constexpr EncryptedString<N> encrypt(const char (&str)[N]) {
    return EncryptedString<N>(str);
}
