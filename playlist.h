#pragma once
#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED
#include "music.h"
#pragma once
using namespace std;

class Playlist :public Music
{
private:
    string playlist_name;
    Music* p_music;
public:
    //sets
    void SetPlaylist_name(string name);
    //gets
    string GetColName();
    virtual void Fill(vector<Song*> songs);

    //virtual string toString();
    virtual void Save(ofstream& f);
    virtual void Load(vector <string> x);
};

#endif // PLAYLIST_H_INCLUDED
