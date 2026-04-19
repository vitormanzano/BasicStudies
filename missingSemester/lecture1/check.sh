#!/bin/bash

if [ -f "$1" ]; then
    echo "$1 exist and is a regular file"
else
    echo "$1 not exists or is not a regular file"
fi
