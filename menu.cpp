#include "menu.h"

Menu::Menu()
{
    this->collection = new Music;
    cout << "Меню и основная коллекция созданы." << endl;
};
Menu::~Menu()
{
    cout << "Меню удалено." << endl;
}
void Menu::AddSongToCollection()
{
    collection->Fill();
}
void Menu::EditSong_name(Song* song)
{
    cout << "Введите новое название трека: ";
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
        cout << "Введите номер исполнителя, которого нужно отредактировать: ";
        std::getline(std::cin, pos);
        cout << "Нажмите enter для удаления этого исполнителя или введите правильное имя:\n";
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
        cout << "Введите правильное имя исполителя:\n";
        std::getline(std::cin, bufstring);
        song->song_artists[0] = bufstring;
    }
};
void Menu::EditSong_date(Song* song)
{
    cout << "Введите корректную дату релиза: " << endl;
    cout << song->song_name << " - " << song->release_date << endl;
    int year = collection->FillDate();
    song->release_date = year;
}
void Menu::EditSongInfo(Song* song)
{
    cout << "Поле для редактирования:\n";
    cout << "1.Название трека\n2.Исполнители\n3.Дата релиза\n";
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
            cout << "Неверный номер операции" << endl;
            break;
        }
    }
    else
    {
        cout << "Неверный номер операции" << endl;
    }
}
void Menu::ChooseSong()
{
    vector<Song*> songlist = collection->GetSongs();
    if (songlist.size() != 0)
    {
        collection->PrintSongs();
        string bufstr;
        cout << "\nВыберите номер трека: ";
        std::getline(std::cin, bufstr);
        cout << endl;
        int x = std::stoi(bufstr);
        Song* song = collection->GetOneSong(x);
        if (x > 0 && song != nullptr)
        {
            cout << "Нажмите 0 для редактирования, 1 для удаления: ";
            std::getline(std::cin, bufstr);
            switch (std::stoi(bufstr))
            {
            case 0:
                EditSongInfo(song);
                break;
            case 1:
                collection->DeleteSongs(x);
                cout << "Трек удален из библиотеки.\n";
                break;
            default:
                cout << "Неверный номер операции" << endl;
                break;
            }
        }
        else
        {
            cout << "Неверный номер трека" << endl;
        }
    }
    else
    {
        cout << "Библиотека пустая." << endl;
    }
}
void Menu::LoadToFile()
{
    ofstream f;
    f.open("Music.txt");
    collection->Save(f); //сохраняем главную коллекцию
    f.close();
    ofstream f2;
    f2.open("Playlists.txt");
    for (int i = 0; i < playlists.size(); i++)
    {
        playlists[i]->Save(f2); //сохраняем плейлисты
    }
    f2.close();
    ofstream f3;
    f3.open("Albums.txt");
    for (int i = 0; i < albums.size(); i++)
    {
        albums[i]->Save(f3); //сохраняем плейлисты
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
    //для главной коллекции
    cout<<"Загрузка коллекции..."<<endl;
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
    //для плейлистов
    ifstream f2;
    f2.open("Playlists.txt");
    info.clear();
    cout<<"Загрузка плейлистов..."<<endl;
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
    //для альбомов
    ifstream f3;
    f3.open("Albums.txt");
    info.clear();
    cout<<"Загрузка альбомов..."<<endl;
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
    cout << "Введите номер плейлиста: " << endl;
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
    cout << "Введите номер альбома: " << endl;
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
        cout << "Некорректные данные" << endl;
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
        cout<<"Библиотека пустая."<<endl;
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
        cout << "Библиотека пустая." << endl;
        return;
    }
    vector<Song*> song_list = collection->GetSongs();
    vector<Song*> copy_song_list;
    cout << "Нажмите 0, если вы хотите отфильтровать песни до определённой даты, 1 - если после: ";
    string bufstr;
    string users_date;
    std::getline(std::cin, bufstr);
    cout << "Введите дату: ";
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
        cout << "Неверный номер операции" << endl;
        break;
    }
}
void Menu::MainMenu()
{
    string x;
    while (true)
    {
        cout << endl;
        cout << "Выберите действие:\n" << "1.Добавить песню в коллекцию.\n";
        cout << "2.Сохранить БД в файл.\n" << "3.Редактировать информацию о треке.\n";
        cout << "4.Получить весь список песен.\n" << "5.Загрузить БД из файла.\n";
        cout << "6.Создать плейлист.\n" << "7.Список плейлистов.\n";
        cout << "8.Просмотреть плейлист.\n" << "9.Создать альбом.\n";
        cout << "10.Вывести список альбомов.\n" << "11.Посмотреть треки альбома.\n";
        cout << "12.Поменять порядок композиций в альбоме.\n" << "13.Получить награжденные альбомы.\n";
        cout << "14.Сделать сортировку песен по дате релиза.\n";
        cout << "15.Сортировка по названию трека.\n" << "16. Фильтрация по дате релиза.\n";
        cout << "17.Выход.\n\n";
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
            cout << "Введите номер альбома: " << endl;
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
        default: cout << "Неверный номер операции" << endl;
            break;
        }
    }
};
