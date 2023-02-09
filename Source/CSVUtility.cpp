/*
  ==============================================================================

    CSVUtility.cpp
    Created: 8 Feb 2023 1:31:16am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "CSVUtility.h"

vector<TrackEntry>* CSVUtility::playlist;

void CSVUtility::save()
{
    fstream file;
    file.open("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Source/playlist.csv", ios::out);
    
    if (file.is_open())
    {
        String playlistString;
        
        for (TrackEntry track : *playlist)
        {
            playlistString += createLine(track) + "\n";
        }
        
        // save
        file<< playlistString;
    }
    else
        cout << "CSVUtility::save File not open!" <<endl;

    file.close();
}

vector<TrackEntry> CSVUtility::read()
{
    vector<TrackEntry> entries;
    string line;
    
    fstream file;
    file.open("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Source/playlist.csv", ios::in);
    
    if(file.is_open())
    {
        while(getline(file, line))
        {
            // push files
            entries.push_back(stringsToTrackEntry(tokenise(line, ',')));
        }
    }
    else
        cout << "CSVUtility::read File not open!" <<endl;
    
    file.close();
    
    return entries;
}

TrackEntry CSVUtility::stringsToTrackEntry(vector<string> tokens)
{
        
    TrackEntry trackEntry{
        File(tokens[2]),
        String(tokens[0]),
        String(tokens[1]),
        String(tokens[2]),
        stof(tokens[3])
    };
    return trackEntry;
    
}


String CSVUtility::createLine(TrackEntry _track)
{
    String line;
    
    line =
    _track.name+","
    +_track.extension+","
    +_track.path+","
    +String(_track.duration);
    
    return line;
}

vector<string> CSVUtility::tokenise(string csvLine, char separator)
{
   vector<string> tokens;
   int start, end;
   string token;

    start = (int) csvLine.find_first_not_of(separator, 0);
    do{
        end = (int) csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
    start = end + 1;
    }while(end > 0);
    
    return tokens;
}


