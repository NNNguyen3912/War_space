#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Animation.h"
#include "Entity.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Score.h"
#include "Constants.h"
#include "Winner_point.h"
#include <iostream>

// Hàm kiểm tra va chạm
bool isCollide(Entity* a, Entity* b) {
    return (b->x - a->x) * (b->x - a->x) +
        (b->y - a->y) * (b->y - a->y) <
        (a->R + b->R) * (a->R + b->R);
}

Score score;

int main() {
    srand(time(0));

    sf::RenderWindow app(sf::VideoMode(W, H), "War Space");
    app.setFramerateLimit(60);

    // Load textures
    sf::Texture t1, t2, t3, t4, t5, t6, t7, t8;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/neon_space_background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    t8.loadFromFile("images/Winner_point.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    sf::Sprite background(t2);
    background.setPosition(0, 0);

    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
    Animation sWinnerPoint(t8, 0, 0, 192, 192, 1, 0.4);

    std::list<Entity*> entities;

    // Tạo các thiên thạch ban đầu
    for (int i = 0; i < 15; i++) {
        asteroid* a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    // Tạo WinnerPoint duy nhất
    WinnerPoint* wp = new WinnerPoint();
    wp->settings(sWinnerPoint, rand() % W, rand() % H, rand() % 360, 15);
    entities.push_back(wp);

    // Tạo người chơi
    player* p = new player();
    p->settings(sPlayer, W / 2, H / 2, 0, 20);
    entities.push_back(p);

    // Main game loop
    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    bullet* b = new bullet();
                    b->settings(sBullet, p->x, p->y, p->angle, 10);
                    entities.push_back(b);
                }
            }
        }

        // Điều khiển người chơi
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle += 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p->angle -= 3;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            p->thrust = true;
        }
        else {
            p->thrust = false;
        }

        // Kiểm tra va chạm
        for (auto a : entities) {
            for (auto b : entities) {
                // Va chạm giữa thiên thạch và đạn
                if (a->name == "asteroid" && b->name == "bullet" && isCollide(a, b)) {
                    a->life = false;
                    b->life = false;

                    score.increase(100);
                    Entity* e = new Entity();
                    e->settings(sExplosion, a->x, a->y);
                    e->name = "explosion";
                    entities.push_back(e);

                    for (int i = 0; i < 2; i++) {
                        if (a->R == 15) continue;
                        Entity* e = new asteroid();
                        e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                        entities.push_back(e);
                    }
                }

                // Va chạm giữa người chơi và thiên thạch
                if (a->name == "player" && b->name == "asteroid" && isCollide(a, b)) {
                    b->life = false;

                    Entity* e = new Entity();
                    e->settings(sExplosion_ship, a->x, a->y);
                    e->name = "explosion";
                    entities.push_back(e);

                    p->settings(sPlayer, W / 2, H / 2, 0, 20);
                    p->dx = 0;
                    p->dy = 0;

                    score.reset();
                }

                // Va chạm giữa đạn và WinnerPoint
                if (a->name == "winner_point" && b->name == "bullet" && isCollide(a, b)) {
                    a->life = false;
                    b->life = false;

                    std::cout << "Congratulations! You win!" << std::endl;
                    app.close();
                }
            }
        }

        if (p->thrust)
            p->anim = sPlayer_go;
        else
            p->anim = sPlayer;

        // Cập nhật thực thể
        for (auto i = entities.begin(); i != entities.end();) {
            Entity* e = *i;
                 
            e->update();
            e->anim.update();

            if (e->life == false) {
                i = entities.erase(i);
                delete e;
            }
            else
                i++;
        }

        // Vẽ mọi thứ
        app.clear();
        app.draw(background);
        for (auto e : entities) e->draw(app);
        app.display();

        // Cập nhật và vẽ tất cả thực thể
        for (auto e : entities) {
            e->update();
            e->anim.update();
            e->draw(app);
        }

    }

    return 0;
}
