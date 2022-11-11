#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include <typeinfo>
#include <algorithm> //для нижнего регистра
#include <cstring>
using namespace std;

bool AllDigits(string str); //проверяет, что строка полностью состоит из цифр

struct Song
{
    string song_name;
    vector<string> song_artists;
    int release_date = 0;
    void SetSong(string name, vector<string> artists, int date);
};

class Music
{
protected:
    vector<Song*> song_list;
public:
    Music();
    ~Music();
    //sets
    void SetSongs(vector<Song*> songs);
    //gets
    Song* GetOneSong(int num);
    int GetReleaseDate(Song* song);

    virtual string GetColName(); //получить название плейлиста или альбома
    //access
    vector<Song*> GetSongs();

    void AddSong(Song* song);
    void DeleteSongs(int num);

    int FillDate(); //заполнение даты
    virtual void Fill();

    void PrintSongs();
    void PrintSongs(vector<Song*> songs);
    void PrintAllArtists(Song* song);
    //virtual string toString();

    //files
    virtual void Save(ofstream& f);
    virtual void Load(vector <string> x);

    //clears
    void ClearSongs();

};

