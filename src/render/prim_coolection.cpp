#include "prim_coolection.hpp"
#include "app/app.hpp"
#include "prim.hpp"

void mr::PrimCollection::draw() const noexcept
{
  for (int i = 0; i < _size; i++) {
    const auto & prim = _prims[i];
    const auto & ssbo = _ssbos[i];
    const auto & data = _datas[i];

    if (data.size() > 0) {
      ssbo.bind();
      prim.draw();
      ssbo.unbind();
    }
  }
}

void mr::PrimCollection::emplace_back(mr::Prim::PrimType ptype, mr::Transform transform) noexcept {
  if (transforms((int)ptype).size() != 0) {
    _datas[(int)ptype].push_back(transform);
    _ssbos[(int)ptype].write(std::span(_datas[(int)ptype]));
    _prims[(int)ptype].num_of_instances()++;
  } else {
    _datas[(int)ptype].push_back(transform);
    _ssbos[(int)ptype] = SSBO(std::span(_datas[(int)ptype]));
    switch (ptype) {
      case Prim::PrimType::eCircle:
        _prims[(int)ptype] = create_circle();
        break;
      case Prim::PrimType::eSquare:
        _prims[(int)ptype] = create_square();
        break;
      case Prim::PrimType::eOther:
        break;
    }
  }
}

void mr::PrimCollection::emplace_back_synced(mr::Application &app, mr::Prim::PrimType ptype, mr::Transform transform) noexcept {
  app.sync_object(mr::serialize(ptype, transform));
  emplace_back(ptype, transform);
}

void mr::PrimCollection::deserialize(const std::string &str) {
  nlohmann::json j = nlohmann::json::parse(str.begin(), str.end());

  float px = j["px"].get<float>();
  float py = j["py"].get<float>();
  float a = j["a"].get<float>();
  float s = j["s"].get<float>();
  mr::Prim::PrimType ptype = j["_ptype"].get<mr::Prim::PrimType>();

  emplace_back(ptype, {{px, py}, a, s});
}
