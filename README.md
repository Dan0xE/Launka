# Quick TDU2 Launcher

## Overview

This is a small launcher for Test Drive Unlimited 2

## Requirements

- Test Drive Unlimited 2 installed on your system.
- A Windows environment.

## Setup

- Download the code from this repo.
- Ensure an .ini file named "config.ini" exists in the same directory as the executable (you can also just rename the config.example file to config.ini and replace the example values). This file should contain the absolute path to your TDU2 directory and the Mutex Name (e.g., `TDU2_PATH=C:\Test Drive Unlimited 2` and `MUTEX_NAME=your_solution`). PLEASE READ THE IMPORTANT SECTION BELOW!

## IMPORTANT

To get the Mutex Name, decrypt the following Blowfish encrypted string with the key that is the lowercase boolean representation of 1

SVKFvl8ULBykxomtsdDYQQ

Use the decrypted solution in place of "your_solution" in the line MUTEX_NAME=your_solution of the "config.ini" file.

A VALID MUTEX NAME IS NEEDED TO LAUNCH TDU2 VIA THIS LAUNCHER, OTHERWISE U MIGHT GET AN "Game has to be started via UpLauncher" ERROR!

## Usage

Run the executable to start the game.

## Support

For help or bug reporting, please open a new issue in this repository.

## License

This project is licensed under the terms of the MIT license.
