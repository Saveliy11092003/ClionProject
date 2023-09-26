#include <iostream>
#include <utility>
#include "gtest/gtest.h"
#include "BigInt.h"


struct StringArg {
    std::string val;
    std::string expected;

    StringArg(std::string val, std::string expected) : val(std::move(val)), expected(std::move(expected)) {}
};

struct BigIntPairArg {
    BigInt val1;
    BigInt val2;
    std::string expected;

    BigIntPairArg(const BigInt &val1, const BigInt &val2, std::string expected) :
            val1(val1), val2(val2), expected(std::move(expected)) {}
};

class BigIntAdditionMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntAdditionMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("123456"), BigInt("98765"), "222221"),
                BigIntPairArg(BigInt("-123456"), BigInt("-98765"), "-222221"),
                BigIntPairArg(BigInt("2849245756"), BigInt("-925742985729"), "-922893739973"),
                BigIntPairArg(BigInt("-2849245756"), BigInt("925742985729"), "922893739973")
        )
);

TEST_P(BigIntAdditionMYTest, assignment_addition) {
    BigIntPairArg arg = GetParam();
    arg.val1 += arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntAdditionMYTest, addition_addition) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 + arg.val2));
}

class BigIntSubtractionMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntSubtractionMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("123456"), BigInt("98765"), "24691"),
                BigIntPairArg(BigInt("-123456"), BigInt("-98765"), "-24691"),
                BigIntPairArg(BigInt("2849245756"), BigInt("925742985729"), "-922893739973"),
                BigIntPairArg(BigInt("-2849245756"), BigInt("-925742985729"), "922893739973")
        )
);

TEST_P(BigIntSubtractionMYTest, assignment_subtraction) {
    BigIntPairArg arg = GetParam();
    arg.val1 -= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

class BigIntDivisionMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntDivisionMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("43528689728"), BigInt("6175282"), "7048"),
                BigIntPairArg(BigInt("6175282"), BigInt("43528689728"), "0"),
                BigIntPairArg(BigInt("-43528689728"), BigInt("6175282"), "-7048"),
                BigIntPairArg(BigInt("6175282"), BigInt("-43528689728"), "0")
        )
);

TEST_P(BigIntDivisionMYTest, assignment_division) {
    BigIntPairArg arg = GetParam();
    arg.val1 /= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntDivisionMYTest, division) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 / arg.val2));
}

class BigIntModMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};
INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntModMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("43528689728"), BigInt("6175282"), "5302192"),
                BigIntPairArg(BigInt("6175282"), BigInt("43528689728"), "6175282"),
                BigIntPairArg(BigInt("-43528689728"), BigInt("6175282"), "-5302192"),
                BigIntPairArg(BigInt("6175282"), BigInt("-43528689728"), "6175282")
        )
);

TEST_P(BigIntModMYTest, assignment_mod) {
    BigIntPairArg arg = GetParam();
    arg.val1 %= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntModMYTest, mod) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 % arg.val2));
}

class BigIntMultiplicationMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntMultiplicationMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("123456866"), BigInt("27223"), "3360866263118"),
                BigIntPairArg(BigInt("-123456866"), BigInt("27223"), "-3360866263118"),
                BigIntPairArg(BigInt("123456866"), BigInt("-27223"), "-3360866263118"),
                BigIntPairArg(BigInt("-123456866"), BigInt("-27223"), "3360866263118")
        )
);

TEST_P(BigIntMultiplicationMYTest, assignment_multiplication) {
    BigIntPairArg arg = GetParam();
    arg.val1 *= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntMultiplicationMYTest, multiplication) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 * arg.val2));
}

TEST(bigint_test, mybitwise_not) {
    BigInt val1 = BigInt("346727846");
    BigInt val2 = BigInt("-346727847");
    ASSERT_EQ("-346727847", (std::string) ~val1);
    ASSERT_EQ("346727846", (std::string) ~val2);
}
class BigIntAndMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};
INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntAndMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("12343415"), BigInt("42542"), "38"),
                BigIntPairArg(BigInt("9745345"), BigInt("-7938457"), "1057153"),
                BigIntPairArg(BigInt("-9745345"), BigInt("-7938457"), "-1057153"),
                BigIntPairArg(BigInt("2435252"), BigInt("29459723"), "65536")
        )
);

TEST_P(BigIntAndMYTest, assignment_and) {
    BigIntPairArg arg = GetParam();
    arg.val1 &= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntAndMYTest, and) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 & arg.val2));
}

class BigIntOrMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntOrMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("12343415"), BigInt("42542"), "12385919"),
                BigIntPairArg(BigInt("9745345"), BigInt("-7938457"), "-16626649"),
                BigIntPairArg(BigInt("-9745345"), BigInt("-7938457"), "-16626649"),
                BigIntPairArg(BigInt("2435252"), BigInt("29459723"), "31829439")

        )
);

TEST_P(BigIntOrMYTest, assignment_or) {
    BigIntPairArg arg = GetParam();
    arg.val1 |= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntOrMYTest, and) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 | arg.val2));
}

class BigIntXorMYTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntXorMYTest,
        ::testing::Values(
                BigIntPairArg(BigInt("12343415"), BigInt("42542"), "12385881"),
                BigIntPairArg(BigInt("9745345"), BigInt("-7938457"), "-15569496"),
                BigIntPairArg(BigInt("-9745345"), BigInt("-7938457"), "15569496"),
                BigIntPairArg(BigInt("2435252"), BigInt("29459723"), "31763903")
        )
);

TEST_P(BigIntXorMYTest, assignment_xor_op) {
    BigIntPairArg arg = GetParam();
    arg.val1 ^= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntXorMYTest, xor_op) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 ^ arg.val2));
}

TEST(bigint_test, verification_set_znak1) {
    BigInt val1 = BigInt("346727846");
    val1.set_sign('+');
    ASSERT_EQ(val1.get_znak(), '+');
}

TEST(bigint_test, verification_set_znak2) {
    BigInt val1 = BigInt("346727846");
    val1.set_sign('-');
    ASSERT_EQ(val1.get_znak(), '-');
}

TEST(bigint_test, verification_length_digit) {
    ASSERT_EQ(get_length(346727846), 9);
    ASSERT_EQ(get_length(0), 1);
}

TEST(bigint_test, verification_digit_to_symbol) {
    ASSERT_EQ(digit_to_symbol(5), '5');
}

TEST(bigint_test, verification_symbol_to_digit) {
    ASSERT_EQ(symbol_to_digit('3'), 3);
}

TEST(bigint_test, verification_get_size) {
    BigInt val1("-28954729843");
    ASSERT_EQ(val1.get_size(), 11);
}

TEST(bigint_test, verification_get_znak) {
    BigInt val1("-28954729843");
    ASSERT_EQ(val1.get_znak(), '-');
}

TEST(bigint_test, verification_get_digit) {
    BigInt val1("28954729843");
    ASSERT_EQ(val1.get_digit()[3], '9');
}

TEST(bigint_test, verification_decimal_to_binary) {
    BigInt val1("28954729843");
    ASSERT_EQ(decimal_to_binary(val1), "11001110101110000110101110111101011");
}

TEST(bigint_test, verification_binary_to_decimal) {
    BigInt val1("28954729843");
    ASSERT_EQ(binary_to_decimal("11001110101110000110101110111101011"),  val1);
}

TEST(bigint_test, verification_delete_zeroes) {
    BigInt val2("28954729843");
    BigInt val1("00000000028954729843");
    ASSERT_EQ(delete_zeroes(val1),  val2);
}

TEST(bigint_test, verification_move_constructor) {
    BigInt val2("28954729843");
    BigInt val3("28954729843");
    ASSERT_EQ(move(val2),  val3);
}

TEST(bigint_test, verification_move_equal) {
    BigInt val2("28954729843");
    BigInt val3("28954729843");
    BigInt val1 = std::move(val2);
    ASSERT_EQ(val1,  val3);
    ASSERT_EQ(val2,  0);
}