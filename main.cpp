// MovieRecommendation.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Movie.h"

int main()
{
    std::vector<Movie*> movies = ReadMoviesFromFile("moviesData.csv");

    if (movies.empty())
    {
        return 1;
    }


    bool exitProgram = false;

    do
    {
    int choice = viewMenu();

    exitProgram = handleMenu(choice, movies);


    } while (!exitProgram);

    //std:: cout << movies.size() <<std:: endl; 

    for (auto movie : movies) {
        delete movie;
    }
        movies.clear();
        return 0;
}
