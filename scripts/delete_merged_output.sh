#!/bin/bash
if [ "$1" == "false" ]; then
  if [ -f "$2" ]; then
    rm "$2"
  fi
fi
