#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PROGRAM="$PROJECT_ROOT/cub3D"
MAPS_DIR="$PROJECT_ROOT/Resources/maps/valid"

RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
RESET="\033[0m"

if [ ! -x "$PROGRAM" ]; then
    echo -e "${YELLOW}Building cub3D...${RESET}"
    make -C "$PROJECT_ROOT" > /dev/null 2>&1 || {
        echo -e "${RED}Failed to build cub3D${RESET}"
        exit 1
    }
fi

segfault_count=0
pass_count=0
total=0

echo -e "${YELLOW}Testing all .cub maps in $MAPS_DIR${RESET}\n"

for map in "$MAPS_DIR"/*.cub; do
    if [ ! -f "$map" ]; then
        echo -e "${RED}No .cub files found in $MAPS_DIR${RESET}"
        exit 1
    fi

    total=$((total + 1))

    "$PROGRAM" "$map" > /dev/null 2>&1
    exit_code=$?

    if [ $exit_code -eq 139 ]; then
        echo -e "${RED}[SEGFAULT]${RESET}  $map"
        segfault_count=$((segfault_count + 1))
    elif [ $exit_code -ne 0 ]; then
        echo -e "${RED}[FAIL $exit_code]${RESET}  $map"
        segfault_count=$((segfault_count + 1))
    else
        echo -e "${GREEN}[OK]${RESET}       $map"
        pass_count=$((pass_count + 1))
    fi
done

echo -e "\n${YELLOW}--- Results ---${RESET}"
echo -e "${GREEN}Passed:    $pass_count / $total${RESET}"
if [ $segfault_count -gt 0 ]; then
    echo -e "${RED}Failed:    $segfault_count / $total${RESET}"
else
    echo -e "${GREEN}Failed:    0 / $total — all valid!${RESET}"
fi
