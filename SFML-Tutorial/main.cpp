#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <sstream>

using namespace sf;
using namespace std;

int score=0;
int game=0;
int size=16;
int L=30,l=20;
int w = size*L; //chiều rộng cửa sổ
int h = size*l; //chiều cao cửa sổ

int dir; // hướng của rắn
int num=4;  // chiều dài rắn

struct Snake
{
    int x,y;
}
    s[100]; //chiều dài max = 100

struct Food //địa điểm đồ ăn
{
    int x,y;
}
f;

void Logic() //di chuyển của rắn
 {
    for (int i=num;i>0;--i)
	 {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
	 }

    if (dir==0) s[0].y+=1;  //di chuyển của đầu rắn
    if (dir==1) s[0].x-=1;
    if (dir==2) s[0].x+=1;
    if (dir==3) s[0].y-=1;

	if ((s[0].x==f.x) && (s[0].y==f.y)) //khi rắn ăn được đồ ăn
      {
        num++;          // tăng 1 đốt
        score++;
    	f.x=rand() % L;
        f.y=rand() % l;
        }

    if (s[0].x>L) s[0].x=0; // rắn di chuyển ra ngoài cửa sổ nó sẽ sang từ bên đối diện
    if (s[0].x<0) s[0].x=L;
    if (s[0].y>l) s[0].y=0;
    if (s[0].y<0) s[0].y=l;

    for (int i=1;i<num;i++)

     if (s[0].x==s[i].x && s[0].y==s[i].y)
     {
        game=1;
        num=i;

     }

 }
int main()
{
    Font aerial;
    aerial.loadFromFile("C:/SFML-Tutorial/bin/Debug/arial.ttf");
    ostringstream ssScore;
    ssScore<<"Score: "<<score;
    Text lblscore;
    lblscore.setCharacterSize(20);
    lblscore.setPosition({10,10});
    lblscore.setFont(aerial);
    lblscore.setColor(Color::Black);
    lblscore.setString(ssScore.str());
	srand(time(0));
    RenderWindow window(VideoMode(w, h), "Snake Game!");

	Texture t1,t2,t3,t4;
    t1.loadFromFile("C:/SFML-Tutorial/bin/Debug/Light Purple Blue.jpg"); //nền
	t2.loadFromFile("images/white.png");    //đồ ăn
	t3.loadFromFile("images/green.png");    //thân rắn
	t4.loadFromFile("images/red.png");      //đầu rắn


    Sprite background(t1);
	Sprite fruit(t2);
	Sprite snake(t3);
	Sprite snakeh(t4);

	Clock clock;
    float timer=0, delay=0.1;

	f.x=10;
    f.y=10;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
        timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) dir=1;
	    if (Keyboard::isKeyPressed(Keyboard::D))  dir=2;
	    if (Keyboard::isKeyPressed(Keyboard::W)) dir=3;
		if (Keyboard::isKeyPressed(Keyboard::S)) dir=0;

		if (timer>delay)
        {
            timer=0;
            Logic();
		}
    window.clear();

    window.draw(background);

    for(int i=0;i<num;i++)
    {
        snake.setPosition(s[i].x*size,s[i].y*size);
        window.draw(snake); // tạo thân rắn
    }

        snakeh.setPosition(s[0].x*size,s[0].y*size);
        window.draw(snakeh);    //tạo đầu rắn
        fruit.setPosition(f.x*size,f.y*size);   // tạo đồ ăn
    window.draw(fruit);
    window.draw(lblscore);
    ssScore.str("");
    ssScore<<"Score: "<<score;
    lblscore.setString(ssScore.str());

    if(game)
    {
        cout<<"Game Over"<<endl;
        cout<<"Your score: "<<score<<endl;
        system("pause");
        window.close();
    }
	window.display();
	}

    return 0;
}
