#include "menu.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    /*
    Music collection;

    for (int i=0; i<3; i++)
    {
        collection.Fill();
    }
    collection.PrintSongs();
    cout<<endl;

    collection.DeleteSongs(1);
    collection.PrintSongs();
    cout<<endl;
    collection.EditSong_name(2);
    collection.EditSong_artist(2);
    collection.EditSong_date(2);
    collection.PrintSongs();

    ofstream f;
    f.open("Music.txt");
    collection.Save(f);
    */
    Menu* menu = new Menu;
    menu->MainMenu();

    return 0;
}

