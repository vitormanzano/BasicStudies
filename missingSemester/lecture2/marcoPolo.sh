#!/bin/bash

marco() {
    currentDirectory="$(pwd)"
    echo "$currentDirectory" > ~/marcoDirectory.txt
}

polo() {
    if [ ! -f "$HOME/marcoDirectory.txt" ] 
        echo "Run marco first!"
        return 1
    fi
    cd "$(cat ~/marcoDirectory.txt)"
}
