#pragma once

#include "../entity.hpp"
#include "../resource_identifiers.hpp"
#include "../data_tables.hpp"

#include <SFML/Graphics/Sprite.hpp>

/*  ***TODO***
* 
*/

//Example of different bullet types, used if bullet is not an abstract class.


//First implementation of Bullet class
class Bullet : public Entity {
    public:
        enum Type {
            FireBullet,
            IceBullet,
            WoodBullet,
            TypeCount
        };

    public:

        // Constructor
        Bullet(Type type, const TextureHolder& textures);

        //Destructor, only needed if abstract class
        virtual ~Bullet() {}

        float GetSpeed() const;

        //could also return damage duration, depends on how the hit to enemy is implemented
        int GetDamage() const;

        virtual sf::FloatRect GetBoundingRect() const;

        unsigned int GetCategory() const;

        //More getter functions, and some way to destroy bullet when it hits an enemy
    private:
        virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void DrawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
        Textures::ID ToTextureID(Bullet::Type type);
        
    protected:
        Type            type_;
        sf::Sprite      sprite_;
        float           speed_;
        int             damage_;
        int             damage_duration_;
};