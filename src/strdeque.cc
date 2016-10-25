#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <cassert>
#include <limits>
#include "strdeque.h"
#include "strdequeconst.h"

#ifndef NDEBUG
const bool DEBUG = true;
#else
const bool DEBUG = false;
#endif

typedef std::deque<std::string> strdeque;
typedef std::unordered_map<unsigned long, strdeque> deque_map;

static unsigned long max_u_long() {
	static const unsigned long max_u_long = std::numeric_limits<unsigned long>::max();
	return max_u_long;
}

static deque_map& all_deques() {
	static deque_map all_deques;
	return all_deques;
}

static std::string string_id_bare(unsigned long& id) {
	return (id == emptystrdeque() ? "The Empty Deque" : std::to_string(id));
}

static std::string string_id(unsigned long& id) {
	std::string bare = string_id_bare(id);
	return (id == emptystrdeque() ? bare : "deque " + bare);
}

extern unsigned long strdeque_new() {
	if(DEBUG) std::cerr << "strdeque_new()" << std::endl;
	static unsigned long next_id = 0;
	assert(next_id < max_u_long());
	deque_map all_deques = all_deques();
	all_deques.insert(std::pair<unsigned long, strdeque>(next_id, strdeque()));
	unsigned long current_id = next_id++;
	if(DEBUG) std::cerr << "strdeque_new: deque " << current_id << " created" << std::endl;
	return current_id;
}

extern void strdeque_delete(unsigned long id) {
	if(DEBUG) {
		std::string string_id_bare = string_id_bare(id);
		std::string string_id = string_id(id);
		std::cerr << "strdeque_delete(" << string_id_bare << ")" << std::endl;
	}
	if(id == emptystrdeque()) {
		if(DEBUG) std::cerr << "strdeque_delete: attempt to remove The Empty Queue" << std::endl;
		return;
	}
	deque_map::iterator found = all_deques().find(id);
	if(found == all_deques().end()) {
		if(DEBUG) std::cerr << "strdeque_delete: " << string_id << " does not exist" << std::endl;
		return;
	}
	all_deques().erase(found);
}

extern size_t strdeque_size(unsigned long id) {
	if(DEBUG) {
		std::string string_id_bare = string_id_bare(id);
		std::string string_id = string_id(id);
		std::cerr << "strdeque_size(" << string_id_bare << ")" << std::endl;
	}
	deque_map::iterator found = all_deques().find(id);
	if(found == all_deques().end()) {
		if(DEBUG) std::cerr << "strdeque_size: " << string_id << " does not exist" << std::endl;
		return 0;
	}
	size_t result = found->second.size();
	if(DEBUG) std::cerr << "strdeque_size: " << string_id << " contains " << result << " elements" << std::endl;
	return result;
}

extern void strdeque_insert_at(unsigned long id, size_t poz, const char* value) {
	if(DEBUG) {
		std::string string_id_bare = string_id_bare(id);
		std::string string_id = string_id(id);
		std::cerr << "strdeque_size(" << string_id_bare << ", " << poz << ", " << (value == NULL ? "NULL" : value) << ")" << std::endl;
	}
	if(value == NULL) {
		if(DEBUG) std::cerr << "strdeque_insert_at: attempt to insert NULL into a deque" << std::endl;
		return;
	}
	if(id == emptystrdeque()) {
		if(DEBUG) std::cerr << "strdegue_insert_at: attempt to insert into The Empty Queue" << std::endl;
		return;
	}
	deque_map::iterator found = all_deques().find(id);
	if(found == all_deques().end()) {
		if(DEBUG) std::cerr << "strdeque_size: " << string_id << " does not exist" << std::endl;
		return;
	}
	size_t deque_size = all_deques()[id].size();
	std::string string_value(value);
	if(poz >= deque_size) poz = deque_size - 1;
	if(poz == deque_size) all_deques()[id].push_back(string_value);
	else if(poz == 0) all_deques()[id].push_front(string_value);
	else all_deques()[id].insert(all_deques()[id].begin() + poz, string_value);
}