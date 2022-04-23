#include "branched-linked-list.hpp"
#include <stdexcept>

BLL::BLL() {
    head_ = nullptr;
}

Node* BLL::PushBack(char dat) {
    Node* n = new Node(dat);
    if (head_ == nullptr) {
        head_ = n;
        return n;
    }
    Node* cur = head_;
    while (cur->next_node_ != nullptr) {
        cur = cur->next_node_;
    }
    cur->next_node_ = n;
    return n;
}

std::string BLL::ToString() const {
    std::string s;
    Node* cur = head_;
    while (cur != nullptr) {
        s += cur->data_;
        if (cur->next_bll_ != nullptr) {
            s += cur->next_bll_->ToString();
        }
        cur = cur->next_node_;
    }
    return s;
}

size_t BLL::Size() const {
    return ToString().length();
}

Node* BLL::NodeAt(size_t idx) const {
    Node* cur = head_;
    size_t count = idx;
    while (cur != nullptr) {
        if (count == 0) {
            return cur;
        }
        if (cur->next_bll_ != nullptr) {
            if (count <= cur->next_bll_->Size()) {
                return cur->next_bll_->NodeAt(count - 1);
            }
            count -= cur->next_bll_->Size();    // count > cur->next_bll_->Size()
        }
        cur = cur->next_node_;
        count--;
    }
    throw std::invalid_argument("");
}

Node* BLL::Head() const {
    return head_;
}

char BLL::GetAt(size_t idx) const {
    if (idx >= Size()) {
        throw std::invalid_argument("");
    }
    return NodeAt(idx)->data_;
}

void BLL::SetAt(size_t idx, char dat) {
    if (idx >= Size()) {
        throw std::invalid_argument("");;
    }
    Node* n = NodeAt(idx);
    n->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
    if (idx >= Size()) {
        throw std::invalid_argument("");
    }
    Node* n = NodeAt(idx);
    if (n->next_bll_ != nullptr) {
        throw std::invalid_argument("");
    }
    n->next_bll_  = list;
    if (!IsBLLAcyclic()) {
        n->next_bll_ = nullptr;
        throw std::invalid_argument("");
    }
}

bool BLL::IsBLLAcyclic() const {
    if (head_ == nullptr) {
        return true;
    }
    Node* slow = head_;
    Node* fast = NextNode(head_);
    while (slow != nullptr && fast != nullptr && NextNode(fast)!= nullptr) {
        if (fast == slow) {
            return false;
        }
        slow = NextNode(slow);
        fast = NextNode(NextNode(fast));
    }
    return true;
}

Node* BLL::NextNode(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->next_bll_ != nullptr) {
        return node->next_bll_->head_;
    }
    return node->next_node_;
}

BLL::BLL(const BLL& to_copy) {
    if (to_copy.head_ == nullptr) {
        head_ = nullptr;
        return;
    }
    Node* prev = nullptr;
    Node* copy = to_copy.head_;
    while (copy != nullptr) {
        Node* n = new Node(copy->data_);
        if (prev == nullptr) {
            head_= n;
            prev = n;
        } else {
            prev->next_node_ = n;
            prev = n;
        }
        if (copy->next_bll_ != nullptr) {
            n->next_bll_  = new BLL(*(copy->next_bll_));
        }
        copy = copy->next_node_;
    }
}

BLL& BLL::operator=(const BLL& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Node* cur = head_;
    while (head_ != nullptr) {
        Node* next = head_->next_node_;
        delete cur->next_bll_;
        delete cur;
        cur = next;
    }
    head_ = nullptr;
    if (rhs.head_ == nullptr) {
        return *this;
    }
    Node* prev = nullptr;
    Node* copy = rhs.head_;
    while (copy != nullptr) {
        Node* n = new Node(copy->data_);
        if (prev == nullptr) {
            head_= n;
            prev = n;
        } else {
            prev->next_node_ = n;
            prev = n;
        }
        if (copy->next_bll_ != nullptr) {
            n->next_bll_ = new BLL(*(copy->next_bll_));
        }
        copy = copy->next_node_;
    }
    return *this;
}

BLL::~BLL() {
    if (head_ == nullptr) {
        return;
    }
    Node* cur = head_;
    while (cur != nullptr) {
        Node* next = cur->next_node_;
        delete cur->next_bll_;
        delete cur;
        cur = next;
    }
    head_ = nullptr;
}