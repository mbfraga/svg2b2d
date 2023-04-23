
#include "svg.h"
#include "svgbuilder.h"

#include "svgshapes.h"
#include "bspanutil.h"


#include <vector>
#include <memory>
#include <fstream>
#include <optional>

//using namespace svg2b2d;

class InnerBuilder : public svg2b2d::BuilderImpl {
public:
  InnerBuilder(const std::filesystem::path& path) {

    std::ifstream t(path.string());
    if (!t.is_open()) {
      return;
    }

    svg2b2d::SVGDocument doc;

    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);

    svg2b2d::ByteSpan inChunk(buffer.data(), buffer.size());   // = svg2b2d::chunk_from_data_size(bytes, sz);
    
    // Load the document from the data
    doc.readFromData(inChunk);

    mDoc = std::move(doc);
  }

  BLImage rasterize() override {
    BLImage img;

    if (mDoc)  {
      img.create(mDoc->width(), mDoc->height(), BL_FORMAT_PRGB32);
      SVGRenderer ctx(img);
      mDoc->draw(ctx);
      ctx.end();
    }

    return img;
  }

private:
  std::optional<svg2b2d::SVGDocument> mDoc;
};

bool parseSVG(const void* bytes, const size_t sz, BLImage& outImage)
{
    svg2b2d::ByteSpan inChunk(bytes, sz);   // = svg2b2d::chunk_from_data_size(bytes, sz);
    
    // Create a new document
    svg2b2d::SVGDocument doc;

    // Load the document from the data
    doc.readFromData(inChunk);
    
    
    // Draw the document into a IRender
    outImage.create(doc.width(), doc.height(), BL_FORMAT_PRGB32);
    SVGRenderer ctx(outImage);
    ctx.clearAll();
    doc.draw(ctx);
    ctx.end();
    
    return true;
}

svg2b2d::SVGBuilder::SVGBuilder(const std::filesystem::path& path) 
: mImpl(std::make_shared<InnerBuilder>(path))
{
}



