# CLI Password Manager

A simple command-line password manager written in C that utilizes the libsodium library for password hashing and sqlite3 for database storage. This password manager allows users to store, edit, delete, and search for passwords associated with different platforms and usernames.

## Features

- Add new password entries.
- Edit existing password entries.
- Delete password entries.
- Search for passwords by platform or username.

## Dependencies

Before you begin, ensure you have the following dependencies installed on your system:

- **gcc**: The GNU Compiler Collection.
- **libsodium**: A modern, easy-to-use software library for encryption, decryption, signatures, password hashing, and more.
- **sqlite3**: A C-language library that implements a small, fast, self-contained, high-reliability, full-featured, SQL database engine.

## Build Instructions

Follow these steps to build the CLI Password Manager:

1. Clone the repository:

   ```bash
   git https://github.com/sandeshkhadka/c-passmanager.git
   cd cd c-passmanager
   ```

2. Build the project using the provided Makefile:

   ```bash
   make
   ```

3. After a successful build, the executable `cpassmanager` will be created in the project directory.

## Usage

The CLI Password Manager offers several commands to interact with your stored passwords.

- **Show the main menu**:

  ```bash
  ./cpassmanager menu
  ```

- **Display help text**:

  ```bash
  ./cpassmanager help
  ```

- **List all stored passwords**:

  ```bash
  ./cpassmanager all
  ```

- **Add a new password entry**:

  ```bash
  ./cpassmanager addnew
  ```

- **Search for passwords by platform or username**:

  ```bash
  ./cpassmanager searchby platform  # Search by platform
  ./cpassmanager searchby username  # Search by username
  ```

## Cleanup

To remove the compiled binary and object files, run:

```bash
make clean
```
