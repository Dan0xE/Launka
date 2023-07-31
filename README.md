# Quick TDU2 Launcher

## Overview

This is a small launcher for Test Drive Unlimited 2

## Requirements

- Test Drive Unlimited 2 installed on your system.
- A Windows environment.

## Setup

- Download the code from this repo.
- Ensure an .ini file named "config.ini" exists (rename the config.example file to config.ini) in the same directory as the executable. This file should contain the absolute path to your TDU2 directory and the Mutex Name (e.g., `TDU2_PATH=C:\Test Drive Unlimited 2` and `MUTEX_NAME=your_solution`).

## Usage

Run the executable to start the game.

## Functionality

To get the Mutex Name, decrypt the following Blowfish encrypted string with the key that is the lowercase boolean representation of 1

SVKFvl8ULBykxomtsdDYQQ

Use the decrypted solution in place of "your_solution" in the line MUTEX_NAME=your_solution of the "config.ini" file.

## Support

For help or bug reporting, please open a new issue in this repository.

## License

This project is licensed under the terms of the MIT license.
