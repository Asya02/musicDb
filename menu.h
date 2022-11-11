#pragma once
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "playlist.h"
#include "album.h"

//��������������� ������� ��� ��������� �����
int Compare(string s1, string s2);

class Menu
{
private:
    Music* collection; //������ ��������� �����
    vector<Playlist*> playlists; //��� �������� ����������
    vector<Album*> albums; //��� �������� ��������
    void DeleteSong();
    void EditSongInfo(Song*);
public:
    Menu();
    ~Menu();
    void MainMenu(); //����� ��������
    void AddSongToCollection(); //���������� ����� � �������� ���������
    //�������������� �����
    void EditSong_name(Song*);
    void EditSong_artist(Song*);
    void EditSong_date(Song*);

    void LoadToFile(); //���������� � ����
    void ChooseSong();
    void ClearCollection();
    void PrintAllSongs();
    void LoadFromFile(); //�������� �� �����
    void AddPlaylist(); //�������� ���������
    void PrintPlaylists();
    void ShowPlaylist(); //�������� ���������� � ��������� � ������ ������ ���������
    //�������
    void AddAlbum();
    void PrintAlbums();
    void ShowAlbum(); //�������� ���������� �� ������� � ������ ������ �������
    vector<Album*> GetAwarded(); //�������� ������ ������������ �������
    //����������
    void SortSongsByDate(vector<Song*> song_list);
    int GetReleaseDate_menu(Song* song);
    void SortSongsByName();
    //������
    void FilterByDate();
};

#endif // MENU_H_INCLUDED
