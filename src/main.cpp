#include <bits/stdc++.h>
#include <unistd.h>
#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "volcano.h"
#include "missile.h"
#include "meter.h"
#include "ring.h"
#include "enemy.h"
#include "turret.h"
#include "enemy_bullet.h"
#include "arrow.h"
#include "fuelcan.h"
#include "compass.h"
#include "bombs.h"
#include "zero.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"
#include "seven.h"
#include "eight.h"
#include "nine.h"
#include "parachute.h"
#include "hammer.h"

using namespace std;

GLMatrices Matrices,Matrices1;
GLuint     programID;
GLFWwindow *window;

int width  = 600;
int height = 600;

/**************************
* Customizable functions *
**************************/

#define VOLCANO_COUNT 20
#define ACTIVATION_RANGE 10000

int score=0;

float mouse_speed = 0.005f;
float hori_angle = 3.14f;
float vert_angle = 0.0f;

Plane plane;
Sea sea;
Volcano volcano[VOLCANO_COUNT];

list<Missile> missile,temp_missile;
Missile init_missile;
float missile_clock;

list<Bombs> bombs,temp_bombs;
Bombs init_bombs;
float bomb_clock;

Meter fuel_meter,altitude_meter;

list<Ring> ring,temp_ring;
Ring ring_collision;

list<pair<Enemy,Turret> > combine_enemy;

list<Enemy_Bullet> enemy_bullet,temp_enemy_bullet;

Arrow arrow;

list<FuelCan> fuelcan;

Compass compass;

list<Parachute> parachute;

list<Hammer> hammer;

float loop_clock;
bool loop_in;
float xl,yl,zl,rl;

float roll_clock;
bool roll_in;
float x_roll,y_roll,z_roll,r_roll;

Zero zero[7],zerol;
One one[7],onel;
Two two[7],twol;
Three three[7],threel;
Four four[7];
Five five[7];
Six six[7];
Seven seven[7];
Eight eight[7];
Nine nine[7];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float turn_camera=0;

int cam=3;
float eyet[3],tart[3];

bool missile_flag,bomb_flag;

Timer t60(1.0 / 60);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        missile_flag=1;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        bomb_flag=1;
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    //Plane View
    if(cam==0)
    {
        eyet[0]=plane.position.x + 2*plane.fund*sin(turn_camera*M_PI/180.0);
        eyet[1]=plane.position.y;
        eyet[2]=plane.position.z + 2*plane.fund*cos(turn_camera*M_PI/180.0);
        tart[0]=plane.position.x + 5*plane.fund*sin(turn_camera*M_PI/180.0);
        tart[1]=plane.position.y;
        tart[2]=plane.position.z + 5*plane.fund*cos(turn_camera*M_PI/180.0);
    }
    //Top View
    if(cam==1)
    {
        eyet[0]=plane.position.x;
        eyet[1]=plane.position.y+6;
        eyet[2]=plane.position.z-0.1;
        tart[0]=plane.position.x;
        tart[1]=plane.position.y;
        tart[2]=plane.position.z;
    }
    //Tower View
    if(cam==2)
    {
        // eyet[0]=plane.position.x+4;
        // eyet[1]=max(plane.position.y+10,20.0f);
        // eyet[2]=max(plane.position.y+10,20.0f);
        eyet[0]=4;
        eyet[1]=20;
        eyet[2]=20;
        tart[0]=plane.position.x;
        tart[1]=plane.position.y;
        tart[2]=plane.position.z;
    }
    //Follow-cam View
    if(cam==3)
    {
        eyet[0]=plane.position.x + 5*plane.fund*sin(-turn_camera*M_PI/180.0);
        eyet[1]=plane.position.y+1;
        eyet[2]=plane.position.z-5*plane.fund*cos(-turn_camera*M_PI/180.0);
        tart[0]=plane.position.x;
        tart[1]=plane.position.y;
        tart[2]=plane.position.z;
    }
    //Helicopter-cam View
    if(cam==4)
    {
        double delta_x,delta_y;
        glfwGetCursorPos(window,&delta_x,&delta_y);
        delta_x =width/2 - delta_x,delta_y = height/2 - delta_y;        
        double sphere_radius = 3,h = plane.position.y - 15 + mouse_speed*delta_y,dx=mouse_speed*delta_x;
        eyet[0]=dx+plane.position.x+sphere_radius*plane.fund*sin(-turn_camera*M_PI/180.0);
        eyet[1]=h+15;
        eyet[2]=sqrt(abs(sphere_radius*sphere_radius - h*h -(eyet[0])*(eyet[0])))+plane.position.z-sphere_radius-sphere_radius*plane.fund*cos(-turn_camera*M_PI/180.0);
        tart[0]=plane.position.x;
        tart[1]=plane.position.y;
        tart[2]=plane.position.z;
    }
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    //Plane View
    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye(eyet[0],eyet[1],eyet[2]);
    glm::vec3 target(tart[0],tart[1],tart[2]);
    // glm::vec3 eye(0,1,-1);
    // glm::vec3 target(0,0,0);
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(loop_in and !roll_in)
        plane.draw(VP,turn_camera,M_PI*(glfwGetTime()-loop_clock),0);
    else if(!loop_in and roll_in)
        plane.draw(VP,turn_camera,0,M_PI*(glfwGetTime()-roll_clock));
    else
        plane.draw(VP,turn_camera,0,0);
    sea.draw(VP);
    for(list<pair<Enemy,Turret> >::iterator it=combine_enemy.begin();it!=combine_enemy.end();it++)
        it->first.draw(VP),it->second.draw(VP);
    temp_enemy_bullet.clear();
    for(list<Enemy_Bullet>::iterator it=enemy_bullet.begin();it!=enemy_bullet.end();it++)
    {
        if(abs((it->position.x)*(it->position.x)+(it->position.y)*(it->position.y)+(it->position.z)*(it->position.z)
            -((plane.position.x)*(plane.position.x)+(plane.position.y)*(plane.position.y)+(plane.position.z)*(plane.position.z)))
            <ACTIVATION_RANGE)
        {
            it->draw(VP);
            temp_enemy_bullet.push_back(*it);
        }
    }
    enemy_bullet=temp_enemy_bullet;
    for(int i=0;i<VOLCANO_COUNT;i++)
        volcano[i].draw(VP);
    temp_missile.clear();
    for(list<Missile>::iterator it=missile.begin();it!=missile.end();it++)
    {
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<ACTIVATION_RANGE)
        {
            it->draw(VP);
            temp_missile.push_back(*it);
        }
    }
    missile=temp_missile;
    temp_bombs.clear();
    for(list<Bombs>::iterator it = bombs.begin();it!=bombs.end();it++)
    {
        if(it->position.y>=0)
        {
            it->draw(VP);
            temp_bombs.push_back(*it);
        }
    }
    bombs=temp_bombs;
    for(list<Ring>::iterator it=ring.begin();it!=ring.end();it++)
        it->draw(VP);
    arrow.draw(VP);
    for(list<FuelCan>::iterator it=fuelcan.begin();it!=fuelcan.end();it++)
    	it->draw(VP);
    for(list<Parachute>::iterator it=parachute.begin();it!=parachute.end();it++)
        it->draw(VP);
    for(list<Hammer>::iterator it=hammer.begin();it!=hammer.end();it++)
        it->draw(VP);
    glm::vec3 eye1(0,0,1);
    glm::vec3 target1(0,0,0);
    Matrices1.view = glm::lookAt( eye1, target1, up );
    glm::mat4 VP1 = Matrices.projection * Matrices1.view;
    fuel_meter.draw(VP1,(plane.fuel/plane.max_fuel)*M_PI);
    altitude_meter.draw(VP1,(plane.position.y/plane.max_height)*M_PI);
    compass.draw(VP1);

    int rem,n=score;
    n=min(n,9999999);
    for(int k=0;k<7;k++)
    {
        rem=n%10;
        n/=10;
        switch(rem)
        {
            case 0:zero[k].draw(VP1);
                    break;
            case 1:one[k].draw(VP1);
                    break;
            case 2:two[k].draw(VP1);
                    break;
            case 3:three[k].draw(VP1);
                    break;
            case 4:four[k].draw(VP1);
                    break;
            case 5:five[k].draw(VP1);
                    break;
            case 6:six[k].draw(VP1);
                    break;
            case 7:seven[k].draw(VP1);
                    break;
            case 8:eight[k].draw(VP1);
                    break;
            case 9:nine[k].draw(VP1);
                    break;
        }
    }
    switch(plane.lives)
    {
    	case 0:zerol.draw(VP1);
                    break;
        case 1:onel.draw(VP1);
                break;
        case 2:twol.draw(VP1);
                break;
        case 3:threel.draw(VP1);
                break;	
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);

    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    int f = glfwGetKey(window, GLFW_KEY_F);
    int g = glfwGetKey(window, GLFW_KEY_G);
    int h = glfwGetKey(window, GLFW_KEY_H);
    int j = glfwGetKey(window, GLFW_KEY_J);
    int k = glfwGetKey(window, GLFW_KEY_K);

    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);

    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    int x = glfwGetKey(window, GLFW_KEY_X);

    if(up)
        plane.position.y+=0.1;
    if(down)
        plane.position.y-=0.1;
    plane.position.y=max(0.0f,min(plane.position.y,plane.max_height));
    if(f)
        cam=0; //Plane View
    if(g)
        cam=1; //Top View
    if(h)
        cam=2; //Tower View
    if(j)
        cam=3; //Follow-cam View
    if(k)
        cam=4; //Helicopter-cam View

    if(z and !loop_in and !roll_in)
    {
        loop_in=1;
        loop_clock=glfwGetTime();
        rl=3;
        xl=plane.position.x;
        yl=plane.position.y+rl; 
        zl=plane.position.z;
    }
    if(x and !loop_in and !roll_in)
    {
        roll_in=1;
        roll_clock=glfwGetTime();
        r_roll=3;
        x_roll=plane.position.x;
        y_roll=plane.position.y+rl; 
        z_roll=plane.position.z;
    }
    if(e)
        plane.rotate('+');
    if(q)
        plane.rotate('-');
    if(!loop_in and !roll_in)
    {
        if(w)
        {
            plane.position.z+=0.1*cos(turn_camera*M_PI/180.0);
            plane.position.x+=0.1*sin(turn_camera*M_PI/180.0);
        }
        if(s)
        {
            plane.position.z-=0.1*cos(turn_camera*M_PI/180.0);
            plane.position.x-=0.1*sin(turn_camera*M_PI/180.0);
        }
        if(a)
            turn_camera+=1;
        if(d)
            turn_camera-=1;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) and glfwGetTime()-missile_clock>1)
    {
        missile_clock=glfwGetTime();
        missile.push_back(init_missile);
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) and glfwGetTime()-bomb_clock>1)
    {
        bomb_clock=glfwGetTime();
        bombs.push_back(init_bombs);
    }
}

void tick_elements() {
    if(loop_in and !roll_in)
    {
        if(glfwGetTime()-loop_clock > 2)
            loop_in=0;
        else
        {
            plane.position.y=yl+rl*sin(M_PI*(glfwGetTime()-loop_clock));
            plane.position.z=zl+rl*cos(M_PI*(glfwGetTime()-loop_clock))*cos(turn_camera*M_PI/180.0);
            plane.position.x=xl+rl*cos(M_PI*(glfwGetTime()-loop_clock))*sin(turn_camera*M_PI/180.0);
        }
    }
    else if(roll_in and !loop_in)
    {
        if(glfwGetTime()-roll_clock > 2)
            roll_in=0;
        else
        {
            if(turn_camera<=180)
                plane.position.z+=0.1;
            else
                plane.position.z-=0.1;
            plane.position.y=y_roll+r_roll*sin(M_PI*(glfwGetTime()-roll_clock));
            plane.position.x=x_roll+r_roll*cos(M_PI*(glfwGetTime()-roll_clock));
        }
    }
    plane.tick();
    arrow.position.x = plane.position.x;
    arrow.position.y = plane.position.y + 0.5;
    arrow.position.z = plane.position.z;
    for(int i=0;i<VOLCANO_COUNT;i++)
        volcano[i].tick();
    for(int i=0;i<VOLCANO_COUNT;i++)
        if((volcano[i].position.x-plane.position.x)*(volcano[i].position.x-plane.position.x)+(volcano[i].position.y-plane.position.y)*(volcano[i].position.y-plane.position.y)+(volcano[i].position.z-plane.position.z)*(volcano[i].position.z-plane.position.z)<5.2*5.2)
        {
            plane.lives=0;
            break;
        }    
    temp_ring.clear();
    for(list<Ring>::iterator it=ring.begin();it!=ring.end();it++)
    {
        ring_collision=*it;
        if(!detect_collision_ring())
            temp_ring.push_back(*it);
        else
            score+=100;
    }
    ring=temp_ring;
    float dirx,diry,dirz,mini=1e18;
    for(list<pair<Enemy,Turret> >::iterator it=combine_enemy.begin();it!=combine_enemy.end();it++)
    {
        if((it->second.position.x-plane.position.x)*(it->second.position.x-plane.position.x)+(it->second.position.y-plane.position.y)*(it->second.position.y-plane.position.y)+(it->second.position.z-plane.position.z)*(it->second.position.z-plane.position.z)<ACTIVATION_RANGE)
        {
            it->second.tick();
            if(it->second.fire)
            {
                it->second.fire=0;
                enemy_bullet.push_back(Enemy_Bullet(it->second.position.x,it->second.position.y,it->second.position.z,COLOR_WHITE,plane.position.x-it->second.position.x,plane.position.y-it->second.position.y,plane.position.z-it->second.position.z));
            }
        }
        if((it->second.position.x-plane.position.x)*(it->second.position.x-plane.position.x)+(it->second.position.y-plane.position.y)*(it->second.position.y-plane.position.y)+(it->second.position.z-plane.position.z)*(it->second.position.z-plane.position.z)<mini)
        {
            mini = (it->second.position.x-plane.position.x)*(it->second.position.x-plane.position.x)+(it->second.position.y-plane.position.y)*(it->second.position.y-plane.position.y)+(it->second.position.z-plane.position.z)*(it->second.position.z-plane.position.z);
            dirx = it->second.position.x - arrow.position.x;
            diry = it->second.position.y - arrow.position.y;
            dirz = it->second.position.z - arrow.position.z;
        }
    }
    for(list<FuelCan>::iterator it=fuelcan.begin();it!=fuelcan.end();it++)
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<2+2*plane.fund*plane.fund)
        {
            it=fuelcan.erase(it);
            plane.fuel=plane.max_fuel;
            break;
        }
    arrow.tick(dirx,diry,dirz,turn_camera);
    init_missile.position.x=plane.position.x;
    init_missile.position.y=plane.position.y;
    init_missile.position.z=plane.position.z;
    init_missile.rotation=turn_camera;
    for(list<Missile>::iterator it=missile.begin();it!=missile.end();it++)
        it->tick();
    init_bombs.position.x=plane.position.x;
    init_bombs.position.y=plane.position.y;
    init_bombs.position.z=plane.position.z;
    for(list<Bombs>::iterator it=bombs.begin();it!=bombs.end();it++)
        it->tick();
    for(list<Enemy_Bullet>::iterator it=enemy_bullet.begin();it!=enemy_bullet.end();it++)
    {
        it->tick();
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<3*(it->radius+plane.fund))
        {
            it = enemy_bullet.erase(it);
            plane.lives--;
        }
    }
    for(list<pair<Enemy,Turret> >::iterator it=combine_enemy.begin();it!=combine_enemy.end();it++)
    { 
        for(list<Missile>::iterator it1=missile.begin();it1!=missile.end();it1++)
        {
            if((it->second.position.x-it1->position.x)*(it->second.position.x-it1->position.x)+(it->second.position.y-it1->position.y)*(it->second.position.y-it1->position.y)+(it->second.position.z-it1->position.z)*(it->second.position.z-it1->position.z)<20.0f and (it1->position.x>=it->second.position.x-it->second.length and it1->position.x<=it->second.position.x+it->second.length) and 
                (it1->position.y>=it->second.position.y-it->second.length and it1->position.y<=it->second.position.y+it->second.length) and (it1->position.z>=it->second.position.z-it->second.length and it1->position.z<=it->second.position.z+it->second.length))
            {
               it = combine_enemy.erase(it);
               missile.erase(it1);
               score+=1000;
               break;
            }
        }
    }
    for(list<pair<Enemy,Turret> >::iterator it=combine_enemy.begin();it!=combine_enemy.end();it++)
    { 
        for(list<Bombs>::iterator it1=bombs.begin();it1!=bombs.end();it1++)
        {
            if((it->second.position.x-it1->position.x)*(it->second.position.x-it1->position.x)+(it->second.position.y-it1->position.y)*(it->second.position.y-it1->position.y)+(it->second.position.z-it1->position.z)*(it->second.position.z-it1->position.z)<20.0f and (it1->position.x>=it->second.position.x-it->second.length and it1->position.x<=it->second.position.x+it->second.length) and 
                (it1->position.y>=it->second.position.y-it->second.length and it1->position.y<=it->second.position.y+it->second.length) and (it1->position.z>=it->second.position.z-it->second.length and it1->position.z<=it->second.position.z+it->second.length))
            {
               it = combine_enemy.erase(it);
               bombs.erase(it1);
               score+=1000;
               break;
            }
        }
    }
    for(list<Parachute>::iterator it=parachute.begin();it!=parachute.end();it++)
    {
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<(ACTIVATION_RANGE/2))
  	      it->tick();
    }
    for(list<Parachute>::iterator it=parachute.begin();it!=parachute.end();it++)
    {
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<(ACTIVATION_RANGE/2))
        {
	        for(list<Missile>::iterator it1=missile.begin();it1!=missile.end();it1++)
	        {
	            if((it->position.x-it1->position.x)*(it->position.x-it1->position.x)+(it->position.y-it1->position.y)*(it->position.y-it1->position.y)+(it->position.z-it1->position.z)*(it->position.z-it1->position.z)<3*(1+it1->radius*it1->radius))
	            {
	               it = parachute.erase(it);
	               missile.erase(it1);
	               score+=500;
	               break;
	            }
	        }
        }
    }
    for(list<Parachute>::iterator it=parachute.begin();it!=parachute.end();it++)
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<3*plane.fund+500 and (plane.position.x>=it->position.x-10 and plane.position.x>=it->position.x+10)
         and (plane.position.y<=it->position.x and plane.position.y>=it->position.x-10) and (plane.position.z>=it->position.z-10 and plane.position.z>=it->position.z+10))
        {
            it = parachute.erase(it);
            plane.lives--;
        }

    for(list<Hammer>::iterator it=hammer.begin();it!=hammer.end();it++)
    	if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<ACTIVATION_RANGE)
	        it->tick();
    for(list<Hammer>::iterator it=hammer.begin();it!=hammer.end();it++)
    {
        if((it->position.x-plane.position.x)*(it->position.x-plane.position.x)+(it->position.y-plane.position.y)*(it->position.y-plane.position.y)+(it->position.z-plane.position.z)*(it->position.z-plane.position.z)<3*(1+plane.fund))
        {
            it = hammer.erase(it);
            plane.lives--;
        }
    }
    for(list<Hammer>::iterator it=hammer.begin();it!=hammer.end();it++)
    {
        for(list<Missile>::iterator it1=missile.begin();it1!=missile.end();it1++)
        {
            if((it->position.x-it1->position.x)*(it->position.x-it1->position.x)+(it->position.y-it1->position.y)*(it->position.y-it1->position.y)+(it->position.z-it1->position.z)*(it->position.z-it1->position.z)<3*(1+it1->radius))
            {
                it = hammer.erase(it);
                missile.erase(it1);
                score+=2000;
                break;
            }
        }
    }

    if(turn_camera<-360)
        turn_camera+=360;
    if(turn_camera>360)
        turn_camera-=360;
    compass.tick(-turn_camera);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Plane(0,15,0, COLOR_RED);
    sea = Sea(0,0,0,COLOR_BLUE);
    int c=0;
    for(int i=-80;i<80;i+=40)
        for(int z=-80;z<=80;z+=40)
            volcano[c++] = Volcano(i,0,z,COLOR_RED,COLOR_GREY);
    
    init_missile = Missile(0,0,0,COLOR_YELLOW);
    missile_clock=-1;
    init_bombs = Bombs(0,0,0,COLOR_DARK_GREEN);
    bomb_clock=-1;
    fuel_meter = Meter(-0.22,0.2,0.5,COLOR_RED_BLOOD);
    altitude_meter = Meter(-0.22,0.1,0.5,COLOR_LIGHT_GREEN);
    compass = Compass(-0.17,-0.1,0.5,COLOR_RED_BLOOD);

    for(int x=3;x<=150;x+=30)
        for(int y=15;y<=25;y+=3)
            for(int z=10;z<=150;z+=30)
                ring.push_back(Ring(x,y,z,COLOR_RING));

    for(int x=13;x<=130;x+=25)
        for(int z=13;z<=130;z+=25)
            parachute.push_back(Parachute(x,20,z,COLOR_RED));

    float dirx,diry,dirz,mini=1e18;
    for(int x=10;x<300;x+=150)
        for(int z=10;z<300;z+=150)
         {
            Enemy enemy = Enemy(x,0,z,COLOR_GROUND);
            Turret turret = Turret(enemy.turret_pos.x,enemy.turret_pos.y,enemy.turret_pos.z,COLOR_BLACK);
            combine_enemy.push_back(make_pair(enemy,turret));
            if(abs((enemy.turret_pos.x*enemy.turret_pos.x+enemy.turret_pos.y*enemy.turret_pos.y+enemy.turret_pos.z*enemy.turret_pos.z)-((plane.position.x*plane.position.x+plane.position.y*plane.position.y+plane.position.z*plane.position.z)))<mini)
            {
                mini=abs((enemy.turret_pos.x*enemy.turret_pos.x+enemy.turret_pos.y*enemy.turret_pos.y+enemy.turret_pos.z*enemy.turret_pos.z)-((plane.position.x*plane.position.x+plane.position.y*plane.position.y+plane.position.z*plane.position.z)));
                dirx = enemy.turret_pos.x - plane.position.x;
                diry = enemy.turret_pos.y - plane.position.y;
                dirz = enemy.turret_pos.z - plane.position.z;
            }
         }
    arrow = Arrow(plane.position.x,plane.position.y,plane.position.z,COLOR_RED_BLOOD,dirx,diry,dirz);

    for(int x=40;x<=150;x+=50)
        hammer.push_back(Hammer(x,20,x,COLOR_BLACK));

    for(int x=3;x<=150;x+=25)
        for(int z=7;z<=150;z+=25)
	        fuelcan.push_back(FuelCan(x,20,z,COLOR_FUEL));
    
    int j=0;
    for(float i=0.5;i>=0;i-=0.08)
    {
        zero[j]=Zero(i,0.5,COLOR_LIGHT_PINK);
        one[j]=One(i,0.5,COLOR_LIGHT_PINK);
        two[j]=Two(i,0.5,COLOR_LIGHT_PINK);
        three[j]=Three(i,0.5,COLOR_LIGHT_PINK);
        four[j]=Four(i,0.5,COLOR_LIGHT_PINK);
        five[j]=Five(i,0.5,COLOR_LIGHT_PINK);
        six[j]=Six(i,0.5,COLOR_LIGHT_PINK);
        seven[j]=Seven(i,0.5,COLOR_LIGHT_PINK);
        eight[j]=Eight(i,0.5,COLOR_LIGHT_PINK);
        nine[j]=Nine(i,0.5,COLOR_LIGHT_PINK);
        j++;
        if(j==7)
            break;
    }

    zerol = Zero(-0.2,0.5,COLOR_LIGHT_PINK);
    onel = One(-0.2,0.5,COLOR_LIGHT_PINK);
    twol = Two(-0.2,0.5,COLOR_LIGHT_PINK);
    threel = Three(-0.2,0.5,COLOR_LIGHT_PINK);

    loop_clock = -1;
    loop_in=0;

    roll_clock = -1;
    roll_in=0;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));

    glfwSetCursorPos(window,width/2,height/2);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    window = initGLFW(width, height);

    initGL (window, width, height);

    eyet[0]=plane.position.x;
    eyet[1]=plane.position.y+1;
    eyet[2]=plane.position.z-1;
    tart[0]=plane.position.x;
    tart[1]=plane.position.y;
    tart[2]=plane.position.z;
    
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            plane.fuel -= 0.05;
            tick_elements();
            tick_input(window);
            if(plane.fuel<=0 || !plane.lives)
            {
            	cout<<"Game Over\n";
           		return 0;
            }
            if(combine_enemy.size()==0)
            {
                cout<<"You Win\n";
                cout<<"Score: "<<score<<endl;
                return 0;
            }
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision_ring(){
    if(abs(plane.position.z-ring_collision.position.z)<=(ring_collision.thickness/2)+plane.fund and (plane.position.x<=ring_collision.position.x+ring_collision.radius and plane.position.x>=ring_collision.position.x-ring_collision.radius) and (plane.position.y<=ring_collision.position.y+ring_collision.radius and plane.position.y>=ring_collision.position.y-ring_collision.radius))
        return 1;
    return 0;
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(60 * M_PI/180,(double)1,0.1,(double)10000);
}
