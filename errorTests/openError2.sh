#!/bin/bash
# try to open file without permissions
chmod 000 ~/monty/errorTests/unreachableFile
~/monty/monty ~/monty/errorTests/unreachableFile
chmod 777 ~/monty/errorTests/unreachableFile
