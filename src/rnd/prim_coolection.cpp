#include "prim_coolection.hpp"
#include "app/app.hpp"
#include "prim.hpp"

void mr::PrimCollection::draw() const noexcept {
  for (int i = 0; i < _size; i++) {
    const auto & prim = _prims[i];
    const auto & ssbo = _ssbos[i];
    const auto & data = _datas[i];

    if (data.size() > 0) {
      prim.draw(ssbo);
    }
  }
}

void mr::PrimCollection::emplace_back(mr::Prim::PrimType ptype, mr::ShapeData transform) noexcept {
  auto &prim = _prims[(int)ptype];
  auto &data = _datas[(int)ptype];
  auto &ssbo = _ssbos[(int)ptype];

  data.push_back(transform);
  if (data.size() > 1) {
    ssbo.update(data);
  } else {
    ssbo = mr::SSBO<mr::ShapeData>(data);
    switch (ptype) {
      case Prim::PrimType::eCircle:
        prim = create_circle();
        break;
      case Prim::PrimType::eSquare:
        prim = create_square();
        break;
      case Prim::PrimType::eOther:
        break;
    }
  }
}

void mr::PrimCollection::emplace_back_synced(mr::Application &app, mr::Prim::PrimType ptype, mr::ShapeData transform) noexcept {
  app.sync_object(mr::serialize(ptype, transform));
  emplace_back(ptype, transform);
}

void mr::PrimCollection::deserialize(const std::string &str) {
  nlohmann::json j = nlohmann::json::parse(str.begin(), str.end());

  float cx = j["cx"].get<float>();
  float cy = j["cy"].get<float>();
  float cz = j["cz"].get<float>();
  float cw = j["cw"].get<float>();
  float px = j["px"].get<float>();
  float py = j["py"].get<float>();
  float a = j["a"].get<float>();
  float s = j["s"].get<float>();
  mr::Prim::PrimType ptype = j["_ptype"].get<mr::Prim::PrimType>();

  emplace_back(ptype, {{px, py}, a, s});
}
