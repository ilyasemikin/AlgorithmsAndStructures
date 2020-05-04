#include <gtest/gtest.h>
#include "list.hpp"
#include "singly_linked_list.hpp"
#include "doubly_linked_list.hpp"

template<typename T>
void is_lists_eq(learn::list<T> *first, learn::list<T> *second) {
	ASSERT_EQ(first->count(), second->count());

	for (size_t i = 0; i < first->count(); i++)
		ASSERT_EQ(first->at(i), second->at(i));
}

template <typename T>
class list_test : public testing::Test {

};

TYPED_TEST_CASE_P(list_test);

template <typename T>
void check_lists_eq(learn::list<T> *first, learn::list<T> *second) {
	ASSERT_EQ(first->count(), second->count());

	for (size_t i = 0; i < first->count(); i++)
		ASSERT_EQ(first->get_at(i), second->get_at(i));
}

TYPED_TEST_P(list_test, empty_on_startup) {
	// Arrange
	TypeParam list;
	
	// Act
	// nothing
	
	// Assert
	EXPECT_EQ(list.count(), 0);
	ASSERT_TRUE(list.empty());
}

TYPED_TEST_P(list_test, count_not_empty) {
	// Arrange
	TypeParam list { 0, 1 };

	// Act
	// nothing
	
	// Assert
	EXPECT_EQ(list.count(), 2);
	ASSERT_FALSE(list.empty());
}

TYPED_TEST_P(list_test, push_back_2_items) {
	// Arrange
	TypeParam list;
	TypeParam expected_list { 0, 1 };

	// Act
	for (size_t i = 0; i < expected_list.count(); i++)
		list.push_back(i);

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, push_front_2_items) {
	// Arrange
	TypeParam list;
	TypeParam expected_list { 1, 0 };

	// Act
	for (size_t i = 0; i < expected_list.count(); i++)
		list.push_front(i);

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, pop_front) {
	// Arrange
	TypeParam list { 0, 1, 2 };
	TypeParam expected_list { 1, 2 };

	// Act
	list.pop_front();

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, pop_back) {
	// Arrange
	TypeParam list { 0, 1, 2 };
	TypeParam expected_list { 0, 1 };

	// Act
	list.pop_back();

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, pop_front_last) {
	// Arrange
	TypeParam list { 0 };

	// Act
	list.pop_front();

	// Assert
	EXPECT_EQ(list.count(), 0);
	ASSERT_TRUE(list.empty());
}

TYPED_TEST_P(list_test, pop_back_last) {
	// Arrange
	TypeParam list { 0 };

	// Act
	list.pop_back();

	// Assert
	EXPECT_EQ(list.count(), 0);
	ASSERT_TRUE(list.empty());
}

TYPED_TEST_P(list_test, incorrect_pop) {
	// Arrange
	TypeParam list;

	// Act
	// nothing
	
	// Assert
	EXPECT_THROW(list.pop_front(), std::logic_error);
	ASSERT_THROW(list.pop_back(), std::logic_error);
}

TYPED_TEST_P(list_test, insert_begin) {
	// Arrange
	TypeParam list { 0, 1, 2, 3 };
	TypeParam expected_list { 9, 0, 1, 2, 3 };

	// Act
	list.insert(0, 9);

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, insert_middle) {
	// Arrange
	TypeParam list { 0, 1, 2, 3 };
	TypeParam expected_list { 0, 1, 9, 2, 3 };

	// Act
	list.insert(2, 9);

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, insert_end) {
	// Arrange
	TypeParam list { 0, 1, 2, 3 };
	TypeParam expected_list { 0, 1, 2, 3, 9 };

	// Act
	list.insert(4, 9);

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, insert_incorrect) {
	// Arrange
	TypeParam list { 0, 1 };

	// Act
	// nothing
	
	// Assert
	ASSERT_THROW(list.insert(3, 6), std::logic_error);
}

TYPED_TEST_P(list_test, get_front_and_back) {
	// Arrange
	TypeParam list { 0, 1, 2 };

	// Act
	// nothing

	// Assert
	EXPECT_EQ(list.front(), 0);
	ASSERT_EQ(list.back(), 2);
}

TYPED_TEST_P(list_test, reverse_2_items) {
	// Arrange
	TypeParam list { 0, 1 };
	TypeParam expected_list { 1, 0 };

	// Act
	list.reverse();

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, reverse_items) {
	// Arrange
	TypeParam list { 0, 1, 2, 3, 4 };
	TypeParam expected_list { 4, 3, 2, 1, 0 };

	// Act
	list.reverse();

	// Assert
	check_lists_eq(&list, &expected_list);
}

TYPED_TEST_P(list_test, item_at_correct_position) {
	// Arrange
	TypeParam list;
	std::vector<int> items { 0, 1, 2, 3 };

	// Act
	for (size_t i = 0; i < items.size(); i++)
		list.push_back(i);
	
	// Assert
	ASSERT_EQ(list.count(), items.size());
	for (size_t i = 0; i < items.size(); i++)
		EXPECT_EQ(items[i], list.get_at(i));
}

TYPED_TEST_P(list_test, item_at_incorrect_position) {
	// Arrange
	TypeParam list { 0, 1 };

	// Act
	// nothing
	
	// Assert
	ASSERT_THROW(list.get_at(2), std::logic_error);
}

REGISTER_TYPED_TEST_CASE_P(
	list_test,
	empty_on_startup,
	count_not_empty,
	push_back_2_items,
	push_front_2_items,
	pop_front,
	pop_back,
	pop_front_last,
	pop_back_last,
	incorrect_pop,
	insert_begin,
	insert_middle,
	insert_end,
	insert_incorrect,
	get_front_and_back,
	reverse_2_items,
	reverse_items,
	item_at_correct_position,
	item_at_incorrect_position
);

using item_type = int;
using list_types = testing::Types<
	learn::doubly_linked_list<item_type>,
	learn::singly_linked_list<item_type>
>;

INSTANTIATE_TYPED_TEST_CASE_P(list_instantiation, list_test, list_types);

TEST(doubly_linked_list, iterator_begin_test) {
	// Arrange
	learn::doubly_linked_list<int> list { 1, 3, 5, 2 };
	std::vector<int> expected { 1, 3, 5, 2 };
	std::vector<int> values;

	// Act
	std::copy(list.begin(), list.end(), std::back_inserter(values));

	// Assert
	ASSERT_EQ(values, expected);
}

TEST(doubly_linked_list, const_iterator_begin_test) {
	// Arrange
	const learn::doubly_linked_list<int> list { 1, 3, 5, 2 };
	std::vector<int> expected { 1, 3, 5, 2 };
	std::vector<int> values;

	// Act
	std::copy(list.begin(), list.end(), std::back_inserter(values));
	
	// Assert
	ASSERT_EQ(values, expected);
}

TEST(doubly_linked_list, insert_it_begin) {
	// Arrange
	learn::doubly_linked_list<int> list { 1, 3, 5, 2 };
	std::vector<int> expected { 0, 1, 3, 5, 2 };
	std::vector<int> values;

	// Act
	list.insert(list.begin(), 0);
	std::copy(list.begin(), list.end(), std::back_inserter(values));

	// Assert
	ASSERT_EQ(values, expected);
}

TEST(doubly_linked_list, insert_it_end) {
	// Arrange
	learn::doubly_linked_list<int> list { 1, 3, 5, 2 };
	std::vector<int> expected { 1, 3, 5, 2, 0 };
	std::vector<int> values;

	// Act
	list.insert(list.end(), 0);
	std::copy(list.begin(), list.end(), std::back_inserter(values));

	// Assert
	ASSERT_EQ(values, expected);
}

TEST(doubly_linked_list, insert_it_middle) {
	// Arrange
	learn::doubly_linked_list<int> list { 1, 3, 5, 2 };
	std::vector<int> expected { 1, 3, 0, 5, 2 };
	std::vector<int> values;

	// Act
	auto it = list.begin();
	it++;
	it++;
	list.insert(it, 0);
	std::copy(list.begin(), list.end(), std::back_inserter(values));

	// Assert
	ASSERT_EQ(values, expected);
}

TEST(doubly_linked_list, at_function) {
	// Arrange
	learn::doubly_linked_list<int> list { 1, 3, 5, 2 };
	std::vector expected{ 1, 3, 5, 2 };

	// Act
	// nothing
	
	// Assert
	ASSERT_EQ(list.count(), expected.size());
	for (size_t i = 0; i < expected.size(); i++)
		ASSERT_EQ(*list.at(i), expected[i]);
	ASSERT_THROW(list.at(4), std::logic_error);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
