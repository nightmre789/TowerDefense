#pragma once
#include <SFML/Graphics.hpp>
#include "util/Definitions.h"
#include <cmath>

using namespace sf;
using namespace std;

class ParticleEmitter : public Drawable, public Transformable {

    struct Particle {
        Vector2f velocity;
        Time lifetime;
        Time life;
    };

    vector<Particle> particles;
    VertexArray vertices;
    Time lifetime;
    Time elapsed;
    Vector2f emitterStart;
    Vector2f emitterEnd;

    Vector2f posOnLine() {
        return { rand () % static_cast<int>(emitterEnd.x - emitterStart.x) + emitterStart.x , 720 };
    }

    void resetParticle(int index) {
        float angle = (rand() % 360) + (float) PI / 360.f;
        float speed = (rand() % 7) + 13.f;
        particles[index].velocity = Vector2f(cos(angle) * speed, (sin(angle) > 0 ? sin(-angle) : sin(angle)) * speed);
        particles[index].lifetime = milliseconds(rand() % 10000 + 3000);
        particles[index].life = seconds(0);

        vertices[index].position = posOnLine();
        vertices[index].color = {255, 170, 0, static_cast<Uint8> (rand() % 200 + 55)};
    }

public:

    ParticleEmitter(unsigned count = 1000)
            : particles(count)
            , vertices(Points, count)
            , lifetime(seconds(10.f))
            , emitterStart(0.f, 0.f)
            , emitterEnd(1280.f, 0.f)
    {}

    void setEmitter(Vector2f start, Vector2f end) { emitterStart = start; emitterEnd = end; }

    void update(Time dt) {
        for (int i = 0; i < particles.size(); i++) {
            Particle &p = particles[i];

            p.lifetime -= dt;
            p.life += dt;

            if (p.lifetime <= Time::Zero)
                resetParticle(i);


            vertices[i].position += p.velocity * dt.asSeconds();
            p.velocity.x += (rand() % 11 - 5) * .2;
            float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
            vertices[i].color.a = static_cast<Uint8> (ratio * 255);
        }
    }

private:
    void draw(RenderTarget &target, RenderStates states) const override {
        target.draw(vertices);
    }
};