#include "scenario_timer.h"

namespace aim {

ScenarioTimer::ScenarioTimer(uint16_t replay_fps) : replay_fps_(replay_fps) {
  float replay_seconds_per_frame = 1 / (float)replay_fps;
  replay_micros_per_frame_ = replay_seconds_per_frame * 1000000;

  // Initialize to non zero number so first frame is considered a new frame.
  replay_frame_number_ = 1000;

  frame_stopwatch_.Start();
  run_stopwatch_.Start();

  previous_frame_start_time_micros_ = frame_stopwatch_.GetElapsedMicros();
  frame_start_time_micros_ = frame_stopwatch_.GetElapsedMicros();
}

void ScenarioTimer::OnStartFrame() {
  has_started_ = true;
  uint64_t new_replay_frame_number = run_stopwatch_.GetElapsedMicros() / replay_micros_per_frame_;
  is_new_replay_frame_ = new_replay_frame_number != replay_frame_number_;
  replay_frame_number_ = new_replay_frame_number;

  previous_frame_start_time_micros_ = frame_start_time_micros_;
  frame_start_time_micros_ = frame_stopwatch_.GetElapsedMicros();
}

void ScenarioTimer::OnStartRender() {
  render_start_time_micros_ = frame_stopwatch_.GetElapsedMicros();
}

void ScenarioTimer::OnEndRender() {
  render_end_time_micros_ = frame_stopwatch_.GetElapsedMicros();
}

uint64_t ScenarioTimer::LastFrameRenderedMicrosAgo() {
  return frame_stopwatch_.GetElapsedMicros() - render_end_time_micros_;
}

}  // namespace aim