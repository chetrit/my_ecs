/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** sparse_array
*/

#include <cassert>
#include <iostream>
#include <optional>

#include "sparse_array.hpp"

template <typename Component>
std::ostream &operator<<(std::ostream &os, std::optional<Component> const &component) {
    if (component)
        os << component.value();
    else
        os << "NULL";
    return os;
}

void test_operator() {
    sparse_array<int> A;
    sparse_array<int> B;

    A.insert_at(0, 0);
    A.insert_at(1, 1);
    A.insert_at(2, 2);

    assert(A[1] == 1);
    std::cout << "[PASSED] [] operator" << std::endl;
    B = A;
    assert(B[1] == A[1]);
    std::cout << "[PASSED] = operator" << std::endl;
}

void test_begin_and_end() {
    sparse_array<int> A;
    size_t count = 0;

    A.insert_at(0, 0);
    A.insert_at(1, 1);
    A.insert_at(2, 2);

    for (auto ptr = A.begin(); ptr < A.end(); ptr++, count++) {
        // assert(ptr[count] == A[count]);
        std::cout << ptr[count] << std::endl;
        // std::cout << A[count] << std::endl;
        // std::cout << "[PASSED] Basic begin and end using iterators() #" << count << std::endl;
    }
}

void test_size() {
    sparse_array<int> A;

    A.insert_at(0, 0);
    A.insert_at(1, 1);
    A.insert_at(2, 2);

    assert(A.size() == 3);
    std::cout << "[PASSED] Basic size() #1\n";
    A.insert_at(3, 3);

    assert(A.size() == 4);
    std::cout << "[PASSED] Basic size() #2\n";
}

void test_erase() {
    sparse_array<int> A;

    A.insert_at(0, 0);
    A.insert_at(1, 1);
    A.insert_at(2, 2);

    A.erase(1);
    assert(A[1] == std::nullopt);
    std::cout << "[PASSED] Basic erased() #1\n";
}

void test_get_index() {
    sparse_array<int> A;

    A.insert_at(0, 0);
    A.insert_at(0, 50);
    A.insert_at(2, 2);

    assert(A.get_index(50) == 0);
    std::cout << "[PASSED] Basic get_index() #1\n";
}

void test_insert_at() {
    sparse_array<int> A;

    A.insert_at(0, 0);
    A.insert_at(1, 1);
    A.insert_at(2, 2);

    assert(A.get_index(1) == 1);
    std::cout << "[PASSED] Basic insert_at() #1\n";

    assert(A.get_index(2) == 2);
    std::cout << "[PASSED] Basic insert_at() #2\n";

    assert(A.get_index(0) == 0);
    std::cout << "[PASSED] Basic insert_at() #3\n";
}

void print_sparse_array(sparse_array<int> arr, std::string expected) {
    std::cout << "Expected: " << expected << " Got: { ";
    for (sparse_array<int>::value_type n : arr) {
        if (n == std::nullopt) {
            std::cout << "nullopt, ";
        } else {
            std::cout << n.value() << ", ";
        }
    }
    std::cout << "}; \n";
}

void test_sparse_array(void) {
    sparse_array<int> v;
    sparse_array<int> v2;

    v.insert_at(0, 1);
    auto &wrong_ref = v.insert_at(1, 7);
    v.insert_at(2, 3);
    v.insert_at(3, 4);
    v.erase(3);
    v.insert_at(4, 1);

    // v2 = v;

    print_sparse_array(v, "(1, 7, 3, nullopt, 1)");
    print_sparse_array(v2, "(1, 7, 3, nullopt, 1)");
    v.insert_at(0, 2);
    print_sparse_array(v, "(2, 7, 3, nullopt, 1)");
    print_sparse_array(v2, "(1, 7, 3, nullopt, 1)");

    v.emplace_at(8, 8);

    std::cout << "FIRSTVALV: " << v2[0].value() << " SECOND VAL: " << v2[1].value() << std::endl;
    auto &test = v[1];
    std::cout << "INDEX OF VAL B (1):" << v.get_index(test) << std::endl;
    ;

    try {
        v.get_index(wrong_ref);
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    test_insert_at();
    test_get_index();
    test_erase();
    test_size();
    // test_begin_and_end();
    test_operator();
    // test_sparse_array();
}