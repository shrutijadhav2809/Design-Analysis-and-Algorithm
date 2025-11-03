// Shruti Jadhav
// 123B1F035
// 21|07|2025


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    long watchTime; // popularity measure (minutes watched)
};

// ------------------- QuickSort Implementation -------------------
int partition(vector<Movie>& movies, int low, int high, string key) {
    // Choose pivot (last element)
    Movie pivot = movies[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition = false;

        if (key == "rating")
            condition = movies[j].imdbRating > pivot.imdbRating;
        else if (key == "year")
            condition = movies[j].releaseYear > pivot.releaseYear;
        else if (key == "popularity")
            condition = movies[j].watchTime > pivot.watchTime;

        if (condition) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return (i + 1);
}

void quickSort(vector<Movie>& movies, int low, int high, string key) {
    if (low < high) {
        int pi = partition(movies, low, high, key);
        quickSort(movies, low, pi - 1, key);
        quickSort(movies, pi + 1, high, key);
    }
}

// ------------------- Display Function -------------------
void displayMovies(const vector<Movie>& movies) {
    cout << "\nSorted Movies:\n";
    cout << "---------------------------------------------\n";
    for (const auto& m : movies) {
        cout << m.title << " | Rating: " << m.imdbRating
             << " | Year: " << m.releaseYear
             << " | WatchTime: " << m.watchTime << " mins\n";
    }
}

// ------------------- Main -------------------
int main() {
    vector<Movie> movies = {
        {"Inception", 8.8, 2010, 5000000},
        {"Interstellar", 8.6, 2014, 4800000},
        {"Oppenheimer", 8.5, 2023, 5200000},
        {"The Dark Knight", 9.0, 2008, 8000000},
        {"Dune", 8.3, 2021, 4200000},
        {"Tenet", 7.4, 2020, 3500000}
    };

    cout << "Sort movies by (rating/year/popularity): ";
    string key;
    cin >> key;

    // Validate user input
    if (key != "rating" && key != "year" && key != "popularity") {
        cout << "Invalid choice! Defaulting to rating.\n";
        key = "rating";
    }

    quickSort(movies, 0, movies.size() - 1, key);
    displayMovies(movies);

    return 0;
}
