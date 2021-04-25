# Program selector

A (work-in-progress) framework for automatically setting up C++ programs based on a source folder, and a program selector that simplifies running programs and switching between them.

## Building

Use the `build.sh` script to build a separate project for each folder in the `src` directory. Program arguments:

- `-b`: Build the source code after generating project files.
- `-r`: Generate project files, build the source code, and then run the `program_selector` executable.
- `-d`: Use the `Debug` configuration instead of `Release` configuration. Can be combined with `-b` or `-r`.
