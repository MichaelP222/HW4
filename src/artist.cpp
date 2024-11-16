// artist.cpp: function definitions file for artist.h

// place header file includes here
#include "../include/artistList.hpp"
#include <iostream>
using namespace std;

// Allocate a new artist record
Artist::Artist(const std::string & artist_id, const std::string & artist_name, int total_followers, std::string genres[Artist::max_genres], int popularity) {
  this->artist_id = artist_id;
  this->artist_name = artist_name;
  this->total_followers = total_followers;
  for (std::size_t i = 0; i < max_genres; ++i) {
        this->genres[i] = genres[i];
    }
  this->popularity = popularity;
}

// Print an artist record
void Artist::printArtist() const{
  cout << "Artist ID: " << this->artist_id << endl;
  cout << "Artist Name: " << this->artist_name << endl;
  cout << "Total Followers: " << this->total_followers << endl;
  cout << "Genres: ";
  for (std::size_t i = 0; i < max_genres; ++i) {
      if (this->genres[i] == ""){
        continue;
      }else{
        cout << this->genres[i] << ",";
      }
    }
  cout << endl;
  cout << "Popularity: " << this->popularity << endl;
}

const std::string& Artist::name() const {
  return this->artist_name;
}
const std::string& Artist::id() const {
  return this->artist_id;
}