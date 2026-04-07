#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;

void motionoftoken(Sprite& tokens, float& deltaTime)
{
    tokens.move(-150 * deltaTime, 0);
}
struct Bird {
    Sprite sprite; // for any moving or animation use it.
    Texture textures[4];// for two pic for bird.
    float y;
    float gravity = 600.0f;
    float velocity_y;
    bool sound_fly; // fly or not?
    float counter = 0;//icreament frame.
    int texture_swaping; //what photo appear.
    bool InGround = false; // if we make multiplayer better for eachbird

    SoundBuffer flyingbuffer; //الرفرفه عادي
    Sound flyingsound;

    SoundBuffer henediBuffer;
    Sound henediSound;

    int jumpcount = 0;
};

void Birdframe(Bird& bird, int Level) {

    if (Level == 1) {
        bird.textures[0].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/b0.png");
        bird.textures[1].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/b1.png");
        bird.textures[2].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/b2.png");
        bird.textures[3].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/b0.png");
        bird.sprite.setScale(1.0f, 1.0f);


        if (!bird.flyingbuffer.loadFromFile("Flappy Bird_sounds_sfx_wing.wav")) {
            cout << "Error!! The file doesnot upload." << endl;
        }

        else {
            bird.flyingsound.setBuffer(bird.flyingbuffer);
        }

        if (!bird.henediBuffer.loadFromFile("henedi.wav")) {
            cout << "Error ! Henedi Sound Not Found" << endl;

        }

        else {
            bird.henediSound.setBuffer(bird.henediBuffer);
            bird.henediSound.setVolume(80); //  عالي شوية عشان يبان
        }

    }

    if (Level == 2) {

        bird.textures[0].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/0.png");
        bird.textures[1].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/1.png");
        bird.textures[2].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/2.png");
        bird.textures[3].loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/3.png");
        bird.sprite.setScale(0.2f, 0.2f);

        if (!bird.flyingbuffer.loadFromFile("Flappy Bird_sounds_sfx_wing.wav")) {
            cout << "Error!! The file doesnot upload." << endl;

        }
        else {
            bird.flyingsound.setBuffer(bird.flyingbuffer);
            bird.flyingsound.setLoop(false);
            bird.flyingsound.stop();
        }

        //  bird.textures[0].setSmooth(true); // for smooth the pic

    }

    //if (Level == 3) {



    //}

    bird.sprite.setTexture(bird.textures[0]);
    bird.sprite.setPosition(100, 220);
    bird.y = 320;
    bird.jumpcount = 0; // for hendi sound start again after 10 jump
    bird.velocity_y = 0;
    bird.texture_swaping = 0;
}


void Updating(Bird& bird, float dt) {
    bird.velocity_y += bird.gravity * dt;
    bird.sprite.move(0, bird.velocity_y * dt);

    if (bird.sprite.getPosition().y > 450) {//to avoid get out from sreen.
        bird.sprite.setPosition(100, 450);
        bird.velocity_y = 0;
    }
    if (bird.sprite.getPosition().y < 0) {
        bird.sprite.setPosition(100, 0);
        bird.velocity_y = 0;
    }
    if (!bird.InGround) {
        bird.counter += dt;
        if (bird.counter >= 0.10f) { // change the frame texture index when comes 0.10sec.
            bird.texture_swaping++;
            if (bird.texture_swaping >= 4) {
                bird.texture_swaping = 0; // start counting again
            }
            bird.sprite.setTexture(bird.textures[bird.texture_swaping]);
            bird.counter = 0;   //to start a new from zero again &again

        }
        if (bird.velocity_y < 0) {
            bird.sprite.setRotation(-20.0f);
        }
        else {
            // bird.sprite.setRotation(40); to not jump suddenly
            float desiredRotation = bird.velocity_y * 0.1f;
            if (desiredRotation > 40.0f) {
                desiredRotation = 40.0f;
            }
            bird.sprite.setRotation(desiredRotation);

        }

    }

    else {

        // bird.sprite.setRotation(0.0f);

        bird.sprite.setTexture(bird.textures[0]);

        bird.sprite.setRotation(20.0f);

    }



}






void flapping(Bird& bird, int currentLevel) {
    bird.velocity_y = -250;
    bird.flyingsound.play();
    bird.jumpcount++;
    if (currentLevel == 1) {
        if (bird.jumpcount >= 10) {
            bird.henediSound.play();
            bird.jumpcount = 0; // ارجع عد من الأول
        }

    }

}

int main() {
    int windowWidth = 900;
    int windowlength = 504; // i think it is perfect size!
    RenderWindow window(VideoMode(windowWidth, windowlength), "Amazing Flappy Bird");
    window.setFramerateLimit(60);

    int currentLevel = 1; // 1 bec. game have start  point at least (just temp.)
    
    Bird flyingbird;
    Birdframe(flyingbird, currentLevel); // know the level from it.
    flyingbird.sprite.setOrigin(34 / 2, 26 / 2); //علشان لما اجي اغير الحركه تبقي معدوله

   // bool InGround = false;

    Clock timer;
    float timecounter = 0.0f;
    const float Fixedtime = 1.0f / 60.0f;
     Texture texture_token;
   if (!texture_token.loadFromFile("C:/Users/B.K/Pictures/Camera Roll/Amazing-Flappy-bird1/Amazing-Flappy-bird2/x64/Debug/assets/pngaaa.com-7014332.png"))
   { //tokens
     cerr << "Error no token" << endl;
     return -1;
    }
    
    Sprite tokens;
    tokens.setTexture(texture_token);
    tokens.setScale(0.06f, 0.06f); //sizing tokens
    tokens.setPosition(500, 250); //starting position

    while (window.isOpen()) {
        Time frameTime = timer.restart();
        timecounter += frameTime.asSeconds();


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }


            if (event.type == Event::KeyPressed) {
                if (!flyingbird.InGround) {
                    if (event.key.code == Keyboard::Add || event.key.code == Keyboard::Space ) {
                        flapping(flyingbird, currentLevel); // velocity
                    }
                }
                else {
                    if (event.key.code == Keyboard::Space) {
                       flyingbird.InGround = false;
                       Birdframe(flyingbird, currentLevel);  //to start from origin
                       flapping(flyingbird, currentLevel);
                        //flyingbird.velocity_y = -100.0f;
                    
                    }
                }
                if (event.key.code == Keyboard::Num1) {
                    currentLevel = 1;
                    Birdframe(flyingbird, 1);
                }
                if (event.key.code == Keyboard::Num2) {
                    currentLevel = 2;
                    Birdframe(flyingbird, 2);

                }

                // if (event.key.code == Keyboard::Num3) {

                  //   currentLevel = 3;

                    // Birdframe(flyingbird, 3);

                 //}

            }

        }
        
        while (timecounter >= Fixedtime) {
           // if (InGround) {
            Updating(flyingbird, Fixedtime);
            //}
           if (flyingbird.sprite.getPosition().y >= 450) {
               flyingbird.InGround = true;
    }
           timecounter -= Fixedtime;
            
        }
      float deltaTime = frameTime.asSeconds();
     motionoftoken(tokens, deltaTime);//function calling
     window.clear();
    window.draw(flyingbird.sprite);
    window.draw(tokens);
    window.display();
}
    return 0;
}















































