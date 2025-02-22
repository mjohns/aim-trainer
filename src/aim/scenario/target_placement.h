#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "aim/common/simple_types.h"
#include "aim/core/target.h"
#include "aim/core/application.h"
#include "aim/proto/scenario.pb.h"

namespace aim {

class WallTargetPlacer {
 public:
  virtual ~WallTargetPlacer() {}

  virtual glm::vec2 GetNextPosition() = 0;
};

std::unique_ptr<WallTargetPlacer> CreateWallTargetPlacer(const ScenarioDef& def,
                                                         TargetManager* target_manager,
                                                         Application* app);

std::unique_ptr<WallTargetPlacer> CreateWallTargetPlacer(const Wall& wall,
                                                         const TargetPlacementStrategy& strategy,
                                                         TargetManager* target_manager,
                                                         Application* app);

}  // namespace aim
