#!/bin/bash

pidwait() {
    local pid=$1

    while kill -0 $pid; do
        echo "Process running..."
    done
    echo "Process finished!"
}
