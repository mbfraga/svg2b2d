#pragma once

#include "blend2d.h"

#include <filesystem>

namespace svg2b2d {

struct BuilderImpl {
  virtual ~BuilderImpl() {}

  virtual BLImage buildImage(double scale) = 0;

  virtual void draw(BLContext& ctx, double scale) const = 0;
};

class SVGBuilder {
public:
  SVGBuilder(const std::filesystem::path& path);
  ~SVGBuilder() {}

  BLImage buildImage(double scale) {
    return mImpl ? mImpl->buildImage(scale) : BLImage();
  }

  virtual void draw(BLContext& ctx, double scale) const {
    if (mImpl) {
        mImpl->draw(ctx, scale);
    }
  }

private:
  std::shared_ptr<BuilderImpl> mImpl;
};

}
