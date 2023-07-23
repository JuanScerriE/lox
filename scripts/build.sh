#!/bin/sh

cmake -S . -B build -GNinja && echo "Copying compile_commands.json..." &&
    cp build/compile_commands.json compile_commands.json && ninja -C build
