#!/bin/bash
mkdir -p ~/Pictures/screenshots/
maim -s > ~/Pictures/screenshots/$(date +%s).png
