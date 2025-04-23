# 🖥️ encryptUrDesktop

A lightweight tool that encrypts/decrypts every file on your Windows desktop using **AES-128 in ECB mode**. Designed for educational or experimental use — not intended for production-grade security.

---

## 📁 Project Structure

```
encryptUrDesktop/
├── aes.c              # Core AES-128 ECB logic
├── aes.h              # AES definitions and declarations
├── encryptUrDesktop.c # Main logic for traversing and encrypting desktop files
├── utils.c            # File traversal and buffer I/O utilities
├── utils.h            # Utility function declarations
```

---

## ⚙️ How It Works

1. **Desktop Targeting**: Automatically locates and targets `C:\Users\<Username>\Desktop\`.
2. **Recursive Traversal**: Walks through all files (excluding directories) under the Desktop folder.
3. **AES-128 ECB**:
   - Encrypts or decrypts each file using AES-128 in ECB mode.
   - Uses **PKCS#7 padding** to align input to 16-byte blocks.
4. **Key Handling**:
   - Uses a static 16-byte key defined in code.
5. **Execution Modes**:
   - `-e`: Encrypt mode
   - `-d`: Decrypt mode

---

## 🚀 How to Use

```bash
encryptUrDesktop.exe -e   # Encrypt all desktop files
encryptUrDesktop.exe -d   # Decrypt all desktop files
```

> **Warning**: This tool modifies files in-place. Make backups before testing.

---

## 🔧 Build Instructions

```bash
gcc -o encryptUrDesktop encryptUrDesktop.c aes.c utils.c -I.
```

> Windows-only: Tested with `MinGW` or compatible toolchains.

---

## ✅ Features & Limitations

✔ Recursively processes all desktop files  
✔ AES-128 encryption in ECB mode  
✔ PKCS#7 padding support  
✘ No dynamic key input (static key only)  
✘ ECB mode is insecure for real-world use  
✘ No file exclusion or backup support

---

## ⚠️ Disclaimer

This project is **for educational purposes only**. It is not secure for protecting sensitive data in real-world applications. ECB mode is susceptible to pattern leakage and should be replaced with CBC, CTR, or GCM in serious contexts.
