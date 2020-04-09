#ifndef ENTITY_H
#define ENTITY_H

// Class for entities in ECS system for games
// An entity contains a vector of components that contains its
// attributes
#include <memory>
#include <vector>

#include "component.h"

constexpr int max_components = 10;

inline std::size_t getNewcomponentTypeId() {
  static std::size_t id = 0;
  return id++;
}

template <typename T> inline std::size_t getcomponentTypeId() noexcept {
  static_assert(std::is_base_of<component, T>::value, "");
  static std::size_t typeID = getNewcomponentTypeId();
  return typeID;
}

constexpr std::size_t maxcomponents = 32;

using compBitSet = std::bitset<max_components>;
using compArray = std::array<component *, max_components>;

class entity {
private:
  std::vector<std::unique_ptr<component>> components;
  compBitSet componentBitSet;
  compArray componentArray;
  bool active = true;

public:
  entity(){};
  virtual ~entity(){};

  void kill() { active = false; }
  bool isActive() const { return active; }

  void handle_events(SDL_Event *event) {
    for (auto &c : components)
      c->handle_events(event);
  }

  void handle_collisions(std::vector<std::unique_ptr<entity>> &entities) {
    for (auto &c : components)
      c->handle_collisions(entities);
  }

  void update() {
    for (auto &c : components)
      c->update();
  }

  void render(SDL_Renderer *renderer) const {
    for (auto &c : components)
      c->render(renderer);
  }

  template <typename T, typename... TArgs>
  entity &add_component(TArgs &&... MArgs) {
    T *comp(new T(this, std::forward<TArgs>(MArgs)...));
    std::unique_ptr<component> ptr_component{comp};
    auto id = getcomponentTypeId<T>();
    componentBitSet[id] = true;
    components.emplace_back(std::move(ptr_component));
    componentArray[id] = components.back().get();
    return *this;
  }

  template <typename T> bool has_component() const {
    return componentBitSet[getcomponentTypeId<T>()];
  }

  template <typename T> T &get_component() const {
    auto ptr(componentArray[getcomponentTypeId<T>()]);
    return *static_cast<T *>(ptr);
  }
};

#endif // ENTITY_H
