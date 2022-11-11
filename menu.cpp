#include "menu.h"

Menu::Menu()
{
    this->collection = new Music;
    cout << "���� � �������� ��������� �������." << endl;
};
Menu::~Menu()
{
    cout << "���� �������." << endl;
}
void Menu::AddSongToCollection()
{
    collection->Fill();
}
void Menu::EditSong_name(Song* song)
{
    cout << "������� ����� �������� �����: ";
    string bufstring;
    std::getline(std::cin, bufstring);
    song->song_name = bufstring;
};
void Menu::EditSong_artist(Song* song)
{
    string pos;
    string bufstring;
    if (song->song_artists.size() != 1)
    {
        collection->PrintAllArtists(song);
        cout << "������� ����� �����������, �������� ����� ���������������: ";
        std::getline(std::cin, pos);
        cout << "������� enter ��� �������� ����� ����������� ��� ������� ���������� ���:\n";
        std::getline(std::cin, bufstring);
        if (bufstring == "")
        {
            song->song_artists.erase(song->song_artists.begin() + std::stoi(pos) - 1);
        }
        else {
            song->song_artists[std::stoi(pos) - 1] = bufstring;
        }
    }
    else {
        cout << "������� ���������� ��� ����������:\n";
        std::getline(std::cin, bufstring);
        song->song_artists[0] = bufstring;
    }
};
void Menu::EditSong_date(Song* song)
{
    cout << "������� ���������� ���� ������: " << endl;
    cout << song->song_name << " - " << song->release_date << endl;
    int year = collection->FillDate();
    song->release_date = year;
}
void Menu::EditSongInfo(Song* song)
{
    cout << "���� ��� ��������������:\n";
    cout << "1.�������� �����\n2.�����������\n3.���� ������\n";
    string bufstr;
    std::getline(std::cin, bufstr);
    if (AllDigits(bufstr))
    {
        int x = std::stoi(bufstr);
        switch (x)
        {
        case 1:
            EditSong_name(song);
            break;
        case 2:
            EditSong_artist(song);
            break;
        case 3:
            EditSong_date(song);
        default:
            cout << "�������� ����� ��������" << endl;
            break;
        }
    }
    else
    {
        cout << "�������� ����� ��������" << endl;
    }
}
void Menu::ChooseSong()
{
    vector<Song*> songlist = collection->GetSongs();
    if (songlist.size() != 0)
    {
        collection->PrintSongs();
        string bufstr;
        cout << "\n�������� ����� �����: ";
        std::getline(std::cin, bufstr);
        cout << endl;
        int x = std::stoi(bufstr);
        Song* song = collection->GetOneSong(x);
        if (x > 0 && song != nullptr)
        {
            cout << "������� 0 ��� ��������������, 1 ��� ��������: ";
            std::getline(std::cin, bufstr);
            switch (std::stoi(bufstr))
            {
            case 0:
                EditSongInfo(song);
                break;
            case 1:
                collection->DeleteSongs(x);
                cout << "���� ������ �� ����������.\n";
                break;
            default:
                cout << "�������� ����� ��������" << endl;
                break;
            }
        }
        else
        {
            cout << "�������� ����� �����" << endl;
        }
    }
    else
    {
        cout << "���������� ������." << endl;
    }
}
void Menu::LoadToFile()
{
    ofstream f;
    f.open("Music.txt");
    collection->Save(f); //��������� ������� ���������
    f.close();
    ofstream f2;
    f2.open("Playlists.txt");
    for (int i = 0; i < playlists.size(); i++)
    {
        playlists[i]->Save(f2); //��������� ���������
    }
    f2.close();
    ofstream f3;
    f3.open("Albums.txt");
    for (int i = 0; i < albums.size(); i++)
    {
        albums[i]->Save(f3); //��������� ���������
    }
    f3.close();
}
void Menu::PrintAllSongs()
{
    collection->PrintSongs();
}
void Menu::PrintPlaylists()
{
    for (int i = 0; i != playlists.size(); i++) {
        cout << i + 1 << " " << playlists[i]->GetColName() << endl;
    }
}
void Menu::PrintAlbums()
{
    vector<string> others;
    for (int i = 0; i != albums.size(); i++) {
        cout << i + 1 << " " << albums[i]->GetColName() << ", ";
        cout << albums[i]->GetSongwriter() << ", " << albums[i]->GetReleaseDate() << endl;
        cout << "Featuring artists: " << endl;
        others = albums[i]->FeaturingArtists();
        for (int j = 0; j != others.size(); j++)
            cout << others[j] << endl;
        cout<<endl;
    }
}
void Menu::LoadFromFile()
{
    char bufstr[101];
    ifstream f;
    f.open("Music.txt");
    vector <string> info;
    //��� ������� ���������
    cout<<"�������� ���������..."<<endl;
    while (!f.eof())
    {
        f.getline(bufstr, 100);
        if (strcmp(bufstr, "<Song>") == 0)
        {
            info.push_back(bufstr);
            while (strcmp(bufstr, "</Song>") != 0)
            {
                f.getline(bufstr, 100);
                info.push_back(bufstr);
            }
            collection->Load(info);
            info.clear();
        }
    }
    f.close();
    //��� ����������
    ifstream f2;
    f2.open("Playlists.txt");
    info.clear();
    cout<<"�������� ����������..."<<endl;
    while (!f2.eof())
    {
        f2.getline(bufstr, 100);
        if (strcmp(bufstr, "<Playlist>") == 0)
        {
            info.push_back(bufstr);
            while (strcmp(bufstr, "</Playlist>") != 0)
            {
                f2.getline(bufstr, 100);
                info.push_back(bufstr);
            }

            Playlist* playlist = new Playlist;
            playlist->Load(info);
            info.clear();
            playlists.push_back(playlist);
        }
    }
    f2.close();
    //��� ��������
    ifstream f3;
    f3.open("Albums.txt");
    info.clear();
    cout<<"�������� ��������..."<<endl;
    while (!f3.eof())
    {
        f3.getline(bufstr, 100);
        if (strcmp(bufstr, "<Album>") == 0)
        {
            info.push_back(bufstr);
            while (strcmp(bufstr, "</Album>") != 0)
            {
                f3.getline(bufstr, 100);
                info.push_back(bufstr);
            }
            Album* album = new Album;
            album->Load(info);
            info.clear();
            albums.push_back(album);
        }
    }
};
void Menu::AddPlaylist()
{
    Playlist* playlist = new Playlist;
    playlist->Fill(collection->GetSongs());
    playlists.push_back(playlist);
}
void Menu::AddAlbum()
{
    Album* album = new Album;
    album->Fill(collection->GetSongs());
    albums.push_back(album);
}
void Menu::ShowPlaylist()
{
    PrintPlaylists();
    cout << "������� ����� ���������: " << endl;
    string bufstr;
    std::getline(std::cin, bufstr);
    int num = 0;
    if (AllDigits(bufstr))
    {
        num = std::stoi(bufstr);
        playlists[num - 1]->PrintSongs();
    }
}
void Menu::ShowAlbum()
{
    PrintAlbums();
    cout << "������� ����� �������: " << endl;
    string bufstr;
    std::getline(std::cin, bufstr);
    int num = 0;
    if (AllDigits(bufstr))
    {
        num = std::stoi(bufstr);
        albums[num - 1]->PrintSongs();
    }
}
vector<Album*> Menu::GetAwarded()
{
    vector<Album*> awarded;
    for (int i = 0; i != albums.size(); i++)
    {
        if (albums[i]->GetIsAwarded())
            awarded.push_back(albums[i]);
    }
    return awarded;
}
int Menu::GetReleaseDate_menu(Song* song)
{
    return song->release_date;
};
int Compare(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    int res = s1.compare(s2);
    return res;
}
void Menu::SortSongsByDate(vector<Song*> song_list)
{
    if (song_list.size() == 0)
    {
        cout << "������������ ������" << endl;
        return;
    }
    vector<Song*> copy_song_list;
    copy_song_list.push_back(song_list[0]);
    for (int i = 1; i < song_list.size(); i++)
    {
        int j;
        for (j = 0; j < copy_song_list.size() && GetReleaseDate_menu(song_list[i]) > GetReleaseDate_menu(copy_song_list[j]); j++);
        if (j == copy_song_list.size())
            copy_song_list.push_back(song_list[i]);
        else
            copy_song_list.insert(copy_song_list.begin() + j, song_list[i]);
    }
    collection->PrintSongs(copy_song_list);
};
void Menu::SortSongsByName()
{
    if (collection->GetSongs().size()==0) {
        cout<<"���������� ������."<<endl;
        return;
    }
    vector<Song*> song_list = collection->GetSongs();
    vector<Song*> copy_song_list;
    copy_song_list.push_back(song_list[0]);
    int j;

    for (int i=1; i<song_list.size(); i++)
    {
        for(j=0; j<copy_song_list.size() && Compare(song_list[i]->song_name, copy_song_list[j]->song_name)>=0; j++);
        if (j==copy_song_list.size())
            copy_song_list.push_back(song_list[i]);
        else
            copy_song_list.insert(copy_song_list.begin()+j, song_list[i]);
    }

    collection->PrintSongs(copy_song_list);
}

void Menu::FilterByDate()
{
    if (collection->GetSongs().size() == 0) {
        cout << "���������� ������." << endl;
        return;
    }
    vector<Song*> song_list = collection->GetSongs();
    vector<Song*> copy_song_list;
    cout << "������� 0, ���� �� ������ ������������� ����� �� ����������� ����, 1 - ���� �����: ";
    string bufstr;
    string users_date;
    std::getline(std::cin, bufstr);
    cout << "������� ����: ";
    std::getline(std::cin, users_date);
    int date_i = stoi(users_date);
    switch (std::stoi(bufstr))
    {
    case 0:
        for (int i = 0; i < song_list.size(); i++)
        {
            int a = GetReleaseDate_menu(song_list[i]);
            if (a < date_i)
            {
                copy_song_list.push_back(song_list[i]);
            }
        }
        collection->PrintSongs(copy_song_list);
        break;
    case 1:

        for (int i = 0; i < song_list.size(); i++)
        {
            int a = GetReleaseDate_menu(song_list[i]);
            if (a > date_i)
            {
                copy_song_list.push_back(song_list[i]);
            }
        }
        collection->PrintSongs(copy_song_list);
        break;
    default:
        cout << "�������� ����� ��������" << endl;
        break;
    }
}
void Menu::MainMenu()
{
    string x;
    while (true)
    {
        cout << endl;
        cout << "�������� ��������:\n" << "1.�������� ����� � ���������.\n";
        cout << "2.��������� �� � ����.\n" << "3.������������� ���������� � �����.\n";
        cout << "4.�������� ���� ������ �����.\n" << "5.��������� �� �� �����.\n";
        cout << "6.������� ��������.\n" << "7.������ ����������.\n";
        cout << "8.����������� ��������.\n" << "9.������� ������.\n";
        cout << "10.������� ������ ��������.\n" << "11.���������� ����� �������.\n";
        cout << "12.�������� ������� ���������� � �������.\n" << "13.�������� ������������ �������.\n";
        cout << "14.������� ���������� ����� �� ���� ������.\n";
        cout << "15.���������� �� �������� �����.\n" << "16. ���������� �� ���� ������.\n";
        cout << "17.�����.\n\n";
        std::getline(std::cin, x);
        cout << endl;
        switch (std::stoi(x))
        {
        case 1:AddSongToCollection();
            break;
        case 2:LoadToFile();
            break;
        case 3:ChooseSong();
            break;
        case 4:PrintAllSongs();
            break;
        case 5:LoadFromFile();
            break;
        case 6:AddPlaylist();
            break;
        case 7:PrintPlaylists();
            break;
        case 8:ShowPlaylist();
            break;
        case 9:AddAlbum();
            break;
        case 10:PrintAlbums();
            break;
        case 11:ShowAlbum();
            break;
        case 12:
        {
            PrintAlbums();
            cout << "������� ����� �������: " << endl;
            string bufstr;
            std::getline(std::cin, bufstr);
            int num = 0;
            if (AllDigits(bufstr))
            {
                num = std::stoi(bufstr);
                albums[num - 1]->ChangeOrder();
            }
            break;
        }
        case 13:
        {
            vector<Album*> als = GetAwarded();
            for (int i = 0; i != als.size(); i++)
            {
                cout << als[i]->GetColName() << ", " << als[i]->GetSongwriter() << ", " << als[i]->GetReleaseDate() << endl;
            }
            break;
        }
        case 14:
        {
            vector<Song*> song_list = collection->GetSongs();
            //for (int i = 0; i != song_list.size(); i++) {
            //    cout << song_list[i] << endl;
            //}
            SortSongsByDate(song_list);
            break;
        }
        case 15:SortSongsByName();
            break;
        case 16: FilterByDate();
            break;
        case 17: return;
        default: cout << "�������� ����� ��������" << endl;
            break;
        }
    }
};
