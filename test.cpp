#include <iostream>
using namespace std;

struct User{
    char name[16];
    int score;
    int dd;
    int mm;
    int aa;
};

int main(){
    FILE *users;
    User data;
    char ans;

    users = fopen("users.dat","ab");

    if (users == NULL){
        cout << "Error";
        return 1;
    }

    // capture information
    do{
        cout << "User name: ";
        cin >> data.name;
        cout << "Score: ";
        cin >> data.score;
        cout << "Day: ";
        cin >> data.dd;
        cout << "Month: ";
        cin >> data.mm;
        cout << "Year: ";
        cin >> data.aa;

        fwrite(&data,sizeof(User),1,users);
        cout << "Want to add another one s/n: ";
        cin >> ans;
    } while(ans!='n');

    fclose(users);
}