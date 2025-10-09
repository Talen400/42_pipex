# Pipex

**Pipex** is a project that explores one of the fundamental concepts of Linux: **system calls**.

To interact with system resources, the Linux kernel uses **file descriptors (FDs)** — references
to open files or streams managed by a process. Every process has file descriptors,
and according to the POSIX standard, the default ones are:

* `stdin` = 0
* `stdout` = 1
* `stderr` = 2

Another important concept is that of **filters** — commands or programs that read from `stdin` 
and write to `stdout` (Example: cat, wc -l, grep...). Filters are what make shell pipelines work. For example:

```bash
cat file.txt | grep "word" | wc -l
```

Each command in the pipeline is a separate process that communicates through pipes.


## The program:

* Parses and executes a sequence of commands
* Creates the necessary pipes between them
* Uses `fork` and `execve` to handle process creation
* Closes unused FDs to avoid leaks or file descriptor exhaustion


## 🧰 Building

To compile the project:

* **Mandatory version:**

  ```bash
  make
  ```

* **Bonus version (with `here_doc` and multiple commands):**

  ```bash
  make bonus
  ```

The binary `pipex` will be generated in the project root directory.


## 🧪 Usage

### ✅ Mandatory version:

```bash
./pipex infile cmd1 cmd2 outfile
```

This will execute the equivalent of:

```bash
< infile cmd1 | cmd2 > outfile
```

### ✨ Bonus version:

Allows multiple commands and includes support for `here_doc`.

#### 📌 Syntax:

```bash
./pipex infile cmd1 cmd2 ... cmdN outfile
```

Equivalent to:

```bash
< infile cmd1 | cmd2 | ... | cmdN > outfile
```

#### ➕ With `here_doc`:

```bash
./pipex here_doc LIMITER cmd1 cmd2 ... cmdN outfile
```

This behaves like:

```bash
<< LIMITER cmd1 | cmd2 | ... | cmdN >> outfile
```

It will read from the standard input until the line containing `LIMITER`, and use that as the input for the pipeline. The output will be **appended** to the outfile (not overwritten).


## 📁 Example

```bash
./pipex infile "grep hello" "wc -l" outfile
```

Is equivalent to:

```bash
< infile grep hello | wc -l > outfile
```

With `here_doc`:

```bash
./pipex here_doc END "cat" "wc -l" result.txt
```

Then you type:

```
line 1
line 2
END
```


## 👤 Author

**tlavared** - 42 São Paulo


*Made with ❤️ at 42 São Paulo*



