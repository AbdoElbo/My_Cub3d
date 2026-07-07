#!/bin/bash

PROGRAM="../../cub3D"
MAPS_DIR="../../Resources/maps/invalid"

RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
RESET="\033[0m"

segfault_count=0
pass_count=0
total=0

echo -e "${YELLOW}Testing all .cub maps in $MAPS_DIR${RESET}\n"

for map in "$MAPS_DIR"/*.cub; do
    # no .cub files found
    if [ ! -f "$map" ]; then
        echo -e "${RED}No .cub files found in $MAPS_DIR${RESET}"
        exit 1
    fi

    total=$((total + 1))

    # run cub3D, suppress output, capture exit code
    "$PROGRAM" "$map"
    exit_code=$?

    # segfault = exit code 139 (128 + signal 11)
    if [ $exit_code -eq 139 ]; then
        echo -e "${RED}[SEGFAULT]${RESET}  $map"
        segfault_count=$((segfault_count + 1))
    elif [ $exit_code -eq 0 ]; then
        echo -e "${RED}[KO $exit_code]${RESET}    $map"
    else
        echo -e "${GREEN}[OK $exit_code]${RESET}    $map"
        pass_count=$((pass_count + 1))
    fi
done

echo -e "\n${YELLOW}--- Results ---${RESET}"

# echo -e "${GREEN}Passed:    $pass_count / $total${RESET}"
if [ $pass_count -ne $total ]; then
    echo -e "${RED}Passed: $pass_count / $total${RESET}"
else
    echo -e "${GREEN}Passed: $pass_count / $total — all clean!${RESET}"
fi

if [ $segfault_count -gt 0 ]; then
    echo -e "${RED}Segfaults: $segfault_count / $total${RESET}"
else
    echo -e "${GREEN}Segfaults: 0 / $total — all clean!${RESET}"
fi
