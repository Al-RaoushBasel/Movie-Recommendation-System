#include "Movie.h"


// constructor
Movie::Movie(std::string& title, int year, std::string& genre, int runtime, double rate, std::string& writers, std::string &summary)
	: movieName(title), year(year), genre(genre), RunTime(runtime), rate(rate), writers(writers), summary(summary){} 


// Getters
std::string Movie::getMovieName() const {
	return movieName;
}

int Movie::getYear() const {
	return year; 
}

std::string Movie::getGenre() const {
	return genre; 
}

int Movie::getRuntime() const {
	return RunTime;
}

double Movie::getRating() const {
	return rate;
}



std::string Movie::getWriters() const {
	return writers;
}

std::string Movie::getSummary() const {
	return summary; 
}




//setters  

//void Movie::setMovieName(const std::string& name)
//{
//	movieName = name;
//}
//
//void Movie::setYear(int year)
//{
//	this->year = year;
//}
//
//void Movie::setGenre(const std::string& genre)
//{
//	this->genre = genre;
//}
//
//void Movie::setRuntime(int runTime)
//{
//	RunTime = runTime;
//}
//
//void Movie::setRate(double rate)
//{
//	this->rate = rate;
//}
//
//
//void Movie::setWriters(const std::string& writers)
//{
//	this->writers = writers;
//}
//
//
//void Movie::setSummary(const std::string& summary) {
//	this->summary = summary;
//}



std::vector<Movie*> ReadMoviesFromFile(const std::string& filename) {
    //vector to store the movie objects in it
    std::vector<Movie*> movies;

    // exception handling ( detect if the file was not opened successfully) 
    try {
        std::ifstream inFile(filename);

        if (!inFile) {
            throw std::runtime_error("Error: Unable to open file: " + filename);
        }


        std::string line;

        // skip the header line (which contains the title and rate, etc .. ) 
        std::getline(inFile, line); 

        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string movieName, genre, writers, summary;
            int year, RunTime;
            double rate;

            // as the file is csv (comma seperated values) we need to skip or ignore the commas which separate the data in the file
            std::getline(ss, movieName, ',');
            ss >> year;
            std::getline(ss.ignore(), genre, ',');
            ss >> RunTime;

            // I used the help of chatgpt to write  the line below (debug the function), because i had a problem with storing some attributes 
            ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            ss >> rate;
            std::getline(ss.ignore(), writers, ',');
            std::getline(ss.ignore(), summary);

            // allocate new movie objects
            Movie* movie = new Movie(movieName, year, genre, RunTime, rate, writers, summary);

            // Add the pointer to the vector 
            movies.push_back(movie);
        }

        // close the file
        inFile.close();
    }

    // catch if the file wasn't opened succesfully 
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // return a vector of pointers to movie objects
    return movies;
}


void printMovieList(const std::vector<Movie*>& movies) {
    // this function is to iterate through a vector that contains movies, and print all the movies details 
    std::cout << std::endl; 
    for (const auto& movie : movies) {
        std::cout << std::endl;
        std::cout << "Movie Name: " << movie->movieName << std::endl;
        std::cout << "Year: " << movie->year << std::endl;
        std::cout << "Genre: " << movie->genre << std::endl;
        std::cout << "Run Time: " << movie->RunTime<< " min" << std::endl;
        std::cout << "Rating: " << movie->rate << std::endl;
        std::cout << "Writers: " << movie->writers << std::endl;
        std::cout << "Summary: " << movie->summary << std::endl << std::endl;
    }
}


void printMovieDetails(const Movie* movie) {
    
    // this function is to print the details of one movie only, it takes a pointer to thaat movie and prints its details
    std::cout << std::endl;
    std::cout << "Title: " << movie->getMovieName() << std::endl;
    std::cout << "Year: " << movie->getYear() << std::endl;
    std::cout << "Genre: " << movie->getGenre() << std::endl;
    std::cout << "Run Time: " << movie->getRuntime() << " min" << std::endl;
    std::cout << "Rating: " << movie->getRating() << std::endl;
    std::cout << "Summary: " << movie->getSummary() << std::endl; 
}


Movie* generateRandomMovie(const std::vector<Movie*>& movies) {
    
    //srand(time(0));
    srand(static_cast<unsigned int>(time(0))); // I had warning when i used srand(time(0)), so I used stackoverflow to solve this issue, we need to cast it to unsigned int 

    // create a vector to store all movies that have rating more than 8
    std::vector<int> vec;

    //iterate through the vector passed to the function, when there is a movie rating that is higher than 8, add it to the vector (vec).
    // I chose 8 to make sure that the movie is good
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i]->getRating() > 8) {
            vec.push_back(i);
        }
    }

    //check if the vector stored the movies or not 
    if (vec.empty()) {
        return nullptr;
    }

    // generate  random number to choose one on the movies randomly from the vector

    int index = rand() % vec.size(); // i used modulo vec.size to generate a number within the vector size 
    return movies[vec[index]];  // return a random movie form the vector
}


int get_ValidYear()
{

    // because the file I found contains movies from 2000 to 2018, i need to make sure that the user enters a valid year to find matches, and i created this function to avoid code duplication
    int year;
    std::string userInput;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Enter the year: ";

        // to make sure that the user enters only numbers and not char
        try {
            std::getline(std::cin, userInput);
            year = std::stoi(userInput);

            // the excel file I used only contains movies released between 2000 ~ 2018
            if (year >= 2000 && year <= 2018) {
                validInput = true; 
                return year;
            }

            else {
                std::cout << "please choose a year between 2000 ~ 2018!" << std::endl;
            }

        }
        catch (const std::invalid_argument) {
            std::cout << "invalid! please enter a numeric year!" << std::endl;
        }
    }

    return 0;
}


std::vector<Movie*> GetTopRatedMoviesByYear(const std::vector<Movie*>& movies) {

    //vector to store the top rated movies
    std::vector<Movie*> topRatedMovies;

   
    int year = get_ValidYear();

    // iterate through the vector of movies
    for (auto movie : movies) {
        if (movie->getYear() == year) {

            // check if the movie has a higher rating than the lowest rated movie in the vector
            if (topRatedMovies.size() < 10 || movie->getRating() > topRatedMovies.back()->getRating()) {

                topRatedMovies.push_back(movie);

                // I used the help of chatgpt to learn how to sort the movies using funcion sort form library algorithm 
                std::sort(topRatedMovies.begin(), topRatedMovies.end(), [](Movie* a, Movie* b) { return a->getRating() > b->getRating(); });

                // i want to return only 10 movies so if the size of topratedmovies vector is more that 10, pop_back until it contain only 10 movies
                if (topRatedMovies.size() > 10) {
                    topRatedMovies.pop_back();
                }
            }
        }
    }

   
    return topRatedMovies;
}


Movie* GenerateRandomMovieByGenreAndYear(const std::vector<Movie*>& movies) {

    // vector of strings contains the genres 
    std::vector<std::string> genres = { "Action", "Comedy", "Drama", "Thriller", "Sci-Fi" , "Documentary", "Music", "Animation", "Sport"};

    // display genre menu
    std::cout << std::endl; 
    std::cout << "Genres: " << std::endl;
    for (int i = 0; i < genres.size(); ++i) {
        std::cout << i + 1 << ". " << genres[i] << std::endl;
    }


    // error handling for the user input
    bool valid_genre = false;
    std::string genre_input;
    int genreChoice;
    
    while (!valid_genre) {
        // no need to add throw here because stoi ( string to integer)  function will throw exception if the conversion from string to int fails then catch block will handle it
        try {
            std::cout << "Enter the number corresponding to your preferred genre: ";
            std::getline(std::cin, genre_input);
            genreChoice = std::stoi(genre_input);

            if (genreChoice >= 1 && genreChoice <= 9) {
                valid_genre = true; // if the user input is within the choices it is a valid input, the function procceds to next block
            }
            else {
                std::cout << "Invalid choice! please choose from the given options!" << std::endl<<std::endl;

            }
        }
        catch (const std::invalid_argument) {
            std::cerr << "Please enter a numeric value!" << std::endl << std::endl;
        }
    }

    int year = get_ValidYear();


    // convert genre choice to zero based index
    int genreIndex = genreChoice - 1;
    std::string selectedGenre = genres[genreIndex];

    
    // vector to store matching movies
    std::vector<Movie*> matchingMovies;

    // iterate through movies and find matches
    for (const auto& movie : movies) {
        // check if the chosed genre is in the genre of the movie 
        // string::npos indicates non-match, so if != npos means there is a match, and if the year entered equals the year of the movie, push it in the vector
        if (movie->getGenre().find(selectedGenre) != std::string::npos && movie->getYear() == year) {
            matchingMovies.push_back(movie);
        }
    }

    // Check if any matches found
    if (matchingMovies.empty()) {
        std::cout << "No movies found matching the genre and year." << std::endl;
        return nullptr;
    }

    // same way as before for chosing a random movie from a vector
    int randomIndex = rand() % matchingMovies.size();

    return matchingMovies[randomIndex];
}


std::string toLowerCase(const std::string& str)
{
    // I used stackoverflow to search how to convert a string to lowercase, I needed this fucntion to improve my searching funtion, because a lot of movies start with capital case letters
    // so when when converting the (input from the user) to lower case and converting the (movie title from the file) to lower case, I will use this function in searchByTitle function to comare 2 strings
    std::string result = str;

    // transform from <algorithm> and tolower <cctype>
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    //convert the passed string to lowercase and return it
    return result;
}

std::vector<Movie*> searchByTitle(const std::vector<Movie*>& movieList)
{
    //vector to store the search results
    std::vector<Movie*> searchResults;

    //get the tile from the user
    std::string title;
    std::cout << "Enter the movie title: ";
    std::cin.ignore(); // ignore the \n from the input
    std::getline(std::cin, title);


    std::string lower_userInput = toLowerCase(title); // use the functtion tolowercase to convert the input of the user and assign it to a new string calles lower_caseInput

    // search for movies with matching titles (not sensitive to capital or lower case)  and able to find partial matches 
    for (const auto& movie : movieList)
    {
        std::string lower_MovieTitle = toLowerCase(movie->getMovieName()); //using tolowercase to convert the movie names while searching to lowercase to be able to compare between the user input and the actual movie tiltes 

        // if there is a match, (the movie title contains the user input) add the movie to the vector "searchresults". 
        if (lower_MovieTitle.find(lower_userInput) != std::string::npos)
        {
            searchResults.push_back(movie);
        }
    }

    if (searchResults.empty()) // check if the vector is empty
    {
        std::cout << "Movie Not Found!" << std::endl; // if there is no matches print that the movie is not found
    }

    return searchResults;
}

std::vector<Movie*> searchMovies(const std::vector<Movie*>& movieList)
{
    std::vector<Movie*> searchResults;

    // ask the user for the search option
    std::cout << "What would you like to search?" << std::endl;
    std::cout << "1. Movie title" << std::endl;
    std::cout << "2. Year" << std::endl;
    std::cout << "3. Writer name" << std::endl;

    bool valid_choice = false;
    std::string userinput;
    int choice;
    
    //validate the user input
    while (!valid_choice)
    {
        try {
            std::getline(std::cin, userinput);
            choice = std::stoi(userinput); // string to int converting 

            if (choice >= 1 && choice <= 3)
                valid_choice = true; // valid input from the user
            else
            {
                std::cout << "please choose from the given options!" << std::endl <<std::endl;
                std::cout << "What would you like to search?:";
            }


        }
        //if the function stoi failed to convert the user input to int it will throw an exception and catch will catch it 
        catch (const std::invalid_argument )
        {
            std::cout << "please enter a valid choice!" << std::endl << std::endl;
            std::cout << "What would you like to search?:";
        }
    }

    //search based on the user's choice
    switch (choice)
    {
    case 1:
    {
        // using the function searchByTitle
        searchResults = searchByTitle(movieList);
        break;
    }
    case 2:
    {
        // to avoid code duplication , this function getvalidyear is created
        int year = get_ValidYear();

        // Search for movies with matching year
        for (const auto& movie : movieList)
        {
            if (movie->getYear() == year)
            {
                searchResults.push_back(movie);
            }
        }
        break;
    }
    case 3:
    {
        std::string writer;
        std::cout << "Enter the writer name: ";
        std::cin.ignore(); // ignore the newline from the  input
        std::getline(std::cin, writer);

        // search for movies with matching writer name
        for (const auto& movie : movieList)
        {
            if (movie->getWriters() == writer)
            {
                searchResults.push_back(movie);
            }
        }

        if (searchResults.empty())
        {
            std::cout << "writer: " << writer << " is not found!" << std::endl; 
        }
        break;
    }
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }

    return searchResults;
}


int viewMenu()
{
    // I chose to make this in a function not in the main to keep the main file readable and organized, and its the same way i used it Bop 1
    int choice;
    std::string userInput;
    bool validinput = false;

    //validating the user input
    while (!validinput)
    {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Generate random movie" << std::endl;
        std::cout << "2. Get top rated movies by year" << std::endl;
        std::cout << "3. Generate random movie by genre and year" << std::endl;
        std::cout << "4. Search movies" << std::endl;
        std::cout << "5. Print all movies" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        //validate user choice
        try {

            //converts the string to integer using stoi from <string> library 
            std::getline(std::cin, userInput);
            choice = std::stoi(userInput);

            if (choice >= 1 && choice <= 6)
            {
                validinput = true;
            }

            else
            {
                std::cout << "Invalid choice!" << std::endl<<std::endl;

            }
        }
        catch (const std::invalid_argument) {
            std::cout << "Invalid! please enter a number within the options available!" << std::endl<< std::endl;
        }
    }

    // return the choice of the user to pass it to handle menu function without needing to handle errors there again!
    return choice;
}


bool handleMenu(int choice, std::vector<Movie*>& movies)
{
    bool exitProgram = false;

    switch (choice) {
    case 1:
    {
        Movie* randomMovie = generateRandomMovie(movies);
        printMovieDetails(randomMovie);
        break;
    }
    case 2:
    {
        std::vector<Movie*> top10 = GetTopRatedMoviesByYear(movies);
        printMovieList(top10);
        break;

    }
    case 3:
    {
        Movie* movie = GenerateRandomMovieByGenreAndYear(movies);
        printMovieDetails(movie);
        break;

    }
    case 4: 
    {
        std::vector<Movie*> search_res = searchMovies(movies);
        printMovieList(search_res);
        break;

    }

    case 5:
        printMovieList(movies);
        break;

        
    case 6:
        return true;

    default:
        //std::cout << "Invalid choice. Please try again." << std::endl;
        break;
        
    }

    std::cout << std::endl;
    return false;
}