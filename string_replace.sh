#!/usr/bin/env bash

DIR="$1"
OLD="$2"
NEW="$3"

if [[ -z "$DIR" || -z "$OLD" || -z "$NEW" ]]; then
  echo "Usage: $0 <directory> <old_string> <new_string>"
  exit 1
fi

find "$DIR" -type f -exec sed -i "s/${OLD}/${NEW}/g" {} +
