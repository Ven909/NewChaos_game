//made by Aws Khaleel and Venkata G. Ande

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace sf;

int main()
{

    //makes a video mode object
    VideoMode vm(1920, 1080);
    //Creates an open window
    RenderWindow window(vm, "Chaos Game", Style::Default);
 
    RectangleShape rect(Vector2f(2, 2));

    // may wanna use pairs instead?? already included the header btw: #include <utility>
    //don't know if this is how vector 2f is used??
    vector<Vector2f> vertexes; //used to store the first 3 clicks which will form teh triangle
    vector<Vector2f> points;   //used to store the 4 click
    
    //handling the user input
    Event event;
    while (window.isOpen())
    {
            
        while (window.pollEvent(event))
        {
            if ((event.type == Event::Closed)  || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                window.close();
            }
            //when the user pushes the mouse button...
            if (event.type == Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    //if the vertexes vector reaches a size of 3, push the fourth point into the points vector instead to start the game
                    if(vertexes.size() == 3)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));  // this notation may be off
                    }
                    //otherwise push the 3 points into the vertexes vector
                    else
                    {
                        vertexes.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));  // this notation may be off
                    }     
                    
                }
            }
            
        }

        //telling the user how to use the program 
        Text promptUser;
        promptUser.setString("Welcome to the Chaos Game! " 
                            "Click 4 times using your mouse. The first 3 clicks will be used to make a triangle and \nthe fourth click will start the game.");
        promptUser.setCharacterSize(24);        //setting font size
        promptUser.setFillColor(Color::White);   //setting font color
        promptUser.setPosition(10, 10);         //positioning the text
        Font font;
        font.loadFromFile("fonts/KOMIKAP_.ttf");  //change to different font if needed, also put it in a folder called fonts
        //font.loadFromFile("fonts/EVILDEAD.ttf"); //doesn't load properly for some reason
        promptUser.setFont(font);
        

        //drawing the midpoints to generate the fractal
        if (points.size() > 0)
        {  
            int vertexRand = rand() % 3; // choosing random vertex point for the triangle
            
            int lastPoint = points.size() - 1;  //the last index in the points index
            int Mid_x = (points[lastPoint].x + vertexes[vertexRand].x) / 2;   // the x coordinate for the midpoint
            int Mid_y = (points[lastPoint].y + vertexes[vertexRand].y) / 2;   // the y coordinate for the midpoint
        
            points.push_back(Vector2f(Mid_x, Mid_y));

            rect.setPosition(Mid_x, Mid_y);  // instructing what coordinate to draw the dots
        }
        //setting the color of the dots
        rect.setFillColor(Color::Red); 
        
        //draw the coordinate points 
        
        //draw triangle
        for (long unsigned int i = 0; i < vertexes.size(); i++)
        {
            rect.setPosition(vertexes.at(i).x, vertexes.at(i).y);
            window.draw(rect);
        }
        //draw the fractal part
        for (long unsigned int i = 0; i < points.size(); i++)
        {
            //if (points.size() > 0)
            //{
                rect.setPosition(points.at(i).x, points.at(i).y);
                window.draw(rect);
            //}

        }

       //display everything created
        
        window.draw(promptUser);

        window.display();

        
       
    }
    return 0;
}
