/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <atomic>
#include <future>
#include <memory>
#include <vector>

#include "cyber/cyber.h"
#include "modules/drivers/wato/proto/config.pb.h"
#include "modules/drivers/proto/sensor_image.pb.h"

#include "modules/drivers/wato/usb_cam.h"

namespace apollo {
namespace drivers {
namespace wato {

using apollo::cyber::Component;
using apollo::cyber::Reader;
using apollo::cyber::Writer;
using apollo::drivers::Image;
using apollo::drivers::wato::config::Config;

class WatoComponent : public Component<> {
 public:
  bool Init() override;
  ~WatoComponent();

 private:
  void run();

  std::shared_ptr<Writer<Image>> writer_ = nullptr;
  std::unique_ptr<UsbCam> wato_device_;
  std::shared_ptr<Config> wato_config_;
  WatoImagePtr raw_image_ = nullptr;
  std::vector<std::shared_ptr<Image>> pb_image_buffer_;
  uint32_t spin_rate_ = 200;
  uint32_t device_wait_ = 2000;
  int index_ = 0;
  int buffer_size_ = 16;
  const int32_t MAX_IMAGE_SIZE = 20 * 1024 * 1024;
  std::future<void> async_result_;
  std::atomic<bool> running_ = {false};
};

CYBER_REGISTER_COMPONENT(WatoComponent)
}  // namespace wato
}  // namespace drivers
}  // namespace apollo
