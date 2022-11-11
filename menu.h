#pragma once
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "playlist.h"
#include "album.h"

//вспомогательная функция для сравнения строк
int Compare(string s1, string s2);

class Menu
{
private:
    Music* collection; //полная коллекция песен
    vector<Playlist*> playlists; //для хранения плейлистов
    vector<Album*> albums; //для хранения альбомов
    void DeleteSong();
    void EditSongInfo(Song*);
public:
    Menu();
    ~Menu();
    void MainMenu(); //выбор операций
    void AddSongToCollection(); //добавление песни в основную коллекцию
    //редактирование полей
    void EditSong_name(Song*);
    void EditSong_artist(Song*);
    void EditSong_date(Song*);

    void LoadToFile(); //сохранение в файл
    void ChooseSong();
    void ClearCollection();
    void PrintAllSongs();
    void LoadFromFile(); //выгрузка из файла
    void AddPlaylist(); //создание плейлиста
    void PrintPlaylists();
    void ShowPlaylist(); //показать информацию о плейлисте и список треков плейлиста
    //альбомы
    void AddAlbum();
    void PrintAlbums();
    void ShowAlbum(); //показать информацию об альбоме и список треков альбома
    vector<Album*> GetAwarded(); //получить только награжденные альбомы
    //сортировки
    void SortSongsByDate(vector<Song*> song_list);
    int GetReleaseDate_menu(Song* song);
    void SortSongsByName();
    //фильтр
    void FilterByDate();
};

#endif // MENU_H_INCLUDED
