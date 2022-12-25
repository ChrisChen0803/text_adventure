#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

struct monster{
    int power;
    int reward;
    int row;
    int col;
};
int health;
int damage;
bool alive;
int currRow;
int mapsize;
int currCol;
int day;
int score;
string name;
vector<monster> monster_list;
vector<monster> monsters_alive;
char map[3][3] = {'N','0','1',
                  'H','D','N',
                  'U','T','F'};
//N means nothing;
//U means damage +1;
//F means finish point;
//T means trap
//H means heal;
//D means Detect a random monster;

void createMonster(int row, int col, int power, int reward){
    monster temp;
    temp.row = row;
    temp.col = col;
    temp.power=power;
    temp.reward=reward;
    monster_list.push_back(temp);
    monsters_alive.push_back(temp);
}
int main(){
    mapsize = 3;
    createMonster(0,1,1,2);
    createMonster(0,2,2,2);
    cout<<monster_list[0].power<<endl;
    cout<<"Welcome to Text Adventure!"<<endl;
    cout<<"Your Name? ";
    std::getline(std::cin, name);
    cout<<"Welcome "<<name<<"!"<<endl;
    health = 1;
    damage = 1;
    score = 0;
    alive = true;
    currRow = 0;
    currCol = 0;
    day = 1;
    while(alive){
        cout<<"---------------------"<<endl;
        cout<<"Day "<<day<<endl;
        cout<<"You current Position: (" << currRow << ", " << currCol << ")"<<endl;
        string move;
        cout<<"What direction you want to go?(up/down/left/right)"<<endl;
        std::getline(std::cin, move);
        bool running = true;
        while(running){
            if(move=="up"){
                currRow--;
                running = false;
            }
            else if(move=="down"){
                currRow++;
                running = false;
            }
            else if(move=="left"){
                currCol--;
                running = false;
            }
            else if(move=="right"){
                currCol++;
                running = false;
            }
            else{
                cout<<"Invalid output, please retry."<<endl;
                cout<<"What direction you want to go?(up/down/left/right)"<<endl;
                std::getline(std::cin, move);
            }
        }
        cout<<"Now your position is (" << currRow << ", " << currCol << ")"<<endl;
        //Check if it is out of range
        if(currCol<0||currCol>=mapsize||currRow<0||currRow>=mapsize){
            cout<<"You fall off the cliff. You died!"<<endl;
            alive = false;
        }
        
        if(map[currRow][currCol]=='N'){
            cout<<"Nothing Happens."<<endl;
        }
        //Find the treasure
        else if(map[currRow][currCol]=='F'){
            cout<<"Congratulations! You find the treasure."<<endl;
            cout<<"Your score is "<<score<<endl;
            break;
        }
        else if (map[currRow][currCol]=='T'){
            cout<<"You step into a trap."<<endl;
            health--;
            map[currRow][currCol]='N';
        }
        else if (map[currRow][currCol]=='U'){
            cout<<"Your weapon has been updated."<<endl;
            damage++;
            map[currRow][currCol]='N';
        }
        else if (map[currRow][currCol]=='H'){
            cout<<"Your find a healing heart"<<endl;
            health++;
            map[currRow][currCol]='N';
        }
        else if(map[currRow][currCol]=='D'){
            cout<<"You find a monster detector."<<endl;
            if(monsters_alive.size()==0){
                cout<<"No monster alive!"<<endl;
            }
            else{
                monster detect = monsters_alive[rand()%monsters_alive.size()];
                cout<<"Detected Monster Position: ("<<detect.row<<", "<<detect.col<<")"<<endl;
            }
        }
        else{
            int monster_num = map[currRow][currCol]-'0';
            monster curr_mon = monster_list[monster_num];
            cout<<"You encounter a monster!"<<endl;
            cout<<"Its power: "<<curr_mon.power<<endl;
            cout<<"Your damage: "<<damage<<endl;
            if(curr_mon.power>damage){
                cout<<"Monster beats you, health-1."<<endl;
                health--;
            }
            else{
                cout<<"You kill the monster!"<<endl;
                score = score + curr_mon.reward;
                map[currRow][currCol]='N';
                for(int i=0;i<monsters_alive.size();i++){
                    monster m = monsters_alive[i];
                    if(m.col==curr_mon.col&&m.row==curr_mon.row){
                        monsters_alive.erase(monsters_alive.begin()+i);
                        break;
                    }
                }
            }
        }
        //You die
        if(health<1){
            cout<<"You died!"<<endl;
            alive = false;
        }
        day++;
    }
    cout<<"Thanks for playing"<<endl;
}