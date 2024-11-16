// artistList.cpp: function definitions for prototypes for artistList.h header file
// place header includes here
#include "../include/artistList.hpp"
#include <iostream>

ArtistList::ArtistEntry::ArtistEntry(ArtistList* list, const Artist& a) {
  this->list = list;
  this->next = nullptr;
  this->prev = nullptr;
  this->artist = a;
}

// Allocate a new artist list
ArtistList::ArtistList() {
  this->length = 0;
  this->first = nullptr;
  this->last = nullptr;
}

std::size_t ArtistList::size() const {
  return this->length;
}

bool ArtistList::is_empty() const {
  return this->size() == 0;
}

ArtistList::ArtistList(const ArtistList & list) {
  this->length = 0;
  this->first = nullptr;
  this->last = nullptr;

  if (list.first != nullptr){
    ArtistEntry* current = list.first;
    
    while (current != nullptr) {
      this->appendArtist(current->artist);
      current = current->next;
    }
  }
}

// Delete a artist list (and all entries)
ArtistList::~ArtistList() noexcept {
  while (!is_empty()) {
    removeLastArtist();
  }
}

// prepend an artist at the beginning of list
void ArtistList::prependArtist(const Artist& a) {
  ArtistEntry *tmp = new ArtistEntry(this, a);

  if (is_empty()){
    first = last = tmp;
  } else {
    tmp->next = first;
    first->prev = tmp;
    first = tmp;
    tmp = nullptr;
  }
  length++;
}

// append an artist to the end of the list
void ArtistList::appendArtist(const Artist& a) {
  ArtistEntry *tmp = new ArtistEntry(this, a);

  if (is_empty()){
    first = last = tmp;
  } else {
    tmp->prev = last;
    last->next = tmp;
    last = tmp;
    tmp = nullptr;
  }
  length++;
}

// remove the first artist from the list
void ArtistList::removeFirstArtist() {
  if (is_empty()){
    return;
  }

  ArtistEntry* tmp = this->first;
  if (this->size() == 1) {
    this->first = nullptr;
    this->last = nullptr;
  } else {
    this->first = tmp->next;
    this->first->prev = nullptr;
  }
  this->length--;
  delete tmp;
}

// remove last artist from the list
void ArtistList::removeLastArtist() {
  if (is_empty()){
    return;
  }

  ArtistEntry* tmp = this->last;
  if (this->size() == 1) {
    this->first = nullptr;
    this->last = nullptr;
  } else {
    this->last = tmp->prev;
    this->last->next = nullptr;
  }
  this->length--;
  delete tmp;
}

// print an artist list
void ArtistList::printArtistList() const {
  if (is_empty()){
    return;
  }
  
  ArtistEntry* tmp = this->first;
  do{
    tmp->artist.printArtist();
    tmp = tmp->next;
  } while (tmp != nullptr);
}

// find an artist by name in an unsorted list
Artist *ArtistList::findArtistName(const std::string& name) const {
  if (is_empty()){
    return nullptr;
  }
  
  ArtistEntry* tmp = this->first;
  while (tmp != nullptr){
    if (tmp->artist.name() == name){
      return &(tmp->artist);
    }
    tmp = tmp->next;
  }
  return nullptr;
}

// remove artist by name in an unsorted list
void ArtistList::removeArtistbyName(const std::string & name) {
  if (is_empty()){
    return;
  }
  
  ArtistEntry* tmp = this->first;
  while (tmp != nullptr){
    if (tmp->artist.name() == name){
      if (tmp == this->first){
        removeFirstArtist();
      } else if (tmp == this->last){
        removeLastArtist();
      } else {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        this->length--;
        delete tmp;
      }
      return;
    }
    tmp = tmp->next;
  }
  tmp = nullptr;
}

void ArtistList::insertArtistAt(std::size_t index, const Artist& artist) {
  if (index > this->size()){
    return;
  }

  if (index == 0){
    this->prependArtist(artist);
    return;
  }

  if (index == (this->size())){
    this->appendArtist(artist);
    return;
  }

  ArtistEntry* finder = this->first;
  for (std::size_t i = 0; i < index; i++){
    finder = finder->next;
  }

  ArtistEntry* tmp = new ArtistEntry(this, artist);
  finder->prev->next = tmp;
  tmp->prev = finder->prev;
  tmp->next = finder;
  finder->prev = tmp;
  this->length++;
}

Artist * ArtistList::at(size_t index) {
  if (index >= this->size()){
    return nullptr;
  }

  if (index == 0){
    this->firstArtist();
  }

  if (index == (this->size() - 1)){
    this->lastArtist();
  }

  ArtistEntry* tmp = this->first;
  for (std::size_t i = 0; i < index; i++){
    tmp = tmp->next;
  }
  return &(tmp->artist);
}

const Artist * ArtistList::at(size_t index) const {
  if (index >= this->size()){
    return nullptr;
  }

  if (index == 0){
    this->firstArtist();
  }

  if (index == (this->size() - 1)){
    this->lastArtist();
  }

  const ArtistEntry* tmp = this->first;
  for (std::size_t i = 0; i < index; i++){
    tmp = tmp->next;
  }
  return &(tmp->artist);
}

Artist* ArtistList::firstArtist() {
  return this->first ? &(this->first->artist) : nullptr;
}

const Artist* ArtistList::  firstArtist() const {
  return this->first ? &(this->first->artist) : nullptr;
}

Artist* ArtistList:: lastArtist() {
  return this->last ? &(this->last->artist) : nullptr;
}

const Artist* ArtistList:: lastArtist() const {
  return this->last ? &(this->last->artist) : nullptr;
}
