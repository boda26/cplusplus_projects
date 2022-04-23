#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
    Node* cur = head_;
    Node* next = nullptr;
    while (cur != nullptr) {
        next = cur->next;
        delete cur;
        cur = next;
    }
    head_ = tail_ = nullptr;
}

Node* DNAstrand::Head() const {
    return head_;
}

void DNAstrand::PushBack(char data) {
    Node* n = new Node(data);
    if (head_ == nullptr) {
        head_ = tail_ = n;
    } else {
        tail_->next = n;
        tail_ = n;
    }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (pattern[0] == '\0' || to_splice_in.head_ == nullptr || this == &to_splice_in) {return;}
    bool find = false;
    Node* store_prev = nullptr;
    Node* store_start = nullptr;
    Node* store_end = nullptr;
    int pattern_len = 0;
    while (pattern[pattern_len] != '\0') {pattern_len++;}
    Node* cur = head_;
    int count = 0;
    Node* start_prev = nullptr;
    Node* start_same_part = nullptr;
    Node* prev = nullptr;
    while (cur != nullptr) {
        if (cur->data != pattern[count]) {count = 0;start_same_part = nullptr;start_prev = nullptr;
            if (cur->data == pattern[count]) {start_prev = prev;start_same_part = cur;count++;}
        } else {
            if (count == 0) {start_prev = prev;start_same_part = cur;}
            count++;
            if (count == pattern_len) {find = true;store_prev = start_prev;store_start = start_same_part;store_end = cur;count = 0;start_same_part = nullptr;start_prev = nullptr;}
        }prev = cur;cur = cur->next;
    }
    if (!find) {throw std::invalid_argument("Can not find pattern!");} 
    if (store_prev == nullptr) {head_ = to_splice_in.head_;
    } else {store_prev->next = to_splice_in.head_;}
    Node* next = store_end->next;
    store_end->next = nullptr;
    to_splice_in.tail_->next = next;
    if (next == nullptr) {tail_ = to_splice_in.tail_;}
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
    int a = 0;
    while (store_start != nullptr) {
        a++;
        Node* next = store_start->next;
        delete store_start;
        store_start = next;
    }
}