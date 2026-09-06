#include <soa/soa_vector.hpp>

#include <cassert>
#include <cstdint>
#include <iostream>

struct Particle {
    float x;
    float y;
    std::uint32_t id;
};

int main() {
    soa::vector<Particle> particles;

    particles.reserve(2);
    particles.push_back({1.0f, 2.0f, 10});
    particles.push_back({3.0f, 4.0f, 20});

    particles[0].x += 10.0f;

    auto second = particles[1];
    second.y = 40.0f;

    assert(particles.size() == 2);
    assert(particles[0].x == 11.0f);
    assert(particles[1].y == 40.0f);
    assert(particles[1].id == 20);

    std::cout << "passed \n";
}