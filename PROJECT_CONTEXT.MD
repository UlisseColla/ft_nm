--- /dev/null
+++ /home/ucolla/Desktop/nm/PROJECT_CONTEXT.md
@@ -0,0 +1,105 @@
+# ft_nm Project Context
+
+## Overview
+This project is a custom implementation of the Unix `nm` command, written in C. It lists symbols from object files, executables, and shared libraries. The program is designed to handle ELF (Executable and Linkable Format) files, supporting both 32-bit and 64-bit architectures.
+
+## Architecture
+The program follows a modular design pipeline:
+1.  **Lexer/Parser**: Parses command-line arguments and flags.
+2.  **Initialization**: Maps the target file into memory using `mmap` and validates the ELF header.
+3.  **Core Processing**: Iterates through ELF sections to find the symbol table, extracts symbol information, and determines the symbol type (flag).
+4.  **Sorting**: Sorts symbols based on names (customizable via flags).
+5.  **Output**: Prints the symbol address, type, and name formatted according to the architecture.
+
+## File Descriptions & Responsibilities
+
+### `src/main.c`
+**Entry Point**
+-   Initializes the `Flags` structure and file list.
+-   Calls `args_lexer` to parse inputs.
+-   Iterates over input files (defaults to `a.out` if none provided).
+-   Orchestrates the flow: `init_elf` -> `ft_nm` -> cleanup.
+
+### `src/args_lexer.c`
+**Argument Parsing**
+-   Parses flags: `-a`, `-g`, `-u`, `-r`, `-p`.
+-   Manages flag priority logic (e.g., `-u` overrides `-g` and `-a`).
+-   Separates filenames from flags.
+-   Handles error reporting for invalid options.
+
+### `src/ft_nm.c`
+**Core Logic**
+-   Locates the Symbol Table (`SHT_SYMTAB`) and String Table within the ELF sections.
+-   Iterates through the raw ELF symbol structures.
+-   Filters symbols based on section indices.
+-   Calls `set_flag` to determine the character representation (e.g., 'T', 'U').
+-   Populates an array of `symbol` structs.
+-   Triggers `quick_sort` (unless `-p` is set).
+-   Delegates printing to `print.c`.
+
+### `src/utils.c`
+**ELF Validation & Memory Mapping**
+-   `init_elf`: Opens the file, retrieves file stats, and maps it into memory.
+-   `check_arch`: Detects architecture (32-bit vs 64-bit) by inspecting ELF magic numbers and `EI_CLASS`.
+-   `check_elf`: Validates ELF header integrity (offsets, sizes) using macros to support both 32/64-bit structures polymorphically.
+-   `get_address`: Formats the symbol address as a hex string, applying correct padding (8 chars for 32-bit, 16 for 64-bit).
+
+### `src/set_flag.c`
+**Symbol Type Determination**
+-   Determines the single-character symbol type (the "flag" in `nm` output).
+-   Logic maps ELF symbol types (`STT_FUNC`, `STT_OBJECT`) and bindings (`STB_GLOBAL`, `STB_WEAK`) to characters.
+-   Handles special section indices (`SHN_UNDEF`, `SHN_ABS`, `SHN_COMMON`).
+-   Distinguishes between global (uppercase) and local (lowercase) symbols.
+-   Uses macros (`SET_FLAG`) to handle both 32-bit and 64-bit symbol structures.
+
+### `src/quick_sort.c`
+**Sorting Algorithm**
+-   Implements the Quicksort algorithm.
+-   Uses a custom string comparison function that:
+    -   Is case-insensitive.
+    -   Ignores underscores (`_`).
+    -   Mimics the specific sorting behavior of the standard `nm` tool.
+
+### `src/print.c`
+**Output Formatting**
+-   Prints the formatted symbol address, type char, and name.
+-   Handles output filtering based on flags (`-u` for undefined, `-g` for external).
+-   Supports reverse printing order (`-r`).
+
+## Supported Flags
+| Flag | Description |
+| :--- | :--- |
+| `-a` | Display all symbols, including debugging symbols. |
+| `-g` | Display only external symbols. |
+| `-u` | Display only undefined symbols. |
+| `-r` | Reverse the sort order. |
+| `-p` | Do not sort the symbols. |
+
+## Key Data Structures
+
+**`Flags`**
+Holds the state of active command-line options (sorting mode, filter mode).
+
+**`file_info`**
+Contains metadata about the mapped file:
+-   `file_name`: Path to the file.
+-   `elf_file`: Pointer to the memory-mapped content.
+-   `file_size`: Size of the file.
+-   `arch`: Enum indicating `ARCH_32` or `ARCH_64`.
+
+**`symbol`**
+Internal representation for sorting and printing:
+-   `name`: Symbol name string.
+-   `address`: Formatted hex address string.
+-   `type`: The calculated character flag (e.g., 'T').
+-   `info`: Raw ELF info byte.
+
+## Implementation Notes
+-   **Memory Management**: The project relies heavily on `mmap` to avoid reading the entire file into a buffer manually.
+-   **Polymorphism**: While `ft_nm.c` in the provided context appears to focus on 64-bit structures, helper files like `utils.c` and `set_flag.c` use macros to support both 32-bit and 64-bit ELF files seamlessly.
+-   **Error Handling**: The lexer and ELF checkers provide robust error messages for invalid inputs or corrupted files.
+```

<!--
[PROMPT_SUGGESTION]Can you explain how the set_flag function determines if a symbol is 'T' vs 't' or 'W' vs 'w'? [/PROMPT_SUGGESTION]
[PROMPT_SUGGESTION]How does the custom string comparison in quick_sort.c differ from standard strcmp? [/PROMPT_SUGGESTION]
-->
