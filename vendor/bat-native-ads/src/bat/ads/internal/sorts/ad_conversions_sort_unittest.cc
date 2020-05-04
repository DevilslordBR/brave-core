/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/sorts/ad_conversions_sort_factory.h"

#include <memory>

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {

class BatAdConversionsSortTest : public ::testing::Test {
 protected:
  BatAdConversionsSortTest() {
    // You can do set-up work for each test here
  }

  ~BatAdConversionsSortTest() override {
    // You can do clean-up work that doesn't throw exceptions here
  }

  // If the constructor and destructor are not enough for setting up and
  // cleaning up each test, you can use the following methods

  void SetUp() override {
    // Code here will be called immediately after the constructor (right before
    // each test)
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)
  }

  AdConversionList GetUnsortedAdConversions() {
    AdConversionList list;

    AdConversionInfo ad_conversion;
    ad_conversion.type = "postview";
    list.push_back(ad_conversion);
    ad_conversion.type = "postclick";
    list.push_back(ad_conversion);
    ad_conversion.type = "postview";
    list.push_back(ad_conversion);
    ad_conversion.type = "postclick";
    list.push_back(ad_conversion);
    ad_conversion.type = "postview";
    list.push_back(ad_conversion);

    return list;
  }
};

TEST_F(BatAdConversionsSortTest,
    NoSortOrder) {
  // Arrange

  // Act
  const auto sort = AdConversionsSortFactory::Build(
      AdConversionInfo::SortType::kNone);

  // Assert
  EXPECT_EQ(nullptr, sort);
}

TEST_F(BatAdConversionsSortTest,
    DescendingSortOrder) {
  // Arrange
  AdConversionList list = GetUnsortedAdConversions();

  const auto sort = AdConversionsSortFactory::Build(
      AdConversionInfo::SortType::kDescendingOrder);

  // Act
  list = sort->Apply(list);

  // Assert
  AdConversionList expected_list;
  AdConversionInfo ad_conversion;
  ad_conversion.type = "postclick";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postclick";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postview";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postview";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postview";
  expected_list.push_back(ad_conversion);

  EXPECT_EQ(expected_list, list);
}

TEST_F(BatAdConversionsSortTest,
    DescendingSortOrderForEmptyList) {
  // Arrange
  AdConversionList list = {};

  const auto sort = AdConversionsSortFactory::Build(
      AdConversionInfo::SortType::kDescendingOrder);

  // Act
  list = sort->Apply(list);

  // Assert
  const AdConversionList expected_list = {};

  EXPECT_EQ(expected_list, list);
}

TEST_F(BatAdConversionsSortTest,
    AscendingSortOrder) {
  // Arrange
  AdConversionList list = GetUnsortedAdConversions();

  const auto sort = AdConversionsSortFactory::Build(
      AdConversionInfo::SortType::kAscendingOrder);

  // Act
  list = sort->Apply(list);

  // Assert
  AdConversionList expected_list;
  AdConversionInfo ad_conversion;
  ad_conversion.type = "postview";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postview";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postview";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postclick";
  expected_list.push_back(ad_conversion);
  ad_conversion.type = "postclick";
  expected_list.push_back(ad_conversion);

  EXPECT_EQ(expected_list, list);
}

TEST_F(BatAdConversionsSortTest,
    AscendingSortOrderForEmptyList) {
  // Arrange
  AdConversionList list = {};

  const auto sort = AdConversionsSortFactory::Build(
      AdConversionInfo::SortType::kAscendingOrder);

  // Act
  list = sort->Apply(list);

  // Assert
  const AdConversionList expected_list = {};

  EXPECT_EQ(expected_list, list);
}

}  // namespace ads
