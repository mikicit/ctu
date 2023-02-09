#include "trie.hpp"

#include <algorithm>
#include <cassert>
#include <memory>

// Util
trie_node* next(const trie_node* node, char index) {
    for (const auto& n : node->children) {
        if (!n || n->payload <= index) continue;
        if (n->is_terminal) return n;

        return next(n, -1);
    }

    if (node->parent) {
        return next(node->parent, node->payload);
    }

    return nullptr;
};

void rec_delete(trie_node* node) {
    if (!node) return;
    for (const auto& n : node->children) {
        if (n) {
            rec_delete(n);
        }
    }

    delete node;
}

// stage 1

// constructors
trie::trie() {
    m_root = new trie_node;
}

trie::trie(const std::vector<std::string> &strings) {
    m_root = new trie_node;

    for (const auto& word : strings) {
        insert(word);
    }
}

// copy constructors and methods
trie::trie(const trie &rhs) {
    this->~trie();
    m_root = new trie_node;
    m_size = 0;

    for (auto &&rh : rhs) {
        insert(rh);
    }
}

trie &trie::operator=(const trie &rhs) {
    if (this == &rhs) {
        return *this;
    }

    this->~trie();
    m_root = new trie_node;
    m_size = 0;

    for (auto &&rh : rhs) {
        insert(rh);
    }

    return *this;
}

// move constructors and methods
trie::trie(trie &&rhs) {
    this->~trie();
    m_root = rhs.m_root;
    m_size = rhs.m_size;
    rhs.m_root = new trie_node;
    rhs.m_size = 0;
}

trie &trie::operator=(trie &&rhs) {
    if (this == &rhs) {
        return *this;
    }

    this->~trie();
    m_root = rhs.m_root;
    m_size = rhs.m_size;
    rhs.m_root = new trie_node;
    rhs.m_size = 0;

    return *this;
}

// destructor
trie::~trie() {
    rec_delete(m_root);
}

// base methods
bool trie::erase(const std::string &str) {
    const char* sptr = str.c_str();
    trie_node* current_node = m_root;

    while (*sptr) {
        if (!current_node->children[*sptr]) {
            return false;
        }

        current_node = current_node->children[*sptr];
        sptr++;
    }

    if (!current_node->is_terminal) return false;

    m_size--;
    current_node->is_terminal = false;

    bool is_leaf = true;

    for (const auto& i : current_node->children) {
        if (i != nullptr) {
            is_leaf = false;
            break;
        }
    }

    if (is_leaf) {
        trie_node* parent = current_node->parent;

        while (parent) {
            parent->children[current_node->payload] = nullptr;
            delete current_node;

            if (parent->is_terminal) break;
            current_node = parent;
            parent = parent->parent;
        }
    }

    return true;
}

bool trie::insert(const std::string &str) {
    const char* sptr = str.c_str();
    trie_node* current_node = m_root;

    while (*sptr) {
        if (current_node->children[*sptr]) {
            current_node = current_node->children[*sptr];
            sptr++;
            continue;
        }

        trie_node* new_node = new trie_node;
        new_node->payload = *sptr;
        new_node->parent = current_node;
        current_node->children[*sptr] = new_node;

        current_node = new_node;

        sptr++;
    }

    if (current_node->is_terminal) {
        return false;
    }

    current_node->is_terminal = true;
    m_size++;

    return true;
}

bool trie::contains(const std::string &str) const {
    const char* sptr = str.c_str();
    trie_node* current_node = m_root;

    while (*sptr) {
        if (!current_node->children[*sptr]) {
            return false;
        }

        current_node = current_node->children[*sptr];
        sptr++;
    }

    if (!current_node->is_terminal) return false;

    return true;
}

bool trie::empty() const {
    return m_size == 0;
}

size_t trie::size() const {
    return m_size;
}

// stage 2

// Const Iterator Init

trie::const_iterator::const_iterator(const trie_node *node) {
    current_node = node;
}

trie::const_iterator &trie::const_iterator::operator++() {
    current_node = next(current_node, -1);
    return *this;
}

trie::const_iterator trie::const_iterator::operator++(int) {
    const_iterator tmp_const_iterator(*this);
    ++(*this);
    return tmp_const_iterator;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    std::string result = "";

    const trie_node* curr_s = current_node;
    while (curr_s) {
        if (curr_s->payload == 0) break;
        result = curr_s->payload + result;
        curr_s = curr_s->parent;
    }

    return result;
}

bool trie::const_iterator::operator==(const trie::const_iterator &rhs) const {
    return this->current_node == rhs.current_node;
}

bool trie::const_iterator::operator!=(const trie::const_iterator &rhs) const {
    return this->current_node != rhs.current_node;
}

trie::const_iterator trie::begin() const {
    if (m_root->is_terminal) return {m_root};
    return {next(m_root, -1)};
}

trie::const_iterator trie::end() const {
    return nullptr;
}

// Stage 4

std::vector<std::string> trie::search_by_prefix(const std::string &prefix) const {
    std::vector<std::string> result;

    for (auto&& word : *this) {
        if (word.rfind(prefix, 0) == 0) {
            result.push_back(word);
        }
    }

    return result;
}

std::vector<std::string> trie::get_prefixes(const std::string &str) const {
    std::vector<std::string> result;

    for (auto&& word : *this) {
        if (str.rfind(word, 0) == 0) {
            result.push_back(word);
        }
    }

    return result;
}

void trie::swap(trie &rhs) {
    std::swap(m_size, rhs.m_size);
    std::swap(m_root, rhs.m_root);
}

bool trie::operator==(const trie &rhs) const {
    if (m_size != rhs.m_size) return false;

    trie::const_iterator second_iterator = rhs.begin();

    for (auto &&rh : rhs) {
        if (rh != *second_iterator) return false;
        ++second_iterator;
    }

    return true;
}

bool trie::operator<(const trie &rhs) const {
    if (m_size == 0 && rhs.m_size == 0) return false;
    if (m_size == 0 && rhs.m_size > 0) return true;
    if (m_size > 0 && rhs.m_size == 0) return false;

    trie::const_iterator second_iterator = rhs.begin();

    for (auto &&rh : *this) {
        if (second_iterator == nullptr) return false;

        std::string compared = *second_iterator;

        int i;
        for (i = 0; rh[i] != '\0' || compared[i] != '\0'; i++) {
            if (rh[i] < compared[i]) {
                return true;
            } else if (rh[i] > compared[i]) {
                return false;
            }
        }

        if (rh[i] != '\0') {
            return false;
        } else if (compared[i] != '\0') {
            return true;
        }

        ++second_iterator;
    }

    if (rhs.size() > m_size) return true;

    return false;
}

bool operator!=(const trie& lhs, const trie& rhs){
    return !(lhs == rhs);
}

bool operator<=(const trie& lhs, const trie& rhs){
    return !(lhs > rhs);
}

bool operator>(const trie& lhs, const trie& rhs){
    return (rhs < lhs);
}

bool operator>=(const trie& lhs, const trie& rhs){
    return !(lhs < rhs);
}

trie trie::operator|(trie const &rhs) const {
    trie new_trie(*this);

    for (auto &&rh : rhs) {
        new_trie.insert(rh);
    }

    return new_trie;
}

int rec_union(trie_node *fnode, trie_node *snode, trie_node *parent, int count) {
    if (fnode->is_terminal && snode->is_terminal) {
        parent->is_terminal = true;
        count++;
    }

    for (const auto &i : fnode->children) {
        if ((i != nullptr) && (snode->children[i->payload] != nullptr)) {
            parent->children[i->payload] = new trie_node;
            parent->children[i->payload]->payload = i->payload;
            parent->children[i->payload]->parent = parent;

            rec_union(i, snode->children[i->payload], parent->children[i->payload], count);
        }
    }

    return count;
}

trie trie::operator&(trie const &rhs) const {
    std::unique_ptr<trie> new_trie(new trie);

// Old variant

//    for (auto &&lh : *this) {
//        if (rhs.contains(lh)) {
//            new_trie.insert(lh);
//        }
//    }

    new_trie->m_size = rec_union(m_root, rhs.m_root, new_trie->m_root, 0);

    return *new_trie;
}

std::ostream& operator<<(std::ostream& out, trie const& trie){
    return out;
}


