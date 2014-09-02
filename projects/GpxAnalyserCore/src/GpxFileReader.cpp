#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "GpxFileReader.h"
#include "AnalyserException.h"
#include "Track.h"
#include "Point.h"

using namespace std;

namespace GpxAnalyserCore
{

enum FileReadState
{
    LookingForTime = 0,
    LookingForName = 1,
    ReadingTrack = 2,
};

Track* GpxFileReader::Read(string& filePath)
{
    cout << "Reading file: " << filePath << endl;

    // TODO: RAII stream appropriately
    ifstream stream(filePath);
    if (!stream.is_open())
    {
        throw AnalyserException("Couldn't open file");
    }
    
    string line;
   
    // TODO: clean this up if there's a failure mid way through
    Track* track = new Track();

    Point point;
    
    FileReadState state = FileReadState::LookingForTime;
    while (getline(stream, line))
    {
        switch (state)
        {
            case FileReadState::LookingForTime:
                {
                    size_t  start = line.find("<time>");
                    size_t  end = line.find("</time>");
                    if (start != string::npos && end != string::npos)
                    {
                        string timeString = line.substr(start + 6, end - 8);
                        if (timeString.length() < 19)
                        {
                            throw AnalyserException("File time element too short");
                        }

                        track->UtcTime.tm_year = atoi(timeString.substr(0, 4).c_str());
                        track->UtcTime.tm_mon = atoi(timeString.substr(5, 2).c_str()) - 1;
                        track->UtcTime.tm_mday = atoi(timeString.substr(8, 2).c_str());
                        track->UtcTime.tm_hour = atoi(timeString.substr(11, 2).c_str());
                        track->UtcTime.tm_min = atoi(timeString.substr(14, 2).c_str());
                        track->UtcTime.tm_sec = atoi(timeString.substr(17, 4).c_str());

                        state = FileReadState::LookingForName;
                    }
                }
                break;
                
            case FileReadState::LookingForName:
                {
                    size_t  start = line.find("<name>");
                    size_t  end = line.find("</name>");
                    if (start != string::npos && end != string::npos)
                    {
                        track->Name = line.substr(start + 6, end - 8);
                        state = FileReadState::ReadingTrack;
                    }
                }
                break;
                
            case FileReadState::ReadingTrack:
                {
                    size_t trkptStart = line.find("<trkpt ");
                    size_t trkptStop = line.find("</trkpt>");
                    size_t latStart = line.find("lat=\"");
                    size_t lonStart = line.find("lon=\"");

                    size_t eleStart = line.find("<ele>");
                    size_t eleStop = line.find("</ele>");
                    size_t timeStart = line.find("<time>");
                    size_t timeStop = line.find("</time>");
                    size_t hrStart = line.find("<gpxtpx:hr>");
                    size_t hrStop = line.find("</gpxtpx:hr>");

                    if (trkptStart != string::npos)
                    {
                        point = Point();
                    }

                    if (latStart != string::npos)
                    {
                        latStart += 5;
                        size_t latStop = line.find('"', latStart);
                        point.Latitude = atof(line.substr(latStart, latStop - latStart).c_str());
                    }

                    if (lonStart != string::npos)
                    {
                        lonStart += 5;
                        size_t lonStop = line.find('"', lonStart);
                        point.Longitude = atof(line.substr(lonStart, lonStop - lonStart).c_str());
                    }


                    if (eleStart != string::npos && eleStop != string::npos)
                    {
                        eleStart += 5;
                        point.Elevation = atof(line.substr(eleStart, eleStop - eleStart).c_str());
                    }

                    if (timeStart != string::npos && timeStop != string::npos)
                    {
                        string timeString = line.substr(timeStart + 6, timeStop - 10);
                        if (timeString.length() < 19)
                        {
                            throw AnalyserException("File time element too short");
                        }

                        point.UtcTime.tm_year = atoi(timeString.substr(0, 4).c_str());
                        point.UtcTime.tm_mon = atoi(timeString.substr(5, 2).c_str()) - 1;
                        point.UtcTime.tm_mday = atoi(timeString.substr(8, 2).c_str());
                        point.UtcTime.tm_hour = atoi(timeString.substr(11, 2).c_str());
                        point.UtcTime.tm_min = atoi(timeString.substr(14, 2).c_str());
                        point.UtcTime.tm_sec = atoi(timeString.substr(17, 4).c_str());
                    }

                    if (hrStart != string::npos && hrStop != string::npos)
                    {
                        hrStart += 11;
                        point.HeartRate = atoi(line.substr(hrStart, hrStop - hrStart).c_str());
                    }

                    if (trkptStop != string::npos && trkptStart == string::npos)
                    {
                        track->Points.push_back(point);
                    }
                }
                break;
        }
    }


    
    stream.close();
    
    return track;
}

}
