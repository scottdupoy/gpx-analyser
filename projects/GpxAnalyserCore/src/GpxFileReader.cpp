#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "GpxFileReader.h"
#include "AnalyserException.h"

using namespace std;

namespace GpxAnalyserCore
{

enum FileReadState
{
    LookingForTime = 0,
    LookingForName = 1,
    ReadingTrack = 2,
};

GpxFile* GpxFileReader::Read(string& filePath)
{
    cout << "Reading file: " << filePath << endl;

    // TODO: RAII stream appropriately
    ifstream stream(filePath);
    if (!stream.is_open())
    {
        throw AnalyserException("Couldn't open file");
    }
    
    string line;
    
    
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
                        string time = line.substr(start + 6, end - 8);
                        cout << "  TIME: " << time << endl;
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
                        string time = line.substr(start + 6, end - 8);
                        cout << "  NAME: " << time << endl;
                        state = FileReadState::ReadingTrack;
                    }
                }
                break;
                
            case FileReadState::ReadingTrack:
                {
                    //cout << "LINE3: " << line << endl;
                }
                break;
        }
        //
        
    }    
    
    stream.close();
    
    return NULL;
}

}
