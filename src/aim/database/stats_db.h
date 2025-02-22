#pragma once

#include <sqlite3.h>

#include <filesystem>
#include <string>
#include <vector>

namespace aim {

struct StatsRow {
  int64_t stats_id = 0;
  std::string timestamp;
  int64_t num_hits = 0;
  int64_t num_kills = 0;
  int64_t num_shots = 0;
  double score = 0.0;
  double cm_per_360 = 0.0;
};

class StatsDb {
 public:
  explicit StatsDb(const std::filesystem::path& db_path);
  ~StatsDb();

  void AddStats(const std::string& scenario_id, StatsRow* row);

  std::vector<StatsRow> GetStats(const std::string& scenario_id);

  StatsDb(const StatsDb&) = delete;
  StatsDb(StatsDb&&) = default;
  StatsDb& operator=(StatsDb other) = delete;
  StatsDb& operator=(StatsDb&& other) = delete;

 private:
  sqlite3* db_ = nullptr;
};

}  // namespace aim
