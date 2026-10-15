# Checklist Before Push - `ft_nm`

This document details all potential issues, non-compliances with the subject (`en.subject.pdf`), safety risks, and recommended fixes before submitting the project.

---

## 1. Forbidden External Functions (Evaluation Blocker)

The subject allows only the following external functions:
> `open(2)`, `close(2)`, `mmap(2)`, `munmap(2)`, `write(2)`, `fstat(2)`, `malloc(3)`, `free(3)`, `exit(3)`, `perror(3)`, `strerror(1)`, `getpagesize(2)` and functions from your own `libft`.

### Issues:
* **[`src/args_lexer.c:61`](file:///Users/ulisse/Desktop/ft_nm/src/args_lexer.c#L61): Call to libc `strcmp`**
  ```c
  if (str[0] != '-' || (strcmp("-", &str[0]) == 0 && ft_strlen(str) == 1)) {
  ```
  `strcmp` is a libc function that is **not allowed**.
  * **Fix:** Replace `strcmp` with `ft_strncmp` from your `libft`, or simplify to:
    ```c
    if (str[0] != '-' || (str[0] == '-' && str[1] == '\0')) {
    ```
* **Verification:** Run `nm -u ft_nm` on Linux after compiling to ensure no unauthorized libc symbols appear in the binary.

---

## 2. Core Functional Requirements & Bugs

### A. Missing Execution on Default `a.out`
* **Subject:** *"List symbols in [file(s)] (a.out by default)."*
* **Location:** [`src/main.c:24-28`](file:///Users/ulisse/Desktop/ft_nm/src/main.c#L24-L28)
* **Problem:** When no file argument is passed, `init_elf` is called on `"./a.out"`, but `ft_nm(&info, flags)` and `munmap(...)` are **never called**:
  ```c
  if (list_size == 0) {
      file_info info = {};
      status = init_elf(&info, "./a.out");
      if (status == 1) return status;
      // BUG: ft_nm is not called here, program simply exits without printing symbols!
  }
  ```
* **Fix:** Make sure `ft_nm(&info, flags)` and `munmap(...)` are executed for `a.out` just like in the file loop, and format error messages like system `nm` (`nm: 'a.out': No such file`).

### B. Relocatable Object Files (`.o`) and 32-bit Binaries Rejected
* **Subject:** *"You have to work with ELF binaries. You have to handle x86_32, x64, object files, .so"*
* **Location:** [`src/utils.c:76-81`](file:///Users/ulisse/Desktop/ft_nm/src/utils.c#L76-L81)
* **Problem:**
  ```c
  if (header->e_ident[EI_CLASS] != ELFCLASS64 &&
      header->e_ident[EI_DATA] != ELFDATA2LSB &&
      header->e_type != ET_EXEC &&
      header->e_type != ET_DYN) {
          return ft_printf_fd(2, "Symbol table or string table not found\n");
  }
  ```
  * For object files (`.o`), `e_type` is `ET_REL`, not `ET_EXEC` or `ET_DYN`.
  * For 32-bit binaries, `EI_CLASS` is `ELFCLASS32`, not `ELFCLASS64`.
* **Fix:** Allow `ET_REL` (`header->e_type == ET_REL || header->e_type == ET_EXEC || header->e_type == ET_DYN`), and check `EI_CLASS` according to `info->arch` (`ELFCLASS32` or `ELFCLASS64`).

### C. Incorrect Header Path `<elf.h>`
* **Location:** [`headers/ft_nm.h:26`](file:///Users/ulisse/Desktop/ft_nm/headers/ft_nm.h#L26)
* **Problem:** `#include "./elf.h"` assumes a local file exists. On Linux systems, it is a system header:
* **Fix:** Use `#include <elf.h>`.

---

## 3. Robustness & Bounds Checking (Strict Crash Prevention)

The subject explicitly specifies:
> *"In no way can your program quit in an unexpected manner (Segmentation fault, bus error, double free, etc)."*
> *"Be cautious. There are many ways to lead your program out of the mapped content, may it be with non-null terminated string, incorrect offsets... Check everything."*

### High-Risk Memory Bounds Issues:
1. **Out-of-Bounds Section Access on Special Symbols (`SHN_ABS`):**
   * **Location:** [`src/set_flag.c:26-30`](file:///Users/ulisse/Desktop/ft_nm/src/set_flag.c#L26-L30)
   * **Problem:**
     ```c
     sec_ ## base *sym_sec = &(((sec_ ## base *)sections)[shndx]);
     if ((void *)sym_sec > max) return 'a';
     uint64_t readonly = !(sym_sec->sh_flags & SHF_WRITE);
     if (shndx == SHN_ABS) {
         return (bind == STB_LOCAL) ? 'a' : 'A';
     }
     ```
     `SHN_ABS` has the value `0xfff1` (65521). When `shndx == SHN_ABS`, indexing `sections[65521]` and dereferencing `sym_sec->sh_flags` occurs **before** the `shndx == SHN_ABS` check, which will cause a segmentation fault / bus error on unmapped memory.
   * **Fix:** Always check special indices (`shndx == SHN_ABS`, `shndx == SHN_UNDEF`, `shndx == SHN_COMMON`) **before** indexing or dereferencing `sections[shndx]`.

2. **String Table Bounds Check:**
   * **Location:** [`src/ft_nm.c:70`](file:///Users/ulisse/Desktop/ft_nm/src/ft_nm.c#L70)
   * **Problem:** `str_table_data + offset` is read without checking if `offset < sec_headers[str_tab_index].sh_size` and without verifying whether strings are null-terminated within mapped file boundaries. Corrupted binaries will cause reading past memory bounds.
   * **Fix:** Validate that `offset < sec_headers[str_tab_index].sh_size` and `(str_table_data + offset) < (info->elf_file + info->file_size)`.

3. **Ignored Return Value in `init_elf`:**
   * **Location:** [`src/utils.c:152-153`](file:///Users/ulisse/Desktop/ft_nm/src/utils.c#L152-L153)
   * **Problem:**
     ```c
     ret = check_arch((unsigned char *)file_bytes, info);
     ret = check_elf(info);
     ```
     If `check_arch` fails and returns `1`, its return code is overwritten by `check_elf`, which proceeds to parse corrupted data.
   * **Fix:**
     ```c
     if (check_arch((unsigned char *)file_bytes, info) != 0)
         return 1;
     return check_elf(info);
     ```

4. **Handling of Empty Files / Directories:**
   * **Location:** [`src/utils.c:136-150`](file:///Users/ulisse/Desktop/ft_nm/src/utils.c#L136-L150)
   * **Problem:** If a file has size `0` (or is a directory), calling `mmap(..., 0, ...)` fails with `EINVAL`, resulting in an unhelpful error message.
   * **Fix:** Check `S_ISDIR(file_stat.st_mode)` and verify that `file_stat.st_size > (off_t)sizeof(Elf64_Ehdr)` before attempting to `mmap`.

---

## 4. Repository Structure & Makefile

* **Separate `ft_printf_fd` directory:**
  The subject states:
  > *"Submit also your folder libft including its own Makefile at the root of your repository."*
  Having an extra library directory `ft_printf_fd` is non-standard for 42 submissions. It is recommended to merge `ft_printf_fd` files inside `libft/` so that `libft` builds a single complete archive (`libft.a`).
* **Makefile Subshell & Background Process:**
  The root [`Makefile`](file:///Users/ulisse/Desktop/ft_nm/Makefile#L35-L53) uses background subshells (`&`, `wait $PID`, `kill -0`) and hides compilation logs in `build.log`. Automated evaluation scripts and strict peer testers often fail or hang with background subshell make loops. A standard, direct rule compilation is recommended.

---

## 5. Summary Priority Action Plan

1. [ ] **Remove `strcmp` in `src/args_lexer.c:61`** (Immediate 0 on forbidden functions if not fixed).
2. [ ] **Fix default execution for `./a.out` in `src/main.c:24`**.
3. [ ] **Fix `check_elf` in `src/utils.c`** to support `.o` (`ET_REL`) and 32-bit (`ELFCLASS32`).
4. [ ] **Fix `set_flag.c`** to handle special sections (`SHN_ABS`, `SHN_UNDEF`) before dereferencing `sections[shndx]`.
5. [ ] **Check `check_arch` return code** before calling `check_elf`.
6. [ ] **Change `#include "./elf.h"` to `#include <elf.h>`** in `headers/ft_nm.h`.
7. [ ] **Test with corrupt ELF files** (e.g. truncated files, corrupted section headers) to ensure no crash/segfault occurs.
