#pragma once

#include "blend2d.h"

#include <filesystem>

namespace svg2b2d {

struct BuilderImpl {
  virtual ~BuilderImpl() {}

  virtual BLImage rasterize() = 0;
};

class SVGBuilder {
public:
  SVGBuilder(const std::filesystem::path& path);
  ~SVGBuilder() {}

  BLImage rasterize() {
    return mImpl ? mImpl->rasterize() : BLImage();
  }

private:
  std::shared_ptr<BuilderImpl> mImpl;
};

}
