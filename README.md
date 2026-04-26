# Windows DLL Injector

A simple Windows DLL injector written in C++ using the WinAPI.  
This project demonstrates how to inject a custom DLL into a running process (e.g., Notepad) and execute code inside the target process.

---

## 📁 Project Structure

| File | Description |
|------|-------------|
| `injector.cpp` | The injector that loads the DLL into the target process |
| `mydll.cpp` | Demo DLL that shows a message box when loaded |
| `README.md` | This file |

---

## ⚙️ How It Works (Step by Step)

1. User enters the **PID** of the target process (e.g., Notepad)
2. `OpenProcess` opens the target process with full access
3. `VirtualAllocEx` allocates memory inside the target process (to store the DLL path)
4. `WriteProcessMemory` writes the DLL path string into the allocated memory
5. `GetModuleHandleA` + `GetProcAddress` find the address of `LoadLibraryA`
6. `CreateRemoteThread` creates a new thread in the target process that calls `LoadLibraryA`
7. `LoadLibraryA` loads the DLL
8. Windows calls `DllMain` inside the DLL
9. `DllMain` executes the demo code (shows a message box)

---

## 🛠️ Compilation

### Using MinGW (GCC)

bash
# Compile the DLL
g++ -shared -o mydll.dll mydll.cpp -static

# Compile the injector
g++ -o injector.exe injector.cpp -static

Using Visual Studio

Component Project Type
injector.cpp Console Application
mydll.cpp Dynamic-Link Library (DLL)

---

🚀 How to Run

1. Run Notepad
   
   notepad.exe
  
2. Find Notepad's PID
   · Press Ctrl + Shift + Esc to open Task Manager
   · Go to the Details tab
   · Find notepad.exe
   · Look at the PID column (e.g., 8472)
3. Copy the DLL
   
   Copy mydll.dll to C:\temp\mydll.dll
  
4. Run the injector as Administrator
   
bash
   injector.exe
  
5. Enter the PID
   
   Enter PID: 8472
  
6. Result
   · A message box will appear inside Notepad:
     
     Title: DLL Injection
     Message: I'm inside Notepad!
    

---

📁 DLL Location

The injector expects the DLL at:

C:\temp\mydll.dll


Make sure the file exists in that path before running the injector.

---

🧠 Code Explanation

Injector Code (injector.cpp)

Function Purpose
OpenProcess Gets a handle to the target process
VirtualAllocEx Allocates memory inside the target process
WriteProcessMemory Writes the DLL path into the allocated memory
GetModuleHandleA Gets the base address of kernel32.dll
GetProcAddress Finds the address of LoadLibraryA
CreateRemoteThread Starts a new thread in the target process
CloseHandle Closes the process handle to free resources

DLL Code (mydll.cpp)

Function Purpose
DllMain Entry point called by Windows when the DLL is loaded
DLL_PROCESS_ATTACH The reason code for when the DLL is first loaded
MessageBox Shows a popup window inside the target process
return TRUE Tells Windows that the DLL loaded successfully

---

⚠️ Requirements

· Windows operating system (x64)
· C++ compiler with WinAPI support (MinGW / MSVC)
· Administrator privileges (required by OpenProcess)

---

🧪 Troubleshooting

Problem Solution
OpenProcess fails Run the injector as Administrator
No message box appears Make sure C:\temp\mydll.dll exists
Notepad closes immediately The DLL must create a separate thread for long tasks
kernel32.dll not found Check for typos (it's kernel32.dll, not kernel132.dll)

---

📚 What I Learned from This Project

· How to open and manipulate another process using OpenProcess
· How to allocate memory in a remote process with VirtualAllocEx
· How to write data into another process's memory
· How to find the address of LoadLibraryA and call it remotely
· How DllMain works and when it gets executed
· Why DllMain should not contain blocking code (use threads instead)
· Debugging common issues like wrong DLL paths, typos in system DLL names, and permission errors

---

🔗 References

· Microsoft Docs: OpenProcess
· Microsoft Docs: VirtualAllocEx
· Microsoft Docs: CreateRemoteThread
· Microsoft Docs: DllMain

--- 

⚖️ Disclaimer
