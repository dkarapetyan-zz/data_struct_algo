#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <iterator>
#include <cassert>

using std::vector;
using std::list;
using std::pair;
using std::string;
using std::move;
typedef list<pair<string, string> > list_of_pairs;
typedef vector<list_of_pairs> hash_table;

const int HASHSIZE = 1000;

class dictionary {

private:
    hash_table __hash_table;

public:
    dictionary();

    ~dictionary();

    void insert_entry(pair<string, string>);

    void delete_entry(string);

    list_of_pairs::iterator &&search_entry(const string &);

    void print_entries();

    unsigned hash(const string &);


};

dictionary::dictionary() : __hash_table(HASHSIZE) { };

dictionary::~dictionary() { };

unsigned dictionary::hash(const string &my_string) {
    auto hashval = 0;
    std::basic_string<char, ::std::__1::char_traits<char>, ::std::__1::allocator<char>>::const_iterator i;
    for (i = my_string.begin(); i != my_string.end(); i++) {

        hashval = *i + hashval;

    }
    return unsigned(hashval % HASHSIZE);


}


void dictionary::insert_entry(pair<string, string> my_pair) {
    if (__hash_table[hash(my_pair.first)].empty()) {
        __hash_table[hash(my_pair.first)].push_back(my_pair);
    }

        // search along linked list for our element
    else {
        for (auto i = __hash_table[hash(my_pair.first)].begin(); i != __hash_table[hash(my_pair.first)].end(); ++i) {
            if (i->first == my_pair.first) {
                // replace definition
                i->second = my_pair.second;
                return;
            }
        }
        // if element doesn't exist, we add it at end of linked list
        __hash_table[hash(my_pair.first)].push_back(my_pair);

    }


}


void dictionary::print_entries() {

    for (auto i = __hash_table.begin(); i != __hash_table.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            std::cout << j->first << ", " << j->second << "\n";
        }

    }
}

list_of_pairs::iterator &&dictionary::search_entry(const string &w) {
    assert(!__hash_table.empty());
    if (__hash_table[hash(w)].empty())
        return move(__hash_table[0].end());
        // search along linked list at hash(w) element in table
    else {
        for (auto i = __hash_table[hash(w)].begin(); i != __hash_table[hash(w)].end(); ++i) {
            if (i->first == w)
                return move(i);
        }
        return move(__hash_table[0].end());
    }
}

void dictionary::delete_entry(string w) {
    assert(!__hash_table.empty());
    // search along linked list at hash(w) element in table
    if (!__hash_table[hash(w)].empty()) {
        for (auto i = __hash_table[hash(w)].begin(); i != __hash_table[hash(w)].end(); ++i) {
            if (i->first == w)
                __hash_table[hash(w)].erase(i);
        }
    }
}

