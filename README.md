### 📌 **Short Description**

**Simple Bash Utils** is a C-based implementation of the classic Bash text processing tools `cat` and `grep`. The project covers argument parsing, file handling, and regular expressions, offering a hands-on experience in POSIX-compliant CLI utility development with full GNU flag support, Makefile automation, and structured C11 programming.

````markdown
# 🐚 Simple Bash Utils

Reimplementation of classic Bash tools `cat` and `grep` using C (C11 standard). This project is part of the School 21 curriculum and deepens skills in command-line utility development, argument parsing, text processing, file handling, and working with regular expressions (regex).

> 📍 POSIX-compliant. Implemented with structured programming principles and GNU-like flag support.

---

## 📁 Project Structure

```bash
simple_bash_utils/
├── src/
│   ├── cat/
│   │   ├── s21_cat.c        # Main logic of cat
│   │   ├── s21_cat.h
│   │   └── Makefile         # Build script for cat
│   │
│   ├── grep/
│   │   ├── s21_grep.c       # Main logic of grep
│   │   ├── s21_grep.h
│   │   └── Makefile         # Build script for grep
│   │
│   └── common/              # Shared modules (if used)
│       ├── file_utils.c
│       └── regex_utils.c
└── README.md
````

---

## 📦 Implemented Utilities

### 🐈 s21\_cat

A reimplementation of the `cat` command-line utility with the following flags:

| Flag | Description                                    |
| ---- | ---------------------------------------------- |
| `-b` | Number non-empty lines                         |
| `-e` | Display `$` at end of each line (implies `-v`) |
| `-n` | Number all lines                               |
| `-s` | Squeeze multiple blank lines into one          |
| `-t` | Display tabs as `^I` (implies `-v`)            |

📌 Executable output: `src/cat/s21_cat`
📌 Usage example:

```bash
./s21_cat -b file.txt
```

---

### 🔍 s21\_grep

A reimplementation of the `grep` utility supporting both basic and extended POSIX regular expressions.

#### ✅ Required flags:

| Flag | Description                |
| ---- | -------------------------- |
| `-e` | Pattern                    |
| `-i` | Ignore case                |
| `-v` | Invert match               |
| `-c` | Count matching lines       |
| `-l` | Output matching file names |
| `-n` | Show line number           |

#### 🧪 Bonus flags (if implemented):

| Flag | Description                      |
| ---- | -------------------------------- |
| `-h` | Hide file names in output        |
| `-s` | Suppress error messages          |
| `-f` | Read patterns from file          |
| `-o` | Show only matching part of lines |

📌 Executable output: `src/grep/s21_grep`
📌 Usage example:

```bash
./s21_grep -i "linux" file.txt
```

---

## 🛠️ Build & Run

Each utility has its own `Makefile`.

```bash
# Build cat
cd src/cat/
make

# Build grep
cd ../grep/
make
```

To clean build artifacts:

```bash
make clean
```

---

## 🧪 Testing

* Integration tests compare output of `s21_cat` and `s21_grep` to GNU `cat` and `grep`
* Tests cover all flag combinations and edge cases
* Input from `stdin` is not required (per project constraints)

---

## 📚 Technologies

* Language: C (C11)
* Build: Makefile
* Standards: POSIX.1-2017
* Regex: `<regex.h>` or PCRE (if bonus implemented)
* Style: [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

---

## 🚀 Educational Goals

* Deepen understanding of Linux CLI tools
* Learn argument parsing with `getopt`
* Work with files and streams in C
* Use regex libraries in C
* Follow structured programming and modular design

---

## 🌐 Author

**👤 z4ng1ew** — [GitHub](https://github.com/z4ng1ew)
Project developed for **School 21**.

---

## 📌 License

This project is for educational use. No license required for submission.

---

## 🔖 Examples

```bash
# s21_cat usage
./s21_cat -n input.txt

# s21_grep usage
./s21_grep -iv "Linux" ./docs/*.md
```
