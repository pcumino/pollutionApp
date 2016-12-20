#!/bin/sh
source app.config
clear;
rm -rf sensorData.json

function requestSensors {
	i=0;
	echo "Getting sensors from $1";
	echo '[' >> sensorData.json;
	while [ $i -le $numberOfSensors ]
	do
		# result=$(curl $1:1026/v2/entities/StreetFixed$i?option=keyValues -s -S --header 'Accept: application/json' | python -mjson.tool);
		# result=$(curl $1:1026/v2/entities/StreetFixed$i?options=keyValues -s -S --header 'Accept: text/plain' | python -mjson.tool);
		# result=$(curl $1:1026/v2/entities/StreetFixed$i/attrs/temperature/value -s -S --header 'Accept: text/plain' | python -mjson.tool)
		result=$(curl $1:$orionPort/v2/entities/StreetFixed$i?options=values&attrs=aircondition,position,temperature -s -S --header 'X-Auth-Token: $authToken' --header 'Accept: application/json');
		if echo "$result" | grep -q "error"; then
			echo "ERROR StreetFixed$i" >> log.txt;
		else
			echo "{\"id\":\"StreetFixed$i\",\"values\":"$result'},' >> sensorData.json;
		fi
		i=$[$i+1];
	done
	sed -i '' '$ s/.$//' sensorData.json;
	echo ']' >> sensorData.json;
	# Removing last newline break
	# This part is important to make the sensorData.json easily readable by the node js app
	perl -pi -e 'chomp if eof' sensorData.json;
}

requestSensors $orionIPaddress;