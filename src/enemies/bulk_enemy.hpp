#pragma once

#include "enemy.hpp"

class BulkEnemy : public Enemy {

    public:
        BulkEnemy(const TextureHolder &textures, unsigned int difficultyLevel = 1, float travelledDistance = 0.f, int directionIndex = 0);
        void TakeHit(int damage, unsigned int bulletType);

    private:
        //bool CheckDestroyBehaviour(CommandQueue& commands) override;
};