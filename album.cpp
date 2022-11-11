#include "album.h"
using namespace std;

void Album::SetAlbumName(string name)
{
    album_name = name;
}
void Album::SetReleaseDate(int date)
{
    release_date = date;
}
void Album::SetSongwriter(string artist)
{
    songwriter = artist;
}
void Album::SetIsAwarded(int awarded)
{
    if (awarded == 0)
        is_awarded = false;
    else
        is_awarded = true;
}
string Album::GetColName()
{
    return album_name;
}
int Album::GetReleaseDate()
{
    return release_date;
}
string Album::GetSongwriter()
{
    return songwriter;
}
bool Album::GetIsAwarded()
{
    return is_awarded;
}
vector<Song*> Album::AuthorSongs(vector<Song*> songs, string author)
{
    vector<Song*> author_songs;
    for (int i = 0; i != songs.size(); i++)
    {
        for (int j = 0; j != songs[i]->song_artists.size(); j++)
        {
            if (author == songs[i]->song_artists[j]) {
                author_songs.push_back(songs[i]);
                break;
            }
        }
    }
    return author_songs;
}
void Album::Fill(vector<Song*> songs)
{
    cout << "Создание альбома" << endl;
    cout << "Введите название альбома: " << endl;
    string bufstr;
    std::getline(std::cin, bufstr);
    SetAlbumName(bufstr);
    cout << "Введите дату релиза альбома: ";
    std::getline(std::cin, bufstr);
    SetReleaseDate(std::stoi(bufstr));
    cout << "Введите автора альбома: ";
    std::getline(std::cin, bufstr);
    SetSongwriter(bufstr);
    vector<Song*> songs2 = AuthorSongs(songs, bufstr);
    if (songs2.size()==0) {
        cout<<"В вашей библиотеке нет треков такого исполнителя."<<endl;
        return;
    }
    PrintSongs(songs2);
    cout << "Наличие наград (0 - нет, 1 - есть): ";
    std::getline(std::cin, bufstr);
    SetIsAwarded(std::stoi(bufstr));
    cout << "Введите id песен (через enter):\n";
    cout << "(для окончания ввода нажмите 0)\n";
    int i = 1; //счетчик для заполнения номера песни
    cout << i << " песня: ";
    std::getline(std::cin, bufstr);
    int num = 0;
    while (bufstr != "0")
    {
        if (AllDigits(bufstr))
            num = std::stoi(bufstr);

        if (num <= songs.size())
        {
            AddSong(songs2[num - 1]);
            i++;
        }
        else {
            cout << "Некорректный id. Треки выбираются из существующей коллекции" << endl;
            return;
        }
        cout << i << " песня: ";
        std::getline(std::cin, bufstr);
    }
}
void Album::Save(ofstream& f)
{
    f << "<Album>" << endl;
    f << album_name << endl;
    f << songwriter << endl;
    f << release_date << endl;
    f << is_awarded << endl;
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
    f << "</Album>" << endl;
};
void Album::Load(vector <string> x)
{
    if (x.size() < 13)
    {
        cout << "Некорректный элемент." << endl;
        return;
    }
    int i = 1; //albumname
    SetAlbumName(x[i]);
    i++; //author
    SetSongwriter(x[i]);
    i++;
    if (AllDigits(x[i])) {
        if (std::stoi(x[i]) > 0)
            SetReleaseDate(std::stoi(x[i]));
    }
    i++; //is_awarded
    SetIsAwarded(std::stoi(x[i]));
    i++;
    while (x[i] != "</Album>") {
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
            i++; //<Song> или </Album>
        }
        else {
            cout << "Некорректный элемент." << endl;
            return;
        }
    }
}
vector<string> Album::FeaturingArtists()
{
    vector<string> others;
    for (int i = 0; i != song_list.size(); i++)
    {
        for (int j = 0; j != song_list[i]->song_artists.size(); j++)
        {
            if (song_list[i]->song_artists[j] != songwriter)
                others.push_back(song_list[i]->song_artists[j]);
        }
    }
    return others;
}
vector<Song*> Album::ChangeOrder()
{
    PrintSongs();
    vector<Song*> songs_copy;
    cout << "Номер песни, которую нужно переставить: ";
    string bufstr;
    std::getline(std::cin, bufstr);
    int pos = 0;
    if (AllDigits(bufstr))
        pos = std::stoi(bufstr) - 1;
    cout << "Введите номер новой позиции: ";
    std::getline(std::cin, bufstr);
    int new_pos = 0;
    if (AllDigits(bufstr))
    {
        new_pos = std::stoi(bufstr) - 1;
        Song* song = song_list[pos];
        cout << song->song_name << endl;
        song_list.erase(song_list.begin() + pos);
        for (int i = 0; i != song_list.size(); i++)
            cout << song_list[i]->song_name << endl;
        songs_copy = song_list;
        songs_copy.insert(songs_copy.begin() + new_pos, song);
        for (int i = 0; i != songs_copy.size(); i++)
            cout << songs_copy[i]->song_name << endl;
        SetSongs(songs_copy);
    }
    return songs_copy;
}
