/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_FILTERS_ADS_HISTORY_CONVERSION_CONFIRMATION_TYPE_FILTER_H_  // NOLINT
#define BAT_ADS_INTERNAL_FILTERS_ADS_HISTORY_CONVERSION_CONFIRMATION_TYPE_FILTER_H_  // NOLINT

#include <deque>

#include "bat/ads/internal/filters/ads_history_filter.h"

namespace ads {

struct AdsHistory;
class ConfirmationType;

class AdsHistoryConversionConfirmationTypeFilter : public AdsHistoryFilter {
 public:
  AdsHistoryConversionConfirmationTypeFilter();
  ~AdsHistoryConversionConfirmationTypeFilter() override;

  std::deque<AdHistory> Apply(
      const std::deque<AdHistory>& history) const override;

 private:
  bool ShouldFilterConfirmationType(
    const ConfirmationType& type) const;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_FILTERS_ADS_HISTORY_CONVERSION_CONFIRMATION_TYPE_FILTER_H_  // NOLINT
