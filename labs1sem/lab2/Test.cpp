//
// Created by user on 30.12.22.
//
#include <iostream>
#include "gtest/gtest.h"
#include "Game/CompetitionWithDetail/CompetitionWithDetail.h"
#include "Game/GameMatrix/GameMatrix.h"
#include "Game/Tournament/Tournament.h"

TEST(MYTest, check_get_score) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    GameScore score;
    score = Matrix.getScore(COOPERATE, COOPERATE, DEFECT);
    ASSERT_EQ(score.getScoreA(), 3);
    ASSERT_EQ(score.getScoreB(), 3);
    ASSERT_EQ(score.getScoreC(), 9);
}

TEST(MYTest, check_get_score_matrix) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    GameScore score;
    score = Matrix.getScore(COOPERATE, COOPERATE, COOPERATE);
    ASSERT_EQ(score.getScoreA(), 7);
    ASSERT_EQ(score.getScoreB(), 7);
    ASSERT_EQ(score.getScoreC(), 7);
}
TEST(MYTest, check_get_score1) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    GameScore score;
    score = Matrix.getScore(COOPERATE, DEFECT, DEFECT);
    ASSERT_EQ(score.getScoreA(), 0);
    ASSERT_EQ(score.getScoreB(), 5);
    ASSERT_EQ(score.getScoreC(), 5);
}

TEST(MYTest, check_get_score2) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    GameScore score;
    score = Matrix.getScore(DEFECT, DEFECT, COOPERATE);
    ASSERT_EQ(score.getScoreA(), 5);
    ASSERT_EQ(score.getScoreB(), 5);
    ASSERT_EQ(score.getScoreC(), 0);
}

TEST(MYTest, check_get_score3) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    GameScore score;
    score = Matrix.getScore(DEFECT, DEFECT, DEFECT);
    ASSERT_EQ(score.getScoreA(), 1);
    ASSERT_EQ(score.getScoreB(), 1);
    ASSERT_EQ(score.getScoreC(), 1);
}


TEST(MYTest, check_vote1) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    string strategy = "AlwaysChoiceC";

    shared_ptr<GameStrategy> str = Factory.createStrategy(Factory.DetectionStrategyName(strategy),  Matrix);

    ASSERT_EQ(str->vote(), COOPERATE);
}

TEST(MYTest, check_vote2) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    string strategy = "AlwaysChoiceD";

    shared_ptr<GameStrategy> str = Factory.createStrategy(Factory.DetectionStrategyName(strategy),  Matrix);

    ASSERT_EQ(str->vote(), DEFECT);
}

TEST(MYTest, check_vote3) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    string strategy = "Alternating";

    shared_ptr<GameStrategy> str = Factory.createStrategy(Factory.DetectionStrategyName(strategy),  Matrix);

    ASSERT_EQ(str->vote(), COOPERATE);
    ASSERT_EQ(str->vote(), DEFECT);
}

TEST(MYTest, check_vote4) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    string strategy = "Tit_For_Tat_Soft";

    shared_ptr<GameStrategy> str = Factory.createStrategy(Factory.DetectionStrategyName(strategy),  Matrix);

    ASSERT_EQ(str->vote(), COOPERATE);
}

TEST(MYTest, check_vote5) {
    StrategyFactory Factory;
    GameMatrix Matrix;
    string strategy = "Tit_For_Tat_Hard";

    shared_ptr<GameStrategy> str = Factory.createStrategy(Factory.DetectionStrategyName(strategy),  Matrix);

    ASSERT_EQ(str->vote(), COOPERATE);
}
