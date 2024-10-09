#pragma once
#include <iostream>
#include <vector>
# include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <stdexcept> 
#include <cctype>

//creating Movie class
/*
* the excel file contains database for movies including:

* 1- movie name
* 2- Year
* 3- Genres
* 4- Runtime
* 5- Rating
* 6- movie poster link
* 7- writers
* 8- cast

*/


class Movie
{
    std::string movieName; 
    int year; 
    std::string genre;
    int RunTime;
    double rate; 
    std::string writers; 
    std::string summary; 
     
public:

    //declaring a constructor to take the information for the movie object 
    Movie(std::string& movieName, int year, std::string& genre, int RunTime, double rate, std::string& writres, std::string& summary);

    // declare getters
    std:: string getMovieName() const;
    int getYear() const;
    std::string getGenre() const; 
    int getRuntime() const; 
    double getRating() const;
    std::string getWriters() const;
    std::string getSummary() const;
    


    // declare setters 
    void setMovieName(const std::string& movieName);
    void setYear(int year);
    void setGenre(const std::string& genre);
    void setRuntime(int RunTime);
    void setRate(double rate);
    void setWriters(const std::string& writers);
    void setSummary(const std::string& summgary); 

    // friend function to be able to access the class private attributes 
    friend void printMovieList(const std::vector<Movie*>& movies);
};


// read movie data function declaration 
std::vector<Movie*> ReadMoviesFromFile(const std::string& filename);

//printing the movie list function declaration 
void printMovieList(const std::vector<Movie*>& movies);  

//print movie details 
void printMovieDetails(const Movie* movie);

//function to get random movie and retuuns a pointer to that movie
Movie* generateRandomMovie(const std::vector<Movie*>& movies);

//function to return top 10 movies by rating of a given year
std::vector<Movie*> GetTopRatedMoviesByYear(const std::vector<Movie*>& movies);

// function that return a movie depending on user preference on genre and year
Movie* GenerateRandomMovieByGenreAndYear(const std::vector<Movie*>& movies); 

// function to search in the vector depeending on the user choice 
std::vector<Movie*> searchMovies(const std::vector<Movie*>& movieList);

// valid year check
int get_ValidYear(); 

// functions to handle the user interface, showing the menu of options available and handling the choice of the user
int viewMenu(); 
bool handleMenu(int choice, std::vector<Movie*>& movies);