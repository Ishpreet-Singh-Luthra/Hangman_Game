#include "GameManager.h"

GameManager::GameManager(): MAX_TRIES(5)
{
    words[0] = "india";
	words[1] = "pakistan";
	words[2] = "nepal";
	words[3] = "malaysia";
	words[4] = "philippines";
	words[5] = "australia";
	words[6] = "iran";
	words[7] = "ethiopia";
	words[8] = "oman";
	words[9] = "indonesia";

    words1[0] = "inception";
	words1[1] = "krrish";
	words1[2] = "spiderman";
	words1[3] = "batman";
	words1[4] = "avengers";
	words1[5] = "tubelight";
	words1[6] = "barfi";
	words1[7] = "bahubali";
	words1[8] = "titanic";
	words1[9] = "rockstar";

    words2[0] = "elephant";
	words2[1] = "horse";
	words2[2] = "hippopotamus";
	words2[3] = "rhinoceros";
	words2[4] = "beaver";
	words2[5] = "mouse";
	words2[6] = "monkey";
	words2[7] = "gorilla";
	words2[8] = "chimpanzee";
	words2[9] = "dog";

    words3[0] = "lamborghini";
	words3[1] = "wagonr";
	words3[2] = "bugatti";
	words3[3] = "mercedes";
	words3[4] = "bmw";
	words3[5] = "hector";
	words3[6] = "batmobile";
	words3[7] = "tesla";
	words3[8] = "santro";
	words3[9] = "creta";
    name_of_player = "default";

    // If a highscore file doesnt exist then create a new one.
    ifstream fin("scores.txt");
    if (!fin)
    {
        // This means that file doesnt exist.
        system("mkdir data");
        ofstream fout("scores.txt");
        fout.close();
    }
    fin.close();
}

void GameManager::print_Title()
{
    cout<<"\t *    *     **     **    *  *****   **   **     **     **    *"<<endl;
    cout<<"\t *    *    *  *    * *   * *        * * * *    *  *    * *   *"<<endl;
    cout<<"\t ******   ******   *  *  * *  ***** *  *  *   ******   *  *  *"<<endl;
    cout<<"\t *    *  *      *  *   * * *      * *     *  *      *  *   * *"<<endl;
    cout<<"\t *    * *        * *    **  ******  *     * *        * *    **"<<endl;

}

void GameManager::displayRules()
{
    // Display the rules and other formalities
    cout<<endl;
    cout<<"\t\t\t GAME RULES"<<endl;
    cout<<"\t\t\t-------------"<<endl;
	cout<<"Welcome to HANGMAN."<<endl;
    cout<<"You have to guess a word."<<endl;
	cout<<"Each letter is represented by a underscore."<<endl;
	cout<<"You can type one letter each try."<<endl;
	cout<< "You have "<<MAX_TRIES<<" tries to try and guess the word."<<endl;
	cout<<"-------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Press enter to continue."<<endl;
    cin.ignore();
    cin.get();
}

void GameManager::Game_start()
{
    int num_Wrong = 0, current_score = 100;  // initializing current score with 100
    // choose a word randomly from the given array.
	srand(time(NULL));
	int n = rand() % 10;
    bool valid =false;
    char cx='0';
    // choices
    cout<<"Please select the mode in which you want to play the game :\nFor Countries press 1 \nFor Movies press 2 \nFor Animals press 3 \nFor Cars press 4"<<endl;
    while (!valid){
        cin>>cx;
        if (cx=='1'){
            word= words[n];
            cout<<"Loading countries...."<<endl;
            valid=true;
        }
        else if (cx=='2'){
            word= words1[n];
            cout<<"Loading movies...."<<endl;
            valid=true;
        }
        else if (cx=='3'){
            word= words2[n];
            cout<<"Loading animals...."<<endl;
            valid=true;
        }
        else if (cx=='4'){
            word= words3[n];
            cout<<"Loading cars...."<<endl;
            valid=true;
        }
        else {
            cout<<"Invalid choice, please enter a valid choice: "<<endl;
        }
    }

    string unknown = string(word.length(), '_');

    // Loop until all guesses are used up.
    system("cls");
	while (num_Wrong < MAX_TRIES)
	{
        cout<<endl;
		cout<<unknown<<endl;
		cout<<"Guess a letter: ";
        char letter;
		cin>>letter;
		// Fill the given word with letter if it is correct, otherwise increment the number of wrong guesses.
        cout<<endl;
        int xxx= Fill_letters(letter, unknown);
        if (xxx==-1){
            cout<<"Sorry, this letter has been guessed already. Try again! "<<endl;
        }
		else if (xxx == 0)
		{
			cout<<"Whoops! Wrong guess!"<<endl;
			num_Wrong++;
            current_score -= 10;    // Deduct 10 points for a wrong guess
		}
		else
		{
			cout<<"Correct!"<<endl;
		}
		// Tell user how many guesses are left.
		cout<<"You have "<<MAX_TRIES - num_Wrong<<" guesses left."<<endl;
		// Check if the word has been guessed correctly.
		if (word == unknown)
		{
			cout<<word<<endl;
			cout<<"Congratulations! You got the word!"<<endl;
			break;
		}
	}
	if(num_Wrong == MAX_TRIES)
	{
		cout<<"\nSorry!...you've been hanged."<<endl;
		cout<<"The word was : "<<word<<endl;
        current_score -= 20;    // If player is unable to guess the word then deduct 20 more.
	}
    if (current_score < 0)
        current_score = 0;

    cout<<"You scored: "<<current_score<<endl;
    cout<<endl;
    High_Scores_Updation(current_score);    // Update the highscores in the file.
}

int GameManager::Fill_letters(char lets_guess, string &lets_guessword)
{
	int i;
	int matches = 0;
	int len = word.length();
	for (i = 0; i < len; i++)
	{
		// Was the letter guessed before?
		if (lets_guess == lets_guessword[i])
			return -1;
		// Is the guessed letter a part of the word?
		if (lets_guess == word[i])
		{
			lets_guessword[i] = lets_guess;
			matches++;
		}
	}
	return matches;
}

void GameManager::Player_name_getter()
{
    cout<<"Please enter your name: ";
    cin>>name_of_player;
}

void GameManager::High_Scores_Updation(int current_score)
{
    // Stores the top 5 high scores
    ifstream fin("scores.txt");

    priority_queue<pair<int, string>> pq;
    string name;
    int score;
    fin>>name;
    while (!fin.eof())
    {
        fin>>score;
        pq.push({ score, name});
        fin>>name;
    }
    pq.push({ current_score, name_of_player });
    fin.close();

    ofstream fout("scores.txt");
    for (int i = 0; !pq.empty() && i < 5; i++)
    {
        fout<<pq.top().second<<" "<<pq.top().first<<endl;
        pq.pop();
    }
    fout.close();
}

void GameManager::High_Scores_printed()
{
    ifstream fin("scores.txt");
    system("cls");
    cout<<"\tTOP SCORERS"<<endl;

    string n;
    int score;
    fin>>n;
    int i = 1;
    while (!fin.eof())
    {
        fin>>score;
        cout<<i<<". "<<n<<"   "<<score<<endl;
        fin>>n;
        i++;
    }
    if (i == 1)
    {
        cout<<"No entries yet."<<endl;
        cout<<"Be the first one to get your name listed!."<<endl;
    }

    cout<<"---------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Press enter to continue."<<endl;
    cin.ignore();
    cin.get();
}