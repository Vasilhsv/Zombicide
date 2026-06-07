
# 🧠Zombiecide

Welcome to the **Zombiecide** game! This is a console-based puzzle game written in C, where your goal is to find matching pairs of numbers on the board.  


## 📥 Download

To get started, you need to download the source code file to your computer:
* [project.c](project.c)

---

## ⚙️ Installation Guide (Windows) 

To compile and run this game, you need the **GCC compiler**. If you don't have it installed, please follow these steps:

### Step 1: Install MSYS2
1.  Open **PowerShell** or **CMD** (Command Prompt).
2.  Run the following command:
    ```powershell
    winget install -e --id MSYS2.MSYS2
    ```

### Step 2: Install GCC
1.  After installation, open the **MSYS2 UCRT64** application (search for it in the Start Menu).
2.  In the terminal that opens, type the following command to install the toolchain:
    ```bash
    pacman -S mingw-w64-ucrt-x86_64-gcc
    ```
3.  When asked `Proceed with installation? [Y/n]`, type **y** and press **Enter**.

### Step 3: Add to Windows Path
To make the compiler accessible from Windows:
1.  Press the **Windows Key** and type: `env`.
2.  Select **"Edit the system environment variables"**.
3.  Click on the **Environment Variables...** button.
4.  Under **System variables** (bottom section), find the row named **Path**, select it, and click **Edit**.
5.  Click **New** and paste the following path (assuming default installation):
    `C:\msys64\ucrt64\bin`
6.  Click **OK** on all windows.
7.  **Important:** Close any open CMD or PowerShell windows for the changes to take effect.

### Step 4: Verification
Open a new terminal and type:
```bash
gcc --version
```
If you see a message like gcc.exe (Rev...) 13.2.0, you are ready to go!


## 🚀 How to Compile & Run
Open your terminal (CMD or PowerShell) inside the folder where you saved Memory_Card_Game.c and run the following commands:

🔹 If using PowerShell:
```powershell
gcc project.c -o project.exe
./project.exe
```
🔹 If using CMD:
```cmd
gcc project.c -o project.exe
project.exe
```

## 🐧 Installation Guide (Linux)

If you are using a Linux distribution (like Ubuntu, Debian, Fedora, or Arch), follow these steps to install GCC and run the game.

### 1. Install GCC
Open your terminal and run the command corresponding to your system:

**For Ubuntu / Debian / Linux Mint:**
```bash
sudo apt update
sudo apt install build-essential
```

**For Fedora:**
```bash
sudo dnf install gcc
```

**For Arch Linux / Manjaro:**
```bash
sudo pacman -S gcc
```

### To verify the installation, type:
```bash
gcc --version
```
### 🚀 2. Compile and Run

Navigate to the folder where you downloaded Memory_Card_Game.c and run the following commands:
```bash
gcc zombiecide.c -o zombiecide
./zombiecide
```
## 🍎 Installation Guide (macOS)

If you are using a Mac, you need to install the **Xcode Command Line Tools** to compile C code.

### 🛠️ 1. Install GCC (via Xcode Tools)
1. Open the **Terminal** (press `Cmd + Space` and type "Terminal").
2. Run the following command:
```bash
xcode-select --install
```
3. A pop-up window will appear asking if you want to install the command line developer tools. Click Install.

## To verify the installation, type:
```bash
gcc --version
```

🚀 2. Compile and Run
Navigate to the folder where you downloaded Memory_Card_Game.c and run the following commands in your Terminal:

```bash
gcc project.c -o zombiecide
./zombiecide
```


## 📧 Contact
If you have any questions or issues, feel free to contact us at:

bill322007@hotmail.com

vartholomaiosvasilhs@gmail.com