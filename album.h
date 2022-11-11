#pragma once
#ifndef ALBUM_H_INCLUDED
#define ALBUM_H_INCLUDED
#pragma once
#include "music.h"

class Album :public Music
{
private:
    string album_name;
    string songwriter;
    int release_date = 0;
    bool is_awarded;
public:
    //sets
    void SetAlbumName(string name);
    void SetReleaseDate(int date);
    void SetSongwriter(string artist);
    void SetIsAwarded(int awarded);
    //gets
    virtual string GetColName();
    int GetReleaseDate();
    string GetSongwriter();
    bool GetIsAwarded();
    vector<string> FeaturingArtists(); //другие участники альбома (кроме исполнителя)

    virtual void Fill(vector<Song*> songs);
    vector<Song*> AuthorSongs(vector<Song*> songs, string author); //функция для получения песен конкретного автора
    virtual void Save(ofstream& f);
    virtual void Load(vector <string> x);
    vector<Song*> ChangeOrder(); //меняет порядок песен в альбоме
};

#endif // ALBUM_H_INCLUDED

