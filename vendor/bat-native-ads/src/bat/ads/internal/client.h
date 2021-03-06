/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_CLIENT_H_
#define BAT_ADS_INTERNAL_CLIENT_H_

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <memory>

#include "bat/ads/ads_client.h"
#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/internal/client_state.h"

namespace ads {

class AdsImpl;

class Client {
 public:
  Client(AdsImpl* ads, AdsClient* ads_client);
  ~Client();

  void Initialize(InitializeCallback callback);

  void AppendAdHistoryToAdsShownHistory(
      const AdHistory& ad_history);
  std::deque<AdHistory> GetAdsShownHistory() const;
  void AppendToPurchaseIntentSignalHistoryForSegment(
      const std::string& segment,
      const PurchaseIntentSignalHistory& history);
  const PurchaseIntentSignalSegmentHistoryMap&
      GetPurchaseIntentSignalHistory() const;
  AdContent::LikeAction ToggleAdThumbUp(
      const std::string& creative_instance_id,
      const std::string& creative_set_id,
      const AdContent::LikeAction action);
  AdContent::LikeAction ToggleAdThumbDown(
      const std::string& creative_instance_id,
      const std::string& creative_set_id,
      const AdContent::LikeAction action);
  CategoryContent::OptAction ToggleAdOptInAction(
      const std::string& category,
      const CategoryContent::OptAction action);
  CategoryContent::OptAction ToggleAdOptOutAction(
      const std::string& category,
      const CategoryContent::OptAction action);
  bool ToggleSaveAd(
      const std::string& creative_instance_id,
      const std::string& creative_set_id,
      const bool saved);
  bool ToggleFlagAd(
      const std::string& creative_instance_id,
      const std::string& creative_set_id,
      const bool flagged);
  bool IsFilteredCategory(
      const std::string& category) const;
  bool IsFilteredAd(
      const std::string& creative_set_id) const;
  bool IsFlaggedAd(
      const std::string& creative_set_id) const;
  void UpdateAdUUID();

  void UpdateSeenAdNotification(
      const std::string& creative_instance_id,
      const uint64_t value);
  std::map<std::string, uint64_t> GetSeenAdNotifications();
  void ResetSeenAdNotifications(
      const CreativeAdNotificationList& ads);

  void UpdateSeenAdvertiser(
      const std::string& advertiser_id,
      const uint64_t value);
  std::map<std::string, uint64_t> GetSeenAdvertisers();
  void ResetSeenAdvertisers(
      const CreativeAdNotificationList& ads);

  void SetNextCheckServeAdNotificationTimestampInSeconds(
      const uint64_t timestamp_in_seconds);
  uint64_t GetNextCheckServeAdNotificationTimestampInSeconds();
  void SetAvailable(
      const bool available);

  bool GetAvailable() const;
  void SetUserModelLanguage(
      const std::string& language);
  std::string GetUserModelLanguage();
  void SetUserModelLanguages(
      const std::vector<std::string>& languages);
  std::vector<std::string> GetUserModelLanguages();
  std::string GetLastPageClassification();
  void AppendPageScoreToPageScoreHistory(
      const std::vector<double>& page_score);
  std::deque<std::vector<double>> GetPageScoreHistory();
  void AppendTimestampToCreativeSetHistory(
      const std::string& creative_instance_id,
      const uint64_t timestamp_in_seconds);
  std::map<std::string, std::deque<uint64_t>> GetCreativeSetHistory() const;
  void AppendTimestampToAdConversionHistory(
      const std::string& creative_set_id,
      const uint64_t timestamp_in_seconds);
  std::map<std::string, std::deque<uint64_t>>
      GetAdConversionHistory() const;
  void AppendTimestampToCampaignHistory(
      const std::string& creative_instance_id,
      const uint64_t timestamp_in_seconds);
  std::map<std::string, std::deque<uint64_t>>
      GetCampaignHistory() const;
  std::string GetVersionCode() const;
  void SetVersionCode(
      const std::string& value);

  void RemoveAllHistory();

 private:
  bool is_initialized_;

  InitializeCallback callback_;

  void SaveState();
  void OnStateSaved(const Result result);

  void LoadState();
  void OnStateLoaded(const Result result, const std::string& json);

  bool FromJson(const std::string& json);

  AdsImpl* ads_;  // NOT OWNED
  AdsClient* ads_client_;  // NOT OWNED

  std::unique_ptr<ClientState> client_state_;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_CLIENT_H_
