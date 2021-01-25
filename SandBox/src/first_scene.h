#pragma once

#include <scene.h>
#include <engine.h>

using namespace DE;

class FirstScene : public DE::Scene
{
    public:
        Mesh mesh;
        FirstScene();
        void onStart() override;
        void onUpdate(float dt) override;
        void onRender() override;
        void onDestroy() override;
};


