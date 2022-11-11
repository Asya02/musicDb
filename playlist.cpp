#include "playlist.h"
using namespace std;

void Playlist::SetPlaylist_name(string name)
{
    playlist_name = name;
};
string Playlist::GetColName()
{
    return playlist_name;
}

void Playlist::Fill(vector<Song*> songs)
{
    cout << "Создание плейлиста" << endl;
    cout << "Введите название плейлиста: " << endl;
    string bufstr;
    std::getline(std::cin, bufstr);
    SetPlaylist_name(bufstr);
    PrintSongs(songs);
    cout << "Введите id песен (через enter) для добавления в плейлист:\n";
    cout << "(для окончания ввода нажмите 0)\n";
    std::getline(std::cin, bufstr);
    int num = 0;
    while (bufstr != "0")
    {
        if (AllDigits(bufstr))
            num = std::stoi(bufstr);
        if (num <= songs.size()) {
            AddSong(songs[num - 1]);
        }
        else {
            cout << "Некорректный id. Треки выбираются из существующей коллекции." << endl;
            return;
        }
        std::getline(std::cin, bufstr);
    }
};
void Playlist::Save(ofstream& f)
{
    f << "<Playlist>" << endl;
    f << playlist_name << endl;
    for (int i = 0; i != song_list.size(); i++)
    {
        f << "<Song>" << endl;
        f << song_list[i]->song_name << endl;
        f << "<Artists>" << endl;
        for (int j = 0; j != song_list[i]->song_artists.size(); j++)
        {
            f << song_list[i]->song_artists[j] << endl;
        }
        f << "</Artists>" << endl;
        f << song_list[i]->release_date << endl;
        f << "</Song>" << endl;
    }
    f << "</Playlist>" << endl;
};
void Playlist::Load(vector <string> x)
{
    if (x.size() < 9)
    {
        cout << "Некорректный элемент" << endl;
        return;
    }
    int i = 1; //playlistname
    SetPlaylist_name(x[i]);
    i++; //song
    while (x[i] != "</Playlist>") {
        Song* song = new Song;
        if (x[i] == "<Song>") {
            i++; //songname
            song->song_name = x[i];
        }
        else {
            cout << "Некорректный элемент." << endl;
            return;
        }
        i++; //<Artists>
        if (x[i] == "<Artists>")
        {
            i++;
            while (x[i] != "</Artists>") {
                song->song_artists.push_back(x[i]);
                i++;
            }
        }
        else {
            cout << "Некорректный элемент." << endl;
            return;
        }
        i++; //year
        if (AllDigits(x[i])) {
            song->release_date = std::stoi(x[i]);
        }
        else {
            cout << "Некорректный элемент." << endl;
            return;
        }
        i++;
        if (x[i] == "</Song>") {
            AddSong(song);
            i++; //<Song> или </Playlist>
        }
        else {
            cout << "Некорректный элемент." << endl;
            return;
        }
    }
};
/*
string Playlist::toString() override
{
    Music::toString()
}
*/
