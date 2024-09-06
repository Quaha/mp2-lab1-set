#include "tbitfield.h"

#include <gtest.h>

TEST(TBitField, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, can_get_length)
{
  TBitField bf(3);

  EXPECT_EQ(3, bf.GetLength());
}

TEST(TBitField, new_bitfield_is_set_to_zero)
{
  TBitField bf(100);

  int sum = 0;
  for (int i = 0; i < bf.GetLength(); i++)
  {
    sum += bf.GetBit(i);
  }

  EXPECT_EQ(0, sum);
}

TEST(TBitField, can_set_bit)
{
  TBitField bf(10);

  EXPECT_EQ(0, bf.GetBit(3));

  bf.SetBit(3);
  EXPECT_NE(0, bf.GetBit(3));
}

TEST(TBitField, can_clear_bit)
{
  TBitField bf(10);

  int bitIdx = 3;

  bf.SetBit(bitIdx);
  EXPECT_NE(0, bf.GetBit(bitIdx));

  bf.ClrBit(bitIdx);
  EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(TBitField, throws_when_create_bitfield_with_negative_length)
{
  ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, throws_when_set_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(TBitField, throws_when_set_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.SetBit(11));
}

TEST(TBitField, throws_when_get_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(TBitField, throws_when_get_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(TBitField, throws_when_clear_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.ClrBit(-3));
}

TEST(TBitField, throws_when_clear_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.ClrBit(11));
}

TEST(TBitField, can_assign_bitfields_of_equal_size)
{
  const int size = 2;
  TBitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_NE(0, bf2.GetBit(0));
  EXPECT_NE(0, bf2.GetBit(1));
}

TEST(TBitField, assign_operator_changes_bitfield_size)
{
  const int size1 = 2, size2 = 5;
  TBitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(2, bf2.GetLength());
}

TEST(TBitField, can_assign_bitfields_of_non_equal_size)
{
  const int size1 = 2, size2 = 5;
  TBitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_NE(0, bf2.GetBit(0));
  EXPECT_NE(0, bf2.GetBit(1));
}

TEST(TBitField, compare_equal_bitfields_of_equal_size)
{
  const int size = 2;
  TBitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 0101
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 0111
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 4, size2 = 5;
  TBitField bf1(size1), bf2(size2), expBf(size2);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 01010
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 01110
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 0101
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 0001
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 4, size2 = 5;
  TBitField bf1(size1), bf2(size2), expBf(size2);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 01010
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 00010
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, can_invert_bitfield)
{
  const int size = 2;
  TBitField bf(size), negBf(size), expNegBf(size);
  // bf = 01
  bf.SetBit(1);
  negBf = ~bf;

  // expNegBf = 10
  expNegBf.SetBit(0);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, can_invert_large_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);
  bf.SetBit(35);
  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  expNegBf.ClrBit(35);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, invert_plus_and_operator_on_different_size_bitfield)
{
  const int firstSze = 4, secondSize = 8;
  TBitField firstBf(firstSze), negFirstBf(firstSze), secondBf(secondSize), testBf(secondSize);
  // firstBf = 0001
  firstBf.SetBit(0);
  negFirstBf = ~firstBf;
  // negFirstBf = 1110

  // secondBf = 00011000
  secondBf.SetBit(3);
  secondBf.SetBit(4);

  // testBf = 00001000
  testBf.SetBit(3);

  EXPECT_EQ(secondBf & negFirstBf, testBf);
}

TEST(TBitField, can_invert_many_random_bits_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);

  std::vector<int> bits;
  bits.push_back(0);
  bits.push_back(1);
  bits.push_back(14);
  bits.push_back(16);
  bits.push_back(33);
  bits.push_back(37);

  for (unsigned int i = 0; i < bits.size(); i++)
    bf.SetBit(bits[i]);

  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  for (unsigned int i = 0; i < bits.size(); i++)
    expNegBf.ClrBit(bits[i]);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, bitfields_with_different_bits_are_not_equal)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.SetBit(1);
  bf1.SetBit(3);

  bf2.SetBit(1);
  bf2.SetBit(2);

  EXPECT_NE(bf1, bf2);
}

// All tests below Created by ChatGPT3

TEST(TBitField, can_set_all_bits) {
    const int size = 10;
    TBitField bf(size);
    for (int i = 0; i < size; i++) {
        bf.SetBit(i);
    }
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(1, bf.GetBit(i));
    }
}

TEST(TBitField, can_clear_all_bits) {
    const int size = 10;
    TBitField bf(size);
    for (int i = 0; i < size; i++) {
        bf.SetBit(i);
    }
    for (int i = 0; i < size; i++) {
        bf.ClrBit(i);
    }
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(0, bf.GetBit(i));
    }
}

TEST(TBitField, can_copy_bitfield) {
    const int size = 5;
    TBitField bf1(size);
    bf1.SetBit(0);
    bf1.SetBit(3);

    TBitField bf2(bf1);

    EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, can_assign_bitfields_of_different_sizes) {
    const int size1 = 5;
    const int size2 = 10;
    TBitField bf1(size1);
    TBitField bf2(size2);

    bf1.SetBit(0);
    bf1.SetBit(4);

    bf2 = bf1;

    EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, throws_when_set_bit_with_invalid_index) {
    const int size = 5;
    TBitField bf(size);
    ASSERT_ANY_THROW(bf.SetBit(size + 1));
}

TEST(TBitField, throws_when_get_bit_with_invalid_index) {
    const int size = 5;
    TBitField bf(size);
    ASSERT_ANY_THROW(bf.GetBit(size + 1));
}

TEST(TBitField, can_create_bitfield_with_zero_size) {
    ASSERT_NO_THROW(TBitField bf(0));
}

TEST(TBitField, correct_length_after_creation) {
    const int size = 15;
    TBitField bf(size);
    EXPECT_EQ(size, bf.GetLength());
}

TEST(TBitField, can_clear_bits_in_uninitialized_bitfield) {
    const int size = 10;
    TBitField bf(size);
    for (int i = 0; i < size; i++) {
        bf.ClrBit(i);
    }
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(0, bf.GetBit(i));
    }
}

TEST(TBitField, can_assign_bitfield_to_itself) {
    const int size = 5;
    TBitField bf(size);
    bf.SetBit(2);

    ASSERT_NO_THROW(bf = bf);
    EXPECT_EQ(1, bf.GetBit(2));
}

TEST(TBitField, or_operator_with_equal_bitfields) {
    const int size = 4;
    TBitField bf1(size), bf2(size), expBf(size);

    bf1.SetBit(1);
    bf2.SetBit(1);

    expBf.SetBit(1);

    EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, and_operator_with_empty_bitfields) {
    const int size = 6;
    TBitField bf1(size), bf2(size), expBf(size);

    EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, invert_empty_bitfield) {
    const int size = 5;
    TBitField bf(size), expBf(size);

    for (int i = 0; i < size; i++) {
        expBf.SetBit(i);
    }

    EXPECT_EQ(expBf, ~bf);
}

TEST(TBitField, bitfields_of_different_sizes_are_not_equal) {
    const int size1 = 4;
    const int size2 = 8;
    TBitField bf1(size1), bf2(size2);

    EXPECT_NE(bf1, bf2);
}

TEST(TBitField, can_use_assignment_operator) {
    const int size1 = 5;
    const int size2 = 7;

    TBitField bf1(size1);
    TBitField bf2(size2);

    bf1.SetBit(2);
    bf2.SetBit(3);

    bf2 = bf1;

    EXPECT_EQ(1, bf2.GetBit(2));
    EXPECT_EQ(0, bf2.GetBit(3));
}

TEST(TBitField, and_operator_with_partial_match) {
    const int size = 8;
    TBitField bf1(size), bf2(size), expBf(size);

    bf1.SetBit(2);
    bf1.SetBit(5);

    bf2.SetBit(2);
    bf2.SetBit(7);

    expBf.SetBit(2);

    EXPECT_EQ(expBf, bf1 & bf2);
}
