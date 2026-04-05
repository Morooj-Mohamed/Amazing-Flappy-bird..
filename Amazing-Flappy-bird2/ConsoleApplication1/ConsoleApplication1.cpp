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
    Texture textures[3];// for two pic for bird.
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

void Birdframe(Bird& bird) {
    bird.textures[0].loadFromFile("C:/Users/B.K/Desktop/Project/b0.png");
    bird.textures[1].loadFromFile("C:/Users/B.K/Desktop/Project/b1.png");
    bird.textures[2].loadFromFile("C:/Users/B.K/Desktop/Project/b2.png");

    bird.sprite.setTexture(bird.textures[0]);
    bird.sprite.setPosition(100, 220);
    bird.y = 320;


    if (!bird.flyingbuffer.loadFromFile("Flappy Bird_sounds_sfx_wing.wav")) {
        cout << "Error!! The file doesnot upload." << endl;
    }
    else {
        bird.flyingsound.setBuffer(bird.flyingbuffer);
      //  bird.flyingsound.setVolume(40); 
    }
    if (!bird.henediBuffer.loadFromFile("WhatsApp Audio 2026-03-24 at 9.39.51 PM (1).wav")) {
        cout << "Error ! Henedi Sound Not Found" << endl;
    }
    else {
        bird.henediSound.setBuffer(bird.henediBuffer);
        bird.henediSound.setVolume(80); //  عالي شوية عشان يبان
    }
    bird.jumpcount = 0;

    bird.velocity_y = 0;
    bird.texture_swaping = 0;
      //  bird.sound_fly = 1;
      //bird.counter = 0;
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
        if (bird.counter >= 0.15f) {
            if (bird.texture_swaping == 0) {
                bird.texture_swaping = 1;
            }
            else {
                bird.texture_swaping = 0;
            }

            bird.sprite.setTexture(bird.textures[bird.texture_swaping]);
            bird.counter = 0;   //to start a new from zero again &again
        }

        if (bird.velocity_y < 0) {
            bird.sprite.setRotation(-20.0f);
        }
        else {
            // bird.sprite.setRotation(40);
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





void flapping(Bird& bird) {
    bird.velocity_y = -250;
    bird.flyingsound.play();

    bird.jumpcount++;

    if (bird.jumpcount >= 10) {
        bird.henediSound.play();
        bird.jumpcount = 0; // ارجع عد من الأول
    }
}

int main() {
    int windowWidth = 900;
    int windowlength = 504; // i think it is perfect size!
    RenderWindow window(VideoMode(windowWidth, windowlength), "Amazing Flappy Bird");
    window.setFramerateLimit(60);

    Bird flyingbird;
    Birdframe(flyingbird);
    flyingbird.sprite.setOrigin(34 / 2, 26 / 2); //علشان لما اجي اغير الحركه تبقي معدوله

   // bool InGround = false;

    Clock timer;
    float timecounter = 0.0f;
    const float Fixedtime = 1.0f / 60.0f;
 Texture texture_token;
 if (!texture_token.loadFromFile("pngaaa.com-7014332.png"))
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
                        flapping(flyingbird); // velocity
                    }
                }
                else {
                    if (event.key.code == Keyboard::Space) {
                       flyingbird.InGround = false;
                        Birdframe(flyingbird);  //to start from origin
                        flapping(flyingbird);
                        //flyingbird.velocity_y = -100.0f;
                    
                    }
                }
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
    //  Uptading(flyingbird, timestep);
   // window.clear(Color::White);
    window.draw(flyingbird.sprite);
    window.draw(tokens);
    window.display();
}
    return 0;
}



//فاضلي اوقف الجناح اول ما يقع DONE
//يكبر ويصغر 






















/* float birdY = bird.getPosition().y;            // just tryy
           if (birdY > 550) {  //ground
               bird.setPosition(bird.getPosition().x, 550);
               velocity_bird = 0;
           }
           if (birdY < 0) {   // screen above
               bird.setPosition(bird.getPosition().x, 0);
           }*/

           //float velocity_bird = 0.0;
           //float gravity = 0.1f;


           // Texture birdtexture;
               //birdtexture.loadFromFile("");
               //Sprite bird;
               //bird.setTexture(birdtexture);

               //bird.setScale(1, 1);
               //bird.setPosition(600, 300);
