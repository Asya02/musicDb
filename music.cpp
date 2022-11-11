#include "music.h"
using namespace std;

bool AllDigits(string str)
{
    for (int i = 0; i != str.length(); i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return false;
    }
    return true;
};
Music::Music()
{
    cout << "Создан объект" << endl;
};

Music::~Music()
{
    cout << "Удалён объект" << endl;
};
//sets
void Music::SetSongs(vector<Song*> songs)
{
    song_list = songs;
}
void Song::SetSong(string name, vector<string> artists, int date)
{
    song_name = name;
    song_artists = artists;
    release_date = date;
}
//gets
vector<Song*> Music::GetSongs()
{
    return song_list;
}

int Music::GetReleaseDate(Song* song)
{
    return song ->release_date;
};

//access
Song* Music::GetOneSong(int num)
{
    return song_list[num - 1];
};
string Music::GetColName()
{
    return "Music";
}
void Music::AddSong(Song* song)
{
    song_list.push_back(song);
};
//здесь разные проверки на корректность введения даты
int Music::FillDate()
{
    string buf_date;
    cout << "Введите год релиза песни или '-', если год неизвестен: ";
    std::getline(std::cin, buf_date);
    cout << endl;
    if (buf_date == "") //в поле release_date будет 0
        return 0;
    if (buf_date == "-")
        return 0;
    while (!((AllDigits(buf_date) && std::stoi(buf_date) > 0)))
    {
        cout << "Введите дату корректно: ";
        std::getline(std::cin, buf_date);
        cout << endl;
    }
    return std::stoi(buf_date);
};

void Music::Fill()
{
    string buf_name;
    cout << "Введите название песни: ";
    std::getline(std::cin, buf_name);

    string buf_artist;
    vector<string> artists;
    cout << "Введите исполнителя(-ей) песни через enter (для окончания ввода нажмите 0): \n";
    std::getline(std::cin, buf_artist);
    while (buf_artist != "0")
    {
        artists.push_back(buf_artist);
        std::getline(std::cin, buf_artist);
    }

    int date = FillDate();
    cout << endl;
    Song* song = new Song;
    song->SetSong(buf_name, artists, date);
    AddSong(song);
};
void Music::PrintSongs(vector<Song*> songs)
{
    for (int i = 0; i != songs.size(); i++)
    {
        cout << i + 1 << " " << songs[i]->song_name << " - ";
        for (int j = 0; j != songs[i]->song_artists.size(); j++)
        {
            cout << songs[i]->song_artists[j] << ", ";
        }
        cout << songs[i]->release_date << endl;
    }
};
void Music::PrintSongs()
{
    for (int i = 0; i != song_list.size(); i++)
    {
        cout << i + 1 << " " << song_list[i]->song_name << " - ";
        for (int j = 0; j != song_list[i]->song_artists.size(); j++)
        {
            cout << song_list[i]->song_artists[j] << ", ";
        }
        cout << song_list[i]->release_date << endl;
    }
};
void Music::DeleteSongs(int num)
{
    song_list.erase(song_list.begin() + num - 1);
};

void Music::PrintAllArtists(Song* song)
{
    for (int i = 0; i != song->song_artists.size(); i++)
    {
        cout << i + 1 << " " << song->song_artists[i] << endl;
    }
}
void Music::Save(ofstream& f)
{
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
};
void Music::Load(vector <string> x)
{
    if (x.size() < 6)
    {
        cout << "Некорректный элемент" << endl;
        return;
    }
    int i = 1;
    Song* song = new Song;
    song->song_name = x[i];
    i++;
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
    i++;
    song->release_date = std::stoi(x[i]);
    i++;
    if (x[i] == "</Song>")
    {
        AddSong(song);
    }
};

void Music::ClearSongs()
{
    song_list.clear();
};

/*
string Music::toString()
{
    string info="";
    for (int i=0; i!=song_list.size(); i++)
    {
        info+=song_list[i]->song_name;
        info+="\nИсполнители:\n";
        for (int j=0; j!=song_list[i]->song_artists.size(); j++) {
            info+=song_list[i]->song_artists[j];
            info+="\n";
        }
        info+="Дата релиза: ";
        info+=song_list[i]->release_date;
        info+="\n";
    }
    return info;
}
*/
