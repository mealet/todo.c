## 🫐 Todo CLI
This is a simple Todo CLI Application written in C <br/>
I've made it just for fun and this code is NOT a good example!

## 🌀 Technical Details
- **Language:** C
- **C-Standart:** C11
- **Build Systems:** cmake

# ✨ Usage
```
todo [ARGUMENTS]

Options:
add [TITLE] [DESCRIPTION]
set [ID] [TITLE] [DESCRIPTION]
remove [ID]
check [ID]
help
```
On first launch program will create todo list file at the same dir and show you CLI arguments.

## 🛠️ How to Build
1. Install C compiler. Recommended: `gcc`, `clang`
2. Install [CMake](https://cmake.org/)
3. Clone this repository:
```sh
git clone https://github.com/mealet/todo.c
```
4. Build project:
```sh
mkdir -p build
cd build
cmake .. && cmake --build .
```
5. Your binary will be at the `build` folder with name _**todo**_ (on Windows: _**todo.exe**_)

## 👮‍♀️ License
Project is licensed under the MIT License. <br/>
To see more see [LICENSE](https://github.com/mealet/todo.c/blob/master/LICENSE)
