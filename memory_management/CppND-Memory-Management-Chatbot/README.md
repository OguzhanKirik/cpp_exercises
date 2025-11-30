Memory Management Chatbot


<img src="images/chatbot_demo.gif"/>

# 🤖 ChatBot Memory Management Optimization

This project implements a **C++ chatbot** that answers user queries related to **memory management in C++**.  
After loading a knowledge base from a text file, the chatbot builds an in-memory **knowledge graph**:

- **Nodes** represent chatbot answers
- **Edges** represent user question keywords

When a user submits a query, the system computes the **Levenshtein distance** to determine the closest matching response.

---

## 🛠️ Project Purpose

The original implementation is functional, but it uses **raw pointers** everywhere and lacks modern C++ memory practices:

- No **smart pointers**
- No **move semantics**
- Poor ownership clarity
- Risk of memory leaks and dangling pointers

Your goal is to **refactor and optimize the program using modern C++ best practices**.

---

## 📚 What You Will Do

You will:

1. **Analyze the codebase**
2. **Identify unsafe memory behavior**
3. **Introduce RAII principles**
4. **Use smart pointers appropriately**
5. **Implement move semantics where beneficial**

There are **five specific required tasks**, described in detail in the classroom instructions.

---

## ❗ Known Issue

The application currently **crashes when the GUI window is closed**.  
This indicates a **memory management bug**.  
Your **first warm-up task** is to find the bug and fix it.

This will help you understand the ownership model and prepare you for the deeper refactoring tasks.

---

## 🧩 Dependencies (Local Setup)

You will need the following:

- **cmake ≥ 3.11**
  - Install: https://cmake.org/install/

- **make ≥ 4.1 (Linux/Mac), ≥ 3.81 (Windows)**
  - Linux: typically preinstalled
  - Mac: install via Xcode Command Line Tools  
    https://developer.apple.com/xcode/features/
  - Windows: http://gnuwin32.sourceforge.net/packages/make.htm

- **gcc/g++ ≥ 5.4**
  - Linux: usually included
  - Mac: bundled with Xcode tools
  - Windows: recommended — MinGW  
    http://www.mingw.org/

- **wxWidgets ≥ 3.0**
  - Linux:
    ```bash
    sudo apt-get install libwxgtk3.0-gtk3-dev libwxgtk3.0-gtk3-0v5
    ```
    If you encounter unmet dependencies, see:  
    https://wiki.codelite.org/pmwiki.php/Main/WxWidgets30Binaries#toc2
  - macOS: Homebrew package  
    https://formulae.brew.sh/formula/wxmac
  - Installation guide:  
    https://wiki.wxwidgets.org/Install  
    *(Adjust version numbers as needed for ≥ 3.0)*

---

## 🚀 Build Instructions

From the root project directory:

```bash
# Clone repository
git clone <repo-url>

# Create and enter build directory
mkdir build && cd build

# Compile
cmake .. && make

# Run
./membot
