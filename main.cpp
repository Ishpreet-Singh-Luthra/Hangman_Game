#include "GameManager.cpp"

int main()
{
    GameManager game;

    int ch;
    do
    {
        system("cls");
        game.print_Title();

        cout<<endl;
        cout<<"\t1. Start the game\n";
        cout<<"\t2. View highscores\n";
        cout<<"\t3. How to play?\n";
        cout<<"\t4. Exit\n";
        cout<<"Enter your choice (1//2//3//4): ";
        cin>>ch;

        if (ch == 1)
        {
            game.Player_name_getter();
            char ch;
            do {
                game.Game_start();
                cout<<"Want to play again? (y//n): ";
                cin>>ch;
            } while (ch == 'y');
        }
        else if (ch == 2)
        {
            game.High_Scores_printed();
        }
        else if (ch == 3)
        {
            game.displayRules();
        }
        else if (ch == 4)
        {
            cout<<"Bye!"<<endl;
        }
        else
        {
            cout<<"Invalid ch, please enter a valid choice"<<endl;
        }
    } while (ch != 4);

    return 0;
}