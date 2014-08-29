var fs = require('fs');
var xml2js = require('xml2js');

function TrackReader() {
}

TrackReader.prototype.read = function(file) {
    // for now assume it's a gpx file
    reader = this;
    console.log('Reading file: ' + file);
    fs.readFile(file, function(err, data) {
        if (err) throw err;
        xml2js.parseString(data, function(err, xml) {
            if (err) throw err;
            reader.parseGpxXml(file, xml);
        });
    });
};

TrackReader.prototype.parseGpxXml = function(file, xml) {
    console.log('XML: ' + xml);
    var gpx = xml.gpx;
    
    var name = gpx.trk[0].name[0];
    var time = gpx.metadata[0].time[0];
    var pointsLength = gpx.trk[0].trkseg[0].trkpt.length;

    
    
    for (p in gpx.trk) {
        console.log('  p: ' + p);
    }
    console.log('time: ' + time);
};

module.exports = TrackReader;

