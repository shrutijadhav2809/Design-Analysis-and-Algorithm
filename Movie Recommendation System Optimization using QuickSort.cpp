Code(c++):

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a movie
struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    int watchTimePopularity; // e.g., number of views or minutes watched
};

// Function to print the movie list
void printMovies(const vector<Movie>& movies) {
    for (const auto& movie : movies) {
        cout << "Title: " << movie.title
             << ", IMDB: " << movie.imdbRating
             << ", Year: " << movie.releaseYear
             << ", Popularity: " << movie.watchTimePopularity << endl;
    }
}

// Swap helper function
void swap(Movie &a, Movie &b) {
    Movie temp = a;
    a = b;
    b = temp;
}
// Partition function for Quicksort
int partition(vector<Movie>& movies, int low, int high, int sortField) {
    Movie pivot = movies[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        bool condition = false;
        // Sorting based on selected field
        switch(sortField) {
            case 1: // IMDB Rating
                condition = movies[j].imdbRating >= pivot.imdbRating;
                break;
            case 2: // Release Year
                condition = movies[j].releaseYear >= pivot.releaseYear;
                break;
            case 3: // Watch Time Popularity
                condition = movies[j].watchTimePopularity >= pivot.watchTimePopularity;
                break;
            default:
                condition = movies[j].imdbRating >= pivot.imdbRating;
        }
        if (condition) {
            ++i;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return i + 1;
}

// Quicksort function
void quickSort(vector<Movie>& movies, int low, int high, int sortField) {
    if (low < high) {
        int pi = partition(movies, low, high, sortField);

        quickSort(movies, low, pi - 1, sortField);
        quickSort(movies, pi + 1, high, sortField);
    }
}

int main() {
    int n;
    cout << "Enter number of movies: ";
    cin >> n;
    cin.ignore();

    vector<Movie> movies(n);

    // Input movie details
    for (int i = 0; i < n; ++i) {
        cout << "Enter details for movie " << i + 1 << ":\n";
        cout << "Title: ";
        getline(cin, movies[i].title);
        cout << "IMDB Rating: ";
        cin >> movies[i].imdbRating;
        cout << "Release Year: ";
        cin >> movies[i].releaseYear;
        cout << "Watch Time Popularity: ";
        cin >> movies[i].watchTimePopularity;
        cin.ignore(); // clear newline
    }

    // Select sorting parameter
    int sortField;
    cout << "\nSort by:\n1. IMDB Rating\n2. Release Year\n3. Watch Time Popularity\nEnter choice: ";
    cin >> sortField;

    // Perform quicksort
    quickSort(movies, 0, n - 1, sortField);

    // Display sorted list
    cout << "\nSorted Movies:\n";
    printMovies(movies);

    return 0;
}

Enter number of movies: 4
Enter details for movie 1:
Title: Inception
IMDB Rating: 8.8
Release Year: 2010
Watch Time Popularity: 950

Enter details for movie 2:
Title: Interstellar
IMDB Rating: 8.6
Release Year: 2014
Watch Time Popularity: 1000

Enter details for movie 3:
Title: The Dark Knight
IMDB Rating: 9.0
Release Year: 2008
Watch Time Popularity: 1200

Enter details for movie 4:
Title: Tenet
IMDB Rating: 7.5
Release Year: 2020
Watch Time Popularity: 850

Sort by:
1. IMDB Rating
2. Release Year
3. Watch Time Popularity
Enter choice: 1

Sorted Movies:
Title: The Dark Knight, IMDB: 9, Year: 2008, Popularity: 1200
Title: Inception, IMDB: 8.8, Year: 2010, Popularity: 950
Title: Interstellar, IMDB: 8.6, Year: 2014, Popularity: 1000
Title: Tenet, IMDB: 7.5, Year: 2020, Popularity: 850
