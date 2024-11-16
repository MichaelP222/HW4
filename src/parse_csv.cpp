// must complete parse_csv function for code to work properly with .csv files
#include <artistList.hpp>
#include <istream>
#include <iostream>
#include <sstream>

// helper function provided to parse genres WITH square brackets
static void parse_genres(std::istream & file, std::string genres[Artist::max_genres]) {
    std::string temp;

    std::getline(file, temp, '[');
    std::getline(file, temp, ']');

    auto genre_idx = 0u;
    for(auto start = 0u; start < temp.size() and genre_idx < Artist::max_genres; ){
        auto start_quote = temp.find_first_of('\'', start) + 1;
        auto end_quote = temp.find_first_of('\'', start_quote);
        
        genres[genre_idx] = temp.substr(start_quote, end_quote - start_quote);
        ++genre_idx;

        start = end_quote + 1;
    }
    
    while(genre_idx < Artist::max_genres){
        genres[genre_idx] = "";
        ++genre_idx;
    }
}

// parse_csv needs to be written by the students
ArtistList parse_csv(std::istream& file) {
    // Insert code here
    // be sure to call the provided parse_genres function to assist you
    // in reading the genres column from the spotify_daily_charts_artists.csv    
    ArtistList parsed_list;
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id;
        std::string name;
        std::string followers;
        std::string genres[Artist::max_genres];
        std::string popularity;
        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,followers,',');
        parse_genres(ss,genres);
        getline(ss,popularity,',');
        getline(ss,popularity,',');
        Artist a(id,name,std::stoi(followers),genres,std::stoi(popularity));
        parsed_list.appendArtist(a);
    }
    return parsed_list;
}