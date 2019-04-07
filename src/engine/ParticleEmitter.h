#include <SFML/Graphics.hpp>
#include "../util/Definitions.h"
#include <cmath>

using namespace sf;
using namespace std;

class ParticleEmitter : public Drawable, public Transformable {

    struct Particle {
        Vector2f velocity;
        Time lifetime;
    };

    vector<Particle> particles;
    VertexArray vertices;
    Time lifetime;
    Time elapsed;
    Vector2f emitter;

    void resetParticle(int index) {
        float angle = (rand() % 180) + (float) PI / 180.f;
        float speed = (rand() % 30) + 10.f;
        particles[index].velocity = Vector2f(cos(angle) * speed, sin(angle) * speed);
        particles[index].lifetime = milliseconds(rand() % 5000 + 5000);

        vertices[index].position = emitter;
    }

public:

    ParticleEmitter(unsigned count = 1000)
            : particles(count)
            , vertices(Points, count)
            , lifetime(seconds(10.f))
            , emitter(0.f, 0.f)
    {}

    void setEmitter(Vector2f position) { emitter = position; }

    void update(Time dt) {
        for (int i = 0; i < particles.size(); i++) {
            Particle &p = particles[i];

            p.lifetime -= dt;

            if (p.lifetime <= Time::Zero)
                resetParticle(i);

            elapsed += dt;
            elapsed = elapsed.asSeconds() > .5 ? seconds(.5) : elapsed; // i have to limit gravity (???) perhaps bug with dt passed in?
            vertices[i].position += p.velocity * dt.asSeconds();
            p.velocity.y += grav / 0.5f * (elapsed.asSeconds() * elapsed.asSeconds() * 0.05);

            float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
            vertices[i].color.a = static_cast<Uint8> (ratio * 255);
        }
    }

private:
    void draw(RenderTarget &target, RenderStates states) const override {
        target.draw(vertices);
    }
};