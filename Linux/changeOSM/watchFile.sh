#!/usr/bin/env bash
clear;
fswatch [opts] -0 $1 | \
  xargs -0 -n1 -I{} \
	git add *;\
	git commit -m "changerOSM";\
	git push origin master;
