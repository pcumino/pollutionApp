var port = 3000;
var express = require('express');
var app = express();
var fs = require("fs");
var bodyParser = require('body-parser');

var jsonParser = bodyParser.json();

var file = "../changeOSM/sensorData.json";

app.get('/', function (req, res) {
	// res.writeHead(200, {'Content-Type': 'text/plain'});
	var value = "";
	getFileContent(file, function(data, readerr){
		value = "<!DOCTYPE html>"+
		"<head>"+
		"<title>Pollution App is running</title>"+
		"</head>"+
		"<body> <pre>"+
		"<h2>PollutionApp is running on port: <i>"+port+"</i></h2> </pre>"+
		"<pre>from local file: <br>"+data+"</pre>"+
		"</body>";
		res.writeHead(200);
	res.end(value);
	});
	// res.end("pollutionApp page");
	
});

app.post('/', jsonParser, function (req, res) {
	var dataFromFile = '';
	if(!file){
		console.log("file not found");
	}

	getFileContent(file, function(data, readerr){
		console.log("\ndata: "+data);
		if(readerr){
			console.log(readerr);
			res.end(readerr);
		}
	});

	if(req.body.subscriptionId){
		getFileContent(file, function(data,readerr){
			if(readerr){
				console.log(readerr);
				res.end(readerr);
			}
			/*
			After get the last subscription this part
			update the in file only the updated sensors
			*/
			if(!data) data = "[]";
			var dataObj = JSON.parse(data);
			var reqID = req.body.data[0].id;
			var reqAircondition = req.body.data[0].aircondition.value;
			var reqPosition = req.body.data[0].position.value;
			var reqTemperature = req.body.data[0].temperature.value;
			/*
			Adding the other sensors to the result string if
			not already present in the file
			*/
			var sensorIndex = getIndexIfObjWithOwnAttr(dataObj,"id",reqID);

			if(sensorIndex >= 0){
				dataObj[sensorIndex].values[0] = reqAircondition;
				dataObj[sensorIndex].values[1] = reqPosition;
				dataObj[sensorIndex].values[2] = reqTemperature;
			}
			else{
				dataObj.push({"id":reqID, "values":[reqAircondition,reqPosition,reqTemperature]});
			}
			dataObj = dataObj.sort(function(a, b) {
				var nameA = a.id.toUpperCase();
				var nameB = b.id.toUpperCase();
				if (nameA < nameB) {
					return -1;
				}
				if (nameA > nameB) {
					return 1;
				}
				return 0;
			});
			fs.writeFile(file, (JSON.stringify(dataObj)) , function(writeerr) {
				if(err) res.end("[Server] "+err);
				else res.end("[Server] "+"done!");
			});

		});
	}
	else
		res.end("[Server] "+"Not a subscription request!\n");
});
var getIndexIfObjWithOwnAttr = function(array, attr, value) {
	for(var i = 0; i < array.length; i++) {
		if(array[i].hasOwnProperty(attr) && array[i][attr] === value) {
			return i;
		}
	}
	return -1;
}
function getFileContent(srcPath, callback) { 
	fs.readFile(srcPath, 'utf8', function (err, data) {
		if (err){
			console.log(err);
			callback("\nerr: "+err);
		}
		else
			callback("\ndata: "+data);
	}
	);
}

var server = app.listen(port, function () {
	var host = server.address().address;
	var port = server.address().port;
	console.log("pollutionApp listening at http://"+host+":"+port);
});
