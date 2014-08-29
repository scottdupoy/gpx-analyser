var TrackReader = require('./TrackReader.js');

function AnalysisManager() {
    this.trackReader = new TrackReader();
};

AnalysisManager.prototype.analyse = function(gpxfile) {
    var track = this.trackReader.read(gpxfile);
};

module.exports = AnalysisManager;

