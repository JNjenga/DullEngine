#pragma once

#include <scene.h>
#include <engine.h>

using namespace DE;

class IntroScene : public DE::Scene
{
    public:
        Mesh mesh;
        IntroScene();
        void onStart() override;
        void onUpdate(float dt) override;
        void onRender() override;
        void onDestroy() override;
};
