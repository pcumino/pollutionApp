#!/usr/bin/env bash
clear;

inotifywait -e close_write,moved_to,create  . |
while read -r directory events $1; do
  ./changeOSM/updateOSM
done


# fswatch [opts] -0 $1 | \
#   xargs -0 -n1 -I{} ./changeOSM/updateOSM ../../MAPs/sample_umarizal_belem.xml;