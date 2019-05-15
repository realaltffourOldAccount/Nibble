#ifndef LAYOUT_H
#define LAYOUT_H

#include "chsr_api.h"

namespace WEngine {

class Layout {
  public:
    Layout(void);
    ~Layout(void);

    void addDrawable();
    void removeDrawable();
    void cleanDrawables();

    void render();

  private:
};

} // namespace WEngine

#endif