#!/usr/bin/env bash
clear;
fswatch [opts] -0 $1 | \
  xargs -0 -n1 -I{} ./changeOSM/updateOSM ../../MAPs/sample_umarizal_belem.xml;