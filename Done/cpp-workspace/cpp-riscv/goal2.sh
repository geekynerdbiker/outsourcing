#!/bin/bash

applications=("CCh")

cache_configurations=("1:256:64" "2:128:64" "4:64:64" "8:32:64" "16:16:64" "32:8:64" "64:4:64" "128:2:64" "256:1:64")

for app in "${applications[@]}"; do
    echo "$app"
    for config in "${cache_configurations[@]}"; do
        echo "$config"
        output=$(./spike --dc="$config" ~swe3005/2023f/proj3/pk ~swe3005/2023f/proj3/bench/"$app".elf)
        last_line=$(echo "$output" | tail -n 1)
        miss_rate=$(echo "$last_line" | grep -oE '[0-9]+\.[0-9]+')
        miss_rate_float=$(echo "$miss_rate" | bc -l)
        echo "$miss_rate_float"
        echo "$output"
    done
done
