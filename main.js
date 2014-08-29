#!/usr/local/bin/node

if (process.argv.length < 3) {
    console.log('ERROR: No gpx file provided');
    console.log();
    usage();
    return;
}

var AnalysisManager = require('./src/AnalysisManager.js');
var analysisManager = new AnalysisManager();

var gpxfile = process.argv[process.argv.length - 1];
analysisManager.analyse(gpxfile);

function usage() {
    console.log('Usage:');
    console.log('  node main.js gpxfile');
}

