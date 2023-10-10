#include "Basic.h"

Basic::Basic():Bloon(){
    //Set m_color to a empty string
    m_color = "";
}

Basic::Basic(int health, int location):Bloon(health,location){
    // list of possible colors
    string list_of_colors[6] = {"red","blue","green","yellow","pink","black"};

    //by the passed health, determine the color of the baloon
    if (health == 1){
        m_color = list_of_colors[red];
    }else if(health == 2){
        m_color = list_of_colors[blue];
    }else if(health == 3){
        m_color = list_of_colors[green];
    }else if(health == 4){
        m_color = list_of_colors[yellow];
    }else if(health == 5){
        m_color = list_of_colors[pink];
    }else if(health >= 6){
        m_color = list_of_colors[black];
    }
}

Basic::~Basic(){
    //make m_color a empty string
    m_color.clear();
}

int Basic::Pop(int damage){
    //Get bloon's health
    int bloon_health = GetHealth();
    
    //list of possible colors
    string list_of_colors[6] = {"red","blue","green","yellow","pink","black"};

    //get new bloon health
    bloon_health -= damage;

    //determine the new bloon's color my the new health
    if (bloon_health == 1){
        m_color = list_of_colors[red];
    }else if(bloon_health == 2){
        m_color = list_of_colors[blue];
    }else if(bloon_health == 3){
        m_color = list_of_colors[green];
    }else if(bloon_health == 4){
        m_color = list_of_colors[yellow];
    }else if(bloon_health == 5){
        m_color = list_of_colors[pink];
    }else if(bloon_health >= 6){
        m_color = list_of_colors[black];
    }

    //if the new bloon health is less than or equal to 0
    //tell the user that the bloon is gone and return the amount
    //of health the bloon had
    if (bloon_health <= 0){
        int health = GetHealth();
        SetHealth(bloon_health);
        cout << "The bloon is now gone!" << endl;
        return health;
    
    //else, Tell the user the new health and return the amount of damage
    //done
    }else{
        SetHealth(bloon_health);
        cout << "The ballon is now " << m_color << endl;
        return damage;
    }
        
}

string Basic::GetColor(){
    //return m_color
    return m_color;
}