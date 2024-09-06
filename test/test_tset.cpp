#include "tset.h"

#include <gtest.h>

TEST(TSet, can_get_max_power_set)
{
  const int size = 5;
  TSet set(size);

  EXPECT_EQ(size, set.GetMaxPower());
}

TEST(TSet, can_insert_non_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.InsElem(k);

  EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, can_insert_existing_element)
{
  const int size = 5;
  const int k = 3;
  TSet set(size);
  set.InsElem(k);
  set.InsElem(k);

  EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, can_delete_non_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.DelElem(k);

  EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, can_delete_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);

  set.InsElem(k);
  EXPECT_GT(set.IsMember(k), 0);

  set.DelElem(k);
  EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, compare_two_sets_of_non_equal_sizes)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);

  EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, compare_two_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = set2 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2.InsElem(1);
  set2.InsElem(3);

  EXPECT_EQ(set1, set2);
}

TEST(TSet, compare_two_non_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  // set2 = {1, 2}
  set2.InsElem(1);
  set2.InsElem(2);

  EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, can_assign_set_of_equal_size)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_greater_size)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_less_size)
{
  const int size1 = 6, size2 = 4;
  TSet set1(size1), set2(size2);
  // set1 = {1, 3, 5}
  set1.InsElem(1);
  set1.InsElem(3);
  set1.InsElem(5);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

TEST(TSet, can_insert_non_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);
  updatedSet = set + k;

  EXPECT_NE(0, updatedSet.IsMember(k));
}

TEST(TSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  const int size = 4;
  const int k = 6;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);

  ASSERT_ANY_THROW(updatedSet = set + k);
}

TEST(TSet, can_insert_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(k);
  updatedSet = set + k;

  EXPECT_NE(0, set.IsMember(k));
}

TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;

  EXPECT_EQ(size, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;
  // expSet = {0, 1, 2, 4}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);

  EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;

  EXPECT_EQ(size2, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(6);
  set3 = set1 + set2;
  // expSet = {0, 1, 2, 4, 6}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);
  expSet.InsElem(6);

  EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 * set2;
  // expSet = {1, 2}
  expSet.InsElem(1);
  expSet.InsElem(2);

  EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 4, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(4);
  set2.InsElem(6);
  set3 = set1 * set2;
  // expSet = {1, 2, 4}
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);

  EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_negation_operator)
{
  const int size = 4;
  TSet set(size), set1(size), expSet(size);
  // set1 = {1, 3}
  set.InsElem(1);
  set.InsElem(3);
  set1 = ~set;
  // expSet = {0, 2}
  expSet.InsElem(0);
  expSet.InsElem(2);

  EXPECT_EQ(expSet, set1);
}

// Added tests

TEST(TSet, throws_when_create_set_with_negative_size) {
	ASSERT_ANY_THROW(TSet set(-3));
}

TEST(TSet, can_check_element_membership) {
	const int size = 5;
	TSet set(size);
	// set = {2}
	set.InsElem(2);

	EXPECT_EQ(1, set.IsMember(2));
}

TEST(TSet, throws_when_insert_element_out_of_range) {
	const int size = 4;
	TSet set(size);

	ASSERT_ANY_THROW(set.InsElem(5));
}

TEST(TSet, throws_when_delete_element_out_of_range) {
	const int size = 4;
	TSet set(size);

	ASSERT_ANY_THROW(set.DelElem(5));
}

TEST(TSet, can_insert_and_delete_multiple_elements) {
	const int size = 5;
	TSet set(size);

	set.InsElem(1);
	set.InsElem(3);
	set.DelElem(1);
	set.DelElem(3);

	EXPECT_EQ(0, set.IsMember(1));
	EXPECT_EQ(0, set.IsMember(3));
}

TEST(TSet, throws_when_check_membership_of_element_out_of_range) {
	const int size = 4;
	TSet set(size);

	ASSERT_ANY_THROW(set.IsMember(6));
}

TEST(TSet, can_combine_sets_using_plus_equal_operator) {
	const int size = 5;
	TSet set1(size), set2(size);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	// set2 = {0, 2}
	set2.InsElem(0);
	set2.InsElem(2);

	set1 = set1 + set2;

	EXPECT_EQ(1, set1.IsMember(0));
	EXPECT_EQ(1, set1.IsMember(1));
	EXPECT_EQ(1, set1.IsMember(2));
	EXPECT_EQ(1, set1.IsMember(3));
}

TEST(TSet, can_intersect_sets_using_multiply_equal_operator) {
	const int size = 5;
	TSet set1(size), set2(size);
	// set1 = {1, 3, 4}
	set1.InsElem(1);
	set1.InsElem(3);
	set1.InsElem(4);
	// set2 = {1, 4}
	set2.InsElem(1);
	set2.InsElem(4);

	set1 = set1 * set2;

	EXPECT_EQ(1, set1.IsMember(1));
	EXPECT_EQ(0, set1.IsMember(3));
	EXPECT_EQ(1, set1.IsMember(4));
}

TEST(TSet, can_combine_sets_of_different_sizes_using_plus_operator) {
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	// set2 = {0, 2, 6}
	set2.InsElem(0);
	set2.InsElem(2);
	set2.InsElem(6);

	TSet result = set1 + set2;

	EXPECT_EQ(1, result.IsMember(0));
	EXPECT_EQ(1, result.IsMember(1));
	EXPECT_EQ(1, result.IsMember(2));
	EXPECT_EQ(1, result.IsMember(3));
	EXPECT_EQ(1, result.IsMember(6));
}

TEST(TSet, can_intersect_sets_of_different_sizes_using_multiply_operator) {
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2);
	// set1 = {1, 3, 4}
	set1.InsElem(1);
	set1.InsElem(3);
	set1.InsElem(4);
	// set2 = {0, 1, 4, 6}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(4);
	set2.InsElem(6);

	TSet result = set1 * set2;

	EXPECT_EQ(0, result.IsMember(0));
	EXPECT_EQ(1, result.IsMember(1));
	EXPECT_EQ(0, result.IsMember(3));
	EXPECT_EQ(1, result.IsMember(4));
	EXPECT_EQ(0, result.IsMember(6));
}

TEST(TSet, can_negate_a_set) {
	const int size = 5;
	TSet set(size), expectedSet(size);
	// set = {1, 3}
	set.InsElem(1);
	set.InsElem(3);
	// expectedSet = {0, 2, 4}
	expectedSet.InsElem(0);
	expectedSet.InsElem(2);
	expectedSet.InsElem(4);

	TSet result = ~set;

	EXPECT_EQ(expectedSet, result);
}

TEST(TSet, can_insert_element_using_plus_operator_within_valid_range) {
	const int size = 5;
	const int elem = 2;
	TSet set(size);

	TSet result = set + elem;

	EXPECT_EQ(1, result.IsMember(elem));
}

TEST(TSet, can_remove_element_using_minus_operator) {
	const int size = 5;
	const int elem = 2;
	TSet set(size);
	set.InsElem(elem);

	TSet result = set - elem;

	EXPECT_EQ(0, result.IsMember(elem));
}

TEST(TSet, throws_when_removing_element_out_of_range_using_minus_operator) {
	const int size = 4;
	const int elem = 5;
	TSet set(size);

	ASSERT_ANY_THROW(set - elem);
}

