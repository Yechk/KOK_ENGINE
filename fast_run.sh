#!/bin/bash

if grep -qs '../KOK_RAM' /proc/mounts; then
  echo "RAM drive is mounted 512mb."
else
  echo "Mounting 512mb RAM drive now."
  if mount -t tmpfs -o size=512m tmpfs ../KOK_RAM; then
    echo "MOUNT SUCCESS"
  else
    exit
  fi
fi

echo "building test2"

if make; then
  echo "---BUILD SUCCESS---"

  echo ""
  echo "RSYNC files to RAM drive"
  rsync -auvzh ./ ../KOK_RAM/KOK_ENGINE_0_1/

  echo "Launching test2..."
  echo ""
  ../KOK_RAM/KOK_ENGINE_0_1/test2
else
  echo "FAILURE"
fi

echo "DONE"
echo ""
